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

#ifndef FrameCPP_VERSION_4_FrTOCSummary_HH
#define FrameCPP_VERSION_4_FrTOCSummary_HH

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
        class FrTOCSummary : public FrTOCPosition
        {
        public:
            typedef FrTOCPosition::n_type        nsummary_type;
            typedef FrTOCPosition::position_type position_type;

            typedef FrTOCPosition::info_type summary_info_type;
            typedef FrTOCPosition::Map_type  MapSummary_type;

            FrTOCSummary( );

            template < typename SE >
            static void Description( Common::Description& Desc );

            const MapSummary_type& GetSummary( ) const;

            MapSummary_type::const_iterator
            GetSummary( const std::string& Name ) const;

            MapSummary_type::const_iterator GetSummary( INT_4U index ) const;

            void QuerySum( const Common::TOCInfo& Info,
                           INT_4U                 FrameOffset,
                           INT_8U                 Position );

            bool operator==( const FrTOCSummary& RHS ) const;

        protected:
            FrTOCSummary( Common::IStream& Stream, INT_4U FrameCount );
            void write( Common::OStream& Stream ) const;
        };

        inline FrTOCSummary::FrTOCSummary( )
        {
        }

        inline FrTOCSummary::FrTOCSummary( Common::IStream& Stream,
                                           INT_4U           FrameCount )
            : FrTOCPosition( Stream, FrameCount )
        {
        }

        template < typename SE >
        void
        FrTOCSummary::Description( Common::Description& Desc )
        {
            Desc( SE( "nSummary",
                      "INT_4U",
                      "Number of unique FrSummary names in file." ) );
            Desc( SE( "nameSum", "*STRING", "Array of FrSummary names" ) );
            Desc( SE( "positionSum",
                      "*INT_8U",
                      "Array of lists of FrSummary offset positions, in bytes,"
                      " from beginning of file (size of nFrame*nSer)" ) );
        }

        inline const FrTOCSummary::MapSummary_type&
        FrTOCSummary::GetSummary( ) const
        {
            return getInfo( );
        }

        inline FrTOCSummary::MapSummary_type::const_iterator
        FrTOCSummary::GetSummary( const std::string& Channel ) const
        {
            return getInfo( Channel );
        }

        inline FrTOCSummary::MapSummary_type::const_iterator
        FrTOCSummary::GetSummary( INT_4U Channel ) const
        {
            return getInfo( Channel );
        }

        inline void
        FrTOCSummary::write( Common::OStream& Stream ) const
        {
            FrTOCPosition::write( Stream );
        }
    } // namespace Version_4
} // namespace FrameCPP

#endif /* FrameCPP_VERSION_4_FrTOCSummary_HH */
