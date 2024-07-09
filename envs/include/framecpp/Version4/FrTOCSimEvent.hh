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

#ifndef FrameCPP_VERSION_4_FrTOCSimEvent_HH
#define FrameCPP_VERSION_4_FrTOCSimEvent_HH

#include "framecpp/Version4/STRING.hh"
#include "framecpp/Version4/GPSTime.hh"

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
        class FrTOCSimEvent
        {
        public:
            typedef INT_4U nSimEvt_type;
            typedef STRING name_type;
            typedef INT_4U gtimesSimEvent_type;
            typedef INT_4U gtimenSimEvent_type;
            typedef INT_8U positionSimEvent_type;

            struct trig_data_type
            {
                GPSTime               GTime;
                positionSimEvent_type positionSimEvent;
            };

            typedef std::map< name_type, trig_data_type > MapSimEvt_type;

            FrTOCSimEvent( );

            Common::FrameSpec::size_type
            Bytes( const Common::StreamBase& Stream ) const;

            bool operator==( const FrTOCSimEvent& RHS ) const;

            static void Description( Common::Description& Desc );

            const MapSimEvt_type& GetSimEvent( ) const;

            MapSimEvt_type::const_iterator
            GetSimEvent( const std::string& Channel ) const;

            void QuerySimEvent( const Common::TOCInfo& Info,
                                INT_4U                 FrameOffset,
                                INT_8U                 Position );

        protected:
            MapSimEvt_type m_info;

            FrTOCSimEvent( Common::IStream& Stream, INT_4U FrameCount );
            void write( Common::OStream& Stream ) const;
        };

        inline Common::FrameSpec::size_type
        FrTOCSimEvent::Bytes( const Common::StreamBase& Stream ) const
        {
            Common::FrameSpec::size_type retval = sizeof( nSimEvt_type );
            //-----------------------------------------------------------------
            //
            //-----------------------------------------------------------------
            if ( m_info.size( ) > 0 )
            {
                for ( MapSimEvt_type::const_iterator cur = m_info.begin( ),
                                                     last = m_info.end( );
                      cur != last;
                      ++cur )
                {
                    retval += cur->first.Bytes( ) // name
                        + sizeof( gtimesSimEvent_type ) +
                        sizeof( gtimenSimEvent_type ) +
                        sizeof( positionSimEvent_type );
                }
            }
            return retval;
        }

        inline const FrTOCSimEvent::MapSimEvt_type&
        FrTOCSimEvent::GetSimEvent( ) const
        {
            return m_info;
        }

        inline FrTOCSimEvent::MapSimEvt_type::const_iterator
        FrTOCSimEvent::GetSimEvent( const std::string& Channel ) const
        {
            return m_info.find( Channel );
        }

    } // namespace Version_4
} // namespace FrameCPP

#endif /* FrameCPP_VERSION_4_FrTOCSimEvent_HH */
