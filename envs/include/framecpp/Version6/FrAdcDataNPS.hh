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

#ifndef FrameCPP_VERSION_6_FrAdcDataNPS_HH
#define FrameCPP_VERSION_6_FrAdcDataNPS_HH

#if defined( __cplusplus )
#if !defined( SWIGIMPORTED )
#include <memory>
#include <vector>
#endif /* ! defined(SWIGIMPORTED) */

#if !defined( SWIGIMPORTED )
#include "framecpp/Common/Container.hh"
#include "framecpp/Common/Description.hh"
#include "framecpp/Common/TOCInfo.hh"

#include "framecpp/Version6/FrameSpec.hh"
#include "framecpp/Version6/Dimension.hh"
#include "framecpp/Version6/FrVect.hh"
#include "framecpp/Version6/STRING.hh"
#endif /* ! defined(SWIGIMPORTED) */
#endif /* defined(__cplusplus) */

#include "framecpp/Version4/FrAdcData.hh"

/* ----------------------------------------------------------------------
 Replaces timeOffsetS and timeOffsetN
 ---------------------------------------------------------------------- */
#undef FR_ADC_DATA_TIMEOFFSET_TYPE
#define FR_ADC_DATA_TIMEOFFSET_TYPE REAL_8

#undef FR_ADC_DATA_PHASE_TYPE
#define FR_ADC_DATA_PHASE_TYPE REAL_4 /* new */

#if defined( __cplusplus )
#if !defined( SWIGIMPORTED )
namespace FrameCPP
{
    namespace Version_6
    {

#undef FR_ADC_DATA_NPS_NAMESPACE
#define FR_ADC_DATA_NPS_NAMESPACE Version_6

        typedef STRING                          name_type;
        typedef STRING                          comment_type;
        typedef FR_ADC_DATA_CHANNEL_GROUP_TYPE  channel_group_type;
        typedef FR_ADC_DATA_CHANNEL_NUMBER_TYPE channel_number_type;
        typedef FR_ADC_DATA_N_BITS_TYPE         nBits_type;
        typedef FR_ADC_DATA_BIAS_TYPE           bias_type;
        typedef FR_ADC_DATA_SLOPE_TYPE          slope_type;
        typedef STRING                          units_type;
        typedef FR_ADC_DATA_SAMPLERATE_TYPE     sampleRate_type;
        typedef FR_ADC_DATA_TIMEOFFSET_TYPE     timeOffset_type;
        typedef FR_ADC_DATA_FSHIFT_TYPE         fShift_type;
        typedef FR_ADC_DATA_PHASE_TYPE          phase_type;
        typedef FR_ADC_DATA_DATAVALID_TYPE      dataValid_type;

        const FR_ADC_DATA_CHANNEL_GROUP_TYPE FR_ADC_DATA_DEFAULT_CHANNEL_GROUP =
            0;
        const FR_ADC_DATA_CHANNEL_NUMBER_TYPE
                                      FR_ADC_DATA_DEFAULT_CHANNEL_NUMBER = 0;
        const FR_ADC_DATA_N_BITS_TYPE FR_ADC_DATA_DEFAULT_NBITS = 0;
        const FR_ADC_DATA_BIAS_TYPE   FR_ADC_DATA_DEFAULT_BIAS = 0.0;
        const FR_ADC_DATA_SLOPE_TYPE  FR_ADC_DATA_DEFAULT_SLOPE = 1.0;
        const FR_ADC_DATA_FSHIFT_TYPE FR_ADC_DATA_DEFAULT_SAMPLE_RATE = -1.0;
        const FR_ADC_DATA_FSHIFT_TYPE FR_ADC_DATA_DEFAULT_FSHIFT = 0.0;
        const FR_ADC_DATA_TIMEOFFSET_TYPE FR_ADC_DATA_DEFAULT_TIME_OFFSET = 0.0;
        const FR_ADC_DATA_PHASE_TYPE      FR_ADC_DATA_DEFAULT_PHASE = 0.0;
        const FR_ADC_DATA_DATAVALID_TYPE  FR_ADC_DATA_DEFAULT_DATA_VALID = 0;

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
            typedef FR_ADC_DATA_TIMEOFFSET_TYPE     timeOffset_type;
            typedef FR_ADC_DATA_FSHIFT_TYPE         fShift_type;
            typedef FR_ADC_DATA_PHASE_TYPE          phase_type;
            typedef FR_ADC_DATA_DATAVALID_TYPE      dataValid_type;

            static const bias_type       DEFAULT_BIAS;
            static const slope_type      DEFAULT_SLOPE;
            static const fShift_type     DEFAULT_FSHIFT;
            static const timeOffset_type DEFAULT_TIME_OFFSET;
            static const phase_type      DEFAULT_PHASE;
            static const dataValid_type  DEFAULT_DATA_VALID;

            static units_type DEFAULT_UNITS( );

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
             * \brief The frequency in the original data corresponding to 0 Hz.
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
             * \brief Set the comment associated with the FrAdcData structure.
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

        protected:
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
            FrAdcDataNPS( const FrAdcDataNPS& Source, Common::IStream* Stream );

            /**
             * \brief Stream copy constructor
             */
            FrAdcDataNPS( const Previous::FrAdcData& Source,
                          Common::IStream*           Stream );

            /**
             * \brief Constructor
             */
            FrAdcDataNPS( const name_type&   Name,
                          channelGroup_type  Group,
                          channelNumber_type Channel,
                          nBits_type         NBits,
                          sampleRate_type    SampleRate,
                          bias_type          Bias,
                          slope_type         Slope,
                          const units_type&  Units,
                          fShift_type        FShift,
                          timeOffset_type    TimeOffset,
                          dataValid_type     DataValid,
                          phase_type         Phase );

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

            void copyCore( const FrAdcDataNPS& Source );

            /**
             * \brief Increment the time offset by the specified value.
             *
             * \param[in] Value
             *     The amount of time by which to adjust the timeOffset value.
             */
            void incrementTimeOffset( timeOffset_type Value );

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

        protected:
            inline void
            setName( const std::string& Name )
            {
                name = Name;
            }

        private:
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
             * Offfset of 1st sample relative to the frame start time.
             */
            timeOffset_type timeOffset;
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
             * Phase (in radian) of heterodyning signal at start of dataset.
             *
             * \note
             *     In the heterodyning process the real time series in
             *     multiplied by cos[2pi fShift(t-to) + phase] to get
             *     the real part and by -sin[2pi fShift(t-t(0)) + phase] to
             *     get the imaginary part of the resulting complex time
             *     series.
             *     The time origin t(0) is the beginning of the frame.
             */
            phase_type phase;
            /**
             * Data valid flag
             *
             * \note
             *     dataValid = 0 -> ADC data valid;
             *     dataValid != 0 -> ADC data suspect/not valid
             */
            dataValid_type dataValid;
        };

        inline FrAdcDataNPS::FrAdcDataNPS( )
            : name( "" ), channelGroup( FR_ADC_DATA_DEFAULT_CHANNEL_GROUP ),
              channelNumber( FR_ADC_DATA_DEFAULT_CHANNEL_NUMBER ),
              bias( DEFAULT_BIAS ), slope( DEFAULT_SLOPE ),
              units( FR_ADC_DATA_DEFAULT_UNITS( ) ),
              sampleRate( FR_ADC_DATA_DEFAULT_SAMPLE_RATE ),
              timeOffset( DEFAULT_TIME_OFFSET ), fShift( DEFAULT_FSHIFT ),
              phase( DEFAULT_PHASE ), dataValid( DEFAULT_DATA_VALID )
        {
        }

        inline FrAdcDataNPS::FrAdcDataNPS( const name_type&   Name,
                                           channelGroup_type  Group,
                                           channelNumber_type Channel,
                                           nBits_type         NBits,
                                           sampleRate_type    SampleRate,
                                           bias_type          Bias,
                                           slope_type         Slope,
                                           const units_type&  Units,
                                           fShift_type        FShift,
                                           timeOffset_type    TimeOffset,
                                           dataValid_type     DataValid,
                                           phase_type         Phase )
            : name( Name ), channelGroup( Group ), channelNumber( Channel ),
              nBits( NBits ), bias( Bias ), slope( Slope ), units( Units ),
              sampleRate( SampleRate ), timeOffset( TimeOffset ),
              fShift( FShift ), phase( Phase ), dataValid( DataValid )
        {
        }

        inline FrAdcDataNPS::FrAdcDataNPS( const Previous::FrAdcData& Source,
                                           Common::IStream*           Stream )
            : name( Source.GetName( ) ), comment( Source.GetComment( ) ),
              channelGroup( Source.GetChannelGroup( ) ),
              channelNumber( Source.GetChannelNumber( ) ),
              nBits( Source.GetNBits( ) ), bias( Source.GetBias( ) ),
              slope( Source.GetSlope( ) ), units( Source.GetUnits( ) ),
              sampleRate( Source.GetSampleRate( ) ),
              timeOffset( REAL_8( Source.GetTimeOffsetS( ) ) +
                          REAL_8( Source.GetTimeOffsetN( ) ) * NANOSECOND ),
              fShift( Source.GetFShift( ) ), phase( DEFAULT_PHASE ),
              dataValid( Source.GetDataValid( ) )
        {
        }

        inline FrAdcDataNPS::FrAdcDataNPS( const FrAdcDataNPS& Source,
                                           Common::IStream*    Stream )
            : name( Source.GetName( ) ), comment( Source.GetComment( ) ),
              channelGroup( Source.GetChannelGroup( ) ),
              channelNumber( Source.GetChannelNumber( ) ),
              nBits( Source.GetNBits( ) ), bias( Source.GetBias( ) ),
              slope( Source.GetSlope( ) ), units( Source.GetUnits( ) ),
              sampleRate( Source.GetSampleRate( ) ),
              timeOffset( Source.GetTimeOffset( ) ),
              fShift( Source.GetFShift( ) ), phase( Source.GetPhase( ) ),
              dataValid( Source.GetDataValid( ) )
        {
        }

        inline FrAdcDataNPS::units_type
        FrAdcDataNPS::DEFAULT_UNITS( )
        {
            return FR_ADC_DATA_DEFAULT_UNITS( );
        }

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

        inline INT_4U
        FrAdcDataNPS::GetChannelGroup( ) const
        {
            return channelGroup;
        }

        inline const std::string&
        FrAdcDataNPS::GetName( ) const
        {
            return name;
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

        inline const FrAdcDataNPS::units_type&
        FrAdcDataNPS::GetUnits( ) const
        {
            return units;
        }

        inline FrAdcDataNPS::sampleRate_type
        FrAdcDataNPS::GetSampleRate( ) const
        {
            return sampleRate;
        }

        inline FrAdcDataNPS::timeOffset_type
        FrAdcDataNPS::GetTimeOffset( ) const
        {
            return timeOffset;
        }

        inline FrAdcDataNPS::fShift_type
        FrAdcDataNPS::GetFShift( ) const
        {
            return fShift;
        }

        inline FrAdcDataNPS::phase_type
        FrAdcDataNPS::GetPhase( ) const
        {
            return phase;
        }

        inline FrAdcDataNPS::dataValid_type
        FrAdcDataNPS::GetDataValid( ) const
        {
            return dataValid;
        }

        inline void
        FrAdcDataNPS::SetDataValid( dataValid_type Value )
        {
            dataValid = Value;
        }

        inline void
        FrAdcDataNPS::SetBias( bias_type Value )
        {
            bias = Value;
        }

        inline void
        FrAdcDataNPS::SetChannelGroup( channelGroup_type Value )
        {
            channelGroup = Value;
        }

        inline void
        FrAdcDataNPS::SetChannelNumber( channelNumber_type Value )
        {
            channelNumber = Value;
        }

        inline void
        FrAdcDataNPS::SetComment( const comment_type& Value )
        {
            comment = Value;
        }

        inline void
        FrAdcDataNPS::SetNBits( nBits_type Value )
        {
            nBits = Value;
        }

        inline void
        FrAdcDataNPS::SetSampleRate( sampleRate_type Value )
        {
            sampleRate = Value;
        }

        inline void
        FrAdcDataNPS::SetSlope( slope_type Value )
        {
            slope = Value;
        }

        inline void
        FrAdcDataNPS::SetTimeOffset( timeOffset_type Value )
        {
            timeOffset = Value;
        }

        inline cmn_streamsize_type
        FrAdcDataNPS::bytes( const Common::StreamBase& Stream ) const
        {
            return name.Bytes( ) + comment.Bytes( ) + sizeof( channelGroup ) +
                sizeof( channelNumber ) + sizeof( nBits ) + sizeof( bias ) +
                sizeof( slope ) + units.Bytes( ) + sizeof( sampleRate ) +
                sizeof( timeOffset ) + sizeof( fShift ) + sizeof( phase ) +
                sizeof( dataValid );
        }

        inline void
        FrAdcDataNPS::copyCore( const FrAdcDataNPS& Source )
        {
            name = Source.name;
            comment = Source.comment;
            channelGroup = Source.channelGroup;
            channelNumber = Source.channelNumber;
            nBits = Source.nBits;
            sampleRate = Source.sampleRate;
            bias = Source.bias;
            slope = Source.slope;
            units = Source.units;
            fShift = Source.fShift;
            timeOffset = Source.timeOffset;
            phase = Source.phase;
            dataValid = Source.dataValid;
        }

        inline void
        FrAdcDataNPS::incrementTimeOffset( timeOffset_type Value )
        {
            timeOffset += Value;
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
            Desc( FrSEType( "timeOffset",
                            Common::Description::Ascii< timeOffset_type >( ),
                            "" ) );
            Desc( FrSEType(
                "fShift", Common::Description::Ascii< fShift_type >( ), "" ) );
            Desc( FrSEType(
                "phase", Common::Description::Ascii< phase_type >( ), "" ) );
            Desc( FrSEType( "dataValid",
                            Common::Description::Ascii< dataValid_type >( ),
                            "" ) );
        }

        inline bool
        FrAdcDataNPS::operator==( const FrAdcDataNPS& RHS ) const
        {
            return (
                ( this == &RHS ) ||
                ( ( name == RHS.name ) && ( comment == RHS.comment ) &&
                  ( channelGroup == RHS.channelGroup ) &&
                  ( channelNumber == RHS.channelNumber ) &&
                  ( nBits == RHS.nBits ) && ( sampleRate == RHS.sampleRate ) &&
                  ( bias == RHS.bias ) && ( slope == RHS.slope ) &&
                  ( units == RHS.units ) && ( fShift == RHS.fShift ) &&
                  ( timeOffset == RHS.timeOffset ) && ( phase == RHS.phase ) &&
                  ( dataValid == RHS.dataValid ) ) );
        }

    } /* namespace Version_6 */
} /* namespace FrameCPP */
#endif /* defined(__cplusplus) */
#endif /* ! defined(SWIGIMPORTED) */
#endif /* FrameCPP_VERSION_6_FrAdcDataNPS_HH */
