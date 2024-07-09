//
// LDASTools frameCPP - A library implementing the LIGO/Virgo frame
// specification
//
// Copyright (C) 2019 California Institute of Technology
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

#ifndef FrameCPP_VERSION_8__IMPL__FrEventSerialIO_HH
#define FrameCPP_VERSION_8__IMPL__FrEventSerialIO_HH

#if defined( __cplusplus )

#if !defined( SWIGIMPORTED )
#include <boost/serialization/nvp.hpp>
#include <boost/serialization/string.hpp>
#include <boost/serialization/split_free.hpp>
#include <boost/serialization/version.hpp>
#endif /* !defined( SWIGIMPORTED ) */

#if !defined( SWIGIMPORTED )
#include "framecpp/Common/FrameSpec.hh"
#include "framecpp/Version8/impl/HelperSerialIO.hh"
#endif /* !defined( SWIGIMPORTED ) */

#include "framecpp/Version8/impl/FrEventData.hh"

#if !defined( SWIGIMPORTED )
namespace FrameCPP
{
    namespace Version_8
    {
        class FrEvent;

        namespace FrEventImpl
        {
            template < typename FR_EVENT_T >
            class SerialIO : public virtual Data
            {
            public:
                //-------------------------------------------------------
                //
                //-------------------------------------------------------
                SerialIO( )
                {
                }

            private:
                friend class boost::serialization::access;

                template < class Archive >
                void
                load( Archive& archiver, const unsigned int version )
                {
                    // clang-format off
                    archiver
                      & BOOST_SERIALIZATION_NVP( name )
#if 0
                      & BOOST_SERIALIZATION_NVP( comment )
                      & BOOST_SERIALIZATION_NVP( inputs )
#if 0
                      & BOOST_SERIALIZATION_NVP( GTime )
#endif /* 0 */
                      & BOOST_SERIALIZATION_NVP( timeBefore )
                      & BOOST_SERIALIZATION_NVP( timeAfter )
                      & BOOST_SERIALIZATION_NVP( eventStatus )
                      & BOOST_SERIALIZATION_NVP( amplitude )
                      & BOOST_SERIALIZATION_NVP( probability )
                      & BOOST_SERIALIZATION_NVP( statistics )
#if 0
                      & BOOST_SERIALIZATION_NVP( Params )
                      & BOOST_SERIALIZATION_NVP( data )
                      & BOOST_SERIALIZATION_NVP( table )
#endif /* 0 */
#endif /* 0 */
                      ;
                    // clang-format on
                } // method - load

                template < class Archive >
                void
                save( Archive& archiver, const unsigned int version ) const
                {
                    // clang-format off
                    archiver
                      & BOOST_SERIALIZATION_NVP( name )
#if 0
                      & BOOST_SERIALIZATION_NVP( comment )
                      & BOOST_SERIALIZATION_NVP( inputs )
#if 0
                      & BOOST_SERIALIZATION_NVP( GTime )
#endif /* 0 */
                      & BOOST_SERIALIZATION_NVP( timeBefore )
                      & BOOST_SERIALIZATION_NVP( timeAfter )
                      & BOOST_SERIALIZATION_NVP( eventStatus )
                      & BOOST_SERIALIZATION_NVP( amplitude )
                      & BOOST_SERIALIZATION_NVP( probability )
                      & BOOST_SERIALIZATION_NVP( statistics )
#if 0
                      & BOOST_SERIALIZATION_NVP( Params )
                      & BOOST_SERIALIZATION_NVP( data )
                      & BOOST_SERIALIZATION_NVP( table )
#endif /* 0 */
#endif /* 0 */
                      ;
                    // clang-format on
                } // method - save

                BOOST_SERIALIZATION_SPLIT_MEMBER( )
            }; // class - SerialIO

        } // namespace FrEventImpl
    } // namespace Version_8
} // namespace FrameCPP

BOOST_CLASS_VERSION( FrameCPP::Version_8::FrEvent, 8 )

#endif /* !defined( SWIGIMPORTED ) */

#endif /* defined( __cplusplus ) */

#endif /* FrameCPP_VERSION_8__IMPL__FrEventSerialIO_HH */
