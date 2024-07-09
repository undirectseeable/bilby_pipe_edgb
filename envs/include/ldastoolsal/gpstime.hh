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

#ifndef GENERAL__GPS_TIME_HH
#define GENERAL__GPS_TIME_HH

#if !defined( SWIGIMPORTED )
#include <stdexcept>
#include <iostream>
#endif /* ! defined(SWIGIMPORTED) */

#include "ldastoolsal/ErrorLog.hh"
#include "ldastoolsal/types.hh"

const REAL_8 NANOSECOND = 10E-9;
const REAL_8 NANOSECOND_MULTIPLIER = 10E+9;
const INT_4U NANOSECOND_INT_MULTIPLIER = 1000000000;
const INT_8U NANOSECOND_INT_64_MULTIPLIER = 1000000000;

namespace LDASTools
{
    namespace AL
    {
        //---------------------------------------------------------------
        /// \brief GPS time class.
        ///
        /// This class is designed to maintain GPS time information.
        /// A UTC time can be used to seed the value.
        ///
        /// \note
        /// <UL>
        ///   <LI>
        ///     Example source http://maia.usno.navy.mil/ser7/tai-utc.dat
        ///   </LI>
        ///
        ///   <LI>
        ///     The environment variable GPS_LEAPSECOND_FILE
        ///     can be set to specify a local GPS leap second
        ///     data file.
        ///   </LI>
        ///
        ///   <LI>
        ///     If a data file exists, it is checked perioticly for
        ///     updates.
        ///   </LI>
        ///
        ///   <LI>
        ///    	The class is only valid for times on or after
        ///	January 1st, 1970 at 00:00 GMT.
        ///   </LI>
        ///
        /// </UL>
        //---------------------------------------------------------------
        class GPSTime
        {

        public:
            //-----------------------------------------------------------
            /// \brief Type representing the second portion
            //-----------------------------------------------------------
            typedef INT_4U seconds_type;
            //-----------------------------------------------------------
            /// \brief Type representing the nanosecond portion
            //-----------------------------------------------------------
            typedef INT_4U nanoseconds_type;

            //-----------------------------------------------------------
            /// \brief Type represting the whole GPS time in nanoseconds
            //-----------------------------------------------------------
            typedef INT_8U gpsnanoseconds_type;

            //-----------------------------------------------------------
            /// \brief Enumerated type to specify time format.
            //-----------------------------------------------------------
            typedef enum
            {
                /// Universal Time Coordinated
                UTC = 0,
                /// Global Positioning %System Time
                GPS
            } unit_type;

            //-----------------------------------------------------------
            /// \brief The default time unit
            //-----------------------------------------------------------
            static const unit_type DEFAULT_TIME_UNIT_TYPE;

            //-----------------------------------------------------------
            /// \brief Constructor - default
            //-----------------------------------------------------------
            GPSTime( );

            //-----------------------------------------------------------
            /// \brief Constructor - copy
            //-----------------------------------------------------------
            GPSTime( const GPSTime& );

            //-----------------------------------------------------------
            /// \brief Constructor
            //-----------------------------------------------------------
            GPSTime( const seconds_type     seconds,
                     const nanoseconds_type nanoseconds,
                     unit_type              Units = DEFAULT_TIME_UNIT_TYPE );

            //-----------------------------------------------------------
            /// \brief Destructor
            //-----------------------------------------------------------
            ~GPSTime( );

            //-----------------------------------------------------------
            /// \brief Second portion of GPS time.
            //-----------------------------------------------------------
            seconds_type GetSeconds( ) const;

            //-----------------------------------------------------------
            /// \brief Second portion of GPS time according to units.
            //-----------------------------------------------------------
            nanoseconds_type GetSeconds( const unit_type Units ) const;

            //-----------------------------------------------------------
            /// \brief Nanosecond portion of GPS time.
            //-----------------------------------------------------------
            nanoseconds_type GetNanoseconds( ) const;

            //-----------------------------------------------------------
            /// \brief GPS as a floating point number.
            //-----------------------------------------------------------
            REAL_8 GetTime( ) const;

            //-----------------------------------------------------------
            /// \brief Retrieve the number of leap seconds for stored time.
            //-----------------------------------------------------------
            INT_2U GetLeapSeconds( ) const;

            //-----------------------------------------------------------
            /// \brief Return the time in nanosecond units
            ///
            /// \return
            ///      The time value as the number of nanoseconds since
            ///	     the start of GPS time.
            //-----------------------------------------------------------
            gpsnanoseconds_type GPSNanoseconds( ) const;

            //-----------------------------------------------------------
            /// \brief  Sets the object to the current GPS time.
            //-----------------------------------------------------------
            void Now( );

            //-----------------------------------------------------------
            /// Helper function to make it compatable with Time class of
            ///   framecpp
            //-----------------------------------------------------------
            seconds_type getSec( ) const;

            //-----------------------------------------------------------
            /// Helper function to make it compatable with Time class of
            ///   framecpp
            //-----------------------------------------------------------
            nanoseconds_type getNSec( ) const;

            //-----------------------------------------------------------
            /// \brief  Returns the time "now" as a GPSTime
            /// \return GPSTime the current time, in GPSTime form
            //-----------------------------------------------------------
            static GPSTime NowGPSTime( );

            //-----------------------------------------------------------
            /// \brief Assignment operator
            //-----------------------------------------------------------
            GPSTime& operator=( const GPSTime& );

            //-----------------------------------------------------------
            /// \brief Addition assignment
            //-----------------------------------------------------------
            GPSTime& operator+=( const double& );

            //-----------------------------------------------------------
            /// \brief Subtraction assignment
            //-----------------------------------------------------------
            GPSTime& operator-=( const double& );

        protected:
            //-----------------------------------------------------------
            /// \brief  Returns the time "now" as a GPSTime
            /// \return GPSTime the current time, in GPSTime form
            //-----------------------------------------------------------
            static GPSTime now( );

        private:
            friend void ErrorLog::operator( )( state              State,
                                               const char*        Filename,
                                               const int          Line,
                                               const std::string& Message,
                                               bool               EOL );
            seconds_type          m_seconds;
            nanoseconds_type      m_nanoseconds;

        }; // class GPSTime

        inline REAL_8
        GPSTime::GetTime( ) const
        {
            return ( m_seconds + ( m_nanoseconds / NANOSECOND_MULTIPLIER ) );
        }

        inline GPSTime::nanoseconds_type
        GPSTime::GetNanoseconds( ) const
        {
            return m_nanoseconds;
        }

        inline GPSTime::seconds_type
        GPSTime::GetSeconds( ) const
        {
            return m_seconds;
        }

        //---------------------------------------------------------------
        /// Helper function to make it compatable with Time class of
        /// framecpp
        //---------------------------------------------------------------
        inline GPSTime::seconds_type
        GPSTime::getSec( ) const
        {
            return GetSeconds( );
        }

        //---------------------------------------------------------------
        /// Helper function to make it compatable with Time class of
        /// framecpp
        //---------------------------------------------------------------
        inline GPSTime::nanoseconds_type
        GPSTime::getNSec( ) const
        {
            return GetNanoseconds( );
        }

        //---------------------------------------------------------------
        /// This routine returns the time value as the number of
        /// nanoseconds that have elapsed since the start of GPS time.
        //---------------------------------------------------------------
        inline GPSTime::gpsnanoseconds_type
        GPSTime::GPSNanoseconds( ) const
        {
            gpsnanoseconds_type retval( GetSeconds( ) );
            return ( ( retval * NANOSECOND_INT_64_MULTIPLIER ) +
                     ( GetNanoseconds( ) ) );
        }

        //---------------------------------------------------------------
        /// \brief Establish the filename which contains the leap seconds
        //---------------------------------------------------------------
        void SetOffsetTableFilename( const std::string& Filename );

        //---------------------------------------------------------------
        /// \brief Addition operator
        //---------------------------------------------------------------
        GPSTime operator+( const GPSTime&, const double& );
        //---------------------------------------------------------------
        /// \brief Addition operator
        //---------------------------------------------------------------
        GPSTime operator+( const double&, const GPSTime& );

        //---------------------------------------------------------------
        /// \brief Subtraction operator
        //---------------------------------------------------------------
        GPSTime operator-( const GPSTime&, const double& );
        //---------------------------------------------------------------
        /// \brief Subtraction operator
        //---------------------------------------------------------------
        double operator-( const GPSTime&, const GPSTime& );

        //---------------------------------------------------------------
        /// \brief Equality operator
        //---------------------------------------------------------------
        bool operator==( const GPSTime&, const GPSTime& );
        //---------------------------------------------------------------
        /// \brief Inequality operator
        //---------------------------------------------------------------
        bool operator!=( const GPSTime&, const GPSTime& );

        //---------------------------------------------------------------
        /// \brief Less than operator
        //---------------------------------------------------------------
        bool operator<( const GPSTime&, const GPSTime& );
        //---------------------------------------------------------------
        /// \brief Greater than operator
        //---------------------------------------------------------------
        bool operator>( const GPSTime&, const GPSTime& );

        //---------------------------------------------------------------
        /// \brief Less than or equal to operator
        //---------------------------------------------------------------
        bool operator<=( const GPSTime&, const GPSTime& );
        //---------------------------------------------------------------
        /// \brief Greater than or equal to operator
        //---------------------------------------------------------------
        bool operator>=( const GPSTime&, const GPSTime& );

        //---------------------------------------------------------------
        /// \brief Output operator
        //---------------------------------------------------------------
        std::ostream& operator<<( std::ostream& Stream, const GPSTime& Time );
    } // namespace AL

} // namespace LDASTools

#endif // GENERAL__GPS_TIME_HH
