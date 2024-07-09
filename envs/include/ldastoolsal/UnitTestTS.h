/* * LDASTools AL - A library collection to provide an abstraction layer
 *
 * Copyright (C) 2018 California Institute of Technology
 *
 * LDASTools AL is free software; you may redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 (GPLv2) of the
 * License or at your discretion, any later version.
 *
 * LDASTools AL is distributed in the hope that it will be useful, but
 * without any warranty or even the implied warranty of merchantability
 * or fitness for a particular purpose. See the GNU General Public
 * License (GPLv2) for more details.
 *
 * Neither the names of the California Institute of Technology (Caltech),
 * The Massachusetts Institute of Technology (M.I.T), The Laser
 * Interferometer Gravitational-Wave Observatory (LIGO), nor the names
 * of its contributors may be used to endorse or promote products derived
 * from this software without specific prior written permission.
 *
 * You should have received a copy of the licensing terms for this
 * software included in the file LICENSE located in the top-level
 * directory of this package. If you did not, you can view a copy at
 * http://dcc.ligo.org/M1500244/LICENSE
 */

/* -*- mode: C++ -*- */
#ifndef UNITTEST_TS_H
#define UNITTEST_TS_H

#include <stdlib.h>
#include <strings.h>

#include <cstdlib>
#include <cstring>

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "ldastoolsal/MemChecker.hh"
#include "ldastoolsal/mutexlock.hh"

namespace LDASTools
{
    namespace Testing
    {
        /// \brief  Provide standard routines for unit testing of code.
        ///
        class UnitTestTS
        {
        public:
            /// \brief  Constructor
            UnitTestTS( void );
            /// \brief  Destructor
            ~UnitTestTS( void );
            /// \brief  Check for error conditions
            std::ostream& Check( bool TestResult );
            /// \brief  Check for error conditions
            void Check( bool TestResult, std::string Message );
            /// \brief  Exit with the appropriate exit code
            void Exit( void );
            /// \brief  Initialize the class with command line arguments
            void Init( int ArgC, char** ArgV );
            /// \brief  Check if in verbose mode
            bool
            IsVerbose( int Level = 0 ) const
            {
                return ( Level <= m_verbose );
            }
            void Lock( );
            /// \brief  Output info message
            std::ostream& Message( bool Leader = true ) const;
            /// \brief  Output info message
            std::ostream& Message( int Level, bool Leader = true ) const;
            void          UnLock( );

        private:
            /// \brief  Level of verbosity
            int m_verbose;
            /// \brief  Failure status flag
            bool m_status;
            /// \brief  Pointer to stream when in non-verbose mode
            mutable std::ostringstream m_null_stream;
            /// \brief	Lock when used in a mult-threaded environment
            LDASTools::AL::MutexLock::baton_type m_key;
            /// \brief  Trigger garbage collection
            LDASTools::AL::MemChecker::Trigger gc_trigger;
        }; // class - UnitTest

        inline UnitTestTS::UnitTestTS( void )
            : m_verbose( -1 ), m_status( true ), gc_trigger( true )
        {
            using LDASTools::AL::MutexLock;

            m_key = MutexLock::Baton( );
            if ( getenv( "TEST_VERBOSE_MODE" ) )
            {
                if ( 0 == strcmp( getenv( "TEST_VERBOSE_MODE" ), "true" ) )
                {
                    m_verbose = 0;
                }
                else if ( 0 ==
                          strcmp( getenv( "TEST_VERBOSE_MODE" ), "false" ) )
                {
                    m_verbose = -1;
                }
                else
                {
                    m_verbose = atoi( getenv( "TEST_VERBOSE_MODE" ) );
                }
            }
        }

        inline UnitTestTS::~UnitTestTS( void )
        {
        }

        inline std::ostream&
        UnitTestTS::Check( bool TestResult )
        {
            m_status = m_status && TestResult;
            if ( IsVerbose( ) )
            {
                std::cout << "-- " << ( ( TestResult ) ? "PASS" : "FAIL" )
                          << ": ";
                return std::cout;
            }
            m_null_stream.str( "" );
            return m_null_stream;
        }

        inline void
        UnitTestTS::Check( bool TestResult, std::string Message )
        {
            using LDASTools::AL::MutexLock;

            MutexLock l( m_key, __FILE__, __LINE__ );

            m_status = m_status && TestResult;
            if ( IsVerbose( ) )
            {
                std::cout << "-- " << ( ( TestResult ) ? "PASS" : "FAIL" )
                          << ": " << Message << std::endl
                          << std::flush;
            }
        }

        inline void
        UnitTestTS::Exit( void )
        {
            using LDASTools::AL::MutexLock;

            gc_trigger.DoGarbageCollection( );

            int e;
            {
                MutexLock l( m_key, __FILE__, __LINE__ );

                e = ( m_status ) ? 0 : 1;
            }
            exit( e );
        }

        inline void
        UnitTestTS::Init( int ArgC, char** ArgV )
        {
            using LDASTools::AL::MutexLock;

            MutexLock l( m_key, __FILE__, __LINE__ );

            for ( int x = 1; x < ArgC; x++ )
            {
                if ( 0 == ( strcmp( ArgV[ x ], "--verbose" ) ) )
                {
                    m_verbose = 0;
                    continue;
                }
            }
        }

        inline void
        UnitTestTS::Lock( )
        {
            m_key.Lock( __FILE__, __LINE__ );
        }

        inline std::ostream&
        UnitTestTS::Message( bool Leader ) const
        {
            if ( IsVerbose( ) )
            {
                if ( Leader )
                {
                    std::cout << "-- MESG: ";
                }
                return std::cout;
            }
            m_null_stream.str( "" );
            return m_null_stream;
        }

        inline std::ostream&
        UnitTestTS::Message( int Level, bool Leader ) const
        {
            if ( IsVerbose( Level ) )
            {
                return Message( Leader );
            }
            m_null_stream.str( "" );
            return m_null_stream;
        }

        inline void
        UnitTestTS::UnLock( )
        {
            m_key.Unlock( __FILE__, __LINE__ );
        }
    } // namespace Testing

} // namespace LDASTools

#endif /* UNITTEST_TS_H */
