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

#ifndef FrameCPP_VERSION_8__IMPL__FrTOCSimDataData_HH
#define FrameCPP_VERSION_8__IMPL__FrTOCSimDataData_HH

namespace FrameCPP
{
    namespace Version_8
    {
        namespace FrTOCImpl
        {
            class FrTOCSimDataData
            {
            public:
                typedef INT_4U nsim_type;
                typedef STRING name_type;
                typedef INT_8U position_type;

                typedef std::vector< position_type >         sim_info_type;
                typedef std::map< name_type, sim_info_type > MapSim_type;

                //-----------------------------------------------------------------
                /// \brief Return all channels
                ///
                /// \return
                ///     Constant container to the indexed FrSimData elements.
                //-----------------------------------------------------------------
                inline const MapSim_type&
                GetSim( ) const
                {
                    return m_info;
                }

                //-----------------------------------------------------------------
                /// \brief Return the indexed data for a named channel.
                ///
                /// \param[in] Channel
                ///     The name of the channel.
                ///
                /// \return
                ///     Constant iterator to the indexed FrSimData element.
                //-----------------------------------------------------------------
                inline MapSim_type::const_iterator
                GetSim( const std::string& Channel ) const
                {
                    return GetSim( ).find( Channel );
                }

                //-----------------------------------------------------------------
                /// \brief Return the indexed data for a named channel.
                ///
                /// \param[in] Channel
                ///     The numeric offset of the channel.
                ///
                /// \return
                ///     Constant iterator to the indexed FrSimData element.
                //-----------------------------------------------------------------
                inline MapSim_type::const_iterator
                GetSim( INT_4U Channel ) const
                {
                    if ( Channel >= GetSim( ).size( ) )
                    {
                        return GetSim( ).end( );
                    }
                    return GetSim( ).find( m_keys[ Channel ] );
                }

            protected:
                typedef std::vector< name_type > key_container_type;
                key_container_type               m_keys;
                MapSim_type                      m_info;
            };

        } // namespace FrTOCImpl
    } // namespace Version_8
} // namespace FrameCPP

#endif /* FrameCPP_VERSION_8__IMPL__FrTOCSimDataData_HH */
