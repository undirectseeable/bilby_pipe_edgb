//
// LDASTools frameCPP - A library implementing the LIGO/Virgo frame
// specification
//
// Copyright (C) 2019 California Institute of Technology
//
// LDASTools frameCPP is free software; you may redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 (GPLv2) of the
// License or at your discretion, any later version.
//
// LDASTools frameCPP is distributed in the hope that it will be useful, but
// without any warranty or even the implied warranty of merchantability
// or fitness for a particular purpose. See the GNU General Public
// License (GPLv2) for more details.
//
// Neither the names of the California Institute of Technology (Caltech),
// The Massachusetts Institute of Technology (M.I.T), The Laser
// Interferometer Gravitational-Wave Observatory (LIGO), nor the names
// of its contributors may be used to endorse or promote products derived
// from this software without specific prior written permission.
//
// You should have received a copy of the licensing terms for this
// software included in the file LICENSE located in the top-level
// directory of this package. If you did not, you can view a copy at
// http://dcc.ligo.org/M1500244/LICENSE
//

#ifndef FrameCPP_VERSION_8__IMPL__FrEndOfFileData_HH
#define FrameCPP_VERSION_8__IMPL__FrEndOfFileData_HH

#include "ldastoolsal/types.hh"

#define FR_END_OF_FILE_N_FRAMES_TYPE INT_4U
#define FR_END_OF_FILE_N_BYTES_TYPE INT_8U
#define FR_END_OF_FILE_SEEK_TOC_TYPE INT_8U
#define FR_END_OF_FILE_CHK_SUM_FR_HEADER_TYPE INT_4U
#define FR_END_OF_FILE_CHK_SUM_TYPE INT_4U
#define FR_END_OF_FILE_CHK_SUM_FILE_TYPE INT_4U

#if !defined( SWIGIMPORTED )

#include "framecpp/Version8/FrameSpec.hh"

namespace FrameCPP
{
    namespace Version_8
    {
        namespace FrEndOfFileImpl
        {
            class Data
            {
            public:
                typedef FR_END_OF_FILE_N_FRAMES_TYPE nFrames_type;
                typedef FR_END_OF_FILE_N_BYTES_TYPE  nBytes_type;
                typedef FR_END_OF_FILE_SEEK_TOC_TYPE seekTOC_type;
                typedef FR_END_OF_FILE_CHK_SUM_FR_HEADER_TYPE
                                                         chkSumFrHeader_type;
                typedef FR_END_OF_FILE_CHK_SUM_TYPE      chkSum_type;
                typedef FR_END_OF_FILE_CHK_SUM_FILE_TYPE chkSumFile_type;

                //-----------------------------------------------------------------
                /// @brief Default constructor
                //-----------------------------------------------------------------
                Data( )
                    : nFrames( 0 ), nBytes( 0 ), seekTOC( 0 ),
                      chkSumFrHeader( 0 ), chkSum( 0 ), chkSumFile( 0 )
                {
                }

                //-----------------------------------------------------------------
                /// \brief Retrieve the checksum.
                ///
                /// \return
                ///     The checksum.
                //-----------------------------------------------------------------
                chkSum_type
                GetChkSum( ) const
                {
                    return chkSum;
                }

                //-----------------------------------------------------------------
                /// \brief Retrieve the file checksum.
                ///
                /// \return
                ///     The file checksum.
                //-----------------------------------------------------------------
                chkSumFile_type
                GetChkSumFile( ) const
                {
                    return chkSumFile;
                }

                //-----------------------------------------------------------------
                /// \brief Retrieve the FrHeader checksum.
                ///
                /// \return
                ///     The FrHEader checksum.
                //-----------------------------------------------------------------
                chkSumFrHeader_type
                GetChkSumFrHeader( ) const
                {
                    return chkSumFrHeader;
                }

                //-----------------------------------------------------------------
                /// \brief Retrieve the total number of bytes in this file.
                ///
                /// \return
                ///     The total number of bytes in this file.
                //-----------------------------------------------------------------
                nBytes_type
                GetNBytes( ) const
                {
                    return nBytes;
                }

                //-----------------------------------------------------------------
                /// \brief Retrieve the number of frames in this file.
                ///
                /// \return
                ///     The number of frames in this file.
                //-----------------------------------------------------------------
                nFrames_type
                GetNFrames( ) const
                {
                    return nFrames;
                }

                //-----------------------------------------------------------------
                /// \brief Retrieve the location of the table of contents.
                ///
                /// \return
                ///     The location of the table of contents.
                //-----------------------------------------------------------------
                seekTOC_type
                GetSeekTOC( ) const
                {
                    return seekTOC;
                }

            protected:
                //-----------------------------------------------------------------
                /// Number of frames in this file
                //-----------------------------------------------------------------
                nFrames_type nFrames;
                //-----------------------------------------------------------------
                /// Total number of bytes in the file; zero if not computed.
                //-----------------------------------------------------------------
                nBytes_type nBytes;
                //-----------------------------------------------------------------
                /// Bytes to back up to the Beginning of the table of contents
                /// structure.
                /// If seekTOC is zero, then there is no table of contents for
                /// this file.
                //-----------------------------------------------------------------
                seekTOC_type seekTOC;
                //-----------------------------------------------------------------
                /// FrHeader checksum
                //-----------------------------------------------------------------
                chkSumFrHeader_type chkSumFrHeader;
                //-----------------------------------------------------------------
                /// Structure checksum.
                ///
                /// \note
                ///     The chkSum AND chkSumFile ariables are not included in
                ///     the computation of checkSum, but chkSumFrHeader is
                ///     includeed
                //-----------------------------------------------------------------
                chkSum_type chkSum;
                //-----------------------------------------------------------------
                /// File checksum.
                //-----------------------------------------------------------------
                chkSumFile_type chkSumFile;
            };

        } // namespace FrEndOfFileImpl
    } // namespace Version_8
} // namespace FrameCPP

#endif /* ! defined(SWIGIMPORTED) */

#endif /* FrameCPP_VERSION_8__IMPL__FrEndOfFileData_HH */
