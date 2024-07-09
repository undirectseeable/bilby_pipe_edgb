/*
 * LDASTools frameCPP - A library implementing the LIGO/Virgo frame
 * specification
 *
 * Copyright (C) 2018 California Institute of Technology
 *
 * LDASTools frameCPP is free software; you may redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 (GPLv2) of the
 * License or at your discretion, any later version.
 *
 * LDASTools frameCPP is distributed in the hope that it will be useful, but
 * without any warranty or even the implied warranty of merchantability
 * or fitness for a particular purpose. See the GNU General Public
 * License (GPLv2) for more details.
 *
 * Neither the names of the California Institute of Technology (Caltech),
 * The Massachusetts Institute of Technology (M.I.T), The Laser
 * Interferometer Gravitational-Wave Observatory (LIGO), nor the names
 * of its contributors may be used to endorse or promote products derived
 * from this software without specific prior written permission.
 *
 * You should have received a copy of the licensing terms for this
 * software included in the file LICENSE located in the top-level
 * directory of this package. If you did not, you can view a copy at
 * http://dcc.ligo.org/M1500244/LICENSE
 */

#ifndef FrameCPP_VERSION_3_FrAdcDataNPS_HH
#define FrameCPP_VERSION_3_FrAdcDataNPS_HH

#if defined( __cplusplus )
#if !defined( SWIGIMPORTED )
#include <memory>
#include <vector>
#endif /* ! defined(SWIGIMPORTED) */

#if !defined( SWIGIMPORTED )
#include "framecpp/Common/Container.hh"

#include "framecpp/Version3/FrameSpec.hh"
#include "framecpp/Version3/Dimension.hh"
#include "framecpp/Version3/FrVect.hh"
#include "framecpp/Version3/STRING.hh"
#endif /* ! defined(SWIGIMPORTED) */
#endif /* defined(__cplusplus) */

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

#undef FR_ADC_DATA_SAMPLERATE_TYPE
#define FR_ADC_DATA_SAMPLERATE_TYPE REAL_8

#undef FR_ADC_DATA_TIMEOFFSETS_TYPE
#define FR_ADC_DATA_TIMEOFFSETS_TYPE INT_4U

#undef FR_ADC_DATA_TIMEOFFSETN_TYPE
#define FR_ADC_DATA_TIMEOFFSETN_TYPE INT_4U

#undef FR_ADC_DATA_FSHIFT_TYPE
#define FR_ADC_DATA_FSHIFT_TYPE REAL_8

#undef FR_ADC_DATA_OVERRANGE_TYPE
#define FR_ADC_DATA_OVERRANGE_TYPE INT_2U

#if defined( __cplusplus )
#if !defined( SWIGIMPORTED )
namespace FrameCPP
{
    namespace Version_3
    {
        const FR_ADC_DATA_BIAS_TYPE        FR_ADC_DATA_DEFAULT_BIAS = 0.0;
        const FR_ADC_DATA_SLOPE_TYPE       FR_ADC_DATA_DEFAULT_SLOPE = 1.0;
        const FR_ADC_DATA_FSHIFT_TYPE      FR_ADC_DATA_DEFAULT_FSHIFT = 0.0;
        const FR_ADC_DATA_TIMEOFFSETS_TYPE FR_ADC_DATA_DEFAULT_TIME_OFFSET_S =
            0;
        const FR_ADC_DATA_TIMEOFFSETN_TYPE FR_ADC_DATA_DEFAULT_TIME_OFFSET_N =
            0;
        const FR_ADC_DATA_OVERRANGE_TYPE FR_ADC_DATA_DEFAULT_OVER_RANGE = 0;
        inline const char*
        FR_ADC_DATA_DEFAULT_UNITS( )
        {
            return "counts";
        }

#define FR_ADC_DATA_NPS_NAMESPACE Version_3

        /**
         * \brief ADC Data that does not reference a pointer
         */
        class FrAdcDataNPS
        {
        public:
            typedef STRING                       name_type;
            typedef STRING                       comment_type;
            typedef FR_ADC_DATA_CRATE_TYPE       crate_type;
            typedef FR_ADC_DATA_CHANNEL_TYPE     channel_type;
            typedef FR_ADC_DATA_N_BITS_TYPE      nBits_type;
            typedef FR_ADC_DATA_BIAS_TYPE        bias_type;
            typedef FR_ADC_DATA_SLOPE_TYPE       slope_type;
            typedef STRING                       units_type;
            typedef FR_ADC_DATA_SAMPLERATE_TYPE  sampleRate_type;
            typedef FR_ADC_DATA_TIMEOFFSETS_TYPE timeOffsetS_type;
            typedef FR_ADC_DATA_TIMEOFFSETN_TYPE timeOffsetN_type;
            typedef FR_ADC_DATA_FSHIFT_TYPE      fShift_type;
            typedef FR_ADC_DATA_OVERRANGE_TYPE   overRange_type;

            static const bias_type        DEFAULT_BIAS;
            static const slope_type       DEFAULT_SLOPE;
            static const fShift_type      DEFAULT_FSHIFT;
            static const timeOffsetS_type DEFAULT_TIME_OFFSET_S;
            static const timeOffsetN_type DEFAULT_TIME_OFFSET_N;
            static const overRange_type   DEFAULT_OVER_RANGE;

            /**
             * \brief Extend the comment associated with the FrAdcData
             * structure.
             */
            void AppendComment( const comment_type& Comment );

            /**
             * \brief Return the name associate with the FrAdcData structure.
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
             * \brief The channel number for the FrAdcData
             *
             * \return
             *     The channel number for the FrAdcData
             */
            channel_type GetChannel( ) const;

            /**
             * \brief The crate number for the FrAdcData
             *
             * \return
             *     The crate number for the FrAdcData
             */
            crate_type GetCrate( ) const;

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
            STRING GetUnits( ) const;

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
            timeOffsetS_type GetTimeOffsetS( ) const;

            /**
             * \brief The offset of the first sample relative to the frame
             * start time.
             *
             * \return
             *     The offset of the first sample relative to the frame
             *     start time.
             */
            timeOffsetN_type GetTimeOffsetN( ) const;

            /**
             * \brief The frequency in the original data corresponding to 0 Hz.
             *
             * \return
             *     The frequency in the original data corresponding to 0 Hz.
             */
            fShift_type GetFShift( ) const;

            /**
             * \brief Retrieve the overRange value.
             *
             * \return
             *     The value of the overRange field.
             */
            overRange_type GetOverRange( ) const;

            /**
             * \brief Set the numeric crate id for the channel
             */
            void SetCrate( crate_type Value );

            /**
             * \brief Set the numeric id for the channel
             */
            void SetChannel( channel_type Value );

            /**
             * \brief Set the comment associated with the FrAdcData structure.
             */
            void SetComment( const comment_type& comment );

            /**
             * \brief Establish the value of the overRange field.
             *
             * \param[in] flag
             *     The desired value of the overRange field.
             */
            void SetOverRange( overRange_type flag );

            /**
             * \brief Establish the value of the bias field.
             *
             * \param[in] bias
             *     The desired value of the bias field.
             */
            void SetBias( bias_type bias );

            /**
             * \brief The number of bits in the A/D output.
             *
             * \param[in] NBits
             *      Tne number of bits in the A/D output.
             */
            void SetNBits( nBits_type NBits );

            /**
             * \brief Establish the value of the sampleRate field.
             *
             * \param[in] SampleRate
             *     The desired value of the sampleRate field.
             */
            void SetSampleRate( sampleRate_type SampleRate );

            /**
             * \brief Establish the value of the slope field.
             *
             * \param[in] slope
             *     The desired value of the slope field.
             */
            void SetSlope( slope_type slope );

            /**
             * \brief Establish the value of the timeOffset field.
             */
            void SetTimeOffset( timeOffsetS_type Seconds,
                                timeOffsetN_type Nanoseconds );
            /**
             * \brief Establish the value of the timeOffset field.
             *
             * \param[in] time
             *     The desired value of the timeOffset field.
             */
            void SetTimeOffsetS( timeOffsetS_type time );

            /**
             * \brief Establish the value of the timeOffset field.
             *
             * \param[in] time
             *     The desired value of the timeOffset field.
             */
            void SetTimeOffsetN( timeOffsetN_type time );

        protected:
            /**
             * Channel name  -- must be unique with the frame
             */
            name_type name;
            /**
             * Comment for the ADC.
             */
            comment_type comment;
            /**
             * Channel grouping number containing ADC.
             *
             * \note
             *     This variable is determined by the site and must be
             *     unique over all detectors.
             */
            crate_type crate;
            /**
             * Channel number
             *
             * \note
             *     This variable is determined by the site and must be
             *     unique over all detectors.
             */
            channel_type channel;
            /**
             * Number of bits in A/D output.
             */
            nBits_type nBits;
            /**
             * DC bias on channel (Units @ ADC counts = 0)
             */
            bias_type bias;
            /**
             * ADC calibration: input units/count.
             */
            slope_type slope;
            /**
             * ADC calibration: input units for slope
             * If dimensionless, then units == \<NONE\>, in CAPITALS
             * (without \<...\>).
             */
            units_type units;
            /**
             * Data acquisition rate, samples per second.
             */
            sampleRate_type sampleRate;
            /**
             * For Triggered data lasting less than one frame, integer
             * seconds start time relative to frame start
             */
            timeOffsetS_type timeOffsetS;
            /**
             * For Triggered data lasting less than one frame, integer
             * residual nanoseconds start time relative to frame start
             */
            timeOffsetN_type timeOffsetN;
            /**
             * The frequency (in HZ) in the original data that corresponds
             * to zero Hz in the heterodyned series.
             *
             * \note
             *     In the heterodyning process the real time series in
             *     multiplied by cos[2pi fShift(t-to) + phase] to get
             *     the real part and by -sin[2pi fShift(t-t(0)) + phase] to
             *     get the imaginary part of the resulting complex time
             *     series.
             *     The time origin t(0) is the beginning of the frame.
             */
            fShift_type fShift;
            /**
             * Data valid flag
             *
             * \note
             *     overRange = 0 -> ADC ddata valid;
             *     overRange != 0 -> ADC data suspect/not valid
             */
            overRange_type overRange;

            /**
             * \brief Default constructor
             */
            FrAdcDataNPS( );

            /**
             * \brief Initialzie the instance from an input stream
             */
            FrAdcDataNPS( Common::IStream& Stream );

            /**
             * \brief Number of bytes needed to write this structure
             *
             * \param[in] Stream
             *     The stream from which to the object is being read or
             *     written.
             *
             * \return
             *     The number of bytes need to read or write this object.
             */
            cmn_streamsize_type bytes( const Common::StreamBase& Stream ) const;

            /**
             * \brief Write contents to the stream
             */
            void write( Common::OStream& Stream ) const;

            /**
             * \brief Comparison operator
             */
            bool operator==( const FrAdcDataNPS& RHS ) const;
        };

        inline void
        FrAdcDataNPS::AppendComment( const comment_type& Comment )
        {
            FrameCPP::Common::AppendComment( comment, Comment );
        }

        inline cmn_streamsize_type
        FrAdcDataNPS::bytes( const Common::StreamBase& Stream ) const
        {
            return name.Bytes( ) + comment.Bytes( ) + sizeof( crate ) +
                sizeof( channel ) + sizeof( nBits ) + sizeof( bias ) +
                sizeof( slope ) + units.Bytes( ) + sizeof( sampleRate ) +
                sizeof( timeOffsetS ) + sizeof( timeOffsetN ) +
                sizeof( fShift ) + sizeof( overRange );
        }

        inline const FrAdcDataNPS::name_type&
        FrAdcDataNPS::GetName( ) const
        {
            return name;
        }

        inline const FrAdcDataNPS::comment_type&
        FrAdcDataNPS::GetComment( ) const
        {
            return comment;
        }

        inline FrAdcDataNPS::channel_type
        FrAdcDataNPS::GetChannel( ) const
        {
            return channel;
        }

        inline FrAdcDataNPS::crate_type
        FrAdcDataNPS::GetCrate( ) const
        {
            return crate;
        }

        inline FrAdcDataNPS::nBits_type
        FrAdcDataNPS::GetNBits( ) const
        {
            return nBits;
        }

        inline FrAdcDataNPS::bias_type
        FrAdcDataNPS::GetBias( ) const
        {
            return bias;
        }

        inline FrAdcDataNPS::slope_type
        FrAdcDataNPS::GetSlope( ) const
        {
            return slope;
        }

        inline FrAdcDataNPS::units_type
        FrAdcDataNPS::GetUnits( ) const
        {
            return units;
        }

        inline FrAdcDataNPS::sampleRate_type
        FrAdcDataNPS::GetSampleRate( ) const
        {
            return sampleRate;
        }

        inline FrAdcDataNPS::timeOffsetS_type
        FrAdcDataNPS::GetTimeOffsetS( ) const
        {
            return timeOffsetS;
        }

        inline FrAdcDataNPS::timeOffsetN_type
        FrAdcDataNPS::GetTimeOffsetN( ) const
        {
            return timeOffsetN;
        }

        inline FrAdcDataNPS::fShift_type
        FrAdcDataNPS::GetFShift( ) const
        {
            return fShift;
        }

        inline FrAdcDataNPS::overRange_type
        FrAdcDataNPS::GetOverRange( ) const
        {
            return overRange;
        }

        inline void
        FrAdcDataNPS::SetOverRange( overRange_type OverRange )
        {
            overRange = OverRange;
        }

        inline void
        FrAdcDataNPS::SetBias( bias_type Bias )
        {
            bias = Bias;
        }

        inline void
        FrAdcDataNPS::SetNBits( nBits_type NBits )
        {
            nBits = NBits;
        }

        inline void
        FrAdcDataNPS::SetSampleRate( sampleRate_type SampleRate )
        {
            sampleRate = SampleRate;
#if WORKING
            /**
             * \todo
             * Modifications to the sample rate need also be reflected in the
             * corrisponding FrVect structures.
             */
            for ( data_type::iterator cur = RefData( ).begin( ),
                                      last = RefData( ).end( );
                  cur != last;
                  ++cur )
            {
                cur->
            }
#endif /* WORKING */
        }

        inline void
        FrAdcDataNPS::SetSlope( slope_type Slope )
        {
            slope = Slope;
        }

        inline void
        FrAdcDataNPS::SetTimeOffset( timeOffsetS_type Seconds,
                                     timeOffsetN_type Nanoseconds )
        {
            timeOffsetS = Seconds;
            timeOffsetN = Nanoseconds;
        }

        inline void
        FrAdcDataNPS::SetTimeOffsetS( timeOffsetS_type TimeOffsetS )
        {
            timeOffsetS = TimeOffsetS;
        }

        inline void
        FrAdcDataNPS::SetTimeOffsetN( timeOffsetN_type TimeOffsetN )
        {
            timeOffsetN = TimeOffsetN;
        }

        inline void
        FrAdcDataNPS::SetCrate( crate_type Value )
        {
            crate = Value;
        }

        inline void
        FrAdcDataNPS::SetChannel( channel_type Value )
        {
            channel = Value;
        }

        inline void
        FrAdcDataNPS::SetComment( const comment_type& Comment )
        {
            comment = Comment;
        }

        inline bool
        FrAdcDataNPS::operator==( const FrAdcDataNPS& RHS ) const
        {
#if LM_INFO
#define LM_INFO_CHECK( a )                                                     \
    if ( !( a == RHS.a ) )                                                     \
    {                                                                          \
        std::cerr << "DEBUG: Comparison of " << #a << " failed" << std::endl;  \
    }

            LM_INFO_CHECK( name );
            LM_INFO_CHECK( comment );
            LM_INFO_CHECK( channelGroup );
            LM_INFO_CHECK( channelNumber );
            LM_INFO_CHECK( nBits );
            LM_INFO_CHECK( bias );
            LM_INFO_CHECK( slope );
            LM_INFO_CHECK( units );
            LM_INFO_CHECK( fShift );
            LM_INFO_CHECK( timeOffset );
            LM_INFO_CHECK( dataValid );
            LM_INFO_CHECK( phase );
            LM_INFO_CHECK( data );
            LM_INFO_CHECK( aux );
#undef LM_INFO_CHECK
#endif /* LM_INFO */

            return ( ( this == &RHS ) ||
                     ( ( name == RHS.name ) && ( comment == RHS.comment ) &&
                       ( crate == RHS.crate ) && ( channel == RHS.channel ) &&
                       ( nBits == RHS.nBits ) &&
                       ( sampleRate == RHS.sampleRate ) &&
                       ( bias == RHS.bias ) && ( slope == RHS.slope ) &&
                       ( units == RHS.units ) && ( fShift == RHS.fShift ) &&
                       ( timeOffsetS == RHS.timeOffsetS ) &&
                       ( timeOffsetN == RHS.timeOffsetN ) &&
                       ( overRange == RHS.overRange ) ) );
        }

    } /* namespace Version_3 */
} /* namespace FrameCPP */
#endif /* ! defined(SWIGIMPORTED) */

#endif /* defined(__cplusplus) */

#endif /* FrameCPP_VERSION_3_FrAdcDataNPS_HH */
