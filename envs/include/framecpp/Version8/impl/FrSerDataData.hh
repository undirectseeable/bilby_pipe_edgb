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

#ifndef FrameCPP_VERSION_8__IMPL__FrSerDataData_HH
#define FrameCPP_VERSION_8__IMPL__FrSerDataData_HH

#if defined( __cplusplus )
#if !defined( SWIG )

#include "framecpp/Common/SearchContainer.hh"

#include "framecpp/Version8/FrTable.hh"
#include "framecpp/Version8/FrVect.hh"

#endif /* !defined( SWIG ) */
#endif /* defined( __cplusplus ) */

#undef FR_SER_DATA_NAME_TYPE
#define FR_SER_DATA_NAME_TYPE std::string

#undef FR_SER_DATA_TIME_TYPE
#define FR_SER_DATA_TIME_TYPE FrameCPP::Version_8::GPSTime

#undef FR_SER_DATA_SAMPLE_RATE_TYPE
#define FR_SER_DATA_SAMPLE_RATE_TYPE REAL_8

#undef FR_SER_DATA_DATA_TYPE
#define FR_SER_DATA_DATA_TYPE std::string

#if defined( __cplusplus )
#if !defined( SWIG )

#include "framecpp/Version8/impl/FrObjectMetaData.hh"

namespace FrameCPP
{
    namespace Version_8
    {
        namespace FrSerDataImpl
        {
            class Data : public Impl::FrObjectMetaData< Data >
            {
            public:
                typedef FR_SER_DATA_NAME_TYPE        name_type;
                typedef FR_SER_DATA_TIME_TYPE        time_type;
                typedef FR_SER_DATA_SAMPLE_RATE_TYPE sampleRate_type;
                typedef FR_SER_DATA_DATA_TYPE        data_type;

                typedef Common::SearchContainer< FrVect, &FrVect::GetName >
                                                    serial_type;
                typedef serial_type::iterator       iterator;
                typedef serial_type::const_iterator const_iterator;

                typedef Common::SearchContainer< FrTable,
                                                 &FrTable::GetNameSlow >
                                                   table_type;
                typedef table_type::iterator       table_iterator;
                typedef table_type::const_iterator const_table_iterator;

                //-------------------------------------------------------
                /// \brief Return the name of station producing serial
                /// data stream.
                ///
                /// \return
                ///     The name associated of station producing serial
                ///     data stream.
                //-------------------------------------------------------
                inline const name_type&
                GetName( ) const
                {
                    return ( name );
                }

                //-------------------------------------------------------
                /// \brief Retrieve the time of data acquisition.
                ///
                /// \return
                ///     The time of data acquisition.
                //-------------------------------------------------------
                inline const time_type&
                GetTime( ) const
                {
                    return ( time );
                }

                //-------------------------------------------------------
                /// \brief Retrieve the sample rate.
                ///
                /// \return
                ///     The sample rate.
                //-------------------------------------------------------
                inline sampleRate_type
                GetSampleRate( ) const
                {
                    return ( sampleRate );
                }

                //-------------------------------------------------------
                /// \brief Retrieve string of ASCII-based data.
                ///
                /// \return
                ///     The string of ASCII-based data.
                //-------------------------------------------------------
                inline const data_type&
                GetData( ) const
                {
                    return ( data );
                }

                //-------------------------------------------------------
                /// \brief Establish the string of ASCII-based data.
                //-------------------------------------------------------
                inline void
                SetData( const data_type& Data )
                {
                    data = Data;
                }

                //-------------------------------------------------------
                /// \brief Identifier for serial data vector.
                ///
                /// \return
                ///     A constant reference the serial data vector.
                //-------------------------------------------------------
                inline const serial_type&
                RefSerial( ) const
                {
                    return ( serial );
                }

                //-------------------------------------------------------
                /// \brief Identifier for serial data vector.
                ///
                /// \return
                ///     A reference the serial data vector.
                //-------------------------------------------------------
                inline serial_type&
                RefSerial( )
                {
                    return ( serial );
                }

                //-------------------------------------------------------
                /// \brief Identifier for user-defined table structure.
                ///
                /// \return
                ///     A constant reference to the  user-defined table
                ///     structure.
                //-------------------------------------------------------
                inline const table_type&
                RefTable( ) const
                {
                    return ( table );
                }
                //-------------------------------------------------------
                /// \brief Identifier for user-defined table structure.
                ///
                /// \return
                ///     A reference to the  user-defined table structure.
                //-------------------------------------------------------
                inline table_type&
                RefTable( )
                {
                    return ( table );
                }

                //-----------------------------------------------------------------
                /// \brief equality operator
                ///
                /// \param[in] RHS
                ///     The FrSerData object to be compared.
                ///
                /// \return
                ///     The value true is returned if this object is equivelent
                ///     to the RHS instance; false otherwise.
                //-----------------------------------------------------------------
                inline bool
                operator==( const Data& RHS ) const
                {
                    return ( ( this == &RHS ) ||
                             ( ( name.compare( RHS.name ) == 0 ) &&
                               ( time == RHS.time ) &&
                               ( sampleRate == RHS.sampleRate ) &&
                               ( data.compare( RHS.data ) == 0 ) &&
                               ( serial == RHS.serial ) &&
                               ( table == RHS.table ) ) );
                }

            protected:
                //-------------------------------------------------------
                /// Name of station producing serial data stream
                //-------------------------------------------------------
                name_type name;
                //-------------------------------------------------------
                /// Time of data acquisition,
                /// GPS time in seconds since GPS standard epoch.
                //-------------------------------------------------------
                time_type time;
                //-------------------------------------------------------
                /// Sample rate, samles per second.
                //-------------------------------------------------------
                sampleRate_type sampleRate;
                //-------------------------------------------------------
                /// Pointer to strin for ASCII-based data.
                //-------------------------------------------------------
                data_type data;
                //-------------------------------------------------------
                /// Identifier for serial data vector.
                //-------------------------------------------------------
                serial_type serial;
                //-------------------------------------------------------
                /// Identifier for user-defined table structure.
                //-------------------------------------------------------
                table_type table;
                //=======================================================
                //-------------------------------------------------------
                static constexpr unsigned int MAX_REF{ 2 };

            }; // class Data
        } // namespace FrSerDataImpl
    } // namespace Version_8
} // namespace FrameCPP

FR_OBJECT_META_DATA_DECLARE( FrSerDataImpl )

#endif /* ! defined(SWIG) */
#endif /* defined(__cplusplus) */

#endif /* FrameCPP_VERSION_8__IMPL__FrSerDataData_HH */
