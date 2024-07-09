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

#ifndef GENERAL__EXEC
#define GENERAL__EXEC

#include <string>
#include <vector>

#include "ldastoolsal/Fork.hh"

namespace LDASTools
{
    namespace AL
    {
        //-------------------------------------------------------------------
        //-------------------------------------------------------------------
        class Exec : public Fork
        {
        public:
            typedef const char* arg_type;
            typedef double      time_type;

            static arg_type COMMAND_END;

            Exec( arg_type Command, ... );

            arg_type Command( ) const;

            bool IfExited( ) const;

            bool CoreDump( ) const;

            int ExitCode( ) const;

            int Signal( ) const;

            virtual void Spawn( );

            const std::string& Stdout( ) const;

            const std::string& Stderr( ) const;

            time_type TimeCPU( ) const;

        protected:
            virtual void evalChild( );
            virtual void evalParent( );

        private:
            static const int E_STDOUT = 0;
            static const int E_STDERR = 1;

            typedef std::vector< arg_type > options_type;

            struct exit_type
            {
                int       s_exit_code;
                int       s_signal;
                bool      s_core_dump;
                bool      s_exited;
                time_type s_time_user;
                time_type s_time_system;

                std::string s_output[ 2 ];
            };

            options_type m_options;
            exit_type    m_child_exit;

            time_type m_start_time_user;
            time_type m_start_time_system;
        };

        inline Exec::arg_type
        Exec::Command( ) const
        {
            return m_options[ 0 ];
        }

        inline bool
        Exec::CoreDump( ) const
        {
            return m_child_exit.s_core_dump;
        }

        inline int
        Exec::ExitCode( ) const
        {
            return m_child_exit.s_exit_code;
        }

        inline bool
        Exec::IfExited( ) const
        {
            return m_child_exit.s_exited;
        }

        inline int
        Exec::Signal( ) const
        {
            return m_child_exit.s_signal;
        }

        inline const std::string&
        Exec::Stderr( ) const
        {
            return m_child_exit.s_output[ E_STDERR ];
        }

        inline const std::string&
        Exec::Stdout( ) const
        {
            return m_child_exit.s_output[ E_STDOUT ];
        }

        inline Exec::time_type
        Exec::TimeCPU( ) const
        {
            return ( m_child_exit.s_time_user + m_child_exit.s_time_system );
        }
    } // namespace AL
} // namespace LDASTools
#endif /* GENERAL__EXEC */
