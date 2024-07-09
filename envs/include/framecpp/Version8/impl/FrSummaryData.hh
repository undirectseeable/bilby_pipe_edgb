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

#ifndef FrameCPP_VERSION_8__IMPL__FrSummaryData_HH
#define FrameCPP_VERSION_8__IMPL__FrSummaryData_HH

#undef FR_SUMMARY_NAME_TYPE
#define FR_SUMMARY_NAME_TYPE std::string

#undef FR_SUMMARY_COMMENT_TYPE
#define FR_SUMMARY_COMMENT_TYPE std::string

#undef FR_SUMMARY_TEST_TYPE
#define FR_SUMMARY_TEST_TYPE std::string

#if defined( __cplusplus ) && !defined( SWIG )

#include "framecpp/Common/SearchContainer.hh"

#include "framecpp/Version8/FrTable.hh"
#include "framecpp/Version8/FrVect.hh"

#include "framecpp/Version8/impl/FrObjectMetaData.hh"

namespace FrameCPP
{
    namespace Version_8
    {
        namespace FrSummaryImpl
        {
            class Data : public Impl::FrObjectMetaData< Data >
            {
            public:
                typedef FR_SUMMARY_NAME_TYPE    name_type;
                typedef FR_SUMMARY_COMMENT_TYPE comment_type;
                typedef FR_SUMMARY_TEST_TYPE    test_type;
                typedef GPSTime                 gtime_type;

                typedef Common::SearchContainer< FrVect, &FrVect::GetName >
                                                     moments_type;
                typedef moments_type::iterator       iterator;
                typedef moments_type::const_iterator const_iterator;

                typedef Common::SearchContainer< FrTable,
                                                 &FrTable::GetNameSlow >
                                                   table_type;
                typedef table_type::iterator       table_iterator;
                typedef table_type::const_iterator const_table_iterator;

                //-----------------------------------------------------------------
                /// \brief Return the name of summary statistic.
                ///
                /// \return
                ///     The name of summary statistic.
                //-----------------------------------------------------------------
                const name_type&
                GetName( ) const
                {
                    return ( name );
                }

                //-----------------------------------------------------------------
                /// \brief Return the comment.
                ///
                /// \return
                ///     The comment.
                //-----------------------------------------------------------------
                inline const comment_type&
                GetComment( ) const
                {
                    return comment;
                }

                //-----------------------------------------------------------------
                /// \brief Return the statistical test(s) used on raw data.
                ///
                /// \return
                ///     The the statistical test(s) used on raw data.
                //-----------------------------------------------------------------
                inline const test_type&
                GetTest( ) const
                {
                    return test;
                }

                //-----------------------------------------------------------------
                /// \brief Return the GPS time corresponding to this object.
                ///
                /// \return
                ///     The GPS time corresponding to this object.
                //-----------------------------------------------------------------
                inline const gtime_type&
                GetGTime( ) const
                {
                    return gtime;
                }

                //-----------------------------------------------------------------
                /// \brief Identifier for vector containing statistical
                /// descriptors.
                ///
                /// \return
                ///     A constant reference to the statistical descriptors.
                //-----------------------------------------------------------------
                inline const moments_type&
                RefMoments( ) const
                {
                    return moments;
                }

                //-----------------------------------------------------------------
                /// \brief Identifier for vector containing statistical
                /// descriptors.
                ///
                /// \return
                ///     A reference to the statistical descriptors.
                //-----------------------------------------------------------------
                inline moments_type&
                RefMoments( )
                {
                    return moments;
                }

                //-----------------------------------------------------------------
                /// \brief Identifier for table containing additional summary
                /// information.
                ///
                /// \return
                ///     A constant reference to the table containing additional
                ///     summary Information.
                //-----------------------------------------------------------------
                inline const table_type&
                RefTable( ) const
                {
                    return table;
                }

                //-----------------------------------------------------------------
                /// \brief Identifier for table containing additional summary
                /// information.
                ///
                /// \return
                ///     A reference to the table containing additional
                ///     summary Information.
                //-----------------------------------------------------------------
                inline table_type&
                RefTable( )
                {
                    return table;
                }

                inline bool
                operator==( const Data& RHS ) const
                {
                    return ( ( this == &RHS ) ||
                             ( ( name.compare( RHS.name ) == 0 ) &&
                               ( comment.compare( RHS.comment ) == 0 ) &&
                               ( test.compare( RHS.test ) == 0 ) &&
                               ( gtime == RHS.gtime ) ) );
                }

            protected:
                //---------------------------------------------------------------
                /// Name of summary statistic.
                //---------------------------------------------------------------
                name_type name;
                //---------------------------------------------------------------
                /// Comment.
                //---------------------------------------------------------------
                comment_type comment;
                //---------------------------------------------------------------
                /// Statistical test(s) used on raw data.
                //---------------------------------------------------------------
                test_type test;
                //---------------------------------------------------------------
                /// GPS time corresponding to this object.
                //---------------------------------------------------------------
                gtime_type gtime;
                //---------------------------------------------------------------
                /// Identifier for vector containing statistical descriptors.
                //---------------------------------------------------------------
                moments_type moments;
                //---------------------------------------------------------------
                /// Indentifier for table containing additional summary
                /// information.
                //---------------------------------------------------------------
                table_type table;
                //=======================================================
                //-------------------------------------------------------
                static constexpr unsigned int MAX_REF{ 3 };
            };

        } // namespace FrSummaryImpl
    } // namespace Version_8

} // namespace FrameCPP

FR_OBJECT_META_DATA_DECLARE( FrSummaryImpl )

#endif /* defined( __cplusplus ) && !defined( SWIG ) */

#endif /* FrameCPP_VERSION_8__IMPL__FrSummaryData_HH */
