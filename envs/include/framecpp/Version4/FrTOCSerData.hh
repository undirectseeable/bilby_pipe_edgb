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

#ifndef FrameCPP_VERSION_4_FrTOCSerData_HH
#define FrameCPP_VERSION_4_FrTOCSerData_HH

#include "framecpp/Version4/FrTOCPosition.hh"
#include "framecpp/Version4/STRING.hh"

namespace FrameCPP
{
    namespace Common
    {
        class TOCInfo;
    }

    namespace Version_4
    {
        //===================================================================
        //===================================================================
        class FrTOCSerData : public FrTOCPosition
        {
        public:
            typedef FrTOCPosition::n_type        nser_type;
            typedef FrTOCPosition::position_type position_type;

            typedef FrTOCPosition::info_type ser_info_type;
            typedef FrTOCPosition::Map_type  MapSer_type;

            FrTOCSerData( );

            template < typename SE >
            static void Description( Common::Description& Desc );

            const MapSer_type& GetSer( ) const;

            MapSer_type::const_iterator GetSer( const std::string& Name ) const;

            MapSer_type::const_iterator GetSer( INT_4U index ) const;

            void QuerySer( const Common::TOCInfo& Info,
                           INT_4U                 FrameOffset,
                           INT_8U                 Position );

            bool operator==( const FrTOCSerData& RHS ) const;

        protected:
            FrTOCSerData( Common::IStream& Stream, INT_4U FrameCount );
            void write( Common::OStream& Stream ) const;
        };

        inline FrTOCSerData::FrTOCSerData( )
        {
        }

        inline FrTOCSerData::FrTOCSerData( Common::IStream& Stream,
                                           INT_4U           FrameCount )
            : FrTOCPosition( Stream, FrameCount )
        {
        }

        template < typename SE >
        void
        FrTOCSerData::Description( Common::Description& Desc )
        {
            Desc( SE( "nSer",
                      "INT_4U",
                      "Number of unique FrSerData names in file." ) );
            Desc( SE( "nameSer", "*STRING", "Array of FrSerData names" ) );
            Desc( SE( "positionSer",
                      "*INT_8U",
                      "Array of lists of FrSerData offset positions, in bytes,"
                      " from beginning of file (size of nFrame*nSer)" ) );
        }

        inline const FrTOCSerData::MapSer_type&
        FrTOCSerData::GetSer( ) const
        {
            return getInfo( );
        }

        inline FrTOCSerData::MapSer_type::const_iterator
        FrTOCSerData::GetSer( const std::string& Channel ) const
        {
            return getInfo( Channel );
        }

        inline FrTOCSerData::MapSer_type::const_iterator
        FrTOCSerData::GetSer( INT_4U Channel ) const
        {
            return getInfo( Channel );
        }

        inline void
        FrTOCSerData::write( Common::OStream& Stream ) const
        {
            FrTOCPosition::write( Stream );
        }
    } // namespace Version_4
} // namespace FrameCPP

#endif /* FrameCPP_VERSION_4_FrTOCSerData_HH */
