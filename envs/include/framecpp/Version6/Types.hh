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

#ifndef FrameCPP_VERSION_6__Types_HH
#define FrameCPP_VERSION_6__Types_HH

#include "framecpp/Version6/FrameStream.hh"

namespace FrameCPP
{
    namespace Version_6
    {
        class Dimension;

        class FrameH;
        class FrAdcData;
        class FrDetector;
        class FrEndOfFile;
        class FrEndOfFrame;
        class FrEvent;
        class FrHeader;
        class FrHistory;
        class FrMsg;
        class FrProcData;
        class FrRawData;
        class FrSE;
        class FrSerData;
        class FrSH;
        class FrSimData;
        class FrSimEvent;
        class FrStatData;
        class FrSummary;
        class FrTable;
        class FrTOC;
        class FrVect;
    } // namespace Version_6

    typedef Version_6::Dimension Dimension;

    typedef Version_6::FrameH       FrameH;
    typedef Version_6::FrAdcData    FrAdcData;
    typedef Version_6::FrDetector   FrDetector;
    typedef Version_6::FrEndOfFile  FrEndOfFile;
    typedef Version_6::FrEndOfFrame FrEndOfFrame;
    typedef Version_6::FrEvent      FrEvent;
    typedef Version_6::FrHeader     FrHeader;
    typedef Version_6::FrHistory    FrHistory;
    typedef Version_6::FrMsg        FrMsg;
    typedef Version_6::FrProcData   FrProcData;
    typedef Version_6::FrRawData    FrRawData;
    typedef Version_6::FrSE         FrSE;
    typedef Version_6::FrSerData    FrSerData;
    typedef Version_6::FrSH         FrSH;
    typedef Version_6::FrSimData    FrSimData;
    typedef Version_6::FrSimEvent   FrSimEvent;
    typedef Version_6::FrStatData   FrStatData;
    typedef Version_6::FrSummary    FrSummary;
    typedef Version_6::FrTable      FrTable;
    typedef Version_6::FrTOC        FrTOC;
    typedef Version_6::FrVect       FrVect;
} // namespace FrameCPP

#endif /* FrameCPP_VERSION_6__Types_HH */
