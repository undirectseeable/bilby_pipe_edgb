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

#ifndef FrameCPP_VERSION_8_FrSummary_HH
#define FrameCPP_VERSION_8_FrSummary_HH

#include "framecpp/Version8/impl/FrSummaryClassicIO.hh"

#if defined( __cplusplus ) && !defined( SWIG )

namespace FrameCPP
{
    namespace Version_8
    {
        //===================================================================
        /// \brief Summary Data Structure Definition
        //===================================================================
      class FrSummary : public FrSummaryImpl::ClassicIO< FrSummary >
      {
        public:
            typedef Common::SearchContainer< FrVect, &FrVect::GetName >
                                                 moments_type;
            typedef moments_type::iterator       iterator;
            typedef moments_type::const_iterator const_iterator;

            typedef Common::SearchContainer< FrTable, &FrTable::GetNameSlow >
                                               table_type;
            typedef table_type::iterator       table_iterator;
            typedef table_type::const_iterator const_table_iterator;

            //-----------------------------------------------------------------
            /// \brief Default constructor
            ///
            /// \return
            ///    A new instance of this object.
            //-----------------------------------------------------------------
            FrSummary( ) = default;

            //-----------------------------------------------------------------
            /// \brief Copy Constructor
            ///
            /// \param[in] Source
            ///     The object from which to copy the information.
            ///
            /// \return
            ///    A new instance of this object.
            //-----------------------------------------------------------------
            FrSummary( const FrSummary& Source ) = default;

        //-----------------------------------------------------------------
        /// \brief Constructor
        ///
        /// \param[in] name
        ///     Name of summary statistic.
        /// \param[in] comment
        ///     Comment.
        /// \param[in] test
        ///     Statistical test(s) used on raw data.
        /// \param[in] gtime
        ///     GPS time corresponding to this FrSummary.
        ///
        /// \return
        ///     A new instance of the object.
        //-----------------------------------------------------------------
        FrSummary( const name_type& name,
                   const comment_type& comment,
                   const test_type& test,
                   const gtime_type&     gtime );

        //-----------------------------------------------------------------
        /// \brief Promotion Constructor
        ///
        /// \param[in] Source
        ///     An FrSummary structure from a previous frame specification.
        /// \param[in] Stream
        ///     The stream from which the earliest version of the
        ///     FrSummary structure was read.
        ///
        /// \return
        ///     A new instance of the object.
        //-----------------------------------------------------------------
        FrSummary( Previous::FrSummary& Source, Common::IStream* Stream );

        //-----------------------------------------------------------------
        /// \brief Return the name of summary statistic.
        ///
        /// \return
        ///     The name of summary statistic.
        //-----------------------------------------------------------------
        const name_type& GetName( ) const;

        //-----------------------------------------------------------------
        /// \brief Merge with another FrSummary
        ///
        /// \param[in] RHS
        ///     The source of the information to append to this FrSummary
        ///     structure.
        ///
        /// \return
        ///     A reference to this object
        //-----------------------------------------------------------------
        FrSummary& Merge( const FrSummary& RHS );

            //-----------------------------------------------------------------
            /// \brief equality operator
            ///
            /// \param[in] RHS
            ///     The FrSummary object to be compared.
            ///
            /// \return
            ///     The value true is returned if this object is equivelent
            ///     to the RHS instance; false otherwise.
            //-----------------------------------------------------------------
            bool operator==( const FrSummary& RHS ) const
        {
          return( Data::operator==( RHS ) );
        }

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
    } // namespace Version_8
} // namespace FrameCPP
#endif /* defined( __cplusplus ) && !defined( SWIG ) */

#endif /* FrameCPP_VERSION_8_FrSummary_HH */
