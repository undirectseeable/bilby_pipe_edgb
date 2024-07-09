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

#ifndef FrameCPP_VERSION_6_FrTOCProcData_HH
#define FrameCPP_VERSION_6_FrTOCProcData_HH

#include "framecpp/Version6/FrameSpec.hh"
#include "framecpp/Version6/STRING.hh"
#include "framecpp/Version6/FrTOCTypes.hh"

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
        class FrTOCProcData
            : public Common::FrTOC::
                  PositionWithCache< STRING, FrTOCTypes::position_type >
        {
        public:
            typedef Common::FrTOC::
                PositionWithCache< STRING, FrTOCTypes::position_type >
                                              base_type;
            typedef FrTOCTypes::n_type        nproc_type;
            typedef FrTOCTypes::position_type position_type;

            typedef FrTOCTypes::position_container_type         proc_info_type;
            typedef FrTOCTypes::ordered_position_container_type MapProc_type;

            FrTOCProcData( );

            Common::FrameSpec::size_type
            Bytes( const Common::StreamBase& Stream ) const;

            template < typename SE >
            static void Description( Common::Description& Desc );

            const key_container_type& GetKeys( ) const;

            const MapProc_type& GetProc( ) const;

            MapProc_type::const_iterator
            GetProc( const std::string& Name ) const;

            MapProc_type::const_iterator GetProc( INT_4U index ) const;

            void QueryProc( const Common::TOCInfo& Info,
                            INT_4U                 FrameOffset,
                            INT_8U                 Position );

            bool operator==( const FrTOCProcData& RHS ) const;

        protected:
            FrTOCProcData( Common::IStream& Stream, INT_4U FrameCount );

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

        inline Common::FrameSpec::size_type
        FrTOCProcData::Bytes( const Common::StreamBase& Stream ) const
        {
            Common::FrameSpec::size_type retval = sizeof( nproc_type );
            if ( m_info.size( ) )
            {
                retval += ( m_info.size( ) *
                            ( sizeof( position_type ) *
                              m_info.begin( )->second.size( ) ) );
            }
            for ( MapProc_type::const_iterator cur = m_info.begin( ),
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
        FrTOCProcData::Description( Common::Description& Desc )
        {
            Desc( SE( "nProc",
                      "INT_4U",
                      "Number of unique FrAdcData names in file." ) );
            Desc( SE( "nameProc", "*STRING", "Array of FrAdcData names" ) );
            Desc( SE( "positionProc",
                      "*INT_8U",
                      "Array of lists of FrProcData offset positions, in bytes,"
                      " from beginning of file (size of nFrame*nProc)" ) );
        }

        inline const FrTOCProcData::key_container_type&
        FrTOCProcData::GetKeys( ) const
        {
            return m_keys;
        }

        inline const FrTOCProcData::MapProc_type&
        FrTOCProcData::GetProc( ) const
        {
            return m_info;
        }

        inline void
        FrTOCProcData::write( Common::OStream& Stream ) const
        {
            base_type::write( Stream );
        }
    } // namespace Version_6
} // namespace FrameCPP

#endif /* FrameCPP_VERSION_6_FrTOCProcData_HH */
