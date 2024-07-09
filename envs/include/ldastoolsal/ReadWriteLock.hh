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

#ifndef GENERAL__READ_WRITE_LOCK_HH
#define GENERAL__READ_WRITE_LOCK_HH

#include <cassert>

#include <stdexcept>
#include <string>

#include <boost/shared_ptr.hpp>

#include "ldastoolsal/unordered_map.hh"

namespace LDASTools
{
    namespace AL
    {
        //-------------------------------------------------------------------
        /// \class ReadWriteLock
        ///
        /// \brief Implements read/write lock symantics
        ///
        /// This class provides proper garbage collection of system
        /// resource used to implement thread safe read/write locks.
        ///
        /// \code{.cpp}
        /// ReadWriteLock::baton_type	baton;
        ///
        /// void
        /// threaded_func()
        /// {
        ///   ReadWriteLock	lock( baton, ReadWriteLock::WRITE,
        ///                       __FILE__, __LINE__ );
        ///   // modify things that should only be done by a single thread
        ///   ...
        ///   // As lock goes out of scope, the destructor is called
        ///   // thereby releasing lock held on baton.
        /// }
        /// \endcode
        ///
        //-------------------------------------------------------------------
        class ReadWriteLock
        {
        public:
            //-----------------------------------------------------------------
            /// \brief Busy lock error
            ///
            /// This error is produced when a task requests to exclusively
            /// lock a resource that is currently locked in a non-blocking
            /// mode.
            //-----------------------------------------------------------------
            class BusyError : public std::runtime_error
            {
            public:
                //---------------------------------------------------------------
                /// \brief Constructor
                //---------------------------------------------------------------
                BusyError( );

            private:
                //---------------------------------------------------------------
                /// \brief Produce the contents of the message string.
                ///
                /// \return
                ///     The contents of the message string.
                //---------------------------------------------------------------
                static std::string msg( );
            };

            //-----------------------------------------------------------------
            /// \brief Deadlock error
            ///
            /// This error is procuded when a task requests a lock that would
            /// result in a deadlock situation.
            //-----------------------------------------------------------------
            class DeadLockError : public std::runtime_error
            {
            public:
                //---------------------------------------------------------------
                /// \brief Constructor
                //---------------------------------------------------------------
                DeadLockError( );

            private:
                //---------------------------------------------------------------
                /// \brief Produce the contents of the message string.
                ///
                /// \return
                ///     The contents of the message string.
                //---------------------------------------------------------------
                static std::string msg( );
            };

            //-----------------------------------------------------------------
            /// \brief Time out error
            ///
            /// This error is procuded when a task requests a lock with a
            /// a time limit and that time limit is reached before the lock
            /// can be given.
            //-----------------------------------------------------------------
            class TimedoutError : public std::runtime_error
            {
            public:
                //---------------------------------------------------------------
                /// \brief Constructor
                //---------------------------------------------------------------
                TimedoutError( );

            private:
                //---------------------------------------------------------------
                /// \brief Produce the contents of the message string.
                ///
                /// \return
                ///     The contents of the message string.
                //---------------------------------------------------------------
                static std::string msg( );
            };

            //-----------------------------------------------------------------
            /// \brief Lock mode
            //-----------------------------------------------------------------
            typedef enum lock_mode
            {
                NONE = 0x0000, /// < Initial mode
                READ = 0x0001, /// < Read lock allows multiple concurrent reads.
                WRITE = 0x0002 /// < Write lock allows exclusive access.
            } mode_type;

            //-----------------------------------------------------------------
            /// \brief Lock state
            //-----------------------------------------------------------------
            enum lock_state
            {
                STATE_NONE = 0x0000, /// < Initial state
                PENDING = 0x0001, /// < Lock requested
                ACTIVE = 0x0002 /// < Lock granted
            };

            //-----------------------------------------------------------------
            /// \brief Manager of the read/write lock resource.
            //-----------------------------------------------------------------
            class baton_type
            {
            public:
                class impl;

                //---------------------------------------------------------------
                /// \brief Constructor
                ///
                /// \param[in] Logging
                ///     If true, then all actions associated with this instance
                ///     will be logged for DeadLockDetector.
                //---------------------------------------------------------------
                baton_type( bool Logging = true );

                //---------------------------------------------------------------
                /// \brief Return pointer to low level data storage.
                ///
                /// \return
                ///     Pointer to low level data storage.
                ///
                /// \note
                ///     This should be used very sparingly since the library
                ///     used to implement this fuctionality may change.
                //---------------------------------------------------------------
                void* Handle( );

                //---------------------------------------------------------------
                /// \brief Request the resource to be locked
                ///
                /// \param[in] Mode
                ///     Any of the lock_modes.
                /// \param[in] File
                ///     The filename from where the call was made.
                /// \param[in] Line
                ///     The line number from where the call was made.
                //---------------------------------------------------------------
                void Lock( mode_type         Mode,
                           const char* const File,
                           const size_t      Line );

                //---------------------------------------------------------------
                /// \brief Request the resource to be locked
                ///
                /// \param[in] Mode
                ///     Any of the lock_modes.
                /// \param[in] TryLock
                ///     If true, then return immediately wether or not the lock
                ///     was obtained.
                /// \param[in] File
                ///     The filename from where the call was made.
                /// \param[in] Line
                ///     The line number from where the call was made.
                //---------------------------------------------------------------
                void Lock( mode_type         Mode,
                           bool              TryLock,
                           const char* const File,
                           const size_t      Line );

                //---------------------------------------------------------------
                /// \brief Request the resource to be locked
                ///
                /// \param[in] Mode
                ///     Any of the lock_modes.
                /// \param[in] Timeout
                ///     Time limit in seconds in which to acquire the lock.
                ///     A value of zero (0) indicates that the method should
                ///     wait until the lock is granted.
                /// \param[in] File
                ///     The filename from where the call was made.
                /// \param[in] Line
                ///     The line number from where the call was made.
                //---------------------------------------------------------------
                void Lock( mode_type         Mode,
                           size_t            Timeout,
                           const char* const File,
                           const size_t      Line );

                //---------------------------------------------------------------
                /// \brief Request the resource to be locked without waiting
                ///
                /// \param[in] Mode
                ///     Any of the lock_modes.
                /// \param[in] File
                ///     The filename from where the call was made.
                /// \param[in] Line
                ///     The line number from where the call was made.
                //---------------------------------------------------------------
                void TryLock( mode_type         Mode,
                              const char* const File,
                              const size_t      Line );

                //---------------------------------------------------------------
                /// \brief Release any locks held on the resource
                ///
                /// \param[in] File
                ///     The filename from where the call was made.
                /// \param[in] Line
                ///     The line number from where the call was made.
                //---------------------------------------------------------------
                void Unlock( const char* const File, const size_t Line );

                //---------------------------------------------------------------
                /// \brief Destroy the resources associated with this instance.
                //---------------------------------------------------------------
                void reset( );

            private:
                friend void*
                           ReadWriteLockBatonHandle( ReadWriteLock::baton_type Baton );
                static int retry_count_max;

                boost::shared_ptr< impl > p;
            };

            //-----------------------------------------------------------------
            /// \brief Constructor
            ///
            /// \param[in] Lock
            ///     Baton controlling access to the resource.
            /// \param[in] Mode
            ///     Any of the lock_modes.
            /// \param[in] File
            ///     The filename from where the call was made.
            /// \param[in] Line
            ///     The line number from where the call was made.
            ///
            /// \code{.cpp}
            ///  l.Lock( ReadWriteLock::READ, __FILE__, __LINE__ );
            /// \endcode
            //-----------------------------------------------------------------
            ReadWriteLock( baton_type  Lock,
                           mode_type   Mode,
                           const char* Filename,
                           int         Linenum );

            //-----------------------------------------------------------------
            /// \brief Constructor
            ///
            /// \param[in] Lock
            ///     Baton controlling access to the resource.
            /// \param[in] Mode
            ///     Any of the lock_modes.
            /// \param[in] TryLock
            ///     If true, then return immediately wether or not the lock
            ///     was obtained.
            /// \param[in] File
            ///     The filename from where the call was made.
            /// \param[in] Line
            ///     The line number from where the call was made.
            //-----------------------------------------------------------------
            ReadWriteLock( baton_type  Lock,
                           mode_type   Mode,
                           bool        TryLock,
                           const char* Filename,
                           int         Linenum );

            //-----------------------------------------------------------------
            /// \brief Constructor
            ///
            /// \param[in] Lock
            ///     Baton controlling access to the resource.
            /// \param[in] Mode
            ///     Any of the lock_modes.
            /// \param[in] Timeout
            ///     Time limit in seconds in which to acquire the lock.
            ///     A value of zero (0) indicates that the method should
            ///     wait until the lock is granted.
            /// \param[in] File
            ///     The filename from where the call was made.
            /// \param[in] Line
            ///     The line number from where the call was made.
            //-----------------------------------------------------------------
            ReadWriteLock( baton_type  Lock,
                           mode_type   Mode,
                           int         Timeout,
                           const char* Filename,
                           int         Linenum );

            //-----------------------------------------------------------------
            /// \brief  Destructor
            //-----------------------------------------------------------------
            virtual ~ReadWriteLock( );

            //-----------------------------------------------------------------
            /// \brief  Create a baton that is appropriate for use with this
            /// class
            //-----------------------------------------------------------------
            static baton_type Baton( );

            //-----------------------------------------------------------------
            /// \brief Modify the mode of lock being held on the resource.
            ///
            /// \param[in] Mode
            ///     The new mode to be held on the resource.
            /// \param[in] File
            ///     The filename from where the call was made.
            /// \param[in] Line
            ///     The line number from where the call was made.
            //-----------------------------------------------------------------
            void Modify( mode_type Mode, const char* Filename, int Linenum );

            //-----------------------------------------------------------------
            /// \brief Release the lock
            ///
            /// \param[in] File
            ///     The filename from where the call was made.
            /// \param[in] Line
            ///     The line number from where the call was made.
            //-----------------------------------------------------------------
            void Release( const char* Filename, int Linenum );

            static int Interval( int Value );
            static int Timeout( int Value );

            //-------------------------------------------------------------------
            /// \brief Handler for thead cancelation
            ///
            /// \param[in] VLock
            ///     The VLock is a pointer to a ReadWriteLock object that holds
            ///     a lock.
            //-------------------------------------------------------------------
            static void ThreadCancel( void* VLock );

        private:
            baton_type sync_baton;
        };

        //---------------------------------------------------------------------
        /// \brief Implements read/write lock symantics for a variable.
        ///
        /// This class allows for manipulation of variables to be thread safe.
        ///
        /// \code{.cpp}
        /// ReadWriteLock::baton_type	baton;
        /// std::string			v;
        /// ReadWriteLockVariable< ReadWriteLock::Write, std::string >
        ///       lock( baton, 0, v);
        ///
        /// try
        /// {
        ///   if ( lock.Var( ).size( ) == 0 )
        ///   {
        ///     lock.Var( ).assign( "New value" );
        ///   }
        /// }
        /// catch( )
        /// {
        /// }
        /// \endcode
        //---------------------------------------------------------------------
        template < ReadWriteLock::mode_type T, typename V >
        class ReadWriteLockVariable
        {
        public:
            //-------------------------------------------------------------------
            /// \brief Baton
            ///
            /// The resource used to manage resouce access.
            //-------------------------------------------------------------------
            typedef ReadWriteLock::baton_type baton_type;
            //-------------------------------------------------------------------
            /// \brief Type of variable
            ///
            /// The type of variable being managed.
            //-------------------------------------------------------------------
            typedef V element_type;

            //-------------------------------------------------------------------
            /// \brief Constructor
            ///
            /// \param[in] Baton
            ///     Baton controlling access to the resource.
            /// \param[in] Timeout
            ///     Maximum length of time to wait on obtaining the lock.
            /// \param[in] Variable
            ///     Variable being managed by the class.
            /// \param[in] Filename
            ///     The filename from where the call was made.
            /// \param[in] Linenum
            ///     The line number from where the call was made.
            //-------------------------------------------------------------------
            ReadWriteLockVariable( baton_type  Baton,
                                   int         Timeout,
                                   V&          Variable,
                                   const char* Filename,
                                   int         Linenum );

            //-------------------------------------------------------------------
            /// \brief Constructor
            ///
            /// \param[in] Baton
            ///     Baton controlling access to the resource.
            /// \param[in] Timeout
            ///     Maximum length of time to wait on obtaining the lock.
            /// \param[in] Variable
            ///     Variable being managed by the class.
            /// \param[in] Filename
            ///     The filename from where the call was made.
            /// \param[in] Linenum
            ///     The line number from where the call was made.
            //-------------------------------------------------------------------
            ReadWriteLockVariable( baton_type  Baton,
                                   int         Timeout,
                                   const V&    Variable,
                                   const char* Filename,
                                   int         Linenum );

            //-------------------------------------------------------------------
            /// \brief Copy constructor
            ///
            /// \param[in] Source
            ///     Source from which to initialize.
            /// \param[in] Filename
            ///     The filename from where the call was made.
            /// \param[in] Linenum
            ///     The line number from where the call was made.
            //-------------------------------------------------------------------
            ReadWriteLockVariable( const ReadWriteLockVariable& Source,
                                   const char*                  Filename,
                                   int                          Linenum );

            //-------------------------------------------------------------------
            /// \brief Read only access to the variable.
            //-------------------------------------------------------------------
            const V& Var( ) const;

            //-------------------------------------------------------------------
            /// \brief Read/Write access to the variable.
            //-------------------------------------------------------------------
            V& Var( );

        private:
            ReadWriteLockVariable( );

            baton_type            m_baton;
            int                   m_timeout;
            V&                    m_variable;
            mutable ReadWriteLock m_lock;
            mutable bool          m_is_locked;
            const bool            m_is_read_only;

            inline baton_type
            release( const char* File, int Line ) const
            {
                m_lock.Release( File, Line ); // Reliquish lock
                m_is_locked = false;
                return m_baton;
            }
        };

        //-------------------------------------------------------------------
        //-------------------------------------------------------------------
        template < ReadWriteLock::mode_type T, typename V >
        inline ReadWriteLockVariable< T, V >::ReadWriteLockVariable(
            baton_type  Baton,
            int         Timeout,
            V&          Variable,
            const char* Filename,
            int         Linenum )
            : m_baton( Baton ), m_timeout( Timeout ), m_variable( Variable ),
              m_lock( Baton, T, m_timeout, Filename, Linenum ),
              m_is_locked( true ), m_is_read_only( false )
        {
        }

        //-------------------------------------------------------------------
        //-------------------------------------------------------------------
        template < ReadWriteLock::mode_type T, typename V >
        inline ReadWriteLockVariable< T, V >::ReadWriteLockVariable(
            baton_type  Baton,
            int         Timeout,
            const V&    Variable,
            const char* Filename,
            int         Linenum )
            : m_baton( Baton ), m_timeout( Timeout ),
              m_variable( const_cast< V& >( Variable ) ),
              m_lock( Baton, T, m_timeout, Filename, Linenum ),
              m_is_locked( true ), m_is_read_only( true )
        {
        }

        //-------------------------------------------------------------------
        //-------------------------------------------------------------------
        template < ReadWriteLock::mode_type T, typename V >
        inline ReadWriteLockVariable< T, V >::ReadWriteLockVariable(
            const ReadWriteLockVariable& Source,
            const char*                  Filename,
            int                          Linenum )
            : m_baton( Source.m_baton ), m_timeout( Source.m_timeout ),
              m_variable( Source.m_variable ),
              m_lock( Source.release( Filename, Linenum ),
                      T,
                      m_timeout,
                      Filename,
                      Linenum ),
              m_is_locked( true ), m_is_read_only( Source.m_is_read_only )
        {
        }

        //-------------------------------------------------------------------
        //-------------------------------------------------------------------
        template < ReadWriteLock::mode_type T, typename V >
        inline const V&
        ReadWriteLockVariable< T, V >::Var( ) const
        {
            if ( m_is_locked == false )
            {
                throw std::logic_error(
                    "ReadWriteLockVariable: data not protected by lock" );
            }
            return m_variable;
        }

        //-------------------------------------------------------------------
        //-------------------------------------------------------------------
        template < ReadWriteLock::mode_type T, typename V >
        inline V&
        ReadWriteLockVariable< T, V >::Var( )
        {
            if ( T == ReadWriteLock::READ )
            {
                assert( 0 );
                throw std::logic_error(
                    "ReadWriteLockVariable: Cannot access variable for writing "
                    "while only holding a read lock" );
            }
            if ( m_is_read_only )
            {
                assert( 0 );
                throw std::logic_error( "ReadWriteLockVariable: Cannot access "
                                        "constant variable for writing" );
            }
            if ( m_is_locked == false )
            {
                assert( 0 );
                throw std::logic_error(
                    "ReadWriteLockVariable: data not protected by lock" );
            }
            return m_variable;
        }

        //-------------------------------------------------------------------
        /// \code{.cpp}
        /// try {
        ///   l.Lock( ReadWriteLock::READ, __FILE__, __LINE__ );
        /// }
        /// catch( const ReadWriteLock::BusyError& Exception )
        /// {
        ///   // Do something since the lock could not be acquired
        ///   ...
        /// }
        /// catch( const ReadWriteLock::DeadLockError& Exception )
        /// {
        ///   // Do something since the lock could not be acquired
        ///   ...
        /// }
        /// \endcode
        //-------------------------------------------------------------------
        inline void
        ReadWriteLock::baton_type::Lock( mode_type         Mode,
                                         const char* const File,
                                         const size_t      Line )
        {
            Lock( Mode, false, File, Line );
        }

        //-------------------------------------------------------------------
        ///
        /// The TryLock method tries to lock the resouce.
        /// If the resouce is locked prior to this call,
        /// then the method returns immediately by
        /// throwing the ReadWriteLock::BusyError exception.
        ///
        /// \code{.cpp}
        /// try {
        ///   l.TryLock( ReadWriteLock::READ, __FILE__, __LINE__ );
        /// }
        /// catch( const ReadWriteLock::BusyError& Exception )
        /// {
        ///   // Do something since the lock could not be acquired
        ///   ...
        /// }
        /// catch( const ReadWriteLock::DeadLockError& Exception )
        /// {
        ///   // Do something since the lock could not be acquired
        ///   ...
        /// }
        /// \endcode
        //-------------------------------------------------------------------
        inline void
        ReadWriteLock::baton_type::TryLock( mode_type         Mode,
                                            const char* const File,
                                            const size_t      Line )
        {
            Lock( Mode, true, File, Line );
        }

        inline void
        ReadWriteLock::baton_type::reset( )
        {
            p.reset( );
        }

    } // namespace AL
} // namespace LDASTools

#endif /* GENERAL__READ_WRITE_LOCK_HH */
