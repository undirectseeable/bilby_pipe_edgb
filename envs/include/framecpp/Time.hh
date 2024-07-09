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

#ifndef FRAME_CPP_INTERFACE__Time_HH
#define FRAME_CPP_INTERFACE__Time_HH

#include "framecpp/FrameCPP.hh"

#if FRAME_SPEC_CURRENT >= 3
#include "ldastoolsal/gpstime.hh"
#else
#error Unsupported Frame specification
#endif /* FRAME_SPEC_CURRENT */

namespace FrameCPP
{
#if FRAME_SPEC_CURRENT >= 3
    typedef LDASTools::AL::GPSTime Time;
#endif /* FRAME_SPEC_CURRENT >= 3 */
} // namespace FrameCPP

#endif /* FRAME_CPP_INTERFACE__FrameH_HH */
