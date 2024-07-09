//
// LDASTools frameCPP - A library implementing the LIGO/Virgo frame
// specification
//
// Copyright (C) 2022 California Institute of Technology
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

#ifndef FRAME_CPP__Common__CKSUM_HH
#define FRAME_CPP__Common__CKSUM_HH

#if !SWIGIMPORTED

namespace FrameCPP
{
    namespace Common
    {
        ///--------------------------------------------------------------
        /// @brief Compute CRC checksum with length encoding
        ///
        /// This implements the calculation of a CRC checksum with
        /// the addition of the number of bytes at the end.
        ///--------------------------------------------------------------
        template < typename CRC >
        class cksum_impl : protected CRC
        {
        public:
            /// CRC algorithm
            typedef CRC crc_type;
            /// Type which holds the number of bytes processed
            typedef std::size_t size_type;
            /// Type to hold the calculated checksum
            typedef uint32_t value_type;

            ///----------------------------------------------------------
            /// @brief Updates the interim CRC.
            ///
            /// @param[in] buffer
            ///   Buffer of bytes to be applied to the interim CRC
            /// @param[in] byte_count
            ///   Number of bytes in buffer to be applied to the interim CRC
            ///----------------------------------------------------------
            inline void
            process_bytes( void const* buffer, size_type byte_count )
            {
                if ( !finished )
                {
                    CRC::process_bytes( buffer, byte_count );
                    length += byte_count;
                }
            }

            ///----------------------------------------------------------
            /// @brief Retrieve the CRC value
            ///
            /// @return
            ///   The calculated CRC value
            ///----------------------------------------------------------
            inline value_type
            checksum( ) const
            {
                const_cast< cksum_impl* >( this )->finalize( );
                return ( CRC::checksum( ) );
            }

            ///----------------------------------------------------------
            /// @brief Allow the stucture to be reused
            ///
            /// This method resets the CRC state back to its initial
            ///   configuration allowing it to be used to calculate
            ///   a new CRC checksum.
            ///----------------------------------------------------------
            inline void
            reset( )
            {
                CRC::reset( );
                length = 0;
                finished = false;
            }

        private:
            size_type length = 0; ///< Number of bytes processed
            bool      finished = false; ///< Keep track of state

            ///----------------------------------------------------------
            /// @brief Finish calculating the checksum
            ///
            /// As part of calculating the checksum, the length is
            ///   added to final calculation
            ///----------------------------------------------------------
            inline void
            finalize( )
            {
                if ( !finished )
                {
                    unsigned char tmp[ sizeof( size_type ) ];
                    int           nzlen = 0;
                    size_type     restlen = length;

                    while ( restlen )
                    {
                        tmp[ nzlen++ ] = restlen & 0xff;
                        restlen >>= 8;
                    }
                    CRC::process_bytes( tmp, nzlen );
                    finished = true;
                }
            }
        }; // namespace Common

    }; // namespace Common

} // namespace FrameCPP

#endif /* !SWIGIMPORTED */

#endif /* FRAME_CPP__Common__CKSUM_HH */
