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

#ifndef LDASTOOLSAL__TASK_TIMER_HH
#define LDASTOOLSAL__TASK_TIMER_HH

#include "ldastoolsal/Task.hh"

namespace LDASTools
{
    namespace AL
    {
        //-------------------------------------------------------------------
        /// \brief Give a task a maximum amount of time to complete
        ///
        /// This class ensures that a task completes within a given amount
        /// of time.
        /// If the task does not complete, the it is canceled using the
        /// registered cancellation signal.
        //-------------------------------------------------------------------
        class Timer : public Task
        {
        public:
            //-----------------------------------------------------------------
            /// \brief Constructor
            ///
            /// \param[in] Seconds
            ///     Number of seconds to allow task to complete
            ///
            /// \param[in] CancelSignal
            ///     Signal to use to cancel this timer.
            //-----------------------------------------------------------------
            Timer( int         Seconds,
                   signal_type CancelSignal = SignalHandler::SIGNAL_UNKNOWN );
            //-----------------------------------------------------------------
            /// \brief Action
            //-----------------------------------------------------------------
            virtual void operator( )( );
            //-----------------------------------------------------------------
            /// \brief True if time ran out for the process to complete.
            //-----------------------------------------------------------------
            bool Error( ) const;

        private:
            int  m_timeout;
            bool m_err;
        };
    } // namespace AL
} // namespace LDASTools

#endif /* LDASTOOLSAL__TASK_TIMER_HH */
