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

#ifndef FrameCPP_VERSION_6_FrTOCEvent_HH
#define FrameCPP_VERSION_6_FrTOCEvent_HH

#include "framecpp/Version6/STRING.hh"
#include "framecpp/Version6/GPSTime.hh"

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
        class FrTOCEvent
        {
        public:
            typedef INT_4U nevent_type;
            typedef STRING name_type;
            typedef INT_4U gtimesEvent_type;
            typedef INT_4U gtimenEvent_type;
            typedef REAL_4 amplitudeEvent_type;
            typedef INT_8U positionEvent_type;

            struct event_type
            {
                GPSTime             GTime;
                amplitudeEvent_type amplitudeEvent;
                positionEvent_type  positionEvent;
            };

            static const int event_type_size = sizeof( gtimesEvent_type ) +
                sizeof( gtimenEvent_type ) + sizeof( amplitudeEvent_type ) +
                sizeof( positionEvent_type );

            typedef std::vector< event_type > events_container_type;
            /* typedef std::vector< event_container_type >
             * events_container_type; */
            typedef std::map< name_type, events_container_type >
                nameEvent_container_type;

            FrTOCEvent( );

            Common::FrameSpec::size_type
            Bytes( const Common::StreamBase& Stream ) const;

            const nameEvent_container_type& GetEvent( ) const;

            void QueryEvent( const Common::TOCInfo& Info,
                             INT_4U                 FrameOffset,
                             INT_8U                 Position );

            bool operator==( const FrTOCEvent& RHS ) const;

            template < typename SE >
            static void Description( Common::Description& Desc );

        protected:
            nameEvent_container_type m_info;

            FrTOCEvent( Common::IStream& Stream );

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
            positionEvent_type
            positionEvent( INT_4U Frame, const std::string& Channel ) const;

            //-----------------------------------------------------------------
            /// \brief Locate the position of the event
            ///
            /// \param[in] EventType
            ///     The name of the event.
            /// \param[in] Index
            ///     Offset of the event.
            ///
            /// \return
            ///     The file position of the requested event.
            //-----------------------------------------------------------------
            positionEvent_type positionEvent( const std::string& EventType,
                                              INT_4U             Index ) const;

            void write( Common::OStream& Stream ) const;
        };

        inline Common::FrameSpec::size_type
        FrTOCEvent::Bytes( const Common::StreamBase& Stream ) const
        {
            Common::FrameSpec::size_type retval = sizeof( nevent_type );
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

        template < typename SE >
        void
        FrTOCEvent::Description( Common::Description& Desc )
        {
            Desc(
                SE( "nEventType", "INT_4U", "Number of FrEvent in the file" ) );
            Desc( SE( "nameEvent", "*STRING", "Array of FrEvent names" ) );
            Desc( SE( "nEvent",
                      "*INT_4U",
                      "Number of FrEvent for each type of FrEvent"
                      " (size of nEventType)" ) );
            Desc(
                SE( "GTimeSEvent", "*INT_4U", "GPS time in integer seconds" ) );
            Desc( SE( "GTimeNEvent",
                      "*INT_4U",
                      "Residual GPS time in integer nanoseconds" ) );
            Desc( SE( "amplitudeEvent", "*REAL_4", "Event amplitude" ) );
            Desc( SE( "positionEvent",
                      "*INT_8U",
                      "Array of FrEvent positions, in bytes,"
                      " from beginning of file" ) );
        }

        inline const FrTOCEvent::nameEvent_container_type&
        FrTOCEvent::GetEvent( ) const
        {
            return m_info;
        }
    } // namespace Version_6
} // namespace FrameCPP

#endif /* FrameCPP_VERSION_6_FrTOCEvent_HH */
