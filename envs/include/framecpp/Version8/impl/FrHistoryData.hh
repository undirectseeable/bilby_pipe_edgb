//
// LDASTools frameCPP - A library implementing the LIGO/Virgo frame
// specification
//
// Copyright (C) 2019 California Institute of Technology
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

#ifndef FrameCPP_VERSION_8__IMPL__FrHistoryData_HH
#define FrameCPP_VERSION_8__IMPL__FrHistoryData_HH

#include <string>

#include "framecpp/Version8/impl/FrObjectMetaData.hh"

namespace FrameCPP
{
    namespace Version_8
    {
        namespace FrHistoryImpl
        {
            class Data : public Impl::FrObjectMetaData< Data >
            {
            public:
                //-----------------------------------------------------------------
                /// \brief Type for name of history record
                //-----------------------------------------------------------------
                typedef std::string name_type;

                //-----------------------------------------------------------------
                /// \brief Type for time of history record
                //-----------------------------------------------------------------
                typedef INT_4U time_type;

                //-----------------------------------------------------------------
                /// \brief Type for comment field.
                ///
                /// Program name and relevant comments needed to
                /// define post-processing.
                //-----------------------------------------------------------------
                typedef std::string comment_type;

                //-----------------------------------------------------------------
                /// \brief Return the name associate with the FrHistory
                /// structure.
                ///
                /// \return
                ///     The name associated with the FrHistory structure
                //-----------------------------------------------------------------
                const name_type&
                GetName( ) const
                {
                    return name;
                }

                //-----------------------------------------------------------------
                /// \brief Return the time of the post-processing.
                ///
                /// \return
                ///     The time of the post-processing.
                //-----------------------------------------------------------------
                time_type
                GetTime( ) const
                {
                    return time;
                }

                //-----------------------------------------------------------------
                /// \brief Return the description of the post-porcessing.
                ///
                /// \return
                ///     The description of the post-processing
                //-----------------------------------------------------------------
                const comment_type&
                GetComment( ) const
                {
                    return comment;
                }

                //---------------------------------------------------------------
                /// Name of the history record.
                /// \note
                ///     When an FrHistory is linked to an FrProcData, its
                ///     name variable must be the FrProcData channel name.
                //---------------------------------------------------------------
                name_type name;
                //---------------------------------------------------------------
                /// \brief Time of history record
                ///
                /// Time of post-processing,
                /// GPS time in integer seconds since GPS standard epoch.
                //---------------------------------------------------------------
                time_type time;
                //---------------------------------------------------------------
                /// Program name and relevant comments needed to define
                /// post-processing.
                //---------------------------------------------------------------
                comment_type comment;

                //---------------------------------------------------------------
                /// \brief equality operator
                ///
                /// \param[in] RHS
                ///     The fr_history_data_type object to be compared.
                ///
                /// \return
                ///     The value true is returned if this object is
                ///     equivelent to the RHS instance; false otherwise.
                //---------------------------------------------------------------
                bool operator==( const Data& RHS ) const
              {
#define CMP__( X ) ( X == RHS.X )
                return ( ( &RHS == this ) ||
                         ( CMP__( name ) && CMP__( time ) && CMP__( comment ) ) );
#undef CMP__
              }
            };
        } // namespace FrHistoryImpl
    } // namespace Version_8
} // namespace FrameCPP

FR_OBJECT_META_DATA_DECLARE( FrHistoryImpl )

#endif /* FrameCPP_VERSION_8__IMPL__FrHistoryData_HH */
