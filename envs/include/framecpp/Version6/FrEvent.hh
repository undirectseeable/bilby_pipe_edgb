/*
 * LDASTools frameCPP - A library implementing the LIGO/Virgo frame
 * specification
 *
 * Copyright (C) 2018 California Institute of Technology
 *
 * LDASTools frameCPP is free software; you may redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 (GPLv2) of the
 * License or at your discretion, any later version.
 *
 * LDASTools frameCPP is distributed in the hope that it will be useful, but
 * without any warranty or even the implied warranty of merchantability
 * or fitness for a particular purpose. See the GNU General Public
 * License (GPLv2) for more details.
 *
 * Neither the names of the California Institute of Technology (Caltech),
 * The Massachusetts Institute of Technology (M.I.T), The Laser
 * Interferometer Gravitational-Wave Observatory (LIGO), nor the names
 * of its contributors may be used to endorse or promote products derived
 * from this software without specific prior written permission.
 *
 * You should have received a copy of the licensing terms for this
 * software included in the file LICENSE located in the top-level
 * directory of this package. If you did not, you can view a copy at
 * http://dcc.ligo.org/M1500244/LICENSE
 */

#ifndef FrameCPP_VERSION_6_FrEvent_HH
#define FrameCPP_VERSION_6_FrEvent_HH

#if defined( __cplusplus )
#if !defined( SWIGIMPORTED )
#include <string>
#include <vector>

#include "framecpp/Common/SearchContainer.hh"
#include "framecpp/Common/TOCInfo.hh"

#include "framecpp/Version4/FrTrigData.hh"

#include "framecpp/Version6/FrameSpec.hh"
#include "framecpp/Version6/GPSTime.hh"
#include "framecpp/Version6/FrVect.hh"
#include "framecpp/Version6/FrTable.hh"
#include "framecpp/Version6/STRING.hh"
#endif /* ! defined(SWIGIMPORTED) */
#endif /* defined(__cplusplus) */

#undef FR_EVENT_PARAM_NAMESPACE
#define FR_EVENT_PARAM_NAMESPACE Version_6

#undef FR_EVENT_NAME_TYPE
#if defined( __cplusplus )
#define FR_EVENT_NAME_TYPE STRING
#endif /* defined(__cplusplus) */

#undef FR_EVENT_COMMENT_TYPE
#if defined( __cplusplus )
#define FR_EVENT_COMMENT_TYPE STRING
#endif /* defined(__cplusplus) */

#undef FR_EVENT_INPUTS_TYPE
#if defined( __cplusplus )
#define FR_EVENT_INPUTS_TYPE STRING
#endif /* defined(__cplusplus) */

#undef FR_EVENT_TIME_TYPE
#define FR_EVENT_TIME_TYPE GPSTime

#undef FR_EVENT_TIME_BEFORE_TYPE
#define FR_EVENT_TIME_BEFORE_TYPE REAL_4

#undef FR_EVENT_TIME_AFTER_TYPE
#define FR_EVENT_TIME_AFTER_TYPE REAL_4

#undef FR_EVENT_EVENT_STATUS_TYPE
#define FR_EVENT_EVENT_STATUS_TYPE INT_4U

#undef FR_EVENT_AMPLITUDE_TYPE
#define FR_EVENT_AMPLITUDE_TYPE REAL_4

#undef FR_EVENT_PROBABILITY_TYPE
#define FR_EVENT_PROBABILITY_TYPE REAL_4

#undef FR_EVENT_STATISTICS_TYPE
#if defined( __cplusplus )
#define FR_EVENT_STATISTICS_TYPE STRING
#endif /* defined(__cplusplus) */

#undef FR_EVENT_PARAM_NAME_TYPE
#if defined( __cplusplus )
#if 0
#define FR_EVENT_PARAM_NAME_TYPE STRING
#else
#define FR_EVENT_PARAM_NAME_TYPE std::string
#endif
#endif /* defined(__cplusplus) */

#undef FR_EVENT_PARAM_VALUE_TYPE
#define FR_EVENT_PARAM_VALUE_TYPE REAL_4

#undef FR_EVENT_N_PARAM_TYPE
#define FR_EVENT_N_PARAM_TYPE INT_2U

#if !defined( SWIGIMPORTED )
#if defined( __cplusplus )
namespace FrameCPP
{
    namespace Version_6
    {
        /*===================================================================
           FrEventStorage
          ===================================================================*/
        class FrEventStorage
        {
        public:
            typedef FR_EVENT_NAME_TYPE         name_type;
            typedef FR_EVENT_COMMENT_TYPE      comment_type;
            typedef FR_EVENT_INPUTS_TYPE       inputs_type;
            typedef FR_EVENT_TIME_TYPE         time_type;
            typedef FR_EVENT_TIME_BEFORE_TYPE  timeBefore_type;
            typedef FR_EVENT_TIME_AFTER_TYPE   timeAfter_type;
            typedef FR_EVENT_EVENT_STATUS_TYPE eventStatus_type;
            typedef FR_EVENT_AMPLITUDE_TYPE    amplitude_type;
            typedef FR_EVENT_PROBABILITY_TYPE  probability_type;
            typedef FR_EVENT_STATISTICS_TYPE   statistics_type;
            typedef FR_EVENT_PARAM_NAME_TYPE   paramName_type;
            typedef FR_EVENT_PARAM_VALUE_TYPE  paramValue_type;

            typedef FR_EVENT_N_PARAM_TYPE                        nParam_type;
            typedef std::pair< paramName_type, paramValue_type > Param_type;
            typedef std::vector< Param_type >                    ParamList_type;

            FrEventStorage( );
            FrEventStorage( const FrEventStorage& Source );
            FrEventStorage( const Previous::FrTrigDataStorage& Source );

            const name_type&       GetName( ) const;
            const comment_type&    GetComment( ) const;
            const inputs_type&     GetInputs( ) const;
            const time_type&       GetGTime( ) const;
            timeBefore_type        GetTimeBefore( ) const;
            timeAfter_type         GetTimeAfter( ) const;
            eventStatus_type       GetEventStatus( ) const;
            amplitude_type         GetAmplitude( ) const;
            probability_type       GetProbability( ) const;
            const statistics_type& GetStatistics( ) const;
            const ParamList_type&  GetParam( ) const;
            ParamList_type&        GetParam( );

        protected:
            struct data_type
            {
                name_type        name;
                comment_type     comment;
                inputs_type      inputs;
                time_type        GTime;
                timeBefore_type  timeBefore;
                timeAfter_type   timeAfter;
                eventStatus_type eventStatus;
                amplitude_type   amplitude;
                probability_type probability;
                statistics_type  statistics;
                ParamList_type   Params;

                data_type( );
                data_type( const data_type& Source );

                cmn_streamsize_type Bytes( ) const;

                bool operator==( const data_type& RHS ) const;

                /**
                 * \brief Read data from stream
                 *
                 * \param[in,out] Stream
                 *     Stream from which the data is read.
                 */
                void operator( )( Common::IStream& Stream );

                /**
                 * \brief Write data to a stream
                 *
                 * \param[in,out] Stream
                 *     Stream to which the data is written.
                 */
                void operator( )( Common::OStream& Stream ) const;
            };

            data_type m_data;
        };

        inline FrEventStorage::data_type::data_type( )
        {
        }

        inline FrEventStorage::data_type::data_type( const data_type& Source )
            : name( Source.name ), comment( Source.comment ),
              inputs( Source.inputs ), GTime( Source.GTime ),
              timeBefore( Source.timeBefore ), timeAfter( Source.timeAfter ),
              eventStatus( Source.eventStatus ), amplitude( Source.amplitude ),
              probability( Source.probability ),
              statistics( Source.statistics ), Params( Source.Params )
        {
        }

        inline bool
        FrEventStorage::data_type::operator==( const data_type& RHS ) const
        {
            return ( ( &RHS == this ) ||
                     ( ( name == RHS.name ) && ( comment == RHS.comment ) &&
                       ( inputs == RHS.inputs ) && ( GTime == RHS.GTime ) &&
                       ( timeBefore == RHS.timeBefore ) &&
                       ( timeAfter == RHS.timeAfter ) &&
                       ( eventStatus == RHS.eventStatus ) &&
                       ( amplitude == RHS.amplitude ) &&
                       ( probability == RHS.probability ) &&
                       ( statistics == RHS.statistics ) &&
                       ( Params == RHS.Params ) ) );
        }

        inline FrEventStorage::FrEventStorage( )
        {
        }

        inline FrEventStorage::FrEventStorage( const FrEventStorage& Source )
            : m_data( Source.m_data )
        {
        }

        inline FrEventStorage::FrEventStorage(
            const Previous::FrTrigDataStorage& Source )
        {
            m_data.name = Source.GetName( );
            m_data.comment = Source.GetComment( );
            m_data.inputs = Source.GetInputs( );
            m_data.GTime = Source.GetGTime( );
            m_data.timeBefore = Source.GetTimeBefore( );
            m_data.timeAfter = Source.GetTimeAfter( );
            m_data.eventStatus = Source.GetTriggerStatus( );
            m_data.amplitude = Source.GetAmplitude( );
            m_data.probability = Source.GetProbability( );
            m_data.statistics = Source.GetStatistics( );
        }

        inline const FrEventStorage::name_type&
        FrEventStorage::GetName( ) const
        {
            return m_data.name;
        }

        inline const FrEventStorage::comment_type&
        FrEventStorage::GetComment( ) const
        {
            return m_data.comment;
        }

        inline const FrEventStorage::inputs_type&
        FrEventStorage::GetInputs( ) const
        {
            return m_data.inputs;
        }

        inline const FrEventStorage::time_type&
        FrEventStorage::GetGTime( ) const
        {
            return m_data.GTime;
        }

        inline FrEventStorage::timeBefore_type
        FrEventStorage::GetTimeBefore( ) const
        {
            return m_data.timeBefore;
        }

        inline FrEventStorage::timeAfter_type
        FrEventStorage::GetTimeAfter( ) const
        {
            return m_data.timeAfter;
        }

        inline FrEventStorage::eventStatus_type
        FrEventStorage::GetEventStatus( ) const
        {
            return m_data.eventStatus;
        }

        inline FrEventStorage::amplitude_type
        FrEventStorage::GetAmplitude( ) const
        {
            return m_data.amplitude;
        }

        inline FrEventStorage::probability_type
        FrEventStorage::GetProbability( ) const
        {
            return m_data.probability;
        }

        inline const FrEventStorage::statistics_type&
        FrEventStorage::GetStatistics( ) const
        {
            return m_data.statistics;
        }

        inline const FrEventStorage::ParamList_type&
        FrEventStorage::GetParam( ) const
        {
            return m_data.Params;
        }

        inline FrEventStorage::ParamList_type&
        FrEventStorage::GetParam( )
        {
            return m_data.Params;
        }

        /*===================================================================
         FrEventRefsT
          ===================================================================*/
        template < typename TVect, typename TTable >
        class FrEventRefsT
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

            FrEventRefsT( )
            {
            }

            FrEventRefsT( const FrEventRefsT& Source ) : m_refs( Source.m_refs )
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
                    return Stream.PtrStructBytes( ) /* data */
                        + Stream.PtrStructBytes( ) /* table */
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

        typedef FrEventRefsT< FrVect, FrTable > FrEventRefs;

        /*===================================================================
          FrEvent
          ===================================================================*/
        class FrEvent
#if !defined( SWIG )
            : public Common::FrameSpec::Object,
              public FrEventStorage,
              public FrEventRefs,
              public Common::TOCInfo
#endif /* ! defined(SWIG) */
        {
        public:
            /**
             * \brief Default constructor
             */
            FrEvent( );

            FrEvent( const FrEvent& Source );

            FrEvent( const name_type&       name,
                     const comment_type&    comment,
                     const inputs_type&     inputs,
                     const time_type&       time,
                     const timeBefore_type  timeBefore,
                     const timeAfter_type   timeAfter,
                     const eventStatus_type eventStatus,
                     const amplitude_type   amplitude,
                     const probability_type prob,
                     const statistics_type& statistics,
                     const ParamList_type&  parameters );
            FrEvent( const Previous::FrTrigData& Source, istream_type* Stream );

            const std::string& GetNameSlow( ) const;

            static promote_ret_type Promote( INT_2U           Source,
                                             promote_arg_type Obj,
                                             istream_type*    Stream );

            static const char* StructName( );

            static const Common::Description* StructDescription( );

            /* Number of bytes needed to write this structure */
            cmn_streamsize_type Bytes( const Common::StreamBase& Stream ) const;

            virtual FrEvent* Create( istream_type& Stream ) const;

            virtual const char* ObjectStructName( ) const;

            virtual void Write( ostream_type& Stream ) const;

#if WORKING_VIRTUAL_TOCQUERY
            virtual void TOCQuery( int InfoClass, ... ) const;
#endif /*  WORKING_VIRTUAL_TOCQUERY */

            /* Merge with another FrEvent */
            FrEvent& Merge( const FrEvent& RHS );

            /**
             * \brief comparison operator
             */
            bool operator==( const FrEvent& RHS ) const;

            /**
             * \brief comparison operator
             */
            virtual bool
            operator==( const Common::FrameSpec::Object& Obj ) const;

        protected:
            /**
             * \brief Down grade an object
             */
            virtual demote_ret_type demote( INT_2U          Target,
                                            demote_arg_type Obj,
                                            istream_type*   Stream ) const;

            /**
             * \brief Upgrade an object
             */
            virtual promote_ret_type promote( INT_2U           Target,
                                              promote_arg_type Obj,
                                              istream_type*    Stream ) const;

#if !WORKING_VIRTUAL_TOCQUERY
            virtual void vTOCQuery( int InfoClass, va_list vl ) const;
#endif /* ! WORKING_VIRTUAL_TOCQUERY */

        private:
            using Common::FrameSpec::Object::Create;

            FrEvent( istream_type& Stream );
        };

        inline FrameCPP::cmn_streamsize_type
        FrEvent::Bytes( const Common::StreamBase& Stream ) const
        {
            return m_data.Bytes( ) + m_refs.Bytes( Stream ) +
                Stream.PtrStructBytes( ) /* next */
                ;
        }

        inline FrEvent::promote_ret_type
        FrEvent::Promote( INT_2U           Source,
                          promote_arg_type Obj,
                          istream_type*    Stream )
        {
            return Object::PromoteObject< Previous::FrTrigData, FrEvent >(
                DATA_FORMAT_VERSION, Source, Obj, Stream );
        }

        inline const char*
        FrEvent::StructName( )
        {
            static const char* name = "FrEvent";
            return name;
        }

        inline bool
        FrEvent::operator==( const FrEvent& RHS ) const
        {
            return ( ( this == &RHS ) ||
                     ( ( m_data == RHS.m_data ) && ( m_refs == RHS.m_refs ) ) );
        }

        template < typename FrEventType, typename ShadowType >
        inline Common::OStream&
        FrEventParamWrite( Common::OStream&                            Stream,
                           const typename FrEventType::ParamList_type& Data )
        {
            typename FrEventType::nParam_type nParam = Data.size( );

            Stream << nParam;

            for ( typename FrEventType::nParam_type cur = 0; cur != nParam;
                  ++cur )
            {
                Stream << Data[ cur ].second;
            }
            for ( typename FrEventType::nParam_type cur = 0; cur != nParam;
                  ++cur )
            {
                ShadowType shadow( Data[ cur ].first );

                Stream << shadow;
            }
            return Stream;
        }

        template < typename FrEventType, typename ShadowType >
        inline Common::IStream&
        FrEventParamRead( Common::IStream&                      Stream,
                          typename FrEventType::ParamList_type& Data )
        {
            typename FrEventType::nParam_type nParam = Data.size( );

            Stream >> nParam;

            Data.resize( nParam );
            for ( typename FrEventType::nParam_type cur = 0; cur != nParam;
                  ++cur )
            {
                Stream >> Data[ cur ].second;
            }
            for ( typename FrEventType::nParam_type cur = 0; cur != nParam;
                  ++cur )
            {
                ShadowType shadow( Data[ cur ].first );

                Stream >> shadow;
            }
            return Stream;
        }

    } /* namespace Version_6 */

} /* namespace FrameCPP */

#endif /* defined(__cplusplus) */

#endif /* ! defined(SWIGIMPORTED) */

#endif /* FrameCPP_VERSION_6_FrEvent_HH */
