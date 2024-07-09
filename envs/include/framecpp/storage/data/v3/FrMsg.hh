//
// LDASTools frameCPP - A library implementing the LIGO/Virgo frame
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

#ifndef FRAMECPPCPP__STORAGE__DATA__V3__FR_MSG_HH
#define FRAMECPPCPP__STORAGE__DATA__V3__FR_MSG_HH

#if defined( __cplusplus )
#if !defined( SWIG )

#include <string>

#include "ldastoolsal/ldas_types.h"

#endif /* !defined( SWIG ) */
#endif /* !defined( __cplusplus ) */

#undef FR_MSG_ALARM_TYPE
#define FR_MSG_ALARM_TYPE std::string

#undef FR_MSG_MESSAGE_TYPE
#define FR_MSG_MESSAGE_TYPE std::string

#undef FR_MSG_SEVERITY_TYPE
#define FR_MSG_SEVERITY_TYPE INT_4U

#if defined( __cplusplus )
#if !defined( SWIG )

namespace FrameCPP
{
    namespace v3
    {
        //-----------------------------------------------------------
        /// @brief Storage space for FrMsg information
        ///
        /// This stores information about an FrMsg element that
        /// needs to persist beyond an I/O operation
        //-----------------------------------------------------------
        class FrMsgData
        {
        public:
            typedef FR_MSG_ALARM_TYPE    alarm_type;
            typedef FR_MSG_MESSAGE_TYPE  message_type;
            typedef FR_MSG_SEVERITY_TYPE severity_type;

            inline const alarm_type&
            GetAlarm( ) const
            {
                return ( alarm );
            }

            inline const message_type&
            GetMessage( ) const
            {
                return ( message );
            }

            inline severity_type
            GetSeverity( ) const
            {
                return ( severity );
            }

            inline void
            SetAlarm( const alarm_type& Value )
            {
                alarm = Value;
            }

            inline void
            SetMessage( const message_type& Value )
            {
                message = Value;
            }

            inline void
            SetSeverity( severity_type Value )
            {
                severity = Value;
            }

        protected:
            //-------------------------------------------------------------
            /// Name of message, error flag or alarm state
            //-------------------------------------------------------------
            alarm_type alarm;
            //-------------------------------------------------------------
            /// Message body
            //-------------------------------------------------------------
            message_type message;
            //-------------------------------------------------------------
            /// Message severity level (To Be Defined)
            //-------------------------------------------------------------
            severity_type severity;
        };

    } // namespace v3

} // namespace FrameCPP

#endif /* !defined( SWIG ) */
#endif /* !defined( __cplusplus ) */

#endif /* FRAMECPPCPP__STORAGE__DATA__V3__FR_MSG_HH */
