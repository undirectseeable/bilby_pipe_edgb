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

#ifndef FrameCPP_VERSION_8__IMPL__FrTOCSerDataData_HH
#define FrameCPP_VERSION_8__IMPL__FrTOCSerDataData_HH

#if !defined( SWIGIMPORTED )

namespace FrameCPP
{
    namespace Version_8
    {
        namespace FrTOCImpl
        {
            class FrTOCSerDataData
            {
            public:
                typedef INT_4U      frame_count_type;
                typedef INT_4U      n_type;
                typedef std::string name_type;
                typedef INT_8U      position_type;

                typedef std::vector< position_type >     info_type;
                typedef std::map< name_type, info_type > MapSer_type;
                typedef std::vector< name_type >         key_container_type;

                const key_container_type&
                GetPositionKeys( ) const
                {
                    return m_keys;
                }

                //-----------------------------------------------------------------
                /// \brief Return all channels
                ///
                /// \return
                ///     Constant container to the indexed FrSerData elements.
                //-----------------------------------------------------------------
                inline const MapSer_type&
                GetSer( ) const
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
                ///     Constant iterator to the indexed FrSerData element.
                //-----------------------------------------------------------------
                inline MapSer_type::const_iterator
                GetSer( const std::string& Channel ) const
                {
                    return m_info.find( Channel );
                }

                //-----------------------------------------------------------------
                /// \brief Return the indexed data for a named channel.
                ///
                /// \param[in] Channel
                ///     The numeric offset of the channel.
                ///
                /// \return
                ///     Constant iterator to the indexed FrSerData element.
                //-----------------------------------------------------------------
                inline MapSer_type::const_iterator
                GetSer( INT_4U Channel ) const
                {
                    if ( Channel >= m_info.size( ) )
                    {
                        return m_info.end( );
                    }
                    return m_info.find( m_keys[ Channel ] );
                }

                FrTOCSerDataData&
                operator=( const FrTOCSerDataData& Source )
                {
                    if ( &Source == this )
                    {
                        return ( *this );
                    }
                    m_keys = Source.m_keys;
                    m_info = Source.m_info;
                    return ( *this );
                }

            protected:
                key_container_type m_keys;
                MapSer_type        m_info;
            };

        } // namespace FrTOCImpl
    } // namespace Version_8
} // namespace FrameCPP

#endif /* !defined( SWIGIMPORTED ) */

#endif /* FrameCPP_VERSION_8__IMPL__FrTOCSerDataData_HH */
