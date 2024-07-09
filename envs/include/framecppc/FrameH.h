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

#ifndef FRAME_CPP_INTERFACE__FRAME_H_H
#define FRAME_CPP_INTERFACE__FRAME_H_H

#include "ldastoolsal/ldas_types.h"

#include "framecppc/FrameC.h"
#include "framecppc/Stream.h"
#include "framecppc/FrChan.h"
#include "framecppc/FrDetector.h"
#include "framecppc/FrEvent.h"
#include "framecppc/FrHistory.h"
#include "framecppc/FrVect.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Begin Group */
/**
 * \addtogroup CInterface
 * @{
 */

typedef const char* frame_h_name_t;
typedef INT_4S      frame_h_run_t;
typedef INT_4U      frame_h_frame_t;
typedef INT_4U      frame_h_data_quality_t;
typedef gpstime_t   frame_h_gtime_t;
typedef INT_2U      frame_h_uleaps_t;
typedef REAL_8      frame_h_dt_t;

typedef INT_2U frame_h_offset_t;

typedef struct frame_h frame_h_t;

/** \brief Field specifiers for querying the table of contents. */
typedef enum frame_h_fields_
{
    /** \brief Marker specifying the end of a frame query */
    FRAME_H_FIELD_LAST,
    /** \brief Desciption
     *
     *  Name of the project or other experiment description
     * (e.g., GEO; LIGO; VIRGO; TAMA; ... )
     */
    FRAME_H_FIELD_NAME,
    /** \brief Run number
     *
     * Run number ( number < 0 reserved for simulated data);
     * monotonic for experimental runs.
     */
    FRAME_H_FIELD_RUN,
    /** \brief Frame number
     *
     * Frame number, monotonically increasing until end of run,
     * re-startarting from 0 with each new run.
     */
    FRAME_H_FIELD_FRAME,
    /** \brief Data quality flag
     *
     * A logical 32-bit word to denote top level quality of data.
     * Lowest order bits are reserved in pairs for various GW detectors.
     */
    FRAME_H_FIELD_DATA_QUALITY,
    /** \brief Frame start time
     *
     * GPS start time of the frame.
     */
    FRAME_H_FIELD_GTIME,
    /** \brief Leap seconds between GPS/TAI and UTC
     *
     * The integer number of leap seconds between GPS/TAI
     * and UTC in the epoch when the frame is written:
     * ULeapS = Int[TAI - UTC].
     */
    FRAME_H_FIELD_ULEAPS,
    /** \brief Frame length in seconds */
    FRAME_H_FIELD_DT
} frame_h_fields;

/**
 * \brief Allocate a fr_frame structure.
 *
 * \note
 * This method should be used as there may be additional data allocated
 * to properly interface to the C++ layer.
 *
 * \param[out] Error
 *     If an error occurs, Error will be non-NULL and a detailed error
 *     message will be available.
 * \param[in] Name
 *     Name of project.
 * \param[in] Start
 *     GPS start time of frame.
 * \param[in] Dt
 *     Duration of frame.
 * \param[in] FrameNumber
 *     Frame number since start of run.
 *
 * \return
 *     Pointer to newly allocated frame_h_t.
 *     If a failure happens, a NULL pointer will be returned.
 */
frame_h_t* FrameCFrameHAlloc( FrameCError**   Error,
                              const char*     Name,
                              frame_h_gtime_t Start,
                              frame_h_dt_t    Dt,
                              frame_h_frame_t FrameNumber );

/**
 * \brief Add a channel to the frame.
 *
 * \param[out] Error
 *     If an error occurs, Error will be non-NULL and a detailed error
 *     message will be available.
 * \param[in] Frame
 *     The frame to which the channel data is to be added.
 * \param[in] Channel
 *     The channel to be added.
 */
int FrameCFrameHFrChanAdd( FrameCError** Error,
                           frame_h_t*    Frame,
                           fr_chan_t*    Channel );

/**
 * \brief Add a detector to the frame.
 *
 * \param[out] Error
 *     If an error occurs, Error will be non-NULL and a detailed error
 *     message will be available.
 * \param[in] Frame
 *     The frame to which the detector data is to be added.
 * \param[in] Detector
 *     The detector to be added.
 */
int FrameCFrameHFrDetectorAdd( FrameCError**  Error,
                               frame_h_t*     Frame,
                               fr_detector_t* Detector );

int FrameCFrameHFree( FrameCError** Error, frame_h_t* frame );

/**
 * \brief Add an event to the frame.
 *
 * \param[out] Error
 *     If an error occurs, Error will be non-NULL and a detailed error
 *     message will be available.
 * \param[in] Frame
 *     The frame to which the history data is to be added.
 * \param[in] Event
 *     The event to be added.
 */
int FrameCFrameHFrEventAdd( FrameCError** Error,
                            frame_h_t*    Frame,
                            fr_event_t*   Event );

/**
 * \brief Add history to the frame.
 *
 * \param[out] Error
 *     If an error occurs, Error will be non-NULL and a detailed error
 *     message will be available.
 * \param[in] Frame
 *     The frame to which the history data is to be added.
 * \param[in] History
 *     The history to be added.
 */
int FrameCFrameHFrHistoryAdd( FrameCError** Error,
                              frame_h_t*    Frame,
                              fr_history_t* History );

/**
 * \brief Read a FrameH structure from the file
 *
 * \param[out] Error
 *     If an error occurs, Error will be non-NULL and a detailed error
 *     message will be available.
 * \param[in] Stream
 *     The stream from which to read the FrameH.
 * \param[in] Pos
 *     The offset in the stream from which to read the channel.
 */
frame_h_t* FrameCFrameHRead( FrameCError** Error,
                             fr_file_t* restrict Stream,
                             frame_h_offset_t    Pos );

/**
 * \brief Read a FrameH structure from the file
 *
 * \param[out] Error
 *     If an error occurs, Error will be non-NULL and a detailed error
 *     message will be available.
 * \param[in] Stream
 *     The stream from which to read the FrameH.
 *
 * \note
 *     This function has the potential to consume a large amount
 *     of system resources as the full frame is pulled into
 *     memory.
 */
frame_h_t* FrameCFrameHReadNext( FrameCError** Error,
                                 fr_file_t* restrict Stream );

/**
 * \brief Retrieve vector information related to the Table of Contents
 *
 * \param[out] Error
 *     A place to report any errors occuring from this call.
 *
 * \param[in] Frame
 *     A FrameH to query.
 *
 * \param[in] Option
 *     Field to query.
 *
 * \param[in] ...
 *     Parameters as dictated by the Option.
 *
 */
void FrameCFrameHQuery( FrameCError**    Error,
                        const frame_h_t* Frame,
                        int              Option,
                        ... );

/**
 * \brief Set values for the FrameH structure
 *
 * \param[out] Error
 *     A place to report any errors occuring from this call.
 *
 * \param[in] Frame
 *
 *
 * \param[in] Option
 *     Field to set.
 *
 * \param[in] ...
 *     Parameters as dictated by the Option.
 *
 */
void
FrameCFrameHSet( FrameCError** Error, const frame_h_t* Frame, int Option, ... );

/**
 * \brief Write the frame to the stream
 *
 * \param[out] Error
 *     If an error occurs, Error will be non-NULL and a detailed error
 *     message will be available.
 * \param[in,out] stream
 *     The output stream where the object is to be written.
 * \param[in] frame
 *     The frame to be written to the stream
 */
int FrameCFrameHWrite( FrameCError** Error,
                       fr_file_t* restrict stream,
                       frame_h_t* restrict frame );

/**
 * \brief Write the frame to the stream
 *
 * \param[out] Error
 *     If an error occurs, Error will be non-NULL and a detailed error
 *     message will be available.
 * \param[in,out] stream
 *     The output stream where the object is to be written.
 * \param[in] frame
 *     The frame to be written to the stream
 * \param[in] compression
 *     The method for compression
 * \param[in] level
 *     Level of compression for methods that support multipler
 *     levels of compression.
 */
int FrameCFrameHWriteCompressed( FrameCError** Error,
                                 fr_file_t* restrict stream,
                                 frame_h_t* restrict           frame,
                                 fr_vect_compression_schemes_t compression,
                                 fr_vect_compression_level_t   level );

/** @} */
/* End Group */
#ifdef __cplusplus
} /* extern "C" */
#endif /* __cplusplus */

#endif /* FRAME_CPP_INTERFACE__FRAME_H_H */
