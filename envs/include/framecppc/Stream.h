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

/*
 */
#ifndef FRAMECPP__FRAME_C_STREAM_H
#define FRAMECPP__FRAME_C_STREAM_H

#include "FrameC.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

struct fr_file;
typedef struct fr_file fr_file_t;

typedef enum
{
    FRAMEC_FILE_MODE_UNSET,
    FRAMEC_FILE_MODE_INPUT,
    FRAMEC_FILE_MODE_OUTPUT
} fr_file_mode_t;

/**
 * \brief Open a stream
 *
 * \param[out] Error
 * If an error occurs, this will contain the details of the error.
 * For full details on error processing, please refer to FrameCError.
 *
 * \param[in] Filename
 * Name of the stream to open.
 *
 * \param[in] Mode
 * Specifies if the file should be open for input or output.
 *
 * \return
 * Upon successfully opening the stream, a non NULL pointer is returned,
 * NULL otherwise.
 */
fr_file_t* FrameCFileOpen( FrameCError**        Error,
                           const char*          Filename,
                           const fr_file_mode_t Mode );

/**
 * \brief Close an open stream
 *
 * \param[out] Error
 * If an error occurs, this will contain the details of the error.
 * For full details on error processing, please refer to FrameCError.
 *
 * \param[in] Stream
 * The stream to close.
 *
 * \return
 * Upon successfully closing the stream a value of true is returned,
 * false otherwise.
 */
int FrameCFileClose( FrameCError** Error, fr_file_t* Stream );

/**
 * \brief Recycle the file structure.
 *
 * \param[out] Error
 * If an error occurs, this will contain the details of the error.
 * For full details on error processing, please refer to FrameCError.
 *
 * \param[in] Stream
 * The stream whos resources will be released.
 *
 * \return
 * The value 1 is returned on success, 0 otherwise.
 */
int FrameCFileFree( FrameCError** Error, fr_file_t* Stream );

/**
 * \brief Obtains the name of the frame library id of the stream
 *
 * \param[out] Error
 * If an error occurs, this will contain the details of the error.
 * For full details on error processing, please refer to FrameCError.
 *
 * \param[in] Stream
 * The stream from which to read the table of contents.
 *
 * \return
 * The enumerated number representing the frame library of the stream.
 */
int FrameCFrameLibrary( FrameCError** Error, fr_file_t* Stream );

/**
 * \brief Obtains the name of the frame library of the stream
 *
 * \param[out] Error
 * If an error occurs, this will contain the details of the error.
 * For full details on error processing, please refer to FrameCError.
 *
 * \param[in] Stream
 * The stream from which to read the table of contents.
 *
 * \param[out] Buffer
 * Allocated buffer to receive the frame library name.
 *
 * \param[in] BufferSize
 * Maximum size of Buffer
 *
 * \return
 * Upon success, 1 is returned; 0 otherwise.
 */
int FrameCFrameLibraryName( FrameCError** Error,
                            fr_file_t*    Stream,
                            char*         Buffer,
                            size_t        BufferSize );

/**
 * \brief Obtain the major version of the frame specification.
 *
 * \param[out] Error
 * If an error occurs, this will contain the details of the error.
 * For full details on error processing, please refer to FrameCError.
 *
 * \param[in] Stream
 * The stream for which to obtain the frame specification.
 *
 * \return
 * The frame specification of the stream.
 */
int FrameCFrameLibraryVersion( FrameCError** Error, fr_file_t* Stream );

/**
 * \brief Obtain the library version
 *
 * \param[out] Error
 * If an error occurs, this will contain the details of the error.
 * For full details on error processing, please refer to FrameCError.
 *
 * \param[in] Stream
 * The stream for which to obtain the library version.
 *
 * \return
 * The library version of the stream.
 *
 * \note
 * The value only has significance in relationship to the frame
 * library used to create the frame.
 */
int FrameCFrameLibraryVersionMinor( FrameCError** Error, fr_file_t* Stream );
/**
 * \brief Verify the frame file checksum
 *
 * \param[out] Error
 * If an error occurs, this will contain the details of the error.
 * For full details on error processing, please refer to FrameCError.
 *
 * \param[in] Stream
 * The stream for which to obtain the library version.
 *
 * \return
 * Upon success, a non-zero value is returned.
 * Upon failure, a zero value is returned.
 *
 * The stream for which to obtain the library version.
 */
int FrameCFileCksumValid( FrameCError** Error, fr_file_t* Stream );
#if WORKING
int FrameCFileIGWDVersion( FrameCError** Error, fr_file_t* Stream );
#endif /* WORKING */

#ifdef __cplusplus
} /* extern "C" */
#endif /* __cplusplus */

#endif /* FRAMECPP__FRAME_C_STREAM_H */
