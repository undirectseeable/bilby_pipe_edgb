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

#ifndef LDAS_TOOLS_AL__DEPRECATED_HH
#define LDAS_TOOLS_AL__DEPRECATED_HH

#if defined( __GNUC__ )
// 4.5 and above support "use instead" messaging
#if __GNUC__ > 4 || ( __GNUC__ == 4 ) && ( __GNUC_MINOR__ >= 5 )
#define LDASTOOLS_DEPRECATED( msg ) __attribute__( ( deprecated( msg ) ) )
#else /* GNU < 4.5 */
#define LDASTOOLS_DEPRECATED( msg ) __attribute__( ( deprecated ) )
#endif /* GNU >= 4.5 */
#elif defined( _MSC_VER )
#define LDASTOOLS_DEPRECATED( msg ) __declspec( deprecated )
#else
#define LDASTOOLS_DEPRECATED( a )
#endif

#endif /* LDAS_TOOLS_AL__DEPRECATED_HH */
