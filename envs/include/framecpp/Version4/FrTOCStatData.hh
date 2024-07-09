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

#ifndef FrameCPP_VERSION_4_FrTOCStatData_HH
#define FrameCPP_VERSION_4_FrTOCStatData_HH

#include "framecpp/Version4/FrTOCTypes.hh"
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
        class FrTOCStatData : FrTOCTypes
        {
        public:
            typedef STRING        name_type;
            typedef INT_4U        nstat_type;
            typedef STRING        detector_type;
            typedef INT_4U        nstat_instance_type;
            typedef INT_4U        tstart_type;
            typedef INT_4U        tend_type;
            typedef INT_4U        version_type;
            typedef position_type positionStat_type;

            struct stat_instance_type
            {
                tstart_type       tStart;
                tend_type         tEnd;
                version_type      version;
                positionStat_type positionStat;
            };

            typedef std::vector< stat_instance_type >
                stat_instance_container_type;

            struct stat_type
            {
                detector_type                detector;
                stat_instance_container_type stat_instances;
            };

            typedef std::map< name_type, stat_type > stat_container_type;

            FrTOCStatData( );

            Common::FrameSpec::size_type
            Bytes( const Common::StreamBase& Stream ) const;

            const stat_container_type& GetStat( ) const;

            bool operator==( const FrTOCStatData& RHS ) const;

            static void Description( Common::Description& Desc );

            void QueryStatData( const Common::TOCInfo& Info,
                                INT_4U                 FrameOffset,
                                INT_8U                 Position );

        protected:
            stat_container_type m_info;

            FrTOCStatData( Common::IStream& Stream );
            void write( Common::OStream& Stream ) const;
        };

        inline Common::FrameSpec::size_type
        FrTOCStatData::Bytes( const Common::StreamBase& Stream ) const
        {
            Common::FrameSpec::size_type retval = sizeof( nstat_type );

            static const INT_4U si = sizeof( tstart_type ) +
                sizeof( tend_type ) + sizeof( version_type ) +
                sizeof( positionStat_type );

            for ( stat_container_type::const_iterator cur = m_info.begin( ),
                                                      last = m_info.end( );
                  cur != last;
                  ++cur )
            {
                retval += cur->first.Bytes( ) + cur->second.detector.Bytes( ) +
                    sizeof( nstat_instance_type ) +
                    ( cur->second.stat_instances.size( ) * si );
            }
            return retval;
        }

        inline const FrTOCStatData::stat_container_type&
        FrTOCStatData::GetStat( ) const
        {
            return m_info;
        }

    } // namespace Version_4
} // namespace FrameCPP

#endif /* FrameCPP_VERSION_4_FrTOCStatData_HH */
