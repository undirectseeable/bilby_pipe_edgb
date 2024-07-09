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

#ifndef FrameCPP_VERSION_8_FrSimData_HH
#define FrameCPP_VERSION_8_FrSimData_HH

#include "framecpp/Version8/impl/FrSimDataClassicIO.hh"

#if defined( __cplusplus ) && !defined( SWIG )

namespace FrameCPP
{
    namespace Version_8
    {
        //===================================================================
        /// \brief Simulated Data Structure Definition
        //===================================================================
        class FrSimData : public FrSimDataImpl::ClassicIO< FrSimData >
        {
        public:
            //-----------------------------------------------------------------
            /// \brief Default constructor
            ///
            /// \return
            ///    A new instance of this object.
            //-----------------------------------------------------------------
            FrSimData( ) = default;

            //-----------------------------------------------------------------
            /// \brief Copy Constructor
            ///
            /// \param[in] Source
            ///     The object from which to copy the information.
            ///
            /// \return
            ///    A new instance of this object.
            //-----------------------------------------------------------------
            FrSimData( const FrSimData& Source ) = default;

            //-----------------------------------------------------------------
            /// \brief Constructor
            ///
            /// \param[in] Name
            ///     Name of simulated data.
            /// \param[in] Comment
            ///     Comment
            /// \param[in] SampleRate
            ///     Simulated data sample rate, samples per second.
            /// \param[in] FShift
            ///     The frequency in the original data that corresponds to
            ///     0 Hz in the heterodyned series.
            /// \param[in] Phase
            ///     Phase of heterodyning signal at start of dataset.
            /// \param[in] TimeOffset
            ///     Offset of 1st sample relative to the frame start time.
            ///
            /// \return
            ///     A new instance of the object.
            //-----------------------------------------------------------------
            FrSimData( const name_type&      Name,
                       const comment_type&   Comment,
                       const sampleRate_type SampleRate,
                       const fShift_type     FShift,
                       const phase_type      Phase,
                       const timeOffset_type TimeOffset = DEFAULT_TIME_OFFSET );

            //-----------------------------------------------------------------
            /// \brief Promotion Constructor
            ///
            /// \param[in] Source
            ///     An FrSimData structure from a previous frame specification.
            /// \param[in] Stream
            ///     The stream from which the earliest version of the
            ///     FrSimData structure was read.
            ///
            /// \return
            ///     A new instance of the object.
            //-----------------------------------------------------------------
            FrSimData( Previous::FrSimData& Source, istream_type* Stream );

            //-----------------------------------------------------------------
            /// \brief Return the name associate with the FrSimData structure.
            ///
            /// \return
            ///     The name associated with the FrSimData structure
            //-----------------------------------------------------------------
            const std::string& GetNameSlow( ) const;

            //-----------------------------------------------------------------
            /// \brief Merge with another FrSimData
            ///
            /// \param[in] RHS
            ///     The source of the information to append to this FrSimData
            ///     structure.
            ///
            /// \return
            ///     A reference to this object
            //-----------------------------------------------------------------
            FrSimData& Merge( const FrSimData& RHS );

            //-----------------------------------------------------------------
            /// \brief equality operator
            ///
            /// \param[in] RHS
            ///     The FrSimData object to be compared.
            ///
            /// \return
            ///     The value true is returned if this object is equivelent
            ///     to the RHS instance; false otherwise.
            //-----------------------------------------------------------------
            inline bool
            operator==( const FrSimData& RHS ) const
            {
                return ( Data::operator==( RHS ) );
            }

            //-----------------------------------------------------------------
            /// \brief equality operator for abstract data type
            ///
            /// \param[in] RHS
            ///     The object to be compared.
            ///
            /// \return
            ///     The value true is returned if this object is equivelent
            ///     to the RHS instance; false otherwise.
            //-----------------------------------------------------------------
            virtual bool
            operator==( const Common::FrameSpec::Object& RHS ) const;
        private:
          using Common::FrameSpec::Object::Create;
        };

    } // namespace Version_8
} // namespace FrameCPP

#endif /* defined( __cplusplus ) && !defined( SWIG ) */

#endif /* FrameCPP_VERSION_8_FrSimData_HH */
