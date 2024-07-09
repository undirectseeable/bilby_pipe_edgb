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

#ifndef FrameCPP__VERSION_6__Specs_HH
#define FrameCPP__VERSION_6__Specs_HH

#include "ldastoolsal/types.hh"

#ifndef SWIGIMPORTED
#include "framecpp/Common/DetectorNames.hh"
#endif /* SWIGIMPORTED */
#include "framecpp/Common/FrameSpec.hh"

#if defined( __cplusplus ) && !defined( SWIG )
namespace FrameCPP
{
    namespace Common
    {
        class IStream;
        class OStream;
    } /* namespace Common */

    namespace Version_4
    {
    }

    /**
     * \brief Implementation of the version 6 specification
     *
     * This namespace includes classes and functions needed to implement
     * the version 6 frame specification as described by LIGO-T970130-F-E
     * dated August 14, 2002.
     */
    namespace Version_6
    {
        using Common::IStream;
        using Common::OStream;

        /**
         * The namespace Previous is to the version 4 frame specification
         * since the version 5 frame specification was never fully
         * implemented.
         */
        namespace Previous = Version_4;

        typedef REAL_4 dt_type;
        typedef INT_8U position_type;

        const CHAR_U DATA_FORMAT_VERSION = 6;
        const CHAR_U LIBRARY_MINOR_VERSION = 3;

        bool init_frame_spec( );

#ifndef SWIGIMPORTED
        extern const Common::DetectorNames& DetectorNameTable;
#endif /* SWIGIMPORTED */

    } /* namespace Version_6 */
} /* namespace FrameCPP */
#endif /* defined(__cplusplus) && !defined(SWIG) */
#endif /* FrameCPP__VERSION_6__Specs_HH */
