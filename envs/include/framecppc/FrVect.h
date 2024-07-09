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

#ifndef FRAME_CPP_CINTERFACE__FR_VECT_H
#define FRAME_CPP_CINTERFACE__FR_VECT_H

#include "ldastoolsal/ldas_types.h"

typedef const char* fr_vect_name_t;
typedef INT_2U      fr_vect_compress_t;
typedef INT_2U      fr_vect_type_t;
typedef INT_8U      fr_vect_ndata_t;
typedef INT_8U      fr_vect_nbytes_t;
typedef CHAR*       fr_vect_data_t;
typedef INT_4U      fr_vect_ndim_t;
typedef INT_8U      fr_vect_nx_t;
typedef REAL_8      fr_vect_dx_t;
typedef REAL_8      fr_vect_startx_t;
typedef const char* fr_vect_unit_x_t;
typedef const char* fr_vect_unit_y_t;

typedef enum fr_vect_fileds_
{
    FR_VECT_FIELD_NAME,
    FR_VECT_FIELD_COMPRESS,
    FR_VECT_FIELD_TYPE,
    FR_VECT_FIELD_NDATA,
    FR_VECT_FIELD_NBYTES,
    FR_VECT_FIELD_DATA,
    FR_VECT_FIELD_NDIM,
    FR_VECT_FIELD_NX,
    FR_VECT_FIELD_DX,
    FR_VECT_FIELD_START_X,
    FR_VECT_FIELD_UNIT_X,
    FR_VECT_FIELD_UNIT_Y,
    FR_VECT_FIELD_LAST
} fr_vect_fields;

typedef enum fr_vect_compression_schemes
{
    FR_VECT_COMPRESS_UNKNOWN,
    FR_VECT_COMPRESS_RAW,
    FR_VECT_COMPRESS_GZIP,
    FR_VECT_COMPRESS_DIFF_GZIP,
    FR_VECT_COMPRESS_ZERO_SUPPRESS_WORD_2,
    FR_VECT_COMPRESS_ZERO_SUPPRESS_WORD_4,
    FR_VECT_COMPRESS_ZERO_SUPPRESS_WORD_8
} fr_vect_compression_schemes_t;

typedef enum fr_vect_data_types
{
    FR_VECT_C,
    FR_VECT_2S,
    FR_VECT_8R,
    FR_VECT_4R,
    FR_VECT_4S,
    FR_VECT_8S,
    FR_VECT_8C,
    FR_VECT_16C,
    FR_VECT_STRING,
    FR_VECT_2U,
    FR_VECT_4U,
    FR_VECT_8U,
    FR_VECT_1U
} fr_vect_data_types_t;

const fr_vect_compress_t FR_VECT_COMPRESS_LITTLEENDIAN = 0x8000;

typedef struct fr_vect fr_vect_t;

typedef int fr_vect_compression_level_t;

#endif /* FRAME_CPP_INTERFACE__FR_VECT_H */
