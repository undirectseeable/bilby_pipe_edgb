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

#ifndef FrameCPP_VERSION_8_FrTOC_HH
#define FrameCPP_VERSION_8_FrTOC_HH

#include "framecpp/Version8/impl/FrTOCClassicIO.hh"

#if ! defined(SWIGIMPORTED)

namespace FrameCPP
{
    namespace Version_8
    {

        //===================================================================
        /// \brief Table of Contents Data Structure Definition
        //===================================================================
        class FrTOC
#if !defined( SWIG )
          : public FrTOCImpl::ClassicIO< FrTOC >
#endif /* !defined( SWIG ) */
        {
        public:
            typedef INT_8U                       position_type;
            typedef std::vector< position_type > position_list_type;

#if !defined( SWIG )
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
#endif /* ! defined(SWIG) */

#if !defined( SWIG )
            struct StatType_type
            {
                std::vector< INT_4U > tStart;
                std::vector< INT_4U > tEnd;
                std::vector< INT_4U > version;
                position_list_type    positionStat;
            };
#endif /* ! defined(SWIG) */

#if !defined( SWIG )
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
#endif /* ! defined(SWIG) */

            typedef LDASTools::AL::
                unordered_map< StatTypeKey, StatType_type, StatTypeKeyHash >
                    MapStatType_type;

            static const INT_4U NO_DATA_AVAILABLE;

          //-----------------------------------------------------------------
          /// \brief Default constructor
          ///
          /// \return
          ///    A new instance of this object.
          //-----------------------------------------------------------------
          FrTOC( ) = default;

          //-----------------------------------------------------------------
          /// \brief Copy Constructor
          ///
          /// \param[in] Source
          ///     The object from which to copy the information.
          ///
          /// \return
          ///    A new instance of this object.
          //-----------------------------------------------------------------
          FrTOC( const FrTOC& Source ) = default;

            //-----------------------------------------------------------------
            /// \brief Constructor
            ///
            /// \param[in] Source
            ///
            /// \return
            ///    A new instance of this object.
            //-----------------------------------------------------------------
            explicit FrTOC( const FrameCPP::Common::FrTOC* Source );

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

            //-----------------------------------------------------------------
            /// \brief The name structure name of this object.
            ///
            /// \return
            ///     The name of the structure as specified by the frame
            ///     specification.
            //-----------------------------------------------------------------
            static const char* StructName( );

            //-----------------------------------------------------------------
            /// \brief Place information about an object into the TOC
            ///
            /// \param[in] Object
            ///     Object from which to extract information for the TOC.
            /// \param[in] Position
            ///     Stream position where object begins.
            //-----------------------------------------------------------------
            virtual void IndexObject( object_type    Object,
                                      std::streampos Position );

            //-----------------------------------------------------------------
            /// \brief Virtual constructor
            ///
            /// \return
            ///    A new instance of this object.
            //-----------------------------------------------------------------
            virtual FrTOC* Create( ) const;

            //-----------------------------------------------------------------
            /// \brief Retieve FrStatData data
            ///
            /// \param[in] NamePattern
            ///     Regular expression describing the FrStatData name of
            ///     interest.
            /// \param[in] StartTime
            ///     The lower bound GPS time of the FrStatData start time.
            /// \param[in] EndTime
            ///     The upper bound GPS time of the FrStatData end time.
            /// \param[in] Version
            ///     The FrStatData version of interest.
            /// \param[out] Result
            ///     All FrStatData information that matched the query.
            //-----------------------------------------------------------------
            virtual void
            FrStatDataQuery( const std::string&            NamePattern,
                             const LDASTools::AL::GPSTime& StartTime,
                             const LDASTools::AL::GPSTime& EndTime,
                             const INT_4U                  Version,
                             Common::FrStatData::Query&    Result ) const;

            //-----------------------------------------------------------------
            /// \brief The name structure name of this object.
            ///
            /// \return
            ///     The name of the structure as specified by the frame
            ///     specification.
            //-----------------------------------------------------------------
            virtual const char* ObjectStructName( ) const;

            inline FrTOC& operator=(FrTOC&& TOC )
            {
              static_cast<FrTOCDataData&>(*this) = static_cast<FrTOCDataData&&>( TOC );
              return( *this );
            }
            //-----------------------------------------------------------------
            /// \brief equality operator
            ///
            /// \param[in] RHS
            ///     The FrAdcData object to be compared.
            ///
            /// \return
            ///     The value true is returned if this object is equivelent
            ///     to the RHS instance; false otherwise.
            //-----------------------------------------------------------------
            virtual bool
            operator==( const Common::FrameSpec::Object& RHS ) const;

            const MapStatType_type& GetStatType( ) const;

        protected:
        protected:
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
            positionEvent( INT_4U FrameIndex, const std::string& Event ) const;

            virtual cmn_position_type positionEvent( const std::string& Event,
                                                     INT_4U Index ) const;

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
                              const std::string& SimEvent ) const;
            virtual cmn_position_type
            positionSimEvent( const std::string& EventType,
                              INT_4U             Index ) const;

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
            virtual void
            seekAdcDataPositions( istream_type&                  Stream,
                                  Common::FrTOC::channel_id_type Channel );

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
            //-----------------------------------------------------------------
            /// \brief Object with checksum data.
            //-----------------------------------------------------------------
            typedef ObjectWithChecksum< Common::FrTOC > toc_base_type;

            using Common::FrameSpec::Object::Create;

            MapStatType_type m_StatType;

            template < typename ChannelType >
            cmn_position_type position_adc( INT_4U      FrameIndex,
                                            ChannelType Channel ) const;

            template < typename ChannelType >
            cmn_position_type position_proc( INT_4U      FrameIndex,
                                             ChannelType Channel ) const;

            const FrTOC& operator=( const FrTOC& Source );
            const FrTOC& operator=( const Previous::FrTOC& Source );
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

    } // namespace Version_8
} // namespace FrameCPP

#endif /* ! defined(SWIGIMPORTED) */

#endif /* FrameCPP_VERSION_8_FrTOC_HH */
