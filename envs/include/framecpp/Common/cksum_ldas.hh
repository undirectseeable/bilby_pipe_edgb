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

#ifndef FRAME_CPP__Common__CRC_LDAS_HH
#define FRAME_CPP__Common__CRC_LDAS_HH

#if !SWIGIMPORTED
#include <cstdint>

#include <boost/endian/conversion.hpp>
#endif /* ! SWIGIMPORTED */

#include "ldastoolsal/types.hh"
#if !SWIGIMPORTED
#include "ldastoolsal/reverse.hh"
#include "framecpp/Common/cksum.hh"
#endif /* ! SWIGIMPORTED */

namespace FrameCPP
{
    namespace Common
    {
        class crc_ldas
        {
        public:
            typedef uint32_t value_type;
            typedef uint64_t size_type;

            crc_ldas( );

            crc_ldas( const crc_ldas& Source );

            value_type checksum( ) const;

            void reset( );

            void process_bytes( const void* Buffer, size_type NBytes );

        private:
            static const value_type m_crctab[ 8 ][ 256 ];
            mutable value_type      checksum_accumulator{ 0 };

            void slice_by_1( const void* Data,
                             size_t      Length,
                             value_type& crc ) const;

            void slice_by_8( const void* Data, size_t Length );

            template < boost::endian::order ByteOrder >
            void process_eight_byte_chunck( const value_type*& Current );
        };

        inline crc_ldas::crc_ldas( )
        {
        }

        inline crc_ldas::crc_ldas( const crc_ldas& Source )
            : checksum_accumulator( Source.checksum_accumulator )
        {
        }

        inline crc_ldas::value_type
        crc_ldas::checksum( ) const
        {
            auto crc = checksum_accumulator;
            crc = ~bswap_32( crc );
            return ( crc );
        }

        inline void
        crc_ldas::reset( )
        {
            checksum_accumulator = 0;
        }

        inline void
        crc_ldas::process_bytes( const void* Buffer, size_type NBytes )
        {
            slice_by_8( Buffer, NBytes );
        }

        template <>
        inline void
        crc_ldas::process_eight_byte_chunck< boost::endian::order::big >(
            const value_type*& Current )
        {
            value_type one = *Current++ ^ bswap_32( checksum_accumulator );
            value_type two = *Current++;

            checksum_accumulator = m_crctab[ 4 ][ one & 0xFF ] ^
                m_crctab[ 5 ][ ( one >> 8 ) & 0xFF ] ^
                m_crctab[ 6 ][ ( one >> 16 ) & 0xFF ] ^
                m_crctab[ 7 ][ ( one >> 24 ) & 0xFF ] ^
                m_crctab[ 0 ][ two & 0xFF ] ^
                m_crctab[ 1 ][ ( two >> 8 ) & 0xFF ] ^
                m_crctab[ 2 ][ ( two >> 16 ) & 0xFF ] ^
                m_crctab[ 3 ][ ( two >> 24 ) & 0xFF ];
        }

        template <>
        inline void
        crc_ldas::process_eight_byte_chunck< boost::endian::order::little >(
            const value_type*& Current )
        {
            value_type one = *Current++ ^ checksum_accumulator;
            value_type two = *Current++;

            checksum_accumulator = m_crctab[ 7 ][ one & 0xFF ] ^
                m_crctab[ 6 ][ ( one >> 8 ) & 0xFF ] ^
                m_crctab[ 5 ][ ( one >> 16 ) & 0xFF ] ^
                m_crctab[ 4 ][ ( one >> 24 ) & 0xFF ] ^
                m_crctab[ 3 ][ two & 0xFF ] ^
                m_crctab[ 2 ][ ( two >> 8 ) & 0xFF ] ^
                m_crctab[ 1 ][ ( two >> 16 ) & 0xFF ] ^
                m_crctab[ 0 ][ ( two >> 24 ) & 0xFF ];
        }

        inline void
        crc_ldas::slice_by_1( const void* Data,
                              size_t      Length,
                              value_type& crc ) const
        {
            const uint8_t* cp( reinterpret_cast< const uint8_t* >( Data ) );
            while ( Length-- )
            {
                crc = ( crc >> 8 ) ^ m_crctab[ 0 ][ ( *cp ^ crc ) & 0xFF ];
                ++cp;
            }
        }

        inline void
        crc_ldas::slice_by_8( const void* Data, size_t Length )
        {
            static const size_t SLICE = 8;
            const uint8_t*      current_byte(
                     reinterpret_cast< const uint8_t* >( Data ) );
            size_t alignment(
                ( ( ~reinterpret_cast< long >( Data ) + 1 ) & 0x03 ) );

            //-----------------------------------------------------------------
            // align on 32-bit boundry for effecient memory access
            //-----------------------------------------------------------------
            if ( alignment )
            {
                size_t l( std::min( alignment, Length ) );

                slice_by_1( Data, l, checksum_accumulator );
                Length -= l;
                current_byte += l;
            }
            //-----------------------------------------------------------------
            // process eight bytes at once (Slicing-by-8)
            //-----------------------------------------------------------------
            const value_type* current(
                reinterpret_cast< const value_type* >( current_byte ) );
            while ( Length >= SLICE )
            {
                process_eight_byte_chunck< boost::endian::order::native >(
                    current );

                Length -= SLICE;
            }

            slice_by_1( current, Length, checksum_accumulator );
        }

        typedef cksum_impl< crc_ldas > cksum_ldas;
    } // namespace Common
} // namespace FrameCPP

#endif /* FRAME_CPP__Common__CRC_LDAS_HH */
