//
// LDASTools frameCPP - A library implementing the LIGO/Virgo frame
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

#ifndef FRAMECPP__STORAGE__V3__FrAdcData_HH
#define FRAMECPP__STORAGE__V3__FrAdcData_HH

#if defined( __cplusplus )
#if !defined( SWIG )
#include <memory>
#include <vector>

#include <boost/shared_ptr.hpp>

#include "ldastoolsal/types.hh"

#include "framecpp/Common/Container.hh"

#endif /* ! defined(SWIG) */
#endif /* defined(__cplusplus) */

#undef FR_ADC_DATA_NAME_TYPE
#define FR_ADC_DATA_NAME_TYPE std::string

#undef FR_ADC_DATA_COMMENT_TYPE
#define FR_ADC_DATA_COMMENT_TYPE std::string

#undef FR_ADC_DATA_CRATE_TYPE
#define FR_ADC_DATA_CRATE_TYPE INT_4U

#undef FR_ADC_DATA_CHANNEL_TYPE
#define FR_ADC_DATA_CHANNEL_TYPE INT_4U

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

#undef FR_ADC_DATA_TIME_OFFSET_S_TYPE
#define FR_ADC_DATA_TIME_OFFSET_S_TYPE INT_4U

#undef FR_ADC_DATA_TIME_OFFSET_N_TYPE
#define FR_ADC_DATA_TIME_OFFSET_N_TYPE INT_4U

#undef FR_ADC_DATA_F_SHIFT_TYPE
#define FR_ADC_DATA_F_SHIFT_TYPE REAL_8

#undef FR_ADC_DATA_OVER_RANGE_TYPE
#define FR_ADC_DATA_OVER_RANGE_TYPE INT_2U

#if defined( __cplusplus )
#if !defined( SWIG )

namespace FrameCPP
{
    namespace v3
    {
        template < typename DATA_TYPE_T, typename AUX_TYPE_T >
        class FrAdcData
        {
        public:
            typedef FR_ADC_DATA_NAME_TYPE           name_type;
            typedef FR_ADC_DATA_COMMENT_TYPE        comment_type;
            typedef FR_ADC_DATA_CRATE_TYPE  crate_type;
            typedef FR_ADC_DATA_CHANNEL_TYPE channel_type;
            typedef FR_ADC_DATA_N_BITS_TYPE         nBits_type;
            typedef FR_ADC_DATA_BIAS_TYPE           bias_type;
            typedef FR_ADC_DATA_SLOPE_TYPE          slope_type;
            typedef FR_ADC_DATA_UNITS_TYPE          units_type;
            typedef FR_ADC_DATA_SAMPLE_RATE_TYPE    sampleRate_type;
            typedef FR_ADC_DATA_TIME_OFFSET_S_TYPE  timeOffsetS_type;
            typedef FR_ADC_DATA_TIME_OFFSET_N_TYPE  timeOffsetN_type;
            typedef FR_ADC_DATA_F_SHIFT_TYPE        fShift_type;
            typedef FR_ADC_DATA_OVER_RANGE_TYPE     overRange_type;
            //-------------------------------------------------------
            typedef Common::Container< DATA_TYPE_T >   data_type;
            typedef typename data_type::const_iterator const_iterator;
            typedef typename data_type::iterator       iterator;
            typedef Common::Container< AUX_TYPE_T >    aux_type;
            typedef typename aux_type::const_iterator  const_aux_iterator;
            typedef typename aux_type::iterator        aux_iterator;
            //-------------------------------------------------------
            static constexpr slope_type DEFAULT_SLOPE{ 0 };
            static constexpr bias_type DEFAULT_BIAS{ 0 };
            static constexpr fShift_type DEFAULT_FSHIFT{ 0 };
            static constexpr timeOffsetS_type DEFAULT_TIME_OFFSET_S{ 0 };
            static constexpr timeOffsetN_type DEFAULT_TIME_OFFSET_N{ 0 };
            static constexpr overRange_type DEFAULT_OVER_RANGE{ 0 };

            static const units_type&
            DEFAULT_UNITS( )
            {
                static units_type retval;
                return ( retval );
            }

            /**
             * \brief Return the name associate with the FrAdcData
             * structure.
             *
             * \return
             *     The name associated with the FrAdcData structure
             */
            const name_type&
            GetName( ) const
            {
                return name;
            }

            /**
             * \brief A brief description of the FrAdcData structure
             *
             * \return
             *     A brief description of the FrAdcData structure
             */
            const comment_type&
            GetComment( ) const
            {
                return comment;
            }

            /**
             * \brief The channel group for the FrAdcData
             *
             * \return
             *     The crate number for the FrAdcData
             */
            crate_type
            GetCrate( ) const
            {
                return crate;
            }

            /**
             * \brief The channel number for the FrAdcData
             *
             * \return
             *     The channel number for the FrAdcData
             */
            channel_type
            GetChannel( ) const
            {
                return channel;
            }

            /**
             * \brief Tne number of bits in the A/D output.
             *
             * \return
             *      Tne number of bits in the A/D output.
             */
            nBits_type
            GetNBits( ) const
            {
                return nBits;
            }

            /**
             * \brief DC bias on channel.
             *
             * \return
             *     DC bias on channel.
             */
            bias_type
            GetBias( ) const
            {
                return bias;
            }

            /**
             * \brief ADC calibration units per count.
             *
             * \return
             *     ADC calibration units per count.
             */
            slope_type
            GetSlope( ) const
            {
                return slope;
            }

            /**
             * \brief The units used in the ADC calibration
             *
             * \return
             *     The units used in the ADC calibration
             */
            const units_type&
            GetUnits( ) const
            {
                return units;
            }

            /**
             * \brief The data acquisition rate.
             *
             * \return
             *     The data acquisition rate.
             */
            sampleRate_type
            GetSampleRate( ) const
            {
                return sampleRate;
            }

            /**
             * \brief The offset of the first sample relative to the frame
             * start time.
             *
             * \return
             *     The offset of the first sample relative to the frame
             *     start time.
             */
            timeOffsetS_type
            GetTimeOffsetS( ) const
            {
                return timeOffsetS;
            }

            /**
             * \brief The offset of the first sample relative to the frame
             * start time.
             *
             * \return
             *     The offset of the first sample relative to the frame
             *     start time.
             */
            timeOffsetN_type
            GetTimeOffsetN( ) const
            {
                return timeOffsetN;
            }

            /**
             * \brief The frequency in the original data corresponding to 0
             * Hz.
             *
             * \return
             *     The frequency in the original data corresponding to 0 Hz.
             */
            fShift_type
            GetFShift( ) const
            {
                return fShift;
            }

            /**
             * \brief Retrieve the overRange value.
             *
             * \return
             *     The value of the overRange field.
             */
            overRange_type
            GetOverRange( ) const
            {
                return overRange;
            }

            /**
             * \brief Identifier for vector for user-provided information.
             *
             * \return
             *     A constant reference to the user-provided information.
             */
            const aux_type&
            RefAux( ) const
            {
                return aux;
            }

            /**
             * \brief Identifier for vector for user-provided information.
             *
             * \return
             *     A reference to the user-provided information.
             */
            aux_type&
            RefAux( )
            {
                return aux;
            }

            /**
             * \brief Identifier for vector of sampled data.
             *
             * \return
             *     A constant reference to the sampled data.
             */
            const data_type&
            RefData( ) const
            {
                return data;
            }

            /**
             * \brief Identifier for vector of sampled data.
             *
             * \return
             *     A reference to the sampled data.
             */
            data_type&
            RefData( )
            {
                return data;
            }

            /**
             * \brief Extend the comment associated with the FrAdcData
             * structure.
             */
            void
            AppendComment( const std::string& Comment )
            {
                FrameCPP::Common::AppendComment( comment, Comment );
            }

            /**
             * \brief Establish the value of the overRange field.
             *
             * \param[in] Value
             *     The desired value of the overRange field.
             */
            void
            SetOverRange( overRange_type Value )
            {
                overRange = Value;
            }

            /**
             * \brief Establish the value of the bias field.
             *
             * \param[in] Value
             *     The desired value of the bias field.
             */
            void
            SetBias( bias_type Value )
            {
                bias = Value;
            }

            /**
             * \brief Establish the value of the crate field
             *
             * \param[in] Value
             *     The desired value of the crate field.
             */
            void
            SetCrate( crate_type Value )
            {
                crate = Value;
            }

            /**
             * \brief Establish the value of the channel field
             *
             * \param[in] Value
             *     The desired value of the channel field.
             */
            void
            SetChannel( channel_type Value )
            {
                channel = Value;
            }

            /**
             * \brief Set the comment associated with the FrAdcData
             * structure.
             *
             * \param[in] Value
             *     The desired value for the comment field.
             */
            void
            SetComment( const comment_type& Value )
            {
                comment = Value;
            }

            /**
             * \brief Tne number of bits in the A/D output.
             *
             * \return
             *      Tne number of bits in the A/D output.
             */
            void
            SetNBits( nBits_type Value )
            {
                nBits = Value;
            }

            /**
             * \brief Establish the value of the sampleRate field
             *
             * \param[in] Value
             *     The desired value of the sampleRate field.
             */
            void
            SetSampleRate( sampleRate_type Value )
            {
                sampleRate = Value;
            }

            /**
             * \brief Establish the value of the slope field.
             *
             * \param[in] Value
             *     The desired value of the slope field.
             */
            void
            SetSlope( slope_type Value )
            {
                slope = Value;
            }

            /**
             * \brief Establish the value of the timeOffset field.
             *
             * \param[in] Value
             *     The value for the timeOffset field.
             */
            void
            SetTimeOffsetS( timeOffsetS_type Value )
            {
                timeOffsetS = Value;
            }

            /**
             * \brief Establish the value of the timeOffset field.
             *
             * \param[in] Value
             *     The value for the timeOffset field.
             */
            void
            SetTimeOffsetN( timeOffsetN_type Value )
            {
                timeOffsetN = Value;
            }

            bool
            operator==( FrAdcData const& RHS ) const
            {
                return ( ( this == &RHS ) ||
                         ( ( name.compare( RHS.name ) == 0 ) &&
                           ( comment.compare( RHS.comment ) == 0 ) &&
                           ( crate == RHS.crate ) &&
                           ( channel == RHS.channel ) &&
                           ( nBits == RHS.nBits ) && ( bias == RHS.bias ) &&
                           ( slope == RHS.slope ) &&
                           ( units.compare( RHS.units ) == 0 ) &&
                           ( sampleRate == RHS.sampleRate ) &&
                           ( timeOffsetS == RHS.timeOffsetS ) &&
                           ( timeOffsetN == RHS.timeOffsetN ) &&
                           ( fShift == RHS.fShift ) &&
                           ( overRange == RHS.overRange ) &&
                           ( data == RHS.data ) && ( aux == RHS.aux ) ) );
            }

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
            crate_type crate;
            //-------------------------------------------------------
            /// Channel nubmer
            //-------------------------------------------------------
            channel_type channel;
            //-------------------------------------------------------
            /// Number of bits in A/D output
            //-------------------------------------------------------
            nBits_type nBits;
            //-------------------------------------------------------
            /// DC bias on channel (Units @ ADC counts = 0)
            //-------------------------------------------------------
            bias_type bias;
            //-------------------------------------------------------
            /// ADC calibration: input units/ct
            //-------------------------------------------------------
            slope_type slope;
            //-------------------------------------------------------
            /// ADC calibration: input units for slope.
            //-------------------------------------------------------
            units_type units;
            //-------------------------------------------------------
            /// Data acquisition rate, samples/s
            //-------------------------------------------------------
            sampleRate_type sampleRate;
            //-------------------------------------------------------
            /// Offset of 1st sample relative to the frame start time
            //-------------------------------------------------------
            timeOffsetS_type timeOffsetS;
            //-------------------------------------------------------
            /// Offset of 1st sample relative to the frame start time
            //-------------------------------------------------------
            timeOffsetN_type timeOffsetN;
            //-------------------------------------------------------
            /// fShift is the frequency (in Hz) in the original data
            /// that corresponds to 0 Hz in the heterodyned series.
            //-------------------------------------------------------
            fShift_type fShift;
            //-------------------------------------------------------
            /// Data valid flag
            //-------------------------------------------------------
            overRange_type overRange;
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

            void
            setName( const name_type& Value )
            {
                name = Value;
            }

        }; // class FrAdcData

    } // namespace v3
} // namespace FrameCPP

#endif /* ! defined(SWIG) */
#endif /* defined(__cplusplus) */

#endif /* FRAMECPP__STORAGE__V3__FrAdcData_HH */
