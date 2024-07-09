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

#ifndef GENERAL__BIT_VECTOR_HH
#define GENERAL__BIT_VECTOR_HH

#if defined( __SUNPRO_CC )
#include <deque>
#define LDAS_BIT_VECTOR std::deque< bool >
#else /* __SUNPRO_CC */
#include <vector>
#define LDAS_BIT_VECTOR std::vector< bool >
#endif /* __SUNPRO_CC */

namespace LDASTools
{
    namespace AL
    {
        /// \brief  Compiler independent bit_vector
        typedef LDAS_BIT_VECTOR bit_vector;
    } // namespace AL
} // namespace LDASTools

#endif /* GENERAL__BIT_VECTOR_HH */
