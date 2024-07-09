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

#ifndef FrameCPP_VERSION_8__IMPL__FrDetectorData_HH
#define FrameCPP_VERSION_8__IMPL__FrDetectorData_HH

#include "ldastoolsal/types.hh"

#define FR_DETECTOR_LONGITUDE_TYPE REAL_8
#define FR_DETECTOR_LATITUDE_TYPE REAL_8
#define FR_DETECTOR_ELEVATION_TYPE REAL_4
#define FR_DETECTOR_ARM_X_AZIMUTH_TYPE REAL_4
#define FR_DETECTOR_ARM_Y_AZIMUTH_TYPE REAL_4
#define FR_DETECTOR_ARM_X_ALTITUDE_TYPE REAL_4
#define FR_DETECTOR_ARM_Y_ALTITUDE_TYPE REAL_4
#define FR_DETECTOR_ARM_X_MIDPOINT_TYPE REAL_4
#define FR_DETECTOR_ARM_Y_MIDPOINT_TYPE REAL_4
#define FR_DETECTOR_LOCAL_TIME_TYPE INT_4S

#if !defined( SWIGIMPORTED )
#include "framecpp/Version8/FrameSpec.hh"

#include "framecpp/Common/SearchContainer.hh"

#include "framecpp/Version8/impl/FrObjectMetaData.hh"

#include "framecpp/Version8/GPSTime.hh"
#include "framecpp/Version8/PTR_STRUCT.hh"

#include "framecpp/Version8/FrTable.hh"
#include "framecpp/Version8/FrVect.hh"
#endif /* ! defined(SWIGIMPORTED) */

#if !defined( SWIGIMPORTED )
namespace FrameCPP
{
    namespace Version_8
    {
        namespace FrDetectorImpl
        {
            class Data : public Impl::FrObjectMetaData< Data >
            {
            public:
                typedef Common::SearchContainer< FrVect, &FrVect::GetName >
                                                 aux_type;
                typedef aux_type::iterator       aux_iterator;
                typedef aux_type::const_iterator const_aux_iterator;

                typedef Common::SearchContainer< FrTable,
                                                 &FrTable::GetNameSlow >
                                                   table_type;
                typedef table_type::iterator       table_iterator;
                typedef table_type::const_iterator const_table_iterator;

                typedef std::string                     name_type;
                typedef char*                           prefix_type;
                typedef FR_DETECTOR_LONGITUDE_TYPE      longitude_type;
                typedef FR_DETECTOR_LATITUDE_TYPE       latitude_type;
                typedef FR_DETECTOR_ELEVATION_TYPE      elevation_type;
                typedef FR_DETECTOR_ARM_X_AZIMUTH_TYPE  armXazimuth_type;
                typedef FR_DETECTOR_ARM_Y_AZIMUTH_TYPE  armYazimuth_type;
                typedef FR_DETECTOR_ARM_X_ALTITUDE_TYPE armXaltitude_type;
                typedef FR_DETECTOR_ARM_Y_ALTITUDE_TYPE armYaltitude_type;
                typedef FR_DETECTOR_ARM_X_MIDPOINT_TYPE armXmidpoint_type;
                typedef FR_DETECTOR_ARM_Y_MIDPOINT_TYPE armYmidpoint_type;
                typedef FR_DETECTOR_LOCAL_TIME_TYPE     localTime_type;

                //-----------------------------------------------------------------
                /// \brief Default constructor
                ///
                /// \return
                ///     A new instance of a Data object
                //-----------------------------------------------------------------

                Data( ) : prefix{ ' ', ' ' }
                {
                }

                Data( const Data& Source ) = default;

                //-----------------------------------------------------------------
                /// \brief Retrieve the name of the instrument.
                ///
                /// \return
                ///     The name of the instrument.
                //-----------------------------------------------------------------
                inline const std::string&
                GetName( ) const
                {
                    return name;
                }

                //-----------------------------------------------------------------
                /// \brief Retrieve the name of the instrument.
                ///
                /// \return
                ///     The name of the instrument.
                //-----------------------------------------------------------------
                const std::string&
                GetNameSlow( ) const
                {
                    return ( GetName( ) );
                }

                //-----------------------------------------------------------------
                /// \brief Retrieve the prefix of the instrument.
                ///
                /// \return
                ///     The prefix for the instrument.
                //-----------------------------------------------------------------
                const CHAR*
                GetPrefix( ) const
                {
                    return prefix;
                }

                //-----------------------------------------------------------------
                /// \brief Retrieve the longitude of the detector vertex.
                ///
                /// \return
                ///     The longitude of the detector vertex.
                //-----------------------------------------------------------------
                longitude_type
                GetLongitude( ) const
                {
                    return longitude;
                }

                //-----------------------------------------------------------------
                /// \brief Retrieve the latitude of the detector vertex.
                ///
                /// \return
                ///     The latitude of the detector vertex.
                //-----------------------------------------------------------------
                latitude_type
                GetLatitude( ) const
                {
                    return latitude;
                }

                //-----------------------------------------------------------------
                /// \brief Retrieve the vertex elevation of the detector.
                ///
                /// \return
                ///     The vertex elevation of the detector.
                //-----------------------------------------------------------------
                elevation_type
                GetElevation( ) const
                {
                    return elevation;
                }

                //-----------------------------------------------------------------
                /// \brief Retrieve the orientation of X arm of the detector.
                ///
                /// \return
                ///     The orientation of the X arm of the detector.
                //-----------------------------------------------------------------
                armXazimuth_type
                GetArmXazimuth( ) const
                {
                    return armXazimuth;
                }

                //-----------------------------------------------------------------
                /// \brief Retrieve the orientation of Y arm of the detector.
                ///
                /// \return
                ///     The orientation of the Y arm of the detector.
                //-----------------------------------------------------------------
                armYazimuth_type
                GetArmYazimuth( ) const
                {
                    return armYazimuth;
                }

                //-----------------------------------------------------------------
                /// \brief Retrieve the altitude angle of X arm of the detector.
                ///
                /// \return
                ///     The altitude angle of the X arm of the detector.
                //-----------------------------------------------------------------
                armXaltitude_type
                GetArmXaltitude( ) const
                {
                    return armXaltitude;
                }

                //-----------------------------------------------------------------
                /// \brief Retrieve the altitude angle of Y arm of the detector.
                ///
                /// \return
                ///     The altitude angle of the Y arm of the detector.
                //-----------------------------------------------------------------
                armYaltitude_type
                GetArmYaltitude( ) const
                {
                    return armYaltitude;
                }

                //-----------------------------------------------------------------
                /// \brief Retrieve the midpoint of the X arm of the detector.
                ///
                /// \return
                ///     The midpoint of the X arm of the detector.
                //-----------------------------------------------------------------
                armXmidpoint_type
                GetArmXmidpoint( ) const
                {
                    return armXmidpoint;
                }

                //-----------------------------------------------------------------
                /// \brief Retrieve the midpoint of the Y arm of the detector.
                ///
                /// \return
                ///     The midpoint of the Y arm of the detector.
                //-----------------------------------------------------------------
                armYmidpoint_type
                GetArmYmidpoint( ) const
                {
                    return armYmidpoint;
                }

                //-----------------------------------------------------------------
                /// \brief Retrieve the local seasonal time.
                ///
                /// \return
                ///     The local seasonal time.
                //-----------------------------------------------------------------
                localTime_type
                GetLocalTime( ) const
                {
                    return localTime;
                }

                //-----------------------------------------------------------------
                /// \brief Identifier for vector for user-provided information.
                ///
                /// \return
                ///     A constant reference to the user-provided information.
                //-----------------------------------------------------------------
                const aux_type&
                RefAux( ) const
                {
                    return aux;
                }

                //-----------------------------------------------------------------
                /// \brief Identifier for vector for user-provided information.
                ///
                /// \return
                ///     A reference to the user-provided information.
                //-----------------------------------------------------------------
                aux_type&
                RefAux( )
                {
                    return aux;
                }

                //-----------------------------------------------------------------
                /// \brief Identifier for user-provided information in table
                /// format.
                ///
                /// \return
                ///     A constant reference to the user-provided table
                ///     information.
                //-----------------------------------------------------------------
                const table_type&
                RefTable( ) const
                {
                    return table;
                }

                //-----------------------------------------------------------------
                /// \brief Identifier for user-provided information in table
                /// format.
                ///
                /// \return
                ///     A reference to the user-provided table information.
                //-----------------------------------------------------------------
                table_type&
                RefTable( )
                {
                    return table;
                }

                inline bool
                operator==( Data const& RHS ) const
                {
#define CMP__( X ) ( X == RHS.X )

                    return ( ( &RHS == this ) ||
                             ( CMP__( name ) && CMP__( prefix[ 0 ] ) &&
                               CMP__( prefix[ 1 ] ) && CMP__( longitude ) &&
                               CMP__( latitude ) && CMP__( elevation ) &&
                               CMP__( armXazimuth ) && CMP__( armYazimuth ) &&
                               CMP__( armXaltitude ) && CMP__( armYaltitude ) &&
                               CMP__( armXmidpoint ) && CMP__( armYmidpoint ) &&
                               CMP__( localTime ) && CMP__( aux ) &&
                               CMP__( table ) ) );

#undef CMP__
                }

            protected:
                static const constexpr INT_2U MAX_REF = 2;

                //---------------------------------------------------------------
                /// Instrument name as described here
                /// (e.g., Virgo; GEO_600; TAMA_300; LHO_2k; LLO_4k; 40M;
                /// PNI; simulated pseudo data - model version etc.)
                //---------------------------------------------------------------
                name_type name;
                //---------------------------------------------------------------
                /// Channel prefix for this detector as described here.
                //---------------------------------------------------------------
                CHAR prefix[ 2 ];
                //---------------------------------------------------------------
                /// Detector vertex longitude, geographical coordinates:
                /// radians; Value > 0 >= E of Greenwich
                /// (-pi < Longitude <= +pi)
                //---------------------------------------------------------------
                longitude_type longitude;
                //---------------------------------------------------------------
                /// Detector vertex latitude, geographical coordinated:
                /// radians; Value >= 0 >= N of Equator
                /// (-pi/2 < Latitude <= +pi/2).
                //---------------------------------------------------------------
                latitude_type latitude;
                //---------------------------------------------------------------
                /// Vertex elevation, in meters, relative to WGS84
                /// ellipsoid.
                //---------------------------------------------------------------
                elevation_type elevation;
                //---------------------------------------------------------------
                /// Orientation of X arm, measured in radians East of North
                /// (0 <= ArmXazimuth < 2pi)
                //---------------------------------------------------------------
                armXazimuth_type armXazimuth;
                //---------------------------------------------------------------
                /// Orientation of Y arm, measured in radians East of North
                /// (0 <= ArmYazimuth < 2pi)
                //---------------------------------------------------------------
                armYazimuth_type armYazimuth;
                //---------------------------------------------------------------
                /// Altitude (pitch) angle to X arm, measured in radians
                /// above horizon (local tangent to WGS84 ellipsoid)
                /// -pi/2 < ArmXaltitude <= pi/2
                //---------------------------------------------------------------
                armXaltitude_type armXaltitude;
                //---------------------------------------------------------------
                /// Altitude (pitch) angle to Y arm, measured in radians
                /// above horizon (local tangent to WGS84 ellipsoid)
                /// -pi/2 < ArmXaltitude <= pi/2
                //---------------------------------------------------------------
                armYaltitude_type armYaltitude;
                //---------------------------------------------------------------
                /// Distance between the detector vertex and the middle of
                /// the X cavity (meters) (should be zero for bars).
                //---------------------------------------------------------------
                armXmidpoint_type armXmidpoint;
                //---------------------------------------------------------------
                /// Distance between the detector vertex and the middle of
                /// the Y cavity (meters) (should be zero for bars).
                //---------------------------------------------------------------
                armYmidpoint_type armYmidpoint;
                //---------------------------------------------------------------
                /// Local seasonal time - UTC in seconds.
                /// If localTime % 1800 != 0 then localTime is undefined.
                //---------------------------------------------------------------
                localTime_type localTime;
                //---------------------------------------------------------------
                /// Indentifier for user-provided structure for additional
                /// detector data.
                //---------------------------------------------------------------
                aux_type aux;
                //---------------------------------------------------------------
                /// Identifier fo ruser-provided table structure for
                /// additional detector data.
                //---------------------------------------------------------------
                table_type table;
            };
        } // namespace FrDetectorImpl
    } // namespace Version_8
} // namespace FrameCPP

FR_OBJECT_META_DATA_DECLARE( FrDetectorImpl )

#endif /* ! defined(SWIGIMPORTED) */

#endif /* FrameCPP_VERSION_8__IMPL__FrDetectorData_HH */
