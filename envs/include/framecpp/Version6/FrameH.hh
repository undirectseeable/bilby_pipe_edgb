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

#ifndef FrameCPP_VERSION_6_FrameH_HH
#define FrameCPP_VERSION_6_FrameH_HH

#if !defined( SWIGIMPORTED )
#include "ldastoolsal/types.hh"

#include <boost/shared_ptr.hpp>

#include "framecpp/Version6/FrameSpec.hh"

#include "framecpp/Common/Description.hh"
#include "framecpp/Common/SearchContainer.hh"
#include "framecpp/Common/FrameH.hh"
#include "framecpp/Common/TOCInfo.hh"
#endif /* !defined(SWIGIMPORTED) */

#include "framecpp/Version4/FrameH.hh"

#if !defined( SWIGIMPORTED )
#include "framecpp/Version6/GPSTime.hh"
#include "framecpp/Version6/STRING.hh"
#include "framecpp/Version6/PTR_STRUCT.hh"
#include "framecpp/Version6/FrSE.hh"

#include "framecpp/Version6/FrDetector.hh"
#include "framecpp/Version6/FrEvent.hh"
#include "framecpp/Version6/FrHistory.hh"
#include "framecpp/Version6/FrProcData.hh"
#include "framecpp/Version6/FrRawData.hh"
#include "framecpp/Version6/FrSimData.hh"
#include "framecpp/Version6/FrSimEvent.hh"
#include "framecpp/Version6/FrSummary.hh"
#include "framecpp/Version6/FrTable.hh"
#include "framecpp/Version6/FrVect.hh"
#endif /* !defined(SWIGIMPORTED) */

#if !defined( SWIGIMPORTED )
namespace FrameCPP
{
    namespace Version_6
    {
        //===================================================================
        /// \brief Non-PTR_STRUCT elements of the FrameH structure
        ///
        /// This class contains the data members of the FrameH structure
        /// that are not refernced by a pointer.
        /// This allows for easier migration into future
        /// frame specifications.
        //===================================================================
        class FrameHNPS : public Common::TOCInfo
        {
        public:
            typedef FRAME_H_NAME_TYPE         name_type;
            typedef FRAME_H_RUN_TYPE          run_type;
            typedef FRAME_H_FRAME_TYPE        frame_type;
            typedef FRAME_H_DATA_QUALITY_TYPE dataQuality_type;
            typedef FRAME_H_G_TIME_S_TYPE     GTimeS_type;
            typedef FRAME_H_G_TIME_N_TYPE     GTimeN_type;
            typedef FRAME_H_G_TIME_TYPE       GTime_type;
            typedef FRAME_H_U_LEAP_S_TYPE     ULeapS_type;
            typedef FRAME_H_LOCAL_TIME_TYPE   localTime_type;
            typedef FRAME_H_DT_TYPE           dt_type;

            //-----------------------------------------------------------------
            /// \brief Default constructor
            ///
            /// Construct a new FrameHNPS object with default values
            ///
            /// \return
            ///     A new FrameHNPS object.
            //-----------------------------------------------------------------
            FrameHNPS( );

            //-----------------------------------------------------------------
            /// \brief Copy Constructor
            ///
            /// Construct a new FrameHNPS object based on Source.
            ///
            /// \param[in] Source
            ///     Instance to use to populate this instance.
            ///
            /// \return
            ///     A new FrameHNPS object.
            //-----------------------------------------------------------------
            FrameHNPS( const FrameHNPS& Source );

            //-----------------------------------------------------------------
            /// \brief Constructor
            ///
            /// Construct a new FrameHNPS object with explicate values.
            ///
            /// \param[in] name
            ///     Name of project or other experiment description.
            /// \param[in] run
            ///     Run number (number < 0 reserved fro simulated data);
            ///     monotonic for experimental runs.
            /// \param[in] frame
            ///     Frame number, monotonically increasing until end of run,
            ///     re-starting from 0 with each new run.
            /// \param[in] time
            ///     Frame start time.
            /// \param[in] uLeapS
            ///     The integer number of leap seconds between GPS/TAI
            ///     and UTC in epoch when the frame is written
            /// \param[in] dt
            ///     Frame length in seconds.
            /// \param[in] dqual
            ///     A logical 32-bit word to denote top level quality of data.
            ///     Lowest order bits are reserved in pairs for the various
            ///     GW detectors.
            ///
            /// \return
            ///     A new FrameHNPS object.
            //-----------------------------------------------------------------
            FrameHNPS( const std::string& name,
                       INT_4S             run,
                       INT_4U             frame,
                       const GPSTime&     time,
                       INT_2U             uLeapS,
                       const REAL_8       dt,
                       INT_4U             dqual );

            //-----------------------------------------------------------------
            /// \brief Retrieve name of project
            ///
            /// \return
            ///     Name of project
            //-----------------------------------------------------------------
            const std::string& GetName( ) const;

            //-----------------------------------------------------------------
            /// \brief Run number
            ///
            /// \return
            ///     The run number of the frame
            //-----------------------------------------------------------------
            run_type GetRun( ) const;

            //-----------------------------------------------------------------
            /// \brief Frame number
            ///
            /// \return
            ///     The frame number of the frame
            //-----------------------------------------------------------------
            frame_type GetFrame( ) const;

            //-----------------------------------------------------------------
            /// \brief Data quality flag
            ///
            /// \return
            ///     The data quality flag for the frame
            //-----------------------------------------------------------------
            dataQuality_type GetDataQuality( ) const;

            //-----------------------------------------------------------------
            /// \brief Start Time
            ///
            /// \return
            ///     The start time of the frame
            //-----------------------------------------------------------------
            const GPSTime& GetGTime( ) const;

            //-----------------------------------------------------------------
            /// \brief Leap seconds
            ///
            /// \return
            ///     The integer number of leap seconds associated with
            ///     the start time.
            //-----------------------------------------------------------------
            ULeapS_type GetULeapS( ) const;

            //-----------------------------------------------------------------
            /// \brief Frame length
            ///
            /// \return
            ///     Length of frame in seconds.
            //-----------------------------------------------------------------
            dt_type GetDt( ) const;

            //-----------------------------------------------------------------
            /// \brief Establish the name
            ///
            /// \param[in] Name
            ///     The name to associate with the frame
            //-----------------------------------------------------------------
            void SetName( const std::string& Name );

            //-----------------------------------------------------------------
            /// \brief Establish the run number
            ///
            /// \param[in] Run
            ///     The run number to associate with the frame.
            //-----------------------------------------------------------------
            void SetRun( run_type Run );

            //-----------------------------------------------------------------
            /// \brief Establish the data quality flag
            ///
            /// \param[in] DataQuality
            ///     The value of the data quality flag.
            //-----------------------------------------------------------------
            void SetDataQuality( dataQuality_type DataQuality );

            //-----------------------------------------------------------------
            /// \brief Establish the frame duration.
            ///
            /// \param[in] Dt
            ///     The length of the frame in seconds
            //-----------------------------------------------------------------
            void SetDt( dt_type Dt );

            //-----------------------------------------------------------------
            /// \brief Establish the start time.
            ///
            /// \param[in] GTime
            ///     The start time of the frame.
            //-----------------------------------------------------------------
            void SetGTime( const GPSTime& GTime );

            //-----------------------------------------------------------------
            /// \brief Establish leap second offset.
            ///
            /// \param[in] Value
            ///     Number of leap seconds since GPS epoc.
            //-----------------------------------------------------------------
            void SetULeapS( ULeapS_type Value );

        protected:
            //-----------------------------------------------------------------
            //-----------------------------------------------------------------
            typedef Common::IStringStream assign_stream_type;

            //-----------------------------------------------------------------
            /// \brief Copy Constructor based on a previous frame specification.
            ///
            /// \param[in] Source
            ///     A FrmaeHNPS object of a previous frame specification.
            ///
            /// \return
            ///     A new FrameHNPS object
            //-----------------------------------------------------------------
            FrameHNPS( const Previous::FrameHNPS& Source );

            //-----------------------------------------------------------------
            /// \brief Hook to provide table of contents information
            ///
            //-----------------------------------------------------------------
#if WORKING_VIRTUAL_TOCQUERY
            virtual void TOCQuery( int InfoClass, ... ) const;
#endif /*  WORKING_VIRTUAL_TOCQUERY */

            //-----------------------------------------------------------------
            /// \brief Assign the contents of the instance
            ///
            /// \param[in] Stream
            ///     An input stream from which to read information for
            ///     the instance.
            ///
            /// \note
            ///     This has been hidden so programmers are not tempted to
            ///     bypass usage of IFrameStream as the input stream.
            //-----------------------------------------------------------------
            void assign( assign_stream_type& Stream );

            //-----------------------------------------------------------------
            /// \brief The description of structure
            ///
            /// \param[out] Desc
            ///     Storage for the description of the structure.
            //-----------------------------------------------------------------
            template < typename SE >
            static void dataDescription( Common::Description& Desc );

            struct data_type
            {
                STRING  name;
                INT_4S  run;
                INT_4U  frame;
                INT_4U  dataQuality;
                GPSTime GTime;
                INT_2U  ULeapS;
                REAL_8  dt;

                //---------------------------------------------------------------
                //---------------------------------------------------------------
                inline data_type( ) : dt( 0 )
                {
                }

                //---------------------------------------------------------------
                //---------------------------------------------------------------
                inline data_type( const data_type& Source )
                    : name( Source.name ), run( Source.run ),
                      frame( Source.frame ), dataQuality( Source.dataQuality ),
                      GTime( Source.GTime ), ULeapS( Source.ULeapS ),
                      dt( Source.dt )
                {
                }

                //---------------------------------------------------------------
                //---------------------------------------------------------------
                inline data_type( const std::string& Name,
                                  INT_4S             Run,
                                  INT_4U             Frame,
                                  const GPSTime&     GTime,
                                  INT_2U             ULeapS,
                                  const REAL_8       DT,
                                  INT_4U             DQual )
                    : name( Name ), run( Run ), frame( Frame ),
                      dataQuality( DQual ), GTime( GTime ), ULeapS( ULeapS ),
                      dt( DT )
                {
                }

                //---------------------------------------------------------------
                //---------------------------------------------------------------
                inline data_type( const Previous::FrameHNPS& Source )
                    : name( Source.GetName( ) ), run( Source.GetRun( ) ),
                      frame( Source.GetFrame( ) ),
                      dataQuality( Source.GetDataQuality( ) ),
                      GTime( Source.GetGTime( ) ),
                      ULeapS( Source.GetULeapS( ) ), dt( Source.GetDt( ) )
                {
                }

                //---------------------------------------------------------------
                //---------------------------------------------------------------
                FrameCPP::cmn_streamsize_type Bytes( ) const;

                inline bool
                operator==( const data_type& RHS ) const
                {
                    bool retval( ( this == &RHS ) ||
                                 ( ( name == RHS.name ) && ( run == RHS.run ) &&
                                   ( frame == RHS.frame ) &&
                                   ( dataQuality == RHS.dataQuality ) &&
                                   ( GTime == RHS.GTime ) &&
                                   ( ULeapS == RHS.ULeapS ) &&
                                   ( dt == RHS.dt ) ) );
                    return retval;
                }

                //---------------------------------------------------------------
                //---------------------------------------------------------------
                inline void
                operator( )( Common::IStream& Stream )
                {
                    Stream >> name >> run >> frame >> dataQuality >> GTime >>
                        ULeapS >> dt;
                }

                //---------------------------------------------------------------
                //---------------------------------------------------------------
                inline void
                operator( )( Common::OStream& Stream ) const
                {
                    Stream << name << run << frame << dataQuality << GTime
                           << ULeapS << dt;
                }

            }; /* struct data_type */

#if !WORKING_VIRTUAL_TOCQUERY
            virtual void vTOCQuery( int InfoClass, va_list vl ) const;
#endif /* ! WORKING_VIRTUAL_TOCQUERY */

            //-----------------------------------------------------------------
            //-----------------------------------------------------------------
            data_type m_data;
        };

        //-------------------------------------------------------------------
        //-------------------------------------------------------------------
        inline FrameCPP::cmn_streamsize_type
        FrameHNPS::data_type::Bytes( ) const
        {
            return name.Bytes( ) + sizeof( run ) // run;
                + sizeof( frame ) // frame;
                + sizeof( dataQuality ) // dataQuality;
                + sizeof( INT_4U ) // GTime Seconds;
                + sizeof( INT_4U ) // GTime Nanoeconds;
                + sizeof( ULeapS ) // ULeapS;
                + sizeof( dt ) // dt;
                ;
        }

        //-------------------------------------------------------------------
        /// Construct a new FrameHNPS object using values from
        /// a previous frame specification.
        //-------------------------------------------------------------------
        inline FrameHNPS::FrameHNPS( const Previous::FrameHNPS& Source )
            : m_data( Source )
        {
        }

        //-------------------------------------------------------------------
        /// Retrieve the name of project or other experiment description.
        //-------------------------------------------------------------------
        inline const std::string&
        FrameHNPS::GetName( ) const
        {
            return m_data.name;
        }

        //-------------------------------------------------------------------
        /// Retrieve the run number associated with the frame.
        //-------------------------------------------------------------------
        inline FrameHNPS::run_type
        FrameHNPS::GetRun( ) const
        {
            return m_data.run;
        }

        //-------------------------------------------------------------------
        /// Retrieve the frame number associated with the frame
        //-------------------------------------------------------------------
        inline FrameHNPS::frame_type
        FrameHNPS::GetFrame( ) const
        {
            return m_data.frame;
        }

        //-------------------------------------------------------------------
        /// Retrieve the data quality flag associated with the frame
        //-------------------------------------------------------------------
        inline FrameHNPS::dataQuality_type
        FrameHNPS::GetDataQuality( ) const
        {
            return m_data.dataQuality;
        }

        //-------------------------------------------------------------------
        /// Retrieve the start time of the frame.
        //-------------------------------------------------------------------
        inline const GPSTime&
        FrameHNPS::GetGTime( ) const
        {
            return m_data.GTime;
        }

        //-------------------------------------------------------------------
        /// Retrieve the number of leap seconds associated with the frame.
        //-------------------------------------------------------------------
        inline FrameHNPS::ULeapS_type
        FrameHNPS::GetULeapS( ) const
        {
            return m_data.ULeapS;
        }

        //-------------------------------------------------------------------
        /// Retrieve the duration of the frame in seconds.
        //-------------------------------------------------------------------
        inline FrameHNPS::dt_type
        FrameHNPS::GetDt( ) const
        {
            return m_data.dt;
        }

        //-------------------------------------------------------------------
        /// Set the project name of the frame.
        /// Values less than zero are reserved for simulated data.
        /// For experimental runs, this value is monotonicly increasing.
        //-------------------------------------------------------------------
        inline void
        FrameHNPS::SetName( const std::string& Name )
        {
            m_data.name = Name;
        }

        //-------------------------------------------------------------------
        /// Set the run number of the frame.
        /// Values less than zero are reserved for simulated data.
        /// For experimental runs, this value is monotonicly increasing.
        //-------------------------------------------------------------------
        inline void
        FrameHNPS::SetRun( run_type Run )
        {
            m_data.run = Run;
        }

        //-------------------------------------------------------------------
        /// Set the data quality flag of the frame.
        //-------------------------------------------------------------------
        inline void
        FrameHNPS::SetDataQuality( dataQuality_type DataQuality )
        {
            m_data.dataQuality = DataQuality;
        }

        //-------------------------------------------------------------------
        /// Set the length of the frame in seconds.
        //-------------------------------------------------------------------
        inline void
        FrameHNPS::SetDt( dt_type Dt )
        {
            m_data.dt = Dt;
        }

        //-------------------------------------------------------------------
        /// Set the start time of the frame.
        //-------------------------------------------------------------------
        inline void
        FrameHNPS::SetGTime( const GPSTime& GTime )
        {
            m_data.GTime = GTime;
            m_data.ULeapS = m_data.GTime.GetLeapSeconds( );
        }

        //-------------------------------------------------------------------
        /// Set the number of leap seconds since GPS epoc.
        //-------------------------------------------------------------------
        inline void
        FrameHNPS::SetULeapS( ULeapS_type Value )
        {
            m_data.ULeapS = Value;
        }

        inline void
        FrameHNPS::assign( assign_stream_type& Stream )
        {
            Stream >> m_data.name >> m_data.run >> m_data.frame >>
                m_data.dataQuality >> m_data.GTime >> m_data.ULeapS >>
                m_data.dt;
        }

        //-------------------------------------------------------------------
        /// Append descriptions of the fields managed by this object to
        /// the user supplied Description object.
        //-------------------------------------------------------------------
        template < typename SE >
        inline void
        FrameHNPS::dataDescription( Common::Description& Desc )
        {
            Desc( SE( "name",
                      "STRING",
                      "Name of project or other experiment description" ) );
            Desc( SE( "run",
                      "INT_4S",
                      "Run number(number<0 reserved for simulated data);"
                      " monotonic for experimental runs." ) );
            Desc( SE( "frame",
                      "INT_4U",
                      "Frame number, monotonically increasing until end of run,"
                      " re-starting from 0 with each new run" ) );
            Desc(
                SE( "dataQuality",
                    "INT_4U",
                    "A logical 32-bit word to denote top level quality of data."
                    " Lowest order bits are reserved in pairs for the various"
                    " GW detectors" ) );
            Desc( SE( "GTimeS", "INT_4U", "Frame start time in GPS seconds" ) );
            Desc( SE( "GTimeN",
                      "INT_4U",
                      "Frame start time residual, integer nanoseconds" ) );
            Desc(
                SE( "ULeapS",
                    "INT_2U",
                    "The integer number of leap seconds between GPS/TAI and UTC"
                    " in the epoch when the frame is written" ) );
            Desc( SE( "dt", "REAL_8", "Frame length in seconds." ) );
        }

        //===================================================================
        /// \brief PTR_STRUCT elements of the FrmaeH structure.
        ///
        /// This class contains the PTR_STRUCT references of the FrameH
        /// structure.
        /// This allows for easier migration into future
        /// frame specifications.
        //===================================================================
        template < typename TDetector,
                   typename TEvent,
                   typename THistory,
                   typename TProcData,
                   typename TRawData,
                   typename TSimData,
                   typename TSimEvent,
                   typename TSummary,
                   typename TTable,
                   typename TVect >
        class FrameHPST
        {
        public:
            static const INT_2U MAX_REF = 13;

            typedef boost::shared_ptr< TRawData > rawData_type;

            typedef typename Common::SearchContainer< TVect, &TVect::GetName >
                                                       type_type;
            typedef typename type_type::iterator       type_iterator;
            typedef typename type_type::const_iterator const_type_iterator;
            typedef typename type_type::hash_iterator  type_hash_iterator;
            typedef typename type_type::const_hash_iterator
                const_type_hash_iterator;

            typedef typename Common::SearchContainer< TVect, &TVect::GetName >
                                                       user_type;
            typedef typename user_type::iterator       user_iterator;
            typedef typename user_type::const_iterator const_user_iterator;
            typedef typename user_type::hash_iterator  user_hash_iterator;
            typedef typename user_type::const_hash_iterator
                const_user_hash_iterator;

            typedef typename Common::SearchContainer< TDetector,
                                                      &TDetector::GetName >
                                                      detectSim_type;
            typedef typename detectSim_type::iterator detectSim_iterator;
            typedef typename detectSim_type::const_iterator
                const_detectSim_iterator;
            typedef
                typename detectSim_type::hash_iterator detectSim_hash_iterator;
            typedef typename detectSim_type::const_hash_iterator
                const_detectSim_hash_iterator;

            typedef typename Common::SearchContainer< TDetector,
                                                      &TDetector::GetName >
                                                       detectProc_type;
            typedef typename detectProc_type::iterator detectProc_iterator;
            typedef typename detectProc_type::const_iterator
                const_detectProc_iterator;
            typedef typename detectProc_type::hash_iterator
                detectProc_hash_iterator;
            typedef typename detectProc_type::const_hash_iterator
                const_detectProc_hash_iterator;

            typedef
                typename Common::SearchContainer< TEvent, &TEvent::GetNameSlow >
                                                        event_type;
            typedef typename event_type::iterator       event_iterator;
            typedef typename event_type::const_iterator const_event_iterator;
            typedef typename event_type::hash_iterator  event_hash_iterator;
            typedef typename event_type::const_hash_iterator
                const_event_hash_iterator;

            typedef
                typename Common::SearchContainer< THistory, &THistory::GetName >
                                                    history_type;
            typedef typename history_type::iterator history_iterator;
            typedef
                typename history_type::const_iterator    const_history_iterator;
            typedef typename history_type::hash_iterator history_hash_iterator;
            typedef typename history_type::const_hash_iterator
                const_history_hash_iterator;

            typedef typename Common::SearchContainer< TProcData,
                                                      &TProcData::GetNameSlow >
                                                     procData_type;
            typedef typename procData_type::iterator procData_iterator;
            typedef
                typename procData_type::const_iterator const_procData_iterator;
            typedef
                typename procData_type::hash_iterator procData_hash_iterator;
            typedef typename procData_type::const_hash_iterator
                const_procData_hash_iterator;

            typedef typename Common::SearchContainer< TSimData,
                                                      &TSimData::GetNameSlow >
                                                    simData_type;
            typedef typename simData_type::iterator simData_iterator;
            typedef
                typename simData_type::const_iterator    const_simData_iterator;
            typedef typename simData_type::hash_iterator simData_hash_iterator;
            typedef typename simData_type::const_hash_iterator
                const_simData_hash_iterator;

            typedef typename Common::SearchContainer< TSimEvent,
                                                      &TSimEvent::GetNameSlow >
                                                     simEvent_type;
            typedef typename simEvent_type::iterator simEvent_iterator;
            typedef
                typename simEvent_type::const_iterator const_simEvent_iterator;
            typedef
                typename simEvent_type::hash_iterator simEvent_hash_iterator;
            typedef typename simEvent_type::const_hash_iterator
                const_simEvent_hash_iterator;

            typedef
                typename Common::SearchContainer< TSummary, &TSummary::GetName >
                                                        summaryData_type;
            typedef typename summaryData_type::iterator summaryData_iterator;
            typedef typename summaryData_type::const_iterator
                const_summaryData_iterator;
            typedef typename summaryData_type::hash_iterator
                summaryData_hash_iterator;
            typedef typename summaryData_type::const_hash_iterator
                const_summaryData_hash_iterator;

            typedef typename Common::SearchContainer< TVect, &TVect::GetName >
                                                    auxData_type;
            typedef typename auxData_type::iterator auxData_iterator;
            typedef
                typename auxData_type::const_iterator    const_auxData_iterator;
            typedef typename auxData_type::hash_iterator auxData_hash_iterator;
            typedef typename auxData_type::const_hash_iterator
                const_auxData_hash_iterator;

            typedef
                typename Common::SearchContainer< TTable, &TTable::GetNameSlow >
                                                     auxTable_type;
            typedef typename auxTable_type::iterator auxTable_iterator;
            typedef
                typename auxTable_type::const_iterator const_auxTable_iterator;
            typedef
                typename auxTable_type::hash_iterator auxTable_hash_iterator;
            typedef typename auxTable_type::const_hash_iterator
                const_auxTable_hash_iterator;

            //-----------------------------------------------------------------
            /// \brief Brief Constructor
            ///
            /// \return
            ///     A new FrameHPST object
            //-----------------------------------------------------------------
            inline FrameHPST( )
            {
            }

            //-----------------------------------------------------------------
            /// \brief Copy Constructor
            ///
            /// \param[in] Source
            ///     The source for the new object.
            ///
            /// \return
            ///     A new FrameHPST object
            //-----------------------------------------------------------------
            inline FrameHPST( const FrameHPST& Source )
                : m_refs( Source.m_refs )
            {
            }

            //-----------------------------------------------------------------
            /// \brief Retrieve the raw data reference
            ///
            /// \return
            ///     A pointer to the raw data structure.
            //-----------------------------------------------------------------
            inline rawData_type
            GetRawData( ) const
            {
                return m_refs.rawData;
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
                return m_refs.rawData;
            }

            inline const type_type&
            RefType( ) const
            {
                return m_refs.type;
            }

            inline type_type&
            RefType( )
            {
                return m_refs.type;
            }

            inline const user_type&
            RefUser( ) const
            {
                return m_refs.user;
            }

            inline user_type&
            RefUser( )
            {
                return m_refs.user;
            }

            inline const detectSim_type&
            RefDetectSim( ) const
            {
                return m_refs.detectSim;
            }

            inline detectSim_type&
            RefDetectSim( )
            {
                return m_refs.detectSim;
            }

            inline const detectProc_type&
            RefDetectProc( ) const
            {
                return m_refs.detectProc;
            }

            inline detectProc_type&
            RefDetectProc( )
            {
                return m_refs.detectProc;
            }

            inline const history_type&
            RefHistory( ) const
            {
                return m_refs.history;
            }

            inline history_type&
            RefHistory( )
            {
                return m_refs.history;
            }

            inline const procData_type&
            RefProcData( ) const
            {
                return m_refs.procData;
            }

            inline procData_type&
            RefProcData( )
            {
                return m_refs.procData;
            }

            inline const simData_type&
            RefSimData( ) const
            {
                return m_refs.simData;
            }

            inline simData_type&
            RefSimData( )
            {
                return m_refs.simData;
            }

            inline const event_type&
            RefEvent( ) const
            {
                return m_refs.event;
            }

            inline event_type&
            RefEvent( )
            {
                return m_refs.event;
            }

            inline const simEvent_type&
            RefSimEvent( ) const
            {
                return m_refs.simEvent;
            }

            inline simEvent_type&
            RefSimEvent( )
            {
                return m_refs.simEvent;
            }

            inline const summaryData_type&
            RefSummaryData( ) const
            {
                return m_refs.summaryData;
            }

            inline summaryData_type&
            RefSummaryData( )
            {
                return m_refs.summaryData;
            }

            inline const auxData_type&
            RefAuxData( ) const
            {
                return m_refs.auxData;
            }

            inline auxData_type&
            RefAuxData( )
            {
                return m_refs.auxData;
            }

            inline const auxTable_type&
            RefAuxTable( ) const
            {
                return m_refs.auxTable;
            }

            inline auxTable_type&
            RefAuxTable( )
            {
                return m_refs.auxTable;
            }

            inline void
            SetRawData( rawData_type r )
            {
                m_refs.rawData = r;
            }

        public:
            inline rawData_type*
            AddressOfRawData( ) const
            {
                return &( const_cast< ref_type& >( m_refs ).rawData );
            }

        protected:
            struct ref_type
            {
                type_type            type;
                user_type            user;
                detectSim_type       detectSim;
                detectProc_type      detectProc;
                mutable history_type history;
                rawData_type         rawData;
                procData_type        procData;
                simData_type         simData;
                event_type           event;
                simEvent_type        simEvent;
                summaryData_type     summaryData;
                auxData_type         auxData;
                auxTable_type        auxTable;

                ref_type( ) : procData( false ), simData( false )
                {
                }

                ref_type( const ref_type& Source )
                {
                    rawData.reset( );
                    type = Source.type;
                    user = Source.user;
                    detectSim = Source.detectSim;
                    detectProc = Source.detectProc;
                    history = Source.history;
                    rawData = Source.rawData;
                    procData = Source.procData;
                    simData = Source.simData;
                    event = Source.event;
                    simEvent = Source.simEvent;
                    summaryData = Source.summaryData;
                    auxData = Source.auxData;
                    auxTable = Source.auxTable;
                }

                inline ~ref_type( )
                {
                }

                inline cmn_streamsize_type
                Bytes( ) const
                {
                    return ( PTR_STRUCT::Bytes( ) *
                             MAX_REF ); // All the pointer elements
                }

                void
                readSubset( IStream& Stream, INT_4U ElementMask )
                {
                    if ( !( ElementMask & Common::FrameH::DETECT_SIM ) )
                    {
                        Stream.RemoveResolver( &( detectSim ), MAX_REF );
                    }
                    if ( !( ElementMask & Common::FrameH::DETECT_PROC ) )
                    {
                        Stream.RemoveResolver( &( detectProc ), MAX_REF );
                    }
                    if ( !( ElementMask & Common::FrameH::HISTORY ) )
                    {
                        Stream.RemoveResolver( &( history ), MAX_REF );
                    }
                    if ( !( ElementMask & Common::FrameH::TYPE ) )
                    {
                        Stream.RemoveResolver( &( type ), MAX_REF );
                    }
                    if ( !( ElementMask & Common::FrameH::USER ) )
                    {
                        Stream.RemoveResolver( &( user ), MAX_REF );
                    }
#if WORKING
                    if ( !( ElementMask & Common::FrameH::RAW_DATA ) )
                    {
                        Stream.RemoveResolver( &( rawData ), MAX_REF );
                    }
#endif /* WORKING */
                    Stream.RemoveResolver( &( procData ), MAX_REF );
                    Stream.RemoveResolver( &( simData ), MAX_REF );
                    Stream.RemoveResolver( &( event ), MAX_REF );
                    Stream.RemoveResolver( &( simEvent ), MAX_REF );
                    Stream.RemoveResolver( &( summaryData ), MAX_REF );
                    if ( !( ElementMask & Common::FrameH::AUX_DATA ) )
                    {
                        Stream.RemoveResolver( &( auxData ), MAX_REF );
                    }
                    if ( !( ElementMask & Common::FrameH::AUX_TABLE ) )
                    {
                        Stream.RemoveResolver( &( auxTable ), MAX_REF );
                    }
                }

                inline bool
                operator==( const ref_type& RHS ) const
                {
                    bool retval( ( this == &RHS ) ||
                                 ( ( type == RHS.type ) &&
                                   ( user == RHS.user ) &&
                                   ( detectSim == RHS.detectSim ) &&
                                   ( detectProc == RHS.detectProc ) &&
                                   ( history == RHS.history ) &&
                                   ( ( rawData == RHS.rawData ) ||
                                     ( ( rawData ) && ( RHS.rawData ) &&
                                       ( *rawData == *( RHS.rawData ) ) ) ) &&
                                   ( procData == RHS.procData ) &&
                                   ( simData == RHS.simData ) &&
                                   ( event == RHS.event ) &&
                                   ( simEvent == RHS.simEvent ) &&
                                   ( summaryData == RHS.summaryData ) &&
                                   ( auxData == RHS.auxData ) &&
                                   ( auxTable == RHS.auxTable ) ) );
                    return retval;
                }

                inline void
                operator( )( Common::IStream& Stream )
                {
                    Stream >> type >> user >> detectSim >> detectProc >>
                        history >> &rawData >> procData >> simData >> event >>
                        simEvent >> summaryData >> auxData >> auxTable;
                }

                inline void
                operator( )( Common::OStream& Stream ) const
                {
                    Common::OStream::Pointer raw_data_ptr( rawData );

                    Stream << type << user << detectSim << detectProc << history
                           << raw_data_ptr << procData << simData << event
                           << simEvent << summaryData << auxData << auxTable;
                }
            };

            ref_type m_refs;

            template < typename SE >
            static inline void
            refDescription( Common::Description& Desc )
            {
                Desc( SE( "type",
                          PTR_STRUCT::Desc( FrVect::StructName( ) ),
                          "Identifier for array used to store general info "
                          "like the event type." ) );
                Desc( SE(
                    "user",
                    PTR_STRUCT::Desc( FrVect::StructName( ) ),
                    "Identifier for array for user-provided information." ) );
                Desc( SE( "detectSim",
                          PTR_STRUCT::Desc( FrDetector::StructName( ) ),
                          "Identifier for array storing model or simulation "
                          "parameter data definition" ) );
                Desc( SE( "detectProc",
                          PTR_STRUCT::Desc( FrDetector::StructName( ) ),
                          "Identifier for detector-derived data." ) );
                Desc( SE( "history",
                          PTR_STRUCT::Desc( FrHistory::StructName( ) ),
                          "Identifier for first history of post-processing with"
                          " which frame may have been generated." ) );
                Desc( SE( "rawData",
                          PTR_STRUCT::Desc(
                              rawData_type::element_type::StructName( ) ),
                          "Identifier for the raw data structure" ) );
                Desc( SE( "procData",
                          PTR_STRUCT::Desc( FrProcData::StructName( ) ),
                          "Identifier for the first post-processed data" ) );
                Desc( SE( "simData",
                          PTR_STRUCT::Desc( FrSimData::StructName( ) ),
                          "Identifier for the first simulated data buffers" ) );
                Desc( SE( "event",
                          PTR_STRUCT::Desc( FrEvent::StructName( ) ),
                          "Identifier for the first event structure" ) );
                Desc( SE( "simEvent",
                          PTR_STRUCT::Desc( FrSimEvent::StructName( ) ),
                          "Identifier for the first simulated event data "
                          "structure." ) );
                Desc(
                    SE( "summaryData",
                        PTR_STRUCT::Desc( FrSummary::StructName( ) ),
                        "Identifier for the first statistical summary data" ) );
                Desc( SE( "auxData",
                          PTR_STRUCT::Desc( FrVect::StructName( ) ),
                          "Identifier for the first auxiliary data" ) );
                Desc( SE( "auxTable",
                          PTR_STRUCT::Desc( FrTable::StructName( ) ),
                          "Identifier for the first auxiliary table data" ) );
            }
        };

        typedef FrameHPST< FrDetector,
                           FrEvent,
                           FrHistory,
                           FrProcData,
                           FrRawData,
                           FrSimData,
                           FrSimEvent,
                           FrSummary,
                           FrTable,
                           FrVect >
            FrameHPS;

        //===================================================================
        //===================================================================
        class FrameH : public Common::FrameH, public FrameHNPS, public FrameHPS
        {
        public:
            typedef Common::FrameH::assign_stream_type assign_stream_type;

            //: Default constructor
            FrameH( );
            FrameH( const FrameH& frame );
            FrameH( const std::string& name,
                    INT_4S             run,
                    INT_4U             frame,
                    const GPSTime&     time,
                    INT_2U             uLeapS,
                    const REAL_8       dt,
                    INT_4U             dqual = 0 );
            FrameH( const FrameHNPS& Source );
            FrameH( const Previous::FrameH& Source, istream_type* Stream );
            ~FrameH( );

            static promote_ret_type Promote( INT_2U           Source,
                                             promote_arg_type Obj,
                                             istream_type*    Stream );

            static const char* StructName( );

            static const Common::Description* StructDescription( );

            //: Number of bytes needed to write this structure
            cmn_streamsize_type Bytes( const Common::StreamBase& Stream ) const;

            //-----------------------------------------------------------------
            /// \brief Virtual constructor
            //-----------------------------------------------------------------
            virtual FrameH* Clone( ) const;

            virtual FrameH* Create( istream_type& Stream ) const;

            virtual const char* ObjectStructName( ) const;

            //: Write the structure to the stream
            virtual void Write( OStream& Stream ) const;

            /// \brief comparison operator
            bool operator==( const FrameH& RHS ) const;

            /// \brief comparison operator
            virtual bool
            operator==( const Common::FrameSpec::Object& Obj ) const;

        protected:
            //-----------------------------------------------------------------
            /// \brief Verify the object as being valid
            ///
            /// \param[in] Verifier
            ///     The instance of the Verify object where state information
            ///     is stored.
            /// \param[in] Stream
            ///     The input stream from which the object is being read.
            //-----------------------------------------------------------------
            virtual void VerifyObject( Common::Verify&       Verifier,
                                       Common::IFrameStream& Stream ) const;
            //-----------------------------------------------------------------
            // Interface routines
            //-----------------------------------------------------------------
            virtual void readSubset( istream_type& Stream, INT_4U ElementMask );

            //-----------------------------------------------------------------
            /// \brief Frame start time in seconds
            //-----------------------------------------------------------------
            virtual start_time_normalized_type normalizedStartTime( ) const;

            //-----------------------------------------------------------------
            /// \brief Duration of the frame
            //-----------------------------------------------------------------
            virtual delta_t_normalized_type normalizedDeltaT( ) const;

            //-----------------------------------------------------------------
            /// \brief Assign the contents of the instance
            ///
            /// \param[in] Stream
            ///     An input stream from which to read information for
            ///     the instance.
            ///
            /// \note
            ///     This has been hidden so programmers are not tempted to
            ///     bypass usage of IFrameStream as the input stream.
            //-----------------------------------------------------------------
            virtual void assign( assign_stream_type& Stream );

        private:
            using Common::FrameSpec::Object::Create;

            FrameH( istream_type& Stream );

            /// \brief Down grade an object
            virtual demote_ret_type demote( INT_2U          Target,
                                            demote_arg_type Obj,
                                            istream_type*   Stream ) const;

            /// \brief Upgrade an object
            virtual promote_ret_type promote( INT_2U           Target,
                                              promote_arg_type Obj,
                                              istream_type*    Stream ) const;
        };

        inline FrameH::FrameH( const Previous::FrameH& Source,
                               istream_type*           Stream )
            : Common::FrameH( StructDescription( ) ), FrameHNPS( Source )
        {
            if ( Stream )
            {
                const INT_2U max_ref = Previous::FrameHPS::MAX_REF;

                Stream->ReplaceRef( RefType( ), Source.RefType( ), max_ref );
                Stream->ReplaceRef( RefUser( ), Source.RefUser( ), max_ref );
                Stream->ReplaceRef(
                    RefDetectSim( ), Source.RefDetectSim( ), max_ref );
                Stream->ReplaceRef(
                    RefDetectProc( ), Source.RefDetectProc( ), max_ref );
                Stream->ReplaceRef(
                    RefHistory( ), Source.RefHistory( ), max_ref );
                Stream->ReplacePtr(
                    AddressOfRawData( ), Source.AddressOfRawData( ), max_ref );
                Stream->ReplaceRef(
                    RefProcData( ), Source.RefProcData( ), max_ref );
                Stream->ReplaceRef(
                    RefSimData( ), Source.RefSimData( ), max_ref );
                Stream->ReplaceRef(
                    RefEvent( ), Source.RefTrigData( ), max_ref );
                Stream->ReplaceRef(
                    RefSimEvent( ), Source.RefSimEvent( ), max_ref );
                Stream->ReplaceRef(
                    RefSummaryData( ), Source.RefSummaryData( ), max_ref );
                Stream->ReplaceRef(
                    RefAuxData( ), Source.RefAuxData( ), max_ref );
                Stream->ReplaceRef(
                    RefAuxTable( ), Source.RefAuxTable( ), max_ref );

                Stream->RemoveResolver( &( Source.RefStrain( ) ), max_ref );
            }
        }

        inline FrameH::promote_ret_type
        FrameH::Promote( INT_2U           Source,
                         promote_arg_type Obj,
                         istream_type*    Stream )
        {
            return Object::PromoteObject< Previous::FrameH, FrameH >(
                DATA_FORMAT_VERSION, Source, Obj, Stream );
        }

        inline const char*
        FrameH::StructName( )
        {
            static const char* name = "FrameH";
            return name;
        }

        inline bool
        FrameH::operator==( const FrameH& RHS ) const
        {
            return ( ( m_data == RHS.m_data ) && ( m_refs == RHS.m_refs ) );
        }

        //-------------------------------------------------------------------
        //-------------------------------------------------------------------
        inline start_time_normalized_type
        FrameH::normalizedStartTime( ) const
        {
            return GetGTime( );
        }

        //-------------------------------------------------------------------
        //-------------------------------------------------------------------
        inline delta_t_normalized_type
        FrameH::normalizedDeltaT( ) const
        {
            return GetDt( );
        }
    } // namespace Version_6
} // namespace FrameCPP

#endif /* !defined(SWIGIMPORTED) */

#endif /* FrameCPP_VERSION_6_FrameH_HH */
