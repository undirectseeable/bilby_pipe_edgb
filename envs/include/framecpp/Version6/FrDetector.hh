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

#ifndef FrameCPP_VERSION_6_FrDetector_HH
#define FrameCPP_VERSION_6_FrDetector_HH

#if !defined( SWIGIMPORTED )
#include <string>
#include <vector>
#endif /* ! defined(SWIGIMPORTED) */

#include "ldastoolsal/types.hh"

#include "framecpp/Common/SearchContainer.hh"
#include "framecpp/Common/TOCInfo.hh"
#include "framecpp/Common/FrDetector.hh"

#include "framecpp/Version6/GPSTime.hh"
#include "framecpp/Version6/STRING.hh"

#include "framecpp/Version6/FrTable.hh"
#include "framecpp/Version6/FrVect.hh"

#include "framecpp/Version4/FrDetector.hh"

namespace FrameCPP
{
    namespace Version_6
    {
        class FrDetector : public Common::FrDetector, public Common::TOCInfo
        {
        public:
            typedef Common::SearchContainer< FrVect, &FrVect::GetName >
                                             aux_type;
            typedef aux_type::iterator       aux_iterator;
            typedef aux_type::const_iterator const_aux_iterator;

            typedef Common::SearchContainer< FrTable, &FrTable::GetNameSlow >
                                               table_type;
            typedef table_type::iterator       table_iterator;
            typedef table_type::const_iterator const_table_iterator;

            //: Default constructor
            FrDetector( );

            FrDetector( const std::string& Name,
                        const char*        Prefix,
                        const REAL_8       Longitude,
                        const REAL_8       Latitude,
                        const REAL_4       Elevation,
                        const REAL_4       ArmXazimuth,
                        const REAL_4       ArmYazimuth,
                        const REAL_4       ArmXaltitude,
                        const REAL_4       ArmYaltitude,
                        const REAL_4       ArmXmidpoint,
                        const REAL_4       ArmYmidpoint,
                        const INT_4S       LocalTime );

            FrDetector( const FrDetector& detector );

            FrDetector( Previous::FrDetector& Source, istream_type* Stream );

            static const char* StructName( );

            static const Common::Description* StructDescription( );

            //: Number of bytes needed to write this structure
            cmn_streamsize_type Bytes( const Common::StreamBase& Stream ) const;

            virtual FrDetector* Create( istream_type& Stream ) const;

            virtual const char* ObjectStructName( ) const;

            virtual void Write( ostream_type& Stream ) const;

            const std::string& GetName( ) const;
            const CHAR*
            GetPrefix( ) const
            {
                return m_data.prefix;
            }
            REAL_8
            GetLongitude( ) const
            {
                return m_data.longitude;
            }
            REAL_8
            GetLatitude( ) const
            {
                return m_data.latitude;
            }
            REAL_4
            GetElevation( ) const
            {
                return m_data.elevation;
            }
            REAL_4
            GetArmXazimuth( ) const
            {
                return m_data.armXazimuth;
            }
            REAL_4
            GetArmYazimuth( ) const
            {
                return m_data.armYazimuth;
            }
            REAL_4
            GetArmXaltitude( ) const
            {
                return m_data.armXaltitude;
            }
            REAL_4
            GetArmYaltitude( ) const
            {
                return m_data.armYaltitude;
            }
            REAL_4
            GetArmXmidpoint( ) const
            {
                return m_data.armXmidpoint;
            }
            REAL_4
            GetArmYmidpoint( ) const
            {
                return m_data.armYmidpoint;
            }
            INT_4S
            GetLocalTime( ) const
            {
                return m_data.localTime;
            }
            const aux_type&
            RefAux( ) const
            {
                return m_data.aux;
            }
            aux_type&
            RefAux( )
            {
                return m_data.aux;
            }
            const table_type&
            RefTable( ) const
            {
                return m_data.table;
            }
            table_type&
            RefTable( )
            {
                return m_data.table;
            }

            //: Merge with another FrDetector
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
#endif /*  WORKING_VIRTUAL_TOCQUERY */

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
                bool       operator==( const fr_detector_data_type& RHS ) const;
                STRING     name;
                CHAR       prefix[ 2 ];
                REAL_8     longitude;
                REAL_8     latitude;
                REAL_4     elevation;
                REAL_4     armXazimuth;
                REAL_4     armYazimuth;
                REAL_4     armXaltitude;
                REAL_4     armYaltitude;
                REAL_4     armXmidpoint;
                REAL_4     armYmidpoint;
                INT_4S     localTime;
                aux_type   aux;
                table_type table;
            };

            fr_detector_data_type m_data;

            FrDetector( istream_type& Stream );
        };

        inline FrDetector::promote_ret_type
        FrDetector::Promote( INT_2U           Source,
                             promote_arg_type Obj,
                             istream_type*    Stream )
        {
            return Object::PromoteObject< Previous::FrDetector, FrDetector >(
                DATA_FORMAT_VERSION, Source, Obj, Stream );
        }

        inline const char*
        FrDetector::StructName( )
        {
            static const char* name = "FrDetector";
            return name;
        }

        inline bool
        FrDetector::operator==( const FrDetector& RHS ) const
        {
            return ( m_data == RHS.m_data );
        }
    } // namespace Version_6
} // namespace FrameCPP
#endif /* FrameCPP_VERSION_6_FrDetector_HH */
