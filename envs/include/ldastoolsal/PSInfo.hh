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

#ifndef LDASTOOLSAL__PS_INFO_HH
#define LDASTOOLSAL__PS_INFO_HH

#include <sys/types.h>
#include <unistd.h>

#include <string>

namespace LDASTools
{
    namespace AL
    {
        /// \brief  Class to retrieve process information.
        class PSInfo
        {
        public:
            /// \brief  Structure to hold information about a process.
            struct psinfo_type
            {
                pid_t       s_pid;
                char        s_state;
                std::string s_user;
                size_t      s_vsz;
                size_t      s_rsz;
                float       s_pcpu;
                float       s_pmem;
                int         s_etime;
                std::string s_fname;
                std::string s_args;
            };

            /// \brief  Constructor
            PSInfo( pid_t PID = getpid( ) );

            /// \brief  Obtain information about a process
            void operator( )( psinfo_type& Query ) const;

        private:
            /// \brief  Process identification.
            pid_t m_pid;
        };
    } // namespace AL
} // namespace LDASTools

#endif /* LDASTOOLSAL__PS_INFO_HH */
