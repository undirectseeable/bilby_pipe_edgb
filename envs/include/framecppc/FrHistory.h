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

#ifndef FRAME_CPP_INTERFACE__FR_HISTORY_H
#define FRAME_CPP_INTERFACE__FR_HISTORY_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Begin Group */
/**
 * \addtogroup CInterface
 * @{
 */

typedef struct fr_history fr_history_t;
typedef INT_4U            fr_history_time_t;

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
 *
 * \param[in] Name
 *     Name of the history record
 * \param[in] Time
 *     Time of post-processing
 *     (GPS seconds since GPS standard epoch)
 * \param[in] Comment
 *     Program name and relevant comments needed to define
 *     post-processing
 *
 * \return
 *     Pointer to newly allocated frame_h_t.
 *     If a failure happens, a NULL pointer will be returned.
 */
fr_history_t* FrameCFrHistoryAlloc( FrameCError**     Error,
                                    const char*       Name,
                                    fr_history_time_t Time,
                                    const char*       Comment );

int FrameCFrHistoryFree( FrameCError** Error, fr_history_t* History );

/** @} */
/* End Group */
#ifdef __cplusplus
} /* extern "C" */
#endif /* __cplusplus */

#endif /* FRAME_CPP_INTERFACE__FR_HISTORY_H */
