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

#ifndef FRAME_CPP_INTERFACE__FRAME_CPP_HH
#define FRAME_CPP_INTERFACE__FRAME_CPP_HH

#if defined( __cplusplus )
#if !defined( SWIGIMPORTED )
#include <string>
#endif /* ! defined(SWIGIMPORTED) */
#endif /* defined(__cplusplus) */

#include "ldastoolsal/types.hh"

#include "framecpp/Common/FrameSpec.hh"

#if defined( __cplusplus )
/**
 * \brief I/O library for implementing the LIGO/Virgo frame specification.
 *
 * All elements described within this namespace are intended to
 * implement the various frame specifications created by LIGO/Virgo.
 */
namespace FrameCPP
{
    /*---------------------------------------------------------------------
     * Constants representing version information
      ---------------------------------------------------------------------*/
    /*---------------------------------------------------------------------
     * Establish the default version namespace
      --------------------------------------------------------------------*/

#ifndef SWIG
#if FRAME_SPEC_CURRENT == 3
    namespace Version_3
    {
    }
    namespace Version = Version_3;
#elif FRAME_SPEC_CURRENT == 4
    namespace Version_4
    {
    }
    namespace Version = Version_4;
#elif FRAME_SPEC_CURRENT == 5
    namespace Version_5
    {
    }
    namespace Version = Version_5;
#elif FRAME_SPEC_CURRENT == 6
    namespace Version_6
    {
    }
    namespace Version = Version_6;
#elif FRAME_SPEC_CURRENT == 7
    namespace Version_7
    {
    }
    namespace Version = Version_7;
#elif FRAME_SPEC_CURRENT == 8
    namespace Version_8
    {
    }
    namespace Version = Version_8;
#else
#error Version namespace not defined for FRAME_SPEC_CURRENT
#endif /* PRAME_SPEC_CURRENT */

    /**
     * \brief Get the CVS date for this version of frameCPP
     */
    std::string GetCVSDate( );

    /**
     * \brief Get the date when frameCPP was built.
     */
    std::string GetBuildDate( );

    /**
     * \brief Return the data format version
     */
    INT_2U GetDataFormatVersion( );

    /**
     * \brief Return the minor version of the frame library
     */
    INT_2U GetFrameLibraryMinorVersion( );

    /**
     * \brief Initialize the C++ Interface
     */
    void Initialize( );
#endif /* SWIG */

} /* namespace FrameCPP */

#endif /* defined(__cplusplus) */
#endif /* FRAME_CPP_INTERFACE__FRAME_CPP_HH */
