/* * LDASTools frameCPP - A library implementing the LIGO/Virgo frame
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

#ifndef FRAME_CPP_INTERFACE__FRAME_C_H
#define FRAME_CPP_INTERFACE__FRAME_C_H

#include "ldastoolsal/ldas_types.h"

#ifndef restrict
#if !( 2 < __GNUC__ || ( 2 == __GNUC__ && 95 <= __GNUC_MINOR__ ) )
#if __STDC_VERSION__ < 199901L
#define restrict
#endif
#elif !defined( __cplusplus )
#if __STDC_VERSION__ < 199901L
#define restrict
#endif
#endif
#endif

#ifdef __cplusplus
#define restrict const
extern "C" {
#endif /* __cplusplus */

#if defined( restrict )
#if DOCUMENTATION_DOXYGEN
#undef restrict
#endif /* DOCUMENTATION_DOXYGEN */
#endif /* defined(restrict) */

/* Begin Group */
/**
 * \addtogroup CInterface C Interface
 *
 * \brief An interface for C applications to utalize FrameCPP
 *
 * @{
 */

typedef INT_4U gpstime_seconds_t;
typedef INT_4U gpstime_nanoseconds_t;
/**
 * \brief GPS Time structure
 */
struct gpstime
{

    /**
     * GPS seconds
     */
    gpstime_seconds_t sec;
    /**
     * GPS nanoseconds.
     * 0 <= nan < 1 second.
     */
    gpstime_nanoseconds_t nan;
};

typedef struct gpstime gpstime_t;

/**
 * \brief Enumeration of error codes
 *
 * To aid in error handling, the C interface adopts from the errno
 * paradigm and has this enumerated type to describe numerically
 * the classification of the error that occurred.
 */
typedef enum errno_
{
    /**
     * \brief No error
     *
     * This enumerated type is used to represent that the call
     * completed successfully
     */
    FRAMEC_ERRNO_NO_ERROR
    /** \cond IGNORE */
    = 0
    /** \endcond */
    ,
    /**
     * \brief General error
     */
    FRAMEC_ERRNO_ERROR,
    /**
     * \brief Error accessing a data member of the channel
     */
    FRAMEC_ERRNO_FR_CHANNEL_ACCESSOR_ERROR,
    /**
     * \brief Error allocating the memory associated with the channel structure.
     */
    FRAMEC_ERRNO_FR_CHANNEL_ALLOC_ERROR,
    /**
     * \brief Error allocating the memory associated with the channel structure.
     */
    FRAMEC_ERRNO_FR_CHANNEL_COMPRESSION_ERROR,
    /**
     * \brief Error releasing the memory associated with the channel structure.
     */
    FRAMEC_ERRNO_FR_CHANNEL_FREE_ERROR,
    /**
     * \brief Error reading the channel structure from the frame file.
     */
    FRAMEC_ERRNO_FR_CHANNEL_READ_ERROR,
    /**
     * \brief Error accessing a data member of the detector structure.
     */
    FRAMEC_ERRNO_FR_DETECTOR_ACCESSOR_ERROR,
    /**
     * \brief Error allocating the memory associated with the detector
     * structure.
     */
    FRAMEC_ERRNO_FR_DETECTOR_ALLOC_ERROR,
    /**
     * \brief Error releasing the memory associated with the detector structure.
     */
    FRAMEC_ERRNO_FR_DETECTOR_FREE_ERROR,
    /**
     * \brief Error reading the detector structure from the frame file.
     */
    FRAMEC_ERRNO_FR_DETECTOR_READ_ERROR,
    /**
     * \brief Error writing the detector structure to the frame file.
     */
    FRAMEC_ERRNO_FR_DETECTOR_WRITE_ERROR,
    /**
     * \brief Error accessing a data member of the event structure.
     */
    FRAMEC_ERRNO_FR_EVENT_ACCESSOR_ERROR,
    /**
     * \brief Error allocating the memory associated with the event structure.
     */
    FRAMEC_ERRNO_FR_EVENT_ALLOC_ERROR,
    /**
     * \brief Error releasing the memory associated with the event structure.
     */
    FRAMEC_ERRNO_FR_EVENT_FREE_ERROR,
    /**
     * \brief Error reading the event structure from the frame file.
     */
    FRAMEC_ERRNO_FR_EVENT_READ_ERROR,
    /**
     * \brief Error writing the event structure to the frame file.
     */
    FRAMEC_ERRNO_FR_EVENT_WRITE_ERROR,
    /**
     * \brief Error allocating the memory associated with the history structure.
     */
    FRAMEC_ERRNO_FR_HISTORY_ALLOC_ERROR,
    /**
     * \brief Error releasing the memory associated with the FrHistory
     * structure.
     */
    FRAMEC_ERRNO_FR_HISTORY_FREE_ERROR,
    /**
     * \brief Error opening the frame file
     */
    FRAMEC_ERRNO_FRAME_OPEN_ERROR,
    /**
     * \brief Error closing the frame file
     */
    FRAMEC_ERRNO_FRAME_CLOSE_ERROR,
    /**
     * \brief Error in the stream indicating inconsistent checksum.
     */
    FRAMEC_ERRNO_FRAME_CHECKSUM_ERROR,
    /**
     * \brief Error accessing a data member of the frame
     */
    FRAMEC_ERRNO_FRAME_H_ACCESSOR_ERROR,
    /**
     * \brief Error obtaining the memory needed for the FrFrame structure.
     */
    FRAMEC_ERRNO_FRAME_H_ALLOC_ERROR,
    /**
     * \brief Error releasing the memory associated with the FrFrame structure.
     */
    FRAMEC_ERRNO_FRAME_H_FREE_ERROR,
    /**
     * \brief Error reading the FrFrame structure from the frame file.
     */
    FRAMEC_ERRNO_FRAME_H_READ_ERROR,
    /**
     * \brief Error writing the FrFrame structure to the frame file.
     */
    FRAMEC_ERRNO_FRAME_H_WRITE_ERROR,
    /**
     * \brief Error accessing a data member of the table of contents
     */
    FRAMEC_ERRNO_FR_TOC_ACCESSOR_ERROR,
    /**
     * \brief Error releasing the memory associated with the FrTOC structure.
     */
    FRAMEC_ERRNO_FR_TOC_FREE_ERROR,
    /**
     * \brief Error reading the FrTOC structure from the frame file.
     */
    FRAMEC_ERRNO_FR_TOC_READ_ERROR
} framec_errno_type;

/**
 * \brief Information concerning failure of a function
 */
typedef struct FrameCError_
{
    framec_errno_type s_errno;
    const char*       s_message;
} FrameCError;

void FrameCErrorInit( FrameCError** Handle );

/**
 * \brief Return the minor version number of the frame library.
 *
 * \return
 *     The minor version number of the frame software.
 *     This value is assiged by the developer of the frame library
 *     and is only meaningful when compared to other values for the
 *     same frame library.
 */
INT_2U FrameCLibraryMinorVersion( void );

gpstime_seconds_t FrameCGPSTimeNow( void );

/**
 * \brief Initialize the library
 */
void FrameCInitialize( void );

/**
 * \brief Cleanup the library
 */
void FrameCCleanup( void );

/** @} */
/* End Group */

#ifdef __cplusplus
} /* extern "C" */
#endif /* __cplusplus */

#endif /* FRAME_CPP_INTERFACE__FRAME_C_H */
