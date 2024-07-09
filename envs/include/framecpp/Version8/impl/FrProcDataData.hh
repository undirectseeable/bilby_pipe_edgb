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

#ifndef FrameCPP_VERSION_8__IMPL__FrProcDataData_HH
#define FrameCPP_VERSION_8__IMPL__FrProcDataData_HH

#if defined( __cplusplus )
#if !defined( SWIG )
#include <memory>
#include <vector>

#include <boost/shared_ptr.hpp>

#include "ldastoolsal/types.hh"

#include "framecpp/Common/Container.hh"

#include "framecpp/Version8/FrHistory.hh"
#include "framecpp/Version8/FrTable.hh"
#include "framecpp/Version8/FrVect.hh"

#endif /* ! defined(SWIG) */
#endif /* defined(__cplusplus) */

#include "framecpp/Version7/FrProcData.hh"

#undef FR_PROC_DATA_NAME_TYPE
#define FR_PROC_DATA_NAME_TYPE std::string

#undef FR_PROC_DATA_COMMENT_TYPE
#define FR_PROC_DATA_COMMENT_TYPE std::string

#undef FR_PROC_DATA_TYPE_TYPE
#define FR_PROC_DATA_TYPE_TYPE INT_2U

#undef FR_PROC_DATA_SUB_TYPE_TYPE
#define FR_PROC_DATA_SUB_TYPE_TYPE INT_2U

#undef FR_PROC_DATA_TIME_OFFSET_TYPE
#define FR_PROC_DATA_TIME_OFFSET_TYPE REAL_8

#undef FR_PROC_DATA_T_RANGE_TYPE
#define FR_PROC_DATA_T_RANGE_TYPE REAL_8

#undef FR_PROC_DATA_F_SHIFT_TYPE
#define FR_PROC_DATA_F_SHIFT_TYPE REAL_8

#undef FR_PROC_DATA_PHASE_TYPE
#define FR_PROC_DATA_PHASE_TYPE REAL_4

#undef FR_PROC_DATA_F_RANGE_TYPE
#define FR_PROC_DATA_F_RANGE_TYPE REAL_8

#undef FR_PROC_DATA_BW_TYPE
#define FR_PROC_DATA_BW_TYPE REAL_8

#undef FR_PROC_DATA_AUX_PARAM_VALUE_TYPE
#define FR_PROC_DATA_AUX_PARAM_VALUE_TYPE REAL_8

#undef FR_PROC_DATA_T_RANGE_TYPE
#define FR_PROC_DATA_T_RANGE_TYPE REAL_8

#define FR_PROC_DATA__MIME_TYPE UNKNOWN_TYPE
#define FR_PROC_DATA__MIME_SUB_TYPE UNKNOWN_SUB_TYPE

#if defined( __cplusplus )
#if !defined( SWIG )

#include "framecpp/Version8/impl/FrObjectMetaData.hh"

namespace FrameCPP
{
    namespace Version_8
    {
        namespace FrProcDataImpl
        {
            class Data : public Impl::FrObjectMetaData< Data >
            {
            public:
                enum e_type_type
                {
                    UNKNOWN_TYPE = 0,
                    TIME_SERIES = 1,
                    FREQUENCY_SERIES = 2,
                    OTHER_1D_SERIES_DATA = 3,
                    TIME_FREQUENCY = 4,
                    WAVELETS = 5,
                    MULTI_DIMENSIONAL = 6
                };

                enum e_subType_type
                {
                    UNKNOWN_SUB_TYPE = 0,
                    /*---------------------------------------------------------------
                      Subtype for fSeries
                      ---------------------------------------------------------------*/
                    DFT = 1,
                    AMPLITUDE_SPECTRAL_DENSITY = 2,
                    POWER_SPECTRAL_DENSITY = 3,
                    CROSS_SPECTRAL_DENSITY = 4,
                    COHERENCE = 5,
                    TRANSFER_FUNCTION = 6
                };

                typedef struct auxParamInfo
                {
                    typedef REAL_8      auxParamValue_type;
                    typedef std::string auxParamName_type;

                    auxParamInfo( ) = default;
                    auxParamInfo( const auxParamInfo& ) = default;

                    auxParamInfo( const auxParamName_type& Name,
                                  auxParamValue_type       Value )
                        : auxParam( Value ), auxParamName( Name )
                    {
                    }

                    inline bool
                    operator==( const auxParamInfo& RHS ) const
                    {
                        return ( ( this == &RHS ) ||
                                 ( ( auxParam == RHS.auxParam ) &&
                                   ( auxParamName.compare( RHS.auxParamName ) ==
                                     0 ) ) );
                    }

                    auxParamValue_type auxParam;
                    auxParamName_type  auxParamName;
                } auxParamInfo_type;

                typedef FR_PROC_DATA_NAME_TYPE           name_type;
                typedef FR_PROC_DATA_COMMENT_TYPE        comment_type;
                typedef FR_PROC_DATA_TYPE_TYPE           type_type;
                typedef FR_PROC_DATA_SUB_TYPE_TYPE       subType_type;
                typedef FR_PROC_DATA_TIME_OFFSET_TYPE    timeOffset_type;
                typedef FR_PROC_DATA_T_RANGE_TYPE        tRange_type;
                typedef FR_PROC_DATA_F_SHIFT_TYPE        fShift_type;
                typedef FR_PROC_DATA_PHASE_TYPE          phase_type;
                typedef FR_PROC_DATA_F_RANGE_TYPE        fRange_type;
                typedef FR_PROC_DATA_BW_TYPE             BW_type;
                typedef std::vector< auxParamInfo_type > auxParam_type;
                //-------------------------------------------------------
                typedef Common::Container< FrVect >    data_type;
                typedef data_type::const_iterator      const_iterator;
                typedef data_type::iterator            iterator;
                typedef Common::Container< FrVect >    aux_type;
                typedef aux_type::const_iterator       const_aux_iterator;
                typedef aux_type::iterator             aux_iterator;
                typedef Common::Container< FrTable >   table_type;
                typedef FrTable                        table_value_type;
                typedef table_type::const_iterator     const_table_iterator;
                typedef table_type::iterator           table_iterator;
                typedef Common::Container< FrHistory > history_type;
                typedef history_type::const_iterator   const_history_iterator;
                typedef history_type::iterator         history_iterator;

                // Backwards compatibility
                typedef auxParam_type             AuxParamList_type;
                typedef auxParam_type::value_type AuxParam_type;

                Data( ) : synced_with_vector_( false )
                {
                }

                inline void
                AppendComment( const std::string& Comment )
                {
                    FrameCPP::Common::AppendComment( comment, Comment );
                }

                inline void
                AppendAuxParam( const auxParam_type::value_type& Param )
                {
                    auxParam.push_back( Param );
                }

                /**
                 * \brief Return the name associate with the FrProcData
                 * structure.
                 *
                 * \return
                 *     The name associated with the FrProcData structure
                 */
                const name_type&
                GetName( ) const
                {
                    return name;
                }

                const name_type& GetNameSlow( ) const;

                /**
                 * \brief A brief description of the FrProcData structure
                 *
                 * \return
                 *     A brief description of the FrProcData structure
                 */
                const comment_type&
                GetComment( ) const
                {
                    return comment;
                }

                inline type_type
                GetType( ) const
                {
                    return ( type );
                }

                inline subType_type
                GetSubType( ) const
                {
                    return ( subType );
                }

                inline timeOffset_type
                GetTimeOffset( ) const
                {
                    return ( timeOffset );
                }

                inline fShift_type
                GetFShift( ) const
                {
                    return ( fShift );
                }

                inline phase_type
                GetPhase( ) const
                {
                    return ( phase );
                }

                inline BW_type
                GetBW( ) const
                {
                    return ( BW );
                }

                inline const auxParam_type&
                GetAuxParam( ) const
                {
                    return ( auxParam );
                }

                inline auxParam_type&
                GetAuxParam( )
                {
                    return ( auxParam );
                }

                /**
                 * \brief Retrieve the frequency range.
                 *
                 * \return
                 *     The frequency range.
                 */
                inline fRange_type
                GetFRange( ) const
                {
                    sync( );
                    return ( fRange );
                }

                /**
                 * \brief Retrieve the time range.
                 *
                 * \return
                 *     The time range.
                 */
                inline tRange_type
                GetTRange( ) const
                {
                    sync( );
                    return ( tRange );
                }

                /**
                 * \brief Convert numeric types to string representation
                 *
                 * \param[in] Type
                 *     Numeric type.
                 *
                 * \return
                 *     The string representation of Type.
                 */
                static const std::string& IDTypeToString( type_type Type );

                /**
                 * \brief Convert numeric sub-types to string representation
                 *
                 * \param[in] Type
                 *     Numeric type.
                 * \param[in] SubType
                 *     Numeric sub-type.
                 *
                 * \return
                 *     The string representation of SubType of Type.
                 */
                static const std::string&
                IDSubTypeToString( type_type Type, subType_type SubType );

                inline void
                SetAuxParam( const auxParam_type& AuxParams )
                {
                    auxParam = AuxParams;
                }
                inline void
                SetComment( const comment_type& Comment )
                {
                    comment = Comment;
                }
                inline void
                SetFRange( fRange_type FRange )
                {
                    fRange = FRange;
                }

                inline void
                SetFShift( fShift_type FShift )
                {
                    fShift = FShift;
                }

                inline void
                SetTimeOffset( timeOffset_type TimeOffset )
                {
                    timeOffset = TimeOffset;
                }

                inline void
                SetTRange( tRange_type TRange )
                {
                    tRange = TRange;
                }

                /**
                 * \brief Identifier for vector for auxilliary data.
                 *
                 * \return
                 *     A constant reference to the auxilliary data.
                 */
                inline const aux_type&
                RefAux( ) const
                {
                    return ( aux );
                }

                /**
                 * \brief Identifier for vector for auxilliary data.
                 *
                 * \return
                 *     A reference to the auxilliary data.
                 */
                inline aux_type&
                RefAux( )
                {
                    return ( aux );
                }

                /**
                 * \brief Identifier for vector for data vector.
                 *
                 * \return
                 *     A constant reference to the data vector.
                 */
                inline const data_type&
                RefData( ) const
                {
                    return ( data );
                }

                /**
                 * \brief Identifier for vector for data vector.
                 *
                 * \return
                 *     A reference to the data vector.
                 */
                inline data_type&
                RefData( )
                {
                    return ( data );
                }

                /**
                 * \brief Identifier for parameter table.
                 *
                 * \return
                 *     A constant reference to the parameter table.
                 */
                inline const table_type&
                RefTable( ) const
                {
                    return ( table );
                }

                /**
                 * \brief Identifier for parameter table.
                 *
                 * \return
                 *     A reference to the parameter table.
                 */
                inline table_type&
                RefTable( )
                {
                    return ( table );
                }

                /**
                 * \brief Identifier for channel history.
                 *
                 * \return
                 *     A constant reference to the channel history.
                 */
                inline const history_type&
                RefHistory( ) const
                {
                    return ( history );
                }

                /**
                 * \brief Identifier for channel history.
                 *
                 * \return
                 *     A reference to the channel history.
                 */
                inline history_type&
                RefHistory( )
                {
                    return ( history );
                }

                /**
                 * \brief equality operator
                 *
                 * \param[in] RHS
                 *     The FrProcData object to be compared.
                 *
                 * \return
                 *     The value true is returned if this object is equivelent
                 *     to the RHS instance; false otherwise.
                 */
                inline bool
                operator==( const Data& RHS ) const
                {
                    return (
                        ( this == &RHS ) ||
                        ( ( name.compare( RHS.name ) == 0 ) &&
                          ( comment.compare( RHS.comment ) == 0 ) &&
                          ( type == RHS.type ) && ( subType == RHS.subType ) &&
                          ( timeOffset == RHS.timeOffset ) &&
                          ( tRange == RHS.tRange ) &&
                          ( fShift == RHS.fShift ) && ( phase == RHS.phase ) &&
                          ( fRange == RHS.fRange ) && ( BW == RHS.BW ) &&
                          ( auxParam == RHS.auxParam ) &&
                          ( data == RHS.data ) && ( aux == RHS.aux ) &&
                          ( table == RHS.table ) &&
                          ( history == RHS.history ) ) );
                }

                static constexpr phase_type PHASE_UNKNOWN{ 0 };
                static constexpr fRange_type FRANGE_UNKNOWN{ 0 };
                static constexpr BW_type BW_UNKNOWN{ 0 };

            protected:
                /**
                 * \brief Copy core data.
                 *
                 * \param[in] Source
                 *     The source from which to copy the data
                 */
                void
                copy_core( const Data& Source )
                {
                    Data::name = Source.name;
                    Data::comment = Source.comment;
                    Data::type = Source.type;
                    Data::subType = Source.subType;
                    Data::timeOffset = Source.timeOffset;
                    Data::tRange = Source.tRange;
                    Data::fShift = Source.fShift;
                    Data::phase = Source.phase;
                    Data::fRange = Source.fRange;
                    Data::BW = Source.BW;
                    //-----------------------------------------------------------
                    Data::aux = Source.aux;
                    Data::table = Source.table;
                    Data::history = Source.history;
                }

                inline void
                sync( ) const
                {
                    if ( synced_with_vector_ )
                    {
                        const_cast< Data* >( this )->sync_with_vector( );
                    }
                }
                void
                sync_with_vector( )
                {
                    if ( ( synced_with_vector_ == false ) &&
                         ( RefData( ).size( ) > 0 ) )
                    {
                        switch ( GetType( ) )
                        {
                        case TIME_SERIES:
                            SetTRange(
                                ( RefData( )[ 0 ]->GetDim( 0 ).GetNx( ) *
                                  RefData( )[ 0 ]->GetDim( 0 ).GetDx( ) ) );
                            break;
                        case FREQUENCY_SERIES:
                            SetFRange(
                                ( RefData( )[ 0 ]->GetDim( 0 ).GetNx( ) *
                                  RefData( )[ 0 ]->GetDim( 0 ).GetDx( ) ) );
                            break;
                        }
                        synced_with_vector_ = true;
                    }
                }

                //-------------------------------------------------------
                /// Channel name -- must be unique with the frame
                //-------------------------------------------------------
                name_type name;
                //-------------------------------------------------------
                /// Comment
                //-------------------------------------------------------
                comment_type comment;
                //-------------------------------------------------------
                /// Type of data object
                //-------------------------------------------------------
                type_type type;
                //-------------------------------------------------------
                /// Subtype for f-Series (TBD for other types)
                //-------------------------------------------------------
                subType_type subType;
                //-------------------------------------------------------
                /// Offset of 1st sample relative to the frame start time
                /// (seconds)
                //-------------------------------------------------------
                timeOffset_type timeOffset;
                //-------------------------------------------------------
                /// Duration of sampled data (tStop-tStart)
                //-------------------------------------------------------
                tRange_type tRange;
                //-------------------------------------------------------
                /// fShift is the frequency in the original data that
                /// corresponds to 0 Hz in the heterodyned series
                //-------------------------------------------------------
                fShift_type fShift;
                //-------------------------------------------------------
                /// Phase of heterodyning signal at start of dataset (radians, 0
                /// if unknown)
                //-------------------------------------------------------
                phase_type phase;
                //-------------------------------------------------------
                /// Frequency range (=fMax-fMin, 0 if unknown)
                //-------------------------------------------------------
                fRange_type fRange;
                //-------------------------------------------------------
                /// Resolution bandwidth
                //-------------------------------------------------------
                BW_type BW;
                //-------------------------------------------------------
                /// Auxiliary parameters
                //-------------------------------------------------------
                auxParam_type auxParam;
                //-------------------------------------------------------
                /// Data vector. The data vector fro single dimensional types
                /// (t-Series and f-Series) must have a single dimension.
                //-------------------------------------------------------
                data_type data;
                //-------------------------------------------------------
                /// Auxiliary data; use is generic.
                //-------------------------------------------------------
                aux_type aux;
                //-------------------------------------------------------
                /// Parameter table
                //-------------------------------------------------------
                table_type table;
                //-------------------------------------------------------
                /// Channel history.
                //-------------------------------------------------------
                history_type history;
                //=======================================================
                //-------------------------------------------------------
                static constexpr unsigned int MAX_REF{ 4 };
                //=======================================================
                //-------------------------------------------------------
                bool synced_with_vector_;
            }; // class Data
        } // namespace FrProcDataImpl
    } // namespace Version_8
} // namespace FrameCPP

FR_OBJECT_META_DATA_DECLARE( FrProcDataImpl )

#endif /* ! defined(SWIG) */
#endif /* defined(__cplusplus) */

#endif /* FrameCPP_VERSION_8__IMPL__FrProcDataData_HH */
