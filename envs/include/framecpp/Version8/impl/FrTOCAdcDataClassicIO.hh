//
// LDASTools frameCPP - A library implementing the LIGO/Virgo frame
// specification
//
// Copyright (C) 2019 California Institute of Technology
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

#ifndef FrameCPP_VERSION_8__IMPL__FrTOCAdcDataClassicIO_HH
#define FrameCPP_VERSION_8__IMPL__FrTOCAdcDataClassicIO_HH

#include "framecpp/Version8/impl/FrTOCAdcDataData.hh"

#if defined( __cplusplus )
#if !defined( SWIG )

#include "framecpp/Common/Description.hh"
#include "framecpp/Common/FrameSpec.hh"
#include "framecpp/Common/FrameSpec.tcc"
#include "framecpp/Common/TOCInfo.hh"

#include "framecpp/Version7/FrTOCAdcData.hh"

#include "framecpp/Version8/impl/FrTOCConstants.hh"
#include "framecpp/Version8/impl/FrTOCAdcDataData.hh"

#include "framecpp/Version8/FrameSpec.hh"
#include "framecpp/Version8/FrSH.hh"
#include "framecpp/Version8/FrSE.hh"
#include "framecpp/Version8/PTR_STRUCT.hh"
#include "framecpp/Version8/STRING.hh"

namespace FrameCPP
{
    namespace Version_8
    {
        namespace FrTOCImpl
        {
            class FrTOCAdcDataClassicIO : public virtual FrTOCAdcDataData
            {
            public:
                //-----------------------------------------------------------------
                /// \brief Default constructor.
                //-----------------------------------------------------------------
                FrTOCAdcDataClassicIO( ) = default;

                //-----------------------------------------------------------------
                /// \brief Number of bytes needed to write this structure
                ///
                /// \param[in] Stream
                ///     The stream from which to the object is being read or
                ///     written.
                ///
                /// \return
                ///     The number of bytes need to read or write this object.
                //-----------------------------------------------------------------
                inline Common::FrameSpec::size_type
                Bytes( const Common::StreamBase& Stream ) const
                {
                    Common::FrameSpec::size_type retval = sizeof( nadc_type );
                    if ( m_info.size( ) )
                    {
                        retval +=
                            ( m_info.size( ) *
                              ( sizeof( channel_id_type ) +
                                sizeof( group_id_type ) +
                                ( sizeof( position_type ) *
                                  m_info.begin( )
                                      ->second.m_positionADC.size( ) ) ) );
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

                //-----------------------------------------------------------------
                /// \brief Gather TOC info for FrAdcData being written.
                ///
                /// \param[in] Info
                ///     Information
                ///
                /// \param[in] FrameOffset
                ///     The frame offset of the frame being written.
                ///     The frame offsets start at 0 (zero).
                ///
                /// \param[in] Position
                ///     The byte offset from the start of the file
                ///     where the structure is written.
                //-----------------------------------------------------------------
                inline void
                QueryAdc( const Common::TOCInfo& Info,
                          INT_4U                 FrameOffset,
                          INT_8U                 Position )
                {
                    using Common::TOCInfo;

                    STRING name;
                    INT_4U channel_id;
                    INT_4U group_id;

                    Info.TOCQuery( TOCInfo::IC_NAME,
                                   TOCInfo::DT_STRING_2,
                                   &name,
                                   TOCInfo::IC_CHANNEL_ID,
                                   TOCInfo::DT_INT_4U,
                                   &channel_id,
                                   TOCInfo::IC_GROUP_ID,
                                   TOCInfo::DT_INT_4U,
                                   &group_id,
                                   TOCInfo::IC_EOQ );

                    adc_info_type& i( m_info[ name ] );
                    i.m_channelID = channel_id;
                    i.m_groupID = group_id;
                    i.m_positionADC.resize( FrameOffset + 1 );
                    i.m_positionADC[ FrameOffset ] = Position;
                }

                //-----------------------------------------------------------------
                /// \brief asignment operator
                ///
                /// \param[in] Source
                ///     The source to be copied.
                //-----------------------------------------------------------------
                inline const FrTOCAdcDataClassicIO&
                operator=( const Previous::FrTOCAdcData& Source )
                {
#if 0
                m_keys = Source.GetKeys( );
                m_info.insert( Source.GetADC( ).begin( ), Source.GetADC( ).end( ));
#endif /* 0 */
                    return *this;
                }

                inline FrTOCAdcDataClassicIO&
                operator=( FrTOCAdcDataClassicIO&& TOC )
                {
                    static_cast< FrTOCAdcDataData& >( *this ) =
                        static_cast< FrTOCAdcDataData&& >( TOC );
                    return *this;
                }

                //-----------------------------------------------------------------
                /// \brief The description of structure
                ///
                /// \param[out] Desc
                ///     Storage for the description of the structure.
                ///
                /// \return
                ///     A Description object which describes this structure as
                ///     specified by the frame specification.
                //-----------------------------------------------------------------
                template < typename SE >
                static void
                Description( Common::Description& Desc )
                {
                    Desc( SE( "nADC",
                              "INT_4U",
                              "Number of unique FrAdcData names in file." ) );
                    Desc( SE(
                        "name", "STRING[nADC]", "Array of FrAdcData names" ) );
                    Desc( SE( "channelID",
                              "INT_4U[nADC]",
                              "Array of ADC channel IDs" ) );
                    Desc( SE(
                        "groupID", "INT_4U[nADC]", "Array of ADC group IDs" ) );
                    Desc(
                        SE( "positionADC",
                            "INT_8U[nADC][nFrame]",
                            "Array of lists of FrAdcData offset positions, in "
                            "bytes,"
                            " from beginning of file (size of nFrame*nADC)" ) );
                }

                // Offset from the end of file to the
                // start of the array of ADC positions in the TOC
                position_type m_positions_start;

            protected:
                //-----------------------------------------------------------------
                /// \brief Read contents from stream
                ///
                /// \param[in] Stream
                ///     The stream from which the object is being read.
                ///
                /// \return
                ///    A new instance of this object.
                //-----------------------------------------------------------------
                void Load( istream_type& Stream, INT_4U FrameCount );

                //-----------------------------------------------------------------
                /// \brief Iterate over contents.
                ///
                /// \param[in] Info
                ///     Specifies the type of information to be searched.
                ///
                /// \param[in] Action
                ///     Action to be taken for each piece of information found.
                //-----------------------------------------------------------------
                inline void
                forEach( Common::FrTOC::query_info_type Info,
                         Common::FrTOC::FunctionBase&   Action ) const
                {
                    switch ( Info )
                    {
                    case Common::FrTOC::TOC_CHANNEL_NAMES:
                    {
                        try
                        {
                            Common::FrTOC::FunctionString& action(
                                dynamic_cast< Common::FrTOC::FunctionString& >(
                                    Action ) );

                            for ( MapADC_type::const_iterator
                                      cur = m_info.begin( ),
                                      last = m_info.end( );
                                  cur != last;
                                  ++cur )
                            {
                                action( cur->first );
                            }
                        }
                        catch ( ... )
                        {
                            // Does not understand Action
                        }
                    }
                    break;
                    default:
                        //---------------------------------------------------------------
                        // ignore all other requests
                        //---------------------------------------------------------------
                        break;
                    }
                }

                //-----------------------------------------------------------------
                /// \brief Cache where the positions of the Adc channels
                ///
                /// \param[in,out] Stream
                ///     The Stream being read
                //-----------------------------------------------------------------
                inline void
                cachePositions( istream_type& Stream )
                {
                    std::streampos here( Stream.tellg( ) );
                    size_t         frame_count =
                        positions_cache.size( ) / m_keys.size( );
                    size_t position_offset = 0;

                    Stream.seekg( -positions_cache_offset, Stream.end );
                    Stream >> positions_cache;
                    Stream.seekg( here, Stream.beg );

                    for ( key_container_type::const_iterator
                              cur = m_keys.begin( ),
                              last = m_keys.end( );
                          cur != last;
                          ++cur )
                    {
                        std::copy(
                            positions_cache.begin( ) + position_offset,
                            positions_cache.begin( ) +
                                ( position_offset + frame_count ),
                            getADC( *cur )->second.m_positionADC.begin( ) );
                        position_offset += frame_count;
                    }
                }

                //-----------------------------------------------------------------
                /// \brief Advance to the specified Adc channel
                ///
                /// \param[in,out] Stream
                ///     The Stream being read
                /// \param[in] Channel
                ///     The requested channel
                //-----------------------------------------------------------------
                inline void
                seekPositions( istream_type& Stream, channel_id_type Channel )
                {
                    const INT_4U frame_count( positions_cache.size( ) /
                                              m_keys.size( ) );
                    const INT_4U offset( Channel * frame_count );

                    if ( positions_cache[ offset ] != 0 )
                    {
                        std::copy(
                            &( positions_cache[ offset ] ),
                            &( positions_cache[ offset + frame_count ] ),
                            &( getADC( Channel )->second.m_positionADC[ 0 ] ) );
                        positions_cache[ offset ] = 0;
                    }
                }

                //-----------------------------------------------------------------
                /// \brief Advance to the specified Adc channel
                ///
                /// \param[in,out] Stream
                ///     The Stream being read
                /// \param[in] Channel
                ///     The requested channel
                //-----------------------------------------------------------------
                inline void
                seekPositions( istream_type&      Stream,
                               const std::string& Channel )
                {
                    const INT_4U frame_count( positions_cache.size( ) /
                                              m_keys.size( ) );
                    const INT_4U offset( reverse_lookup( Channel ) *
                                         frame_count );

                    if ( positions_cache[ offset ] != 0 )
                    {
                        std::copy(
                            &( positions_cache[ offset ] ),
                            &( positions_cache[ offset + frame_count ] ),
                            &( getADC( Channel )->second.m_positionADC[ 0 ] ) );
                        positions_cache[ offset ] = 0;
                    }
                }

                //-----------------------------------------------------------------
                /// \brief Write the structure to the stream
                ///
                /// \param[in] Stream
                ///     The output stream where the object is to be written.
                //-----------------------------------------------------------------
                inline void
                write( Common::OStream& Stream ) const
                {
                    //-----------------------------------------------------------------
                    // Flatten data so it is streamable
                    //-----------------------------------------------------------------
                    std::vector< name_type >::size_type s( m_info.size( ) );
                    if ( s )
                    {
                        std::vector< name_type >::size_type fc(
                            m_info.begin( )->second.m_positionADC.size( ) );

                        std::vector< name_type >       names( s );
                        std::vector< channel_id_type > channel_ids( s );
                        std::vector< group_id_type >   group_ids( s );
                        std::vector< position_type >   positions( s * fc );
                        //---------------------------------------------------------------
                        // Copy data for streaming
                        //---------------------------------------------------------------
                        std::vector< name_type >::iterator cur_name =
                            names.begin( );
                        std::vector< channel_id_type >::iterator
                                                               cur_channel_id = channel_ids.begin( );
                        std::vector< group_id_type >::iterator cur_group_id =
                            group_ids.begin( );
                        std::vector< position_type >::iterator cur_position =
                            positions.begin( );

                        for ( MapADC_type::const_iterator cur = m_info.begin( ),
                                                          last = m_info.end( );
                              cur != last;
                              ++cur,
                                                          ++cur_name,
                                                          ++cur_channel_id,
                                                          ++cur_group_id,
                                                          cur_position += fc )
                        {
                            *cur_name = cur->first;
                            *cur_channel_id = cur->second.m_channelID;
                            *cur_group_id = cur->second.m_groupID;
                            std::copy( cur->second.m_positionADC.begin( ),
                                       cur->second.m_positionADC.end( ),
                                       cur_position );
                        }
                        //---------------------------------------------------------------
                        // Stream out
                        //---------------------------------------------------------------
                        Stream << nadc_type( s ) << names << channel_ids
                               << group_ids << positions;
                    }
                    else
                    {
                        Stream << nadc_type( s );
                        // Stream << nadc_type( FrTOC::NO_DATA_AVAILABLE );
                    }
                }

            private:
                typedef LDASTools::AL::unordered_map< std::string, INT_4U >
                                                     reverse_lookup_type;
                typedef std::vector< position_type > positions_cache_type;

                inline MapADC_type&
                getADC( )
                {
                    return m_info;
                }

                inline MapADC_type::iterator
                getADC( const std::string& Channel )
                {
                    MapADC_type& i( getADC( ) );

                    return i.find( Channel );
                }

                inline MapADC_type::iterator
                getADC( INT_4U Channel )
                {
                    MapADC_type& i( getADC( ) );

                    if ( Channel >= i.size( ) )
                    {
                        return i.end( );
                    }
                    return i.find( m_keys[ Channel ] );
                }

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

                inline reverse_lookup_type::mapped_type
                reverse_lookup( const reverse_lookup_type::key_type& Key ) const
                {
                    if ( 0 == reverse_lookup_.size( ) )
                    {
                        reverse_lookup_type::mapped_type index = 0;
                        for ( key_container_type::const_iterator
                                  cur = m_keys.begin( ),
                                  last = m_keys.end( );
                              cur != last;
                              ++cur, ++index )
                        {
                            reverse_lookup_[ *cur ] = index;
                        }
                    }
                    return reverse_lookup_[ Key ];
                }
            }; // class ClassicIO

        } // namespace FrTOCImpl
    } // namespace Version_8
} // namespace FrameCPP

#endif /* ! defined(SWIG) */
#endif /* defined( __cplusplus ) */

#endif /* FrameCPP_VERSION_8__IMPL__FrTOCAdcDataClassicIO_HH */
