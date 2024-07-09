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

#ifndef RegexMatchHH
#define RegexMatchHH

#if !defined( SWIGIMPORTED )
#include <cstddef>
#endif /* ! defined(SWIGIMPORTED) */

#include "regex.hh"

//-----------------------------------------------------------------------------
/// \brief  Regular Expression Match
///
/// This class represents a regular expression match.  It attempts to match a
/// string with a regular expression, storing the information resulting from
/// captures (the parenthesis expressions).
///
class RegexMatch
{
public:
    typedef size_t off_type;
    typedef int    flag_type;

    /* Constructor/Destructor */
    RegexMatch( off_type nmatches = 0 );
    ~RegexMatch( );

    /* Regex Match */
    bool match( const Regex& r, const char* string, flag_type eflags = 0 );

    //---------------------------------------------------------------------
    // \brief Return the maximum number of matches
    //---------------------------------------------------------------------
    off_type capacity( ) const;

    //---------------------------------------------------------------------
    // \brief Return the number of matches actually found
    //---------------------------------------------------------------------
    off_type size( ) const;

    /* Accessors */
    bool        isSubValid( off_type m );
    const char* getSubStart( off_type m );
    const char* getSubEnd( off_type m );
    int         getSubStartOffset( off_type m );
    int         getSubEndOffset( off_type m );
    off_type    getSubLength( off_type m );
    std::string getSubString( off_type m );
    off_type    getNMatches( ) const;

private:
    /* Data */
    regmatch_t* mMatches;
    off_type    mNMatches;
    const char* mString;
    off_type    found;
};

//-----------------------------------------------------------------------
/// Returns the maximum number of matches which this object can hold.
///  This is equal to the number of matches which was passed to the
///   constructor.
///
/// \return off_type
//-----------------------------------------------------------------------
inline RegexMatch::off_type
RegexMatch::capacity( ) const
{
    return mNMatches;
}

//-----------------------------------------------------------------------
/// Returns the number of matches that were found after the
///   call to match()
///
/// \return off_type
//-----------------------------------------------------------------------
inline RegexMatch::off_type
RegexMatch::size( ) const
{
    return found;
}

//-----------------------------------------------------------------------------
/// \brief  Check Substring Match Validity
///
/// This returns whether or not a substring match exists at the specified index.
///
/// \param m
///
/// \return bool
///
inline bool
RegexMatch::isSubValid( off_type m )
{
    return ( ( m < mNMatches ) && ( mMatches[ m ].rm_so != -1 ) );
}

//-----------------------------------------------------------------------------
/// \brief  Get Substring Start
///
/// Returns a pointer to the beginning of a substring match.  If the requested
/// match is not valid, a null pointer is returned.
///
/// \param m
///
/// \return const char*
///
inline const char*
RegexMatch::getSubStart( off_type m )
{
    if ( !isSubValid( m ) )
    {
        return 0;
    }

    return mString + mMatches[ m ].rm_so;
}

//-----------------------------------------------------------------------------
/// \brief  Get Substring End
///
/// Returns a pointer to the end of a substring match.  If the requested
/// match is not valid, a null pointer is returned.
///
/// \param m
///
/// \return const char*
///
inline const char*
RegexMatch::getSubEnd( off_type m )
{
    if ( !isSubValid( m ) )
    {
        return 0;
    }

    return mString + mMatches[ m ].rm_eo;
}

//-----------------------------------------------------------------------------
/// \brief  Get Substring Starting Offset
///
/// Returns the offset to the beginning of a substring match.  If the requested
/// match is not valid, then -1 is returned.
///
/// \param m
///
/// \return const char*
///
inline int
RegexMatch::getSubStartOffset( off_type m )
{
    if ( !isSubValid( m ) )
    {
        return -1;
    }

    return mMatches[ m ].rm_so;
}

//-----------------------------------------------------------------------------
/// \brief  Get Substring Ending Offset
///
/// Returns the offset to the end of a substring match.  If the requested
/// match is not valid, then -1 is returned.
///
/// \param m
///
/// \return const char*
///
inline int
RegexMatch::getSubEndOffset( off_type m )
{
    if ( !isSubValid( m ) )
    {
        return -1;
    }

    return mMatches[ m ].rm_eo;
}

//-----------------------------------------------------------------------------
/// \brief  Get Substring Length
///
/// Returns the number of characters in a substring match.
///
/// \param m
///
/// \return off_type
///
inline RegexMatch::off_type
RegexMatch::getSubLength( off_type m )
{
    return ( getSubEndOffset( m ) - getSubStartOffset( m ) );
}

//-----------------------------------------------------------------------------
/// \brief  Get Number of Matches
///
/// Returns the maximum number of matches which this object can hold.  This is
/// equal to the number of matches which was passed to the constructor.
///
/// \return off_type
///
inline RegexMatch::off_type
RegexMatch::getNMatches( ) const
{
    return mNMatches;
}

#endif // RegexMatchHH
