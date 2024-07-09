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

#ifndef FrameCPP__Common__FrSH_HH
#define FrameCPP__Common__FrSH_HH

#include "framecpp/Common/FrameSpec.hh"
#include "framecpp/Common/StringStream.hh"

#include <iostream>

namespace FrameCPP
{
    namespace Common
    {
        class Description;
        class IStringStream;

        //-------------------------------------------------------------------
        /// \brief Interface definition for an FrSH structure
        class FrSH : public FrameSpec::Object
        {
        public:
            typedef INT_2U        cmn_classId_type;
            typedef IStringStream assign_stream_type;

            FrSH( );

            //-----------------------------------------------------------------
            /// \todo
            ///     See about storing name in this class and eliminate the
            ///     need for this virtual method.
            //-----------------------------------------------------------------
            virtual const std::string& name( ) const = 0;

            virtual cmn_classId_type classId( ) const = 0;

            //-----------------------------------------------------------------
            /// \brief Assign the contents of the instance
            ///
            /// \param[in] Stream
            ///     An input stream from which to read information for
            ///     the instance.
            //-----------------------------------------------------------------
            virtual void assign( assign_stream_type& Stream ) = 0;
        };

        inline FrSH::FrSH( )
            : FrameSpec::Object( FrameSpec::Info::FSI_FR_SH,
                                 (Description*)NULL )
        {
        }
    } // namespace Common
} // namespace FrameCPP

#endif /* FrameCPP__Common__FrSH_HH */
