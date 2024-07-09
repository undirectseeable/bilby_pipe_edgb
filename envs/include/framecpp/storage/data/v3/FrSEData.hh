//
// LDASTools frameCPP - A library implementing the LIGO/Virgo frame
// specification
//
// Copyright (C) 2020 California Institute of Technology
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

#ifndef FRAMECPP__STORAGE__FR_SE_DATA_HH
#define FRAMECPP__STORAGE__FR_SE_DATA_HH

#include <string>

#include "ldastoolsal/ldas_types.h"

namespace FrameCPP
{
    namespace v3
    {
        class FrSE
        {
        public:
            typedef std::string name_type;
            typedef std::string classId_type;
            typedef std::string comment_type;

            //-----------------------------------------------------------------
            /// \brief Return name of object
            //-----------------------------------------------------------------
            const name_type&
            GetName( ) const
            {
                return name;
            }

            //-----------------------------------------------------------------
            /// \brief Return class of object
            //-----------------------------------------------------------------
            const classId_type&
            GetClass( ) const
            {
                return classId;
            }

            //-----------------------------------------------------------------
            /// \brief Return comment of object
            //-----------------------------------------------------------------
            const comment_type&
            GetComment( ) const
            {
                return comment;
            }

            //-----------------------------------------------------------------
            /// \brief comparison operator
            //-----------------------------------------------------------------
            bool
            operator==( const FrSE& RHS ) const
            {
                return ( ( this == &RHS ) ||
                         ( ( name.compare( RHS.name ) == 0 ) && ( classId.compare( RHS.classId ) == 0 ) &&
                           ( comment.compare( RHS.comment ) == 0 ) ) );
            }

        protected:
            //---------------------------------------------------------------
            /// Name of an element of the structure being described.
            /// All element names within the structure must be unique.
            //---------------------------------------------------------------
            name_type name;
            //---------------------------------------------------------------
            /// The string representation of data type of the element.
            //---------------------------------------------------------------
            classId_type classId;
            //---------------------------------------------------------------
            /// Description of the element.
            //---------------------------------------------------------------
            comment_type comment;
        };
    } // namespace v3
} // namespace FrameCPP

#endif /* FRAMECPP__STORAGE__FR_SE_DATA_HH */
