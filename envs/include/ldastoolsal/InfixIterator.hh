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

#ifndef LDASTOOLSAL__INFIX_ITERATOR_HH
#define LDASTOOLSAL__INFIX_ITERATOR_HH

#include <ostream>
#include <iterator>

namespace LDASTools
{
    namespace AL
    {
        template < class T,
                   class charT = char,
                   class traits = std::char_traits< charT > >

        class infix_ostream_iterator
            : public std::
                  iterator< std::output_iterator_tag, void, void, void, void >
        {
            std::basic_ostream< charT, traits >* os;
            charT const*                         delimiter;
            bool                                 first_elem;

        public:
            typedef charT                               char_type;
            typedef traits                              traits_type;
            typedef std::basic_ostream< charT, traits > ostream_type;

            infix_ostream_iterator( ostream_type& s )
                : os( &s ), delimiter( 0 ), first_elem( true )
            {
            }

            infix_ostream_iterator( ostream_type& s, charT const* d )
                : os( &s ), delimiter( d ), first_elem( true )
            {
            }

            infix_ostream_iterator< T, charT, traits >&
            operator=( T const& item )
            {
                // Here's the only real change from ostream_iterator:
                // We don't print the delimiter the first time. After that,
                // each invocation prints the delimiter *before* the item, not
                // after. As a result, we only get delimiters *between* items,
                // not after every one.
                if ( ( !first_elem ) && ( delimiter != 0 ) )
                {
                    *os << delimiter;
                }
                *os << item;
                first_elem = false;
                return *this;
            }

            infix_ostream_iterator< T, charT, traits >& operator*( )
            {
                return *this;
            }

            infix_ostream_iterator< T, charT, traits >&
            operator++( )
            {
                return *this;
            }

            infix_ostream_iterator< T, charT, traits >&
            operator++( int )
            {
                return *this;
            }
        }; // class - infix_ostream_iterator
    } // namespace AL
} // namespace LDASTools

#endif /* LDASTOOLSAL__INFIX_ITERATOR_HH */
