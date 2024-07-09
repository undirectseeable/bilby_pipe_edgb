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

#ifndef General__PtrHash_HH
#define General__PtrHash_HH

#include "ldastoolsal/unordered_map.hh"

namespace LDASTools
{
    namespace AL
    {
        struct PtrHash : std::unary_function< const void*, size_t >
        {
            size_t
            operator( )( const void* Key ) const
            {
#if SIZEOF_VOIDP == SIZEOF_LONG_LONG
                typedef unsigned long long hash_type;
#elif SIZEOF_VOIDP == SIZEOF_LONG
                typedef unsigned long hash_type;
#endif
                union
                {
                    const void* s_ptr;
                    hash_type   s_hash_key;
                } hk;

                LDASTools::AL::hash< hash_type > h;

                hk.s_ptr = Key;
                hk.s_hash_key >>=
                    3; // Shift down since data should be byte aligned.
                return h( hk.s_hash_key );
            }
        };
    } // namespace AL
} // namespace LDASTools
#endif /* General__PtrHash_HH */
