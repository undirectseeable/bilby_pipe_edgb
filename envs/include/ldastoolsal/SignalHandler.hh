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

#ifndef LDAS_TOOLS_AL__SIGNAL_HANDLER_HH
#define LDAS_TOOLS_AL__SIGNAL_HANDLER_HH

#include <list>

#include "ldastoolsal/Singleton.hh"
#include "ldastoolsal/unordered_map.hh"

namespace LDASTools
{
    namespace AL
    {
        class SignalHandler : public Singleton< SignalHandler >
        {
        public:
            enum signal_type
            {
                SIGNAL_ABORT,
                SIGNAL_ALARM,
                SIGNAL_HANGUP,
                SIGNAL_ISALIVE,
                SIGNAL_TERMINATE,
                SIGNAL_USER_1,
                SIGNAL_USER_2,
                SIGNAL_UNKNOWN
            };

            class Callback
            {
            public:
                virtual ~Callback( );

                virtual void SignalCallback( signal_type Signal ) = 0;
            };

            class IgnoreCallback : public Callback
            {
            public:
                virtual ~IgnoreCallback( );

                virtual void SignalCallback( signal_type Signal );
            };

            static void Register( Callback* CB, signal_type Signal );

            static void Unregister( Callback* CB, signal_type Signal );

            static void Callbacks( signal_type Signal );

            static int OSSignal( signal_type Signal );

            static void ThreadCaptureSignal( signal_type Signal );

            static void ThreadIgnoreSignal( signal_type Signal );

            static IgnoreCallback IgnoreCB;

        private:
            typedef std::list< Callback* > callbacks_type;
            typedef LDASTools::AL::unordered_map< int, callbacks_type >
                signal_queue_type;

            signal_queue_type signal_queue;

            void callbacks( signal_type Signal );

            void reg( Callback* CB, signal_type Signal );

            void unreg( Callback* CB, signal_type Signal );
        };

    } // namespace AL
} // namespace LDASTools

#endif /* LDAS_TOOLS_AL__SIGNAL_HANDLER_HH */
