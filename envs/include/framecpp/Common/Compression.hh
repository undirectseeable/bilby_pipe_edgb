//
// LDASTools frameCPP - A library implementing the LIGO/Virgo frame
// specification
//
// Copyright (C) 2018 California Institute of Technology
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

#ifndef FRAME_CPP__Common__Compression_hh
#define FRAME_CPP__Common__Compression_hh

#if !defined( SWIGIMPORTED )
#include <limits>

#include <iostream>
#include <sstream>
#include <stdexcept>

#include <boost/shared_array.hpp>
#endif /* ! defined(SWIGIMPORTED) */

#include "ldastoolsal/types.hh"
#include "ldastoolsal/unordered_map.hh"

#include "framecpp/Common/CompressionException.hh"

namespace FrameCPP
{
    //---------------------------------------------------------------------
    /// \brief Routines related to compression algorithems
    //---------------------------------------------------------------------
    namespace Compression
    {
        typedef boost::shared_array< CHAR_U > output_type;

        //-------------------------------------------------------------------
        /// \brief Enumerated type for supported vector data types.
        //-------------------------------------------------------------------
        enum data_types_type
        {
            FR_VECT_C = 0, ///< CHAR data type
            FR_VECT_2S = 1, ///< INT_2S data type
            FR_VECT_8R = 2, ///< REAL_8 data type
            FR_VECT_4R = 3, ///< REAL_4 data type
            FR_VECT_4S = 4, ///< INT_4S data type
            FR_VECT_8S = 5, ///< INT_8S data type
            FR_VECT_8C = 6, ///< COMPLEX_8 data type
            FR_VECT_16C = 7, ///< COMPLEX_16 data type
            FR_VECT_STRING = 8, ///< STRING data type
            FR_VECT_2U = 9, ///< INT_2U data type
            FR_VECT_4U = 10, ///< INT_4U data type
            FR_VECT_8U = 11, ///< INT_8U data type
            FR_VECT_1U = 12 ///< CHAR_U data type
        };

        //-------------------------------------------------------------------
        /// \brief Enumerated type for general compression modes
        //-------------------------------------------------------------------
        enum compress_type
        {
            //=================================================================
            //          ***  S T A N D A R D   M O D E S  ***
            //=================================================================
            //-----------------------------------------------------------------
            /// Uncompressed raw values
            //-----------------------------------------------------------------
            MODE_RAW = 0,
            //-----------------------------------------------------------------
            /// Gzip of any data type
            //-----------------------------------------------------------------
            MODE_GZIP = 0x10000,
            MODE_DIFF = 0x20000,
            //-----------------------------------------------------------------
            /// Gzip of differential values for FR_VECT_C, FR_VECT_1U,
            /// FR_VECT_2S, FR_VECT_2U, FR_VECT_4S, and FR_VECT_4U.
            //-----------------------------------------------------------------
            MODE_DIFF_GZIP = 0x30000,
            //-----------------------------------------------------------------
            /// Zero suppression algorithm for FR_VECT_2S and FR_VECT_2U.
            //-----------------------------------------------------------------
            MODE_ZERO_SUPPRESS_SHORT = 0x40000,
            //-----------------------------------------------------------------
            /// Zero suppression algorithm for FR_VECT_4S, FR_VECT_4U,
            /// FR_VECT_4R.
            //-----------------------------------------------------------------
            MODE_ZERO_SUPPRESS_INT_FLOAT = 0x50000,
            //-----------------------------------------------------------------
            /// Zero suppression algorithm for FR_VECT_4S, FR_VECT_4U,
            /// FR_VECT_4R, and FR_VECT_8C.
            /// If used on data types FR_VECT_2U or FR_VECT_2S,
            /// then the mode is modified to MODE_ZERO_SUPPRESS_SHORT.
            //-----------------------------------------------------------------
            MODE_ZERO_SUPPRESS_WORD_4 = 0x60000,
            //-----------------------------------------------------------------
            /// Zero suppression algorithm for FR_VECT_8S, FR_VECT_8U,
            /// FR_VECT_8R, and FR_VECT_16C.
            /// If used on data types FR_VECT_4U, FR_VECT_4S, FR_VECT_4R
            /// or FR_VECT_8C,
            /// then the mode is modified to MODE_ZERO_SUPPRESS_INT_FLOAT.
            /// If used on data types FR_VECT_2U or FR_VECT_2S,
            /// then the mode is modified to MODE_ZERO_SUPPRESS_SHORT.
            //-----------------------------------------------------------------
            MODE_ZERO_SUPPRESS_WORD_8 = 0x70000,

            //=================================================================
            //             ***  M E T A   M O D E S  ****
            //=================================================================
            //-----------------------------------------------------------------
            /// This meta mode uses MODE_ZERO_SUPPRESS_SHORT for FR_VECT_2S
            /// and FR_VECT_2U;
            /// All other data types are compressed using MODE_GZIP.
            //-----------------------------------------------------------------
            MODE_ZERO_SUPPRESS_2_OTHERWISE_GZIP = 0x1000000,
            //-----------------------------------------------------------------
            /// This meta mode uses MODE_ZERO_SUPPRESS_SHORT for FR_VECT_2S
            /// and FR_VECT_2U;
            /// for FR_VECT_4U, FR_VECT_4S, FR_VECT_4R, and FR_VECT_8C,
            /// compression mode MODE_ZERO_SUPPRESS_INT_FLOAT is used;
            /// All other data types are compressed using MODE_GZIP.
            //-----------------------------------------------------------------
            MODE_ZERO_SUPPRESS_2_4_OTHERWISE_GZIP = 0x2000000,
            //-----------------------------------------------------------------
            /// This meta mode uses MODE_ZERO_SUPPRESS_SHORT for FR_VECT_2S
            /// and FR_VECT_2U;
            /// for FR_VECT_4U, FR_VECT_4S, FR_VECT_4R, and FR_VECT_8C,
            /// compression mode MODE_ZERO_SUPPRESS_INT_FLOAT is used;
            /// for FR_VECT_8U, FR_VECT_8S, FR_VECT_8R, and FR_VECT_16C,
            /// compression mode MODE_ZERO_SUPPRESS_WORD_8 is used;
            /// All other data types are compressed using MODE_GZIP.
            //-----------------------------------------------------------------
            MODE_ZERO_SUPPRESS_2_4_8_OTHERWISE_GZIP = 0x3000000,
            //-----------------------------------------------------------------
            /// This compression mode tries to compress the data using all
            /// known compression modes and keeps the one with the highest
            /// compression ratio.
            //-----------------------------------------------------------------
            MODE_BEST_COMPRESSION = 0x4000000
        };

        //===================================================================
        // types
        //===================================================================
        typedef INT_2U compression_base_type;

        typedef LDASTools::AL::unordered_map< INT_4U, data_types_type >
            data_type_mapping;

        typedef LDASTools::AL::unordered_map< INT_4U, compress_type >
            compress_type_mapping;

        typedef LDASTools::AL::unordered_map< compress_type, INT_4U >
            compress_type_reverse_mapping;

        //-------------------------------------------------------------------
        /// \brief compress data without altering the source
        ///
        /// \param[in,out] CompressionMode
        ///     On input, this variable represents the desired compression
        ///     method to be used.
        ///     Because some compression modes represent a set of compression
        ///     methods, this value may be modified to signify the one
        ///     actually choosen.
        /// \param[in] Level
        ///     Some compression methods support the idea of levels.
        ///     For these methods, it usually is a trade off between speed
        ///     and size.
        ///     The higher the level, the harder the algorithm tries to
        ///     compress the data.
        /// \param[in] CompressionMapping
        ///     Provides an interface from the frame spec to the generic
        ///     compression routine about the compression being requested.
        /// \param[in] CompressionReverseMapping
        ///     Provides mapping information about how to go from the generic
        ///     compression modes to the frame specification compression
        ///     modes.
        /// \param[in] DataType
        ///     The data type of the source.
        /// \param[in] DataTypeMapping
        ///     This is a table mapping the supported data types allowed
        ///     by the user.
        ///     Since these routines are general, they may be able to do
        ///     more than what the caller is requesting.
        ///     This table limits the allowed data types.
        /// \param[in] Source
        ///     This is a buffer of data to be compressed.
        /// \param[in] SourceLength
        ///     The number of data elements in the origional, uncompressed
        ///     data array.
        /// \param[in] SourceByteLength
        ///     The number of bytes used by Source.
        /// \param[out] Dest
        ///     The buffer in compressed format.
        ///     If the compression failed, then this will be a NULL pointer.
        ///     If the compression succeeded, this will be a pointer
        ///     allocated via new[] and is the responsibility of the caller
        ///     to deallocate.
        /// \param[out] DestByteLength
        ///     The number of bytes used by Dest.
        ///     If the compression failed, then this will be zero.
        //-------------------------------------------------------------------
        void Compress(
            INT_4U&                              CompressionMode,
            INT_4U                               Level,
            const compress_type_mapping&         CompressionMapping,
            const compress_type_reverse_mapping& CompressionReverseMapping,
            INT_4U                               DataType,
            const data_type_mapping&             DataTypeMapping,
            const CHAR_U*                        Source,
            const INT_8U                         SourceLength,
            const INT_8U                         SourceByteLength,
            output_type&                         Dest,
            INT_8U&                              DestByteLength );

        //-------------------------------------------------------------------
        /// \brief uncompress data without altering the source
        ///
        /// \param[in] NativeOrder
        ///     Boolean describing if the data being uncompressed is of the
        ///     same byte order as the host.
        /// \param[in] CompressionMode
        ///     Version specific compression mode.
        /// \param[in] CompressionMapping
        ///     Map from version specific compression modes to compression
        ///     modes used by the general compression routines.
        /// \param[in] DataType
        ///     Version specific data type.
        /// \param[in] DataTypeMapping
        ///     Map from version specific data type to data types
        ///     used by the general compression routines.
        /// \param[in] Source
        ///     The compressed data stream.
        /// \param[in] SourceLength
        ///     The number of data elements.
        /// \param[in] SourceByteLength
        ///     The number of bytes
        /// \param[out] Dest
        ///     New buffer containing the decompressed data.
        /// \param[out] DataByteLength
        ///     The number of bytes allocated to Dest.
        //-------------------------------------------------------------------
        void Expand( const bool                   NativeOrder,
                     const INT_4U                 CompressionMode,
                     const compress_type_mapping& CompressionMapping,
                     const INT_4U                 DataType,
                     const data_type_mapping&     DataTypeMapping,
                     const CHAR_U*                Source,
                     const INT_8U                 SourceLength,
                     const INT_8U                 SourceByteLength,
                     output_type&                 Dest,
                     INT_8U&                      DataByteLength );

    } // namespace Compression

} // namespace FrameCPP

HASH_NAMESPACE_BEGIN
{
    template <>
    struct hash< FrameCPP::Compression::compress_type >
    {
        inline size_t
        operator( )( const FrameCPP::Compression::compress_type Key ) const
        {
            return ( Key >> 16 );
        }
    };
}
HASH_NAMESPACE_END

#endif /* FRAME_CPP__Common__Compression_hh */
