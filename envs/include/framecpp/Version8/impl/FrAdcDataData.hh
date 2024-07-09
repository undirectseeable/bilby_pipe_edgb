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

#ifndef FrameCPP_VERSION_8__IMPL__FrAdcDataData_HH
#define FrameCPP_VERSION_8__IMPL__FrAdcDataData_HH

#if defined( __cplusplus )
#if !defined( SWIG )
#include <memory>
#include <vector>

#include <boost/shared_ptr.hpp>

#include "ldastoolsal/types.hh"

#include "framecpp/Common/Container.hh"

#endif /* ! defined(SWIG) */
#endif /* defined(__cplusplus) */

#include "framecpp/Version3/FrAdcDataPST.hh"
#include "framecpp/Version6/FrAdcDataNPS.hh"

#undef FR_ADC_DATA_NAME_TYPE
#define FR_ADC_DATA_NAME_TYPE std::string

#undef FR_ADC_DATA_COMMENT_TYPE
#define FR_ADC_DATA_COMMENT_TYPE std::string

#undef FR_ADC_DATA_CHANNEL_GROUP_TYPE
#define FR_ADC_DATA_CHANNEL_GROUP_TYPE INT_4U

#undef FR_ADC_DATA_CHANNEL_NUMBER_TYPE
#define FR_ADC_DATA_CHANNEL_NUMBER_TYPE INT_4U

#undef FR_ADC_DATA_N_BITS_TYPE
#define FR_ADC_DATA_N_BITS_TYPE INT_4U

#undef FR_ADC_DATA_BIAS_TYPE
#define FR_ADC_DATA_BIAS_TYPE REAL_4

#undef FR_ADC_DATA_SLOPE_TYPE
#define FR_ADC_DATA_SLOPE_TYPE REAL_4

#undef FR_ADC_DATA_UNITS_TYPE
#define FR_ADC_DATA_UNITS_TYPE std::string

#undef FR_ADC_DATA_SAMPLE_RATE_TYPE
#define FR_ADC_DATA_SAMPLE_RATE_TYPE REAL_8

#undef FR_ADC_DATA_TIME_OFFSET_TYPE
#define FR_ADC_DATA_TIME_OFFSET_TYPE REAL_8

#undef FR_ADC_DATA_F_SHIFT_TYPE
#define FR_ADC_DATA_F_SHIFT_TYPE REAL_8

#undef FR_ADC_DATA_PHASE_TYPE
#define FR_ADC_DATA_PHASE_TYPE REAL_4

#undef FR_ADC_DATA_DATA_VALID_TYPE
#define FR_ADC_DATA_DATA_VALID_TYPE INT_2U

#if defined( __cplusplus )
#if !defined( SWIG )

#include "framecpp/storage/data/FrAdcData.hh"
#include "framecpp/Version8/impl/FrObjectMetaData.hh"

#include "framecpp/Version8/Dimension.hh"
#include "framecpp/Version8/FrVect.hh"

namespace FrameCPP
{
    namespace Version_8
    {
        namespace FrAdcDataImpl
        {
            class Data : public Impl::FrObjectMetaData< Data >,
                         public v5::FrAdcData< FrVect, FrVect >
            {
            public:
                typedef FR_ADC_DATA_NAME_TYPE           name_type;
                typedef FR_ADC_DATA_COMMENT_TYPE        comment_type;
                typedef FR_ADC_DATA_CHANNEL_GROUP_TYPE  channelGroup_type;
                typedef FR_ADC_DATA_CHANNEL_NUMBER_TYPE channelNumber_type;
                typedef FR_ADC_DATA_N_BITS_TYPE         nBits_type;
                typedef FR_ADC_DATA_BIAS_TYPE           bias_type;
                typedef FR_ADC_DATA_SLOPE_TYPE          slope_type;
                typedef FR_ADC_DATA_UNITS_TYPE          units_type;
                typedef FR_ADC_DATA_SAMPLE_RATE_TYPE    sampleRate_type;
                typedef FR_ADC_DATA_TIME_OFFSET_TYPE    timeOffset_type;
                typedef FR_ADC_DATA_F_SHIFT_TYPE        fShift_type;
                typedef FR_ADC_DATA_PHASE_TYPE          phase_type;
                typedef FR_ADC_DATA_DATA_VALID_TYPE     dataValid_type;
                //-------------------------------------------------------
                typedef Common::Container< FrVect >        data_type;
                typedef typename data_type::const_iterator const_iterator;
                typedef typename data_type::iterator       iterator;
                typedef Common::Container< FrVect >        aux_type;
                typedef typename aux_type::const_iterator  const_aux_iterator;
                typedef typename aux_type::iterator        aux_iterator;
                //-------------------------------------------------------
                static constexpr slope_type DEFAULT_SLOPE{ 1.0 };
                static constexpr bias_type DEFAULT_BIAS{ 0 };
                static constexpr fShift_type DEFAULT_FSHIFT{ 0 };
                static constexpr timeOffset_type DEFAULT_TIME_OFFSET{ 0 };
                static constexpr dataValid_type DEFAULT_DATA_VALID{ 0 };
                static constexpr phase_type DEFAULT_PHASE{ 0 };

                static const units_type& DEFAULT_UNITS( );
                /**
                 * \brief Return the name associate with the FrAdcData
                 * structure.
                 *
                 * \return
                 *     The name associated with the FrAdcData structure
                 */
                const name_type& GetName( ) const;

                /**
                 * \brief A brief description of the FrAdcData structure
                 *
                 * \return
                 *     A brief description of the FrAdcData structure
                 */
                const comment_type& GetComment( ) const;

                /**
                 * \brief The channel group for the FrAdcData
                 *
                 * \return
                 *     The crate number for the FrAdcData
                 */
                channelGroup_type GetChannelGroup( ) const;

                /**
                 * \brief The channel number for the FrAdcData
                 *
                 * \return
                 *     The channel number for the FrAdcData
                 */
                channelNumber_type GetChannelNumber( ) const;

                /**
                 * \brief Tne number of bits in the A/D output.
                 *
                 * \return
                 *      Tne number of bits in the A/D output.
                 */
                nBits_type GetNBits( ) const;

                /**
                 * \brief DC bias on channel.
                 *
                 * \return
                 *     DC bias on channel.
                 */
                bias_type GetBias( ) const;

                /**
                 * \brief ADC calibration units per count.
                 *
                 * \return
                 *     ADC calibration units per count.
                 */
                slope_type GetSlope( ) const;

                /**
                 * \brief The units used in the ADC calibration
                 *
                 * \return
                 *     The units used in the ADC calibration
                 */
                const units_type& GetUnits( ) const;

                /**
                 * \brief The data acquisition rate.
                 *
                 * \return
                 *     The data acquisition rate.
                 */
                sampleRate_type GetSampleRate( ) const;

                /**
                 * \brief The offset of the first sample relative to the frame
                 * start time.
                 *
                 * \return
                 *     The offset of the first sample relative to the frame
                 *     start time.
                 */
                timeOffset_type GetTimeOffset( ) const;

                /**
                 * \brief The frequency in the original data corresponding to 0
                 * Hz.
                 *
                 * \return
                 *     The frequency in the original data corresponding to 0 Hz.
                 */
                fShift_type GetFShift( ) const;

                /**
                 * \brief Phase of hetrodyning signal at start of dataset.
                 *
                 * \return
                 * 	The Phase (in radians) of hetrodyning signal at
                 *	start of dataset.
                 */
                phase_type GetPhase( ) const;

                /**
                 * \brief Retrieve the overRange value.
                 *
                 * \return
                 *     The value of the overRange field.
                 */
                dataValid_type GetDataValid( ) const;

                /**
                 * \brief Identifier for vector for user-provided information.
                 *
                 * \return
                 *     A constant reference to the user-provided information.
                 */
                const aux_type& RefAux( ) const;

                /**
                 * \brief Identifier for vector for user-provided information.
                 *
                 * \return
                 *     A reference to the user-provided information.
                 */
                aux_type& RefAux( );

                /**
                 * \brief Identifier for vector of sampled data.
                 *
                 * \return
                 *     A constant reference to the sampled data.
                 */
                const data_type& RefData( ) const;

                /**
                 * \brief Identifier for vector of sampled data.
                 *
                 * \return
                 *     A reference to the sampled data.
                 */
                data_type& RefData( );

                /**
                 * \brief Extend the comment associated with the FrAdcData
                 * structure.
                 */
                void AppendComment( const std::string& comment );

                /**
                 * \brief Establish the value of the dataValid field.
                 *
                 * \param[in] flag
                 *     The desired value of the overRange field.
                 */
                void SetDataValid( dataValid_type flag );

                /**
                 * \brief Establish the value of the bias field.
                 *
                 * \param[in] bias
                 *     The desired value of the bias field.
                 */
                void SetBias( bias_type bias );

                /**
                 * \brief Establish the value of the channelGroup field
                 *
                 * \param[in] Value
                 *     The desired value of the channelGroup field.
                 */
                void SetChannelGroup( channelGroup_type Value );

                /**
                 * \brief Establish the value of the channelNumber field
                 *
                 * \param[in] Value
                 *     The desired value of the channelNumber field.
                 */
                void SetChannelNumber( channelNumber_type Value );

                /**
                 * \brief Set the comment associated with the FrAdcData
                 * structure.
                 *
                 * \param[in] Value
                 *     The desired value for the comment field.
                 */
                void SetComment( const comment_type& Value );

                /**
                 * \brief Tne number of bits in the A/D output.
                 *
                 * \return
                 *      Tne number of bits in the A/D output.
                 */
                void SetNBits( nBits_type Value );

                /**
                 * \brief Establish the value of the sampleRate field
                 *
                 * \param[in] Value
                 *     The desired value of the sampleRate field.
                 */
                void SetSampleRate( sampleRate_type Value );

                /**
                 * \brief Establish the value of the slope field.
                 *
                 * \param[in] slope
                 *     The desired value of the slope field.
                 */
                void SetSlope( slope_type slope );

                /**
                 * \brief Establish the value of the timeOffset field.
                 *
                 * \param[in] Value
                 *     The value for the timeOffset field.
                 */
                void SetTimeOffset( timeOffset_type Value );

                bool operator==( Data const& RHS ) const;

            protected:
                //-------------------------------------------------------
                /// Channel name -- must be unique with the frame
                //-------------------------------------------------------
                name_type name;
                //-------------------------------------------------------
                /// Comment
                //-------------------------------------------------------
                comment_type comment;
                //-------------------------------------------------------
                /// Channel grouping number containing ADC
                //-------------------------------------------------------
                channelGroup_type channelGroup;
                //-------------------------------------------------------
                /// Channel nubmer
                //-------------------------------------------------------
                channelNumber_type channelNumber;
                //-------------------------------------------------------
                /// Number of bits in A/D output
                //-------------------------------------------------------
                nBits_type nBits;
                //-------------------------------------------------------
                /// DC bias on channel (Units @ ADC counts = 0)
                //-------------------------------------------------------
                bias_type bias{ DEFAULT_BIAS };
                //-------------------------------------------------------
                /// ADC calibration: input units/ct
                //-------------------------------------------------------
                slope_type slope{ DEFAULT_SLOPE };
                //-------------------------------------------------------
                /// ADC calibration: input units for slope.
                //-------------------------------------------------------
                units_type units{ DEFAULT_UNITS( ) };
                //-------------------------------------------------------
                /// Data acquisition rate, samples/s
                //-------------------------------------------------------
                sampleRate_type sampleRate;
                //-------------------------------------------------------
                /// Offset of 1st sample relative to the frame start time
                //-------------------------------------------------------
                timeOffset_type timeOffset{ DEFAULT_TIME_OFFSET };
                //-------------------------------------------------------
                /// fShift is the frequency (in Hz) in the original data
                /// that corresponds to 0 Hz in the heterodyned series.
                //-------------------------------------------------------
                fShift_type fShift{ DEFAULT_FSHIFT };
                //-------------------------------------------------------
                /// Phase (in radian) of hetrodyning signal at start
                /// of dataset
                //-------------------------------------------------------
                phase_type phase{ DEFAULT_PHASE };
                //-------------------------------------------------------
                /// Data valid flag
                //-------------------------------------------------------
                dataValid_type dataValid{ DEFAULT_DATA_VALID };
                //=======================================================
                //-------------------------------------------------------
                static constexpr unsigned int MAX_REF{ 2 };
                //-------------------------------------------------------
                /// Identifier for vector of sampled data.
                //-------------------------------------------------------
                data_type data;
                //-------------------------------------------------------
                /// Identifier for vector for user-provided information;
                /// use is generic
                //-------------------------------------------------------
                aux_type aux;

                void incrementTimeOffset( timeOffset_type Value );

                void setName( const name_type& Value );

            }; // class Data

            inline void
            Data::AppendComment( const std::string& Comment )
            {
                FrameCPP::Common::AppendComment( comment, Comment );
            }

            inline const Data::units_type&
            Data::DEFAULT_UNITS( )
            {
                static units_type retval;
                return ( retval );
            }

            inline const Data::comment_type&
            Data::GetComment( ) const
            {
                return comment;
            }

            inline Data::channelNumber_type
            Data::GetChannelNumber( ) const
            {
                return channelNumber;
            }

            inline Data::channelGroup_type
            Data::GetChannelGroup( ) const
            {
                return channelGroup;
            }

            inline const Data::name_type&
            Data::GetName( ) const
            {
                return name;
            }

            inline Data::nBits_type
            Data::GetNBits( ) const
            {
                return nBits;
            }

            inline Data::bias_type
            Data::GetBias( ) const
            {
                return bias;
            }

            inline Data::slope_type
            Data::GetSlope( ) const
            {
                return slope;
            }

            inline const Data::units_type&
            Data::GetUnits( ) const
            {
                return units;
            }

            inline Data::sampleRate_type
            Data::GetSampleRate( ) const
            {
                return sampleRate;
            }

            inline Data::timeOffset_type
            Data::GetTimeOffset( ) const
            {
                return timeOffset;
            }

            inline Data::fShift_type
            Data::GetFShift( ) const
            {
                return fShift;
            }

            inline Data::phase_type
            Data::GetPhase( ) const
            {
                return phase;
            }

            inline Data::dataValid_type
            Data::GetDataValid( ) const
            {
                return dataValid;
            }

            inline const Data::aux_type&
            Data::RefAux( ) const
            {
                return aux;
            }

            inline Data::aux_type&
            Data::RefAux( )
            {
                return aux;
            }

            inline const Data::data_type&
            Data::RefData( ) const
            {
                return data;
            }

            inline Data::data_type&
            Data::RefData( )
            {
                return data;
            }

            inline void
            Data::SetDataValid( dataValid_type Value )
            {
                dataValid = Value;
            }

            inline void
            Data::SetBias( bias_type Value )
            {
                bias = Value;
            }

            inline void
            Data::SetChannelGroup( channelGroup_type Value )
            {
                channelGroup = Value;
            }

            inline void
            Data::SetChannelNumber( channelNumber_type Value )
            {
                channelNumber = Value;
            }

            inline void
            Data::SetComment( const comment_type& Value )
            {
                comment = Value;
            }

            inline void
            Data::SetNBits( nBits_type Value )
            {
                nBits = Value;
            }

            inline void
            Data::SetSampleRate( sampleRate_type Value )
            {
                sampleRate = Value;
            }

            inline void
            Data::SetSlope( slope_type Value )
            {
                slope = Value;
            }

            inline void
            Data::SetTimeOffset( timeOffset_type Value )
            {
                timeOffset = Value;
            }

            inline void
            Data::incrementTimeOffset( timeOffset_type Value )
            {
                timeOffset += Value;
            }

            inline void
            Data::setName( const name_type& Value )
            {
                name = Value;
            }

            inline bool
            Data::operator==( Data const& RHS ) const
            {
                return ( ( this == &RHS ) ||
                         ( ( name.compare( RHS.name ) == 0 ) &&
                           ( comment.compare( RHS.comment ) == 0 ) &&
                           ( channelGroup == RHS.channelGroup ) &&
                           ( channelNumber == RHS.channelNumber ) &&
                           ( nBits == RHS.nBits ) && ( bias == RHS.bias ) &&
                           ( slope == RHS.slope ) &&
                           ( units.compare( RHS.units ) == 0 ) &&
                           ( sampleRate == RHS.sampleRate ) &&
                           ( timeOffset == RHS.timeOffset ) &&
                           ( fShift == RHS.fShift ) && ( phase == RHS.phase ) &&
                           ( dataValid == RHS.dataValid ) &&
                           ( data == RHS.data ) && ( aux == RHS.aux ) ) );
            }
        } // namespace FrAdcDataImpl
    } // namespace Version_8
} // namespace FrameCPP

FR_OBJECT_META_DATA_DECLARE( FrAdcDataImpl )

#endif /* ! defined(SWIG) */
#endif /* defined(__cplusplus) */

#endif /* FrameCPP_VERSION_8__IMPL__FrAdcDataData_HH */
