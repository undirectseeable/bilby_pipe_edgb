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

#ifndef FrameCPP_VERSION_6_FrTOCSimData_HH
#define FrameCPP_VERSION_6_FrTOCSimData_HH

#include "framecpp/Version6/STRING.hh"

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
        class FrTOCSimData
        {
        public:
            typedef INT_4U nsim_type;
            typedef STRING name_type;
            typedef INT_8U position_type;

            typedef std::vector< position_type >         sim_info_type;
            typedef std::map< name_type, sim_info_type > MapSim_type;

            FrTOCSimData( );

            Common::FrameSpec::size_type
            Bytes( const Common::StreamBase& Stream ) const;

            const MapSim_type& GetSim( ) const;

            MapSim_type::const_iterator GetSim( const std::string& Name ) const;

            MapSim_type::const_iterator GetSim( INT_4U index ) const;

            void QuerySim( const Common::TOCInfo& Info,
                           INT_4U                 FrameOffset,
                           INT_8U                 Position );

            bool operator==( const FrTOCSimData& RHS ) const;

            template < typename SE >
            static void Description( Common::Description& Desc );

        protected:
            typedef std::vector< name_type > key_container_type;
            key_container_type               m_keys;
            MapSim_type                      m_info;

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

            FrTOCSimData( Common::IStream& Stream, INT_4U FrameCount );
            void write( Common::OStream& Stream ) const;
        };

        inline Common::FrameSpec::size_type
        FrTOCSimData::Bytes( const Common::StreamBase& Stream ) const
        {
            Common::FrameSpec::size_type retval = sizeof( nsim_type );
            if ( m_info.size( ) )
            {
                retval += ( m_info.size( ) *
                            ( sizeof( position_type ) *
                              m_info.begin( )->second.size( ) ) );
            }
            for ( MapSim_type::const_iterator cur = m_info.begin( ),
                                              last = m_info.end( );
                  cur != last;
                  ++cur )
            {
                retval += cur->first.Bytes( );
            }
            return retval;
        }

        template < typename SE >
        void
        FrTOCSimData::Description( Common::Description& Desc )
        {
            Desc( SE( "nSim",
                      "INT_4U",
                      "Number of unique FrAdcData names in file." ) );
            Desc( SE( "nameSim", "*STRING", "Array of FrAdcData names" ) );
            Desc( SE( "positionSim",
                      "*INT_8U",
                      "Array of lists of FrSimData offset positions, in bytes,"
                      " from beginning of file (size of nFrame*nSim)" ) );
        }

        inline const FrTOCSimData::MapSim_type&
        FrTOCSimData::GetSim( ) const
        {
            return m_info;
        }

    } // namespace Version_6
} // namespace FrameCPP

#endif /* FrameCPP_VERSION_6_FrTOCSimData_HH */
