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

#ifndef GENERAL__FORK_HH
#define GENERAL__FORK_HH

#include <sys/types.h>
#include <unistd.h>

namespace LDASTools
{
    namespace AL
    {
        class Fork
        {
        public:
            Fork( );
            virtual ~Fork( );
            pid_t ChildPid( ) const;

            bool IsChildAlive( ) const;

            virtual void Spawn( );

        protected:
            virtual void evalChild( ) = 0;
            virtual void evalParent( ) = 0;

            void closeStdIn( );
            void closeStdOut( );
            void closeStdErr( );

            bool isParent( ) const;

            int getReadFD( ) const;
            int getWriteFD( ) const;

            int getStdIn( ) const;
            int getStdOut( ) const;
            int getStdErr( ) const;

        private:
            static const int F_STDIN;
            static const int F_STDOUT;
            static const int F_STDERR;

            static const int F_READ;
            static const int F_WRITE;

            pid_t m_child_pid;
            int   m_pipes[ 3 ][ 2 ];

            void close_pipes( );
            void close_pipe( int Major, int Minor );
        };

        inline pid_t
        Fork::ChildPid( ) const
        {
            return m_child_pid;
        }

        inline void
        Fork::closeStdIn( )
        {
            close_pipe( F_STDIN, ( isParent( ) ? F_WRITE : F_READ ) );
        }

        inline void
        Fork::closeStdOut( )
        {
            close_pipe( F_STDOUT, ( isParent( ) ? F_READ : F_WRITE ) );
        }

        inline void
        Fork::closeStdErr( )
        {
            close_pipe( F_STDERR, ( isParent( ) ? F_READ : F_WRITE ) );
        }

        inline bool
        Fork::isParent( ) const
        {
            return ( m_child_pid != 0 );
        }

        inline int
        Fork::getReadFD( ) const
        {
            return ( isParent( ) ) ? m_pipes[ 0 ][ 0 ] : m_pipes[ 1 ][ 0 ];
        }

        inline int
        Fork::getWriteFD( ) const
        {
            return ( isParent( ) ) ? m_pipes[ 1 ][ 1 ] : m_pipes[ 0 ][ 1 ];
        }

        inline int
        Fork::getStdIn( ) const
        {
            return ( m_pipes[ F_STDIN ][ ( isParent( ) ? F_WRITE : F_READ ) ] );
        }

        inline int
        Fork::getStdOut( ) const
        {
            return (
                m_pipes[ F_STDOUT ][ ( isParent( ) ? F_READ : F_WRITE ) ] );
        }

        inline int
        Fork::getStdErr( ) const
        {
            return (
                m_pipes[ F_STDERR ][ ( isParent( ) ? F_READ : F_WRITE ) ] );
        }
    } // namespace AL
} // namespace LDASTools

#endif /* GENERAL__TIMEOUT_HH */
