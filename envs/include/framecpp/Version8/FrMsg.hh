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

#ifndef FrameCPP_VERSION_8_FrMsg_HH
#define FrameCPP_VERSION_8_FrMsg_HH

#ifndef SWIGIMPORTED
#include <vector>

#include <boost/serialization/access.hpp>
#include <boost/serialization/base_object.hpp>
#include <boost/serialization/version.hpp>
#endif /* SWIGIMPORTED */

#include "ldastoolsal/types.hh"

#include "framecpp/Version8/impl/FrMsgClassicIO.hh"
#include "framecpp/Version8/impl/FrMsgSerialIO.hh"

namespace FrameCPP
{
    namespace Version_8
    {
        //===================================================================
        /// \brief Message Log Data Structure Definition
        //===================================================================
        class FrMsg : public FrMsgImpl::ClassicIO< FrMsg >,
                      public FrMsgImpl::SerialIO< FrMsg >
        {
        public:
            typedef FrMsgImpl::Data::alarm_type    alarm_type;
            typedef FrMsgImpl::Data::severity_type severity_type;

            static constexpr severity_type const DEFAULT_SEVERITY{ 0 };

            //-----------------------------------------------------------------
            /// \brief Default constructor
            ///
            /// \return
            ///    A new instance of this object.
            //-----------------------------------------------------------------
            FrMsg( );

            //-----------------------------------------------------------------
            /// \brief Copy Constructor
            ///
            /// \param[in] Source
            ///     The object from which to copy the information.
            ///
            /// \return
            ///    A new instance of this object.
            //-----------------------------------------------------------------
            FrMsg( const FrMsg& Source );

            //-----------------------------------------------------------------
            /// \brief Copy Constructor
            ///
            /// \param[in] Alarm
            ///     Name of message, error flag or alarm state.
            /// \param[in] Message
            ///     Message body
            /// \param[in] Severity
            ///     Message severity level.
            /// \param[in] GTime
            ///     GPS time corresponding to this FrMsg.
            ///
            /// \return
            ///    A new instance of this object.
            //-----------------------------------------------------------------
            FrMsg( const std::string& Alarm,
                   const std::string& Message,
                   INT_4U             Severity,
                   const GPSTime&     GTime );

            //-----------------------------------------------------------------
            /// \brief Promotion Constructor
            ///
            /// \param[in] Source
            ///     An FrAdcData structure from a previous frame specification.
            /// \param[in] Stream
            ///     The stream from which the earliest version of the
            ///     FrAdcData structure was read.
            ///
            /// \return
            ///     A new instance of an FrAdcData object
            //-----------------------------------------------------------------
            FrMsg( Previous::FrMsg& Source, istream_type* Stream );

            virtual ~FrMsg( );

            //-----------------------------------------------------------------
            /// \brief Retrieve the name of message, error flag, or alarm
            /// state.
            ///
            /// \return
            ///     The name of message, error flag, or alarm state.
            //-----------------------------------------------------------------
            const alarm_type& GetAlarm( ) const;

            //-----------------------------------------------------------------
            /// \brief Merge with another FrMsg
            ///
            /// \param[in] RHS
            ///     The source of the information to append to this FrMsg
            ///     structure.
            ///
            /// \return
            ///     A reference to this object
            //-----------------------------------------------------------------
            FrMsg& Merge( const FrMsg& RHS );

            //-----------------------------------------------------------------
            /// \brief equality operator
            ///
            /// \param[in] RHS
            ///     The FrAdcData object to be compared.
            ///
            /// \return
            ///     The value true is returned if this object is equivelent
            ///     to the RHS instance; false otherwise.
            //-----------------------------------------------------------------
            bool operator==( const FrMsg& RHS ) const;
        };

        inline bool
        FrMsg::operator==( const FrMsg& RHS ) const
        {
            return ( FrMsgImpl::Data::operator==( RHS ) );
        }

    } // namespace Version_8
} // namespace FrameCPP

#endif /* FrameCPP_VERSION_8_FrMsg_HH */
