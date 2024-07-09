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

#ifndef FRAME_CPP_CINTERFACE__FR_CHAN_H
#define FRAME_CPP_CINTERFACE__FR_CHAN_H

#include "ldastoolsal/ldas_types.h"

#include "framecpp/FrAdcData.hh"
#include "framecpp/FrProcData.hh"

#include "framecppc/FrameC.h"
#include "framecppc/Stream.h"
#include "framecppc/FrVect.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

typedef const char*                     fr_chan_comment_t;
typedef FR_ADC_DATA_CHANNEL_GROUP_TYPE  fr_chan_channel_group_t;
typedef FR_ADC_DATA_CHANNEL_NUMBER_TYPE fr_chan_channel_number_t;
typedef FR_ADC_DATA_DATAVALID_TYPE      fr_chan_data_valid_t;
typedef const char*                     fr_chan_name_t;
typedef FR_ADC_DATA_TIMEOFFSET_TYPE     fr_chan_offset_t;
typedef FR_ADC_DATA_SAMPLERATE_TYPE     fr_chan_sample_rate_t;
typedef FR_ADC_DATA_TIMEOFFSET_TYPE     fr_chan_time_offset_t;
typedef FR_ADC_DATA_N_BITS_TYPE         fr_chan_n_bits_t;
typedef FR_PROC_DATA_T_RANGE_TYPE       fr_chan_t_range_t;

typedef enum fr_chan_fields_
{
    FR_CHAN_FIELD_CHANNEL_GROUP,
    FR_CHAN_FIELD_CHANNEL_NUMBER,
    FR_CHAN_FIELD_COMMENT,
    FR_CHAN_FIELD_DATA_VALID,
    FR_CHAN_FIELD_NAME,
    FR_CHAN_FIELD_N_BITS,
    FR_CHAN_FIELD_SAMPLE_RATE,
    FR_CHAN_FIELD_TIME_OFFSET,
    FR_CHAN_FIELD_T_RANGE,
    FR_CHAN_FIELD_LAST
} fr_chan_fields;

/* Begin Group */
/**
 * \addtogroup CInterface
 * @{
 */

/** \name FrChan
 * \anchor CInterfaceFrChan
 */
/** @{ */ /* begin - FrChan */
/**
 * \brief Enumerated type of channel
 *
 * A channel provides a generic interface to several types of data
 * stream described inside the frame specification.
 * This enumerated type specifies the actual data type stream.
 */
typedef enum fr_chan_type
{
    /**
     * \brief Descriptor for FrAdc channel
     */
    FR_ADC_CHAN_TYPE,
    /**
     * \brief Descriptor for FrEvent channel
     */
    FR_EVENT_CHAN_TYPE,
    /**
     * \brief Descriptor for FrProc channel
     */
    FR_PROC_CHAN_TYPE,
    /**
     * \brief Descriptor for FrSimData channel
     */
    FR_SIM_CHAN_TYPE,
    /**
     * \brief Descriptor for FrSimEventData channel
     */
    FR_SIM_EVENT_CHAN_TYPE,
    /**
     * \brief Descriptor for Unknown channel
     */
    UNKNOWN_CHAN_TYPE
} fr_chan_type_t;

/** \brief Types of FrProcData */
typedef enum fr_proc_type
{
    /**
     * \brief Unknown/user defined
     */
    FR_PROC_TYPE_UNKNOWN
    /** \cond IGNORE */
    = 0
    /** \endcond */
    ,
    /**
     * \brief Time Series
     */
    FR_PROC_TYPE_TIME_SERIES
    /** \cond IGNORE */
    = 1
    /** \endcond */
    ,
    /**
     * \brief Frequency Series
     */
    FR_PROC_TYPE_FREQUENCY_SERIES
    /** \cond IGNORE */
    = 2
    /** \endcond */
    ,
    /**
     * \brief Other 1D Series data
     */
    FR_PROC_TYPE_OTHER_1D_SERIES
    /** \cond IGNORE */
    = 3
    /** \endcond */
    ,
    /**
     * \brief Time-Frequency
     */
    FR_PROC_TYPE_TIME_FREQUENCY
    /** \cond IGNORE */
    = 4
    /** \endcond */
    ,
    /**
     * \brief Wavelets
     */
    FR_PROC_TYPE_WAVELET
    /** \cond IGNORE */
    = 5
    /** \endcond */
    ,
    /**
     * \brief Multi-dimensional
     */
    Fr_PROC_TYPE_MULTI_DIMENSIONAL
    /** \cond IGNORE */
    = 6
    /** \endcond */
} fr_proc_type_t;

/** \brief Sub types of FrProcData */
typedef enum fr_proc_sub_type
{
    /**
     * \brief Unknown/user defined
     */
    FR_PROC_SUB_TYPE_UNKNOWN
    /** \cond IGNORE */
    = 0
    /** \endcond */
    ,
    /**
     * \brief DFT
     */
    FR_PROC_SUB_TYPE_DFT
    /** \cond IGNORE */
    = 1
    /** \endcond */
    ,
    /**
     * \brief Amplitude Spectral Density
     */
    FR_PROC_SUB_TYPE_AMPLITUDE_SPECTRAL_DENSITY
    /** \cond IGNORE */
    = 2
    /** \endcond */
    ,
    /**
     * \brief Power spectral density
     */
    FR_PROC_SUB_TYPE_POWER_SPECTRAL_DENSITY
    /** \cond IGNORE */
    = 3
    /** \endcond */
    ,
    /**
     * \brief Cross spectral density
     */
    FR_PROC_SUB_TYPE_CROSS_SPECTRAL_DENSITY
    /** \cond IGNORE */
    = 4
    /** \endcond */
    ,
    /**
     * \brief Coherence
     */
    FR_PROC_SUB_TYPE_COHERENCE
    /** \cond IGNORE */
    = 5
    /** \endcond */
    ,
    /**
     * \brief Transfer function
     */
    FR_PROC_SUB_TYPE_TRANSFER_FUNCTION
    /** \cond IGNORE */
    = 6
    /** \endcond */
} fr_proc_sub_type_t;

/**
 * \brief Description of an FrAdc structure
 */
struct fr_adc_chan;
/**
 * \brief Description of an FrProc structure
 */
struct fr_proc_chan;
/**
 * \brief Description of an FrSimData structure
 */
struct fr_sim_chan;

/**
 * \brief Type aliasing for FrAdc channel
 */
typedef struct fr_adc_chan fr_adc_chan_t;
/**
 * \brief Type aliasing for FrProc channel
 */
typedef struct fr_proc_chan fr_proc_chan_t;
/**
 * \brief Type aliasing for FrSimData channel
 */
typedef struct fr_sim_chan fr_sim_chan_t;

/**
 * \brief Type aliasing for fr_chan structure
 */
typedef struct fr_chan fr_chan_t;

/**
 * \brief Alloc an fr_chan_t
 *
 * \param[out] Error
 *      If an error occurs, this will contain the details of the error.
 *      For full details on error processing, please refer to FrameCError.
 *
 * \param[in] Name
 *      The name for the channel.
 *
 * \param[in] Type
 *      The fr_chan_type to be created.
 *      All except for FR_PROC_CHAN_TYPE can be allocated.
 *      Please refer to FrProcChanalloc() if a channel of type
 *      FR_PROC_CHAN_TYPE needs to be allocated.
 *
 * \param[in] DataType
 *     Specifier for the type of data to be stored
 *     in the vector.
 *
 * \param[in] NData
 *     The number of data elements the vector
 *     needs to have.
 *
 * \return
 *     Pointer to newly allocated fr_chan_t.
 *     If a failure happens, a NULL pointer will be returned.
 */
fr_chan_t* FrameCFrChanAlloc( FrameCError**        Error,
                              const char*          Name,
                              fr_chan_type_t       Type,
                              fr_vect_data_types_t DataType,
                              fr_vect_ndata_t      NData );

/**
 * \brief Alloc an fr_chan_t
 *
 * \param[out] Error
 * If an error occurs, this will contain the details of the error.
 * For full details on error processing, please refer to FrameCError.
 *
 * \param[in] Name
 *      The name for the channel.
 *
 * \param[in] Type
 * The fr_proc_type to be created.
 *
 * \param[in] SubType
 * The fr_proc_sub_type to be created.
 *
 * \param[in] DataType
 *     Specifier for the type of data to be stored
 *     in the vector.
 *
 * \param[in] NData
 *     The number of data elements the vector
 *     needs to have.
 *
 * \return
 *     Pointer to newly allocated fr_chan_t.
 *     If a failure happens, a NULL pointer will be returned.
 */
fr_chan_t* FrameCFrProcChanAlloc( FrameCError**        Error,
                                  const char*          Name,
                                  fr_proc_type_t       Type,
                                  fr_proc_sub_type_t   SubType,
                                  fr_vect_data_types_t DataType,
                                  fr_vect_ndata_t      NData );

/**
 * \brief Alloc an fr_chan_t
 *
 * \param[out] Error
 * If an error occurs, this will contain the details of the error.
 * For full details on error processing, please refer to FrameCError.
 *
 * \param[in] Name
 *     The name for the channel.
 *
 * \param[in] MimeTypeName
 *     The ASCII representation of the mime type
 *
 * \param[in] NData
 *     The number of data elements the vector
 *     needs to have.
 *
 * \param[in] MimeData
 *     The mime stream.
 *
 * \return
 *     Pointer to newly allocated fr_chan_t.
 *     If a failure happens, a NULL pointer will be returned.
 */
fr_chan_t* FrameCFrProcMimeChanAlloc( FrameCError**   Error,
                                      const char*     Name,
                                      const char*     MimeTypeName,
                                      fr_vect_ndata_t NData,
                                      fr_vect_data_t  MimeData );

/**
 * \brief Recyle the fr_chan_t structure.
 *
 * \param[out] Error
 * If an error occurs, this will contain the details of the error.
 * For full details on error processing, please refer to FrameCError.
 *
 * \param[in] Channel
 * The channel resouce to be recycled.
 */
void FrameCFrChanFree( FrameCError** Error, fr_chan_t* Channel );

/**
 * \brief Retrieve information related to the Channel
 *
 * \param[out] Error
 *     A place to report any errors occuring from this call.
 *
 * \param[in] Channel
 *     A channel to query.
 *
 * \param[in] Option
 *     Field to query.
 *
 * \param[in] ...
 *     Parameters as dictated by the Option.
 *
 */
void FrameCFrChanQuery( FrameCError**    Error,
                        const fr_chan_t* Channel,
                        int              Option,
                        ... );

/**
 * \brief Read a channel from the stream.
 *
 * \param[out] Error
 * If an error occurs, this will contain the details of the error.
 * For full details on error processing, please refer to FrameCError.
 *
 * \param[in] Stream
 * The stream from which to read the table of contents.
 *
 * \param[in] Name
 * The name of the channel to be read.
 *
 * \param[in] Pos
 * The offset in the stream from which to read the channel.
 *
 * \return
 * Upon successful completion, a newly allocated fr_chan_t structure
 * is returned.
 * It is the responsibility of the user to call FrameCFrChanFree to recycle
 * this resource.
 */
fr_chan_t* FrameCFrChanRead( FrameCError** Error,
                             fr_file_t* restrict Stream,
                             fr_chan_name_t restrict Name,
                             fr_chan_offset_t        Pos );

/**
 * \brief Establish information about the Channel
 *
 * \param[out] Error
 *     A place to report any errors occuring from this call.
 *
 * \param[in] Channel
 *     A channel to modify.
 *
 * \param[in] Option
 *     Field to modify.
 *
 * \param[in] ...
 *     Parameters as dictated by the Option.
 *
 */
void FrameCFrChanSet( FrameCError**    Error,
                      const fr_chan_t* Channel,
                      int              Option,
                      ... );

/**
 * \brief Allocate new space for an FrVect.
 *
 * \param[out] Error
 *     A place to report any errors occuring from this call.
 *
 * \param[in] Channel
 *     The channel containing the data vector to compress.
 *
 * \param[in] DataType
 *     Specifier for the type of data to be stored
 *     in the vector.
 *
 * \param[in] NData
 *     The number of data elements the vector
 *     needs to have.
 *
 */
void FrameCFrChanVectorAlloc( FrameCError**        Error,
                              fr_chan_t*           Channel,
                              fr_vect_data_types_t DataType,
                              fr_vect_ndata_t      NData );
/**
 * \brief Expand the data located in the data vector.
 *
 * \param[out] Error
 *     A place to report any errors occuring from this call.
 *
 * \param[in] Channel
 *     The channel containing the data vector to compress.
 * \param[in] Scheme
 *     Method to use to compress the data.
 */
void FrameCFrChanVectorCompress( FrameCError**                 Error,
                                 fr_chan_t*                    Channel,
                                 fr_vect_compression_schemes_t Scheme );
/**
 * \brief Expand the data located in the data vector.
 *
 * \param[out] Error
 *     A place to report any errors occuring from this call.
 *
 * \param[in] Channel
 *     The channel containing the data vector to expand.
 */
void FrameCFrChanVectorExpand( FrameCError** Error, fr_chan_t* Channel );
/**
 * \brief Retrieve vector information related to the Channel
 *
 * \param[out] Error
 *     A place to report any errors occuring from this call.
 *
 * \param[in] Channel
 *     A channel to query.
 *
 * \param[in] Option
 *     Field to query.
 *
 * \param[in] ...
 *     Parameters as dictated by the Option.
 *
 */
void FrameCFrChanVectorQuery( FrameCError**    Error,
                              const fr_chan_t* Channel,
                              int              Option,
                              ... );

/**
 * \brief Set vector information related to the Channel
 *
 * \param[out] Error
 *     A place to report any errors occuring from this call.
 *
 * \param[in] Channel
 *     A channel to modify.
 *
 * \param[in] Option
 *     Field to set.
 *
 * \param[in] ...
 *     Parameters as dictated by the Option.
 *
 */
void FrameCFrChanVectorSet( FrameCError** Error,
                            fr_chan_t*    Channel,
                            int           Option,
                            ... );

/** @} */ /* end - FrChan group*/
/** @} */
/* End Group */

#ifdef __cplusplus
} /* extern "C" */
#endif /* __cplusplus */

#endif /* FRAME_CPP_INTERFACE__FR_CHAN_H */
