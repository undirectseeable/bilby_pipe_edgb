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

#ifndef FrameCPP_VERSION_8_FrAdcData_HH
#define FrameCPP_VERSION_8_FrAdcData_HH

#include "framecpp/Version8/impl/FrAdcDataClassicIO.hh"

#if defined( __cplusplus ) && !defined( SWIGIMPORTED )
namespace FrameCPP
{
    namespace Version_8
    {
        //===================================================================
        /// \brief Event data
        //===================================================================
        class FrAdcData : public FrAdcDataImpl::ClassicIO< FrAdcData >
        {
        public:
            typedef boost::shared_ptr< FrAdcData > subset_ret_type;

            /**
             * \brief Default constructor
             *
             */
            FrAdcData( );

            /**
             * \brief Constructor
             *
             * \param[in] Name
             *     The Channel name -- must be unique within the frame
             * \param[in] ChannelGroup
             *     Channel grouping number containing ADC.
             * \param[in] ChannelNumber
             *     Channel number.
             * \param[in] NBits
             *     Number of bits in A/D output.
             * \param[in] Bias
             *     DC bias on channel (Units ADC counts = 0)
             * \param[in] Slope
             *     ADC calibration: input units/count.
             * \param[in] Units
             *     ADC calibration: input units for slope.
             * \param[in] SampleRate
             *     Data acquistion rate, samples/s.
             * \param[in] FShift
             *     The frequency (in Hz) in the origional data that
             *     oorresponds to 0 Hz in the heterodyned series.
             * \param[in] TimeOffset
             *     Offset of the first sample relative to the frame start
             *     time (seconds). Must be positive and smaller than the
             *     frame length.
             * \param[in] DataValid
             *     Data valid flag.
             * \param[in] Phase
             *     Phase of heterodyning signal at start of dataset.
             *
             * \return
             *     A new instance of the object.
             */
            FrAdcData( const name_type&   Name,
                       channelGroup_type  ChannelGroup,
                       channelNumber_type ChannelNumber,
                       nBits_type         NBits,
                       sampleRate_type    SampleRate,
                       bias_type          Bias = Data::DEFAULT_BIAS,
                       slope_type         Slope = Data::DEFAULT_SLOPE,
                       const units_type&  Units = Data::DEFAULT_UNITS( ),
                       fShift_type        FShift = Data::DEFAULT_FSHIFT,
                       timeOffset_type TimeOffset = Data::DEFAULT_TIME_OFFSET,
                       dataValid_type  DataValid = Data::DEFAULT_DATA_VALID,
                       phase_type      Phase = Data::DEFAULT_PHASE );

            /**
             * \brief Promotion Constructor
             *
             * \param[in] Source
             *     An FrAdcData structure from a previous frame
             specification.
             * \param[in] Stream
             *     The stream from which the earliest version of the
             *     FrAdcData structure was read.
             *
             * \return
             *     A new instance of the object.
             */
            FrAdcData( Previous::FrAdcData& Source, istream_type* Stream );

            /**
             * \brief Retrieve the name of the FrAdcData struture.
             */
            const name_type& GetNameSlow( ) const;

            /**
             * \brief Merge with another FrAdcData
             *
             * \param[in] RHS
             *     The source of the information to append to this FrAdcData
             *     structure.
             *
             * \return
             *     A reference to this object
             */
            FrAdcData& Merge( const FrAdcData& RHS );

            /**
             * \brief Request a subset of the data.
             *
             * \param[in] Offset
             *     The number of seconds from the start of the FrAdcData
             *     object from which to start extracting data.
             * \param[in] Dt
             *     The number of seconds of data in the resulting FrAdcData
             *     strucutre.
             *
             * \return
             *     A FrAdcData structure which contains Dt seconds of data
             *     starting at Offset of this FrAdcData structure.
             */
            subset_ret_type Subset( REAL_8 Offset, REAL_8 Dt ) const;

            /**
             * \brief equality operator
             *
             * \param[in] RHS
             *     The FrAdcData object to be compared.
             *
             * \return
             *     The value true is returned if this object is equivelent
             *     to the RHS instance; false otherwise.
             */
            bool operator==( const FrAdcData& RHS ) const;

            /**
             * \brief equality operator for abstract data type
             *
             * \param[in] Obj
             *     The object to be compared.
             *
             * \return
             *     The value true is returned if this object is equivelent
             *     to the RHS instance; false otherwise.
             */
            virtual bool
            operator==( const Common::FrameSpec::Object& Obj ) const;
        };

        inline bool
        FrAdcData::operator==( const FrAdcData& RHS ) const
        {
            return ( ( this == &RHS ) ||
                     ( static_cast< const Data& >( *this ) ==
                       static_cast< const Data& >( RHS ) ) );
        }

    } // namespace Version_8
} // namespace FrameCPP

#endif /* defined( __cplusplus ) && !defined( SWIGIMPORTED ) */

#endif /* FrameCPP_VERSION_8_FrAdcData_HH */
