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

#ifndef GENERAL__PROFILE_HH
#define GENERAL__PROFILE_HH

#if !defined( SWIGIMPORTED )
#include <string>
#include <sstream>
#endif /* ! defined(SWIGIMPORTED) */

#include "ldastoolsal/gpstime.hh"

namespace LDASTools
{
    namespace AL
    {
        //---------------------------------------------------------------------
        /// \brief Provide profiling information
        ///
        /// This class is intended to be used for debugging purposes.
        /// It records the the time the instance was instantiated and then
        /// reports the differnce between the current time and the instantiated
        /// time so a developer can evaluate the speed of a routine.
        //---------------------------------------------------------------------
        class Profile
        {
        public:
            //-------------------------------------------------------------------
            /// \brief Constructor
            ///
            /// \param Header
            ///     This is a message which is to appear at the beginning of
            ///     each line of output.
            ///     It most commonly will be the fully qualified name of the
            ///     function or method that was invoked.
            //-------------------------------------------------------------------
            Profile( const char* Header );

            //-------------------------------------------------------------------
            /// \brief Output profiling information
            ///
            /// \param Filename
            ///     The name of the file being profiled.
            /// \param Line
            ///     The line number inside the file being profiled.
            /// \param Message
            ///     Text to appear immediately following the Header given
            ///     at instantiation.
            ///
            /// \return
            ///     The profiling data formatted as a string.
            //-------------------------------------------------------------------
            std::string operator( )( const char* Filename,
                                     size_t      Line,
                                     const char* Message = "" );

        private:
            const char* m_header;
            GPSTime     m_start;
            GPSTime     m_previous;
            GPSTime     m_now;
        };

        inline Profile::Profile( const char* Header ) : m_header( Header )
        {
            m_start.Now( );
            m_previous.Now( );
        }

        inline std::string
        Profile::
        operator( )( const char* Filename, size_t Line, const char* Message )
        {
            std::ostringstream msg;

            m_now.Now( );

            msg << m_header << Message << " dt: " << ( m_now - m_previous )
                << " cum: " << ( m_now - m_start ) << " [ line: " << Line
                << " file: " << Filename << " ]";
            m_previous = m_now;

            return msg.str( );
        }
    } // namespace AL
} // namespace LDASTools

#endif /* GENERAL__PROFILE_HH */
