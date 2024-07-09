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

#ifndef FrameCPP_VERSION_7_FrEvent_HH
#define FrameCPP_VERSION_7_FrEvent_HH

#if defined( __cplusplus )
#if !defined( SWIG )
#include <string>
#include <vector>

#include "framecpp/Common/SearchContainer.hh"
#include "framecpp/Common/TOCInfo.hh"
#endif /* ! defined(SWIG) */
#endif /* defined(__cplusplus) */

#include "framecpp/Version6/FrEvent.hh"

#if defined( __cplusplus )
#if !defined( SWIG )
#include "framecpp/Version7/FrameSpec.hh"
#include "framecpp/Version7/GPSTime.hh"
#include "framecpp/Version7/FrVect.hh"
#include "framecpp/Version7/FrTable.hh"
#include "framecpp/Version7/STRING.hh"
#endif /* ! defined(SWIG) */
#endif /* defined(__cplusplus) */

#undef FR_EVENT_PARAM_VALUE_TYPE
#define FR_EVENT_PARAM_VALUE_TYPE REAL_8

#if !defined( SWIGIMPORTED )

#if defined( __cplusplus )

namespace FrameCPP
{
    namespace Version_7
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
            FrEventStorage( const Previous::FrEventStorage& Source );

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
                /**
                 * Name of event
                 */
                STRING name;
                /**
                 * Descriptor of event.
                 */
                STRING comment;
                /**
                 * Input channels and filter parameters to event process.
                 */
                STRING inputs;
                /**
                 * GPS time corresponding to reference value of evet,
                 * as defined by the search algorithm.
                 */
                time_type GTime;
                /**
                 * Signal duration before
                 */
                timeBefore_type timeBefore;
                /**
                 * Signal duration after
                 */
                timeAfter_type timeAfter;
                /**
                 * Defined by event search algorithm.
                 */
                eventStatus_type eventStatus;
                /**
                 * Continuouis output amplitude returned by event.
                 */
                amplitude_type amplitude;
                /**
                 * Likelihood estimate of event, if available.
                 * (probability  = -1 if cannot be estimated)
                 */
                probability_type probability;
                /**
                 * Statistical description of event, if rlevant or available.
                 */
                STRING statistics;
                /**
                 * Array of additional event parameters.
                 */
                ParamList_type Params;

                data_type( );
                data_type( const data_type& Source );

                cmn_streamsize_type Bytes( ) const;

                bool operator==( const data_type& RHS ) const;

                void operator( )( Common::IStream& Stream );
                void operator( )( Common::OStream& Stream ) const;
            };

            data_type m_data;
        };

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
            const Previous::FrEventStorage& Source )
        {
            m_data.name = Source.GetName( );
            m_data.comment = Source.GetComment( );
            m_data.inputs = Source.GetInputs( );
            m_data.GTime = Source.GetGTime( );
            m_data.timeBefore = Source.GetTimeBefore( );
            m_data.timeAfter = Source.GetTimeAfter( );
            m_data.eventStatus = Source.GetEventStatus( );
            m_data.amplitude = Source.GetAmplitude( );
            m_data.probability = Source.GetProbability( );
            m_data.statistics = Source.GetStatistics( );

            const Previous::FrEventStorage::ParamList_type pl =
                Source.GetParam( );

            for ( Previous::FrEventStorage::ParamList_type::const_iterator
                      cur = pl.begin( ),
                      last = pl.end( );
                  cur != last;
                  ++cur )
            {
                m_data.Params.push_back(
                    Param_type( cur->first, cur->second ) );
            }
        }

        /*===================================================================
           FrEventRefsT
          ===================================================================*/

#if !defined( SWIG )
        using Previous::FrEventRefsT;
        typedef Previous::FrEventRefs FrEventRefs;
#endif /* ! defined(SWIG) */

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
            /* Default constructor */
            FrEvent( );
            FrEvent( const FrEvent& eventData );
            FrEvent( const std::string&     name,
                     const std::string&     comment,
                     const std::string&     inputs,
                     const GPSTime&         time,
                     const timeBefore_type  timeBefore,
                     const timeAfter_type   timeAfter,
                     const eventStatus_type eventStatus,
                     const amplitude_type   amplitude,
                     const probability_type prob,
                     const std::string&     statistics,
                     const ParamList_type&  parameters );
            FrEvent( const Previous::FrEvent& Source, istream_type* Stream );

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

            /* Merge with another FrEvent */
            FrEvent& Merge( const FrEvent& RHS );

#if WORKING_VIRTUAL_TOCQUERY
            virtual void TOCQuery( int InfoClass, ... ) const;
#endif /*  WORKING_VIRTUAL_TOCQUERY */

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
            return Object::PromoteObject< Previous::FrEvent, FrEvent >(
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
    } /* namespace Version_7 */
} /* namespace FrameCPP */

#endif /* defined(__cplusplus) */

#endif /* ! defined(SWIGIMPORTED) */

#endif /* FrameCPP_VERSION_7_FrEvent_HH */
