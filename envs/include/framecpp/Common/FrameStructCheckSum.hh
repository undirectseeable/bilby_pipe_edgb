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

/* -*- mode: C++; c-basic-offset: 2; -*- */
#ifndef FrameCPP__COMMON__FrameStructCheckSum_HH
#define FrameCPP__COMMON__FrameStructCheckSum_HH

#include "ldastoolsal/types.hh"

#include "framecpp/Common/FrameSpec.hh"
#include "framecpp/Common/IOStream.hh"

namespace FrameCPP
{
    namespace Common
    {
        //-------------------------------------------------------------------
        /// \brief Per frame structure checksum
        ///
        /// This class is intended to provide methods to support the
        /// per frame structure checksum data which as added with
        /// version 8 of the frame specification.
        ///
        /// \tparam CT
        ///     The actual type used for the checksum field.
        //-------------------------------------------------------------------
        template < class CT >
        class FrameStructCheckSum
        {
        public:
            typedef CT chkSum_type;

            FrameStructCheckSum( );

            FrameStructCheckSum( IStream& Stream );

            virtual FrameSpec::size_type
            Bytes( const StreamBase& Stream ) const;

        private:
            chkSum_type m_chkSum;
        };
    } // namespace Common
} // namespace FrameCPP

#include "framecpp/Common/FrameStructCheckSum.tcc"

#endif /* FrameCPP__COMMON__FrameStructCheckSum_HH */
