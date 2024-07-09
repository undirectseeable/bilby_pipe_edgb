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

#ifndef FrameCPP_VERSION_8__IMPL__DimensionSerialIO_HH
#define FrameCPP_VERSION_8__IMPL__DimensionSerialIO_HH

#include <boost/serialization/nvp.hpp>
#include <boost/serialization/string.hpp>
#include <boost/serialization/split_free.hpp>
#include <boost/serialization/version.hpp>

#include "framecpp/Version8/Dimension.hh"

namespace boost
{
    namespace serialization
    {
        // Dimension

        template < class Archive >
        void
        load( Archive&                        archiver,
              FrameCPP::Version_8::Dimension& dimension,
              const unsigned int              version )
        {
            using FrameCPP::Version_8::Dimension;

            Dimension::nx_type     nx;
            Dimension::dx_type     dx;
            Dimension::startX_type startX;
            std::string  unitX;

            archiver& BOOST_SERIALIZATION_NVP( nx ) &
                BOOST_SERIALIZATION_NVP( dx ) &
                BOOST_SERIALIZATION_NVP( startX ) &
                BOOST_SERIALIZATION_NVP( unitX );

            dimension.SetNx( nx );
            dimension.SetDx( dx );
            dimension.SetStartX( startX );
            dimension.SetUnitX( unitX );
        }

        template < class Archive >
        void
        save( Archive&                              archiver,
              const FrameCPP::Version_8::Dimension& dimension,
              const unsigned int                    version )
        {
            using boost::serialization::make_nvp;
            using FrameCPP::Version_8::Dimension;

            auto nx{ dimension.GetNx( ) };
            auto dx{ dimension.GetDx( ) };
            auto startX{ dimension.GetStartX( ) };
            auto unitX{ static_cast< const std::string& >( dimension.GetUnitX( ) ) };

            archiver& BOOST_SERIALIZATION_NVP( nx ) &
              BOOST_SERIALIZATION_NVP( dx ) &
              BOOST_SERIALIZATION_NVP( startX ) &
              BOOST_SERIALIZATION_NVP( unitX );
        }

    } // namespace serialization
} // namespace boost

BOOST_SERIALIZATION_SPLIT_FREE( FrameCPP::Version_8::Dimension )

#endif /* FrameCPP_VERSION_8__IMPL__DimensionSerialIO_HH */
