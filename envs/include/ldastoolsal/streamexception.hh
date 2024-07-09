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

#ifndef GeneralStreamExceptionHH
#define GeneralStreamExceptionHH

#include <iostream>

#include "ldasexception.hh"

//-----------------------------------------------------------------------------
/// \brief  Stream Exception
///
class StreamException : public LdasException
{
public:
    /// \brief  Enumerated type classifying the type of stream errors.
    enum Error
    {
        BAD_STREAM = 0,
        FAIL_STREAM,
        END_OF_FILE,
        UNKNOWN_ERROR
    };

    /* Constructors */
    StreamException( std::istream&      in,
                     int                library,
                     const std::string& info,
                     const char*        file = 0,
                     size_t             line = 0 );
    StreamException( std::ostream&      out,
                     int                library,
                     const std::string& info,
                     const char*        file = 0,
                     size_t             line = 0 );
    StreamException( int                library,
                     int                code,
                     const std::string& message,
                     const std::string& info,
                     const char*        file = 0,
                     size_t             line = 0 ) throw( );
};

//-----------------------------------------------------------------------------
/// \brief  Constructor.
///
/// \param library Name of library or api casuing the excption
/// \param code Code for the exception
/// \param message Text message describing the exception
/// \param info Additional information about the exception
/// \param file Name of the file where the exception was thrown
/// \param line Line number of the file where the exception was thrown
///
inline StreamException::StreamException( int                library,
                                         int                code,
                                         const std::string& message,
                                         const std::string& info,
                                         const char*        file,
                                         size_t             line ) throw( )
    : LdasException( library, code, message, info, file, line )
{
}

#endif // GeneralStreamExceptionHH
