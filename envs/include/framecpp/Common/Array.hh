//
// LDASTools frameCPP - A library implementing the LIGO/Virgo frame
// specification
//
// Copyright (C) 2018 California Institute of Technology
//
// LDASTools frameCPP is free software; you may redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 (GPLv2) of the
// License or at your discretion, any later version.
//
// LDASTools frameCPP is distributed in the hope that it will be useful, but
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

#ifndef FrameCPP__COMMON__Array_HH
#define FrameCPP__COMMON__Array_HH

#if !defined( SWIGIMPORTED )
#include <vector>
#endif /* ! defined(SWIGIMPORTED) */

#include "framecpp/Common/FrameSpec.hh"

namespace FrameCPP
{
    namespace Common
    {
        //-------------------------------------------------------------------
        /// \brief Storage class for array data streams of a frame
        ///
        /// This template manages arrays intended to be part of a
        /// frame stream.
        ///
        /// \tparam N
        ///     The frame data type used to store the array size within
        ///     the stream.
        /// \tparam T
        ///     The element type to be used for storing the individual
        ///     elements of the array.
        ///
        //-------------------------------------------------------------------
        template < typename N, typename T >
        class Array : public std::vector< T >
        {
        public:
            typedef N                                         n_size_type;
            typedef typename std::vector< T >::const_iterator const_iterator;

            cmn_streamsize_type Bytes( const StreamBase& Stream ) const;

            cmn_streamsize_type bytes( ) const;

            bool operator==( const Array& RHS ) const;

        private:
        };

        //-------------------------------------------------------------------
        /// \brief Number of bytes needed by the frame stream for this object.
        ///
        /// This member returns the number of bytes needed to store this
        /// object to the specified stream.
        ///
        /// \param[in] Stream
        ///     The frame stream being used.
        ///
        /// \return
        ///     Number of bytes needed to store this object to the specified
        ///     stream.
        //-------------------------------------------------------------------
        template < typename N, typename T >
        cmn_streamsize_type
        Array< N, T >::Bytes( const StreamBase& Stream ) const
        {
            cmn_streamsize_type retval = sizeof( n_size_type );

            for ( const_iterator cur = this->begin( ), last = this->end( );
                  cur != last;
                  ++cur )
            {
                retval += cur->Bytes( Stream );
            }
            return retval;
        }

        //-------------------------------------------------------------------
        /// \brief Number of bytes needed by the frame stream for this object.
        ///
        /// This member returns the number of bytes needed to store this
        /// object.
        ///
        /// \return
        ///     Number of bytes needed to store this object.
        //-------------------------------------------------------------------
        template < typename N, typename T >
        cmn_streamsize_type
        Array< N, T >::bytes( ) const
        {
            cmn_streamsize_type retval = sizeof( n_size_type );

            for ( const_iterator cur = this->begin( ), last = this->end( );
                  cur != last;
                  ++cur )
            {
                retval += cur->bytes( );
            }
            return retval;
        }

        //-------------------------------------------------------------------
        /// \brief Compare the equality of two Array objects
        ///
        /// This member returns true if the two Array objects are
        /// equivelant.
        ///
        /// \param[in] RHS
        ///     Object appearing on the right hand side of the
        ///     equality operator.
        ///
        /// \return
        ///     True if the two objects are equal; false otherwise
        //-------------------------------------------------------------------
        template < typename N, typename T >
        bool
        Array< N, T >::operator==( const Array& RHS ) const
        {
            bool retval = ( &RHS == this );

            if ( retval == false )
            {
                if ( this->size( ) == RHS.size( ) )
                {
                    retval = true;
                    for ( const_iterator rhs_cur = RHS.begin( ),
                                         cur = this->begin( ),
                                         last = this->end( );
                          cur != last;
                          ++cur, ++rhs_cur )
                    {
                        if ( !( *cur == *rhs_cur ) )
                        {
                            retval = false;
                            break;
                        }
                    }
                }
            }
            return retval;
        }
    } // namespace Common
} // namespace FrameCPP
#endif /* FrameCPP__COMMON__Array_HH */
