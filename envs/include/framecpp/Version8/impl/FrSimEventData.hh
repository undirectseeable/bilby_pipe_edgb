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

#ifndef FrameCPP_VERSION_8__IMPL__FrSimEventData_HH
#define FrameCPP_VERSION_8__IMPL__FrSimEventData_HH

#if defined( __cplusplus )
#if !defined( SWIG )
#include <string>

#include "ldastoolsal/types.hh"

#endif /* ! defined(SWIG) */
#endif /* defined(__cplusplus) */

#include "framecpp/Version7/FrSimEvent.hh"

#if defined( __cplusplus )
#if !defined( SWIG )
#include "framecpp/Version8/impl/FrObjectMetaData.hh"

#include "framecpp/Version8/STRING.hh"
#include "framecpp/Version8/GPSTime.hh"
#include "framecpp/Version8/FrTable.hh"
#include "framecpp/Version8/FrVect.hh"

#endif /* ! defined(SWIG) */
#endif /* defined(__cplusplus) */

#undef FR_SIM_EVENT_NAME_TYPE
#define FR_SIM_EVENT_NAME_TYPE std::string

#undef FR_SIM_EVENT_COMMENT_TYPE
#define FR_SIM_EVENT_COMMENT_TYPE std::string

#undef FR_SIM_EVENT_INPUTS_TYPE
#define FR_SIM_EVENT_INPUTS_TYPE std::string

#undef FR_SIM_EVENT_TIME_TYPE
#define FR_SIM_EVENT_TIME_TYPE GPSTime

#undef FR_SIM_EVENT_AMPLITUDE_TYPE
#define FR_SIM_EVENT_AMPLITUDE_TYPE REAL_4

#undef FR_SIM_EVENT_PARAM_VALUE_TYPE
#define FR_SIM_EVENT_PARAM_VALUE_TYPE REAL_8

#undef FR_SIM_EVENT_N_PARAM_TYPE
#define FR_SIM_EVENT_N_PARAM_TYPE INT_2U

#undef FR_SIM_EVENT_PARAM_NAME_TYPE
#define FR_SIM_EVENT_PARAM_NAME_TYPE std::string

#undef FR_SIM_EVENT_TIME_BEFORE_TYPE
#define FR_SIM_EVENT_TIME_BEFORE_TYPE REAL_4

#undef FR_SIM_EVENT_TIME_AFTER_TYPE
#define FR_SIM_EVENT_TIME_AFTER_TYPE REAL_4

#if defined( __cplusplus )

#if !defined( SWIGIMPORTED )
namespace FrameCPP
{
    namespace Version_8
    {
        namespace FrSimEventImpl
        {
            class Data : public Impl::FrObjectMetaData< Data >
            {
            public:
                typedef FR_SIM_EVENT_N_PARAM_TYPE     nParam_type;
                typedef FR_SIM_EVENT_PARAM_NAME_TYPE  paramName_type;
                typedef FR_SIM_EVENT_PARAM_VALUE_TYPE paramValue_type;
                typedef std::pair< paramName_type, paramValue_type > Param_type;
                typedef std::vector< Param_type > ParamList_type;

                typedef FR_SIM_EVENT_NAME_TYPE        name_type;
                typedef FR_SIM_EVENT_COMMENT_TYPE     comment_type;
                typedef FR_SIM_EVENT_INPUTS_TYPE      inputs_type;
                typedef FR_SIM_EVENT_TIME_TYPE        GTime_type;
                typedef FR_SIM_EVENT_TIME_BEFORE_TYPE timeBefore_type;
                typedef FR_SIM_EVENT_TIME_AFTER_TYPE  timeAfter_type;
                typedef FR_SIM_EVENT_AMPLITUDE_TYPE   amplitude_type;
                //-------------------------------------------------------
                typedef Common::SearchContainer< FrVect, &FrVect::GetName >
                    data_type;
                typedef Common::SearchContainer< FrTable,
                                                 &FrTable::GetNameSlow >
                    table_type;

                inline void
                AppendComment( const comment_type& Comment )
                {
                    FrameCPP::Common::AppendComment( comment, Comment );
                }

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

                inline amplitude_type
                GetAmplitude( ) const
                {
                    return amplitude;
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
                /// Continuous output amplitude returned by event
                //-------------------------------------------------------
                amplitude_type amplitude;
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

        } // namespace FrSimEventImpl
    } // namespace Version_8
} // namespace FrameCPP
#endif /* !defined( SWIGIMPORTED ) */

#if !defined( SWIG )
FR_OBJECT_META_DATA_DECLARE( FrSimEventImpl )
#endif /* !defined( SWIG ) */

#endif /* defined( __cplusplus ) */

#endif /* FrameCPP_VERSION_8__IMPL__FrSimEventData_HH */
