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

#ifndef GENERAL__CONDITIONAL_VARIABLE_HH
#define GENERAL__CONDITIONAL_VARIABLE_HH

#include <boost/shared_ptr.hpp>

#include "ldastoolsal/types.hh"
#include "ldastoolsal/mutexlock.hh"

namespace LDASTools
{
    namespace AL
    {
        //---------------------------------------------------------------------
        /// \brief Thread syncronization based on condition
        //---------------------------------------------------------------------
        class ConditionalVariable
        {
        public:
            //-------------------------------------------------------------------
            /// \brief Constructor - Default
            //-------------------------------------------------------------------
            ConditionalVariable( );
            //-------------------------------------------------------------------
            /// \brief Destructor
            //-------------------------------------------------------------------
            ~ConditionalVariable( );
            //-------------------------------------------------------------------
            /// \brief Awaken some thread waiting on condition
            //-------------------------------------------------------------------
            void Broadcast( );
            //-------------------------------------------------------------------
            /// \brief Return the lock associated with condition
            //-------------------------------------------------------------------
            MutexLock::baton_type Mutex( );
            //-------------------------------------------------------------------
            /// \brief Release lock associated with condition.
            //-------------------------------------------------------------------
            void Release( );
            //-------------------------------------------------------------------
            /// \brief Awaken a blocked thread
            //-------------------------------------------------------------------
            void Signal( );
            //-------------------------------------------------------------------
            /// \brief Timed block on condition
            //-------------------------------------------------------------------
            bool TimedWait( INT_4U Seconds );
            //-------------------------------------------------------------------
            /// \brief Block on condition
            //-------------------------------------------------------------------
            void Wait( );

        private:
            class impl;
            boost::shared_ptr< impl > pimpl_;

            ConditionalVariable( const ConditionalVariable& Source );
            ConditionalVariable& operator=( const ConditionalVariable& Source );
        };
    } // namespace AL
} // namespace LDASTools

#endif /* GENERAL__CONDITIONAL_VARIABLE_HH */
