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

#ifndef FrameCPP_VERSION_8_FrTable_HH
#define FrameCPP_VERSION_8_FrTable_HH

#ifndef SWIGIMPORTED
#include "framecpp/Version8/impl/FrTableClassicIO.hh"
#include "framecpp/Version8/impl/FrTableSerialIO.hh"
#endif /* SWIGIMPORTED */

#ifndef SWIGIMPORTED

namespace FrameCPP
{
    namespace Version_8
    {
        //===================================================================
        /// \brief Table Data Structure Definition
        //===================================================================
        class FrTable
#if !defined( SWIG )
          : public FrTableImpl::ClassicIO< FrTable >,
            public FrTableImpl::SerialIO< FrTable >
#endif /* ! defined( SWIG ) */
        {
        public:
            //-----------------------------------------------------------------
            /// \brief Default constructor
            ///
            /// \return
            ///    A new instance of this object.
            //-----------------------------------------------------------------
            FrTable( );

            //-----------------------------------------------------------------
            /// \brief Copy Constructor
            ///
            /// \param[in] Source
            ///     The object from which to copy the information.
            ///
            /// \return
            ///    A new instance of this object.
            //-----------------------------------------------------------------
            FrTable( const FrTable& Source );

#if 0
            //-----------------------------------------------------------------
            /// \brief Copy Constructor
            ///
            /// \param[in] Source
            ///     The object from which to copy the information.
            ///
            /// \return
            ///    A new instance of this object.
            //-----------------------------------------------------------------
            FrTable( const FrTableNPS& Source );
#endif /* 0 */

            //-----------------------------------------------------------------
            /// \brief Constructor
            ///
            /// \param[in] name
            ///     The of this table.
            /// \param[in] nrows
            ///     Number of rows in table.
            ///
            /// \return
            ///     A new instance of the object.
            //-----------------------------------------------------------------
            FrTable( const name_type& name, nRow_type nrows );

            //-----------------------------------------------------------------
            /// \brief Promotion Constructor
            ///
            /// \param[in] Source
            ///     An FrTable structure from a previous frame specification.
            /// \param[in] Stream
            ///     The stream from which the earliest version of the
            ///     FrTable structure was read.
            ///
            /// \return
            ///     A new instance of the object.
            //-----------------------------------------------------------------
            FrTable( Previous::FrTable& Source, Common::IStream* Stream );

            //-----------------------------------------------------------------
            /// \brief Destructor
            //-----------------------------------------------------------------
            virtual ~FrTable( );

            //-----------------------------------------------------------------
            /// \brief Retrieve the name of the table.
            ///
            /// \return
            ///     The name of the table.
            //-----------------------------------------------------------------
            const name_type& GetNameSlow( ) const;

            //-----------------------------------------------------------------
            /// \brief Merge with another FrTable
            ///
            /// \param[in] RHS
            ///     The source of the information to append to this FrTable
            ///     structure.
            ///
            /// \return
            ///     A reference to this object
            //-----------------------------------------------------------------
            FrTable& Merge( const FrTable& RHS );

            //-----------------------------------------------------------------
            /// \brief Concatinate with another FrTable
            ///
            /// \param[in] RHS
            ///     The source of the information to append to this FrTable
            ///     structure.
            ///
            /// \return
            ///     A reference to this object
            //-----------------------------------------------------------------
            FrTable& operator+=( const FrTable& RHS );

            //-----------------------------------------------------------------
            /// \brief equality operator
            ///
            /// \param[in] RHS
            ///     The FrTable object to be compared.
            ///
            /// \return
            ///     The value true is returned if this object is equivelent
            ///     to the RHS instance; false otherwise.
            //-----------------------------------------------------------------
            bool operator==( const FrTable& RHS ) const;

            //-----------------------------------------------------------------
            /// \brief equality operator for abstract data type
            ///
            /// \param[in] RHS
            ///     The object to be compared.
            ///
            /// \return
            ///     The value true is returned if this object is equivelent
            ///     to the RHS instance; false otherwise.
            //-----------------------------------------------------------------
            virtual bool
            operator==( const Common::FrameSpec::Object& RHS ) const;
        };

        //-------------------------------------------------------------------
        /// \brief Tests the equality of two tables.
        ///
        /// \param[in] RHS
        ///     Right hand side of equality expression.
        ///
        /// \return
        ///     True if the two tables are equivelant, false otherwise.
        //-------------------------------------------------------------------
        inline bool
        FrTable::operator==( const FrTable& RHS ) const
        {
            return ( m_data == RHS.m_data );
        }

    } // namespace Version_8
} // namespace FrameCPP

#endif /* SWIGIMPORTED */

#endif /* FrameCPP_VERSION_8_FrTable_HH */
