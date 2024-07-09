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

#ifndef FrameCPP_VERSION_8__IMPL__FrTOCAdcDataData_HH
#define FrameCPP_VERSION_8__IMPL__FrTOCAdcDataData_HH

#if !defined( SWIGIMPORTED )
namespace FrameCPP
{
    namespace Version_8
    {
        namespace FrTOCImpl
        {
            class FrTOCAdcDataData
            {
            public:
                typedef INT_4U nadc_type;
                typedef STRING name_type;
                typedef INT_4U channel_id_type;
                typedef INT_4U group_id_type;
                typedef INT_8U position_type;

                struct adc_info_type
                {
                    //---------------------------------------------------------------
                    /// \brief Channel ID of ADC
                    //---------------------------------------------------------------
                    channel_id_type m_channelID;
                    //---------------------------------------------------------------
                    /// \brief Group ID of ADC
                    //---------------------------------------------------------------
                    group_id_type m_groupID;
                    //---------------------------------------------------------------
                    /// \brief FrAdcData offset positions.
                    ///
                    /// FrAdcData offset positions, in bytes,
                    /// from the beginning of the file.
                    /// The size of the array is nFrame
                    //---------------------------------------------------------------
                    std::vector< position_type > m_positionADC;
                    //---------------------------------------------------------------
                    /// \brief Adc channel index number, sequential as read from
                    /// the TOC
                    //---------------------------------------------------------------
                    INT_4U m_index;

                    //---------------------------------------------------------------
                    //---------------------------------------------------------------
                    inline adc_info_type( )
                    {
                    }

                    //---------------------------------------------------------------
                    //---------------------------------------------------------------
                    inline adc_info_type(
                        channel_id_type                    ChannelId,
                        group_id_type                      GroupId,
                        const std::vector< position_type > Positions,
                        INT_4U                             Index )
                        : m_channelID( ChannelId ), m_groupID( GroupId ),
                          m_positionADC( Positions ), m_index( Index )
                    {
                    }

                    //---------------------------------------------------------------
                    //---------------------------------------------------------------
                    adc_info_type(
                        channel_id_type ChannelId,
                        group_id_type   GroupId,
                        const std::vector< position_type >::const_iterator
                            BeginPos,
                        const std::vector< position_type >::const_iterator
                               EndPos,
                        INT_4U Index )
                        : m_channelID( ChannelId ), m_groupID( GroupId ),
                          m_positionADC( BeginPos, EndPos ), m_index( Index )
                    {
                    }
                };

                typedef std::vector< name_type > key_container_type;

                //-----------------------------------------------------------------
                /// \brief Container of indexed FrAdcData elements.
                ///
                /// This structure is ordered by the name of the FrAdcData
                /// channel name.
                /// There is one element for each channel of indexed data.
                //-----------------------------------------------------------------
                typedef std::map< name_type, adc_info_type > MapADC_type;

                //-----------------------------------------------------------------
                /// \brief Return all channels
                ///
                /// \return
                ///     Constant container to the indexed FrAdcData elements.
                //-----------------------------------------------------------------
                inline const MapADC_type& GetADC( ) const;

                //-----------------------------------------------------------------
                /// \brief Return the indexed data for a named channel.
                ///
                /// \param[in] Channel
                ///     The name of the channel.
                ///
                /// \return
                ///     Constant iterator to the indexed FrAdcData element.
                //-----------------------------------------------------------------
                MapADC_type::const_iterator
                GetADC( const std::string& Name ) const;

                //-----------------------------------------------------------------
                /// \brief Return the indexed data for an indexed channel.
                ///
                /// \param[in] Channel
                ///     The numeric offset of the channel.
                ///
                /// \return
                ///     Constant iterator to the indexed FrAdcData element.
                //-----------------------------------------------------------------
                MapADC_type::const_iterator GetADC( INT_4U Channel ) const;

                //-----------------------------------------------------------------
                /// \brief Retrieve the keys
                ///
                /// \return
                ///     Constant container of keys.
                //-----------------------------------------------------------------
                inline const key_container_type& GetKeys( ) const;

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
                bool operator==( const FrTOCAdcDataData& RHS ) const;

            protected:
                key_container_type m_keys;
                MapADC_type        m_info;

                inline MapADC_type&
                getADC( )
                {
                    return m_info;
                }

                inline MapADC_type::iterator
                getADC( const std::string& Channel )
                {
                    return m_info.find( Channel );
                }

                inline MapADC_type::iterator
                getADC( INT_4U Channel )
                {
                    MapADC_type& i( getADC( ) );

                    if ( Channel >= i.size( ) )
                    {
                        return i.end( );
                    }
                    return i.find( m_keys[ Channel ] );
                }
            };

            inline const FrTOCAdcDataData::MapADC_type&
            FrTOCAdcDataData::GetADC( ) const
            {
                return ( m_info );
            }

            inline FrTOCAdcDataData::MapADC_type::const_iterator
            FrTOCAdcDataData::GetADC( const std::string& Channel ) const
            {
                return m_info.find( Channel );
            }

            inline FrTOCAdcDataData::MapADC_type::const_iterator
            FrTOCAdcDataData::GetADC( INT_4U Channel ) const
            {
                if ( Channel >= m_info.size( ) )
                {
                    return ( m_info.end( ) );
                }
                return m_info.find( m_keys[ Channel ] );
            }

            inline const FrTOCAdcDataData::key_container_type&
            FrTOCAdcDataData::GetKeys( ) const
            {
                return m_keys;
            }
        } // namespace FrTOCImpl
    } // namespace Version_8
} // namespace FrameCPP
#endif /* !defined( SWIGIMPORTED ) */

#endif /* FrameCPP_VERSION_8__IMPL__FrTOCAdcDataData_HH */
