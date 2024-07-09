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

#ifndef LDASTOOLSAL__MEM_CHECKER_HH
#define LDASTOOLSAL__MEM_CHECKER_HH

#include <list>
#include <string>

namespace LDASTools
{
    namespace AL
    {
        //-------------------------------------------------------------------
        /// \brief Memory garbage collector
        ///
        /// This class keeps track of user defined cleanup routines to be
        /// called.
        ///
        /// \todo Put in code snippet
        //-------------------------------------------------------------------
        class MemChecker
        {
        public:
            //-----------------------------------------------------------------
            /// \brief Trigger garbage collection upon deletion.
            //-----------------------------------------------------------------
            class Trigger
            {
            public:
                //---------------------------------------------------------------
                /// \brief Default Constructor
                ///
                /// \param[in] Final
                ///     True if this trigger is to be considered the final
                ///     cleanup trigger.
                //---------------------------------------------------------------
                Trigger( bool Final = false );

                //---------------------------------------------------------------
                /// \brief Destructor
                //---------------------------------------------------------------
                ~Trigger( );

                //---------------------------------------------------------------
                /// \brief Force early garbage collection
                //---------------------------------------------------------------
                void DoGarbageCollection( ) const;

                //---------------------------------------------------------------
                /// \brief Determine if a trigger is registered for cleanup
                //---------------------------------------------------------------
                static bool IsRegistered( );

            private:
                static bool registered;

                bool final;
            };
            //-----------------------------------------------------------------
            /// \brief  Type specifier for exit functions.
            //-----------------------------------------------------------------
            typedef void ( *CleanupFunction )( );

            //-----------------------------------------------------------------
            /// \brief  Add a cleanup function to call.
            ///
            /// \param[in] Function
            ///     The function to be called
            ///
            /// \param[in] Name
            ///     A descriptive name of the action being taken
            ///
            /// \param[in] Ring
            ///     The level at which to call.
            ///     The ring structure is inverted in that rings of higher value
            ///     are called prior to rings of lesser values.
            //-------------------------------------------------------------------
            static void Append( CleanupFunction    Function,
                                const std::string& Name,
                                int                Ring,
                                bool               Always = false );

            //-----------------------------------------------------------------
            /// \brief Query the exiting state of the system.
            //-----------------------------------------------------------------
            static bool IsExiting( );

            //-----------------------------------------------------------------
            /// \brief Debugger routine
            //-----------------------------------------------------------------
            static void Info( );

        private:
            friend class Trigger;
            //-----------------------------------------------------------------
            /// \brief Release all resources entrusted
            //-----------------------------------------------------------------
            static void cleanup( );

            //-----------------------------------------------------------------
            /// \brief Set the exit status for other to query.
            ///
            /// \param[in] Value
            ///     New value for exiting status.
            //-----------------------------------------------------------------
            static void is_exiting( bool Value );
        };

        inline bool
        MemChecker::Trigger::IsRegistered( )
        {
            return registered;
        }
    } // namespace AL
} // namespace LDASTools

#endif /* LDASTOOLSAL__MEM_CHECKER_HH */
