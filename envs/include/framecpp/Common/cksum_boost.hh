//
// LDASTools frameCPP - A library implementing the LIGO/Virgo frame
// specification
//
// Copyright (C) 2022 California Institute of Technology
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

#ifndef FRAME_CPP__Common__CRC_BOOST_HH
#define FRAME_CPP__Common__CRC_BOOST_HH

#if !SWIGIMPORTED

#include <cstdint>

#include <boost/crc.hpp>

#include "framecpp/Common/cksum.hh"

namespace FrameCPP
{
    namespace Common
    {

        typedef boost::crc_optimal< 32, //< Number of bits
                                    0x04C11DB7, //< General Polynomial
                                    0, //< Initial Remainder
                                    0xFFFFFFFF, //< Final XOR (complemented)
                                    false, //< Reflect Input
                                    false //< Reflect Remainder
                                    >
            boost_crc_cksum_type;

        /// @brief Implements Un*x cksum utility
        ///
        /// This implements the CRC checksum as defined by the Un*x command of
        /// hte same name
        typedef cksum_impl< boost_crc_cksum_type > cksum_boost;

    }; // namespace Common

} // namespace FrameCPP

#endif /* !SWIGIMPORTED */

#endif /* FRAME_CPP__Common__CRC_BOOST_HH */
