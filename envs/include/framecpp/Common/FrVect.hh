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

#ifndef FRAME_CPP__COMMON__FR_VECT_HH
#define FRAME_CPP__COMMON__FR_VECT_HH

#include "framecpp/Common/FrameSpec.hh"
#include "framecpp/Common/Compression.hh"

namespace FrameCPP
{
    namespace Common
    {
        class FrVect
        {
        public:
            typedef INT_4U cmn_compression_scheme_type;
            typedef INT_2U cmn_compression_level_type;

            virtual ~FrVect( );

            virtual Compression::compression_base_type Compression( ) const = 0;

            virtual void CompressData( cmn_compression_scheme_type Scheme,
                                       cmn_compression_level_type  Level ) = 0;

            virtual FrameSpec::Object*
            CloneCompressed( cmn_compression_scheme_type Scheme,
                             cmn_compression_level_type  Level ) const = 0;

        protected:
            void compressToBuffer(
                const Compression::compress_type_mapping& CompressionMapping,
                const Compression::compress_type_reverse_mapping&
                                                      CompressionReverseMapping,
                const Compression::data_type_mapping& DataTypeMapping,
                const INT_4U                          DataType,
                const INT_8U                          NData,
                const CHAR_U*                         Source,
                const INT_8U                          SourceNBytes,
                const INT_4U                          SourceCompressionMode,
                Compression::output_type&             Dest,
                INT_8U&                               DestNBytes,
                INT_4U&                               DestCompressionMode,
                const INT_4U                          Level ) const;

            void expandToBuffer(
                const Compression::compress_type_mapping& CompressionMapping,
                const Compression::data_type_mapping&     DataTypeMapping,
                const INT_4U                              DataType,
                const INT_8U                              NData,
                const CHAR_U*                             Source,
                const INT_8U                              SourceNBytes,
                const INT_4U                              SourceCompressionMode,
                const INT_4U                              SourceByteOrder,
                Compression::output_type&                 Dest,
                INT_8U&                                   DestNBytes ) const;
        };

#if !defined( SWIG )
        inline FrVect::~FrVect( )
        {
        }
#endif /* ! defined(SWIG) */

    } // namespace Common
} // namespace FrameCPP

#endif /* FRAME_CPP__COMMON__FR_VECT_HH */
