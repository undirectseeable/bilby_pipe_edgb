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

#ifndef FRAMECPP__FRAME_FILENAME_HH
#define FRAMECPP__FRAME_FILENAME_HH

#include <string>

#include "ldastoolsal/ldasexception.hh"

namespace FrameCPP
{
    namespace Common
    {
        /// \brief Class to parse frame filename
        ///
        /// This implemnetation is based on the document LIGO-T010150
        class FrameFilename
        {
        public:
            typedef unsigned int gps_seconds_type;
            typedef unsigned int total_time_interval_type;

            /// \brief Exception describing a corrupted frame file name.
            class InvalidFrameFilename : public LdasException
            {
            public:
                InvalidFrameFilename( const std::string& Filename,
                                      const std::string& Spec,
                                      const char*        File,
                                      size_t             Line );

            private:
                static std::string format( const std::string& Filename,
                                           const std::string& Spec );
            };

            /// \brief Constructor
            FrameFilename( const std::string& Filename );
            /// \brief Return the base filename
            const std::string& Base( ) const;
            /// \brief Return the directory component of the filename
            const std::string& Dir( ) const;
            /// \brief Return the description of the contents of a file
            const std::string& D( ) const;
            /// \brief Return the GPS start time in seconds of the first frame
            /// in the
            // file
            gps_seconds_type G( ) const;
            /// \brief Return the source of the data
            const std::string& S( ) const;
            /// \brief Return the total time interval covered by the file, in
            /// seconds
            total_time_interval_type T( ) const;
            /// \brief Return the extension component of the filename
            const std::string& Ext( ) const;

        private:
            /// \brief Name of document specifying LDAS' naming convetion for
            /// frame files
            static const std::string m_spec;

            /// \brief Origional text of filename
            std::string m_filename;
            /// \brief S component of filename
            std::string m_s;
            /// \brief D component of filename
            std::string m_d;
            /// \brief G component of filename
            gps_seconds_type m_g;
            /// \brief T component of filename
            total_time_interval_type m_tt;
            std::string              m_ext;
            /// \brief Base component of the filename
            std::string m_base;
            /// \brief Directory component of the filename
            std::string m_directory;
            /// \brief state indicating that the name comforms to the spec
            bool m_good;
        }; // class FrameFilename

        inline const std::string&
        FrameFilename::Base( ) const
        {
            if ( !m_good )
            {
                throw InvalidFrameFilename(
                    m_filename, m_spec, __FILE__, __LINE__ );
            }
            return m_base;
        }

        inline const std::string&
        FrameFilename::Dir( ) const
        {
            if ( !m_good )
            {
                throw InvalidFrameFilename(
                    m_filename, m_spec, __FILE__, __LINE__ );
            }
            return m_directory;
        }

        inline const std::string&
        FrameFilename::D( ) const
        {
            if ( !m_good )
            {
                throw InvalidFrameFilename(
                    m_filename, m_spec, __FILE__, __LINE__ );
            }
            return m_d;
        }

        inline FrameFilename::gps_seconds_type
        FrameFilename::G( ) const
        {
            if ( !m_good )
            {
                throw InvalidFrameFilename(
                    m_filename, m_spec, __FILE__, __LINE__ );
            }
            return m_g;
        }

        inline const std::string&
        FrameFilename::S( ) const
        {
            if ( !m_good )
            {
                throw InvalidFrameFilename(
                    m_filename, m_spec, __FILE__, __LINE__ );
            }
            return m_s;
        }

        inline FrameFilename::total_time_interval_type
        FrameFilename::T( ) const
        {
            if ( !m_good )
            {
                throw InvalidFrameFilename(
                    m_filename, m_spec, __FILE__, __LINE__ );
            }
            return m_tt;
        }

        inline const std::string&
        FrameFilename::Ext( ) const
        {
            if ( !m_good )
            {
                throw InvalidFrameFilename(
                    m_filename, m_spec, __FILE__, __LINE__ );
            }
            return m_ext;
        }
    } // namespace Common
} // namespace FrameCPP

#endif /* FRAMECPP__FRAME_FILENAME_HH */
