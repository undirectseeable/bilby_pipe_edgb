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

#ifndef LDASTOOLSAL__TASK_HH
#define LDASTOOLSAL__TASK_HH

#include <boost/shared_ptr.hpp>

#include "ldastoolsal/mutexlock.hh"
#include "ldastoolsal/Thread.hh"

namespace LDASTools
{
    namespace AL
    {
        //--------------------------------------------------------------------
        /// \brief A unit of work to be done usually within a thread.
        ///
        /// This is an abstract class that should be used as the base
        /// for a class that is to perform some task usually within
        /// a thread.
        //--------------------------------------------------------------------
        class Task
        {
        public:
            typedef boost::shared_ptr< char > name_type;
            typedef Thread::cancel_type       cancel_method;

            //-----------------------------------------------------------------
            /// \brief Data class for passing signal information
            //-----------------------------------------------------------------
            typedef Thread::signal_type signal_type;

            //-----------------------------------------------------------------
            /// \brief Constructor
            ///
            /// \param[in] Name
            ///     Sudo unique name identifying the task
            /// \param[in] CancelMethod
            ///     Method to use when terminating the task
            /// \param[in] CancelSignal
            ///     Signal to use for termination of the task
            //-----------------------------------------------------------------
            Task( const std::string& Name,
                  cancel_method      CancelMethod = Thread::CANCEL_ABANDON,
                  signal_type CancelSignal = SignalHandler::SIGNAL_UNKNOWN );

            //-----------------------------------------------------------------
            /// \brief Destructor
            //-----------------------------------------------------------------
            virtual ~Task( );

            //-----------------------------------------------------------------
            /// \brief Retrieve baton to gain exclusive access
            //-----------------------------------------------------------------
            MutexLock::baton_type Baton( ) const;

            //-----------------------------------------------------------------
            /// \brief Retrieve method to use for terminating the task.
            ///
            /// \return
            ///     The method to be used to terminate the task.
            //-----------------------------------------------------------------
            cancel_method CancelMethod( ) const;

            //-----------------------------------------------------------------
            /// \brief Retrieve signal to use for terminating the task.
            ///
            /// \return
            ///     The signal to be used to terminate the task.
            //-----------------------------------------------------------------
            signal_type CancelSignal( ) const;

            //-----------------------------------------------------------------
            /// \brief Retrieve state information concearning deletion.
            ///
            /// \return
            ///    True if the task should be deleted once terminated.
            //-----------------------------------------------------------------
            bool DeleteOnCompletion( ) const;

            //-----------------------------------------------------------------
            /// \brief Action to be done when task completes
            //-----------------------------------------------------------------
            virtual void OnCompletion( int TaskThreadState );

            //-----------------------------------------------------------------
            /// \brief Get the name of the current task
            //-----------------------------------------------------------------
            name_type TaskName( ) const;

            //-----------------------------------------------------------------
            /// \brief Action to perform
            //-----------------------------------------------------------------
            virtual void operator( )( ) = 0;

        protected:
            void taskName( const std::string& Name );

            void delete_on_completion( bool Value );

        private:
            struct _p_type;

            name_type                  name;
            std::unique_ptr< _p_type > _p;
        };

        inline Task::name_type
        Task::TaskName( ) const
        {
            return name;
        }

        inline void
        Task::taskName( const std::string& Name )
        {
            name.reset( ::strdup( Name.c_str( ) ) );
        }
    } // namespace AL
} // namespace LDASTools

#endif /* LDASTOOLSAL__TASK_HH */
