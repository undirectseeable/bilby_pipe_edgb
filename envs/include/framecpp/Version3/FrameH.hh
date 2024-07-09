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

#ifndef FrameCPP_VERSION_3_FrameH_HH
#define FrameCPP_VERSION_3_FrameH_HH

#if !defined( SWIGIMPORTED )

#include "ldastoolsal/types.hh"

#include <boost/shared_ptr.hpp>

#include "framecpp/Version3/FrameSpec.hh"

#include "framecpp/Common/Description.hh"
#include "framecpp/Common/SearchContainer.hh"
#include "framecpp/Common/FrameH.hh"

#include "framecpp/Version3/GPSTime.hh"
#include "framecpp/Version3/STRING.hh"
#include "framecpp/Version3/PTR_STRUCT.hh"
#include "framecpp/Version3/FrSE.hh"

#include "framecpp/Version3/FrDetector.hh"
#include "framecpp/Version3/FrHistory.hh"
#include "framecpp/Version3/FrProcData.hh"
#include "framecpp/Version3/FrRawData.hh"
#include "framecpp/Version3/FrSimData.hh"
#include "framecpp/Version3/FrSummary.hh"
#include "framecpp/Version3/FrTrigData.hh"
#include "framecpp/Version3/FrVect.hh"
#endif /* !defined(SWIGIMPORTED) */

#undef FRAME_H_NAME_TYPE
#define FRAME_H_NAME_TYPE STRING

#undef FRAME_H_RUN_TYPE
#define FRAME_H_RUN_TYPE INT_4U

#undef FRAME_H_FRAME_TYPE
#define FRAME_H_FRAME_TYPE INT_4U

#undef FRAME_H_G_TIME_S_TYPE
#define FRAME_H_G_TIME_S_TYPE INT_4U

#undef FRAME_H_G_TIME_N_TYPE
#define FRAME_H_G_TIME_N_TYPE INT_4U

#undef FRAME_H_G_TIME
#define FRAME_H_G_TIME_TYPE GPSTime

#undef FRAME_H_U_LEAP_S_TYPE
#define FRAME_H_U_LEAP_S_TYPE INT_2U

#undef FRAME_H_LOCAL_TIME_TYPE
#define FRAME_H_LOCAL_TIME_TYPE INT_4S

#undef FRAME_H_DT_TYPE
#define FRAME_H_DT_TYPE REAL_8

#if !defined( SWIGIMPORTED )

#if defined( __cplusplus )
namespace FrameCPP
{
    namespace Version_3
    {
        //===================================================================
        /// \brief Non-PTR_STRUCT elements of the FrameH structure
        ///
        /// This class contains the data members of the FrameH structure
        /// that are not refernced by a pointer.
        /// This allows for easier migration into future
        /// frame specifications.
        //===================================================================
        class FrameHNPS
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

            //-----------------------------------------------------------------
            /// \brief Default constructor
            //-----------------------------------------------------------------
            FrameHNPS( );

            //-----------------------------------------------------------------
            /// \brief Copy Constructor
            ///
            /// \param[in] Source
            ///     The
            //-----------------------------------------------------------------
            FrameHNPS( const FrameHNPS& Source );

            /// \brief Constructor
            FrameHNPS( const std::string& Name,
                       run_type           Run,
                       frame_type         Frame,
                       const GTime_type&  GTimeValue,
                       ULeapS_type        ULeapSValue,
                       localTime_type     LocalTime,
                       const dt_type      Dt );

            const std::string& GetName( ) const;

            run_type GetRun( ) const;

            frame_type GetFrame( ) const;

            const GTime_type& GetGTime( ) const;

            ULeapS_type GetULeapS( ) const;

            dt_type GetDt( ) const;

            localTime_type GetLocalTime( ) const;

            void SetRun( run_type Run );

            void SetDt( dt_type Dt );

            void SetGTime( const GTime_type& Value );

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
            /// \brief Name of project or other experiment description
            ///
            /// Name of project or other experiment description.
            /// (e.g., GEO; LIGO; VIRGO; TAMA; ...)
            //-----------------------------------------------------------------
            name_type name;
            //-----------------------------------------------------------------
            /// \brief Run number
            //-----------------------------------------------------------------
            run_type run;
            //-----------------------------------------------------------------
            /// \brief Frame number
            ///
            /// This value is monotonically increasing until the end of
            /// the run.
            //-----------------------------------------------------------------
            frame_type frame;
            //-----------------------------------------------------------------
            /// \brief Frame start time
            ///
            /// The GPS time since GPS standard epoch.
            //-----------------------------------------------------------------
            GTime_type GTime;
            //-----------------------------------------------------------------
            /// \brief The number of leap seconds
            ///
            /// The integer number of leap seconds between GPS\/TAI and UTC
            /// in the epoch when the frame is written:
            /// ULeapS = Int[TAI - UTC].
            //-----------------------------------------------------------------
            ULeapS_type ULeapS;
            //-----------------------------------------------------------------
            /// \brief Local seasonal time
            ///
            /// UTC in seconds [integer multiple of 1800 seconds].
            //-----------------------------------------------------------------
            localTime_type localTime;
            //-----------------------------------------------------------------
            /// \brief Frame length in seconds
            //-----------------------------------------------------------------
            dt_type dt;

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
            /// \brief Dictionary description of data
            ///
            /// \param[out] Desc
            ///     The handle to a dictionary description to which this
            ///     type of object is to be added.
            //-----------------------------------------------------------------
            static void dataDescription( Common::Description& Desc );

            //-----------------------------------------------------------------
            /// \brief Number of bytes required by this object
            ///
            /// \return
            ///     The number of bytes need to read or write this object
            ///     to a stream.
            //-----------------------------------------------------------------
            streamsize_type bytes( ) const;

            //-----------------------------------------------------------------
            /// \brief
            //-----------------------------------------------------------------
            bool compare_nps( const FrameHNPS& RHS ) const;

            //-----------------------------------------------------------------
            //-----------------------------------------------------------------
            void read( istream_type& Stream );

            //-----------------------------------------------------------------
            //-----------------------------------------------------------------
            void write( ostream_type& Stream ) const;
        };

        inline const std::string&
        FrameHNPS::GetName( ) const
        {
            return name;
        }

        inline FrameHNPS::run_type
        FrameHNPS::GetRun( ) const
        {
            return run;
        }

        inline FrameHNPS::frame_type
        FrameHNPS::GetFrame( ) const
        {
            return frame;
        }

        inline const FrameHNPS::GTime_type&
        FrameHNPS::GetGTime( ) const
        {
            return GTime;
        }

        inline FrameHNPS::ULeapS_type
        FrameHNPS::GetULeapS( ) const
        {
            return ULeapS;
        }

        inline FrameHNPS::dt_type
        FrameHNPS::GetDt( ) const
        {
            return dt;
        }

        inline FrameHNPS::localTime_type
        FrameHNPS::GetLocalTime( ) const
        {
            return localTime;
        }

        inline void
        FrameHNPS::SetRun( run_type Run )
        {
            run = Run;
        }

        inline void
        FrameHNPS::SetDt( dt_type Dt )
        {
            dt = Dt;
        }

        inline void
        FrameHNPS::SetGTime( const GTime_type& Value )
        {
            GTime = Value;
        }

        //-------------------------------------------------------------------
        /// Set the number of leap seconds since GPS epoc.
        //-------------------------------------------------------------------
        inline void
        FrameHNPS::SetULeapS( ULeapS_type Value )
        {
            ULeapS = Value;
        }

        inline streamsize_type
        FrameHNPS::bytes( ) const
        {
            return name.Bytes( ) + sizeof( run ) // run;
                + sizeof( frame ) // frame;
                + sizeof( GTimeS_type ) // GTime Seconds;
                + sizeof( GTimeN_type ) // GTime Nanoeconds;
                + sizeof( ULeapS ) // ULeapS;
                + sizeof( localTime ) + sizeof( dt ) // dt;
                ;
        }

        inline void
        FrameHNPS::dataDescription( Common::Description& Desc )
        {
            Desc( FrSE( "name",
                        "STRING",
                        "Name of project or other experiment description" ) );
            Desc( FrSE( "run",
                        "INT_4U",
                        "Run number(number<0 reserved for simulated data);"
                        " monotonic for experimental runs." ) );
            Desc(
                FrSE( "frame",
                      "INT_4U",
                      "Frame number, monotonically increasing until end of run,"
                      " re-starting from 0 with each new run" ) );
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

        inline bool
        FrameHNPS::compare_nps( const FrameHNPS& RHS ) const
        {
            return ( ( this == &RHS ) ||
                     ( ( name == RHS.name ) && ( run == RHS.run ) &&
                       ( frame == RHS.frame ) && ( GTime == RHS.GTime ) &&
                       ( ULeapS == RHS.ULeapS ) &&
                       ( localTime == RHS.localTime ) && ( dt == RHS.dt ) ) );
        }

        inline void
        FrameHNPS::read( istream_type& Stream )
        {
            Stream >> name >> run >> frame >> GTime >> ULeapS >> localTime >>
                dt;
        }

        inline void
        FrameHNPS::write( ostream_type& Stream ) const
        {
            Stream << name << run << frame << GTime << ULeapS << localTime
                   << dt;
        }

        //===================================================================
        //===================================================================
        template < typename TDetector,
                   typename TTrigData,
                   typename THistory,
                   typename TProcData,
                   typename TRawData,
                   typename TSimData,
                   typename TSummary,
                   typename TVect >
        class FrameHPST
        {
        public:
            static const INT_2U MAX_REF = 12;

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

            inline const procData_type&
            RefStrain( ) const
            {
                return m_refs.strain;
            }

            inline procData_type&
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
                procData_type        strain;
                simData_type         simData;
                trigData_type        trigData;
                summaryData_type     summaryData;
                auxData_type         auxData;

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
                    simData = Source.simData;
                    trigData = Source.trigData;
                    summaryData = Source.summaryData;
                    auxData = Source.auxData;
                }

                inline ~ref_type( )
                {
                }

                inline streamsize_type
                Bytes( ) const
                {
                    return ( PTR_STRUCT::Bytes( ) *
                             MAX_REF ); // All the pointer elements
                }

                void
                readSubset( istream_type& Stream, INT_4U ElementMask )
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
                    Stream.RemoveResolver( &( simData ), MAX_REF );
                    Stream.RemoveResolver( &( trigData ), MAX_REF );
                    Stream.RemoveResolver( &( summaryData ), MAX_REF );
                    if ( !( ElementMask & Common::FrameH::AUX_DATA ) )
                    {
                        Stream.RemoveResolver( &( auxData ), MAX_REF );
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
                               ( simData == RHS.simData ) &&
                               ( trigData == RHS.trigData ) &&
                               ( summaryData == RHS.summaryData ) &&
                               ( auxData == RHS.auxData ) ) );
                }

                inline void
                operator( )( istream_type& Stream )
                {
                    Stream >> type >> user >> detectSim >> detectProc >>
                        history >> &rawData >> procData >> strain >> simData >>
                        trigData >> summaryData >> auxData;
                }

                inline void
                operator( )( ostream_type& Stream ) const
                {
                    ostream_type::Pointer raw_data_ptr( rawData );

                    Stream << type << user << detectSim << detectProc << history
                           << raw_data_ptr << procData << strain << simData
                           << trigData << summaryData << auxData;
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
                Desc( FrSE( "summaryData",
                            PTR_STRUCT::Desc( FrSummary::StructName( ) ),
                            "" ) );
                Desc( FrSE( "auxData",
                            PTR_STRUCT::Desc( FrVect::StructName( ) ),
                            "" ) );
            }
        };

        typedef FrameHPST< FrDetector,
                           FrTrigData,
                           FrHistory,
                           FrProcData,
                           FrRawData,
                           FrSimData,
                           FrSummary,
                           FrVect >
            FrameHPS;

        //===================================================================
        /// \brief FrameH Data Structure Definition
        //===================================================================
        class FrameH : public Common::FrameH, public FrameHNPS, public FrameHPS
        {
        public:
            using Common::FrameSpec::Object::Create;

            typedef Common::FrameH::assign_stream_type assign_stream_type;

            //-----------------------------------------------------------------
            /// \brief Default constructor
            //-----------------------------------------------------------------
            FrameH( );
            FrameH( const FrameH& frame );
            FrameH( const std::string& name,
                    run_type           run,
                    frame_type         frame,
                    const GTime_type&  time,
                    ULeapS_type        uLeapS,
                    localTime_type     LocalTime,
                    const dt_type      dt );
            FrameH( const FrameHNPS& Source );
            ~FrameH( );

            static promote_ret_type Promote( frame_spec_version_type Source,
                                             promote_arg_type        Obj,
                                             istream_type*           Stream );

            static const char* StructName( );

            static const Common::Description* StructDescription( );

            /// \brief Number of bytes needed to write this structure
            streamsize_type Bytes( const Common::StreamBase& Stream ) const;

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
            FrameH( istream_type& Stream );

            /// \brief Down grade an object
            virtual demote_ret_type demote( frame_spec_version_type Target,
                                            demote_arg_type         Obj,
                                            istream_type* Stream ) const;

            /// \brief Upgrade an object
            virtual promote_ret_type promote( frame_spec_version_type Target,
                                              promote_arg_type        Obj,
                                              istream_type* Stream ) const;
        };

        inline FrameH::promote_ret_type
        FrameH::Promote( frame_spec_version_type Source,
                         promote_arg_type        Obj,
                         istream_type*           Stream )
        {
            return Common::PromoteObject( DATA_FORMAT_VERSION, Source, Obj );
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
            return ( ( this->compare_nps( RHS ) ) && ( m_refs == RHS.m_refs ) );
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

    } // namespace Version_3
} // namespace FrameCPP

#endif /* defined(__cplusplus) */

#endif /* !defined(SWIGIMPORTED) */

#endif /* FrameCPP_VERSION_3_FrameH_HH */
