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

#ifndef GeneralRegexHH
#define GeneralRegexHH

#if !defined( SWIGIMPORTED )
#include <string>
#include <regex.h>
#endif /* ! defined(SWIGIMPORTED) */

#include "ldasexception.hh"

//-----------------------------------------------------------------------------
/// \brief  POSIX Regular Expression
///
/// This class represents a POSIX regular expression.
///
class Regex
{
public:
    /* Constructors/Destructor */
    Regex( );
    explicit Regex( const std::string& regex, int flags = REG_EXTENDED );
    explicit Regex( const char* regex, int flags = REG_EXTENDED );
    Regex( const Regex& Source );
    ~Regex( ) throw( );

    /* Accessors */
    bool               compiled( ) const;
    const regex_t&     getPattern( ) const;
    const std::string& getRegex( ) const;

    Regex& operator=( const Regex& Source );

private:
    void compile( );

    /* Data */
    std::string mRegex;
    regex_t     mPattern;
    int         mFlags;
    bool        mCompiled;
};

//-----------------------------------------------------------------------------
/// \brief  Get compilation status
///
/// \return state of compilation
///
inline bool
Regex::compiled( ) const
{
    return mCompiled;
}

//-----------------------------------------------------------------------------
/// \brief  Get Compiled Pattern
///
/// \return const regex_t &
///
inline const regex_t&
Regex::getPattern( ) const
{
    return mPattern;
}

//-----------------------------------------------------------------------------
/// \brief  Get Regular Expression
///
/// \return const std::string&
///
inline const std::string&
Regex::getRegex( ) const
{
    return mRegex;
}

#endif // GeneralRegexHH
