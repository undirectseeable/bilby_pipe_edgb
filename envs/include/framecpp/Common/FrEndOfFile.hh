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

#ifndef FrameCPP__COMMON__FR_END_OF_FILE_HH
#define FrameCPP__COMMON__FR_END_OF_FILE_HH

#include "framecpp/Common/FrameSpec.hh"
#include "framecpp/Common/StringStream.hh"

namespace FrameCPP
{
    namespace Common
    {
        class Description;
        class CheckSum;
        class IFrameStream;
        class IStringStream;

        class FrEndOfFile : public FrameSpec::Object
        {
        public:
            typedef INT_8U        nBytes_cmn_type;
            typedef INT_4U        nFrames_cmn_type;
            typedef INT_8U        seekTOC_cmn_type;
            typedef INT_4U        chkType_cmn_type;
            typedef INT_4U        chkSum_cmn_type;
            typedef IStringStream assign_stream_type;

            static const Common::FrameSpec::Info::frame_object_types
                s_object_id = Common::FrameSpec::Info::FSI_FR_END_OF_FILE;

            FrEndOfFile( const Description* Desc );

            virtual ~FrEndOfFile( );

            virtual nBytes_cmn_type NBytes( ) const = 0;

            virtual nFrames_cmn_type NFrames( ) const = 0;

            virtual seekTOC_cmn_type SeekTOC( ) const;

            //-----------------------------------------------------------------
            /// \brief Run filters over the given bytes.
            ///
            /// \param[in,out] Stream
            ///     The source of the bytes to read.
            /// \param[in,out] Check
            ///     The running checksum calculation
            /// \param[out] Type
            ///     The recorded CRC type present in this structure when read
            ///     from the stream.
            /// \param[in] Buffer
            ///     The bytes to be filtered
            /// \param[in] Size
            ///     The number of bytes in Buffer to be checked.
            ///
            /// \return
            ///     The checksum value recorded within the
            ///     FrEndOfFile structure.
            //-----------------------------------------------------------------
            virtual chkSum_cmn_type Filter( const Common::IStream& Stream,
                                            CheckSum&              Check,
                                            chkType_cmn_type&      Type,
                                            void*                  Buffer,
                                            INT_8U Size ) const = 0;

            //-----------------------------------------------------------------
            /// \brief Assign the contents of the instance
            ///
            /// \param[in] Stream
            ///     An input stream from which to read information for
            ///     the instance.
            //-----------------------------------------------------------------
            virtual void assign( assign_stream_type& Stream ) = 0;
        };
    } // namespace Common
} // namespace FrameCPP

#endif /* FrameCPP__COMMON__FR_END_OF_FILE_HH */
