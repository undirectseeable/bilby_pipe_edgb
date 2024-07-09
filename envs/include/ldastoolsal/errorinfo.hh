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

#ifndef GeneralErrorInfoHH
#define GeneralErrorInfoHH

/// System Includes
#if !defined( SWIGIMPORTED )
#include <string>
#endif /* ! defined(SWIGIMPORTED) */

//-----------------------------------------------------------------------------
/// \brief  Error Information
///
///  This class is used by the LdasException class to store information about
/// a thrown exception.
///
class ErrorInfo
{
public:
    /// \brief  Constructor
    ///
    /// \param library Library enumerated type
    /// \param code Error code
    /// \param msg String representation of error code.
    /// \param info Addition information specific to the
    ///        error
    /// \param file File in which the error was thrown.
    /// \param line Line number in file where error was thrown.
    ErrorInfo( int                library,
               int                code,
               const std::string& msg,
               const std::string& info = "",
               const char*        file = 0,
               size_t             line = 0 );

    /// \brief  Copy constructor
    /// \param e Source
    ErrorInfo( const ErrorInfo& e );

    /// Destructor
    ~ErrorInfo( );

    /// \brief  Assign
    const ErrorInfo& operator=( const ErrorInfo& e );
    bool             operator==( const ErrorInfo& e ) const;
    bool             operator!=( const ErrorInfo& e ) const;

    /* Accessors */
    int                getLibrary( ) const;
    int                getCode( ) const;
    const std::string& getMessage( ) const;
    const std::string& getInfo( ) const;
    const char*        getFile( ) const;
    size_t             getLine( ) const;

private:
    /// The library in which the error occurred (int).
    int mLibrary;
    /// The error code (int)
    int mCode;
    /// A string representation of the error code (string).
    std::string mMsg;
    /// Additional information specific to the error (string)
    std::string mInfo;
    /// The file in which the error was thrown (const char*)
    char* mFile;
    /// The line on which the error was thrown (size_t)
    size_t mLine;
};

//-----------------------------------------------------------------------------
/// \brief  Not-Equal Comparison
///
/// \param e
///
/// \return bool
///
inline bool
ErrorInfo::operator!=( const ErrorInfo& e ) const
{
    return !operator==( e );
}

//-----------------------------------------------------------------------------
/// \brief  Get Library
///
/// \return int The number of the library which threw the exception.
///
inline int
ErrorInfo::getLibrary( ) const
{
    return mLibrary;
}

//-----------------------------------------------------------------------------
/// \brief  Get Error Code
///
/// \return int
///
inline int
ErrorInfo::getCode( ) const
{
    return mCode;
}

//-----------------------------------------------------------------------------
/// \brief  Get Error Message
///
/// Returns a text representation of the error code.
///
///!return const std::string&
///
inline const std::string&
ErrorInfo::getMessage( ) const
{
    return mMsg;
}

//-----------------------------------------------------------------------------
/// \brief  Get Error Information
///
/// Returns additional information about the error.
///
/// \return const std::string&
///
inline const std::string&
ErrorInfo::getInfo( ) const
{
    return mInfo;
}

//-----------------------------------------------------------------------------
/// \brief  Get File Name
///
/// Get the name of the file in which the error was thrown.
///
/// \return const char*
///
inline const char*
ErrorInfo::getFile( ) const
{
    return mFile;
}

//-----------------------------------------------------------------------------
/// \brief  Get Line Number
///
/// Get the line number on which the error was thrown.
///
/// \return size_t
///
inline size_t
ErrorInfo::getLine( ) const
{
    return mLine;
}

#endif // GeneralErrorInfoHH
