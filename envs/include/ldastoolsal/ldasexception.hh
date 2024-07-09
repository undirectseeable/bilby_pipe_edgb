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

#ifndef GeneralLdasExceptionHH
#define GeneralLdasExceptionHH

/// System Includes
#if !defined( SWIGIMPORTED )
#include <string>
#include <vector>
#include <stdexcept>
#endif /* ! defined(SWIGIMPORTED) */

/// Local Includes
#include "errorinfo.hh"

////----------------------------------------------------------------------
//// \brief Namespace for the different library packages
////----------------------------------------------------------------------
namespace Library
{

    //-----------------------------------------------------------------------------
    /// \brief  Libraries
    ///
    /// An enumeration of all the libraries which will be throwing LdasException
    /// errors.
    ///
    enum Lib
    {
        DISKCACHEAPI,
        FRAMEAPI,
        FRAMECPP,
        GENERAL,
        GENERICAPI,
        ILWD,
        METADATAAPI
    };

} // namespace Library

//-----------------------------------------------------------------------------
/// \brief  LDAS Exception Class
///
/// This class defines the types of exceptions thrown by the LDAS libraries.
/// The class stores multiple instances of ErrorInfo objects, allowing an
/// exception to be tracked as it is thrown and re-thrown in the code.
///
/// This class carries a lot of information with it, so it should only be used
/// to report errors.  Throwing this class should not be a normal part of the
/// program flow.
///
/// Due to the overhead, this class is probably not very good for reporting
/// memory allocation errors.
///
class LdasException
{
public:
    /* Constructors */
    LdasException( );
    explicit LdasException( int                library,
                            int                code,
                            const std::string& msg,
                            const std::string& info = "",
                            const char*        file = 0,
                            size_t             line = 0 );
    LdasException( const ErrorInfo& e );
    LdasException( const LdasException& e );

    /* Destructor */
    virtual ~LdasException( );

    /* Operator Overloads */
    LdasException& operator=( const LdasException& e );
    bool           operator==( const LdasException& e ) const;
    bool           operator!=( const LdasException& e ) const;

    /* Accessors */
    const ErrorInfo& getError( size_t i ) const;
    const ErrorInfo& operator[]( size_t i ) const;
    size_t           getSize( ) const;

    /* Mutators */
    void addError( int                library,
                   int                code,
                   const std::string& msg,
                   const std::string& info = "",
                   const char*        file = 0,
                   size_t             line = 0 );
    void addError( const ErrorInfo& e );

private:
    /* Data */
    std::vector< ErrorInfo > mErrors;
};

//-----------------------------------------------------------------------------
/// \brief  Equal Comparison
///
/// \param e
///
/// \return bool
///
inline bool
LdasException::operator==( const LdasException& e ) const
{
    return ( mErrors == e.mErrors );
}

//-----------------------------------------------------------------------------
/// \brief  Not-Equal Comparison
///
/// \param e
///
/// \return bool
///
inline bool
LdasException::operator!=( const LdasException& e ) const
{
    return ( mErrors != e.mErrors );
}

//-----------------------------------------------------------------------------
/// \brief  Get Size
///
/// Return the number of ErrorInfo objects contained in this object.
///
/// \return size_t
///
inline size_t
LdasException::getSize( ) const
{
    return mErrors.size( );
}

#endif // GeneralLdasExceptionHH
