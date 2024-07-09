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

#ifndef FrameCPP_VERSION_4_FrTOC_HH
#define FrameCPP_VERSION_4_FrTOC_HH

#include <map>
#include <vector>

#include "framecpp/Common/FrameSpec.hh"
#include "framecpp/Common/FrTOC.hh"

#include "framecpp/Version4/FrameSpec.hh"
#include "framecpp/Version4/FrTOCData.hh"
#include "framecpp/Version4/FrTOCAdcData.hh"
#include "framecpp/Version4/FrTOCProcData.hh"
#include "framecpp/Version4/FrTOCSerData.hh"
#include "framecpp/Version4/FrTOCSimData.hh"
#include "framecpp/Version4/FrTOCSimEvent.hh"
#include "framecpp/Version4/FrTOCStatData.hh"
#include "framecpp/Version4/FrTOCSummary.hh"
#include "framecpp/Version4/FrTOCTrigData.hh"
#include "framecpp/Version4/STRING.hh"

namespace FrameCPP
{
    namespace Version_4
    {

        //===================================================================
        //===================================================================
        class FrTOC : public Common::FrTOC,
                      public FrTOCData,
                      public FrTOCStatData,
                      public FrTOCAdcData,
                      public FrTOCProcData,
                      public FrTOCSimData,
                      public FrTOCSerData,
                      public FrTOCSummary,
                      public FrTOCTrigData,
                      public FrTOCSimEvent
        {
        public:
            typedef INT_8U                       position_type;
            typedef std::vector< position_type > position_list_type;

            class StatTypeKey
            {
            public:
                std::string s_name;
                std::string s_detector;

                StatTypeKey( const std::string& Name,
                             const std::string& Detector );
                bool operator<( const StatTypeKey& RHS ) const;
                bool operator==( const StatTypeKey& RHS ) const;
                bool operator!=( const StatTypeKey& RHS ) const;
            };

            struct StatType_type
            {
                std::vector< INT_4U > tStart;
                std::vector< INT_4U > tEnd;
                std::vector< INT_4U > version;
                position_list_type    positionStat;
            };

            class StatTypeKeyHash
            {
            public:
                size_t
                operator( )( const StatTypeKey& Key ) const
                {
                    LDASTools::AL::hash< const char* > h;

                    std::string key( Key.s_name );
                    key += Key.s_detector;
                    return h( key.c_str( ) );
                }
            };

            typedef LDASTools::AL::
                unordered_map< StatTypeKey, StatType_type, StatTypeKeyHash >
                    MapStatType_type;

            static const INT_4U NO_DATA_AVAILABLE;

            FrTOC( );

            //-----------------------------------------------------------------
            /// \brief Iterate over elements of the Table of Contents
            ///
            /// \param[in] Info
            ///     Type of objects upon which to iterate.
            /// \param[in,out] Action
            ///     Action to be performed.
            ///
            //-----------------------------------------------------------------
            virtual void ForEach( query_info_type Info,
                                  FunctionBase&   Action ) const;

            static const char* StructName( );

            static const Common::Description* StructDescription( );

            virtual void IndexObject( object_type    Object,
                                      std::streampos Position );

            virtual Common::FrameSpec::size_type
            Bytes( const Common::StreamBase& Stream ) const;

            virtual FrTOC* Create( ) const;

            virtual FrTOC* Create( istream_type& Stream ) const;

            virtual void
            FrStatDataQuery( const std::string&            NamePattern,
                             const LDASTools::AL::GPSTime& StartTime,
                             const LDASTools::AL::GPSTime& EndTime,
                             const INT_4U                  Version,
                             Common::FrStatData::Query&    Result ) const;

            virtual const char* ObjectStructName( ) const;

            virtual void Write( ostream_type& Stream ) const;

            /// \brief comparison operator
            virtual bool
            operator==( const Common::FrameSpec::Object& Obj ) const;

            const MapStatType_type& GetStatType( ) const;

        protected:
            /// \brief Down grade an object
            virtual demote_ret_type demote( INT_2U          Target,
                                            demote_arg_type Obj,
                                            istream_type*   Stream ) const;

            /// \brief Upgrade an object
            virtual promote_ret_type promote( INT_2U           Target,
                                              promote_arg_type Obj,
                                              istream_type*    Stream ) const;

        protected:
            //-----------------------------------------------------------------
            // Interface routines
            //-----------------------------------------------------------------
            virtual INT_4U nFrame( ) const;

            virtual const cmn_dt_container_type&     dt( ) const;
            virtual const cmn_GTimeS_container_type& GTimeS( ) const;
            virtual const cmn_GTimeN_container_type& GTimeN( ) const;
            virtual cmn_runs_container_type const&   runs( ) const;

            virtual cmn_position_type
            positionDetector( const std::string& Name ) const;

            virtual cmn_position_type positionH( INT_4U FrameIndex ) const;

            virtual const cmn_name_container_type& nameADC( ) const;

            virtual cmn_position_type
                                      positionADC( INT_4U FrameIndex, const std::string& Channel ) const;
            virtual cmn_position_type positionADC( INT_4U FrameIndex,
                                                   INT_4U Channel ) const;

            virtual cmn_position_type
            positionEvent( INT_4U             FrameIndex,
                           const std::string& Channel ) const;

            virtual cmn_position_type
            positionEvent( const std::string& EventType, INT_4U Index ) const;

            virtual const cmn_name_container_type& nameProc( ) const;

            virtual cmn_position_type
                                      positionProc( INT_4U FrameIndex, const std::string& Channel ) const;
            virtual cmn_position_type positionProc( INT_4U FrameIndex,
                                                    INT_4U Channel ) const;

            virtual const cmn_name_container_type& nameSer( ) const;

            virtual cmn_position_type
            positionSer( INT_4U FrameIndex, const std::string& Channel ) const;

            virtual const cmn_name_container_type& nameSim( ) const;

            virtual cmn_position_type
            positionSim( INT_4U FrameIndex, const std::string& Channel ) const;

            virtual cmn_position_type
            positionSimEvent( INT_4U             FrameIndex,
                              const std::string& Channel ) const;
            virtual cmn_position_type
            positionSimEvent( const std::string& EventType,
                              INT_4U             Index ) const;

            //-----------------------------------------------------------------
            // Misc functions
            //-----------------------------------------------------------------
            //-----------------------------------------------------------------
            /// \brief Cache where the positions of the Adc channels
            ///
            /// \param[in,out] Stream
            ///     The Stream being read
            //-----------------------------------------------------------------
            virtual void cacheAdcDataPositions( istream_type& Stream );

            //-----------------------------------------------------------------
            /// \brief Advance to the specified Adc channel
            ///
            /// \param[in,out] Stream
            ///     The Stream being read
            /// \param[in] Channel
            ///     The requested channel
            //-----------------------------------------------------------------
            virtual void seekAdcDataPositions( istream_type&   Stream,
                                               channel_id_type Channel );

            //-----------------------------------------------------------------
            /// \brief Advance to the specified Adc channel
            ///
            /// \param[in,out] Stream
            ///     The Stream being read
            /// \param[in] Channel
            ///     The requested channel
            //-----------------------------------------------------------------
            virtual void seekAdcDataPositions( istream_type&      Stream,
                                               const std::string& Channel );

            //-----------------------------------------------------------------
            /// \brief Cache where the positions of the FrProcData channels
            ///
            /// \param[in,out] Stream
            ///     The Stream being read
            //-----------------------------------------------------------------
            virtual void procDataCachePositions( istream_type& Stream );

            virtual INT_4U             nSH( ) const;
            virtual INT_2U             SHid( INT_4U Offset ) const;
            virtual const std::string& SHname( INT_4U Offset ) const;

            virtual void loadHeader( Common::IStream& Stream );

        private:
            using Common::FrameSpec::Object::Create;

            MapStatType_type m_StatType;

            FrTOC( istream_type& Stream );

            template < typename ChannelType >
            cmn_position_type position_adc( INT_4U      FrameIndex,
                                            ChannelType Channel ) const;

            template < typename ChannelType >
            cmn_position_type position_proc( INT_4U      FrameIndex,
                                             ChannelType Channel ) const;
        };

        inline FrTOC::StatTypeKey::StatTypeKey( const std::string& Name,
                                                const std::string& Detector )
            : s_name( Name ), s_detector( Detector )
        {
        }

        inline bool
        FrTOC::StatTypeKey::operator<( const StatTypeKey& RHS ) const
        {
            if ( s_name.compare( RHS.s_name ) == 0 )
            {
                return s_detector < RHS.s_detector;
            }
            return s_name < RHS.s_name;
        }

        inline bool
        FrTOC::StatTypeKey::operator==( const StatTypeKey& RHS ) const
        {
            return ( ( s_name == RHS.s_name ) &&
                     ( s_detector == RHS.s_detector ) );
        }

        inline bool
        FrTOC::StatTypeKey::operator!=( const StatTypeKey& RHS ) const
        {
            return ( !( *this == RHS ) );
        }

        inline const char*
        FrTOC::StructName( )
        {
            static const CHAR* class_name( "FrTOC" );
            return class_name;
        }

        inline const FrTOC::MapStatType_type&
        FrTOC::GetStatType( ) const
        {
            return m_StatType;
        }
    } // namespace Version_4
} // namespace FrameCPP

#endif /* FrameCPP_VERSION_4_FrTOC_HH */
