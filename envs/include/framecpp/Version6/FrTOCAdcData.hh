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

#ifndef FrameCPP_VERSION_6_FrTOCAdcData_HH
#define FrameCPP_VERSION_6_FrTOCAdcData_HH

#include <vector>

#include "framecpp/Version6/STRING.hh"

namespace FrameCPP
{
    namespace Common
    {
        class TOCInfo;

    }

    namespace Version_6
    {
        //===================================================================
        //===================================================================
        class FrTOCAdcData
        {
        public:
            typedef INT_4U nadc_type;
            typedef STRING name_type;
            typedef INT_4U channel_id_type;
            typedef INT_4U group_id_type;
            typedef INT_8U position_type;

            struct adc_info_type
            {
                //---------------------------------------------------------------
                /// \brief Channel ID of ADC
                //---------------------------------------------------------------
                channel_id_type m_channelID;
                //---------------------------------------------------------------
                /// \brief Group ID of ADC
                //---------------------------------------------------------------
                group_id_type m_groupID;
                //---------------------------------------------------------------
                /// \brief FrAdcData offset positions.
                ///
                /// FrAdcData offset positions, in bytes,
                /// from the beginning of the file.
                /// The size of the array is nFrame
                //---------------------------------------------------------------
                std::vector< position_type > m_positionADC;
                //---------------------------------------------------------------
                /// \brief Adc channel index number, sequential as read from the
                /// TOC
                //---------------------------------------------------------------
                INT_4U m_index;

                //---------------------------------------------------------------
                //---------------------------------------------------------------
                adc_info_type( );

                //---------------------------------------------------------------
                //---------------------------------------------------------------
                adc_info_type( channel_id_type                    ChannelId,
                               group_id_type                      GroupId,
                               const std::vector< position_type > Positions,
                               INT_4U                             Index );

                //---------------------------------------------------------------
                //---------------------------------------------------------------
                adc_info_type(
                    channel_id_type ChannelId,
                    group_id_type   GroupId,
                    const std::vector< position_type >::const_iterator BeginPos,
                    const std::vector< position_type >::const_iterator EndPos,
                    INT_4U                                             Index );
            };

            typedef std::vector< name_type >             key_container_type;
            typedef std::map< name_type, adc_info_type > MapADC_type;

            FrTOCAdcData( );

            Common::FrameSpec::size_type
            Bytes( const Common::StreamBase& Stream ) const;

            const MapADC_type& GetADC( ) const;

            MapADC_type::const_iterator GetADC( const std::string& Name ) const;

            MapADC_type::const_iterator GetADC( INT_4U index ) const;

            //-----------------------------------------------------------------
            /// \brief Retrieve the keys
            ///
            /// \return
            ///     Constant container of keys.
            //-----------------------------------------------------------------
            const key_container_type& GetKeys( ) const;

            void QueryAdc( const Common::TOCInfo& Info,
                           INT_4U                 FrameOffset,
                           INT_8U                 Position );

            bool operator==( const FrTOCAdcData& RHS ) const;

            template < typename SE >
            static void Description( Common::Description& Desc );

        protected:
            //-----------------------------------------------------------------
            // Offset from the end of file for the
            // start of the array of ADC positions in the TOC
            //-----------------------------------------------------------------
            position_type m_positions_start;

            key_container_type m_keys;
            MapADC_type        m_info;

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

            void seekPositions( istream_type& Stream, channel_id_type Channel );

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

        inline FrTOCAdcData::adc_info_type::adc_info_type( )
        {
        }

        inline FrTOCAdcData::adc_info_type::adc_info_type(
            channel_id_type                    ChannelId,
            group_id_type                      GroupId,
            const std::vector< position_type > Positions,
            INT_4U                             Index )
            : m_channelID( ChannelId ), m_groupID( GroupId ),
              m_positionADC( Positions ), m_index( Index )
        {
        }

        inline FrTOCAdcData::adc_info_type::adc_info_type(
            channel_id_type                                    ChannelId,
            group_id_type                                      GroupId,
            const std::vector< position_type >::const_iterator BeginPos,
            const std::vector< position_type >::const_iterator EndPos,
            INT_4U                                             Index )
            : m_channelID( ChannelId ), m_groupID( GroupId ),
              m_positionADC( BeginPos, EndPos ), m_index( Index )
        {
        }

        inline Common::FrameSpec::size_type
        FrTOCAdcData::Bytes( const Common::StreamBase& Stream ) const
        {
            Common::FrameSpec::size_type retval = sizeof( nadc_type );
            if ( m_info.size( ) )
            {
                retval +=
                    ( m_info.size( ) *
                      ( sizeof( channel_id_type ) + sizeof( group_id_type ) +
                        ( sizeof( position_type ) *
                          m_info.begin( )->second.m_positionADC.size( ) ) ) );
            }
            for ( MapADC_type::const_iterator cur = m_info.begin( ),
                                              last = m_info.end( );
                  cur != last;
                  ++cur )
            {
                retval += cur->first.Bytes( );
            }
            return retval;
        }

        template < typename SE >
        void
        FrTOCAdcData::Description( Common::Description& Desc )
        {
            Desc( SE( "nADC",
                      "INT_4U",
                      "Number of unique FrAdcData names in file." ) );
            Desc( SE( "name", "*STRING", "Array of FrAdcData names" ) );
            Desc( SE( "channelID", "*INT_4U", "Array of ADC channel IDs" ) );
            Desc( SE( "groupID", "*INT_4U", "Array of ADC group IDs" ) );
            Desc( SE( "positionADC",
                      "*INT_8U",
                      "Array of lists of FrAdcData offset positions, in bytes,"
                      " from beginning of file (size of nFrame*nADC)" ) );
        }

        inline const FrTOCAdcData::MapADC_type&
        FrTOCAdcData::GetADC( ) const
        {
            return m_info;
        }

        inline const FrTOCAdcData::key_container_type&
        FrTOCAdcData::GetKeys( ) const
        {
            return m_keys;
        }

        inline FrTOCAdcData::MapADC_type&
        FrTOCAdcData::getADC( )
        {
            return m_info;
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
        FrTOCAdcData::seekPositions( istream_type&   Stream,
                                     channel_id_type Channel )
        {
            const INT_4U frame_count( positions_cache.size( ) /
                                      m_keys.size( ) );
            const INT_4U offset( Channel * frame_count );

            if ( positions_cache[ offset ] != 0 )
            {
                std::copy( &( positions_cache[ offset ] ),
                           &( positions_cache[ offset + frame_count ] ),
                           &( getADC( Channel )->second.m_positionADC[ 0 ] ) );
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
                           &( getADC( Channel )->second.m_positionADC[ 0 ] ) );
                positions_cache[ offset ] = 0;
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
    } // namespace Version_6
} // namespace FrameCPP

#endif /* FrameCPP_VERSION_6_FrTOCAdcData_HH */
