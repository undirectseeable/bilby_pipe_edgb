//
// LDASTools - A library implementing the LIGO/Virgo frame
// specification
//
// Copyright (C) 2020 California Institute of Technology
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

#ifndef FrameCPP_VERSION_8__IMPL__FrTOCEventData_HH
#define FrameCPP_VERSION_8__IMPL__FrTOCEventData_HH

namespace FrameCPP
{
    namespace Version_8
    {
        namespace FrTOCImpl
        {
            class FrTOCEventData
            {
            public:
                typedef INT_4U nevent_type;
                typedef STRING name_type;
                typedef INT_4U nTotalEvent_type;
                typedef INT_4U gtimesEvent_type;
                typedef INT_4U gtimenEvent_type;
                typedef REAL_4 amplitudeEvent_type;
                typedef INT_8U positionEvent_type;

                struct event_type
                {
                    //---------------------------------------------------------------
                    /// \brief Start time of event.
                    //---------------------------------------------------------------
                    GPSTime GTime;
                    //---------------------------------------------------------------
                    /// \brief Amplitude of event.
                    //---------------------------------------------------------------
                    amplitudeEvent_type amplitudeEvent;
                    //---------------------------------------------------------------
                    /// \brief FrEvent offset positions.
                    ///
                    /// FrEvent offset positions, in bytes,
                    /// from the beginning of the file.
                    //---------------------------------------------------------------
                    positionEvent_type positionEvent;

                    inline const event_type&
                    operator=( const Previous::FrTOCEvent::event_type& Source )
                    {
                        GTime = Source.GTime;
                        amplitudeEvent = Source.amplitudeEvent;
                        positionEvent = Source.positionEvent;

                        return *this;
                    }
                };

                static const int event_type_size = sizeof( gtimesEvent_type ) +
                    sizeof( gtimenEvent_type ) + sizeof( amplitudeEvent_type ) +
                    sizeof( positionEvent_type );

                typedef std::vector< event_type > events_container_type;
                /* typedef std::vector< event_container_type >
                 * events_container_type; */
                typedef std::map< name_type, events_container_type >
                    nameEvent_container_type;

                constexpr static INT_4U NO_DATA_AVAILABLE = 0xFFFFFFFF;

                //-----------------------------------------------------------------
                /// \brief Return all events
                ///
                /// \return
                ///     Constant container to the indexed FrEvent elements.
                //-----------------------------------------------------------------
                const nameEvent_container_type&
                GetEvent( ) const
                {
                    return m_info;
                }

            protected:
                nameEvent_container_type m_info;

                //-----------------------------------------------------------------
                /// \brief Locate the position of the event
                ///
                /// \param[in] Frame
                ///     Frame offset of the event.
                /// \param[in] Event
                ///     The name of the event.
                ///
                /// \return
                ///     The file position of the requested event.
                //-----------------------------------------------------------------
                inline positionEvent_type
                positionEvent( INT_4U Frame, const std::string& Event ) const
                {
                  std::cerr << "DEBUG: positionEvent(" << Frame << ", " << Event << ")" << std::endl;
                    const nameEvent_container_type::const_iterator event(
                        m_info.find( Event ) );
                    //-----------------------------------------------------------------
                    // Locate the event by name
                    //-----------------------------------------------------------------
                    if ( event == m_info.end( ) )
                    {
                        //---------------------------------------------------------------
                        // Event name does not exist.
                        //---------------------------------------------------------------
                        std::ostringstream msg;

                        msg << "No FrEvent structures with the name '" << Event
                            << "'";
                        std::cerr << "DEBUG: " << msg.str( ) << std::endl;
                        throw std::out_of_range( msg.str( ) );
                    }
                    //-----------------------------------------------------------------
                    // Verify that the index exists
                    //-----------------------------------------------------------------
                    if ( Frame >= event->second.size( ) )
                    {
                        std::ostringstream msg;

                        msg << "Request for frame " << Frame
                            << " exceeds the range of 0 through "
                            << ( event->second.size( ) - 1 );
                        std::cerr << "DEBUG: " << msg.str( ) << std::endl;
                        throw std::out_of_range( msg.str( ) );
                    }
                    //-----------------------------------------------------------------
                    // Return position information
                    //-----------------------------------------------------------------
                    std::cerr << "DEBUG: FrEvent file position: " << event->second[ Frame ].positionEvent << std::endl;
                    return event->second[ Frame ].positionEvent;
                }

                inline positionEvent_type
                positionEvent( const std::string& Event, INT_4U Index ) const
                {
                  std::cerr << "DEBUG: positionEvent(" << Event << ", " << Index << ")" << std::endl;

                    const nameEvent_container_type::const_iterator event(
                        m_info.find( Event ) );
                    //-----------------------------------------------------------------
                    // Locate the event by name
                    //-----------------------------------------------------------------
                    if ( event == m_info.end( ) )
                    {
                        //---------------------------------------------------------------
                        // Event name does not exist.
                        //---------------------------------------------------------------
                        std::ostringstream msg;

                        msg << "No FrEvent structures with the name '" << Event
                            << "'";
                        std::cerr << "DEBUG: " << msg.str( ) << std::endl;
                        throw std::out_of_range( msg.str( ) );
                    }
                    //-----------------------------------------------------------------
                    // Verify that the index exists
                    //-----------------------------------------------------------------
                    if ( Index >= event->second.size( ) )
                    {
                        std::ostringstream msg;

                        msg << "Request for index " << Index
                            << " exceeds the range of 0 through "
                            << ( event->second.size( ) - 1 );
                        throw std::out_of_range( msg.str( ) );
                    }
                    //-----------------------------------------------------------------
                    // Return position information
                    //-----------------------------------------------------------------
                    std::cerr << "DEBUG: FrEvent file position: " << event->second[ Index ].positionEvent << std::endl;
                    return event->second[ Index ].positionEvent;
                }
            };

        } // namespace FrTOCImpl
    } // namespace Version_8
} // namespace FrameCPP

#endif /* FrameCPP_VERSION_8__IMPL__FrTOCEventData_HH */
