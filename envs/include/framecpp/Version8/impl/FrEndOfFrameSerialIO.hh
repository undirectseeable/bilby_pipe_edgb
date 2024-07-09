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

#ifndef FrameCPP_VERSION_8__IMPL__FrEndOfFrameSerialIO_HH
#define FrameCPP_VERSION_8__IMPL__FrEndOfFrameSerialIO_HH

#include <boost/serialization/nvp.hpp>
#include <boost/serialization/string.hpp>
#include <boost/serialization/split_free.hpp>
#include <boost/serialization/version.hpp>

#include "framecpp/Common/FrameSpec.hh"
#include "framecpp/Version8/impl/HelperSerialIO.hh"
#include "framecpp/Version8/impl/FrEndOfFrameData.hh"

namespace FrameCPP
{
    namespace Version_8
    {
        class FrEndOfFrame;

        namespace FrEndOfFrameImpl
        {
            template < typename FR_END_OF_FRAME_T >
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
                    using boost::serialization::make_nvp;

                    // clang-format off
                    archiver&
                      BOOST_SERIALIZATION_NVP( run ) &
                      BOOST_SERIALIZATION_NVP( frame ) &
                      BOOST_SERIALIZATION_NVP( GTime )
                      ;
                    // clang-format on
                } // method - load

                template < class Archive >
                void
                save( Archive& archiver, const unsigned int version ) const
                {
                    using boost::serialization::make_nvp;
                    using FrameCPP::Version_8::FrEndOfFrame;

                    // clang-format off
                    archiver&
                      BOOST_SERIALIZATION_NVP( run ) &
                      BOOST_SERIALIZATION_NVP( frame ) &
                      BOOST_SERIALIZATION_NVP( GTime )
                      ;
                    // clang-format on
                } // method - save

                BOOST_SERIALIZATION_SPLIT_MEMBER( )
            }; // class - SerialIO

        } // namespace FrEndOfFrameImpl
    } // namespace Version_8
} // namespace FrameCPP

BOOST_CLASS_VERSION( FrameCPP::Version_8::FrEndOfFrame, 8 )

#endif /* FrameCPP_VERSION_8__IMPL__FrEndOfFrameSerialIO_HH */
