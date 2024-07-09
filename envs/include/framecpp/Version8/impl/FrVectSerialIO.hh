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

#ifndef FrameCPP_VERSION_8__IMPL__FrVectSerialIO_HH
#define FrameCPP_VERSION_8__IMPL__FrVectSerialIO_HH

#if !defined( SWIGIMPORTED )
#include <boost/serialization/binary_object.hpp>
#include <boost/serialization/nvp.hpp>
#include <boost/serialization/string.hpp>
#include <boost/serialization/split_member.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/version.hpp>
#endif /* !defined( SWIGIMPORTED ) */

#if !defined( SWIGIMPORTED )
#include "framecpp/Common/FrameSpec.hh"
#include "framecpp/Version8/impl/DimensionSerialIO.hh"
#include "framecpp/Version8/impl/HelperSerialIO.hh"
#endif /* !defined( SWIGIMPORTED ) */
#include "framecpp/Version8/impl/FrVectData.hh"

#if !defined( SWIGIMPORTED )
namespace FrameCPP
{
    namespace Version_8
    {
        class FrVect;
        namespace FrVectImpl
        {
            template < typename FR_VECT_T >
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
                save( Archive& ar, const unsigned int version ) const
                {
                    using boost::serialization::make_binary_object;
                    using boost::serialization::make_nvp;

                    ar& make_nvp( "name", m_data.name ) &
                        make_nvp( "compress", m_data.compress ) &
                        make_nvp( "type", m_data.type ) &
                        make_nvp( "nData", m_data.nData ) &
                        make_nvp( "nBytes", m_data.nBytes );
                    if ( m_data.nBytes > 0 )
                    {
                        auto serialized = make_binary_object(
                            &( m_data.data[ 0 ] ), m_data.nBytes );
                        ar& make_nvp( "data", serialized );
                    }
#if 0
                    ar& make_nvp( "dim", m_data.dimension );
#endif /* 0 */
                    ar& make_nvp( "unitY", m_data.unitY );
                }

                template < class Archive >
                void
                load( Archive& ar, const unsigned int version )
                {
                    using boost::serialization::make_binary_object;
                    using boost::serialization::make_nvp;

                    ar& make_nvp( "name", m_data.name ) &
                        make_nvp( "compress", m_data.compress ) &
                        make_nvp( "type", m_data.type ) &
                        make_nvp( "nData", m_data.nData ) &
                        make_nvp( "nBytes", m_data.nBytes );
                    if ( m_data.nBytes > 0 )
                    {
                        m_data.data.reset(
                            new data_type::element_type[ m_data.nBytes ] );
                        auto serialized = make_binary_object(
                            &( m_data.data[ 0 ] ), m_data.nBytes );
                        ar& make_nvp( "data", serialized );
                    }
#if 0
                    ar& make_nvp( "dim", m_data.dimension );
#endif /* 0 */
                    ar& make_nvp( "unitY", m_data.unitY );
                }
                BOOST_SERIALIZATION_SPLIT_MEMBER( )
            };

        } // namespace FrVectImpl
    } // namespace Version_8
} // namespace FrameCPP

BOOST_CLASS_VERSION( FrameCPP::Version_8::FrVect, 8 )

#endif /* !defined( SWIGIMPORTED ) */

#endif /* FrameCPP_VERSION_8__IMPL__FrVectSerialIO_HH */
