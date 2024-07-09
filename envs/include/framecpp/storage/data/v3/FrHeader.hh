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

#ifndef FRAMECPPCPP__STORAGE__DATA__FR_HEADER_HH
#define FRAMECPPCPP__STORAGE__DATA__FR_HEADER_HH

#include <string>

#include "ldastoolsal/ldas_types.h"

namespace FrameCPP
{
    namespace v3
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
            typedef CHAR_U magic_id_type[ 5 ]; //< Bytes 0-4
            typedef struct
            {
                CHAR_U major; //< Byte 5
                CHAR_U minor; //< Byte 6
            } version_type;

            typedef struct
            {
                magic_id_type magic_id;
                version_type  version;
            } identifier_type;

            typedef struct
            {
                CHAR_U sizeInt2; //< Byte 7
                CHAR_U sizeInt4; //< Byte 8
                CHAR_U sizeInt8; //< Byte 9
            } integer_sizes;

            typedef struct
            {
                CHAR_U sizeReal4; //< Byte 10
                CHAR_U sizeReal8; //< Byte 11
            } real_sizes;

            typedef struct
            {
                CHAR_U x1234[ 2 ]; //< Bytes 12-13
                CHAR_U x12345678[ 4 ]; //< Bytes 14-17
                CHAR_U x123456789abcdef[ 8 ]; //< Bytes 18-25
            } integer_ordering;

            typedf struct
            {
                CHAR_U smallPi[ 4 ]; //< Bytes 26-29
                CHAR_U bigPi[ 8 ]; //< Bytes 30-37
            } real_ordering;

        protected:
            magic_id_type magic_id;
            typedef union
            {
                typedef struct
                {
                    identifier_type       identifier;
                    integer_sizes_type    integer_sizes;
                    real_sizes_type       real_sizes;
                    integer_ordering_type integer_ordering;
                    real_ordering_type    real_ordering;
                    CHAR_U                ascii_A; //< Byte 38
                    CHAR_U                ascii_Z; //< Byte 39
                } raw_type raw;
                CHAR_U     block[ sizeof( raw_type ) ];
            } fr_header_body_type;
        };

    } // namespace v3

} // namespace FrameCPP

#endif /* FRAMECPPCPP__STORAGE__DATA__FR_HEADER_HH */
