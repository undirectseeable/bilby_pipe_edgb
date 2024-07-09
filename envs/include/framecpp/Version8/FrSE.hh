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

#ifndef FrameCPP__VERSION_8__FrSE_HH
#define FrameCPP__VERSION_8__FrSE_HH

#include "framecpp/Version8/impl/FrSEClassicIO.hh"
#include "framecpp/Version8/impl/FrSESerialIO.hh"

#include "framecpp/Common/FrameSpec.hh"

namespace FrameCPP
{
    namespace Version_8
    {
        //---------------------------------------------------------------
        /// \brief Contains field information of a dictionary structure.
        ///
        /// This class gives information describing a single field of the
        /// class structure being described.
        /// In a dicitionary structure, there may be multiple occurances
        /// of FrSE.
        /// The order of the FrSE corresponds to the order of the fields
        /// as written to the stream.
        ///
        /// \see FrSH
        //---------------------------------------------------------------
        class FrSE : public FrSEImpl::ClassicIO< FrSE >,
                     public FrSEImpl::SerialIO< FrSE >
        {
        public:
            //-----------------------------------------------------------
            /// \brief Default constructor
            //-----------------------------------------------------------
            FrSE( );

            //-----------------------------------------------------------
            /// \brief constructor
            ///
            /// \param[in] Name
            ///     Name of an element of the structure being described by
            ///     this dictionary structure.
            /// \param[in] ClassId
            ///     The data type of the element being described by this
            ///     dictionary structure.
            /// \param[in] Comment
            ///     Description of the element being described by this
            ///     dictionary strucutre.
            //-----------------------------------------------------------
            FrSE( const name_type&    Name,
                  const classId_type& ClassId,
                  const comment_type& Comment = "" );

            //-----------------------------------------------------------
            /// \brief Desctructor
            //-----------------------------------------------------------
            virtual ~FrSE( );

            //-----------------------------------------------------------
            /// \brief comparison operator
            //-----------------------------------------------------------
            inline bool
            operator==( const FrSE& RHS ) const
            {
                return ( Data::operator==( RHS ) );
            }

        }; // class - FrSE
    } // namespace Version_8
} // namespace FrameCPP
#endif /* FrameCPP__VERSION_8__FrSE_HH */
