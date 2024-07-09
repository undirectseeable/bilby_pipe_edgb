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

#ifndef LDASTOOLSAL__SYSTEM_CALL_HH
#define LDASTOOLSAL__SYSTEM_CALL_HH

namespace LDASTools
{
    namespace AL
    {
        //-------------------------------------------------------------
        /// \brief Interface for doing operating system calls
        //-------------------------------------------------------------
        class SystemCall
        {
        public:
            SystemCall( );

            //-----------------------------------------------------------
            /// \brief Destructor to properly destroy all resources.
            //-----------------------------------------------------------
            virtual ~SystemCall( );

            //-----------------------------------------------------------
            /// \brief Return the thread specific value of errno
            //-----------------------------------------------------------
            int SystemErrNo( ) const;

            //-----------------------------------------------------------
            /// \brief Return the return code of the system call
            //-----------------------------------------------------------
            int SystemReturnCode( ) const;

        protected:
            //-----------------------------------------------------------
            /// \brief Return code of the system call.
            ///
            /// This is the return code returned by the system call as
            /// defined by the system call's documentation.
            //-----------------------------------------------------------
            int m_returnCode;
            //-----------------------------------------------------------
            /// \brief Thread specific value of errno at time of exit.
            ///
            /// This allows for the thread specific errno value to be
            /// known outside of the calling thread.
            /// It is most benificial for error recovery as some
            /// conditions should cause a retry.
            //-----------------------------------------------------------
            int m_errNo;
        };

        inline SystemCall::~SystemCall( )
        {
        }

        inline int
        SystemCall::SystemErrNo( ) const
        {
            return m_errNo;
        }

        inline int
        SystemCall::SystemReturnCode( ) const
        {
            return m_returnCode;
        }
    } // namespace AL
} // namespace LDASTools

#endif /* LDASTOOLSAL__SYSTEM_CALL_HH */
