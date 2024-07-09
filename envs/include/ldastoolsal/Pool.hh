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

#ifndef LDASTOOLSAL__POOL_HH
#define LDASTOOLSAL__POOL_HH

#include <stdexcept>
#include <list>

#include "ldastoolsal/mutexlock.hh"

namespace LDASTools
{
    namespace AL
    {
        //-------------------------------------------------------------
        /// \brief Maintain a collection system calls
        //-------------------------------------------------------------
        template < typename T >
        class Pool
        {
        public:
            typedef T value_type;

            Pool( );

            virtual ~Pool( );

            void Relinquish( value_type Source );

            value_type Request( value_type ( *CreateFunc )( ) );

        protected:
            typedef std::list< value_type > pool_type;

            pool_type             m_available;
            MutexLock::baton_type m_baton;

            virtual void relinquish( value_type Source );

            virtual value_type request( value_type ( *CreateFunc )( ) );
        };

        template < typename T >
        Pool< T >::Pool( ) : m_baton( __FILE__, __LINE__ )
        {
        }

        template < typename T >
        Pool< T >::~Pool( )
        {
        }

        template < typename T >
        void
        Pool< T >::Relinquish( value_type Source )
        {
            MutexLock l( m_baton, __FILE__, __LINE__ );

            relinquish( Source );
        }

        template < typename T >
        T Pool< T >::Request( value_type ( *CreateFunc )( ) )
        {
            MutexLock l( m_baton, __FILE__, __LINE__ );

            return ( request( CreateFunc ) );
        }

        template < typename T >
        void
        Pool< T >::relinquish( value_type Source )
        {
            m_available.push_back( Source );
        }

        template < typename T >
        T Pool< T >::request( value_type ( *CreateFunc )( ) )
        {
            value_type retval;

            if ( m_available.empty( ) )
            {
                retval = ( *CreateFunc )( );
            }
            else
            {
                retval = m_available.back( );
                m_available.pop_back( );
            }

            return retval;
        }

    } // namespace AL
} // namespace LDASTools

#endif /* LDASTOOLSAL__POOL_HH */
