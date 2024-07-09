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

#ifndef GENERAL__DIRECTORY
#define GENERAL__DIRECTORY

#include <list>
#include <string>

#include <boost/shared_ptr.hpp>

namespace LDASTools
{
    namespace AL
    {
        //-------------------------------------------------------------------
        /// \brief Read the contents of a directory
        ///
        /// This provides a system independent interface to reading the
        /// the contents of a directory.
        /// It can operate in a blocking or non-blocking mode.
        /// By default, it operates in non-blocking mode.
        //-------------------------------------------------------------------
        class Directory
        {
        public:
            //-----------------------------------------------------------------
            /// \brief Enumerated type specifying the blocking mode.
            ///
            /// This is used by the Mode method to specify the blocking
            /// mode the subsequent calls should operate in.
            //-----------------------------------------------------------------
            enum mode_type
            {
                //---------------------------------------------------------------
                /// \brief Blocking mode
                ///
                /// When in blocking mode, calls made will operate in the
                /// current
                /// thread and return when the system call returns.
                //---------------------------------------------------------------
                MODE_BLOCKING,
                //---------------------------------------------------------------
                /// \brief Non blocking mode
                ///
                /// When in non-blocking mode, calls are done in a thread and
                /// given a specific amount of time in which to return.
                /// If they do not return within the alotted time, then
                /// an exception is thrown.
                //---------------------------------------------------------------
                MODE_NON_BLOCKING
            };

            typedef std::list< std::string > block_read_type;

            //-----------------------------------------------------------------
            /// \brief Constructor
            ///
            /// Construct a new instance of this object.
            //-----------------------------------------------------------------
            Directory( const std::string& DirName, bool OpenDirectory = true );

            //-----------------------------------------------------------------
            /// \brief Destructor
            ///
            /// Release resources back to the system.
            //-----------------------------------------------------------------
            ~Directory( );

            //-----------------------------------------------------------------
            /// \brief Close the directory
            //-----------------------------------------------------------------
            void Close( );

            const char* EntryName( ) const;

            int Fd( ) const;

            const std::string& Name( ) const;

            mode_type Mode( ) const;

            void Mode( mode_type Mode );

            /// Retrieve the next entry.
            /// returns true if a valid entry was found, false otherwise
            bool Next( );

            void Next( block_read_type& Entries );

            void Open( );

            //-----------------------------------------------------------------
            /// \brief Retrieve the number of seconds any one of the calls
            /// should take.
            //-----------------------------------------------------------------
            static int Timeout( );

            //-----------------------------------------------------------------
            /// \brief Specify the number of seconds any one of the calls should
            /// take.
            //-----------------------------------------------------------------
            static void Timeout( int Value );

            class Internals;
            typedef boost::shared_ptr< Internals > value_type;

        private:
            value_type m_internals;
            mode_type  m_blocking_mode;

            void eval_request( const int Request );
        };

        inline Directory::mode_type
        Directory::Mode( ) const
        {
            return m_blocking_mode;
        }

        inline void
        Directory::Mode( mode_type Mode )
        {
            m_blocking_mode = Mode;
        }
    } // namespace AL
} // namespace LDASTools

#endif /* GENERAL__DIRECTORY */
