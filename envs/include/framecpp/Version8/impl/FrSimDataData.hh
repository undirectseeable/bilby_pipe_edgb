//
// LDASTools frameCPP - A library implementing the LIGO/Virgo frame
// specification
//
// Copyright (C) 2018-2020 California Institute of Technology
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

#ifndef FrameCPP_VERSION_8__IMPL__FrSimDataData_HH
#define FrameCPP_VERSION_8__IMPL__FrSimDataData_HH

#if defined( __cplusplus ) && !defined( SWIG )

#endif /* defined( __cplusplus ) && !defined( SWIG ) */

#undef FR_SIM_DATA_NAME_TYPE
#if defined( __cplusplus )
#define FR_SIM_DATA_NAME_TYPE std::string
#endif /* defined(__cplusplus) */

#undef FR_SIM_DATA_COMMENT_TYPE
#if defined( __cplusplus )
#define FR_SIM_DATA_COMMENT_TYPE std::string
#endif /* defined(__cplusplus) */

#undef FR_SIM_DATA_SAMPLERATE_TYPE
#define FR_SIM_DATA_SAMPLERATE_TYPE REAL_8

#undef FR_SIM_DATA_TIMEOFFSEST_TYPE
#define FR_SIM_DATA_TIMEOFFSET_TYPE REAL_8

#undef FR_SIM_DATA_FSHIFT_TYPE
#define FR_SIM_DATA_FSHIFT_TYPE REAL_8

#undef FR_SIM_DATA_PHASE_TYPE
#define FR_SIM_DATA_PHASE_TYPE REAL_4

#if defined( __cplusplus ) && !defined( SWIG )

#include "framecpp/Common/SearchContainer.hh"

#include "framecpp/Version8/FrTable.hh"
#include "framecpp/Version8/FrVect.hh"

#include "framecpp/Version8/impl/FrObjectMetaData.hh"

namespace FrameCPP
{
    namespace Version_8
    {
        namespace FrSimDataImpl
        {
            class Data : public Impl::FrObjectMetaData< Data >
            {
            public:
                typedef FR_SIM_DATA_NAME_TYPE                name_type;
                typedef FR_SIM_DATA_COMMENT_TYPE             comment_type;
                typedef FR_SIM_DATA_SAMPLERATE_TYPE          sampleRate_type;
                typedef FR_SIM_DATA_TIMEOFFSET_TYPE          timeOffset_type;
                typedef FR_SIM_DATA_FSHIFT_TYPE              fShift_type;
                typedef FR_SIM_DATA_PHASE_TYPE               phase_type;
                typedef typename Common::Container< FrVect > data_type;
                typedef typename data_type::iterator         iterator;
                typedef typename data_type::const_iterator   const_iterator;

                typedef
                    typename Common::SearchContainer< FrVect, &FrVect::GetName >
                                                      input_type;
                typedef typename input_type::iterator input_iterator;
                typedef
                    typename input_type::const_iterator const_input_iterator;

                typedef
                    typename Common::SearchContainer< FrTable,
                                                      &FrTable::GetNameSlow >
                                                      table_type;
                typedef typename table_type::iterator table_iterator;
                typedef
                    typename table_type::const_iterator const_table_iterator;

                constexpr static timeOffset_type DEFAULT_TIME_OFFSET{ 0 };

                inline const name_type&
                GetName( ) const
                {
                    return ( name );
                }

                inline const comment_type&
                GetComment( ) const
                {
                    return ( comment );
                }

                inline sampleRate_type
                GetSampleRate( ) const
                {
                    return ( sampleRate );
                }

                inline timeOffset_type
                GetTimeOffset( ) const
                {
                    return ( timeOffset );
                }

                inline fShift_type
                GetFShift( ) const
                {
                    return ( fShift );
                }

                inline phase_type
                GetPhase( ) const
                {
                    return ( phase );
                }

                //-----------------------------------------------------------------
                /// \brief Establish the value of the comment field.
                ///
                /// \param[in] Comment
                ///     The desired value of the comment field.
                //-----------------------------------------------------------------
                inline void
                SetComment( const comment_type& Comment )
                {
                    comment = Comment;
                }

                //-----------------------------------------------------------------
                /// \brief Establish the value of the sampleRate field.
                ///
                /// \param[in] SampleRate
                ///     The desired value of the sampleRate field.
                //-----------------------------------------------------------------
                inline void
                SetSampleRate( sampleRate_type SampleRate )
                {
                    sampleRate = SampleRate;
#if WORKING
                    //-----------------------------------------------------------------
                    /// \todo
                    /// Modifications to the sample rate need also be reflected
                    /// in the corrisponding FrVect structures.
                    //-----------------------------------------------------------------
                    for ( fr_sim_data_data_type::iterator
                              cur = RefData( ).begin( ),
                              last = RefData( ).end( );
                          cur != last;
                          ++cur )
                    {
                        cur->
                    }
#endif /* WORKING */
                }

                //-----------------------------------------------------------------
                /// \brief Establish the value of the timeOffset field.
                ///
                /// \param[in] Time
                ///     The desired value of the timeOffset field.
                //-----------------------------------------------------------------
                inline void
                SetTimeOffset( timeOffset_type TimeOffset )
                {
                    timeOffset = TimeOffset;
                }

                inline const data_type&
                RefData( ) const
                {
                    return data;
                }

                inline data_type&
                RefData( )
                {
                    return data;
                }

                inline const input_type&
                RefInput( ) const
                {
                    return input;
                }

                inline input_type&
                RefInput( )
                {
                    return input;
                }

                inline const table_type&
                RefTable( ) const
                {
                    return table;
                }

                inline table_type&
                RefTable( )
                {
                    return table;
                }

                inline bool
                operator==( const Data& RHS ) const
                {
                    return ( ( this == &RHS ) ||
                             ( ( name.compare( RHS.name ) == 0 ) &&
                               ( comment.compare( RHS.comment ) == 0 ) &&
                               ( sampleRate == RHS.sampleRate ) &&
                               ( timeOffset == RHS.timeOffset ) &&
                               ( fShift == RHS.fShift ) &&
                               ( phase == RHS.phase ) ) );
                }

            protected:
                //-------------------------------------------------------
                /// Name of simulated data
                //-------------------------------------------------------
                name_type name;
                //-------------------------------------------------------
                /// Comment
                //-------------------------------------------------------
                comment_type comment;
                //-------------------------------------------------------
                /// Simulated data sample rate, samples/s
                //-------------------------------------------------------
                sampleRate_type sampleRate;
                //-------------------------------------------------------
                /// Offset of 1st sample relative to the frame start time
                //-------------------------------------------------------
                timeOffset_type timeOffset;
                //-------------------------------------------------------
                /// fShift is the frequency in the original data
                //-------------------------------------------------------
                fShift_type fShift;
                //-------------------------------------------------------
                /// Phase of hetrodyning signal at start of dataset.
                //-------------------------------------------------------
                phase_type phase;

                data_type  data;
                input_type input;
                table_type table;
                //=======================================================
                //-------------------------------------------------------
                static constexpr unsigned int MAX_REF{ 3 };
            }; // class Data
        } // namespace FrSimDataImpl
    } // namespace Version_8
} // namespace FrameCPP

FR_OBJECT_META_DATA_DECLARE( FrSimDataImpl )

#endif /* defined( __cplusplus ) && !defined( SWIG ) */

#endif /* FrameCPP_VERSION_8__IMPL__FrSimDataData_HH */
