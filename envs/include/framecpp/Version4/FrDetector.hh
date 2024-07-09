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

#ifndef FrameCPP_VERSION_4_FrDetector_HH
#define FrameCPP_VERSION_4_FrDetector_HH

#if !defined( SWIGIMPORTED )
#include <string>
#include <vector>
#endif /* ! defined(SWIGIMPORTED) */

#include "ldastoolsal/types.hh"

#include "framecpp/Common/SearchContainer.hh"
#include "framecpp/Common/TOCInfo.hh"
#include "framecpp/Common/FrDetector.hh"

#include "framecpp/Version4/GPSTime.hh"
#include "framecpp/Version4/STRING.hh"

#include "framecpp/Version4/FrTable.hh"
#include "framecpp/Version4/FrVect.hh"

#include "framecpp/Version3/FrDetector.hh"

namespace FrameCPP
{
    namespace Version_4
    {
        class FrDetector : public Common::FrDetector, public Common::TOCInfo
        {
        public:
            typedef Common::SearchContainer< FrVect, &FrVect::GetName >
                                              more_type;
            typedef more_type::iterator       aux_iterator;
            typedef more_type::const_iterator const_aux_iterator;

            typedef Common::SearchContainer< FrTable, &FrTable::GetNameSlow >
                                                    more_table_type;
            typedef more_table_type::iterator       table_iterator;
            typedef more_table_type::const_iterator const_table_iterator;

            /// \brief Default constructor
            FrDetector( );

            FrDetector( const std::string& Name,
                        const INT_2S       LongitudeD,
                        const INT_2S       LongitudeM,
                        const REAL_4       LongitudeS,
                        const INT_2S       LatitudeD,
                        const INT_2S       LatitudeM,
                        const REAL_4       LatitudeS,
                        const REAL_4       Elevation,
                        const REAL_4       ArmXazimuth,
                        const REAL_4       ArmYazimuth );

            FrDetector( const FrDetector& detector );

            FrDetector( Previous::FrDetector& Source, istream_type* Stream );

            static const char* StructName( );

            static const Common::Description* StructDescription( );

            /// \brief Number of bytes needed to write this structure
            cmn_streamsize_type Bytes( const Common::StreamBase& Stream ) const;

            virtual FrDetector* Create( istream_type& Stream ) const;

            virtual const char* ObjectStructName( ) const;

            virtual void Write( ostream_type& Stream ) const;

            const std::string& GetName( ) const;
            INT_2S             GetLongitudeD( ) const;
            INT_2S             GetLongitudeM( ) const;
            REAL_4             GetLongitudeS( ) const;
            INT_2S             GetLatitudeD( ) const;
            INT_2S             GetLatitudeM( ) const;
            REAL_4             GetLatitudeS( ) const;
            REAL_4             GetElevation( ) const;
            REAL_4             GetArmXazimuth( ) const;
            REAL_4             GetArmYazimuth( ) const;

            const more_type&       RefMore( ) const;
            more_type&             RefMore( );
            const more_table_type& RefMoreTable( ) const;
            more_table_type&       RefMoreTable( );

            /// \brief Merge with another FrDetector
            FrDetector& Merge( const FrDetector& RHS );

            static promote_ret_type Promote( INT_2U           Source,
                                             promote_arg_type Obj,
                                             istream_type*    Stream );

            /// \brief comparison operator
            bool operator==( const FrDetector& RHS ) const;

            /// \brief comparison operator
            virtual bool
            operator==( const Common::FrameSpec::Object& Obj ) const;

#if WORKING_VIRTUAL_TOCQUERY
            virtual void TOCQuery( int InfoClass, ... ) const;
#endif /* WORKING_VIRTUAL_TOCQUERY */

        protected:
            /// \brief Down grade an object
            virtual demote_ret_type demote( INT_2U          Target,
                                            demote_arg_type Obj,
                                            istream_type*   Stream ) const;

            /// \brief Upgrade an object
            virtual promote_ret_type promote( INT_2U           Target,
                                              promote_arg_type Obj,
                                              istream_type*    Stream ) const;

#if !WORKING_VIRTUAL_TOCQUERY
            virtual void vTOCQuery( int InfoClass, va_list vl ) const;
#endif /* ! WORKING_VIRTUAL_TOCQUERY */

        private:
            using Common::FrameSpec::Object::Create;

            struct fr_detector_data_type
            {
                bool      operator==( const fr_detector_data_type& RHS ) const;
                STRING    name;
                INT_2S    longitudeD;
                INT_2S    longitudeM;
                REAL_4    longitudeS;
                INT_2S    latitudeD;
                INT_2S    latitudeM;
                REAL_4    latitudeS;
                REAL_4    elevation;
                REAL_4    armXazimuth;
                REAL_4    armYazimuth;
                more_type more;
                more_table_type moreTable;
            };

            fr_detector_data_type m_data;

            FrDetector( istream_type& Stream );
        };

        inline const char*
        FrDetector::StructName( )
        {
            static const char* name = "FrDetector";
            return name;
        }

        inline INT_2S
        FrDetector::GetLongitudeD( ) const
        {
            return m_data.longitudeD;
        }

        inline INT_2S
        FrDetector::GetLongitudeM( ) const
        {
            return m_data.longitudeM;
        }

        inline REAL_4
        FrDetector::GetLongitudeS( ) const
        {
            return m_data.longitudeS;
        }

        inline INT_2S
        FrDetector::GetLatitudeD( ) const
        {
            return m_data.latitudeD;
        }

        inline INT_2S
        FrDetector::GetLatitudeM( ) const
        {
            return m_data.latitudeM;
        }

        inline REAL_4
        FrDetector::GetLatitudeS( ) const
        {
            return m_data.latitudeS;
        }

        inline REAL_4
        FrDetector::GetElevation( ) const
        {
            return m_data.elevation;
        }

        inline REAL_4
        FrDetector::GetArmXazimuth( ) const
        {
            return m_data.armXazimuth;
        }

        inline REAL_4
        FrDetector::GetArmYazimuth( ) const
        {
            return m_data.armYazimuth;
        }

        inline const FrDetector::more_type&
        FrDetector::RefMore( ) const
        {
            return m_data.more;
        }

        inline FrDetector::more_type&
        FrDetector::RefMore( )
        {
            return m_data.more;
        }

        inline const FrDetector::more_table_type&
        FrDetector::RefMoreTable( ) const
        {
            return m_data.moreTable;
        }

        inline FrDetector::more_table_type&
        FrDetector::RefMoreTable( )
        {
            return m_data.moreTable;
        }

        inline FrDetector::promote_ret_type
        FrDetector::Promote( INT_2U           Source,
                             promote_arg_type Obj,
                             istream_type*    Stream )
        {
            return Object::PromoteObject< Previous::FrDetector, FrDetector >(
                DATA_FORMAT_VERSION, Source, Obj, Stream );
        }

        inline bool
        FrDetector::operator==( const FrDetector& RHS ) const
        {
            return ( m_data == RHS.m_data );
        }
    } // namespace Version_4
} // namespace FrameCPP
#endif /* FrameCPP_VERSION_4_FrDetector_HH */
