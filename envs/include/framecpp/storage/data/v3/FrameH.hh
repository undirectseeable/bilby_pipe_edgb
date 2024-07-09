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

#ifndef FRAMECPP__STORAGE__V3__FRAME_H_HH
#define FRAMECPP__STORAGE__V3__FRAME_H_HH

#if defined( __cplusplus )
#if !defined( SWIG )

#include <boost/shared_ptr.hpp>

#include "ldastoolsal/types.hh"
#include "ldastoolsal/gpstime.hh"

#include "framecpp/Common/Container.hh"

#endif /* ! defined(SWIG) */
#endif /* defined(__cplusplus) */

#undef FRAME_H_NAME_TYPE
#define FRAME_H_NAME_TYPE std::string

#undef FRAME_H_RUN_TYPE
#define FRAME_H_RUN_TYPE INT_4U

#undef FRAME_H_FRAME_TYPE
#define FRAME_H_FRAME_TYPE INT_4U

#undef FRAME_H_G_TIME_TYPE
#define FRAME_H_G_TIME_TYPE LDASTools::AL::GPSTime

#undef FRAME_H_G_TIME_S_TYPE
#define FRAME_H_G_TIME_S_TYPE INT_4U

#undef FRAME_H_G_TIME_N_TYPE
#define FRAME_H_G_TIME_N_TYPE INT_4U

#undef FRAME_H_U_LEAP_S_TYPE
#define FRAME_H_U_LEAP_S_TYPE INT_2U

#undef FRAME_H_LOCAL_TIME_TYPE
#define FRAME_H_LOCAL_TIME_TYPE INT_4S

#undef FRAME_H_DT_TYPE
#define FRAME_H_DT_TYPE REAL_8

#if defined( __cplusplus )
#if !defined( SWIG )

namespace FrameCPP
{
    namespace v3
    {
        template < typename TYPE_T,
                   typename USER_T,
                   typename DETECT_SIM_T,
                   typename DETECT_PROC_T,
                   typename HISTORY_T,
                   typename RAW_DATA_T,
                   typename PROC_DATA_T,
                   typename STRAIN_T,
                   typename SIM_DATA_T,
                   typename TRIG_DATA_T,
                   typename SUMMARY_DATA_T,
                   typename AUX_DATA_T,
                   typename AUX_TABLE_T >
        class FrameH
        {
        public:
            typedef FRAME_H_NAME_TYPE       name_type;
            typedef FRAME_H_RUN_TYPE        run_type;
            typedef FRAME_H_FRAME_TYPE      frame_type;
            typedef FRAME_H_G_TIME_S_TYPE   GTimeS_type;
            typedef FRAME_H_G_TIME_N_TYPE   GTimeN_type;
            typedef FRAME_H_G_TIME_TYPE     GTime_type;
            typedef FRAME_H_U_LEAP_S_TYPE   ULeapS_type;
            typedef FRAME_H_LOCAL_TIME_TYPE localTime_type;
            typedef FRAME_H_DT_TYPE         dt_type;
            //-------------------------------------------------------
            static const INT_2U                     MAX_REF = 13;
            typedef boost::shared_ptr< RAW_DATA_T > rawData_type;

            typedef Common::SearchContainer< TYPE_T, &TYPE_T::GetName >
                                                       type_type;
            typedef typename type_type::iterator       type_iterator;
            typedef typename type_type::const_iterator const_type_iterator;
            typedef typename type_type::hash_iterator  type_hash_iterator;
            typedef typename type_type::const_hash_iterator
                const_type_hash_iterator;

            typedef Common::SearchContainer< USER_T, &USER_T::GetName >
                                                       user_type;
            typedef typename user_type::iterator       user_iterator;
            typedef typename user_type::const_iterator const_user_iterator;
            typedef typename user_type::hash_iterator  user_hash_iterator;
            typedef typename user_type::const_hash_iterator
                const_user_hash_iterator;

            typedef Common::SearchContainer< DETECT_SIM_T,
                                             &DETECT_SIM_T::GetName >
                                                      detectSim_type;
            typedef typename detectSim_type::iterator detectSim_iterator;
            typedef typename detectSim_type::const_iterator
                const_detectSim_iterator;
            typedef
                typename detectSim_type::hash_iterator detectSim_hash_iterator;
            typedef typename detectSim_type::const_hash_iterator
                const_detectSim_hash_iterator;

            typedef Common::SearchContainer< DETECT_PROC_T,
                                             &DETECT_PROC_T::GetName >
                                                       detectProc_type;
            typedef typename detectProc_type::iterator detectProc_iterator;
            typedef typename detectProc_type::const_iterator
                const_detectProc_iterator;
            typedef typename detectProc_type::hash_iterator
                detectProc_hash_iterator;
            typedef typename detectProc_type::const_hash_iterator
                const_detectProc_hash_iterator;

            typedef Common::SearchContainer< TRIG_DATA_T,
                                             &TRIG_DATA_T::GetNameSlow >
                                                     trigData_type;
            typedef typename trigData_type::iterator trigData_iterator;
            typedef
                typename trigData_type::const_iterator const_trigData_iterator;
            typedef
                typename trigData_type::hash_iterator trigData_hash_iterator;
            typedef typename trigData_type::const_hash_iterator
                const_trigData_hash_iterator;

            typedef Common::SearchContainer< HISTORY_T, &HISTORY_T::GetName >
                                                    history_type;
            typedef typename history_type::iterator history_iterator;
            typedef
                typename history_type::const_iterator    const_history_iterator;
            typedef typename history_type::hash_iterator history_hash_iterator;
            typedef typename history_type::const_hash_iterator
                const_history_hash_iterator;

            typedef Common::SearchContainer< PROC_DATA_T,
                                             &PROC_DATA_T::GetNameSlow >
                                                     procData_type;
            typedef typename procData_type::iterator procData_iterator;
            typedef
                typename procData_type::const_iterator const_procData_iterator;
            typedef
                typename procData_type::hash_iterator procData_hash_iterator;
            typedef typename procData_type::const_hash_iterator
                const_procData_hash_iterator;

            typedef Common::SearchContainer< STRAIN_T, &STRAIN_T::GetNameSlow >
                                                         strain_type;
            typedef typename strain_type::iterator       strain_iterator;
            typedef typename strain_type::const_iterator const_strain_iterator;
            typedef typename strain_type::hash_iterator  strain_hash_iterator;
            typedef typename strain_type::const_hash_iterator
                const_strain_hash_iterator;

            typedef Common::SearchContainer< SIM_DATA_T,
                                             &SIM_DATA_T::GetNameSlow >
                                                    simData_type;
            typedef typename simData_type::iterator simData_iterator;
            typedef
                typename simData_type::const_iterator    const_simData_iterator;
            typedef typename simData_type::hash_iterator simData_hash_iterator;
            typedef typename simData_type::const_hash_iterator
                const_simData_hash_iterator;

            typedef Common::SearchContainer< SUMMARY_DATA_T,
                                             &SUMMARY_DATA_T::GetName >
                                                        summaryData_type;
            typedef typename summaryData_type::iterator summaryData_iterator;
            typedef typename summaryData_type::const_iterator
                const_summaryData_iterator;
            typedef typename summaryData_type::hash_iterator
                summaryData_hash_iterator;
            typedef typename summaryData_type::const_hash_iterator
                const_summaryData_hash_iterator;

            typedef Common::SearchContainer< AUX_DATA_T, &AUX_DATA_T::GetName >
                                                    auxData_type;
            typedef typename auxData_type::iterator auxData_iterator;
            typedef
                typename auxData_type::const_iterator    const_auxData_iterator;
            typedef typename auxData_type::hash_iterator auxData_hash_iterator;
            typedef typename auxData_type::const_hash_iterator
                const_auxData_hash_iterator;

            typedef Common::SearchContainer< AUX_TABLE_T,
                                             &AUX_TABLE_T::GetNameSlow >
                                                     auxTable_type;
            typedef typename auxTable_type::iterator auxTable_iterator;
            typedef
                typename auxTable_type::const_iterator const_auxTable_iterator;
            typedef
                typename auxTable_type::hash_iterator auxTable_hash_iterator;
            typedef typename auxTable_type::const_hash_iterator
                const_auxTable_hash_iterator;
            //-------------------------------------------------------

            inline rawData_type*
            AddressOfRawData( ) const
            {
                return ( const_cast< rawData_type* >( &rawData ) );
            }

            //-----------------------------------------------------------------
            /// \brief Retrieve name of project
            ///
            /// Retrieve the name of project or other experiment description.
            ///
            /// \return
            ///     Name of project
            //-----------------------------------------------------------------
            const name_type&
            GetName( ) const
            {
                return name;
            }

            //-----------------------------------------------------------------
            /// \brief Run number
            ///
            /// Retrieve the run number associated with the frame.
            ///
            /// \return
            ///     The run number of the frame
            //-----------------------------------------------------------------
            run_type
            GetRun( ) const
            {
                return run;
            }

            //-----------------------------------------------------------------
            /// \brief Frame number
            ///
            /// Retrieve the frame number associated with the frame
            ///
            /// \return
            ///     The frame number of the frame
            //-----------------------------------------------------------------
            frame_type
            GetFrame( ) const
            {
                return frame;
            }

            //-----------------------------------------------------------------
            /// \brief Start Time
            ///
            /// Retrieve the start time of the frame.
            ///
            /// \return
            ///     The start time of the frame
            //-----------------------------------------------------------------
            const GTime_type&
            GetGTime( ) const
            {
                return GTime;
            }

            //-----------------------------------------------------------------
            /// \brief Leap seconds
            ///
            /// Retrieve the number of leap seconds associated with the frame.
            ///
            /// \return
            ///     The integer number of leap seconds associated with
            ///     the start time.
            //-----------------------------------------------------------------
            ULeapS_type
            GetULeapS( ) const
            {
                return ULeapS;
            }

            //-----------------------------------------------------------------
            /// \brief Local time
            ///
            /// Local seasonal time - UTC in seconds
            ///
            /// \return
            ///     The UTC seasonal time in seconds.
            //-----------------------------------------------------------------
            localTime_type
            GetLocalTime( ) const
            {
                return localTime;
            }

            //-----------------------------------------------------------------
            /// \brief Frame length
            ///
            /// Retrieve the duration of the frame in seconds.
            ///
            /// \return
            ///     Length of frame in seconds.
            //-----------------------------------------------------------------
            dt_type
            GetDt( ) const
            {
                return dt;
            }

            //-----------------------------------------------------------------
            /// \brief Establish the name
            ///
            /// Set the project name of the frame.
            /// Values less than zero are reserved for simulated data.
            /// For experimental runs, this value is monotonicly increasing.
            ///
            /// \param[in] Name
            ///     The name to associate with the frame
            //-----------------------------------------------------------------
            void
            SetName( const name_type& Name )
            {
                name = Name;
            }

            //-----------------------------------------------------------------
            /// \brief Establish the run number
            ///
            /// Set the run number of the frame.
            /// Values less than zero are reserved for simulated data.
            /// For experimental runs, this value is monotonicly increasing.
            ///
            /// \param[in] Run
            ///     The run number to associate with the frame.
            //-----------------------------------------------------------------
            void
            SetRun( run_type Run )
            {
                run = Run;
            }

            //-----------------------------------------------------------------
            /// \brief Establish the frame duration.
            ///
            /// Set the length of the frame in seconds.
            ///
            /// \param[in] Dt
            ///     The length of the frame in seconds
            //-----------------------------------------------------------------
            void
            SetDt( dt_type Dt )
            {
                dt = Dt;
            }

            //-----------------------------------------------------------------
            /// \brief Establish the start time.
            ///
            /// Set the start time of the frame.
            ///
            /// \param[in] Value
            ///     The start time of the frame.
            //-----------------------------------------------------------------
            void
            SetGTime( const GTime_type& Value )
            {
                GTime = Value;
                ULeapS = GTime.GetLeapSeconds( );
            }

            //-----------------------------------------------------------------
            /// \brief Establish UTC seasonal local time
            ///
            /// Set UTC seasonal local time
            ///
            /// \param[in] LocalTime
            ///     UTC seasonal local time
            //-----------------------------------------------------------------
            void
            SetLocalTime( localTime_type LocalTime )
            {
                localTime = LocalTime;
            }

            //-----------------------------------------------------------------
            /// \brief Establish leap second offset.
            ///
            /// \param[in] Value
            ///     Number of leap seconds since GPS epoc.
            //-----------------------------------------------------------------
            void
            SetULeapS( ULeapS_type Value )
            {
                ULeapS = Value;
            }

            //-----------------------------------------------------------------
            /// \brief Retrieve the raw data reference
            ///
            /// Set the number of leap seconds since GPS epoc.
            ///
            /// \return
            ///     A pointer to the raw data structure.
            //-----------------------------------------------------------------
            inline rawData_type
            GetRawData( ) const
            {
                return rawData;
            }

            //-----------------------------------------------------------------
            /// \brief Retrieve the raw data reference
            ///
            /// \return
            ///     A pointer to the raw data structure.
            //-----------------------------------------------------------------
            inline rawData_type
            GetRawData( )
            {
                return rawData;
            }

            inline const type_type&
            RefType( ) const
            {
                return type;
            }

            inline type_type&
            RefType( )
            {
                return type;
            }

            inline const user_type&
            RefUser( ) const
            {
                return user;
            }

            inline user_type&
            RefUser( )
            {
                return user;
            }

            inline const detectSim_type&
            RefDetectSim( ) const
            {
                return detectSim;
            }

            inline detectSim_type&
            RefDetectSim( )
            {
                return detectSim;
            }

            inline const detectProc_type&
            RefDetectProc( ) const
            {
                return detectProc;
            }

            inline detectProc_type&
            RefDetectProc( )
            {
                return detectProc;
            }

            inline const history_type&
            RefHistory( ) const
            {
                return history;
            }

            inline history_type&
            RefHistory( )
            {
                return history;
            }

            inline const strain_type&
            RefProcData( ) const
            {
                return strain;
            }

            inline strain_type&
            RefProcData( )
            {
                return strain;
            }

            inline const simData_type&
            RefSimData( ) const
            {
                return simData;
            }

            inline simData_type&
            RefSimData( )
            {
                return simData;
            }

            inline const trigData_type&
            RefTrigData( ) const
            {
                return trigData;
            }

            inline trigData_type&
            RefTrigData( )
            {
                return trigData;
            }

            inline const summaryData_type&
            RefSummaryData( ) const
            {
                return summaryData;
            }

            inline summaryData_type&
            RefSummaryData( )
            {
                return summaryData;
            }

            inline const auxData_type&
            RefAuxData( ) const
            {
                return auxData;
            }

            inline auxData_type&
            RefAuxData( )
            {
                return auxData;
            }

            inline const auxTable_type&
            RefAuxTable( ) const
            {
                return auxTable;
            }

            inline auxTable_type&
            RefAuxTable( )
            {
                return auxTable;
            }

            inline void
            SetRawData( rawData_type r )
            {
                rawData = r;
            }

            inline bool
            operator==( const FrameH& RHS ) const
            {
                return ( ( this == &RHS ) ||
                         ( ( name.compare( RHS.name ) == 0 ) &&
                           ( run == RHS.run ) && ( frame == RHS.frame ) &&
                           ( GTime == RHS.GTime ) && ( ULeapS == RHS.ULeapS ) &&
                           ( localTime == RHS.localTime ) &&
                           ( dt == RHS.dt ) ) );
            }

        protected:
            //-------------------------------------------------------
            name_type      name;
            run_type       run;
            frame_type     frame;
            GTime_type     GTime;
            ULeapS_type    ULeapS;
            localTime_type localTime;
            dt_type        dt;
            //-------------------------------------------------------
            type_type            type;
            user_type            user;
            detectSim_type       detectSim;
            detectProc_type      detectProc;
            mutable history_type history;
            rawData_type         rawData;
            procData_type        procData;
            strain_type          strain;
            simData_type         simData;
            trigData_type        trigData;
            summaryData_type     summaryData;
            auxData_type         auxData;
            auxTable_type        auxTable;
        };

    } // namespace v3
} // namespace FrameCPP

#endif /* ! defined(SWIG) */
#endif /* defined(__cplusplus) */

#endif /* FRAMECPP__STORAGE__V3__FRAME_H_HH */
