// LDASTools frameCPP - A library implementing the LIGO/Virgo frame
// specification
//
// Copyright (C) 2019 California Institute of Technology
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

#include "ldastoolsal/ldas_types.h"

#ifndef FRAMECPP__SUPPORT__FR_OBJECT_META_DATA_HH
#define FRAMECPP__SUPPORT__FR_OBJECT_META_DATA_HH

namespace FrameCPP
{
    namespace v3
    {
        template < typename Object_T >
        class FrObjectMetaData
        {
        public:
            typedef const char* const struct_name_type;
            typedef const char* const struct_desc_type;
            typedef INT_2U const      struct_id_type;

            static struct_name_type
            FrameSpecName( )
            {
                return ( struct_name );
            }

            // Deptricated
            static struct_name_type
            StructName( )
            {
                return ( FrameSpecName( ) );
            }

            //-----------------------------------------------------------------
            /// \brief Return the dictionary name of the structure.
            //-----------------------------------------------------------------
            static struct_desc_type
            FrameSpecDescription( )
            {
                return ( struct_desc );
            }

            //-----------------------------------------------------------------
            /// \brief Return the dictionary name of the structure.
            //-----------------------------------------------------------------
            static struct_id_type
            FrameSpecId( )
            {
                return ( struct_id );
            }

            static struct_name_type struct_name;
            static struct_desc_type struct_desc;
            static struct_id_type   struct_id;
        };

    } // namespace v3

} // namespace FrameCPP

#endif /* FRAMECPP__SUPPORT__FR_OBJECT_META_DATA_HH */
