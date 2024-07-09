//
// LDASTools frameCPP - A library implementing the LIGO/Virgo frame
// specification
//
// Copyright (C) 2018-2020 California Institute of Technology
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

#ifndef FrameCPP_VERSION_8__FRIMPL__FrRawDataData_HH
#define FrameCPP_VERSION_8__FRIMPL__FrRawDataData_HH

#if defined( __cplusplus ) && !defined( SWIG )

#include "framecpp/Common/SearchContainer.hh"

#include "framecpp/Version8/FrAdcData.hh"
#include "framecpp/Version8/FrMsg.hh"
#include "framecpp/Version8/FrSerData.hh"
#include "framecpp/Version8/FrTable.hh"
#include "framecpp/Version8/FrVect.hh"

namespace FrameCPP
{
    namespace Version_8
    {
        namespace FrRawDataImpl
        {
            class Data : public Impl::FrObjectMetaData< Data >
            {
            public:
                typedef std::string name_type;
                typedef Common::SearchContainer< FrSerData,
                                                 &FrSerData::GetNameSlow >
                                                      firstSer_type;
                typedef firstSer_type::iterator       firstSer_iterator;
                typedef firstSer_type::const_iterator const_firstSer_iterator;
                typedef firstSer_type::hash_iterator  firstSer_hash_iterator;
                typedef firstSer_type::const_hash_iterator
                    const_firstSer_hash_iterator;

                typedef Common::SearchContainer< FrAdcData,
                                                 &FrAdcData::GetNameSlow >
                                                      firstAdc_type;
                typedef firstAdc_type::iterator       firstAdc_iterator;
                typedef firstAdc_type::const_iterator const_firstAdc_iterator;
                typedef firstAdc_type::hash_iterator  firstAdc_hash_iterator;
                typedef firstAdc_type::const_hash_iterator
                    const_firstAdc_hash_iterator;

                typedef Common::SearchContainer< FrTable,
                                                 &FrTable::GetNameSlow >
                                                  firstTable_type;
                typedef firstTable_type::iterator firstTable_iterator;
                typedef firstTable_type::const_iterator
                                                       const_firstTable_iterator;
                typedef firstTable_type::hash_iterator firstTable_hash_iterator;
                typedef firstTable_type::const_hash_iterator
                    const_firstTable_hash_iterator;

                typedef Common::SearchContainer< FrMsg, &FrMsg::GetAlarm >
                                                    logMsg_type;
                typedef logMsg_type::iterator       logMsg_iterator;
                typedef logMsg_type::const_iterator const_logMsg_iterator;
                typedef logMsg_type::hash_iterator  logMsg_hash_iterator;
                typedef logMsg_type::const_hash_iterator
                    const_logMsg_hash_iterator;

                typedef Common::SearchContainer< FrVect, &FrVect::GetName >
                                                       more_type;
                typedef more_type::iterator            more_iterator;
                typedef more_type::const_iterator      const_more_iterator;
                typedef more_type::hash_iterator       more_hash_iterator;
                typedef more_type::const_hash_iterator const_more_hash_iterator;

                //-----------------------------------------------------------------
                /// @brief Nam eof raw data.
                ///
                /// @return
                ///   A constant reference to the name of the raw data
                ///   structure.
                //-----------------------------------------------------------------
                inline const name_type&
                GetName( ) const
                {
                    return ( name );
                }

                //-----------------------------------------------------------------
                /// \brief Identifier for first serial data structure.
                ///
                /// \return
                ///     A constant reference to the first serial data structure.
                //-----------------------------------------------------------------
                inline const firstSer_type&
                RefFirstSer( ) const
                {
                    return ( firstSer );
                }

                //-----------------------------------------------------------------
                /// \brief Identifier for first serial data structure.
                ///
                /// \return
                ///     A reference to the first serial data structure.
                //-----------------------------------------------------------------
                inline firstSer_type&
                RefFirstSer( )
                {
                    return ( firstSer );
                }

                //-----------------------------------------------------------------
                /// \brief Identifier for first ADC data structure.
                ///
                /// \return
                ///     A constant reference to the first ADC data structure.
                //-----------------------------------------------------------------
                inline const firstAdc_type&
                RefFirstAdc( ) const
                {
                    return ( firstAdc );
                }

                //-----------------------------------------------------------------
                /// \brief Identifier for first ADC data structure.
                ///
                /// \return
                ///     A reference to the first ADC data structure.
                //-----------------------------------------------------------------
                inline firstAdc_type&
                RefFirstAdc( )
                {
                    return ( firstAdc );
                }

                //-----------------------------------------------------------------
                /// \brief Identifier for first table data structure.
                ///
                /// \return
                ///     A constant reference to the first table data structure.
                //-----------------------------------------------------------------
                inline const firstTable_type&
                RefFirstTable( ) const
                {
                    return ( firstTable );
                }

                //-----------------------------------------------------------------
                /// \brief Identifier for first table data structure.
                ///
                /// \return
                ///     A reference to the first table data structure.
                //-----------------------------------------------------------------
                inline firstTable_type&
                RefFirstTable( )
                {
                    return ( firstTable );
                }

                //-----------------------------------------------------------------
                /// \brief Identifier for first error message data structure.
                ///
                /// \return
                ///     A constant reference to the first error message data
                ///     structure.
                //-----------------------------------------------------------------
                inline const logMsg_type&
                RefLogMsg( ) const
                {
                    return ( logMsg );
                }

                //-----------------------------------------------------------------
                /// \brief Identifier for first error message data structure.
                ///
                /// \return
                ///     A reference to the first error message data structure.
                //-----------------------------------------------------------------
                inline logMsg_type&
                RefLogMsg( )
                {
                    return ( logMsg );
                }

                //-----------------------------------------------------------------
                /// \brief Identifier for additional user-defined data
                /// structure.
                ///
                /// \return
                ///     A constant reference to the additional user-defined data
                ///     structure.
                //-----------------------------------------------------------------
                inline const more_type&
                RefMore( ) const
                {
                    return ( more );
                }

                //-----------------------------------------------------------------
                /// \brief Identifier for additional user-defined data
                /// structure.
                ///
                /// \return
                ///     A reference to the additional user-defined data
                ///     structure.
                //-----------------------------------------------------------------
                inline more_type&
                RefMore( )
                {
                    return ( more );
                }

                inline bool
                operator==( const Data& RHS ) const
                {
                    return ( ( this == &RHS ) ||
                             ( ( name == RHS.name ) &&
                               ( firstSer == RHS.firstSer ) &&
                               ( firstAdc == RHS.firstAdc ) &&
                               ( firstTable == RHS.firstTable ) &&
                               ( logMsg == RHS.logMsg ) &&
                               ( more == RHS.more ) ) );
                }

            protected:
                //---------------------------------------------------------------
                /// Name of raw data.
                //---------------------------------------------------------------
                name_type name;
                //---------------------------------------------------------------
                /// Identifier for first serial data structure in the
                /// linked list.
                //---------------------------------------------------------------
                firstSer_type firstSer;
                //---------------------------------------------------------------
                /// Identifier for first ADC data structure in the
                /// linked list.
                //---------------------------------------------------------------
                firstAdc_type firstAdc;
                //---------------------------------------------------------------
                /// Identifier for first table data structure in the
                /// linked list.
                //---------------------------------------------------------------
                firstTable_type firstTable;
                //---------------------------------------------------------------
                /// Identifier for first error message data structure in the
                /// linked list.
                //---------------------------------------------------------------
                logMsg_type logMsg;
                //---------------------------------------------------------------
                /// Identifier for the additional user-defined data structure
                /// in the linked list.
                //---------------------------------------------------------------
                more_type more;
                //=======================================================
                //-------------------------------------------------------
                static constexpr unsigned int MAX_REF{ 5 };
            };

        }; // namespace FrRawDataImpl
    } // namespace Version_8
} // namespace FrameCPP

FR_OBJECT_META_DATA_DECLARE( FrRawDataImpl )

#endif /* defined( __cplusplus ) && !defined( SWIG ) */

#endif /* FrameCPP_VERSION_8__FRIMPL__FrRawDataData_HH */
