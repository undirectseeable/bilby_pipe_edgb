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

#ifndef FRAME_CPP_INTERFACE__FR_EVENT_H
#define FRAME_CPP_INTERFACE__FR_EVENT_H

#include "framecpp/FrEvent.hh"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#undef FR_EVENT_NAME_TYPE
#define FR_EVENT_NAME_TYPE char*

#undef FR_EVENT_COMMENT_TYPE
#define FR_EVENT_COMMENT_TYPE char*

#undef FR_EVENT_INPUTS_TYPE
#define FR_EVENT_INPUTS_TYPE char*

#undef FR_EVENT_STATISTICS_TYPE
#define FR_EVENT_STATISTICS_TYPE char*

#undef FR_EVENT_PARAM_NAME_TYPE
#define FR_EVENT_PARAM_NAME_TYPE char*

/* Begin Group */
/**
 * \addtogroup CInterface
 * @{
 */

typedef struct fr_event            fr_event_t;
typedef FR_EVENT_NAME_TYPE         fr_event_name_t;
typedef FR_EVENT_COMMENT_TYPE      fr_event_comment_t;
typedef FR_EVENT_INPUTS_TYPE       fr_event_inputs_t;
typedef gpstime_t                  fr_event_gtime_t;
typedef FR_EVENT_TIME_BEFORE_TYPE  fr_event_time_before_t;
typedef FR_EVENT_TIME_AFTER_TYPE   fr_event_time_after_t;
typedef FR_EVENT_EVENT_STATUS_TYPE fr_event_event_status_t;
typedef FR_EVENT_AMPLITUDE_TYPE    fr_event_amplitude_t;
typedef FR_EVENT_PROBABILITY_TYPE  fr_event_probability_t;
typedef FR_EVENT_STATISTICS_TYPE   fr_event_statistics_t;
typedef FR_EVENT_N_PARAM_TYPE      fr_event_n_param_t;
typedef FR_EVENT_PARAM_VALUE_TYPE  fr_event_parameter_t;
typedef FR_EVENT_PARAM_NAME_TYPE   fr_event_parameter_name_t;

typedef struct
{
    fr_event_parameter_t      s_parameter;
    fr_event_parameter_name_t s_parameter_name;
} fr_event_parameters_t;

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
 *     Name of event.
 * \param[in] Comment
 *     Descriptor of event.
 * \param[in] Inputs
 *     Input channels and filter parameters to event process.
 * \param[in] GTime
 *     GPS time corresponding to reference value of event.
 * \param[in] TimeBefore
 *     Signal duration before time.
 * \param[in] TimeAfter
 *     Signal duration after time.
 * \param[in] EventStatus
 *     Defined by event search algorithm.
 * \param[in] Amplitude
 *     Continuous output amplitude returned by event.
 * \param[in] Probability
 *     Likelihood estimate of event.
 * \param[in] Statistics
 *     Statistical description of event.
 * \param[in] NParam
 *     Number of additional event parameters.
 * \param[in] Parameters
 *     Array of additional event parameters.
 *
 * \return
 *     Pointer to newly allocated fr_event_t.
 *     If a failure happens, a NULL pointer will be returned.
 *
 */
fr_event_t* FrameCFrEventAlloc( FrameCError**                 Error,
                                const fr_event_name_t         Name,
                                const fr_event_comment_t      Comment,
                                const fr_event_inputs_t       Inputs,
                                const fr_event_gtime_t        GTime,
                                const fr_event_time_before_t  TimeBefore,
                                const fr_event_time_after_t   TimeAfter,
                                const fr_event_event_status_t EventStatus,
                                const fr_event_amplitude_t    Amplitude,
                                const fr_event_probability_t  Probability,
                                const fr_event_statistics_t   Statistics,
                                const fr_event_n_param_t      NParam,
                                const fr_event_parameters_t*  Parameters );

int FrameCFrEventFree( FrameCError** Error, fr_event_t* Event );

/** @} */
/* End Group */
#ifdef __cplusplus
} /* extern "C" */
#endif /* __cplusplus */

#endif /* FRAME_CPP_INTERFACE__FR_EVENT_H */
