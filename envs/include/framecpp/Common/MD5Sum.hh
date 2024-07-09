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

#ifndef FRAMECPP__COMMON__MD5SUM_HH
#define FRAMECPP__COMMON__MD5SUM_HH

#if !defined( SWIGIMPORTED )
#include <iostream>
#include <stdexcept>
#endif /* ! defined(SWIGIMPORTED) */

#include <boost/shared_ptr.hpp>

#include "ldastoolsal/types.hh"

namespace FrameCPP
{
    namespace Common
    {
        class MD5Sum;
    }
} // namespace FrameCPP

namespace std
{
    std::ostream& operator<<( std::ostream&                   Stream,
                              const FrameCPP::Common::MD5Sum& Data );
}

namespace FrameCPP
{
    namespace Common
    {
        class MD5Sum
        {
        public:
            typedef void*   data_type;
            typedef INT_4U  size_type;
            typedef CHAR_U* md_type;

            MD5Sum( );

            MD5Sum( const MD5Sum& Source );

            std::ostream& DumpIntermediate( std::ostream& Stream ) const;

            void Finalize( ) const;

            bool Finalized( ) const;

            void Reset( );

            void Update( const data_type Data, size_type Length );

            md_type Value( ) const;

            std::ostream& operator<<( std::ostream& Stream );

            MD5Sum& operator=( const MD5Sum& MD5 );

            bool operator==( const MD5Sum& RHS ) const;

            bool operator!=( const MD5Sum& RHS ) const;

        private:
            friend std::ostream& std::operator<<( std::ostream& stream,
                                                  const MD5Sum& Data );

            struct _state_type;

            typedef boost::shared_ptr< _state_type > state_type;

            mutable state_type state;
        };

        inline bool
        MD5Sum::operator!=( const MD5Sum& RHS ) const
        {
            return !operator==( RHS );
        }
    } // namespace Common
} // namespace FrameCPP

#endif /* FRAMECPP__COMMON__MD5SUM_HH */
