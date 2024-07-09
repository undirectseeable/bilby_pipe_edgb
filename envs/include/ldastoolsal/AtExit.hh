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

#ifndef LDASTOOLSAL__AT_EXIT_HH
#define LDASTOOLSAL__AT_EXIT_HH

#include <list>

#include "ldastoolsal/Deprecated.hh"
#include "ldastoolsal/mutexlock.hh"
#include "ldastoolsal/Singleton.hh"

namespace LDASTools
{
    namespace AL
    {
        //-------------------------------------------------------------------
        /// \brief Cleanup upon exit
        ///
        /// This class keeps track of user defined cleanup routines to be
        /// called as the application exits.
        ///
        /// \deprecated
        ///     This class has been depricated because it is unsafe to call
        ///     when using share objects.
        ///     As this class was being used to deallocated resource to make
        ///     reading of valgrind output more meaningful,
        ///     please reference LDASTools::AL::MemChecker instead.
        //-------------------------------------------------------------------
        class AtExit
        {
        public:
            /// \brief  Type specifier for exit functions.
            //-----------------------------------------------------------------
            typedef void ( *ExitFunction )( );

            //-----------------------------------------------------------------
            /// \brief  Add a cleanup function to call when program is exiting.
            ///
            /// \param[in] Function
            ///     The function to be called when exiting
            ///
            /// \param[in] Name
            ///     A descriptive name of the action being taken
            ///
            /// \param[in] Ring
            ///     The level at which to call.
            ///     The ring structure is inverted in that rings of higher value
            ///     are called prior to rings of lesser values.
            ///
            /// \depricated
            //-------------------------------------------------------------------
            LDASTOOLS_DEPRECATED( )
            static void
            Append( ExitFunction Function, const std::string& Name, int Ring );

            //-----------------------------------------------------------------
            /// \brief Release all resources entrusted
            ///
            /// \depricated
            //-----------------------------------------------------------------
            LDASTOOLS_DEPRECATED( )
            static void Cleanup( );

            //-----------------------------------------------------------------
            /// \brief Query the exiting state of the system.
            ///
            /// \depricated
            //-----------------------------------------------------------------
            LDASTOOLS_DEPRECATED( )
            static bool IsExiting( );

        } LDASTOOLS_DEPRECATED(
            "use method LDASTools::AL::MemChecker instead" );
    } // namespace AL
} // namespace LDASTools

#if DEPRICATED_NAMESPACE_GENERAL
namespace General
{
    using LDASTools::AL::AtExit;
}
#endif /* DEPRICATED_NAMESPACE_GENERAL */

#endif /* LDASTOOLSAL__AT_EXIT_HH */
