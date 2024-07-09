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

#ifndef FrameCPP_VERSION_8__IMPL__FrTOCEventClassicIO_HH
#define FrameCPP_VERSION_8__IMPL__FrTOCEventClassicIO_HH

#if defined( __cplusplus )
#if !defined( SWIG )
#include <numeric>

#include "framecpp/Common/Description.hh"
#include "framecpp/Common/FrameSpec.hh"
#include "framecpp/Common/FrameSpec.tcc"
#include "framecpp/Common/TOCInfo.hh"

#include "framecpp/Version7/FrTOCEvent.hh"

#include "framecpp/Version8/impl/FrTOCEventData.hh"

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
            class FrTOCEventClassicIO : public virtual FrTOCEventData
            {
            public:
                //-------------------------------------------------------
                //
                //-------------------------------------------------------
                FrTOCEventClassicIO( ) = default;

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
                    Common::FrameSpec::size_type retval =
                        sizeof( nevent_type ) + sizeof( nTotalEvent_type );
                    //-----------------------------------------------------------------
                    //
                    //-----------------------------------------------------------------
                    for ( nameEvent_container_type::const_iterator
                              cur = m_info.begin( ),
                              last = m_info.end( );
                          cur != last;
                          ++cur )
                    {
                        retval += cur->first.Bytes( ) + sizeof( nevent_type ) +
                            ( cur->second.size( ) * event_type_size );
                    }
                    return retval;
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
                    Desc( SE( "nEventType",
                              "INT_4U",
                              "Number of FrEvent in the file" ) );
                    Desc( SE( "nameEvent",
                              "STRING[nEventType]",
                              "Array of FrEvent names" ) );
                    Desc( SE( "nEvent",
                              "INT_4U[nEventType]",
                              "Number of FrEvent for each type of FrEvent"
                              " (size of nEventType)" ) );
                    Desc( SE(
                        "nTotalEvent", "INT_4U", "Total number of FrEvent" ) );
                    Desc( SE( "GTimeSEvent",
                              "INT_4U[nTotalEvent]",
                              "GPS time in integer seconds" ) );
                    Desc( SE( "GTimeNEvent",
                              "INT_4U[nTotalEvent]",
                              "Residual GPS time in integer nanoseconds" ) );
                    Desc( SE( "amplitudeEvent",
                              "REAL_4[nTotalEvent]",
                              "Event amplitude" ) );
                    Desc( SE( "positionEvent",
                              "INT_8U[nTotalEvent]",
                              "Array of FrEvent positions, in bytes,"
                              " from beginning of file" ) );
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
                Load( istream_type& Stream )
                {
                    nevent_type nevent;

                    Stream >> nevent;

                    if ( nevent )
                    {
                        //---------------------------------------------------------------
                        // Read in the information
                        //---------------------------------------------------------------
                        std::vector< name_type >   names( nevent );
                        std::vector< nevent_type > events( nevent );

                        Stream >> names >> events;

                        nevent_type offset = 0;

                        auto adder = []( nTotalEvent_type sum,
                                         nevent_type      increment ) {
                            return ( ( increment == NO_DATA_AVAILABLE )
                                         ? sum
                                         : sum + increment );
                        };
                        nTotalEvent_type nevent_sum = std::accumulate(
                            events.begin( ), events.end( ), 0, adder );

                        nTotalEvent_type nTotalEvent;

                        Stream >> nTotalEvent;

                        if ( nTotalEvent != nevent_sum )
                        {
                            throw std::runtime_error(
                                "nTotalEvent is not the sumation of nEvent" );
                        }

                        std::vector< gtimesEvent_type > gtimes( nTotalEvent );
                        std::vector< gtimenEvent_type > gtimen( nTotalEvent );
                        std::vector< amplitudeEvent_type > amplitude(
                            nTotalEvent );
                        std::vector< positionEvent_type > position(
                            nTotalEvent );

                        Stream >> gtimes >> gtimen >> amplitude >> position;
                        std::vector< nevent_type >::const_iterator
                            cur_event_counter = events.begin( );

                        for ( std::vector< name_type >::const_iterator
                                  cur = names.begin( ),
                                  last = names.end( );
                              cur != last;
                              ++cur, ++cur_event_counter )
                        {
                            events_container_type& cur_events = m_info[ *cur ];

                            if ( ( *cur_event_counter == 0 ) ||
                                 ( *cur_event_counter == NO_DATA_AVAILABLE ) )
                            {
                                continue;
                            }
                            cur_events.resize( *cur_event_counter );
                            for ( nevent_type x = 0,
                                              x_last = *cur_event_counter;
                                  x != x_last;
                                  ++x, ++offset )
                            {
                                cur_events[ x ].GTime = GPSTime(
                                    gtimes[ offset ], gtimen[ offset ] );
                                cur_events[ x ].amplitudeEvent =
                                    amplitude[ offset ];
                                cur_events[ x ].positionEvent =
                                    position[ offset ];
                            }
                        }
                    }
                    else
                    {
                        nevent_type tevent;

                        Stream >> tevent;
                    }
                }

                //-----------------------------------------------------------------
                /// \brief Gather TOC info for FrEvent being written.
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
                QueryEvent( const Common::TOCInfo& Info,
                            INT_4U                 FrameOffset,
                            INT_8U                 Position )
                {
                    using FrameCPP::Common::TOCInfo;

                    STRING name;
                    INT_4U sec;
                    INT_4U nsec;
                    REAL_4 ampl;

                    Info.TOCQuery( TOCInfo::IC_NAME,
                                   TOCInfo::DataType( name ),
                                   &name,
                                   TOCInfo::IC_GTIME_S,
                                   TOCInfo::DataType( sec ),
                                   &sec,
                                   TOCInfo::IC_GTIME_N,
                                   TOCInfo::DataType( nsec ),
                                   &nsec,
                                   TOCInfo::IC_AMPLITUDE,
                                   TOCInfo::DataType( ampl ),
                                   &ampl,
                                   TOCInfo::IC_EOQ );

                    events_container_type& i( m_info[ name ] );

                    event_type e;
                    e.GTime = GPSTime( sec, nsec );
                    e.amplitudeEvent = ampl;
                    e.positionEvent = Position;

                    i.push_back( e );
                }

                //-----------------------------------------------------------------
                /// \brief asignment operator
                ///
                /// \param[in] Source
                ///     The source to be copied.
                //-----------------------------------------------------------------
                inline const FrTOCEventClassicIO&
                operator=( const Previous::FrTOCEvent& Source )
                {
                    m_info.erase( m_info.begin( ), m_info.end( ) );
                    const Previous::FrTOCEvent::nameEvent_container_type& data(
                        Source.GetEvent( ) );

                    for ( Previous::FrTOCEvent::nameEvent_container_type::
                              const_iterator cur = data.begin( ),
                                             last = data.end( );
                          cur != last;
                          ++cur )
                    {
                        m_info[ cur->first ].resize( cur->second.size( ) );
                        std::copy( cur->second.begin( ),
                                   cur->second.end( ),
                                   m_info[ cur->first ].begin( ) );
                    }

                    return *this;
                }

                inline FrTOCEventClassicIO&
                operator=( FrTOCEventClassicIO&& TOC )
                {
                    static_cast< FrTOCEventData& >( *this ) =
                        static_cast< FrTOCEventData&& >( TOC );
                    return *this;
                }

            protected:
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
                    if ( m_info.size( ) > 0 )
                    {
                        std::vector< name_type >   names( m_info.size( ) );
                        std::vector< nevent_type > nevent( m_info.size( ) );
                        nevent_type                offset( 0 );
                        nevent_type                eoffset( 0 );
                        std::vector< gtimesEvent_type >    gtimes;
                        std::vector< gtimenEvent_type >    gtimen;
                        std::vector< amplitudeEvent_type > amplitude;
                        std::vector< positionEvent_type >  position;

                        for ( nameEvent_container_type::const_iterator
                                  cur = m_info.begin( ),
                                  last = m_info.end( );
                              cur != last;
                              ++cur, ++offset )
                        {
                            names[ offset ] = cur->first;
                            const nevent_type c = ( cur->second.size( ) == 0 )
                                ? ( NO_DATA_AVAILABLE )
                                : ( cur->second.size( ) );
                            nevent[ offset ] = c;
                            if ( c != NO_DATA_AVAILABLE )
                            {
                                const int ns( c + eoffset );

                                gtimes.resize( ns );
                                gtimen.resize( ns );
                                amplitude.resize( ns );
                                position.resize( ns );

                                for ( nevent_type x = 0; x != c;
                                      ++x, ++eoffset )
                                {
                                    gtimes[ eoffset ] =
                                        cur->second[ x ].GTime.GetSeconds( );
                                    gtimen[ eoffset ] =
                                        cur->second[ x ]
                                            .GTime.GetNanoseconds( );
                                    amplitude[ eoffset ] =
                                        cur->second[ x ].amplitudeEvent;
                                    position[ eoffset ] =
                                        cur->second[ x ].positionEvent;
                                }
                            }
                        }

                        const nTotalEvent_type nTotalEvent( gtimes.size( ) );

                        Stream << nevent_type( m_info.size( ) ) << names
                               << nevent << nTotalEvent << gtimes << gtimen
                               << amplitude << position;
                    }
                    else
                    {
                        Stream << nevent_type( 0 ); // nEventType
                        Stream << nevent_type( 0 ); // nTotalEvent
                    }
                }

            }; // class ClassicIO

        } // namespace FrTOCImpl
    } // namespace Version_8
} // namespace FrameCPP

#endif /* ! defined(SWIG) */
#endif /* defined( __cplusplus ) */

#endif /* FrameCPP_VERSION_8__IMPL__FrTOCEventClassicIO_HH */
