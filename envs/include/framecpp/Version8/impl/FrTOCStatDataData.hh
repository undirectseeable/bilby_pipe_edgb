//
// LDASTools - A library implementing the LIGO/Virgo frame
// specification
//
// Copyright (C) 2020 California Institute of Technology
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

#ifndef FrameCPP_VERSION_8__IMPL__FrTOCStatDataData_HH
#define FrameCPP_VERSION_8__IMPL__FrTOCStatDataData_HH

#if !defined( SWIGIMPORTED )

namespace FrameCPP
{
    namespace Version_8
    {
        namespace FrTOCImpl
        {
            class FrTOCStatDataData
            {
            public:
                typedef STRING name_type;
                typedef INT_4U nstat_type;
                typedef STRING detector_type;
                typedef INT_4U nstat_instance_type;
                typedef INT_4U tstart_type;
                typedef INT_4U tend_type;
                typedef INT_4U version_type;
                typedef INT_8U positionStat_type;

                struct stat_instance_type
                {
                    //---------------------------------------------------------------
                    /// \brief Start time of the static data.
                    //---------------------------------------------------------------
                    tstart_type tStart;
                    //---------------------------------------------------------------
                    /// \brief End time of the static data.
                    //---------------------------------------------------------------
                    tend_type tEnd;
                    //---------------------------------------------------------------
                    /// \brief Version of the static data.
                    //---------------------------------------------------------------
                    version_type version;
                    //---------------------------------------------------------------
                    /// \brief FrStatData offset positions.
                    ///
                    /// FrStatData offset positions, in bytes,
                    /// from the beginning of the file.
                    //---------------------------------------------------------------
                    positionStat_type positionStat;
                };

                typedef std::vector< stat_instance_type >
                    stat_instance_container_type;

                struct stat_type
                {
                    //---------------------------------------------------------------
                    /// \brief FrDetector associated with the static data.
                    //---------------------------------------------------------------
                    detector_type detector;
                    //---------------------------------------------------------------
                    /// \brief Container of static data members
                    //---------------------------------------------------------------
                    stat_instance_container_type stat_instances;
                };

                typedef std::map< name_type, stat_type > stat_container_type;

                //-----------------------------------------------------------------
                /// \brief Return all channels
                ///
                /// \return
                ///     Constant container to the indexed FrStatData elements.
                //-----------------------------------------------------------------
                inline const stat_container_type&
                GetStat( ) const
                {
                    return m_info;
                }

                //-----------------------------------------------------------------
                /// \brief Return number of FrStatData structures.
                ///
                /// \return
                ///     The number of FrStatData structures.
                //-----------------------------------------------------------------
                inline INT_4U
                GetNTotalStat( ) const
                {
                    INT_4U retval = 0;
                    for ( stat_container_type::const_iterator
                              cur = m_info.begin( ),
                              last = m_info.end( );
                          cur != last;
                          ++cur )
                    {
                        retval += cur->second.stat_instances.size( );
                    }
                    return retval;
                }

              //-----------------------------------------------------------------
              /// \brief equality operator
              ///
              /// \param[in] RHS
              ///     The FrTOCAdcData object to be compared.
              ///
              /// \return
              ///     The value true is returned if this object is equivelent
              ///     to the RHS instance; false otherwise.
              //-----------------------------------------------------------------
              bool operator==( const FrTOCStatDataData& RHS ) const;

            protected:
                stat_container_type m_info;
            };
        } // namespace FrTOCImpl
    } // namespace Version_8
} // namespace FrameCPP

#endif /* !defined( SWIGIMPORTED ) */

#endif /* FrameCPP_VERSION_8__IMPL__FrTOCStatDataData_HH */
