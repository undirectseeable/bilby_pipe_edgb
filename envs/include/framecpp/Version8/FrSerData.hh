//
// LDASTools frameCPP - A library implementing the LIGO/Virgo frame
// specification
//
// Copyright (C) 2018 California Institute of Technology
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

#ifndef FrameCPP_VERSION_8_FrSerData_HH
#define FrameCPP_VERSION_8_FrSerData_HH

#include "framecpp/Version8/impl/FrSerDataClassicIO.hh"

#if defined( __cplusplus ) && !defined( SWIGIMPORTED )

namespace FrameCPP
{
    namespace Version_8
    {
        //===================================================================
        /// \brief Raw Data Structure Definition
        //===================================================================
        class FrSerData : public FrSerDataImpl::ClassicIO< FrSerData >
        {
        public:
            //-----------------------------------------------------------------
            /// \brief Default constructor
            ///
            /// \return
            ///    A new instance of this object.
            //-----------------------------------------------------------------
            FrSerData( ) = default;

            //-----------------------------------------------------------------
            /// \brief Copy Constructor
            ///
            /// \param[in] Source
            ///     The object from which to copy the information.
            ///
            /// \return
            ///    A new instance of this object.
            //-----------------------------------------------------------------
            FrSerData( const FrSerData& Source ) = default;

            //-----------------------------------------------------------------
            /// \brief Constructor
            ///
            /// \param[in] name
            ///     Name of station producing serial data stream.
            /// \param[in] time
            ///     Time of data acquisition.
            /// \param[in] sampleRate
            ///     Sample rate, samples per second.
            ///
            /// \return
            ///     A new instance of the object.
            //-----------------------------------------------------------------
            FrSerData( const std::string& name,
                       const GPSTime&     time,
                       sampleRate_type    sampleRate );

            //-----------------------------------------------------------------
            /// \brief Promotion Constructor
            ///
            /// \param[in] Source
            ///     An FrSerData structure from a previous frame specification.
            /// \param[in] Stream
            ///     The stream from which the earliest version of the
            ///     FrSerData structure was read.
            ///
            /// \return
            ///     A new instance of the object.
            //-----------------------------------------------------------------
            FrSerData( Previous::FrSerData& Source, istream_type* Stream );

            //----------------------------------------------------------
            /// \brief Return the name of station producing serial
            /// data stream.
            ///
            /// \return
            ///     The name associated of station producing serial
            ///     data stream.
            //----------------------------------------------------------
            const name_type& GetNameSlow( ) const;

            //-----------------------------------------------------------------
            /// \brief Merge with another FrSerData
            ///
            /// \param[in] RHS
            ///     The source of the information to append to this FrSerData
            ///     structure.
            ///
            /// \return
            ///     A reference to this object
            //-----------------------------------------------------------------
            FrSerData& Merge( const FrSerData& RHS );

            //-----------------------------------------------------------------
            /// \brief equality operator
            ///
            /// \param[in] RHS
            ///     The FrSerData object to be compared.
            ///
            /// \return
            ///     The value true is returned if this object is equivelent
            ///     to the RHS instance; false otherwise.
            //-----------------------------------------------------------------
            inline bool
            operator==( const FrSerData& RHS ) const
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
            //-----------------------------------------------------------------
            /// \brief Object with checksum data.
            //-----------------------------------------------------------------
            typedef ObjectWithChecksum< Common::FrameSpec::Object > object_type;

            using Common::FrameSpec::Object::Create;
        };

    } // namespace Version_8
} // namespace FrameCPP

#endif /* defined( __cplusplus ) && !defined( SWIGIMPORTED ) */

#endif /* FrameCPP_VERSION_8_FrSerData_HH */
