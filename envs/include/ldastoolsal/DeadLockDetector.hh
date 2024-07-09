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

#ifndef GENERAL__DEAD_LOCK_DETECTOR_HH
#define GENERAL__DEAD_LOCK_DETECTOR_HH

#define DEAD_LOCK_DETECTOR_ENABLED 0

#if DEAD_LOCK_DETECTOR_ENABLED

#include <list>

#if DEAD_LOCK_DETECTOR_USES_UNORDERED_MAP
#include "ldastoolsal/unordered_map.hh"
#else /* DEAD_LOCK_DETECTOR_USES_UNORDERED_MAP */
#include <map>
#endif /* DEAD_LOCK_DETECTOR_USES_UNORDERED_MAP */

#include "ldastoolsal/gpstime.hh"
#include "ldastoolsal/mutexlock.hh"
#include "ldastoolsal/ReadWriteLock.hh"

namespace LDASTools
{
    namespace AL
    {
        class DeadLockDetector
        {
        public:
            typedef pthread_t thread_type;
            typedef enum
            {
                MUTEX,
                RW_READ,
                RW_WRITE,
                UNSPECIFIED
            } lock_class_type;

            typedef enum
            {
                INITIALIZED,
                PENDING,
                ACQUIRED,
                RELEASED,
                ACQUISITION_ERROR
            } state_type;

            struct state_info_type
            {
                lock_class_type s_lock_type;
                state_type      s_state;
                void*           s_lock;
                int             s_error;
                const char*     s_filename;
                unsigned int    s_linenumber;

                state_info_type( void*           LockPtr,
                                 lock_class_type LockType,
                                 state_type      LockState,
                                 const char*     Filename,
                                 int             LineNumber )
                    : s_lock_type( LockType ), s_state( LockState ),
                      s_lock( LockPtr ), s_filename( Filename ),
                      s_linenumber( LineNumber )
                {
                }
            };

            static void Dump( );

            static std::ostream&
            DumpWithoutLocking( std::ostream& Stream = std::cerr );

            static int SetDebugging( int Value );

            static void SetState( lock_class_type       Lock,
                                  MutexLock::baton_type MutexPtr,
                                  state_type            State,
                                  const char*           Filename = "",
                                  unsigned int          LineNum = 0 );

            static void SetState( state_info_type& Info );

#if HAVE_PTHREAD_RW_LOCK
            static void SetState( lock_class_type           Lock,
                                  ReadWriteLock::baton_type LockPtr,
                                  state_type                State,
                                  const char*               Filename = "",
                                  unsigned int              LineNum = 0 );
#endif /* HAVE_PTHREAD_RW_LOCK */

            static void ThreadRegister( thread_type        Thread,
                                        const std::string& Desc = "" );

            static void ThreadUnregister( thread_type Thread );

        private:
            static void set_state( state_info_type& Info );
        };

        inline void
        DeadLockDetector::SetState( state_info_type& Info )
        {
            set_state( Info );
        }

    } // namespace AL
} // namespace LDASTools
#endif /* DEAD_LOCK_DETECTOR_ENABLED */
#endif /* GENERAL__DEAD_LOCK_DETECTOR_HH */
