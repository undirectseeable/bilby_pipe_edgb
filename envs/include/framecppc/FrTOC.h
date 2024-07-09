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

#ifndef FRAME_CPP_INTERFACE__FR_TOC_H
#define FRAME_CPP_INTERFACE__FR_TOC_H

#include "ldastoolsal/ldas_types.h"

#include "framecppc/FrameC.h"
#include "framecppc/Stream.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Begin Group */
/**
 * \addtogroup CInterface
 * @{
 */

/** \name FrTOC
 * \anchor CInterfaceFrTOC
 */
/** @{ */ /* begin - FrChan */
/**
 * \brief Delta time as used in the fr_toc structure.
 */
typedef REAL_8               fr_toc_dt_element_t;
typedef fr_toc_dt_element_t* fr_toc_dt_t;
typedef const char*          fr_toc_detector_name_t;

/**
 * \brief Start time as used in the fr_toc structure.
 */
typedef gpstime_t    fr_toc_t0_t;
typedef fr_toc_t0_t* fr_toc_t0_array_t;

typedef INT_4U      fr_toc_adc_n_t;
typedef const char* fr_toc_adc_name_t;
typedef INT_4U      fr_toc_nframe_t;
typedef INT_4U      fr_toc_detector_n_t;
typedef INT_4U      fr_toc_proc_n_t;
typedef const char* fr_toc_proc_name_t;
typedef INT_4U      fr_toc_sim_n_t;
typedef const char* fr_toc_sim_name_t;

/** \brief Field specifiers for querying the table of contents. */
typedef enum fr_toc_fields_
{
    /** \brief Marker specifying the end of a TOC query */
    FR_TOC_FIELD_LAST,
    /** \brief Retrieve the start time of each frame in the stream
     *
     * The number of entries in this set is governed by NFRAME
     */
    /** \brief The number of adc channels in the stream
     */
    FR_TOC_FIELD_ADC_N,
    /** \brief The array of adc names in the stream
     */
    FR_TOC_FIELD_ADC_NAMES,
    /** \brief Retrieve the start time of each frame in the stream
     *
     * The number of entries in this set is governed by NFRAME
     */
    FR_TOC_FIELD_GTIME,
    /** \brief Retrieve the duration of each frame in the stream
     *
     * The number of entries in this set is governed by NFRAME
     */
    FR_TOC_FIELD_DT,
    /** \brief The number of detectors in the stream
     */
    FR_TOC_FIELD_DETECTOR_N,
    /** \brief The array of detectors in the stream
     */
    FR_TOC_FIELD_DETECTOR_NAMES,
    /** \brief The number of frames in the stream
     */
    FR_TOC_FIELD_NFRAME,
    /** \brief The number of proc channels in the stream
     */
    FR_TOC_FIELD_PROC_N,
    /** \brief The array of proc names in the stream
     */
    FR_TOC_FIELD_PROC_NAMES,
    /** \brief The number of sim channels in the stream
     */
    FR_TOC_FIELD_SIM_N,
    /** \brief The array of sim names in the stream
     */
    FR_TOC_FIELD_SIM_NAMES,
    /* Elements below here are logical */
    FR_TOC_FIELD_DT_NTH
} fr_toc_fields;

typedef struct fr_toc_t_ fr_toc_t;

/**
 * \brief Obtain the table of contensts.
 *
 * \param[out] Error
 * If an error occurs, this will contain the details of the error.
 * For full details on error processing, please refer to FrameCError.
 *
 * \param[in] Stream
 * The stream from which to read the table of contents.
 *
 * \return
 * Upon successful completion, a newly allocated fr_toc_t structure
 * is returned.
 * It is the responsibility of the user to call FrameCFrTOCFree to recycle
 * this resource.
 */
fr_toc_t* FrameCFrTOCRead( FrameCError** Error, fr_file_t* Stream );

/**
 * \brief Recyle the table of contents structure.
 *
 * \param[out] Error
 *     If an error occurs, this will contain the details of the error.
 *     For full details on error processing, please refer to FrameCError.
 *
 * \param[in] TOC
 *     The table of contents resouce to be recycled.
 */
void FrameCFrTOCFree( FrameCError** Error, fr_toc_t* TOC );

/**
 * \brief Retrieve vector information related to the Table of Contents
 *
 * \param[out] Error
 *     A place to report any errors occuring from this call.
 *
 * \param[in] TOC
 *     A TOC to query.
 *
 * \param[in] Option
 *     Field to query.
 *
 * \param[in] ...
 *     Parameters as dsctated by the Option.
 *
 */
void
FrameCFrTOCQuery( FrameCError** Error, const fr_toc_t* TOC, int Option, ... );

/** @} */ /* end - FrTOC group*/
/** @} */
/* End Group */
#ifdef __cplusplus
} /* extern "C" */
#endif /* __cplusplus */

#endif /* FRAME_CPP_INTERFACE__FR_TOC_H */
