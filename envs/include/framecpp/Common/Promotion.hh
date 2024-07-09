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

#ifndef FRAMECPP__COMMON__Promotion_HH
#define FRAMECPP__COMMON__Promotion_HH

namespace FrameCPP
{
    template < typename T >
    inline bool
    NeedsToBeDemoted( Common::FrameSpec::Object* Obj )
    {
        if ( dynamic_cast< T* >( Obj ) != (T*)NULL )
        {
            // No conversion needed
            return false;
        }
        return true;
    }

    template < typename T >
    inline bool
    NeedsToBePromoted( Common::FrameSpec::Object* Obj )
    {
        if ( dynamic_cast< T* >( Obj ) != (T*)NULL )
        {
            return false;
        }
        return true;
    }
} // namespace FrameCPP

#endif /* FRAMECPP__COMMON__Promotion_HH */
