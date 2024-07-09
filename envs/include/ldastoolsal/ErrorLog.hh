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

#ifndef GENERAL__ERROR_LOG_H
#define GENERAL__ERROR_LOG_H

#if !defined( SWIGIMPORTED )
#include <iostream>
#endif /* ! defined(SWIGIMPORTED) */

#include "ldastoolsal/mutexlock.hh"
#include "ldastoolsal/types.hh"

namespace LDASTools
{
    namespace AL
    {
        //-------------------------------------------------------------------
        /// \brief  Error reporting mechanism
        class ErrorLog
        {
        public:
            enum state
            {
                ASSERT_FAILURE,
                //---------------------------------------------------------------
                /// \brief  Message represents a fatal condition.
                FATAL,
                //---------------------------------------------------------------
                /// \brief  Message is for debbugging purposes.
                DEBUG,
                //---------------------------------------------------------------
                /// \brief  Message represents a non-fatal condition.
                WARNING,
                //---------------------------------------------------------------
                /// \brief  Message supplies additional information.
                INFO
            };

            //-----------------------------------------------------------------
            /// \brief  Constructor
            ErrorLog( std::ostream& Stream, bool OpenState );
            //-----------------------------------------------------------------
            /// \brief  Destructor
            ~ErrorLog( );

            static bool AbortOnAssertFailure( );
            static void AbortOnAssertFailure( bool Value );

            //-----------------------------------------------------------------
            /// \brief  Check log's open state
            bool IsOpen( ) const;

            //-----------------------------------------------------------------
            /// \brief  Set log's open state
            bool IsOpen( bool State );

            void MaskBitClear( state State );

            void MaskBitSet( state State );

            //-----------------------------------------------------------------
            /// \brief  Write message to log
            void operator( )( state              State,
                              const char*        Filename,
                              const int          Line,
                              const std::string& Message,
                              bool               EOL = true );

            //-----------------------------------------------------------------
            /// \brief  Resetting of the output stream to use
            //-----------------------------------------------------------------
            void operator( )( std::ostream& Stream );

        private:
            static bool m_abort_on_assert_failure;

            //-----------------------------------------------------------------
            /// \brief  Stream associated with the log
            std::ostream* m_stream;
            //-----------------------------------------------------------------
            /// \brief  Lock to ensure syncronous output
            MutexLock::baton_type m_lock;
            //-----------------------------------------------------------------
            /// \brief  Open state of log
            bool   m_is_open;
            INT_4U m_mask;
        };

        inline bool
        ErrorLog::AbortOnAssertFailure( )
        {
            return m_abort_on_assert_failure;
        }

        inline void
        ErrorLog::AbortOnAssertFailure( bool Value )
        {
            m_abort_on_assert_failure = Value;
        }

        inline bool
        ErrorLog::IsOpen( ) const
        {
            return m_is_open;
        }

        inline bool
        ErrorLog::IsOpen( bool State )
        {
            bool retval = m_is_open;
            m_is_open = State;
            return retval;
        }

        inline void
        ErrorLog::MaskBitClear( state State )
        {
            m_mask &= ~( INT_4U( 1 << State ) );
        }

        inline void
        ErrorLog::MaskBitSet( state State )
        {
            m_mask |= ( 1 << State );
        }

        inline void
        ErrorLog::operator( )( std::ostream& Stream )
        {
            m_stream = &Stream;
        }
        extern ErrorLog StdErrLog;

        extern ErrorLog JournalLog;
    } // namespace AL
} // namespace LDASTools

#endif /* GENERAL__ERROR_LOG_H */
