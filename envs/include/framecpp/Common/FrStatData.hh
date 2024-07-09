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

#ifndef FrameCPP__COMMON__FR_STAT_DATA_HH
#define FrameCPP__COMMON__FR_STAT_DATA_HH

#if !defined( SWIGIMPORTED )
#include <list>

#include <boost/shared_ptr.hpp>
#endif /* ! defined(SWIGIMPORTED) */

#include "ldastoolsal/gpstime.hh"

#include "framecpp/Common/FrameSpec.hh"

namespace FrameCPP
{
    namespace Common
    {
        class FrDetector;

        class FrStatData : public FrameSpec::Object
        {
        public:
            class Query
            {
            public:
                typedef boost::shared_ptr< FrDetector > fr_detector_type;
                typedef boost::shared_ptr< FrStatData > fr_stat_data_type;

                typedef Common::IFrameStream stream_type;

                static const INT_4U ALL_VERSIONS = 0xFFFFFFFF;
                static const INT_4U LATEST_VERSION = 0xFFFFFFFE;

                ~Query( );
                void Add( const std::string&            NamePattern,
                          const LDASTools::AL::GPSTime& StartTime,
                          const LDASTools::AL::GPSTime& EndTime,
                          const INT_4U                  Version );

                void Add( const INT_4U       QueryStartTime,
                          const INT_4U       QueryEndTime,
                          const INT_4U       QueryVersion,
                          const std::string& Name,
                          const INT_4U       Start,
                          const INT_4U       End,
                          const INT_4U       Version,
                          const INT_8U       Position,
                          const std::string& Detector );

                void Reset( stream_type& Stream );

                static void Range( const LDASTools::AL::GPSTime& StartTime,
                                   const LDASTools::AL::GPSTime& EndTime,
                                   INT_4U&                       Start,
                                   INT_4U&                       End );

                INT_4U size( ) const;

                fr_stat_data_type operator[]( INT_4U Index );

            private:
                struct query_info_type
                {
                    fr_stat_data_type s_fr_stat_data;
                    INT_8U            s_fr_stat_pos;
                    // Information needed when looking for the latest version
                    std::string s_nameStat;
                    std::string s_detector;
                    INT_4U      s_tStart;
                    INT_4U      s_tEnd;
                    INT_4U      s_version;
                };

                typedef std::vector< query_info_type > data_type;

                class CompareFilePosition
                {
                public:
                    int operator( )( const query_info_type& LHS,
                                     const query_info_type& RHS ) const;
                };

                std::list< fr_detector_type > m_detectors;
                bool                          m_dirty;
                data_type                     m_fr_stat_data;
                stream_type*                  m_stream;

                void load( );

                std::unique_ptr< FrStatData >
                read_fr_stat_data( stream_type&       Stream,
                                   const std::string& Detector,
                                   INT_8U             PositionOfStatData );
            };

            typedef Query::fr_detector_type fr_detector_type;

            static const FrameSpec::Info::frame_object_types STRUCT_ID =
                FrameSpec::Info::FSI_FR_STAT_DATA;

            FrStatData( const Description* Desc );

            virtual ~FrStatData( );

            virtual fr_detector_type GetDetector( ) const = 0;
        };

        //===================================================================
        //===================================================================
        inline int
        FrStatData::Query::CompareFilePosition::
        operator( )( const query_info_type& LHS,
                     const query_info_type& RHS ) const
        {
            return LHS.s_fr_stat_pos < RHS.s_fr_stat_pos;
        }

        inline void
        FrStatData::Query::Range( const LDASTools::AL::GPSTime& StartTime,
                                  const LDASTools::AL::GPSTime& EndTime,
                                  INT_4U&                       Start,
                                  INT_4U&                       End )
        {
            // Round down
            Start = StartTime.GetSeconds( );
            // Round up
            End = ( ( EndTime.GetNanoseconds( ) > 0 )
                        ? ( EndTime.GetSeconds( ) + 1 )
                        : ( EndTime.GetSeconds( ) ) );
        }

        inline INT_4U
        FrStatData::Query::size( ) const
        {
            return m_fr_stat_data.size( );
        }

        //===================================================================
        //===================================================================
        inline FrStatData::FrStatData( const Description* Desc )
            : FrameSpec::Object( STRUCT_ID, Desc )
        {
        }

        inline FrStatData::~FrStatData( )
        {
        }

    } // namespace Common
} // namespace FrameCPP

#endif /* FrameCPP__COMMON__FR_STAT_DATA_HH */
