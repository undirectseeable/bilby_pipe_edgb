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

#ifndef FrameCPP_VERSION_8__IMPL__FrTOCSimEventData_HH
#define FrameCPP_VERSION_8__IMPL__FrTOCSimEventData_HH

namespace FrameCPP
{
    namespace Version_8
    {
        namespace FrTOCImpl
        {
            class FrTOCSimEventData
            {
            public:
                typedef INT_4U nevent_type;
                typedef STRING name_type;
                typedef INT_4U nTotalSEvent_type;
                typedef INT_4U gtimesSim_type;
                typedef INT_4U gtimenSim_type;
                typedef REAL_4 amplitudeSimEvent_type;
                typedef INT_8U positionSimEvent_type;

                struct event_type
                {
                    //---------------------------------------------------------------
                    /// \brief Start time of event.
                    //---------------------------------------------------------------
                    GPSTime GTime;
                    //---------------------------------------------------------------
                    /// \brief Amplitude of event.
                    //---------------------------------------------------------------
                    amplitudeSimEvent_type amplitudeSimEvent;
                    //---------------------------------------------------------------
                    /// \brief FrSimEvent offset positions.
                    ///
                    /// FrSimEvent offset positions, in bytes,
                    /// from the beginning of the file.
                    //---------------------------------------------------------------
                    positionSimEvent_type positionSimEvent;

                    inline const event_type&
                    operator=( const Previous::FrTOCSimEvent::event_type& Source )
                    {
                        GTime = Source.GTime;
                        amplitudeSimEvent = Source.amplitudeSimEvent;
                        positionSimEvent = Source.positionSimEvent;

                        return *this;
                    }
                };

                static const int event_type_size = sizeof( gtimesSim_type ) +
                    sizeof( gtimenSim_type ) + sizeof( amplitudeSimEvent_type ) +
                    sizeof( positionSimEvent_type );

                typedef std::vector< event_type > events_container_type;
                /* typedef std::vector< event_container_type >
                 * events_container_type; */
                typedef std::map< name_type, events_container_type >
                    nameSimEvent_container_type;

                constexpr static INT_4U NO_DATA_AVAILABLE = 0xFFFFFFFF;

                //-----------------------------------------------------------------
                /// \brief Return all events
                ///
                /// \return
                ///     Constant container to the indexed FrSimEvent elements.
                //-----------------------------------------------------------------
                const nameSimEvent_container_type&
                GetSimEvent( ) const
                {
                    return m_info;
                }

            protected:
                nameSimEvent_container_type m_info;

                //-----------------------------------------------------------------
                /// \brief Locate the position of the event
                ///
                /// \param[in] Frame
                ///     Frame offset of the event.
                /// \param[in] SimEvent
                ///     The name of the event.
                ///
                /// \return
                ///     The file position of the requested event.
                //-----------------------------------------------------------------
                inline positionSimEvent_type
                positionSimEvent( INT_4U Frame, const std::string& SimEvent ) const
                {
                  std::cerr << "DEBUG: positionSimEvent(" << Frame << ", " << SimEvent << ")" << std::endl;
                    const nameSimEvent_container_type::const_iterator event(
                        m_info.find( SimEvent ) );
                    //-----------------------------------------------------------------
                    // Locate the event by name
                    //-----------------------------------------------------------------
                    if ( event == m_info.end( ) )
                    {
                        //---------------------------------------------------------------
                        // SimEvent name does not exist.
                        //---------------------------------------------------------------
                        std::ostringstream msg;

                        msg << "No FrSimEvent structures with the name '" << SimEvent
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
                    std::cerr << "DEBUG: FrSimEvent file position: " << event->second[ Frame ].positionSimEvent << std::endl;
                    return event->second[ Frame ].positionSimEvent;
                }

                inline positionSimEvent_type
                positionSimEvent( const std::string& SimEvent, INT_4U Index ) const
                {
                  std::cerr << "DEBUG: positionSimEvent(" << SimEvent << ", " << Index << ")" << std::endl;

                    const nameSimEvent_container_type::const_iterator event(
                        m_info.find( SimEvent ) );
                    //-----------------------------------------------------------------
                    // Locate the event by name
                    //-----------------------------------------------------------------
                    if ( event == m_info.end( ) )
                    {
                        //---------------------------------------------------------------
                        // SimEvent name does not exist.
                        //---------------------------------------------------------------
                        std::ostringstream msg;

                        msg << "No FrSimEvent structures with the name '" << SimEvent
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
                    std::cerr << "DEBUG: FrSimEvent file position: " << event->second[ Index ].positionSimEvent << std::endl;
                    return event->second[ Index ].positionSimEvent;
                }
            };

        } // namespace FrTOCImpl
    } // namespace Version_8
} // namespace FrameCPP

#endif /* FrameCPP_VERSION_8__IMPL__FrTOCSimEventData_HH */
