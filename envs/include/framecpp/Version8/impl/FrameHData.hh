//
// LDASTools frameCPP - A library implementing the LIGO/Virgo frame
// specification
//
// Copyright (C) 2019 California Institute of Technology
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

#ifndef FrameCPP_VERSION_8__IMPL__FrameHData_HH
#define FrameCPP_VERSION_8__IMPL__FrameHData_HH

#if defined( __cplusplus )
#if !defined( SWIG )
#include <memory>
#include <vector>

#include "ldastoolsal/types.hh"

#include "framecpp/Common/Container.hh"

#endif /* ! defined(SWIG) */
#endif /* defined(__cplusplus) */

#include "framecpp/Version7/FrameH.hh"

#if !defined( SWIGIMPORTED )
#include "framecpp/Version8/impl/FrObjectMetaData.hh"

#include "framecpp/Version8/FrDetector.hh"
#include "framecpp/Version8/FrEvent.hh"
#include "framecpp/Version8/FrHistory.hh"
#include "framecpp/Version8/FrProcData.hh"
#include "framecpp/Version8/FrRawData.hh"
#include "framecpp/Version8/FrSimData.hh"
#include "framecpp/Version8/FrSimEvent.hh"
#include "framecpp/Version8/FrSummary.hh"
#include "framecpp/Version8/FrTable.hh"
#include "framecpp/Version8/FrVect.hh"
#endif /* !defined(SWIGIMPORTED) */

#include "framecpp/storage/data/FrameH.hh"

#if defined( __cplusplus )
#if !defined( SWIG )

namespace FrameCPP
{
    namespace Version_8
    {
        namespace FrameHImpl
        {
          class Data : public Impl::FrObjectMetaData< Data >,
                       public v5::FrameH<FrVect /* type */,
                                         FrVect /* user */,
                                         FrDetector /* detectSim */,
                                         FrDetector /* detectProc*/,
                                         FrHistory /* history */,
                                         FrRawData /* rawData */,
                                         FrProcData /* procData */,
                                         FrSimData /* simData */,
                                         FrEvent /* event */,
                                         FrSimEvent /* simEvent */,
                                         FrSummary /* summaryData */,
                                         FrVect /* auxData */,
                                         FrTable /* auxTable */
                                         >
            {
            };

        } // namespace FrameHImpl
    } // namespace Version_8
} // namespace FrameCPP

FR_OBJECT_META_DATA_DECLARE( FrameHImpl )

#endif /* ! defined(SWIG) */
#endif /* defined(__cplusplus) */

#endif /* FrameCPP_VERSION_8__IMPL__FrameHData_HH */
