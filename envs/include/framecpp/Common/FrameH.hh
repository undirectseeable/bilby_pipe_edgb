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

#ifndef FrameCPP__COMMON__FRAME_H_HH
#define FrameCPP__COMMON__FRAME_H_HH

#include "framecpp/Common/FrameSpec.hh"
#include "framecpp/Common/StringStream.hh"

namespace FrameCPP
{
    namespace Common
    {
        class Description;

        class FrameH : public FrameSpec::Object
        {
        public:
            typedef IStringStream assign_stream_type;

            using FrameSpec::Object::Create;

            enum copy_type
            {
                DETECT_SIM = 0x0001,
                DETECT_PROC = 0x0002,
                HISTORY = 0x0004,
                RAW_DATA = 0x0008,
                AUX_DATA = 0x0010,
                AUX_TABLE = 0x0020,
                TYPE = 0x0040,
                USER = 0x0080
            };

#if 0
      enum detector_copy_type
      {
	DEEP_COPY_DETECTORS,
	SHALLOW_COPY_DETECTORS
      };
#endif /* 0 */

            static const Common::FrameSpec::Info::frame_object_types
                s_object_id = Common::FrameSpec::Info::FSI_FRAME_H;

            FrameH( const Description* Desc );

            virtual ~FrameH( );

            virtual start_time_normalized_type normalizedStartTime( ) const = 0;

            virtual delta_t_normalized_type normalizedDeltaT( ) const = 0;

            virtual void readSubset( IStream& Stream, INT_4U ElementMask ) = 0;

            //-----------------------------------------------------------------
            /// \brief Assign the contents of the instance
            ///
            /// \param[in] Stream
            ///     An input stream from which to read information for
            ///     the instance.
            //-----------------------------------------------------------------
            virtual void assign( assign_stream_type& Stream ) = 0;

        private:
        };
    } // namespace Common
} // namespace FrameCPP

#endif /* FrameCPP__COMMON__FRAME_H_HH */
