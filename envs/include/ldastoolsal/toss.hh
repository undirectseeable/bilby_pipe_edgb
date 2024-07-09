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

#ifndef TOSS_HH
#define TOSS_HH

#include <string>

namespace LDASTools
{
    namespace Error
    {
        //-------------------------------------------------------------------
        /// \brief  Helper function for throwing standard exceptions
        ///
        /// \param[in] ClassName
        ///     The class throwing the exception, as a string.
        /// \param[in] Filename
        ///     The program unit where the exception is thrown
        /// \param[in] LineNumber
        ///	    The line number in the file where exception is thrown
        /// \param[in] Description
        ///	    A short description of the exceptional condition
        //-------------------------------------------------------------------
        template < class T >
        void toss( const std::string& ClassName,
                   const std::string& Filename,
                   int                LineNumber,
                   const std::string& Description );
    } // namespace Error
} // namespace LDASTools

#endif // TOSS_HH
