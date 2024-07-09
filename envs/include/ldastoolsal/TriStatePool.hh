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

#ifndef LDASTOOLSAL__TRI_STATE_POOL_HH
#define LDASTOOLSAL__TRI_STATE_POOL_HH

#include <stdexcept>
#include <list>

#include "ldastoolsal/Pool.hh"

namespace LDASTools
{
    namespace AL
    {
        //-------------------------------------------------------------------
        /// \brief Base class for objects to be stored in the TriStatePool
        ///
        /// This class describes the interface used by the TriStatePool
        /// class.
        //-------------------------------------------------------------------
        class TriStateInterface
        {
        protected:
            template < class Pool >
            friend class TriStatePool;

            //-----------------------------------------------------------------
            /// \brief Test if the object should be made immediate available
            ///
            /// Virtual method called to test if object should be made
            /// immedately available.
            ///
            /// \return True if the object can be immediately reused.
            //-----------------------------------------------------------------
            virtual bool makeAvailable( ) const;
        };

        inline bool
        TriStateInterface::makeAvailable( ) const
        {
            return ( false );
        }

        //-------------------------------------------------------------
        /// \brief Maintain a collection system calls
        //-------------------------------------------------------------
        template < typename T >
        class TriStatePool : public Pool< T >
        {
        public:
            typedef typename Pool< T >::value_type value_type;

            TriStatePool( );

        protected:
            virtual void relinquish( value_type Source );

            virtual value_type request( value_type ( *CreateFunc )( ) );

        private:
            typedef typename Pool< T >::pool_type pool_type;

            pool_type tri_state_pool;
        };

        template < typename T >
        TriStatePool< T >::TriStatePool( )
        {
        }

        template < typename T >
        void
        TriStatePool< T >::relinquish( value_type Source )
        {
            if ( Source->makeAvailable( ) )
            {
                Pool< T >::relinquish( Source );
                return;
            }
            tri_state_pool.push_back( Source );
        }

        template < typename T >
        typename TriStatePool< T >::value_type
            TriStatePool< T >::request( value_type ( *CreateFunc )( ) )
        {
            typename pool_type::iterator cur = tri_state_pool.begin( ),
                                         last = tri_state_pool.end( );
            while ( cur != last )
            {
                if ( ( *cur )->makeAvailable( ) )
                {
                    typename pool_type::iterator::value_type source = *cur;

                    // Remove from tri-state queue
                    cur = tri_state_pool.erase( cur );
                    // and make available for use
                    Pool< T >::relinquish( source );
                    continue;
                }
                ++cur;
            }
            return Pool< T >::request( CreateFunc );
        }

    } // namespace AL
} // namespace LDASTools

#endif /* LDASTOOLSAL__TRI_STATE_POOL_HH */
