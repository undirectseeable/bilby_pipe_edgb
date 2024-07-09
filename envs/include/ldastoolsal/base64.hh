//
// LDASTools AL - A library collection to provide an abstraction layer
//
// Copyright (C) 2018 California Institute of Technology
//
// LDASTools AL is free software; you may redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 (GPLv2) of the
// License or at your discretion, any later version.
//
// LDASTools AL is distributed in the hope that it will be useful, but
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

#ifndef GeneralBase64HH
#define GeneralBase64HH

#include <stdlib.h>
#include <string>

#include "ldastoolsal/bit_vector.hh"

//-----------------------------------------------------------------------------
/// \brief  Base 64 Conversion
///
/// This class is used to convert to and from Base 64.  Base 64 is a way to
/// encode binary data using printable ASCII characters.  It uses 4 characters
/// for every 3 bytes.
///
/// This is a static class.
///
class Base64
{
public:
    typedef LDASTools::AL::bit_vector bit_vector;

    /* Conversion */

    /// \brief  Encode bit_vector
    static size_t encode( std::string& Destination, const bit_vector& Source );
    /// \brief  Encode generic 8 bit data
    static size_t encode( char* destination, const void* source, size_t size );

    /// \brief  Decode bit_vector
    static size_t decode( bit_vector& Destination, const std::string& Source );
    /// \brief  Decode generic 8 bit data
    static size_t decode( void* destination, const char* source );

    /* Size Calculation */
    /// \brief  Compute number of output bytes given the number of input bytes
    static size_t calculateEncodedSize( size_t bytes );
    /// \brief  Compute number of output bytes given a null terminated string
    static size_t calculateDecodedSize( const char* s );

    // Helper

    /// \brief  Establish the number of characters per line
    static void setNumCharactersPerLine( const int num );

private:
    /* Helper ---------------------------------------------------------- */

    /// \brief  Get next Base64 value
    static bool getChar( const char** source, unsigned char& c );

    /* Data ------------------------------------------------------------ */

    /// \brief  Base 64 translation table
    static const char* mTable;

    /// \brief  Number of characters per line
    static int mCharsPerLine;
};

#endif // GeneralBase64HH
