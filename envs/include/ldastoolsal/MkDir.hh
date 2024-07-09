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

#ifndef GENERAL__CMD__MKDIR_HH
#define GENERAL__CMD__MKDIR_HH

#include <string>

namespace LDASTools
{
    namespace Cmd
    {
        class MkDir
        {
        public:
            typedef int mode_type;
            typedef int option_type;

            enum options
            {
                OPT_NONE = 0,
                OPT_MAKE_PARENT_DIRECTORIES = 0x0001
            };

            //-----------------------------------------------------------------
            /// \brief Constructor
            ///
            /// \param[in] Mode
            ///     Mode for the created directory.
            /// \param[in] Options
            ///     Options for the created directory.
            //-----------------------------------------------------------------
            MkDir( mode_type Mode, option_type Options = OPT_NONE );

            //-----------------------------------------------------------------
            ///
            //-----------------------------------------------------------------
            void operator( )( const std::string& Directory ) const;

            static const char PATH_SEP;

        private:
            mode_type mode;

            void eval( const std::string& Directory ) const;
        };
    } // namespace Cmd
} // namespace LDASTools

#endif /* GENERAL__CMD__MKDIR_HH */
