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

#ifndef FRAME_CPP__Common__CompressionGZip_hh
#define FRAME_CPP__Common__CompressionGZip_hh

#include <boost/shared_array.hpp>

namespace FrameCPP
{
    namespace Compression
    {
        //-------------------------------------------------------------------
        /// \brief Routines related to the gzip compression algorith
        //-------------------------------------------------------------------
        namespace GZip
        {
            //-----------------------------------------------------------------
            /// \brief Compress the data with GZip.
            ///
            /// \param[in] DataIn
            ///     Pointer to the data to be compressed
            /// \param[in] NBytesIn
            ///     The number of bytes to be compressed.
            ///     Upon return, the size of the compressed buffer is returned.
            /// \param[in] Level
            ///     Compression level.
            /// \param[out] DataOut
            ///     Pointer to the data to be compressed
            /// \param[out] NBytesOut
            ///     The number of bytes to be compressed.
            ///     Upon return, the size of the compressed buffer is returned.
            /// \todo Correct this documentation
            //-----------------------------------------------------------------
            void Compress( const CHAR_U*                  DataIn,
                           INT_8U                         NBytesIn,
                           size_t                         Level,
                           boost::shared_array< CHAR_U >& DataOut,
                           INT_8U&                        NBytesOut );

            //-----------------------------------------------------------------
            /// \brief Expand the data with GZip.
            ///
            /// \param[in] DataIn
            /// \param[in] NBytesIn
            /// \param[out] DataOut
            /// \param[in,out] NBytesOut
            ///     On input, this must be set to the expected number of bytes
            ///     for the expanded buffer.
            ///     On output, this will have the number of bytes in the
            ///     DataOut buffer.
            //-----------------------------------------------------------------
            void Expand( const CHAR_U*                  DataIn,
                         INT_8U                         NBytesIn,
                         boost::shared_array< CHAR_U >& DataOut,
                         INT_8U&                        NBytesOut );

        } // namespace GZip

    } // namespace Compression

} // namespace FrameCPP

#endif /* FRAME_CPP__Common__CompressionGZip_hh */
