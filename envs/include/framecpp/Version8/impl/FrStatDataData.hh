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

#ifndef FrameCPP_VERSION_8__IMPL__FrStatDataData_HH
#define FrameCPP_VERSION_8__IMPL__FrStatDataData_HH

#if defined( __cplusplus ) && !defined( SWIG )

#include "framecpp/Common/SearchContainer.hh"

#include "framecpp/Version8/FrDetector.hh"
#include "framecpp/Version8/FrTable.hh"
#include "framecpp/Version8/FrVect.hh"

#include "framecpp/Version8/impl/FrObjectMetaData.hh"

namespace FrameCPP
{
    namespace Version_8
    {
        namespace FrStatDataImpl
        {
            class Data : public Impl::FrObjectMetaData< Data >
            {
            public:
                typedef std::string name_type;
                typedef std::string comment_type;
                typedef std::string representation_type;
                typedef INT_4U      timeStart_type;
                typedef INT_4U      timeEnd_type;
                typedef INT_4U      version_type;

                typedef boost::shared_ptr< FrDetector > detector_type;

                typedef boost::shared_ptr< FrDetector > const
                    const_detector_type;

                typedef
                    typename Common::SearchContainer< FrVect, &FrVect::GetName >
                                                           data_type;
                typedef typename data_type::iterator       iterator;
                typedef typename data_type::const_iterator const_iterator;

                typedef
                    typename Common::SearchContainer< FrTable,
                                                      &FrTable::GetNameSlow >
                                                      table_type;
                typedef typename table_type::iterator table_iterator;
                typedef
                    typename table_type::const_iterator const_table_iterator;

                //-----------------------------------------------------------------
                /// \brief Retrieve static data name
                ///
                /// \return
                ///     The static data name
                //-----------------------------------------------------------------
                inline const std::string&
                GetName( ) const
                {
                    return ( name );
                }

                //-----------------------------------------------------------------
                /// \brief Retrieve the comment
                ///
                /// \return
                ///     The comment
                //-----------------------------------------------------------------
                inline const std::string&
                GetComment( ) const
                {
                    return ( comment );
                }

                //-----------------------------------------------------------------
                /// \brief Retrieve the type of static data
                ///
                /// \return
                ///     The type of static data being represente
                //-----------------------------------------------------------------
                inline const std::string&
                GetRepresentation( ) const
                {
                    return ( representation );
                }

                //-----------------------------------------------------------------
                /// \brief Retrieve the start time
                ///
                /// \return
                ///     The start time of the static data validity.
                //-----------------------------------------------------------------
                inline timeStart_type
                GetTimeStart( ) const
                {
                    return ( timeStart );
                }

                //-----------------------------------------------------------------
                /// \brief Retrieve the end time
                ///
                /// \return
                ///     The end time of the static data validity.
                //-----------------------------------------------------------------
                inline timeEnd_type
                GetTimeEnd( ) const
                {
                    return ( timeEnd );
                }

                //-----------------------------------------------------------------
                /// \brief Retrieve the version number
                ///
                /// \return
                ///    The version number for this static structure.
                //-----------------------------------------------------------------
                inline version_type
                GetVersion( ) const
                {
                    return ( version );
                }

                inline detector_type
                GetDetector( )
                {
                    return detector;
                }

                inline const_detector_type
                GetDetector( ) const
                {
                    return detector;
                }

                inline const data_type&
                RefData( ) const
                {
                    return data;
                }

                inline data_type&
                RefData( )
                {
                    return data;
                }

                inline const table_type&
                RefTable( ) const
                {
                    return table;
                }

                inline table_type&
                RefTable( )
                {
                    return table;
                }

                inline detector_type*
                AddressOfDetector( ) const
                {
                    return &( const_cast< Data* >( this )->detector );
                }

                inline void
                SetDetector( detector_type Detector )
                {
                    detector = Detector;
                }

                inline bool
                operator==( const Data& RHS ) const
                {
                    return (
                        ( this == &RHS ) ||
                        ( ( name == RHS.name ) && ( comment == RHS.comment ) &&
                          ( representation == RHS.representation ) &&
                          ( timeStart == RHS.timeStart ) &&
                          ( timeEnd == RHS.timeEnd ) &&
                          ( version == RHS.version ) &&
                          ( ( detector == RHS.detector ) ||
                            ( detector && RHS.detector &&
                              ( *detector == *( RHS.detector ) ) ) ) &&
                          ( data == RHS.data ) && ( table == RHS.table ) ) );
                }

            protected:
                //---------------------------------------------------------------
                /// Static data name
                //---------------------------------------------------------------
                name_type name;
                //---------------------------------------------------------------
                /// Comment for static data
                //---------------------------------------------------------------
                comment_type comment;
                //---------------------------------------------------------------
                /// Type of static data being represented. e,g., calibration,
                /// swept sine, pole-zero, FIR or IIR coefficients...
                //---------------------------------------------------------------
                representation_type representation;
                //---------------------------------------------------------------
                /// Start time of static data validity.
                /// GPS time in integer seconds since GPS standard epoch.
                //---------------------------------------------------------------
                timeStart_type timeStart;
                //---------------------------------------------------------------
                /// End time of static data validity.
                /// A value of zero represents the end time being unknown.
                /// GPS time in integer seconds since GPS standard epoch.
                //---------------------------------------------------------------
                timeEnd_type timeEnd;
                //---------------------------------------------------------------
                /// Version number for this static structure.
                /// i.e., the counter begins at 0 and is incremented by 1
                /// thereafter.
                /// Updated statics for the same time window
                /// (e.g., modified calibration data) will be identified by
                /// identified by unique version numbers.
                //---------------------------------------------------------------
                version_type version;

                detector_type detector;
                data_type     data;
                table_type    table;
                //=======================================================
                //-------------------------------------------------------
                static constexpr unsigned int MAX_REF{ 3 };
            }; // class Data
        } // namespace FrStatDataImpl
    } // namespace Version_8
} // namespace FrameCPP

FR_OBJECT_META_DATA_DECLARE( FrStatDataImpl )

#endif /* defined( __cplusplus ) && !defined( SWIG ) */

#endif /* FrameCPP_VERSION_8__IMPL__FrStatDataData_HH */
