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

#ifndef FRAME_CPP__Common__CHECKSUM_HH
#define FRAME_CPP__Common__CHECKSUM_HH

#if HAVE_ENDIAN_H
#include <endian.h>
#else /* HAVE_ENDIAN_H */
#ifndef __BIG_ENDIAN
#define __BIG_ENDIAN 0xFF00
#endif /* __BIG_ENDIAN */
#ifndef __LITTLE_ENDIAN
#define __LITTLE_ENDIAN 0x00FF
#endif /* __LITTLE_ENDIAN */

#if WORDS_BIGENDIAN
#define __BYTE_ORDER __BIG_ENDIAN
#else /* WORDS_BIGENDIAN */
#define __BYTE_ORDER __LITTLE_ENDIAN
#endif /* WORDS_BIGENDIAN */

#endif /* HAVE_ENDIAN_H */

#if !SWIGIMPORTED
#include <iostream>

#include <stdint.h>
#endif /* !SWIGIMPORTED */

#include "ldastoolsal/types.hh"

#include "framecpp/Common/cksum_boost.hh"
#include "framecpp/Common/cksum_ldas.hh"

namespace FrameCPP
{
    namespace Common
    {
        class CheckSum
        {
        public:
            enum kind_type
            {
                UNSET = -1,
                NONE = 0,
                CRC = 1
            };
            typedef INT_8U size_type;
            typedef INT_4U value_type;
            CheckSum( const kind_type Type );
            virtual ~CheckSum( );
            static CheckSum* Create( kind_type Type );
            static CheckSum* Create( kind_type Type, value_type Value );
            kind_type        GetType( ) const;
            virtual void     Reset( );
            virtual void
            calc( const void* Buffer,
                  size_type   NBytes ) = 0; /// \brief Things to be do to
            /// \brief Things to do to complete the calculation
            value_type         value( );
            virtual CheckSum*  Clone( ) const = 0;
            static std::string FormatError( value_type ExpectedValue,
                                            value_type CalculatedValue );

        protected:
            value_type m_value;
            CheckSum( const CheckSum& Source );
            virtual void finish( ) = 0;

        private:
            kind_type m_type = UNSET;
            CheckSum( );
        };

        inline CheckSum::kind_type
        CheckSum::GetType( ) const
        {
            return m_type;
        }

        inline CheckSum::value_type
        CheckSum::value( )
        {
            finish( );
            return m_value;
        }

        class CheckSumCRC : public CheckSum
        {
        public:
            using CheckSum::size_type;
            typedef cksum_ldas           crc_type;
            typedef CheckSum::value_type value_type;

            CheckSumCRC( );
            CheckSumCRC( value_type Value );
            virtual CheckSumCRC* Clone( ) const;
            virtual void         Reset( );
            virtual void         calc( const void* Buffer, size_type NBytes );

        protected:
            CheckSumCRC( const CheckSumCRC& Source );
            virtual void finish( );
            crc_type     crc_generator;

        private:
            bool m_active = true;
        };

    }; // namespace Common

} // namespace FrameCPP

#endif /* FRAME_CPP__Common__CHECKSUM_HH */
