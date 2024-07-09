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

#ifndef FrameCPP_VERSION_6_FrTOCSimEvent_HH
#define FrameCPP_VERSION_6_FrTOCSimEvent_HH

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
        class FrTOCSimEvent
        {
        public:
            typedef INT_4U nevent_type;
            typedef STRING name_type;
            typedef INT_4U gtimesSim_type;
            typedef INT_4U gtimenSim_type;
            typedef REAL_4 amplitudeSimEvent_type;
            typedef INT_8U positionSimEvent_type;

            struct event_type
            {
                GPSTime                GTime;
                amplitudeSimEvent_type amplitudeSimEvent;
                positionSimEvent_type  positionSimEvent;
            };

            static const int event_type_size = sizeof( gtimesSim_type ) +
                sizeof( gtimenSim_type ) + sizeof( amplitudeSimEvent_type ) +
                sizeof( positionSimEvent_type );

            typedef std::vector< event_type > events_container_type;
            typedef std::map< name_type, events_container_type >
                nameSimEvent_container_type;

            FrTOCSimEvent( );

            Common::FrameSpec::size_type
            Bytes( const Common::StreamBase& Stream ) const;

            const nameSimEvent_container_type& GetSimEvent( ) const;

            void QuerySimEvent( const Common::TOCInfo& Info,
                                INT_4U                 FrameOffset,
                                INT_8U                 Position );

            bool operator==( const FrTOCSimEvent& RHS ) const;

            template < typename SE >
            static void Description( Common::Description& Desc );

        protected:
            nameSimEvent_container_type m_info;

            FrTOCSimEvent( Common::IStream& Stream );

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
            positionSimEvent_type
            positionSimEvent( INT_4U Frame, const std::string& SimEvent ) const;

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
            positionSimEvent_type
            positionSimEvent( const std::string& EventType,
                              INT_4U             Index ) const;

            void write( Common::OStream& Stream ) const;
        };

        inline Common::FrameSpec::size_type
        FrTOCSimEvent::Bytes( const Common::StreamBase& Stream ) const
        {
            Common::FrameSpec::size_type retval = sizeof( nevent_type );
            //-----------------------------------------------------------------
            //
            //-----------------------------------------------------------------
            for ( nameSimEvent_container_type::const_iterator
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
        FrTOCSimEvent::Description( Common::Description& Desc )
        {
            Desc( SE( "nSimEventType",
                      "INT_4U",
                      "Number of FrSimEvent in the file" ) );
            Desc(
                SE( "nameSimEvent", "*STRING", "Array of FrSimEvent names" ) );
            Desc( SE( "nSimEvent",
                      "*INT_4U",
                      "Number of FrSimEvent for each type of FrSimEvent"
                      " (size of nSimEventType)" ) );
            Desc( SE( "GTimeSSim", "*INT_4U", "GPS time in integer seconds" ) );
            Desc( SE( "GTimeNSim",
                      "*INT_4U",
                      "Residual GPS time in integer nanoseconds" ) );
            Desc( SE( "amplitudeSimEvent", "*REAL_4", "SimEvent amplitude" ) );
            Desc( SE( "positionSimEvent",
                      "*INT_8U",
                      "Array of FrSimEvent positions, in bytes,"
                      " from beginning of file" ) );
        }

        inline const FrTOCSimEvent::nameSimEvent_container_type&
        FrTOCSimEvent::GetSimEvent( ) const
        {
            return m_info;
        }

    } // namespace Version_6
} // namespace FrameCPP

#endif /* FrameCPP_VERSION_6_FrTOCSimEvent_HH */
