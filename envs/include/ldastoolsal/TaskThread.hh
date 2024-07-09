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

#ifndef LDASTOOLSAL__TASK_THREAD_HH
#define LDASTOOLSAL__TASK_THREAD_HH

#include "ldastoolsal/ConditionalVariable.hh"
#include "ldastoolsal/Thread.hh"
#include "ldastoolsal/Task.hh"

namespace LDASTools
{
    namespace AL
    {
        class TaskThread : public Thread
        {
        public:
            enum state_type
            {
                TASK_THREAD_NOT_STARTED,
                TASK_THREAD_SLEEPING,
                TASK_THREAD_RUNNING,
                TASK_THREAD_TIMEDOUT,
                TASK_THREAD_FINISHED,
                TASK_THREAD_EXITING
            };

            typedef Thread::cancel_type cancel_method;
            typedef Thread::signal_type task_signal_type;

            TaskThread( );
            virtual ~TaskThread( );
            void AddTask( Task& TaskToDo );
            void AddTask( Task* TaskToDo );
            void CriticalSection( bool );

            bool                  Halt( );
            MutexLock::baton_type Mutex( );
            enum state_type       State( ) const;
            static std::string    StateStr( enum state_type Value );
            bool                  TimedOut( );
            void                  TimedWait( int Seconds );
            void                  Wait( );

            const char* Type( ) const;

            Task::name_type Name( ) const;

        private:
            bool                m_done;
            ConditionalVariable m_task_available;
            Task*               m_task;
            const char*         m_task_type_name;
            Task::name_type     task_name;
            cancel_method       m_cancel_method;
            task_signal_type    m_cancel_signal;
            state_type          m_state;

            virtual void action( );

            TaskThread( const TaskThread& Source );
            TaskThread& operator=( const TaskThread& Source );
        };

        inline void
        TaskThread::AddTask( Task& TaskToDo )
        {
            AddTask( &TaskToDo );
        }

        inline MutexLock::baton_type
        TaskThread::Mutex( )
        {
            return m_task_available.Mutex( );
        }

        inline Task::name_type
        TaskThread::Name( ) const
        {
            return task_name;
        }

        inline enum TaskThread::state_type
        TaskThread::State( ) const
        {
            return m_state;
        }

        inline bool
        TaskThread::TimedOut( )
        {
            CriticalSection( true );
            bool retval( m_state == TASK_THREAD_TIMEDOUT );
            CriticalSection( false );

            return retval;
        }

        inline const char*
        TaskThread::Type( ) const
        {
            return m_task_type_name;
        }

    } // namespace AL
} // namespace LDASTools

#endif /* LDASTOOLSAL__TASK_THREAD_HH */
