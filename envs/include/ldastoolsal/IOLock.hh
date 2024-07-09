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

#include <iostream>
#include <list>

#include "ldastoolsal/mutexlock.hh"

namespace LDASTools
{
    namespace AL
    {
        /// \brief  Class to coordinate writing of streams.
        ///
        /// This class allows multithreaded applications to share a stream
        /// when threads cooperate.
        class IOLock
        {
        public:
            typedef MutexLock::baton_type baton_type;

            /// \brief  Obtain the lock for a stream.
            static baton_type GetKey( const std::ostream& Stream );

        private:
            struct lock_set
            {
                const void* key;
                baton_type  lock;
            };
            typedef std::list< lock_set* > keys_ostream_type;

            static baton_type m_key_ostream;

            static keys_ostream_type m_keys_ostream;
        }; // class - IOLock
    } // namespace AL
} // namespace LDASTools
