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

#ifndef FrameCPP_VERSION_8_FrProcData_HH
#define FrameCPP_VERSION_8_FrProcData_HH

#include "framecpp/Version8/impl/FrProcDataClassicIO.hh"

#if defined( __cplusplus ) && !defined( SWIGIMPORTED )

namespace FrameCPP
{
    namespace Version_8
    {
        /**
         * \brief Post-Processed Data Structure Definition.
         */
        class FrProcData : public FrProcDataImpl::ClassicIO< FrProcData >
        {
        public:
            typedef boost::shared_ptr< FrProcData > subset_ret_type;

            /**
             * \brief Default constructor
             *
             * \return
             *    A new instance of this object.
             */
            FrProcData( ) = default;

            /**
             * \brief Copy Constructor
             *
             * \param[in] Source
             *     The object from which to copy the information.
             *
             * \return
             *    A new instance of this object.
             */
            FrProcData( const FrProcData& Source ) = default;

            /**
             * \brief Constructor
             *
             * \param[in] Name
             *     Data or channel name
             * \param[in] Comment
             *     Comment
             * \param[in] Type
             *     Type of data object.
             * \param[in] SubType
             *     Subtype of f-Series.
             * \param[in] TimeOffset
             *     Ofset of 1st sample relative to the frame start time.
             * \param[in] TRange
             *     Duration of sampled data.
             * \param[in] FShift
             *     The frequency in the original data that corresponds to
             *     zero Hz in the heterodyned series.
             * \param[in] Phase
             *     Phase of heterodyning signal at start of dataset.
             * \param[in] FRange
             *     Frequency range.
             * \param[in] BW
             *     Resolution bandwidth.
             *
             * \return
             *    A new instance of this object.
             */
            FrProcData( const name_type&    Name,
                        const comment_type& Comment,
                        type_type           Type,
                        subType_type        SubType,
                        timeOffset_type     TimeOffset,
                        tRange_type         TRange,
                        fShift_type         FShift,
                        phase_type          Phase,
                        fRange_type         FRange,
                        BW_type             BW );

            /**
             * \brief Promotion Constructor
             *
             * \param[in] Source
             *     An FrProcData structure from a previous frame
             * specification. \param[in] Stream The stream from which the
             * earliest version of the FrProcData structure was read.
             *
             * \return
             *     A new instance of an FrProcData object
             */
            FrProcData( Previous::FrProcData& Source, istream_type* Stream );

            /**
             * \brief Destructor
             */
            ~FrProcData( );

            /**
             * \brief Return the name associate with the FrProcData
             * structure.
             *
             * \return
             *     The name associated with the FrProcData structure
             */
            const name_type&
            GetNameSlow( ) const
            {
                return Data::GetNameSlow( );
            }

            inline bool
            operator==( const FrProcData& RHS ) const
            {
                return ( Data::operator==( RHS ) );
            }

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

            /**
             * \brief Merge with another FrProcData
             *
             * \param[in] RHS
             *     The source of the information to append to this
             * FrProcData structure.
             *
             * \return
             *     A reference to this object
             */
            FrProcData& Merge( const FrProcData& RHS );

            /**
             * \brief Request a subset of the data.
             *
             * \param[in] Offset
             *     The number of seconds from the start of the FrProcData
             *     object from which to start extracting data.
             * \param[in] Dt
             *     The number of seconds of data in the resulting FrProcData
             *     strucutre.
             *
             * \return
             *     A FrProcData structure which contains Dt seconds of data
             *     starting at Offset of this FrProcData structure.
             */
            subset_ret_type Subset( REAL_8 Offset, REAL_8 Dt ) const;

        private:
            /**
             * \brief Object with checksum data.
             */
            typedef ObjectWithChecksum< Common::FrameSpec::Object > object_type;

            using Common::FrameSpec::Object::Create;

            /**
             * \brief Retrieve a time series subset.
             *
             * \param[in] Offset
             *     The number of seconds from the start of the FrProcData
             *     object from which to start extracting data.
             * \param[in] Dt
             *     The number of seconds of data in the resulting FrProcData
             *     strucutre.
             *
             * \return
             *     A FrProcData structure which contains Dt seconds of data
             *     starting at Offset of this FrProcData structure.
             */
            subset_ret_type sub_time_series( REAL_8 Offset, REAL_8 Dt ) const;
        };

    } /* namespace Version_8 */
} /* namespace FrameCPP */

#endif /* defined( __cplusplus ) && !defined( SWIGIMPORTED ) */

#endif /* FrameCPP_VERSION_8_FrProcData_HH */
