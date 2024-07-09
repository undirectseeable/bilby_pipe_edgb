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

#ifndef FRAME_CPP_INTERFACE__FR_DETECTOR_H
#define FRAME_CPP_INTERFACE__FR_DETECTOR_H

#include "ldastoolsal/ldas_types.h"

#include "framecppc/FrameC.h"
#include "framecppc/Stream.h"

#define DETECTOR_PREFIX_LEN 2

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Begin Group */
/**
 * \addtogroup CInterface
 * @{
 */

/**
 * \brief Instrument name
 */
typedef const char* fr_detector_name_t;
/**
 * \brief Channel prefix for this detecor
 */
typedef struct
{
    char prefix[ 2 ];
} fr_detector_prefix_t;
/**
 * \brief latitude as used in the fr_detector structure.
 */
typedef REAL_8 fr_detector_latitude_t;
/**
 * \brief longitude as used in the fr_detector structure.
 */
typedef REAL_8 fr_detector_longitude_t;
/**
 * \brief elevation as used in the fr_detector structure.
 */
typedef REAL_4 fr_detector_elevation_t;
/**
 * \brief x axis azimuth as used in the fr_detector structure.
 */
typedef REAL_4 fr_detector_arm_x_azimuth_t;
/**
 * \brief y axis azimuth as used in the fr_detector structure.
 */
typedef REAL_4 fr_detector_arm_y_azimuth_t;
/**
 * \brief x axis altitude as used in the fr_detector structure.
 */
typedef REAL_4 fr_detector_arm_x_altitude_t;
/**
 * \brief y axis altitude as used in the fr_detector structure.
 */
typedef REAL_4 fr_detector_arm_y_altitude_t;
/**
 * \brief x axis midpoint as used in the fr_detector structure.
 */
typedef REAL_4 fr_detector_arm_x_midpoint_t;
/**
 * \brief y axis midpoint as used in the fr_detector structure.
 */
typedef REAL_4 fr_detector_arm_y_midpoint_t;
/**
 * \brief local seasonal time as used in the fr_detector structure.
 */
typedef INT_4S fr_detector_localtime_t;

/** \brief Field specifiers for querying the table of contents. */
typedef enum fr_detector_fields_
{
    /** \brief Marker specifying the end of a detector query */
    FR_DETECTOR_FIELD_LAST,
    /**
     * \brief Instrument name
     *
     * Instrument name as described by the latest frame specification.
     * (e.g., Virgo; GEO_600; TAMA_300; LHO2k; LLO_4k; CIT_40;
     * simulated pseudo data -model version etc.)
     */
    FR_DETECTOR_FIELD_NAME,
    /**
     * \brief Channel prefix for this detector
     *
     */
    FR_DETECTOR_FIELD_PREFIX,
    /**
     * \brief Detector vertex longitude
     *
     * Detector vertex longitude, geographical coordinates:
     * radians; Value > 0 => E of Greenwich
     */
    FR_DETECTOR_FIELD_LONGITUDE,
    /**
     * \brief Detector vertex latitude
     *
     * Detector vertex latitude, geographical coordinates:
     * radians; Value > 0 => N of Equator
     */
    FR_DETECTOR_FIELD_LATITUDE,
    /**
     * \brief Vertex elevation, meters, relative to WGS84 ellipsoid.
     *
     */
    FR_DETECTOR_FIELD_ELEVATION,
    /**
     * \brief Orientation of X arm
     *
     * Orientation of X arm, measured in raidans East of North.
     *
     */
    FR_DETECTOR_FIELD_ARM_X_AZIMUTH,
    /**
     * \brief Orientation of Y arm
     *
     * Orientation of Y arm, measured in raidans East of North.
     *
     */
    FR_DETECTOR_FIELD_ARM_Y_AZIMUTH,
    /**
     * \brief Altitude (pitch) angle of X arm.
     *
     * Altitude (pitch) angle of X arm, measured in radians above horizon
     * (local tangent to WGS84 ellipsoid)
     */
    FR_DETECTOR_FIELD_ARM_X_ALTITUDE,
    /**
     * \brief Altitude (pitch) angle of Y arm.
     *
     * Altitude (pitch) angle of Y arm, measured in radians above horizon
     * (local tangent to WGS84 ellipsoid)
     */
    FR_DETECTOR_FIELD_ARM_Y_ALTITUDE,
    /**
     * \brief Distance between the detector vertex and the middle of the X
     * cavity
     *
     * The distance is in units of meters.
     * The value should be zero for bars.
     */
    FR_DETECTOR_FIELD_ARM_X_MIDPOINT,
    /**
     * \brief Distance between the detector vertex and the middle of the Y
     * cavity
     *
     * The distance is in units of meters.
     * The value should be zero for bars.
     */
    FR_DETECTOR_FIELD_ARM_Y_MIDPOINT,
    /**
     * \brief Local seasonal time - UTC in seconds.
     *
     * If local time % 1800 != 0, then local time is undefined.
     */
    FR_DETECTOR_FIELD_LOCAL_TIME
} fr_detector_fields;

typedef struct fr_detector fr_detector_t;

/**
 * \brief Standard detectors
 */
typedef enum
{
    DETECTOR_LOCATION_H1,
    DETECTOR_LOCATION_H2,
    DETECTOR_LOCATION_L1,
    DETECTOR_LOCATION_V1
} std_detectors;

/**
 * \brief Allocate a new Detector structure.
 *
 * \param[out] Error
 * If an error occurs, this will contain the details of the error.
 * For full details on error processing, please refer to FrameCError.
 *
 * \param[in] name
 * Instrument name as described in Appendix D of the frame spec.
 *
 * \param[in] prefix
 * Channel prefix for this detector as described in Appendix D.
 *
 * \param[in] latitude
 * Detector vertex latitude, geographical coordinates.
 *
 * \param[in] longitude
 * Detector vertex longitude, geographical coordinates.
 *
 * \param[in] elevation
 * Vertex elevation, meters, relative to WGS84 ellipsoid.
 *
 * \param[in] azimuth_x
 * Orientations of X arm, measured in radians East of North.
 *
 * \param[in] azimuth_y
 * Orientations of Y arm, measured in radians East of North.
 *
 * \param[in] altitude_x
 * Altitude (pitch) angle of X arm, measured in radians.
 *
 * \param[in] altitude_y
 * Altitude (pitch) angle of Y arm, measured in radians.
 *
 * \param[in] midpoint_x
 * Distance between the detector vertex and middle of the X cavity (meters).
 *
 * \param[in] midpoint_y
 * Distance between the detector vertex and middle of the Y cavity (meters).
 *
 * \param[in] localtime
 * Local seasonal time - UTC in seconds.
 *
 * \return
 * Upon successful completion, a newly allocated fr_detector_t
 * is returned.
 * It is the responsibility of the user to call FrDetectorFree
 * to recycle this resource.
 */
fr_detector_t* FrameCFrDetectorAlloc( FrameCError** Error,
                                      const char* restrict name,
                                      const char* restrict         prefix,
                                      fr_detector_latitude_t       latitude,
                                      fr_detector_longitude_t      longitude,
                                      fr_detector_elevation_t      elevation,
                                      fr_detector_arm_x_azimuth_t  azimuth_x,
                                      fr_detector_arm_y_azimuth_t  azimuth_y,
                                      fr_detector_arm_x_altitude_t altitude_x,
                                      fr_detector_arm_y_altitude_t altitude_y,
                                      fr_detector_arm_x_midpoint_t midpoint_x,
                                      fr_detector_arm_y_midpoint_t midpoint_y,
                                      fr_detector_localtime_t      localtime );

/**
 * \brief Recyle the detector structure.
 *
 * \param[out] Error
 * If an error occurs, this will contain the details of the error.
 * For full details on error processing, please refer to FrameCError.
 *
 * \param[in] detector
 * The detector resouce to be recycled.
 */
void FrameCFrDetectorFree( FrameCError** Error, fr_detector_t* detector );

/**
 * \brief Retrieve vector information related to the Table of Contents
 *
 * \param[out] Error
 *     A place to report any errors occuring from this call.
 *
 * \param[in] Detector
 *     A FrDetector to query.
 *
 * \param[in] Option
 *     Field to query.
 *
 * \param[in] ...
 *     Parameters as dictated by the Option.
 *
 */
void FrameCFrDetectorQuery( FrameCError**        Error,
                            const fr_detector_t* Detector,
                            int                  Option,
                            ... );

/**
 * \brief Read a new Detector structure.
 *
 * \param[out] Error
 * If an error occurs, this will contain the details of the error.
 * For full details on error processing, please refer to FrameCError.
 *
 * \param[in] Stream
 * The stream from which to read the detector.
 *
 * \param[in] Name
 * Instrument name.
 *
 * \return
 * Upon successful completion, a newly allocated fr_detector_t
 * is returned.
 * It is the responsibility of the user to call FrDetectorFree
 * to recycle this resource.
 */
fr_detector_t* FrameCFrDetectorRead( FrameCError** Error,
                                     fr_file_t* restrict Stream,
                                     const char* restrict Name );

/**
 * \brief Write a Detector structure to the stream.
 *
 * \param[out] Error
 * If an error occurs, this will contain the details of the error.
 * For full details on error processing, please refer to FrameCError.
 *
 * \param[in] Stream
 * The stream on which to write the detector.
 *
 * \param[in] Detector
 * The detector to write to the stream.
 *
 * \return
 * A value of 1 is returned on success;
 * zero otherwise.
 */
int FrameCFrDetectorWrite( FrameCError** Error,
                           fr_file_t* restrict  Stream,
                           const fr_detector_t* restrict Detector );

/**
 * \brief Retrieve information about some standard detectors.
 *
 * \param[out] Error
 * If an error occurs, this will contain the details of the error.
 * For full details on error processing, please refer to FrameCError.
 *
 * \param[in] Type
 * This is the interferometer's designation.
 *
 * \param[in] Time
 * This is the time for which to check the designation.
 * This will rarely change the results, but in the situations where
 * it does, it is critical.
 * The time should be the start time of the frame.
 */
fr_detector_t* FrameCGetDetector( FrameCError**    Error,
                                  std_detectors    Type,
                                  const gpstime_t* restrict Time );

/** @} */
/* End Group */
#ifdef __cplusplus
} /* extern "C" */
#endif /* __cplusplus */

#endif /* FRAME_CPP_INTERFACE__FR_DETECTOR_H */
