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

#ifndef FrameCPP_VERSION_8__IMPL__FrTOCSerDataClassicIO_HH
#define FrameCPP_VERSION_8__IMPL__FrTOCSerDataClassicIO_HH

#include "framecpp/Version8/impl/FrTOCSerDataData.hh"

#if defined( __cplusplus )
#if !defined( SWIG )

#include "framecpp/Common/Description.hh"
#include "framecpp/Common/FrameSpec.hh"
#include "framecpp/Common/FrameSpec.tcc"
#include "framecpp/Common/TOCInfo.hh"

#include "framecpp/Version7/FrTOCSerData.hh"

#include "framecpp/Version8/impl/FrTOCSerDataData.hh"

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
            class FrTOCSerDataClassicIO : public virtual FrTOCSerDataData
            {
            public:
                //-------------------------------------------------------
                //
                //-------------------------------------------------------
                FrTOCSerDataClassicIO( ) = default;

                Common::FrameSpec::size_type
                Bytes( const stream_base_type& Stream ) const
                {
                    auto retval = for_each(
                        m_info.begin( ), m_info.end( ), byte_counter( ) );

                    return ( sizeof( n_type ) + retval.value );
                }

                //-----------------------------------------------------------------
                /// \brief The description of structure
                ///
                /// \return
                ///     A Description object which describes this structure as
                ///     specified by the frame specification.
                //-----------------------------------------------------------------
                template < typename SE >
                static void
                Description( Common::Description& Desc )
                {
                    Desc( SE( "nSer",
                              "INT_4U",
                              "Number of unique FrSerData names in file." ) );
                    Desc( SE( "nameSer",
                              "STRING[nSer]",
                              "Array of FrSerData names" ) );
                    Desc(
                        SE( "positionSer",
                            "INT_8U[nSer][nFrame]",
                            "Array of lists of FrSerData offset positions, in "
                            "bytes,"
                            " from beginning of file (size of nFrame*nSer)" ) );
                }

                //-----------------------------------------------------------------
                /// \brief Read contents from stream
                ///
                /// \param[in] Stream
                ///     The stream from which the object is being read.
                ///
                /// \return
                ///    A new instance of this object.
                //-----------------------------------------------------------------
                inline void
                Load( istream_type& Stream, INT_4U FrameCount )
                {
                    n_type n;
                    Stream >> n;

                    if ( n && ( n != ~n_type( 0 ) ) )
                    {
                        //---------------------------------------------------------------
                        // Read in the information
                        //---------------------------------------------------------------
                        io_key_container_type::size_type s( n );
                        std::vector< position_type >     positions( s *
                                                                FrameCount );

                        m_io_keys.resize( s );

                        Stream >> m_io_keys >> positions;

                        //---------------------------------------------------------------
                        // Move into structure.
                        //---------------------------------------------------------------
                        m_keys.resize( m_io_keys.size( ) );
                        std::for_each(
                            m_io_keys.begin( ),
                            m_io_keys.end( ),
                            inflate( m_keys, m_info, positions, FrameCount ) );
                    }
                }

                FrTOCSerDataClassicIO&
                operator=( const Previous::FrTOCSerData& Source )
                {
#if WORKING
                    m_keys = Source.GetPositionKeys( );
                    m_info = Source.GetSer( );
#endif /* WORKING */
                    return ( *this );
                }

                //-----------------------------------------------------------------
                /// \brief Gather TOC info for FrSerData being written.
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
                QuerySer( const Common::TOCInfo& Info,
                          INT_4U                 FrameOffset,
                          INT_8U                 Position )
                {
                    using Common::TOCInfo;

                    name_type name;

                    Info.TOCQuery( TOCInfo::IC_NAME,
                                   TOCInfo::DT_STRING_2,
                                   &name,
                                   TOCInfo::IC_EOQ );

                    auto& i( m_info[ name ] );
                    i.resize( FrameOffset + 1 );
                    i[ FrameOffset ] = Position;
                }

            protected:
                typedef STRING io_name_type;

                typedef std::vector< io_name_type > io_key_container_type;

                const io_key_container_type&
                GetIOPositionKeys( ) const
                {
                    return m_io_keys;
                }

                io_key_container_type m_io_keys;

                //-----------------------------------------------------------------
                /// \brief Write the structure to the stream
                ///
                /// \param[in] Stream
                ///     The output stream where the object is to be written.
                //-----------------------------------------------------------------
                inline void
                write( ostream_type& Stream ) const
                {
                    n_type serial_data_count( m_info.size( ) );
                    if ( serial_data_count )
                    {
                        //---------------------------------------------------------------
                        // Flatten data so it is streamable
                        //---------------------------------------------------------------
                        frame_count_type frame_count(
                            m_info.begin( )->second.size( ) );

                        //---------------------------------------------------------------
                        // Copy data for streaming
                        //---------------------------------------------------------------
                        auto flattened = for_each(
                            m_info.begin( ),
                            m_info.end( ),
                            deflate( serial_data_count, frame_count ) );
                        //---------------------------------------------------------------
                        // Stream out
                        //---------------------------------------------------------------
                        Stream << n_type( serial_data_count ) << flattened.names
                               << flattened.positions;
                    }
                    else
                    {
                        Stream << ~n_type( 0 );
                    }
                }

            private:
                struct byte_counter
                {
                    void
                    operator( )( const MapSer_type::value_type& Current )
                    {
                        value += ( sizeof( position_type ) *
                                   Current.second.size( ) ) +
                            io_name_type::Bytes( Current.first );
                    }

                    Common::FrameSpec::size_type value{ 0 };
                };

                struct deflate
                {
                    typedef std::vector< io_name_type >  names_type;
                    typedef std::vector< position_type > positions_type;

                    deflate( n_type Count, frame_count_type FrameCount )
                        : count( Count ), frame_count( FrameCount ),
                          names( Count ), positions( Count * FrameCount )
                    {
                        cur_name = names.begin( );
                        cur_position = positions.begin( );
                    }

                    void
                    operator( )( const MapSer_type::value_type& Current )
                    {
                        *cur_name = Current.first;
                        std::copy( Current.second.begin( ),
                                   Current.second.end( ),
                                   cur_position );
                        ++cur_name;
                        cur_position += frame_count;
                    }
                    n_type           count;
                    frame_count_type frame_count;

                    names_type               names;
                    positions_type           positions;
                    names_type::iterator     cur_name;
                    positions_type::iterator cur_position;
                };

                struct inflate
                {
                    key_container_type&          keys;
                    MapSer_type&                 info;
                    key_container_type::iterator cur_key;
                    info_type                    positions;
                    info_type::const_iterator    cur_position;
                    size_t                       frame_count;

                    inflate( key_container_type& Keys,
                             MapSer_type&        Info,
                             info_type&          Positions,
                             size_t              FrameCount )
                        : keys( Keys ), info( Info ), positions( Positions ),
                          frame_count( FrameCount )
                    {
                        cur_key = keys.begin( );
                        cur_position = positions.begin( );
                    }

                    void
                    operator( )(
                        const io_key_container_type::value_type& Current )
                    {
                        *cur_key = Current;
                        auto& node = info[ Current ];
                        node.resize( frame_count );
                        auto stop_position = cur_position + frame_count;
                        node.assign( cur_position, stop_position );
                        ++cur_key;
                        cur_position = stop_position;
                    }
                };

                Common::FrTOC::cmn_name_container_type name_keys;
            }; // class ClassicIO

        } // namespace FrTOCImpl
    } // namespace Version_8
} // namespace FrameCPP

#endif /* ! defined(SWIG) */
#endif /* defined( __cplusplus ) */

#endif /* FrameCPP_VERSION_8__IMPL__FrTOCSerDataClassicIO_HH */
