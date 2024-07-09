/*
 * LDASTools frameCPP - A library implementing the LIGO/Virgo frame
 * specification
 *
 * Copyright (C) 2018 California Institute of Technology
 *
 * LDASTools frameCPP is free software; you may redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 (GPLv2) of the
 * License or at your discretion, any later version.
 *
 * LDASTools frameCPP is distributed in the hope that it will be useful, but
 * without any warranty or even the implied warranty of merchantability
 * or fitness for a particular purpose. See the GNU General Public
 * License (GPLv2) for more details.
 *
 * Neither the names of the California Institute of Technology (Caltech),
 * The Massachusetts Institute of Technology (M.I.T), The Laser
 * Interferometer Gravitational-Wave Observatory (LIGO), nor the names
 * of its contributors may be used to endorse or promote products derived
 * from this software without specific prior written permission.
 *
 * You should have received a copy of the licensing terms for this
 * software included in the file LICENSE located in the top-level
 * directory of this package. If you did not, you can view a copy at
 * http://dcc.ligo.org/M1500244/LICENSE
 */

#ifndef FrameCPP__VERSION_3__STRING_HH
#define FrameCPP__VERSION_3__STRING_HH

#if defined( __cplusplus )

#if !defined( SWIGIMPORTED )
#include <string>
#endif /* ! defined(SWIGIMPORTED) */

#if !defined( SWIGIMPORTED )
#include "ldastoolsal/types.hh"

#include "framecpp/Common/STRING.hh"
#endif /* ! defined(SWIGIMPORTED) */

namespace FrameCPP
{
    namespace Version_3
    {
        typedef Common::STRING< INT_2U >        STRING;
        typedef Common::STRING_SHADOW< INT_2U > STRING_SHADOW;
    } /* namespace Version_3 */
} /* namespace FrameCPP */

#endif /* defined(__cplusplus) */

#endif /* FrameCPP__VERSION_3__STRING_HH */
