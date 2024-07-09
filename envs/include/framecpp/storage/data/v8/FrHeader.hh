//
// LDASTools frameCPP - A library implementing the LIGO/Virgo frame
// specification
//
// Copyright (C) 2020 California Institute of Technology
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

#ifndef FRAMECPPCPP__STORAGE__DATA__V8__FR_HEADER_HH
#define FRAMECPPCPP__STORAGE__DATA__V8__FR_HEADER_HH

#include <string>

#include "ldastoolsal/ldas_types.h"

#include "framecpp/storage/data/v3/FrHeader.hh"

namespace FrameCPP
{
    namespace v8
    {
        //-----------------------------------------------------------
        /// @brief Storage space for FrSH information
        ///
        /// This stores information about an FrSH element that
        /// needs to persist beyond an I/O operation
        //-----------------------------------------------------------
        class FrHeader
        {
        public:
          typedef v3::magic_id_type magic_id_type; //< Bytes 0-4
          typedef v3::version_type version_type;
          typedef v3::identifier_type identifier_type;
          typedef v3::integer_sizes integer_sizes;
          typedef v3::real_sizes real_sizes;
          typedef v3::integer_ordering integer_ordering;
          typedef v3::real_ordering real_ordering;

        protected:
            typedef union
            {
                typedef struct
                {
                    identifier_type       identifier;
                    integer_sizes_type    integer_sizes;
                    real_sizes_type       real_sizes;
                    integer_ordering_type integer_ordering;
                    real_ordering_type    real_ordering;
                    CHAR_U                frame_library; //< Byte 38
                    CHAR_U                checksum_scheme; //< Byte 39
                } raw_type raw;
                CHAR_U     block[ sizeof( raw_type ) ];
            } fr_header_body_type;
        };

    } // namespace v8

} // namespace FrameCPP

#endif /* FRAMECPPCPP__STORAGE__DATA__V8__FR_HEADER_HH */
