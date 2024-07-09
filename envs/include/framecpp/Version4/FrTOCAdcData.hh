//
// LDASTools frameCPP - A library implementing the LIGO/Virgo frame
// specification
//
// Copyright (C) 2018 California Institute of Technology
//
// LDASTools frameCPP is free software; you may redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 (GPLv2) of the
// License or at your discretion, any later version.
//
// LDASTools frameCPP is distributed in the hope that it will be useful, but
// without any warranty or even the implied warranty of merchantability
// or fitness for a particular purpose. See the GNU General Public
// License (GPLv2) for more details.
//
// Neither the names of the California Institute of Technology (Caltech),
// The Massachusetts Institute of Technology (M.I.T), The Laser
// Interferometer Gravitational-Wave Observatory (LIGO), nor the names
// of its contributors may be used to endorse or promote products derived
// from this software without specific prior written permission.
//
// You should have received a copy of the licensing terms for this
// software included in the file LICENSE located in the top-level
// directory of this package. If you did not, you can view a copy at
// http://dcc.ligo.org/M1500244/LICENSE
//

#ifndef FrameCPP_VERSION_4_FrTOCAdcData_HH
#define FrameCPP_VERSION_4_FrTOCAdcData_HH

#include "ldastoolsal/unordered_map.hh"

#include "framecpp/Common/FrTOC.hh"

#include "framecpp/Version4/FrameSpec.hh"
#include "framecpp/Version4/FrTOCTypes.hh"
#include "framecpp/Version4/STRING.hh"

namespace FrameCPP
{
    namespace Common
    {
        class TOCInfo;
    }

    namespace Version_4
    {
        //===================================================================
        //===================================================================
        class FrTOCAdcData : public FrTOCTypes
        {
        public:
            typedef STRING name_type;
            typedef INT_4U nADC_type;
            typedef INT_4U channelID_type;
            typedef INT_4U groupID_type;

            struct adc_info_type
            {
                channelID_type               channelID;
                groupID_type                 groupID;
                std::vector< position_type > positionADC;
            };
            typedef std::map< name_type, adc_info_type > MapADC_type;

            FrTOCAdcData( );

            Common::FrameSpec::size_type
            Bytes( const Common::StreamBase& Stream ) const;

            static void Description( Common::Description& Desc );

            const MapADC_type& GetADC( ) const;

            MapADC_type::const_iterator GetADC( const std::string& Name ) const;

            MapADC_type::const_iterator GetADC( INT_4U index ) const;

            void QueryADC( const Common::TOCInfo& Info,
                           INT_4U                 FrameOffset,
                           INT_8U                 Position );

            bool operator==( const FrTOCAdcData& RHS ) const;

        protected:
            typedef std::vector< name_type > key_container_type;

            //-----------------------------------------------------------------
            // Offset from the end of file for the
            // start of the array of ADC positions in the TOC
            //-----------------------------------------------------------------
            key_container_type m_keys;
            MapADC_type        m_adc_info;

            FrTOCAdcData( Common::IStream& Stream, INT_4U FrameCount );

            //-----------------------------------------------------------------
            /// \brief Iterate over contents.
            ///
            /// \param[in] Info
            ///     Specifies the type of information to be searched.
            ///
            /// \param[in] Action
            ///     Action to be taken for each piece of information found.
            //-----------------------------------------------------------------
            void forEach( Common::FrTOC::query_info_type Info,
                          Common::FrTOC::FunctionBase&   Action ) const;

            void cachePositions( istream_type& Stream );

            void seekPositions( istream_type& Stream, channelID_type Channel );

            void seekPositions( istream_type&      Stream,
                                const std::string& Channel );

            void write( Common::OStream& Stream ) const;

        private:
            typedef LDASTools::AL::unordered_map< std::string, INT_4U >
                                                 reverse_lookup_type;
            typedef std::vector< position_type > positions_cache_type;

            MapADC_type& getADC( );

            MapADC_type::iterator getADC( const std::string& Name );

            MapADC_type::iterator getADC( INT_4U index );

            //-----------------------------------------------------------------
            /// A cache of the positions of the FrAdcData structures within
            /// the stream.
            //-----------------------------------------------------------------
            positions_cache_type positions_cache;
            //-----------------------------------------------------------------
            /// The number of bytes from the end of the stream where the
            ///   array containing the FrAdcData offsets.
            //-----------------------------------------------------------------
            position_type positions_cache_offset;

            //-----------------------------------------------------------------
            /// Provide means where a channel index can be mapped to a
            /// channel name
            //-----------------------------------------------------------------
            mutable reverse_lookup_type reverse_lookup_;

            reverse_lookup_type::mapped_type
            reverse_lookup( const reverse_lookup_type::key_type& key ) const;
        };

        inline FrTOCAdcData::FrTOCAdcData( )
        {
        }

        inline FrTOCAdcData::FrTOCAdcData( Common::IStream& Stream,
                                           INT_4U           FrameCount )
        {
            nADC_type n;
            Stream >> n;
            if ( n && ( n != ~nADC_type( 0 ) ) )
            {
                //---------------------------------------------------------------
                // Read in the information
                //---------------------------------------------------------------
                key_container_type::size_type s( n );
                if ( positions_cache.size( ) != ( s * FrameCount ) )
                {
                    positions_cache.resize( s * FrameCount );
                }

                m_keys.resize( s );
                std::vector< channelID_type > channel_id( s );
                std::vector< groupID_type >   group_id( s );

                Stream >> m_keys >> channel_id >> group_id;
                //---------------------------------------------------------------
                // Capture the starting position relative to the end of the
                // file.
                //---------------------------------------------------------------
                positions_cache_offset = Stream.Size( ) - Stream.tellg( );
                Stream >> positions_cache;
                //---------------------------------------------------------------
                // Move into structure.
                //---------------------------------------------------------------
                std::vector< position_type >::const_iterator cur_position =
                    positions_cache.begin( );

                key_container_type::size_type x( 0 );
                for ( key_container_type::const_iterator cur = m_keys.begin( ),
                                                         last = m_keys.end( );
                      cur != last;
                      ++cur, ++x, cur_position += FrameCount )
                {
                    adc_info_type& i = m_adc_info[ *cur ];
                    i.channelID = channel_id[ x ];
                    i.groupID = group_id[ x ];
                    i.positionADC.assign( cur_position,
                                          cur_position + FrameCount );
                }
            }
        }

        inline Common::FrameSpec::size_type
        FrTOCAdcData::Bytes( const Common::StreamBase& Stream ) const
        {
            Common::FrameSpec::size_type retval = sizeof( nADC_type );
            if ( m_adc_info.size( ) )
            {
                retval +=
                    ( m_adc_info.size( ) *
                      ( sizeof( channelID_type ) + sizeof( groupID_type ) +
                        ( sizeof( position_type ) *
                          m_adc_info.begin( )->second.positionADC.size( ) ) ) );
            }
            for ( MapADC_type::const_iterator cur = m_adc_info.begin( ),
                                              last = m_adc_info.end( );
                  cur != last;
                  ++cur )
            {
                retval += cur->first.Bytes( );
            }
            return retval;
        }

        inline const FrTOCAdcData::MapADC_type&
        FrTOCAdcData::GetADC( ) const
        {
            return m_adc_info;
        }

        inline FrTOCAdcData::MapADC_type::const_iterator
        FrTOCAdcData::GetADC( const std::string& Channel ) const
        {
            const MapADC_type& i( GetADC( ) );

            return i.find( Channel );
        }

        inline FrTOCAdcData::MapADC_type::const_iterator
        FrTOCAdcData::GetADC( INT_4U Channel ) const
        {
            const MapADC_type& i( GetADC( ) );

            if ( Channel >= i.size( ) )
            {
                return i.end( );
            }
            return i.find( m_keys[ Channel ] );
        }

        inline FrTOCAdcData::MapADC_type&
        FrTOCAdcData::getADC( )
        {
            return m_adc_info;
        }

        inline FrTOCAdcData::MapADC_type::iterator
        FrTOCAdcData::getADC( const std::string& Channel )
        {
            MapADC_type& i( getADC( ) );

            return i.find( Channel );
        }

        inline FrTOCAdcData::MapADC_type::iterator
        FrTOCAdcData::getADC( INT_4U Channel )
        {
            MapADC_type& i( getADC( ) );

            if ( Channel >= i.size( ) )
            {
                return i.end( );
            }
            return i.find( m_keys[ Channel ] );
        }

        inline void
        FrTOCAdcData::cachePositions( istream_type& Stream )
        {
            std::streampos here( Stream.tellg( ) );

            Stream.seekg( -positions_cache_offset, Stream.end );
            Stream >> positions_cache;
            Stream.seekg( here, Stream.beg );
        }

        inline void
        FrTOCAdcData::seekPositions( istream_type&  Stream,
                                     channelID_type Channel )
        {
            const INT_4U frame_count( positions_cache.size( ) /
                                      m_keys.size( ) );
            const INT_4U offset( Channel * frame_count );

            if ( positions_cache[ offset ] != 0 )
            {
                std::copy( &( positions_cache[ offset ] ),
                           &( positions_cache[ offset + frame_count ] ),
                           &( getADC( Channel )->second.positionADC[ 0 ] ) );
                positions_cache[ offset ] = 0;
            }
        }

        inline void
        FrTOCAdcData::seekPositions( istream_type&      Stream,
                                     const std::string& Channel )
        {
            const INT_4U frame_count( positions_cache.size( ) /
                                      m_keys.size( ) );
            const INT_4U offset( reverse_lookup( Channel ) * frame_count );

            if ( positions_cache[ offset ] != 0 )
            {
                std::copy( &( positions_cache[ offset ] ),
                           &( positions_cache[ offset + frame_count ] ),
                           &( getADC( Channel )->second.positionADC[ 0 ] ) );
                positions_cache[ offset ] = 0;
            }
        }

        inline void
        FrTOCAdcData::write( Common::OStream& Stream ) const
        {
            //-----------------------------------------------------------------
            // Flatten data so it is streamable
            //-----------------------------------------------------------------
            std::vector< name_type >::size_type s( m_adc_info.size( ) );
            if ( s )
            {
                std::vector< name_type >::size_type fc(
                    m_adc_info.begin( )->second.positionADC.size( ) );

                std::vector< name_type >      names( s );
                std::vector< channelID_type > channel_id( s );
                std::vector< groupID_type >   group_id( s );
                std::vector< position_type >  positions( s * fc );
                //---------------------------------------------------------------
                // Copy data for streaming
                //---------------------------------------------------------------
                std::vector< name_type >::iterator cur_name = names.begin( );
                std::vector< channelID_type >::iterator cur_channel_id =
                    channel_id.begin( );
                std::vector< groupID_type >::iterator cur_group_id =
                    group_id.begin( );
                std::vector< position_type >::iterator cur_position =
                    positions.begin( );

                for ( MapADC_type::const_iterator cur = m_adc_info.begin( ),
                                                  last = m_adc_info.end( );
                      cur != last;
                      ++cur, ++cur_name, cur_position += fc )
                {
                    *cur_name = cur->first;
                    *cur_channel_id = cur->second.channelID;
                    *cur_group_id = cur->second.groupID;
                    std::copy( cur->second.positionADC.begin( ),
                               cur->second.positionADC.end( ),
                               cur_position );
                }
                //---------------------------------------------------------------
                // Stream out
                //---------------------------------------------------------------
                Stream << nADC_type( s ) << names << channel_id << group_id
                       << positions;
            }
            else
            {
                Stream << ~nADC_type( 0 );
            }
        }

        inline FrTOCAdcData::reverse_lookup_type::mapped_type
        FrTOCAdcData::reverse_lookup(
            const reverse_lookup_type::key_type& Key ) const
        {
            if ( 0 == reverse_lookup_.size( ) )
            {
                reverse_lookup_type::mapped_type index = 0;
                for ( key_container_type::const_iterator cur = m_keys.begin( ),
                                                         last = m_keys.end( );
                      cur != last;
                      ++cur, ++index )
                {
                    reverse_lookup_[ *cur ] = index;
                }
            }
            return reverse_lookup_[ Key ];
        }
    } // namespace Version_4
} // namespace FrameCPP

#endif /* FrameCPP_VERSION_4_FrTOCAdcData_HH */
