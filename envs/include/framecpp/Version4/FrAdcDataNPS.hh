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

#ifndef FrameCPP_VERSION_4_FrAdcDataNPS_HH
#define FrameCPP_VERSION_4_FrAdcDataNPS_HH

#if defined( __cplusplus )
#if !defined( SWIGIMPORTED )
#include <memory>
#include <vector>
#endif /* ! defined(SWIGIMPORTED) */

#if !defined( SWIGIMPORTED )
#include "framecpp/Common/Container.hh"
#include "framecpp/Common/Description.hh"
#include "framecpp/Common/TOCInfo.hh"

#include "framecpp/Version4/FrameSpec.hh"
#include "framecpp/Version4/Dimension.hh"
#include "framecpp/Version4/FrVect.hh"
#include "framecpp/Version4/STRING.hh"
#endif /* ! defined(SWIGIMPORTED) */
#endif /* defined(__cplusplus) */

#include "framecpp/Version3/FrAdcData.hh"

#undef FR_ADC_DATA_TIMEOFFSETS_TYPE
#define FR_ADC_DATA_TIMEOFFSETS_TYPE INT_4S

#undef FR_ADC_DATA_CHANNEL_GROUP_TYPE
#define FR_ADC_DATA_CHANNEL_GROUP_TYPE INT_4U /* Replaces crate */

#undef FR_ADC_DATA_CHANNEL_NUMBER_TYPE
#define FR_ADC_DATA_CHANNEL_NUMBER_TYPE INT_4U /* Replaces channel */

#undef FR_ADC_DATA_DATAVALID_TYPE
#define FR_ADC_DATA_DATAVALID_TYPE INT_2U /* Replaces overRange */

#if defined( __cplusplus )
#if !defined( SWIGIMPORTED )
namespace FrameCPP
{
    namespace Version_4
    {
        typedef STRING                          name_type;
        typedef STRING                          comment_type;
        typedef FR_ADC_DATA_CHANNEL_GROUP_TYPE  channel_group_type;
        typedef FR_ADC_DATA_CHANNEL_NUMBER_TYPE channel_number_type;
        typedef FR_ADC_DATA_N_BITS_TYPE         nBits_type;
        typedef FR_ADC_DATA_BIAS_TYPE           bias_type;
        typedef FR_ADC_DATA_SLOPE_TYPE          slope_type;
        typedef STRING                          units_type;
        typedef FR_ADC_DATA_SAMPLERATE_TYPE     sampleRate_type;
        typedef FR_ADC_DATA_TIMEOFFSETS_TYPE    timeOffsetS_type;
        typedef FR_ADC_DATA_TIMEOFFSETN_TYPE    timeOffsetN_type;
        typedef FR_ADC_DATA_FSHIFT_TYPE         fShift_type;
        typedef FR_ADC_DATA_DATAVALID_TYPE      dataValid_type;

        const FR_ADC_DATA_BIAS_TYPE        FR_ADC_DATA_DEFAULT_BIAS = 0.0;
        const FR_ADC_DATA_SLOPE_TYPE       FR_ADC_DATA_DEFAULT_SLOPE = 1.0;
        const FR_ADC_DATA_FSHIFT_TYPE      FR_ADC_DATA_DEFAULT_FSHIFT = 0.0;
        const FR_ADC_DATA_TIMEOFFSETS_TYPE FR_ADC_DATA_DEFAULT_TIME_OFFSET_S =
            0;
        const FR_ADC_DATA_TIMEOFFSETN_TYPE FR_ADC_DATA_DEFAULT_TIME_OFFSET_N =
            0;
        const FR_ADC_DATA_DATAVALID_TYPE FR_ADC_DATA_DEFAULT_DATA_VALID = 0;

        inline const char*
        FR_ADC_DATA_DEFAULT_UNITS( )
        {
            return "counts";
        }

        class FrAdcDataNPS
        {
        public:
            typedef STRING                          name_type;
            typedef STRING                          comment_type;
            typedef FR_ADC_DATA_CHANNEL_GROUP_TYPE  channelGroup_type;
            typedef FR_ADC_DATA_CHANNEL_NUMBER_TYPE channelNumber_type;
            typedef FR_ADC_DATA_N_BITS_TYPE         nBits_type;
            typedef FR_ADC_DATA_BIAS_TYPE           bias_type;
            typedef FR_ADC_DATA_SLOPE_TYPE          slope_type;
            typedef STRING                          units_type;
            typedef FR_ADC_DATA_SAMPLERATE_TYPE     sampleRate_type;
            typedef FR_ADC_DATA_TIMEOFFSETS_TYPE    timeOffsetS_type;
            typedef FR_ADC_DATA_TIMEOFFSETN_TYPE    timeOffsetN_type;
            typedef FR_ADC_DATA_FSHIFT_TYPE         fShift_type;
            typedef FR_ADC_DATA_DATAVALID_TYPE      dataValid_type;

            static const bias_type        DEFAULT_BIAS;
            static const slope_type       DEFAULT_SLOPE;
            static const fShift_type      DEFAULT_FSHIFT;
            static const timeOffsetS_type DEFAULT_TIME_OFFSET_S;
            static const timeOffsetN_type DEFAULT_TIME_OFFSET_N;
            static const dataValid_type   DEFAULT_DATA_VALID;

            /**
             * \brief Return the name associate with the FrAdcData structure.
             *
             * \return
             *     The name associated with the FrAdcData structure
             */
            const std::string& GetName( ) const;

            /**
             * \brief A brief description of the FrAdcData structure
             *
             * \return
             *     A brief description of the FrAdcData structure
             */
            const std::string& GetComment( ) const;

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
            dataValid_type GetDataValid( ) const;

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
            void SetDataValid( INT_2U flag );

            /**
             * \brief Establish the value of the bias field.
             *
             * \param[in] Value
             *     The desired value of the bias field.
             */
            void SetBias( REAL_4 Value );

            /**
             * \brief Establish the value of the slope field.
             *
             * \param[in] Value
             *     The desired value of the slope field.
             */
            void SetSlope( REAL_4 Value );

            /**
             * \brief Establish the value of the timeOffset field.
             *
             * \param[in] Seconds
             *     The value for the timeOffsetS field.
             * \param[in] Nanoseconds
             *     The value for the timeOffsetN field.
             */
            void SetTimeOffset( INT_4U Seconds, INT_4U Nanoseconds );

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
            channelGroup_type channelGroup;
            /**
             * Channel number
             *
             * \note
             *     This variable is determined by the site and must be
             *     unique over all detectors.
             */
            channelNumber_type channelNumber;
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
             *     dataValid = 0 -> ADC ddata valid;
             *     dataValid != 0 -> ADC data suspect/not valid
             */
            dataValid_type dataValid;

            /**
             * \brief Default constructor
             */
            FrAdcDataNPS( );

            /**
             * \brief Stream constructor
             */
            FrAdcDataNPS( Common::IStream& Stream );

            /**
             * \brief Promotion constructor
             */
            FrAdcDataNPS( const Previous::FrAdcData& Source,
                          Common::IStream*           Stream );
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

            template < typename DescriptionType, typename FrSEType >
            static void structDescription( DescriptionType& Desc );
            /**
             * \brief Comparison operator
             */
            bool operator==( const FrAdcDataNPS& RHS ) const;
        };

        inline void
        FrAdcDataNPS::AppendComment( const std::string& Comment )
        {
            FrameCPP::Common::AppendComment( comment, Comment );
        }

        inline const std::string&
        FrAdcDataNPS::GetComment( ) const
        {
            return comment;
        }

        inline FrAdcDataNPS::channelNumber_type
        FrAdcDataNPS::GetChannelNumber( ) const
        {
            return channelNumber;
        }

        inline FrAdcDataNPS::channelGroup_type
        FrAdcDataNPS::GetChannelGroup( ) const
        {
            return channelGroup;
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

        inline STRING
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

        inline INT_2U
        FrAdcDataNPS::GetDataValid( ) const
        {
            return dataValid;
        }

        inline void
        FrAdcDataNPS::SetDataValid( INT_2U flag )
        {
            dataValid = flag;
        }

        inline void
        FrAdcDataNPS::SetBias( REAL_4 Value )
        {
            bias = Value;
        }

        inline void
        FrAdcDataNPS::SetSlope( REAL_4 Value )
        {
            slope = Value;
        }

        inline void
        FrAdcDataNPS::SetTimeOffset( INT_4U Seconds, INT_4U Nanoseconds )
        {
            timeOffsetS = Seconds;
            timeOffsetN = Nanoseconds;
        }

        inline cmn_streamsize_type
        FrAdcDataNPS::bytes( const Common::StreamBase& Stream ) const
        {
            return name.Bytes( ) + comment.Bytes( ) + sizeof( channelGroup ) +
                sizeof( channelNumber ) + sizeof( nBits ) + sizeof( bias ) +
                sizeof( slope ) + units.Bytes( ) + sizeof( sampleRate ) +
                sizeof( timeOffsetS ) + sizeof( timeOffsetN ) +
                sizeof( fShift ) + sizeof( dataValid );
        }

        template < typename DescriptionType, typename FrSEType >
        inline void
        FrAdcDataNPS::structDescription( DescriptionType& Desc )
        {
            Desc( FrSEType(
                "name", Common::Description::Ascii< name_type >( ), "" ) );
            Desc( FrSEType( "comment",
                            Common::Description::Ascii< comment_type >( ),
                            "" ) );
            Desc( FrSEType( "channelGroup",
                            Common::Description::Ascii< channelGroup_type >( ),
                            "" ) );
            Desc( FrSEType( "channelNumber",
                            Common::Description::Ascii< channelNumber_type >( ),
                            "" ) );
            Desc( FrSEType(
                "nBits", Common::Description::Ascii< nBits_type >( ), "" ) );
            Desc( FrSEType(
                "bias", Common::Description::Ascii< bias_type >( ), "" ) );
            Desc( FrSEType(
                "slope", Common::Description::Ascii< slope_type >( ), "" ) );
            Desc( FrSEType(
                "units", Common::Description::Ascii< units_type >( ), "" ) );
            Desc( FrSEType( "sampleRate",
                            Common::Description::Ascii< sampleRate_type >( ),
                            "" ) );
            Desc( FrSEType( "timeOffsetS",
                            Common::Description::Ascii< timeOffsetS_type >( ),
                            "" ) );
            Desc( FrSEType( "timeOffsetN",
                            Common::Description::Ascii< timeOffsetN_type >( ),
                            "" ) );
            Desc( FrSEType(
                "fShift", Common::Description::Ascii< fShift_type >( ), "" ) );
            Desc( FrSEType( "dataValid",
                            Common::Description::Ascii< dataValid_type >( ),
                            "" ) );
        }

        inline bool
        FrAdcDataNPS::operator==( const FrAdcDataNPS& RHS ) const
        {
            return ( ( this == &RHS ) ||
                     ( ( name == RHS.name ) && ( comment == RHS.comment ) &&
                       ( channelGroup == RHS.channelGroup ) &&
                       ( channelNumber == RHS.channelNumber ) &&
                       ( nBits == RHS.nBits ) && ( bias == RHS.bias ) &&
                       ( slope == RHS.slope ) && ( units == RHS.units ) &&
                       ( sampleRate == RHS.sampleRate ) &&
                       ( timeOffsetS == RHS.timeOffsetS ) &&
                       ( timeOffsetN == RHS.timeOffsetN ) &&
                       ( fShift == RHS.fShift ) &&
                       ( dataValid == RHS.dataValid ) ) );
        }
    } /* namespace Version_4 */
} /* namespace FrameCPP */
#endif /* defined(__cplusplus) */
#endif /* ! defined(SWIGIMPORTED) */
#endif /* FrameCPP_VERSION_4_FrAdcDataNPS_HH */
