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

#ifndef LDASTOOLSAL__TIMER_THREAD_HH
#define LDASTOOLSAL__TIMER_THREAD_HH

#include <list>

#include "ldastoolsal/gpstime.hh"
#include "ldastoolsal/mutexlock.hh"
#include "ldastoolsal/Singleton.hh"
#include "ldastoolsal/SignalHandler.hh"
#include "ldastoolsal/types.hh"

namespace LDASTools
{
    namespace AL
    {
        /// \brief  Keep track of threads to be run for a specified time.
        class TimerThread : public Singleton< TimerThread >
        {
        public:
            /// \brief  Unique key
            typedef INT_4U key_t;

            TimerThread( );
            ~TimerThread( );

            key_t AddTimer( int Wakeup, SignalHandler::signal_type Signal );
            bool  RemoveTimer( key_t Key );

        private:
            //-----------------------------------------------------------------
            /// \brief Forward declaration of structure holding private data.
            ///
            /// \note
            ///      This structure is defined in the source code to
            ///      abstract the implementation.
            //-----------------------------------------------------------------
            struct p_type;
            //-----------------------------------------------------------------
            /// \brief A reference to the private data
            //-----------------------------------------------------------------
            std::unique_ptr< p_type > p_;
        };
    } // namespace AL
} // namespace LDASTools

#endif /* LDASTOOLSAL__TIMER_THREAD_HH */
