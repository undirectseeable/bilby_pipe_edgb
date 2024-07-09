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

#ifndef GeneralUtilHH
#define GeneralUtilHH

#if !defined( SWIGIMPORTED )
#include <assert.h>
#include <string>
#include <strings.h>
#endif /* ! defined(SWIGIMPORTED) */

#include "ldastoolsal/unordered_map.hh"

//-----------------------------------------------------------------------
/// \brief Objects of general use and interst.
///
/// The objects that are described in this namespace cover a broad
/// range and are to be used by many other parts of the software.
//-----------------------------------------------------------------------
namespace LDASTools
{
    //---------------------------------------------------------------------
    /// \brief The Abstraction Layer
    ///
    /// The classes and other objects defined in this namespace are
    /// intended to provide a unified interface across multiple
    /// platforms.
    //---------------------------------------------------------------------
    namespace AL
    {
        int         cmp_nocase( const std::string& S1, const std::string& S2 );
        int         cmp_nocase( const char* lhs, const char* rhs );
        bool        is_space( const char c );
        bool        not_space( const char c );
        void        string2lower( std::string& s );
        std::string slower( const std::string& s );

#if !defined( unordered_map )

        /// \brief  Hash proto
        template < class T >
        struct ic_hash
        {
        };

        //-----------------------------------------------------------------------------
        /// \brief  Case-Insensitive String Hash Specialization
        ///
        /// A specialization of the STL hash functional to perform a
        /// case-insensitive hash of a C++ string.
        ///
        template <>
        struct ic_hash< std::string >
        {
            /// \brief  Overloaded call operator.
            ///
            /// \param s A reference to the string representing the
            ///    search key.
            ///
            /// \return size_t Index into the hash.
            ///
            std::size_t
            operator( )( const std::string& s ) const
            {
                std::string tmp( slower( s ) );
#if defined( UNORDERED_MAP_NAMESPACE )
                LDASTools::AL::hash< std::string > h;
                return h( tmp );
#else /* UNORDered_MAP_NAMESPACE */
                LDASTools::AL::hash< const CHAR* > h;
                return h( tmp.c_str( ) );
#endif /* UNORDered_MAP_NAMESPACE */
            }
        };

#endif /* unordered_map */

        void Rethrow( const std::string&    Prefix,
                      const std::exception& Exception );

        //-----------------------------------------------------------------------------
        /// \brief  Case-Insensitive Compare Functional
        ///
        /// A Function Object used to perform a case-insensitive compare of two
        /// string objects.
        ///
        class CaseInsensitiveCmp
        {
        public:
            /// \brief  Overloaded call operator.
            ///
            /// \param s1 A reference to the first string object.
            /// \param s2 A reference to the second string object.
            ///
            /// \return bool True if strings are equal, false otherwise.
            ///
            bool
            operator( )( const std::string& s1, const std::string& s2 ) const
            {
                return cmp_nocase( s1.c_str( ), s2.c_str( ) ) == 0;
            }
        };

    } // namespace AL
} // namespace LDASTools

#endif // GeneralUtilHH
