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

#ifndef FrameCPP_VERSION_8_FrStatData_HH
#define FrameCPP_VERSION_8_FrStatData_HH

#include "framecpp/Version8/impl/FrStatDataClassicIO.hh"

namespace FrameCPP
{
    namespace Version_8
    {
        //===================================================================
        /// \brief Static Data Structure Definition
        //===================================================================
        class FrStatData : public FrStatDataImpl::ClassicIO< FrStatData >
        {
        public:
            //-----------------------------------------------------------------
            /// \brief Default constructor
            ///
            /// \return
            ///    A new instance of this object.
            //-----------------------------------------------------------------
            FrStatData( ) = default;

            //-----------------------------------------------------------------
            /// \brief Copy Constructor
            ///
            /// \param[in] Source
            ///     The object from which to copy the information.
            ///
            /// \return
            ///    A new instance of this object.
            //-----------------------------------------------------------------
            FrStatData( const FrStatData& Source );

            //-----------------------------------------------------------------
            /// \brief Constructor
            ///
            /// \param[in] name
            ///     Static data name
            /// \param[in] comment
            ///     Comemnt
            /// \param[in] representation
            ///     Type of static data being represented
            /// \param[in] timeStart
            ///     Start time of static data validity.
            /// \param[in] timeEnd
            ///     End time of static data validity.
            /// \param[in] version
            ///     Version number of this static structure.
            ///
            /// \return
            ///     A new instance of the object.
            //-----------------------------------------------------------------
            FrStatData( const name_type&           Name,
                        const comment_type&        Comment,
                        const representation_type& Representation,
                        timeStart_type             TimeStart,
                        timeEnd_type               TimeEnd,
                        version_type               Version );

            //-----------------------------------------------------------------
            /// \brief Promotion Constructor
            ///
            /// \param[in] Source
            ///     An FrAdcData structure from a previous frame specification.
            /// \param[in] Stream
            ///     The stream from which the earliest version of the
            ///     FrAdcData structure was read.
            ///
            /// \return
            ///     A new instance of the object.
            //-----------------------------------------------------------------
            FrStatData( const Previous::FrStatData& Source,
                        istream_type*               Stream );

            //-----------------------------------------------------------------
            /// \brief Merge with another FrAdcData
            ///
            /// \param[in] RHS
            ///     The source of the information to append to this FrAdcData
            ///     structure.
            ///
            /// \return
            ///     A reference to this object
            //-----------------------------------------------------------------
            FrStatData& Merge( const FrStatData& RHS );

            //-----------------------------------------------------------------
            /// \brief equality operator
            ///
            /// \param[in] RHS
            ///     The FrAdcData object to be compared.
            ///
            /// \return
            ///     The value true is returned if this object is equivelent
            ///     to the RHS instance; false otherwise.
            //-----------------------------------------------------------------
            inline bool
            operator==( const FrStatData& RHS ) const
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
#endif /* FrameCPP_VERSION_8_FrStatData_HH */
