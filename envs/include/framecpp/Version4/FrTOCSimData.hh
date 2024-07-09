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

#ifndef FrameCPP_VERSION_4_FrTOCSimData_HH
#define FrameCPP_VERSION_4_FrTOCSimData_HH

#include "framecpp/Common/FrTOC.hh"

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
        class FrTOCSimData : public FrTOCPosition
        {
        public:
            typedef FrTOCPosition::n_type        nsim_type;
            typedef FrTOCPosition::position_type position_type;

            typedef FrTOCPosition::info_type sim_info_type;
            typedef FrTOCPosition::Map_type  MapSim_type;

            FrTOCSimData( );

            static void Description( Common::Description& Desc );

            const MapSim_type& GetSim( ) const;

            MapSim_type::const_iterator GetSim( const std::string& Name ) const;

            MapSim_type::const_iterator GetSim( INT_4U index ) const;

            void QuerySim( const Common::TOCInfo& Info,
                           INT_4U                 FrameOffset,
                           INT_8U                 Position );

            bool operator==( const FrTOCSimData& RHS ) const;

        protected:
            FrTOCSimData( Common::IStream& Stream, INT_4U FrameCount );

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

        inline FrTOCSimData::FrTOCSimData( )
        {
        }

        inline FrTOCSimData::FrTOCSimData( Common::IStream& Stream,
                                           INT_4U           FrameCount )
            : FrTOCPosition( Stream, FrameCount )
        {
        }

        inline const FrTOCSimData::MapSim_type&
        FrTOCSimData::GetSim( ) const
        {
            return getInfo( );
        }

        inline FrTOCSimData::MapSim_type::const_iterator
        FrTOCSimData::GetSim( const std::string& Channel ) const
        {
            return getInfo( Channel );
        }

        inline FrTOCSimData::MapSim_type::const_iterator
        FrTOCSimData::GetSim( INT_4U Channel ) const
        {
            return getInfo( Channel );
        }

        inline void
        FrTOCSimData::write( Common::OStream& Stream ) const
        {
            FrTOCPosition::write( Stream );
        }
    } // namespace Version_4
} // namespace FrameCPP

#endif /* FrameCPP_VERSION_4_FrTOCSimData_HH */
