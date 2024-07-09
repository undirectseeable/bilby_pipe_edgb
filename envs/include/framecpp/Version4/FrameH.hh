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

#ifndef FrameCPP_VERSION_4_FrameH_HH
#define FrameCPP_VERSION_4_FrameH_HH

#if !defined( SWIGIMPORTED )

#include "ldastoolsal/types.hh"

#include <boost/shared_ptr.hpp>

#include "framecpp/Version4/FrameSpec.hh"

#include "framecpp/Common/Description.hh"
#include "framecpp/Common/SearchContainer.hh"
#include "framecpp/Common/FrameH.hh"
#include "framecpp/Common/TOCInfo.hh"
#endif /* !defined(SWIGIMPORTED) */

#include "framecpp/Version3/FrameH.hh"

#if !defined( SWIGIMPORTED )
#include "framecpp/Version4/GPSTime.hh"
#include "framecpp/Version4/STRING.hh"
#include "framecpp/Version4/PTR_STRUCT.hh"
#include "framecpp/Version4/FrSE.hh"

#include "framecpp/Version4/FrDetector.hh"
#include "framecpp/Version4/FrHistory.hh"
#include "framecpp/Version4/FrProcData.hh"
#include "framecpp/Version4/FrRawData.hh"
#include "framecpp/Version4/FrSimData.hh"
#include "framecpp/Version4/FrSimEvent.hh"
#include "framecpp/Version4/FrSummary.hh"
#include "framecpp/Version4/FrTable.hh"
#include "framecpp/Version4/FrTrigData.hh"
#include "framecpp/Version4/FrVect.hh"
#endif /* !defined(SWIGIMPORTED) */

#undef FRAME_H_DATA_QUALITY_TYPE
#define FRAME_H_DATA_QUALITY_TYPE INT_4U

#if !defined( SWIGIMPORTED )

#undef FRAME_H_RUN_TYPE
#define FRAME_H_RUN_TYPE INT_4S

namespace FrameCPP
{
    namespace Version_4
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
            typedef FRAME_H_NAME_TYPE       name_type;
            typedef FRAME_H_RUN_TYPE        run_type;
            typedef FRAME_H_FRAME_TYPE      frame_type;
            typedef FRAME_H_G_TIME_S_TYPE   GTimeS_type;
            typedef FRAME_H_G_TIME_N_TYPE   GTimeN_type;
            typedef FRAME_H_G_TIME_TYPE     GTime_type;
            typedef FRAME_H_U_LEAP_S_TYPE   ULeapS_type;
            typedef FRAME_H_LOCAL_TIME_TYPE localTime_type;
            typedef FRAME_H_DT_TYPE         dt_type;

            /// \brief Default constructor
            FrameHNPS( );

            /// \brief Copy Constructor
            FrameHNPS( const FrameHNPS& Source );

            /// \brief Constructor
            FrameHNPS( const std::string& name,
                       INT_4S             run,
                       INT_4U             frame,
                       const GPSTime&     time,
                       INT_2U             uLeapS,
                       INT_4S             LocalTime,
                       const REAL_8       dt,
                       INT_4U             dqual );

            const std::string& GetName( ) const;

            INT_4S GetRun( ) const;

            INT_4U GetFrame( ) const;

            INT_4U GetDataQuality( ) const;

            const GPSTime& GetGTime( ) const;

            INT_2U GetULeapS( ) const;

            REAL_8 GetDt( ) const;

            INT_4S GetLocalTime( ) const;

            void SetRun( INT_4S Run );

            void SetDataQuality( INT_4U DataQuality );

            void SetDt( REAL_8 Dt );

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

            /// \brief Copy Constructor
            FrameHNPS( const Previous::FrameHNPS& Source );

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

            static void dataDescription( Common::Description& Desc );

            struct data_type
            {
                STRING  name;
                INT_4S  run;
                INT_4U  frame;
                INT_4U  dataQuality;
                GPSTime GTime;
                INT_2U  ULeapS;
                INT_4S  localTime;
                REAL_8  dt;

                inline data_type( ) : dt( 0 )
                {
                }

                inline data_type( const data_type& Source )
                    : name( Source.name ), run( Source.run ),
                      frame( Source.frame ), dataQuality( Source.dataQuality ),
                      GTime( Source.GTime ), ULeapS( Source.ULeapS ),
                      dt( Source.dt )
                {
                }

                inline data_type( const std::string& Name,
                                  INT_4S             Run,
                                  INT_4U             Frame,
                                  const GPSTime&     GTime,
                                  INT_2U             ULeapS,
                                  INT_4U             LocalTime,
                                  const REAL_8&      DT,
                                  INT_4U             DQual )
                    : name( Name ), run( Run ), frame( Frame ),
                      dataQuality( DQual ), GTime( GTime ), ULeapS( ULeapS ),
                      localTime( LocalTime ), dt( DT )
                {
                }

                inline data_type( const Previous::FrameHNPS& Source )
                    : name( Source.GetName( ) ), run( Source.GetRun( ) ),
                      frame( Source.GetFrame( ) ), dataQuality( 0 ),
                      GTime( Source.GetGTime( ) ),
                      ULeapS( Source.GetULeapS( ) ),
                      localTime( Source.GetLocalTime( ) ), dt( Source.GetDt( ) )
                {
                }

                FrameCPP::cmn_streamsize_type Bytes( ) const;

                inline bool
                operator==( const data_type& RHS ) const
                {
                    return ( ( this == &RHS ) ||
                             ( ( name == RHS.name ) && ( run == RHS.run ) &&
                               ( frame == RHS.frame ) &&
                               ( dataQuality == RHS.dataQuality ) &&
                               ( GTime == RHS.GTime ) &&
                               ( ULeapS == RHS.ULeapS ) &&
                               ( localTime == RHS.localTime ) &&
                               ( dt == RHS.dt ) ) );
                }

                inline void
                operator( )( Common::IStream& Stream )
                {
                    Stream >> name >> run >> frame >> dataQuality >> GTime >>
                        ULeapS >> localTime >> dt;
                }

                inline void
                operator( )( Common::OStream& Stream ) const
                {
                    Stream << name << run << frame << dataQuality << GTime
                           << ULeapS << localTime << dt;
                }

            }; /* struct data_type */

            data_type m_data;

        protected:
#if !WORKING_VIRTUAL_TOCQUERY
            virtual void vTOCQuery( int InfoClass, va_list vl ) const;
#endif /* ! WORKING_VIRTUAL_TOCQUERY */
        };

        inline FrameCPP::cmn_streamsize_type
        FrameHNPS::data_type::Bytes( ) const
        {
            return name.Bytes( ) + sizeof( run ) // run;
                + sizeof( frame ) // frame;
                + sizeof( dataQuality ) // dataQuality;
                + sizeof( INT_4U ) // GTime Seconds;
                + sizeof( INT_4U ) // GTime Nanoeconds;
                + sizeof( ULeapS ) // ULeapS;
                + sizeof( localTime ) + sizeof( dt ) // dt;
                ;
        }

        inline FrameHNPS::FrameHNPS( const Previous::FrameHNPS& Source )
            : m_data( Source )
        {
        }

        inline const std::string&
        FrameHNPS::GetName( ) const
        {
            return m_data.name;
        }

        inline INT_4S
        FrameHNPS::GetRun( ) const
        {
            return m_data.run;
        }

        inline INT_4U
        FrameHNPS::GetFrame( ) const
        {
            return m_data.frame;
        }

        inline INT_4U
        FrameHNPS::GetDataQuality( ) const
        {
            return m_data.dataQuality;
        }

        inline const GPSTime&
        FrameHNPS::GetGTime( ) const
        {
            return m_data.GTime;
        }

        inline INT_2U
        FrameHNPS::GetULeapS( ) const
        {
            return m_data.ULeapS;
        }

        inline REAL_8
        FrameHNPS::GetDt( ) const
        {
            return m_data.dt;
        }

        inline INT_4S
        FrameHNPS::GetLocalTime( ) const
        {
            return m_data.localTime;
        }

        inline void
        FrameHNPS::SetRun( INT_4S Run )
        {
            m_data.run = Run;
        }

        inline void
        FrameHNPS::SetDataQuality( INT_4U DataQuality )
        {
            m_data.dataQuality = DataQuality;
        }

        inline void
        FrameHNPS::SetDt( REAL_8 Dt )
        {
            m_data.dt = Dt;
        }

        inline void
        FrameHNPS::SetGTime( const GPSTime& GTime )
        {
            m_data.GTime = GTime;
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
                m_data.localTime >> m_data.dt;
        }

        inline void
        FrameHNPS::dataDescription( Common::Description& Desc )
        {
            Desc( FrSE( "name",
                        "STRING",
                        "Name of project or other experiment description" ) );
            Desc( FrSE( "run",
                        "INT_4S",
                        "Run number(number<0 reserved for simulated data);"
                        " monotonic for experimental runs." ) );
            Desc(
                FrSE( "frame",
                      "INT_4U",
                      "Frame number, monotonically increasing until end of run,"
                      " re-starting from 0 with each new run" ) );
            Desc( FrSE(
                "dataQuality",
                "INT_4U",
                "A logical 32-bit word to denote top level quality of data."
                " Lowest order bits are reserved in pairs for the various"
                " GW detectors" ) );
            Desc(
                FrSE( "GTimeS", "INT_4U", "Frame start time in GPS seconds" ) );
            Desc( FrSE( "GTimeN",
                        "INT_4U",
                        "Frame start time residual, integer nanoseconds" ) );
            Desc( FrSE(
                "ULeapS",
                "INT_2U",
                "The integer number of leap seconds between GPS/TAI and UTC"
                " in the epoch when the frame is written" ) );
            Desc( FrSE( "localTime", "INT_4S", "Local seasonal time - UTC" ) );
            Desc( FrSE( "dt", "REAL_8", "Frame length in seconds." ) );
        }

        //===================================================================
        //===================================================================
        template < typename TDetector,
                   typename TTrigData,
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
            static const INT_2U MAX_REF = 14;

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

            typedef typename Common::SearchContainer< TTrigData,
                                                      &TTrigData::GetNameSlow >
                                                     trigData_type;
            typedef typename trigData_type::iterator trigData_iterator;
            typedef
                typename trigData_type::const_iterator const_trigData_iterator;
            typedef
                typename trigData_type::hash_iterator trigData_hash_iterator;
            typedef typename trigData_type::const_hash_iterator
                const_trigData_hash_iterator;

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

            typedef typename Common::SearchContainer< TProcData,
                                                      &TProcData::GetNameSlow >
                                                         strain_type;
            typedef typename strain_type::iterator       strain_iterator;
            typedef typename strain_type::const_iterator const_strain_iterator;
            typedef typename strain_type::hash_iterator  strain_hash_iterator;
            typedef typename strain_type::const_hash_iterator
                const_strain_hash_iterator;

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

            inline FrameHPST( )
            {
            }

            inline FrameHPST( const FrameHPST& Source )
                : m_refs( Source.m_refs )
            {
            }

            inline rawData_type
            GetRawData( ) const
            {
                return m_refs.rawData;
            }

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

            inline const strain_type&
            RefStrain( ) const
            {
                return m_refs.strain;
            }

            inline strain_type&
            RefStrain( )
            {
                return m_refs.strain;
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

            inline const trigData_type&
            RefTrigData( ) const
            {
                return m_refs.trigData;
            }

            inline trigData_type&
            RefTrigData( )
            {
                return m_refs.trigData;
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
                strain_type          strain;
                simData_type         simData;
                trigData_type        trigData;
                simEvent_type        simEvent;
                summaryData_type     summaryData;
                auxData_type         auxData;
                auxTable_type        auxTable;

                ref_type( )
                {
                }

                ref_type( const ref_type& Source )
                {
                    type = Source.type;
                    user = Source.user;
                    detectSim = Source.detectSim;
                    detectProc = Source.detectProc;
                    history = Source.history;
                    rawData = Source.rawData;
                    procData = Source.procData;
                    strain = Source.strain;
                    simData = Source.simData;
                    trigData = Source.trigData;
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
                readSubset( Common::IStream& Stream, INT_4U ElementMask )
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
                    if ( !( ElementMask & Common::FrameH::RAW_DATA ) )
                    {
                        Stream.RemoveResolver( &( rawData ), MAX_REF );
                    }
                    Stream.RemoveResolver( &( procData ), MAX_REF );
                    Stream.RemoveResolver( &( strain ), MAX_REF );
                    Stream.RemoveResolver( &( simData ), MAX_REF );
                    Stream.RemoveResolver( &( trigData ), MAX_REF );
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
                    return ( ( this == &RHS ) ||
                             ( ( type == RHS.type ) && ( user == RHS.user ) &&
                               ( detectSim == RHS.detectSim ) &&
                               ( detectProc == RHS.detectProc ) &&
                               ( history == RHS.history ) &&
                               ( ( rawData == RHS.rawData ) ||
                                 ( ( !rawData ) && ( !RHS.rawData ) &&
                                   ( *rawData == *( RHS.rawData ) ) ) ) &&
                               ( procData == RHS.procData ) &&
                               ( strain == RHS.strain ) &&
                               ( simData == RHS.simData ) &&
                               ( trigData == RHS.trigData ) &&
                               ( simEvent == RHS.simEvent ) &&
                               ( summaryData == RHS.summaryData ) &&
                               ( auxData == RHS.auxData ) &&
                               ( auxTable == RHS.auxTable ) ) );
                }

                inline void
                operator( )( Common::IStream& Stream )
                {
                    Stream >> type >> user >> detectSim >> detectProc >>
                        history >> &rawData >> procData >> strain >> simData >>
                        trigData >> simEvent >> summaryData >> auxData >>
                        auxTable;
                }

                inline void
                operator( )( Common::OStream& Stream ) const
                {
                    Common::OStream::Pointer raw_data_ptr( rawData );

                    Stream << type << user << detectSim << detectProc << history
                           << raw_data_ptr << procData << strain << simData
                           << trigData << simEvent << summaryData << auxData
                           << auxTable;
                }
            };

            ref_type m_refs;

            static inline void
            refDescription( Common::Description& Desc )
            {
                Desc( FrSE(
                    "type", PTR_STRUCT::Desc( FrVect::StructName( ) ), "" ) );
                Desc( FrSE(
                    "user", PTR_STRUCT::Desc( FrVect::StructName( ) ), "" ) );
                Desc( FrSE( "detectSim",
                            PTR_STRUCT::Desc( FrDetector::StructName( ) ),
                            "" ) );
                Desc( FrSE( "detectProc",
                            PTR_STRUCT::Desc( FrDetector::StructName( ) ),
                            "" ) );
                Desc( FrSE( "history",
                            PTR_STRUCT::Desc( FrHistory::StructName( ) ),
                            "" ) );
                Desc( FrSE( "rawData",
                            PTR_STRUCT::Desc(
                                rawData_type::element_type::StructName( ) ),
                            "" ) );
                Desc( FrSE( "procData",
                            PTR_STRUCT::Desc( FrProcData::StructName( ) ),
                            "" ) );
                Desc( FrSE( "strain",
                            PTR_STRUCT::Desc( FrProcData::StructName( ) ),
                            "" ) );
                Desc( FrSE( "simData",
                            PTR_STRUCT::Desc( FrSimData::StructName( ) ),
                            "" ) );
                Desc( FrSE( "trigData",
                            PTR_STRUCT::Desc( FrTrigData::StructName( ) ),
                            "" ) );
                Desc( FrSE( "simEvent",
                            PTR_STRUCT::Desc( FrSimEvent::StructName( ) ),
                            "" ) );
                Desc( FrSE( "summaryData",
                            PTR_STRUCT::Desc( FrSummary::StructName( ) ),
                            "" ) );
                Desc( FrSE( "auxData",
                            PTR_STRUCT::Desc( FrVect::StructName( ) ),
                            "" ) );
                Desc( FrSE( "auxTable",
                            PTR_STRUCT::Desc( FrTable::StructName( ) ),
                            "" ) );
            }
        };

        typedef FrameHPST< FrDetector,
                           FrTrigData,
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

            /// \brief Default constructor
            FrameH( );
            FrameH( const FrameH& frame );
            FrameH( const std::string& name,
                    const INT_4S       run,
                    const INT_4U       frame,
                    const GPSTime&     time,
                    const INT_2U       uLeapS,
                    const INT_4S       LocalTime,
                    const REAL_8       dt,
                    const INT_4U       dqual = 0 );
            FrameH( const FrameHNPS& Source );
            FrameH( const Previous::FrameH& Source, istream_type* Stream );
            ~FrameH( );

            static promote_ret_type Promote( INT_2U           Source,
                                             promote_arg_type Obj,
                                             istream_type*    Stream );

            static const char* StructName( );

            static const Common::Description* StructDescription( );

            /// \brief Number of bytes needed to write this structure
            cmn_streamsize_type Bytes( const Common::StreamBase& Stream ) const;

            //-----------------------------------------------------------------
            /// \brief Virtual constructor
            //-----------------------------------------------------------------
            virtual FrameH* Clone( ) const;

            virtual FrameH* Create( istream_type& Stream ) const;

            virtual const char* ObjectStructName( ) const;

            /// \brief Write the structure to the stream
            virtual void Write( ostream_type& Stream ) const;

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
                    RefStrain( ), Source.RefStrain( ), max_ref );
                Stream->ReplaceRef(
                    RefSimData( ), Source.RefSimData( ), max_ref );
                Stream->ReplaceRef(
                    RefTrigData( ), Source.RefTrigData( ), max_ref );
                Stream->ReplaceRef(
                    RefSummaryData( ), Source.RefSummaryData( ), max_ref );
                Stream->ReplaceRef(
                    RefAuxData( ), Source.RefAuxData( ), max_ref );
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
    } // namespace Version_4
} // namespace FrameCPP

#endif /* !defined(SWIGIMPORTED) */

#endif /* FrameCPP_VERSION_6_FrameH_HH */
