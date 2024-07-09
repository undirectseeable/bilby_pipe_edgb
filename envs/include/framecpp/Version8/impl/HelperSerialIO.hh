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

#ifndef FrameCPP_VERSION_8__IMPL__HelperSerialIO_HH
#define FrameCPP_VERSION_8__IMPL__HelperSerialIO_HH

#include <boost/serialization/nvp.hpp>
#include <boost/serialization/string.hpp>
#include <boost/serialization/split_free.hpp>
#include <boost/serialization/version.hpp>

#include "ldastoolsal/gpstime.hh"

namespace boost
{
  namespace serialization
  {
    // GPS Time

    template<class Archive>
    void load( Archive& archiver, LDASTools::AL::GPSTime& gpstime, const unsigned int version)
    {
      using LDASTools::AL::GPSTime;

      GPSTime::seconds_type GTimeS;
      GPSTime::nanoseconds_type GTimeN;

      archiver & BOOST_SERIALIZATION_NVP( GTimeS )
        & BOOST_SERIALIZATION_NVP( GTimeN );

      gpstime = GPSTime( GTimeS, GTimeN );
    }

    template<class Archive>
    void save( Archive& archiver, const LDASTools::AL::GPSTime& gpstime, const unsigned int version)
    {
      using LDASTools::AL::GPSTime;

      GPSTime::seconds_type GTimeS( gpstime.GetSeconds( ) );
      GPSTime::nanoseconds_type GTimeN( gpstime.GetNanoseconds( ) );

      archiver & BOOST_SERIALIZATION_NVP( GTimeS )
        & BOOST_SERIALIZATION_NVP( GTimeN );
    }

  }
}

BOOST_SERIALIZATION_SPLIT_FREE( LDASTools::AL::GPSTime )

#endif /* FrameCPP_VERSION_8__IMPL__HelperSerialIO_HH */
