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

#ifndef FrameCPP_VERSION_4_FrTOCData_HH
#define FrameCPP_VERSION_4_FrTOCData_HH

#include "framecpp/Version4/FrTOCTypes.hh"
#include "framecpp/Version4/STRING.hh"

namespace FrameCPP
{
    namespace Version_4
    {
        //===================================================================
        //===================================================================
        class FrTOCData : public FrTOCTypes
        {
        public:
            typedef INT_2S uleaps_type;
            typedef INT_4S localTime_type;
            typedef INT_4U nframe_type;
            typedef INT_4U gtimen_type;
            typedef INT_4U gtimes_type;
            typedef REAL_8 dt_type;
            typedef INT_4S runs_type;
            typedef INT_4U frame_type;
            typedef INT_4U nsh_type;
            typedef INT_2U shid_type;
            typedef STRING shname_type;

            typedef std::vector< gtimen_type > gtimen_container_type;
            typedef std::vector< gtimes_type > gtimes_container_type;
            //-----------------------------------------------------------------
            /// \brief Array of FrDetector names.
            //-----------------------------------------------------------------
            typedef std::vector< dt_type >       dt_container_type;
            typedef std::vector< runs_type >     runs_container_type;
            typedef std::vector< frame_type >    frame_container_type;
            typedef std::vector< position_type > positionH_container_type;
            typedef std::vector< position_type > nFirstADC_container_type;
            typedef std::vector< position_type > nFirstSer_container_type;
            typedef std::vector< position_type > nFirstTable_container_type;
            typedef std::vector< position_type > nFirstMsg_container_type;
            typedef std::vector< shid_type >     shid_container_type;
            typedef std::vector< shname_type >   shname_container_type;

            FrTOCData( );

            Common::FrameSpec::size_type
            Bytes( const Common::StreamBase& Stream ) const;

            localTime_type                    GetLocalTime( ) const;
            const dt_container_type&          GetDt( ) const;
            const frame_container_type&       GetFrame( ) const;
            const gtimes_container_type&      GetGTimeN( ) const;
            const gtimen_container_type&      GetGTimeS( ) const;
            nframe_type                       GetNFrame( ) const;
            const nFirstADC_container_type&   GetNFirstADC( ) const;
            const nFirstSer_container_type&   GetNFirstSer( ) const;
            const nFirstTable_container_type& GetNFirstTable( ) const;
            const nFirstMsg_container_type&   GetNFirstMsg( ) const;
            const positionH_container_type&   GetPositionH( ) const;
            const runs_container_type&        GetRuns( ) const;
            const shid_container_type&        GetSHid( ) const;
            const shname_container_type&      GetSHname( ) const;
            uleaps_type                       GetULeapS( ) const;

            bool operator==( const FrTOCData& RHS ) const;

            static void Description( Common::Description& Desc );

        protected:
            uleaps_type                m_ULeapS;
            localTime_type             m_localTime;
            gtimes_container_type      m_GTimeS;
            gtimen_container_type      m_GTimeN;
            dt_container_type          m_dt;
            runs_container_type        m_runs;
            frame_container_type       m_frame;
            positionH_container_type   m_positionH;
            nFirstADC_container_type   m_nFirstADC;
            nFirstSer_container_type   m_nFirstSer;
            nFirstTable_container_type m_nFirstTable;
            nFirstMsg_container_type   m_nFirstMsg;
            shid_container_type        m_SHid;
            shname_container_type      m_SHname;

            FrTOCData( Common::IStream& Stream );

            void load( Common::IStream& Stream );

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
            retval += sizeof( m_ULeapS ) + sizeof( m_localTime ) +
                sizeof( nframe_type ) +
                ( m_frame.size( ) *
                  ( sizeof( gtimes_type ) + sizeof( gtimen_type ) +
                    sizeof( dt_type ) + sizeof( runs_type ) +
                    sizeof( frame_type ) +
                    sizeof( position_type ) // m_positionH
                    + sizeof( position_type ) // m_nFirstADC
                    + sizeof( position_type ) // m_nFirstSer
                    + sizeof( position_type ) // m_nFirstTable
                    + sizeof( position_type ) // m_nFirstMsg
                    ) );
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
            // Return the results
            //-----------------------------------------------------------------
            return retval;
        }

        inline FrTOCData::localTime_type
        FrTOCData::GetLocalTime( ) const
        {
            return m_localTime;
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
            return m_frame.size( );
        }

        inline const FrTOCData::nFirstADC_container_type&
        FrTOCData::GetNFirstADC( ) const
        {
            return m_nFirstADC;
        }

        inline const FrTOCData::nFirstSer_container_type&
        FrTOCData::GetNFirstSer( ) const
        {
            return m_nFirstSer;
        }

        inline const FrTOCData::nFirstTable_container_type&
        FrTOCData::GetNFirstTable( ) const
        {
            return m_nFirstTable;
        }

        inline const FrTOCData::nFirstMsg_container_type&
        FrTOCData::GetNFirstMsg( ) const
        {
            return m_nFirstMsg;
        }

        inline const FrTOCData::positionH_container_type&
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

        inline FrTOCData::uleaps_type
        FrTOCData::GetULeapS( ) const
        {
            return m_ULeapS;
        }

        inline bool
        FrTOCData::operator==( const FrTOCData& RHS ) const
        {
            return ( ( &RHS == this ) ||
                     ( ( m_ULeapS == RHS.m_ULeapS ) &&
                       ( m_localTime == RHS.m_localTime ) &&
                       ( m_GTimeS == RHS.m_GTimeS ) &&
                       ( m_GTimeN == RHS.m_GTimeN ) && ( m_dt == RHS.m_dt ) &&
                       ( m_runs == RHS.m_runs ) && ( m_frame == RHS.m_frame ) &&
                       ( m_positionH == RHS.m_positionH ) &&
                       ( m_SHid == RHS.m_SHid ) &&
                       ( m_SHname == RHS.m_SHname ) ) );
        }

    } // namespace Version_4
} // namespace FrameCPP

#endif /* FrameCPP_VERSION_4_FrTOCData_HH */
