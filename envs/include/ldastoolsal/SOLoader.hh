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

#ifndef LDAS__GENERAL__SO_LOADER_HH
#define LDAS__GENERAL__SO_LOADER_HH

#include <string>

namespace LDASTools
{
    namespace AL
    {
        /// \brief Dynamic library loader
        ///
        /// This allows for the abstaction of dynamic loading of a library.
        class SOLoader
        {
        public:
            typedef void* symbol_type;
            typedef void ( *function_type )( void );

            enum
            {
                SOLOADER_MANDITORY,
                SOLOADER_OPTIONAL
            };

            /// \brief Constructor
            ///
            /// \param[in] Path
            ///   Directory containing the dynamic library
            /// \param[in] LibName
            ///   Base name of the library (no standard operating system prefix
            ///   or suffix)
            ///
            /// \return
            ///   new instance of this object
            SOLoader( const std::string& Path,
                      const std::string& LibName,
                      int                Type = SOLOADER_MANDITORY );

            /// \brief Destructor
            ///
            /// Destroy resources associated with the object
            ~SOLoader( );

            /// \brief Retrieve a function from the dynamically loaded library
            ///
            /// \param[in] Function
            ///   The name of the function as it appears in the dynamic library.
            ///
            /// \return
            ///   Address of the function
            function_type GetFunction( const std::string& Function );

            /// \brief Retrieve a symbol from the dynamically loaded library
            ///
            /// \param[in] Symbol
            ///   The name of the symbol as it appears in the dynamic library.
            ///
            /// \return
            ///   Address of the symbol
            symbol_type GetSymbol( const std::string& Symbol );

        private:
            typedef void* handle_type;

            handle_type m_handle;

            SOLoader( const SOLoader& Source );

            const SOLoader& operator=( const SOLoader& Source );
        };
    } // namespace AL
} // namespace LDASTools

#endif /* LDAS__GENERAL__SO_LOADER_HH */
