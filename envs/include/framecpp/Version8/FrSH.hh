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

#ifndef FrameCPP__VERSION_8__FrSH_HH
#define FrameCPP__VERSION_8__FrSH_HH

#if !defined( SWIGIMPORTED )
#include "framecpp/Common/FrameSpec.hh"
#include "framecpp/Common/FrSH.hh"
#include "framecpp/Common/TOCInfo.hh"
#endif /* !defined( SWIGIMPORTED ) */

#if !defined( SWIGIMPORTED )
#include "framecpp/Version8/FrameSpec.hh"
#endif /* !defined( SWIGIMPORTED ) */

#include "framecpp/Version8/impl/FrSHClassicIO.hh"
#include "framecpp/Version8/impl/FrSHSerialIO.hh"

namespace FrameCPP
{
    namespace Version_8
    {
        //-------------------------------------------------------------------
        /// \brief Contains class information of a dictionary structure.
        ///
        /// A dictionary structure is written to the output stream the
        /// imediately preceeding the first occurance of the frame structure
        /// it describes.
        /// This class gives information about the class structure being
        /// described.
        /// In a dictionary structure, there is only one occurance of FrSH.
        /// It must be the first element of the dictionary structure.
        ///
        /// \see FrSE
        //-------------------------------------------------------------------
        class FrSH
#if !defined( SWIGIMPORTED )
          : public FrSHImpl::ClassicIO< FrSH >,
                     public FrSHImpl::SerialIO< FrSH >,
                     public Common::TOCInfo
#endif /* !defined( SWIGIMPORTED ) */
        {
        public:
            //-----------------------------------------------------------------
            /// \brief Default constructor
            //-----------------------------------------------------------------
            FrSH( );

            //-----------------------------------------------------------------
            /// \brief constructor
            ///
            /// \param[in] Name
            ///     Name of structure being described by this dictionary
            ///     structure.
            /// \param[in] ClassId
            ///     Class number of structure being described
            /// \param[in] Comment
            ///     Comment describing the class.
            //-----------------------------------------------------------------
            FrSH( const name_type&    Name,
                  class_type          ClassId,
                  const comment_type& Comment );

            //-----------------------------------------------------------------
            /// \brief Desctructor
            //-----------------------------------------------------------------
            virtual ~FrSH( );

            //-----------------------------------------------------------------
            /// \brief comparison operator
            //-----------------------------------------------------------------
            bool operator==( const FrSH& RHS ) const;

            //-----------------------------------------------------------------
            /// \brief comparison operator
            //-----------------------------------------------------------------
            virtual bool
            operator==( const Common::FrameSpec::Object& Obj ) const;

        protected:
#if !WORKING_VIRTUAL_TOCQUERY
            //-----------------------------------------------------------------
            /// \brief Answer requests for information as needed by TOC
            ///
            /// \param[in] InfoClass
            ///     Class of information being requested.
            /// \param[in] vl
            ///     Variable argument list of requested data.
            //-----------------------------------------------------------------
            virtual void vTOCQuery( int InfoClass, va_list vl ) const;
#endif /* ! WORKING_VIRTUAL_TOCQUERY */
        }; // class - FrSH

    } // namespace Version_8
} // namespace FrameCPP
#endif /* FrameCPP__VERSION_8__FrSH_HH */
