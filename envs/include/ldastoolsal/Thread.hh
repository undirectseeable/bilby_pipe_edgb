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

#ifndef LDASTOOLSAL__THREAD_HH
#define LDASTOOLSAL__THREAD_HH

#include <limits.h>

#include <stdexcept>

#include <boost/shared_ptr.hpp>

#include "ldastoolsal/mutexlock.hh"
#include "ldastoolsal/SignalHandler.hh"

namespace LDASTools
{
    namespace AL
    {
        class Thread
        {
        public:
            class thread_type;

            class cancellation : public std::runtime_error
            {
            public:
                cancellation( const std::string& Header,
                              const char*        File,
                              const int          Line );

            private:
                static std::string format( const std::string& Header,
                                           const char*        File,
                                           const int          Line );
            };

            class deadlock : public std::logic_error
            {
            public:
                deadlock( const std::string& Header,
                          const char*        File,
                          const int          Line );

            private:
                static std::string format( const std::string& Header,
                                           const char*        File,
                                           const int          Line );
            };

            class invalid_argument : public std::invalid_argument
            {
            public:
                invalid_argument( const std::string& Header,
                                  const char*        File,
                                  const int          Line );

            private:
                static std::string format( const std::string& Header,
                                           const char*        File,
                                           const int          Line );
            };

            class range_error : public std::range_error
            {
            public:
                range_error( const std::string& Header,
                             const char*        File,
                             const int          Line );

            private:
                static std::string format( const std::string& Header,
                                           const char*        File,
                                           const int          Line );
            };

            typedef enum
            {
                CANCEL_ABANDON,
                CANCEL_IGNORE,
                CANCEL_ASYNCHRONOUS,
                CANCEL_DEFERRED,
                CANCEL_EXCEPTION,
                CANCEL_BY_SIGNAL,
                CANCEL_UNKNOWN
            } cancel_type;

            typedef SignalHandler::signal_type signal_type;

            typedef void ( *cleanup_function_type )( void* );

            //-------------------------------------------------------------------
            /// \brief Operates on current thread.
            //-------------------------------------------------------------------
            class Self
            {
            public:
                //-----------------------------------------------------------------
                /// \brief Request termination of the current thread
                //-----------------------------------------------------------------
                static void Cancel( );

                //-----------------------------------------------------------------
                /// \brief Deliver pending cancellation requests to the calling
                /// thread.
                ///
                /// \param[in] Header
                ///     Description of the method from which the request was
                ///     made
                /// \param[in] File
                ///     Filename from where the request was made.
                /// \param[in] Line
                ///     Line number in Filename from where the request was made.
                //-----------------------------------------------------------------
                static void CancellationCheck( const std::string& Header,
                                               const char*        File,
                                               const int          Line );

                //-----------------------------------------------------------------
                /// \brief Retrieve the cancellation method
                //-----------------------------------------------------------------
                static cancel_type CancellationType( signal_type& Signal );

                //-----------------------------------------------------------------
                /// \brief Specify the method of cancelation
                //-----------------------------------------------------------------
                static void CancellationType(
                    cancel_type Type,
                    signal_type Signal = SignalHandler::SIGNAL_UNKNOWN );

                static thread_type Id( );

            private:
                Self( );
            };

            Thread( );

            virtual ~Thread( );

            virtual void Cancel( );

            //-------------------------------------------------------------------
            /// \brief Deliver pending cancellation requests to the calling
            /// thread.
            ///
            /// \param[in] Header
            ///     Description of the method from which the request was made
            /// \param[in] File
            ///     Filename from where the request was made.
            /// \param[in] Line
            ///     Line number in Filename from where the request was made.
            //-------------------------------------------------------------------
            void CancellationCheck( const std::string& Header,
                                    const char*        File,
                                    const int          Line ) const;

            void CancellationEnable( bool Value );

            //-------------------------------------------------------------------
            /// \brief Return the type of cancellation.
            ///
            /// \param[out] Signal
            ///     Any auxiliary information associated with the cancellation
            ///     type
            /// \return
            ///     The type of cancellation.
            ///
            /// \see cancel_type
            //-------------------------------------------------------------------
            cancel_type CancellationType( signal_type& Signal ) const;

            //-------------------------------------------------------------------
            /// \brief Establiosh the type of cancellation.
            ///
            /// \param[in] Type
            ///     The type of cancellation.
            /// \param[in] Signal
            ///     Any auxiliary information associated with the cancellation
            ///     type.
            //-------------------------------------------------------------------
            void CancellationType(
                cancel_type Type,
                signal_type Signal = SignalHandler::SIGNAL_UNKNOWN );

            void Detach( ) const;

            virtual void Join( );

            bool IsAlive( ) const;

            //-------------------------------------------------------------------
            /// \brief Return the cancellation state of the thread
            ///
            /// \return
            ///     Returns true if the thread has been cancelled,
            ///     false otherwise.
            //-------------------------------------------------------------------
            bool IsCancelled( ) const;

            //-------------------------------------------------------------------
            /// \brief Reports detached state
            ///
            /// \return
            ///     Returns true if the thread has been detached,
            ///     false otherwise
            //-------------------------------------------------------------------
            bool IsDetached( ) const;

            bool IsParentThread( ) const;

            int Kill( signal_type Signal ) const;

            //-------------------------------------------------------------------
            /// \brief Retrieve key for parent thread
            //-------------------------------------------------------------------
            thread_type ParentThread( ) const;

            virtual int Spawn( );

            static void SelfCancellationCheck( const std::string& Header,
                                               const char*        File,
                                               const int          Line );

            void SignalCapture( signal_type Sig );

            void SignalIgnore( signal_type Sig );

            static size_t StackSizeDefault( );

            static void StackSizeDefault( size_t StackSize );

            bool operator==( const Thread& Source ) const;

        protected:
            typedef void* ( *start_function_type )( void* );

            //-------------------------------------------------------------------
            /// \brief Job to be acomplished by the thread
            ///
            //-------------------------------------------------------------------
            virtual void action( ) = 0;

            //-------------------------------------------------------------------
            /// \brief Perform cleanup of a cancelled thread
            ///
            /// \param[in] Source
            ///     The thread being cancelled.
            //-------------------------------------------------------------------
            static void cancelCleanup( Thread* Source );

            //-------------------------------------------------------------------
            /// \brief Spawn a new thread
            ///
            /// \param[in] StartFunction
            ///     The routine for the new thread to start.
            //-------------------------------------------------------------------
            int spawn( start_function_type StartFunction = (start_function_type)
                           start_routine );

            thread_type threadId( ) const;

        private:
            class impl;

            boost::shared_ptr< impl > p;

            //-------------------------------------------------------------------
            /// \brief Signal to use for cancelation
            //-------------------------------------------------------------------
            signal_type m_cancel_via_signal;
            //-------------------------------------------------------------------
            /// \brief Enable or disable the cancellability of a thread
            //-------------------------------------------------------------------
            mutable bool m_cancel_state;
            //-------------------------------------------------------------------
            /// \brief Conditional state of thread being cancelled.
            //-------------------------------------------------------------------
            mutable bool m_cancel_thread;

            //-------------------------------------------------------------------
            /// \brief Method used for thread cancellation.
            //-------------------------------------------------------------------
            mutable cancel_type m_cancellation_type;

            //-------------------------------------------------------------------
            /// \brief State of detached
            //-------------------------------------------------------------------
            mutable bool detached;
            //-------------------------------------------------------------------
            //-------------------------------------------------------------------
            static Thread* start_routine( Thread* ThreadSource );

            void cancellation_enable( bool Value );
            void set_cancelled_state( );
        };
    } // namespace AL
} // namespace LDASTools

#endif /* LDASTOOLSAL__THREAD_HH */
