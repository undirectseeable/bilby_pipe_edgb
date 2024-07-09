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

#ifndef FrameCPP_VERSION_4_FrTOCProcData_HH
#define FrameCPP_VERSION_4_FrTOCProcData_HH

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
        class FrTOCProcData
            : public Common::FrTOC::
                  PositionWithCache< STRING, FrTOCPosition::position_type >
        {
        public:
            typedef Common::FrTOC::
                PositionWithCache< STRING, FrTOCPosition::position_type >
                                                 base_type;
            typedef FrTOCPosition::n_type        nproc_type;
            typedef FrTOCPosition::position_type position_type;

            typedef FrTOCPosition::info_type proc_info_type;
            typedef FrTOCPosition::Map_type  MapProc_type;

            FrTOCProcData( );

            static void Description( Common::Description& Desc );

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

        inline FrTOCProcData::FrTOCProcData( )
        {
        }

        inline FrTOCProcData::FrTOCProcData( Common::IStream& Stream,
                                             INT_4U           FrameCount )
            : Common::FrTOC::PositionWithCache< STRING,
                                                FrTOCPosition::position_type >(
                  Stream, FrameCount )
        {
        }

        inline const FrTOCProcData::MapProc_type&
        FrTOCProcData::GetProc( ) const
        {
            return getInfo( );
        }

        inline FrTOCProcData::MapProc_type::const_iterator
        FrTOCProcData::GetProc( const std::string& Channel ) const
        {
            return getInfo( Channel );
        }

        inline FrTOCProcData::MapProc_type::const_iterator
        FrTOCProcData::GetProc( INT_4U Channel ) const
        {
            return getInfo( Channel );
        }

        inline void
        FrTOCProcData::write( Common::OStream& Stream ) const
        {
            base_type::write( Stream );
        }
    } // namespace Version_4
} // namespace FrameCPP

#endif /* FrameCPP_VERSION_4_FrTOCProcData_HH */
