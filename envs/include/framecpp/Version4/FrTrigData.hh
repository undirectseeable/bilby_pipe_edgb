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

#ifndef FrameCPP_VERSION_4_FrTrigData_HH
#define FrameCPP_VERSION_4_FrTrigData_HH

#if !defined( SWIGIMPORTED )
#include <string>
#include <vector>

#include "framecpp/Common/SearchContainer.hh"
#include "framecpp/Common/TOCInfo.hh"
#endif /* ! defined(SWIGIMPORTED) */

#include "framecpp/Version3/FrTrigData.hh"

#if !defined( SWIGIMPORTED )

#include "framecpp/Version4/FrameSpec.hh"
#include "framecpp/Version4/GPSTime.hh"
#include "framecpp/Version4/FrVect.hh"
#include "framecpp/Version4/FrTable.hh"
#include "framecpp/Version4/STRING.hh"

namespace FrameCPP
{
    namespace Version_4
    {
        //===================================================================
        // FrTrigDataStorage
        //===================================================================
        class FrTrigDataStorage
        {
        public:
            FrTrigDataStorage( );
            FrTrigDataStorage( const FrTrigDataStorage& Source );
            FrTrigDataStorage( const Previous::FrTrigDataStorage& Source );

            const std::string&
            GetName( ) const
            {
                return m_data.name;
            }
            const std::string&
            GetComment( ) const
            {
                return m_data.comment;
            }
            const std::string&
            GetInputs( ) const
            {
                return m_data.inputs;
            }
            const GPSTime&
            GetGTime( ) const
            {
                return m_data.GTime;
            }
            REAL_4
            GetTimeBefore( ) const
            {
                return m_data.timeBefore;
            }
            REAL_4
            GetTimeAfter( ) const
            {
                return m_data.timeAfter;
            }
            INT_4U
            GetTriggerStatus( ) const
            {
                return m_data.triggerStatus;
            }
            REAL_4
            GetAmplitude( ) const
            {
                return m_data.amplitude;
            }
            REAL_4
            GetProbability( ) const
            {
                return m_data.probability;
            }
            const std::string&
            GetStatistics( ) const
            {
                return m_data.statistics;
            }

        protected:
            struct data_type
            {
                STRING  name;
                STRING  comment;
                STRING  inputs;
                GPSTime GTime;
                REAL_4  timeBefore;
                REAL_4  timeAfter;
                INT_4U  triggerStatus;
                REAL_4  amplitude;
                REAL_4  probability;
                STRING  statistics;

                data_type( );
                data_type( const data_type& Source );

                cmn_streamsize_type Bytes( ) const;

                bool operator==( const data_type& RHS ) const;

                void operator( )( Common::IStream& Stream );
                void operator( )( Common::OStream& Stream ) const;
            };

            data_type m_data;
        };

        inline FrTrigDataStorage::data_type::data_type( )
        {
        }

        inline FrTrigDataStorage::data_type::data_type(
            const data_type& Source )
            : name( Source.name ), comment( Source.comment ),
              inputs( Source.inputs ), GTime( Source.GTime ),
              timeBefore( Source.timeBefore ), timeAfter( Source.timeAfter ),
              triggerStatus( Source.triggerStatus ),
              amplitude( Source.amplitude ), probability( Source.probability ),
              statistics( Source.statistics )
        {
        }

        inline bool
        FrTrigDataStorage::data_type::operator==( const data_type& RHS ) const
        {
            return ( ( &RHS == this ) ||
                     ( ( name == RHS.name ) && ( comment == RHS.comment ) &&
                       ( inputs == RHS.inputs ) && ( GTime == RHS.GTime ) &&
                       ( timeBefore == RHS.timeBefore ) &&
                       ( timeAfter == RHS.timeAfter ) &&
                       ( triggerStatus == RHS.triggerStatus ) &&
                       ( amplitude == RHS.amplitude ) &&
                       ( probability == RHS.probability ) &&
                       ( statistics == RHS.statistics ) ) );
        }

        inline FrTrigDataStorage::FrTrigDataStorage( )
        {
        }

        inline FrTrigDataStorage::FrTrigDataStorage(
            const FrTrigDataStorage& Source )
            : m_data( Source.m_data )
        {
        }

        inline FrTrigDataStorage::FrTrigDataStorage(
            const Previous::FrTrigDataStorage& Source )
        {
            m_data.name = Source.GetName( );
            m_data.comment = Source.GetComment( );
            m_data.inputs = Source.GetInputs( );
            m_data.GTime = Source.GetGTime( );
            m_data.triggerStatus = Source.GetBvalue( );
            m_data.amplitude = Source.GetRvalue( );
            m_data.probability = Source.GetProbability( );
            m_data.statistics = Source.GetStatistics( );
            //-----------------------------------------------------------------
            // Initialize fields new to this version
            //-----------------------------------------------------------------
            m_data.timeBefore = REAL_4( 0.0 );
            m_data.timeAfter = REAL_4( 0.0 );
        }

        //===================================================================
        // FrTrigDataRefsT
        //===================================================================
        template < typename TVect, typename TTable >
        class FrTrigDataRefsT
        {
        public:
            typedef typename Common::SearchContainer< TVect, &TVect::GetName >
                                                       data_type;
            typedef typename data_type::iterator       iterator;
            typedef typename data_type::const_iterator const_iterator;

            typedef
                typename Common::SearchContainer< TTable, &TTable::GetNameSlow >
                                                        table_type;
            typedef typename table_type::iterator       table_iterator;
            typedef typename table_type::const_iterator const_table_iterator;

            static const INT_2U MAX_REF = 2;

            FrTrigDataRefsT( )
            {
            }

            FrTrigDataRefsT( const FrTrigDataRefsT& Source )
                : m_refs( Source.m_refs )
            {
            }

            inline const data_type&
            RefData( ) const
            {
                return m_refs.data;
            }

            inline data_type&
            RefData( )
            {
                return m_refs.data;
            }

            inline const table_type&
            RefTable( ) const
            {
                return m_refs.table;
            }

            inline table_type&
            RefTable( )
            {
                return m_refs.table;
            }

        protected:
            struct ref_type
            {
                data_type  data;
                table_type table;

                ref_type( )
                {
                }

                ref_type( const ref_type& Source )
                    : data( Source.data ), table( Source.table )
                {
                }

                inline FrameCPP::cmn_streamsize_type
                Bytes( const Common::StreamBase& Stream ) const
                {
                    return Stream.PtrStructBytes( ) // data
                        + Stream.PtrStructBytes( ) // table
                        ;
                }

                bool
                operator==( const ref_type& RHS ) const
                {
                    return (
                        ( this == &RHS ) ||
                        ( ( data == RHS.data ) && ( table == RHS.table ) ) );
                }

                void
                operator( )( Common::IStream& Stream )
                {
                    Stream >> data >> table;
                }

                void
                operator( )( Common::OStream& Stream ) const
                {
                    Stream << data << table;
                }
            };

            ref_type m_refs;
        };

        typedef FrTrigDataRefsT< FrVect, FrTable > FrTrigDataRefs;

        //===================================================================
        // FrTrigData
        //===================================================================
        class FrTrigData : public Common::FrameSpec::Object,
                           public FrTrigDataStorage,
                           public FrTrigDataRefs,
                           public Common::TOCInfo
        {
        public:
            /// \brief Default constructor
            FrTrigData( );
            FrTrigData( const FrTrigData& Source );
            FrTrigData( const std::string& Name,
                        const std::string& Comment,
                        const std::string& Inputs,
                        const GPSTime&     GTime,
                        const REAL_4       TimeBefore,
                        const REAL_4       TimeAfter,
                        const INT_4U       TriggerStatus,
                        const REAL_4       Amplitude,
                        const REAL_4       Probability,
                        const std::string& Statistics );
            FrTrigData( const Previous::FrTrigData& Source,
                        istream_type*               Stream );

            const std::string& GetNameSlow( ) const;

            static promote_ret_type Promote( INT_2U           Source,
                                             promote_arg_type Obj,
                                             istream_type*    Stream );

            static const char* StructName( );

            static const Common::Description* StructDescription( );

            /// \brief Number of bytes needed to write this structure
            cmn_streamsize_type Bytes( const Common::StreamBase& Stream ) const;

            virtual FrTrigData* Create( istream_type& Stream ) const;

            virtual const char* ObjectStructName( ) const;

#if WORKING_VIRTUAL_TOCQUERY
            virtual void TOCQuery( int InfoClass, ... ) const;
#endif /*  WORKING_VIRTUAL_TOCQUERY */

            virtual void Write( ostream_type& Stream ) const;

            /// \brief Merge with another FrTrigData
            FrTrigData& Merge( const FrTrigData& RHS );

            /// \brief comparison operator
            bool operator==( const FrTrigData& RHS ) const;

            /// \brief comparison operator
            virtual bool
            operator==( const Common::FrameSpec::Object& Obj ) const;

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

            FrTrigData( istream_type& Stream );
        };

        inline FrameCPP::cmn_streamsize_type
        FrTrigData::Bytes( const Common::StreamBase& Stream ) const
        {
            return m_data.Bytes( ) + m_refs.Bytes( Stream ) +
                Stream.PtrStructBytes( ) // next
                ;
        }

        inline FrTrigData::promote_ret_type
        FrTrigData::Promote( INT_2U           Source,
                             promote_arg_type Obj,
                             istream_type*    Stream )
        {
            return Object::PromoteObject< Previous::FrTrigData, FrTrigData >(
                DATA_FORMAT_VERSION, Source, Obj, Stream );
        }

        inline const char*
        FrTrigData::StructName( )
        {
            static const char* name = "FrTrigData";
            return name;
        }

        inline bool
        FrTrigData::operator==( const FrTrigData& RHS ) const
        {
            return ( ( this == &RHS ) ||
                     ( ( m_data == RHS.m_data ) && ( m_refs == RHS.m_refs ) ) );
        }
    } // namespace Version_4
} // namespace FrameCPP

#endif /* ! defined(SWIGIMPORTED) */

#endif /* FrameCPP_VERSION_4_FrTrigData_HH */
