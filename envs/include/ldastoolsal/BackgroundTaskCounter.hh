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

#ifndef LDASTOOLSAL__BACKGROUND_TASK_COUNTER_HH
#define LDASTOOLSAL__BACKGROUND_TASK_COUNTER_HH

#include "ldastoolsal/types.hh"
#include "ldastoolsal/mutexlock.hh"
#include "ldastoolsal/ConditionalVariable.hh"

namespace LDASTools
{
    namespace AL
    {
        class BackgroundTaskCounter
        {
        public:
            BackgroundTaskCounter( );

            INT_4U Active( );

            void CriticalSection( bool Value );

            void Decrement( );

            void DecrementOnly( );

            void Increment( );

            void Wait( );

        private:
            LDASTools::AL::ConditionalVariable m_sync;
            MutexLock::baton_type              m_baton;
            INT_4U                             m_count;
        };

        inline BackgroundTaskCounter::BackgroundTaskCounter( ) : m_count( 0 )
        {
        }

        inline INT_4U
        BackgroundTaskCounter::Active( )
        {
            MutexLock l( m_baton, __FILE__, __LINE__ );

            return m_count;
        }

        inline void
        BackgroundTaskCounter::CriticalSection( bool Value )
        {
            if ( Value )
            {
                m_sync.Mutex( ).Lock( __FILE__, __LINE__ );
            }
            else
            {
                m_sync.Mutex( ).Unlock( __FILE__, __LINE__ );
            }
        }

        inline void
        BackgroundTaskCounter::Decrement( )
        {
            CriticalSection( true );
            DecrementOnly( );
            m_sync.Broadcast( );
            CriticalSection( false );
        }

        inline void
        BackgroundTaskCounter::DecrementOnly( )
        {
            MutexLock l( m_baton, __FILE__, __LINE__ );

            if ( m_count )
            {
                --m_count;
            }
        }

        inline void
        BackgroundTaskCounter::Increment( )
        {
            MutexLock l( m_baton, __FILE__, __LINE__ );

            ++m_count;
        }

        inline void
        BackgroundTaskCounter::Wait( )
        {
            m_sync.Wait( );
        }

    } // namespace AL
} // namespace LDASTools

#endif /* LDASTOOLSAL__BACKGROUND_TASK_COUNTER_HH */
