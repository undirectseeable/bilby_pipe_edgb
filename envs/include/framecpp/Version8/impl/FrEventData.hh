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

#ifndef FrameCPP_VERSION_8__IMPL__FrEventData_HH
#define FrameCPP_VERSION_8__IMPL__FrEventData_HH

#if defined( __cplusplus )
#if !defined( SWIG )
#include <string>

#include "ldastoolsal/types.hh"

#endif /* ! defined(SWIG) */
#endif /* defined(__cplusplus) */

#include "framecpp/Version7/FrEvent.hh"

#if defined( __cplusplus )
#if !defined( SWIG )
#include "framecpp/Version8/impl/FrObjectMetaData.hh"

#include "framecpp/Version8/STRING.hh"
#include "framecpp/Version8/GPSTime.hh"
#include "framecpp/Version8/FrTable.hh"
#include "framecpp/Version8/FrVect.hh"

#endif /* ! defined(SWIG) */
#endif /* defined(__cplusplus) */

#undef FR_EVENT_PARAM_NAME_TYPE
#define FR_EVENT_PARAM_NAME_TYPE std::string

#if defined( __cplusplus )

#if !defined( SWIGIMPORTED )

namespace FrameCPP
{
    namespace Version_8
    {
        namespace FrEventImpl
        {
            class Data : public Impl::FrObjectMetaData< Data >
            {
            public:
                typedef FR_EVENT_N_PARAM_TYPE     nParam_type;
                typedef FR_EVENT_PARAM_NAME_TYPE  paramName_type;
                typedef FR_EVENT_PARAM_VALUE_TYPE paramValue_type;
                typedef std::pair< paramName_type, paramValue_type > Param_type;
                typedef std::vector< Param_type > ParamList_type;

                typedef std::string                name_type;
                typedef std::string                comment_type;
                typedef std::string                inputs_type;
                typedef GPSTime                    GTime_type;
                typedef FR_EVENT_TIME_BEFORE_TYPE  timeBefore_type;
                typedef FR_EVENT_TIME_AFTER_TYPE   timeAfter_type;
                typedef FR_EVENT_EVENT_STATUS_TYPE eventStatus_type;
                typedef FR_EVENT_AMPLITUDE_TYPE    amplitude_type;
                typedef FR_EVENT_PROBABILITY_TYPE  probability_type;
                typedef std::string                statistics_type;
                //-------------------------------------------------------
                typedef Common::SearchContainer< FrVect, &FrVect::GetName >
                    data_type;
                typedef Common::SearchContainer< FrTable,
                                                 &FrTable::GetNameSlow >
                    table_type;

                inline name_type const&
                GetName( ) const
                {
                    return name;
                }

                inline comment_type const&
                GetComment( ) const
                {
                    return comment;
                }

                inline inputs_type const&
                GetInputs( ) const
                {
                    return inputs;
                }

                inline GTime_type const&
                GetGTime( ) const
                {
                    return GTime;
                }

                inline timeBefore_type
                GetTimeBefore( ) const
                {
                    return timeBefore;
                }

                inline timeAfter_type
                GetTimeAfter( ) const
                {
                    return timeAfter;
                }

                inline eventStatus_type
                GetEventStatus( ) const
                {
                    return eventStatus;
                }

                inline amplitude_type
                GetAmplitude( ) const
                {
                    return amplitude;
                }

                inline probability_type
                GetProbability( ) const
                {
                    return probability;
                }

                inline statistics_type const&
                GetStatistics( ) const
                {
                    return statistics;
                }

                inline ParamList_type const&
                GetParam( ) const
                {
                    return ( Params );
                }

                inline ParamList_type&
                GetParam( )
                {
                    return ( Params );
                }

                inline const data_type&
                RefData( ) const
                {
                    return ( data );
                }

                inline data_type&
                RefData( )
                {
                    return ( data );
                }

                inline const table_type&
                RefTable( ) const
                {
                    return ( table );
                }

                inline table_type&
                RefTable( )
                {
                    return ( table );
                }

                inline bool
                operator==( Data const& RHS ) const
                {
                    return ( ( this == &RHS ) ||
                             ( ( name.compare( RHS.name ) == 0 ) &&
                               ( comment.compare( RHS.comment ) == 0 ) &&
                               ( inputs.compare( RHS.inputs ) == 0 )
                               //
                               ) );
                }

            protected:
                //-------------------------------------------------------
                /// Name of event
                //-------------------------------------------------------
                name_type name;
                //-------------------------------------------------------
                /// Descriptor of event.
                //-------------------------------------------------------
                comment_type comment;
                //-------------------------------------------------------
                /// Input channels and filter parameters to event process.
                //-------------------------------------------------------
                inputs_type inputs;
                //-------------------------------------------------------
                /// GPS time corresponding to reference value of event,
                /// as defined by the search algorithm.
                //-------------------------------------------------------
                GTime_type GTime;
                //-------------------------------------------------------
                /// Signal duration before (GTimeS.GTimeN)(seconds)
                //-------------------------------------------------------
                timeBefore_type timeBefore;
                //-------------------------------------------------------
                /// Signal duration after (GTimeS.GTimeN)(seconds)
                //-------------------------------------------------------
                timeAfter_type timeAfter;
                //-------------------------------------------------------
                /// Defined by event search algorithm
                //-------------------------------------------------------
                eventStatus_type eventStatus;
                //-------------------------------------------------------
                /// Continuous output amplitude returned by event
                //-------------------------------------------------------
                amplitude_type amplitude;
                //-------------------------------------------------------
                /// Likelihood estimate of event, if available
                /// (probability = -1 if cannot be estimated)
                //-------------------------------------------------------
                probability_type probability;
                //-------------------------------------------------------
                /// Statistical description of event, if relevant
                /// or available.
                //-------------------------------------------------------
                statistics_type statistics;
                //-------------------------------------------------------
                /// Array of parameters
                //-------------------------------------------------------
                ParamList_type Params;
                //=======================================================
                //-------------------------------------------------------
                static constexpr unsigned int MAX_REF{ 2 };
                //-------------------------------------------------------
                /// Container of additional event results.
                //-------------------------------------------------------
                data_type data;
                //-------------------------------------------------------
                /// Table containing additional event information
                //-------------------------------------------------------
                table_type table;
            };

        } // namespace FrEventImpl
    } // namespace Version_8
} // namespace FrameCPP

#endif /* !defined( SWIGIMPORTED ) */

#if !defined( SWIG )
FR_OBJECT_META_DATA_DECLARE( FrEventImpl )
#endif /* !defined( SWIG ) */

#endif /* defined( __cplusplus ) */

#endif /* FrameCPP_VERSION_8__IMPL__FrEventData_HH */
