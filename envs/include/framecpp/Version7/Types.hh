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

#ifndef FrameCPP_VERSION_7__Types_HH
#define FrameCPP_VERSION_7__Types_HH

#include "framecpp/Version7/FrameStream.hh"

namespace FrameCPP
{
    namespace Version_7
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
        class FrSummary;
        class FrTable;
        class FrTOC;
        class FrVect;
    } // namespace Version_7

    typedef Version_7::Dimension Dimension;

    typedef Version_7::FrameH       FrameH;
    typedef Version_7::FrAdcData    FrAdcData;
    typedef Version_7::FrDetector   FrDetector;
    typedef Version_7::FrEndOfFile  FrEndOfFile;
    typedef Version_7::FrEndOfFrame FrEndOfFrame;
    typedef Version_7::FrEvent      FrEvent;
    typedef Version_7::FrHeader     FrHeader;
    typedef Version_7::FrHistory    FrHistory;
    typedef Version_7::FrMsg        FrMsg;
    typedef Version_7::FrProcData   FrProcData;
    typedef Version_7::FrRawData    FrRawData;
    typedef Version_7::FrSE         FrSE;
    typedef Version_7::FrSerData    FrSerData;
    typedef Version_7::FrSH         FrSH;
    typedef Version_7::FrSimData    FrSimData;
    typedef Version_7::FrSimEvent   FrSimEvent;
    typedef Version_7::FrSummary    FrSummary;
    typedef Version_7::FrTable      FrTable;
    typedef Version_7::FrTOC        FrTOC;
    typedef Version_7::FrVect       FrVect;
} // namespace FrameCPP

#endif /* FrameCPP_VERSION_7__Types_HH */
