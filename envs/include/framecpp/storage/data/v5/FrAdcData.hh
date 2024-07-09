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

#ifndef FRAMECPP__STORAGE__V5__FrAdcData_HH
#define FRAMECPP__STORAGE__V5__FrAdcData_HH

#if defined( __cplusplus )
#if !defined( SWIG )
#include "ldastoolsal/types.hh"

#include "framecpp/Common/Container.hh"

#endif /* ! defined(SWIG) */
#endif /* defined(__cplusplus) */

#undef FR_ADC_DATA_TIME_OFFSET_S_TYPE
#undef FR_ADC_DATA_TIME_OFFSET_N_TYPE

#undef FR_ADC_DATA_TIME_OFFSET_TYPE
#define FR_ADC_DATA_TIME_OFFSET_TYPE REAL_8

#undef FR_ADC_DATA_PHASE_TYPE
#define FR_ADC_DATA_PHASE_TYPE REAL_4

#if defined( __cplusplus )
#if !defined( SWIG )

namespace FrameCPP
{
    namespace v5
    {
        template < typename DATA_TYPE_T, typename AUX_TYPE_T >
        class FrAdcData
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
            static constexpr timeOffset_type DEFAULT_TIME_OFFSET{ 0 };
            static constexpr dataValid_type DEFAULT_DATA_VALID{ 0 };
            static constexpr phase_type DEFAULT_PHASE{ 0 };

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
            channelGroup_type
            GetChannelGroup( ) const
            {
                return channelGroup;
            }

            /**
             * \brief The channel number for the FrAdcData
             *
             * \return
             *     The channel number for the FrAdcData
             */
            channelNumber_type
            GetChannelNumber( ) const
            {
                return channelNumber;
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
            timeOffset_type
            GetTimeOffset( ) const
            {
                return timeOffset;
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
             * \brief Phase of hetrodyning signal at start of dataset.
             *
             * \return
             * 	The Phase (in radians) of hetrodyning signal at
             *	start of dataset.
             */
            phase_type
            GetPhase( ) const
            {
                return phase;
            }

            /**
             * \brief Retrieve the overRange value.
             *
             * \return
             *     The value of the overRange field.
             */
            dataValid_type
            GetDataValid( ) const
            {
                return dataValid;
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
             * \brief Establish the value of the dataValid field.
             *
             * \param[in] Value
             *     The desired value of the overRange field.
             */
            void
            SetDataValid( dataValid_type Value )
            {
                dataValid = Value;
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
             * \brief Establish the value of the channelGroup field
             *
             * \param[in] Value
             *     The desired value of the channelGroup field.
             */
            void
            SetChannelGroup( channelGroup_type Value )
            {
                channelGroup = Value;
            }

            /**
             * \brief Establish the value of the channelNumber field
             *
             * \param[in] Value
             *     The desired value of the channelNumber field.
             */
            void
            SetChannelNumber( channelNumber_type Value )
            {
                channelNumber = Value;
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
            void SetTimeOffset( timeOffset_type Value )
            {
                timeOffset = Value;
            }

            bool
            operator==( FrAdcData const& RHS ) const
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
            timeOffset_type timeOffset;
            //-------------------------------------------------------
            /// fShift is the frequency (in Hz) in the original data
            /// that corresponds to 0 Hz in the heterodyned series.
            //-------------------------------------------------------
            fShift_type fShift;
            //-------------------------------------------------------
            /// Phase (in radian) of hetrodyning signal at start
            /// of dataset
            //-------------------------------------------------------
            phase_type phase;
            //-------------------------------------------------------
            /// Data valid flag
            //-------------------------------------------------------
            dataValid_type dataValid;
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
            incrementTimeOffset( timeOffset_type Value )
            {
                timeOffset += Value;
            }

            void
            setName( const name_type& Value )
            {
                name = Value;
            }

        }; // class FrAdcData

    } // namespace v5
} // namespace FrameCPP

#endif /* ! defined(SWIG) */
#endif /* defined(__cplusplus) */

#endif /* FRAMECPP__STORAGE__V5__FrAdcData_HH */
