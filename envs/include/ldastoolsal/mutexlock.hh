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

#ifndef MUTEXLOCK_HH
#define MUTEXLOCK_HH

#if !defined( SWIGIMPORTED )
#include <assert.h>
#include <errno.h>
#include <string.h>

#include <iostream>
#include <stdexcept>

#include <boost/shared_ptr.hpp>

#endif /* ! defined(SWIGIMPORTED) */

namespace LDASTools
{
    namespace AL
    {
        /// \class MutexLock
        ///
        /// \brief Descibes an object which release a mutex lock
        ///
        /// This class ensures that the given mutex is unlocked whenever an
        /// exception is thrown but not caught in a locked section.
        ///
        /// It should be used like this:
        ///
        /// \code
        /// {
        ///     MutexLock lock(baton); // mutex is now locked
        ///     do whatever...
        ///     ...
        /// } // MutexLock has been destructed so mutex is now unlocked
        /// \endcode
        ///
        ///
        /// Creating two MutexLock objects with the same mutex in the same scope
        /// will cause a deadlock.
        ///
        class MutexLock
        {
        public:
            /// \brief Alias for the system specific mutex type.
            class BusyError : public std::runtime_error
            {
            public:
                BusyError( );

            private:
                static std::string msg( );
            };

            class baton_type
            {
            public:
                baton_type( const char*  File = __FILE__,
                            unsigned int Line = __LINE__,
                            bool         Logging = true );

                void* Handle( );

                void Lock( const char* File, const size_t Line );

                void TryLock( const char* File, const size_t Line );

                void Unlock( const char* File, const size_t Line );

                inline operator bool( ) const
                {
                    if ( pimpl_.get( ) )
                    {
                        return true;
                    }
                    return false;
                }

            protected:
                class impl;

                boost::shared_ptr< impl > pimpl_;
            };

            //
            /// \brief  Constructor
            /// \param Baton The object to provide lock syncronization.
            /// \param File The from where the request was made.
            /// \param Line The line number from where the request was made.
            //
            MutexLock( baton_type         Baton,
                       const char* const  File,
                       const unsigned int Line );

            /// \brief  Destructor
            ~MutexLock( );

            /// \brief  Create a baton that is appropriate for use with this
            /// class
            static baton_type Baton( );

            /// \brief  Release the lock before object is destructed
            void Release( const char* const  File /* = "" */,
                          const unsigned int Line /* = 0 */ );

            //-------------------------------------------------------------------
            /// \brief Handler for thead cancelation
            ///
            /// \param[in] VLock
            ///     The VLock is a pointer to a ReadWriteLock object that holds
            ///     a lock.
            /// \param[in] File
            ///     The file where the request was made.
            /// \param[in] Line
            ///     The line number from where the request was made.
            //-------------------------------------------------------------------
            static void ThreadCancel( void*              VLock,
                                      const char*        File = __FILE__,
                                      const unsigned int Line = __LINE__ );

        private:
            /// \brief  Default Constructor
            ///
            /// Default constructor is private to prevent copying of classes
            /// internal data.
            MutexLock( );

            /// \brief  Copy Constructor
            ///
            /// Copy constructor is private to prevent copying of classes
            ///   internal data.
            MutexLock( const MutexLock& );

            /// \brief  Assigment operator
            ///
            /// Assignment operator is privat to prevent copying of classes
            /// internal data
            const MutexLock& operator=( const MutexLock& );

            /// \brief  Object to prevent multiple access to critical sections
            /// of code.
            baton_type baton;

            /// \brief Keeps track of logging state.
            bool m_logging;
        };

        template < typename V >
        class MutexLockVariable
        {
        public:
            MutexLockVariable( MutexLock::baton_type Baton,
                               V&                    Variable,
                               const char*           Filename /* = "" */,
                               int                   Linenum /* = 0 */ );

            MutexLockVariable( MutexLock::baton_type Baton,
                               const V&              Variable,
                               const char*           Filename /* = "" */,
                               int                   Linenum = 0 );
            MutexLockVariable( const MutexLockVariable& Source,
                               const char*              Filename /* = ""*/,
                               int                      Linenum /* = 0 */ );

            const V& Var( ) const;

            V& Var( );

        private:
            MutexLockVariable( );

            MutexLock::baton_type m_baton;
            V&                    m_variable;
            mutable MutexLock     m_lock;
            mutable bool          m_is_locked;

            MutexLock::baton_type release( ) const;
        };

        template < typename V >
        inline MutexLockVariable< V >::MutexLockVariable(
            MutexLock::baton_type Baton,
            V&                    Variable,
            const char*           Filename,
            int                   Linenum )
            : m_baton( Baton ), m_variable( Variable ),
              m_lock( Baton, Filename, Linenum ), m_is_locked( true )
        {
        }

        template < typename V >
        inline MutexLockVariable< V >::MutexLockVariable(
            MutexLock::baton_type Baton,
            const V&              Variable,
            const char*           Filename,
            int                   Linenum )
            : m_baton( Baton ), m_variable( const_cast< V& >( Variable ) ),
              m_lock( Baton, Filename, Linenum ), m_is_locked( true )
        {
        }

        template < typename V >
        inline MutexLockVariable< V >::MutexLockVariable(
            const MutexLockVariable& Source, const char* Filename, int Linenum )
            : m_baton( Source.m_baton ), m_variable( Source.m_variable ),
              m_lock( Source.release( ), Filename, Linenum ),
              m_is_locked( true )
        {
        }

        template < typename V >
        inline const V&
        MutexLockVariable< V >::Var( ) const
        {
            if ( m_is_locked == false )
            {
                throw std::logic_error(
                    "MutexLockVariable: data not protected by lock" );
            }
            return m_variable;
        }

        template < typename V >
        inline V&
        MutexLockVariable< V >::Var( )
        {
            if ( m_is_locked == false )
            {
                throw std::logic_error(
                    "MutexLockVariable: data not protected by lock" );
            }
            return m_variable;
        }

        template < typename V >
        MutexLock::baton_type
        MutexLockVariable< V >::release( ) const
        {
            m_lock.Release( __FILE__, __LINE__ ); // Reliquish lock
            m_is_locked = false;
            return m_baton;
        }
    } // namespace AL
} // namespace LDASTools

#endif // MUTEXLOCK_HH
