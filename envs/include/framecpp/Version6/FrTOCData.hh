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

#ifndef FrameCPP_VERSION_6_FrTOCData_HH
#define FrameCPP_VERSION_6_FrTOCData_HH

#if !defined( SWIGIMPORTED )
#include "framecpp/Version6/STRING.hh"
#endif /* ! defined(SWIGIMPORTED) */

#if !defined( SWIGIMPORTED )
namespace FrameCPP
{
    namespace Common
    {
        class TOCInfo;
    }

    namespace Version_6
    {
        //===================================================================
        //===================================================================
        class FrTOCData
        {
        public:
            typedef INT_4U data_quality_type;
            typedef REAL_8 dt_type;
            typedef INT_4U frame_type;
            typedef INT_4U gtimen_type;
            typedef INT_4U gtimes_type;
            typedef STRING namedetector_type;
            typedef INT_4U ndetector_type;
            typedef INT_8U nfirstadc_type;
            typedef INT_8U nfirstmsg_type;
            typedef INT_8U nfirstser_type;
            typedef INT_8U nfirsttable_type;
            typedef INT_4U nframe_type;
            typedef INT_4U nsh_type;
            typedef INT_8U positiondetector_type;
            typedef INT_8U positionh_type;
            typedef INT_4S runs_type;
            typedef INT_2U shid_type;
            typedef STRING shname_type;
            typedef INT_2S uleaps_type;

            typedef std::vector< data_quality_type >
                                               data_quality_container_type;
            typedef std::vector< dt_type >     dt_container_type;
            typedef std::vector< frame_type >  frame_container_type;
            typedef std::vector< gtimen_type > gtimen_container_type;
            typedef std::vector< gtimes_type > gtimes_container_type;
            typedef std::vector< namedetector_type >
                                                    namedetector_container_type;
            typedef std::vector< nfirstadc_type >   nfirstadc_container_type;
            typedef std::vector< nfirstmsg_type >   nfirstmsg_container_type;
            typedef std::vector< nfirstser_type >   nfirstser_container_type;
            typedef std::vector< nfirsttable_type > nfirsttable_container_type;
            typedef std::vector< positiondetector_type >
                                                  positiondetector_container_type;
            typedef std::vector< positionh_type > positionh_container_type;
            typedef std::vector< runs_type >      runs_container_type;
            typedef std::vector< shid_type >      shid_container_type;
            typedef std::vector< shname_type >    shname_container_type;

            FrTOCData( );

            Common::FrameSpec::size_type
            Bytes( const Common::StreamBase& Stream ) const;

            const data_quality_container_type& GetDataQuality( ) const;
            const dt_container_type&           GetDt( ) const;
            const frame_container_type&        GetFrame( ) const;
            const gtimes_container_type&       GetGTimeN( ) const;
            const gtimen_container_type&       GetGTimeS( ) const;
            const nfirstadc_container_type&    GetNFirstADC( ) const;
            const nfirstmsg_container_type&    GetNFirstMsg( ) const;
            const nfirstser_container_type&    GetNFirstSer( ) const;
            const nfirsttable_container_type&  GetNFirstTable( ) const;
            nframe_type                        GetNFrame( ) const;
            const positionh_container_type&    GetPositionH( ) const;
            const runs_container_type&         GetRuns( ) const;
            const shid_container_type&         GetSHid( ) const;
            const shname_container_type&       GetSHname( ) const;
            uleaps_type                        GetULeapS( ) const;

            const namedetector_container_type&     GetNameDetector( ) const;
            const positiondetector_container_type& GetPositionDetector( ) const;

            bool operator==( const FrTOCData& RHS ) const;

            template < typename SE >
            static void Description( Common::Description& Desc );

        protected:
            uleaps_type                     m_ULeapS;
            data_quality_container_type     m_dataQuality;
            gtimes_container_type           m_GTimeS;
            gtimen_container_type           m_GTimeN;
            dt_container_type               m_dt;
            runs_container_type             m_runs;
            frame_container_type            m_frame;
            positiondetector_container_type m_positionDetector;
            positionh_container_type        m_positionH;
            namedetector_container_type     m_nameDetector;
            nfirstadc_container_type        m_nFirstADC;
            nfirstser_container_type        m_nFirstSer;
            nfirsttable_container_type      m_nFirstTable;
            nfirstmsg_container_type        m_nFirstMsg;
            shid_container_type             m_SHid;
            shname_container_type           m_SHname;

            //-----------------------------------------------------------------
            /// \brief Iterate over contents.
            ///
            /// \param[in] Info
            ///     Specifies the type of information to be searched.
            ///
            /// \param[in] Action
            ///     Action to be taken for each piece of information found.
            //-----------------------------------------------------------------
            void forEach( Common::FrTOC::query_info_type Info,
                          Common::FrTOC::FunctionBase&   Action ) const;

            FrTOCData( Common::IStream& Stream );
            void load( Common::IStream& Stream );
            void write( Common::OStream& Stream ) const;
        };

        inline FrTOCData::FrTOCData( ) : m_ULeapS( 0 )
        {
        }

        inline Common::FrameSpec::size_type
        FrTOCData::Bytes( const Common::StreamBase& Stream ) const
        {
            Common::FrameSpec::size_type retval = 0;

            //-----------------------------------------------------------------
            // main header block
            //-----------------------------------------------------------------
            retval += sizeof( m_ULeapS ) + sizeof( nframe_type ) +
                ( m_dataQuality.size( ) *
                  ( sizeof( data_quality_type ) + sizeof( gtimes_type ) +
                    sizeof( gtimen_type ) + sizeof( dt_type ) +
                    sizeof( runs_type ) + sizeof( frame_type ) +
                    sizeof( positionh_type ) + sizeof( nfirstadc_type ) +
                    sizeof( nfirstmsg_type ) + sizeof( nfirstser_type ) +
                    sizeof( nfirsttable_type ) ) );
            //-----------------------------------------------------------------
            // SH elements
            //-----------------------------------------------------------------
            retval +=
                sizeof( nsh_type ) + ( sizeof( shid_type ) * m_SHid.size( ) );
            for ( shname_container_type::const_iterator cur = m_SHname.begin( ),
                                                        last = m_SHname.end( );
                  cur != last;
                  ++cur )
            {
                retval += cur->Bytes( );
            }
            //-----------------------------------------------------------------
            // Detector information
            //-----------------------------------------------------------------
            retval += sizeof( ndetector_type ) +
                ( sizeof( positiondetector_type ) *
                  m_positionDetector.size( ) );
            for ( namedetector_container_type::const_iterator
                      cur = m_nameDetector.begin( ),
                      last = m_nameDetector.end( );
                  cur != last;
                  ++cur )
            {
                retval += cur->Bytes( );
            }
            //-----------------------------------------------------------------
            // Return the results
            //-----------------------------------------------------------------
            return retval;
        }

        template < typename SE >
        void
        FrTOCData::Description( Common::Description& Desc )
        {
            Desc(
                SE( "ULeapS", "INT_2S", "From the first FrameH in the file" ) );
            //-----------------------------------------------------------------
            Desc( SE( "nFrame", "INT_4U", "Number of frames in the file" ) );
            Desc( SE( "dataQuality",
                      "*INT_4U",
                      "Array of integer QA words from each FrameH"
                      " (size of nFrames)" ) );
            Desc( SE( "GTimeS",
                      "*INT_4U",
                      "Array of integer GPS frae times (size of nFrames" ) );
            Desc( SE( "GTimeN",
                      "*INT_4U",
                      "Array of integer GPS residual nanoseconds for the frame"
                      " (size of nFrame" ) );
            Desc(
                SE( "dt",
                    "*REAL_8",
                    "Array of frame durations in seconds( size of nFrames)" ) );
            Desc( SE(
                "runs", "*INT_4S", "Array of run numbers (size of nFrame)" ) );
            Desc( SE( "frame",
                      "*INT_4U",
                      "Array of frame numbers (size of nFrame)" ) );
            Desc( SE( "positionH",
                      "*INT_8U",
                      "Array of FrameH positions, in bytes, from the"
                      " bginning of file (size of nFrame)" ) );
            Desc( SE( "nFirstADC",
                      "*INT_8U",
                      "Array of first FrADCData positions, in bytes,"
                      " from beginning of file (size of nFrame)" ) );
            Desc( SE( "nFirstSer",
                      "*INT_8U",
                      "Array of first FrSerData positions in bytes,"
                      " from beginning of file (size of nFrame)" ) );
            Desc( SE( "nFirstTable",
                      "*INT_8U",
                      "Array of first FrTable positions, in bytes,"
                      " from beginning of file (size of nFrame)" ) );
            Desc( SE( "nFirstMsg",
                      "*INT_8U",
                      "Array of first FrMsg positions, in bytes,"
                      " from beginning of file (size of nFrame)" ) );
            //-----------------------------------------------------------------
            Desc( SE(
                "nSH", "INT_4U", "Number of FrSH structures in the file" ) );
            Desc( SE( "SHid", "*INT_2U", "Array of FrSH IDs (size of nSH)" ) );
            Desc( SE(
                "SHname", "*STRING", "Array of FrSH names (size of nSH)" ) );
            //-----------------------------------------------------------------
            Desc( SE( "nDetector",
                      "INT_4U",
                      "Number of distinct types of FrDetector in the file" ) );
            Desc( SE( "nameDetector",
                      "*STRING",
                      "Array of FrDetector names (size of nDetector)."
                      " They appear alphabetically" ) );
            Desc( SE( "positionDetector",
                      "*INT_8U",
                      "Array of FrDetector positions from the beginning"
                      " of file (size of nDetector)." ) );
        }

        inline const FrTOCData::data_quality_container_type&
        FrTOCData::GetDataQuality( ) const
        {
            return m_dataQuality;
        }

        inline const FrTOCData::dt_container_type&
        FrTOCData::GetDt( ) const
        {
            return m_dt;
        }

        inline const FrTOCData::frame_container_type&
        FrTOCData::GetFrame( ) const
        {
            return m_frame;
        }

        inline const FrTOCData::gtimen_container_type&
        FrTOCData::GetGTimeN( ) const
        {
            return m_GTimeN;
        }

        inline const FrTOCData::gtimes_container_type&
        FrTOCData::GetGTimeS( ) const
        {
            return m_GTimeS;
        }

        inline FrTOCData::nframe_type
        FrTOCData::GetNFrame( ) const
        {
            return m_dataQuality.size( );
        }

        inline const FrTOCData::nfirstadc_container_type&
        FrTOCData::GetNFirstADC( ) const
        {
            return m_nFirstADC;
        }

        inline const FrTOCData::nfirstmsg_container_type&
        FrTOCData::GetNFirstMsg( ) const
        {
            return m_nFirstMsg;
        }

        inline const FrTOCData::nfirstser_container_type&
        FrTOCData::GetNFirstSer( ) const
        {
            return m_nFirstSer;
        }

        inline const FrTOCData::nfirsttable_container_type&
        FrTOCData::GetNFirstTable( ) const
        {
            return m_nFirstTable;
        }

        inline const FrTOCData::positionh_container_type&
        FrTOCData::GetPositionH( ) const
        {
            return m_positionH;
        }

        inline const FrTOCData::runs_container_type&
        FrTOCData::GetRuns( ) const
        {
            return m_runs;
        }

        inline const FrTOCData::shid_container_type&
        FrTOCData::GetSHid( ) const
        {
            return m_SHid;
        }

        inline const FrTOCData::shname_container_type&
        FrTOCData::GetSHname( ) const
        {
            return m_SHname;
        }

        inline const FrTOCData::namedetector_container_type&
        FrTOCData::GetNameDetector( ) const
        {
            return m_nameDetector;
        }

        inline const FrTOCData::positiondetector_container_type&
        FrTOCData::GetPositionDetector( ) const
        {
            return m_positionDetector;
        }

        inline FrTOCData::uleaps_type
        FrTOCData::GetULeapS( ) const
        {
            return m_ULeapS;
        }

        inline bool
        FrTOCData::operator==( const FrTOCData& RHS ) const
        {
#define CMP__( X ) ( X == RHS.X )

            return ( ( &RHS == this ) ||
                     ( CMP__( m_ULeapS ) && CMP__( m_dataQuality ) &&
                       CMP__( m_GTimeS ) && CMP__( m_GTimeN ) &&
                       CMP__( m_dt ) && CMP__( m_runs ) && CMP__( m_frame ) &&
                       CMP__( m_positionH ) && CMP__( m_nFirstADC ) &&
                       CMP__( m_nFirstSer ) && CMP__( m_nFirstTable ) &&
                       CMP__( m_nFirstMsg ) && CMP__( m_SHid ) &&
                       CMP__( m_SHname ) && CMP__( m_nameDetector ) &&
                       CMP__( m_positionDetector ) ) );
#undef CMP__
        }

    } // namespace Version_6
} // namespace FrameCPP

#endif /* ! defined(SWIGIMPORTED) */

#endif /* FrameCPP_VERSION_6_FrTOCData_HH */
