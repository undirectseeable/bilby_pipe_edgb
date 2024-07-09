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

#ifndef FrameCPP__COMMON__FR_DETECTOR_HH
#define FrameCPP__COMMON__FR_DETECTOR_HH

#include <boost/preprocessor/stringize.hpp>
#include "framecpp/Common/FrameSpec.hh"

namespace FrameCPP
{
    namespace Common
    {
        class FrDetector : public FrameSpec::Object
        {
        public:
            static const FrameSpec::Info::frame_object_types STRUCT_ID =
                FrameSpec::Info::FSI_FR_DETECTOR;

            FrDetector( const Description* Desc );

            virtual ~FrDetector( );
        };

        inline FrDetector::FrDetector( const Description* Desc )
            : FrameSpec::Object( STRUCT_ID, Desc )
        {
        }

        inline FrDetector::~FrDetector( )
        {
        }

    } // namespace Common
} // namespace FrameCPP

#endif /* FrameCPP__COMMON__FR_DETECTOR_HH */
