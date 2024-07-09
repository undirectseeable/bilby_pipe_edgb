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

#ifndef FRAME_CPP__Common__CompressionZeroSuppress_hh
#define FRAME_CPP__Common__CompressionZeroSuppress_hh

#include <boost/shared_array.hpp>
#include <boost/shared_ptr.hpp>

#include "ldastoolsal/types.hh"

#include "framecpp/Common/CompressionDifferential.hh"
#include "framecpp/Common/CompressionException.hh"

namespace FrameCPP
{
    //=====================================================================
    // Exceptions
    //=====================================================================

    class FrZCompRangeError : public FrUncompressable
    {
    public:
        inline FrZCompRangeError( INT_2S Value )
            : FrUncompressable( format_msg( Value ) ){};

    private:
        inline std::string
        format_msg( INT_2S Value )
        {
            std::ostringstream oss;

            oss << "Buffer cannot be compressed using FrVectZCompShort because "
                   "value of "
                << Value << " encountered";
            return oss.str( );
        }
    };

    class FrZCompIRangeError : public FrUncompressable
    {
    public:
        inline FrZCompIRangeError( INT_4S Value )
            : FrUncompressable( format_msg( Value ) ){};

    private:
        inline std::string
        format_msg( INT_4S Value )
        {
            std::ostringstream oss;

            oss << "Buffer cannot be compressed using FrVectZCompInt because "
                   "value of "
                << Value << " encountered";
            return oss.str( );
        }
    };

    namespace Compression
    {
        //-------------------------------------------------------------------
        /// \brief Routines related to the gzip compression algorith
        //-------------------------------------------------------------------
        namespace ZeroSuppress
        {
            typedef boost::shared_array< CHAR_U > data_type;
            typedef data_type::element_type       data_element_type;
            typedef INT_8U                        nbytes_type;
            typedef INT_8U                        ndata_type;
            typedef INT_4U                        data_type_type;

            //-----------------------------------------------------------------
            /// \brief Compress the data with ZeroSuppress.
            ///
            /// \param[in] DataIn
            ///     Pointer to the data to be compressed
            /// \param[in] NBytesIn
            ///     The number of bytes to be compressed.
            ///     Upon return, the size of the compressed buffer is returned.
            /// \param[out] DataOut
            ///     Pointer to the data to be compressed
            /// \param[out] NBytesOut
            ///     The number of bytes to be compressed.
            ///     Upon return, the size of the compressed buffer is returned.
            /// \todo Correct this documentation
            //-----------------------------------------------------------------
            template < int >
            void Compress( const data_element_type*                  DataIn,
                           nbytes_type                               NBytesIn,
                           boost::shared_array< data_element_type >& DataOut,
                           nbytes_type& NBytesOut );

            template < int >
            void Compress( const data_element_type* DataIn,
                           nbytes_type              NBytesIn,
                           data_type&               DataOut,
                           nbytes_type&             NBytesOut );

            template < int >
            void Expand( const data_element_type*                  DataIn,
                         nbytes_type                               DataInBytes,
                         bool                                      ByteSwap,
                         boost::shared_array< data_element_type >& DataOut,
                         ndata_type                                NDataOut,
                         nbytes_type&                              NBytesOut );

            template < int >
            void Expand( const data_element_type* DataIn,
                         nbytes_type              DataInBytes,
                         bool                     ByteSwap,
                         data_type&               DataOut,
                         ndata_type               NDataOut,
                         nbytes_type&             NBytesOut );

            template < int >
            void
            DiffCompress( const data_element_type*                  DataIn,
                          nbytes_type                               NBytesIn,
                          data_type_type                            DataType,
                          boost::shared_array< data_element_type >& DataOut,
                          nbytes_type&                              NBytesOut );

            template < int >
            void DiffCompress( const data_element_type* DataIn,
                               nbytes_type              NBytesIn,
                               data_type_type           DataType,
                               data_type&               DataOut,
                               nbytes_type&             NBytesOut );

            //-----------------------------------------------------------------
            /// \brief Expansion of the data
            ///
            /// \param[in] DataIn
            ///     The data to be expanded
            /// \param[in] DataInBytes
            ///     Then number of bytes in DataIn.
            /// \param[in] ByteSwap
            ///     If true, then perform byte swapping; false otherwise
            /// \param[in] DataType
            ///     The data type of the compressed data.
            /// \param[out] DataOut
            ///     If DataIn is uncompressable, then the resulting
            ///     uncompressed data is stored here.
            ///     If DataIn is can not be uncompressed, then this will
            ///     be set to a NULL pointer.
            /// \param[in] NDataOut
            ///     The number of data elements expected to be in the
            ///     uncompressed buffer.
            /// \param[in] NBytesOut
            ///     Then number of bytes allocated to DataOut.
            //-----------------------------------------------------------------
            template < int Size >
            void DiffExpand( const data_element_type* DataIn,
                             nbytes_type              DataInBytes,
                             bool                     ByteSwap,
                             data_type_type           DataType,
                             boost::shared_array< data_element_type >& DataOut,
                             ndata_type                                NDataOut,
                             nbytes_type& NBytesOut );

            //-----------------------------------------------------------------
            /// \brief Expansion of the data
            ///
            /// \param[in] DataIn
            ///     The data to be expanded
            /// \param[in] DataInBytes
            ///     Then number of bytes in DataIn.
            /// \param[in] ByteSwap
            ///     If true, then perform byte swapping; false otherwise
            /// \param[in] DataType
            ///     The data type of the compressed data.
            /// \param[out] DataOut
            ///     If DataIn is uncompressable, then the resulting
            ///     uncompressed data is stored here.
            ///     If DataIn is can not be uncompressed, then this will
            ///     be set to a NULL pointer.
            /// \param[in] NDataOut
            ///     The number of data elements expected to be in the
            ///     uncompressed buffer.
            /// \param[in] NBytesOut
            ///     Then number of bytes allocated to DataOut.
            //-----------------------------------------------------------------
            template < int Size >
            void DiffExpand( const data_element_type* DataIn,
                             nbytes_type              DataInBytes,
                             bool                     ByteSwap,
                             data_type_type           DataType,
                             data_type&               DataOut,
                             ndata_type               NDataOut,
                             nbytes_type&             NBytesOut );

        } // namespace ZeroSuppress

    } // namespace Compression

} // namespace FrameCPP

#endif /* FRAME_CPP__Common__CompressionZeroSuppress_hh */
