//
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

#ifndef FrameCPP_VERSION_8__IMPL__FrObjectMetaData_HH
#define FrameCPP_VERSION_8__IMPL__FrObjectMetaData_HH

#include "framecpp/storage/data/FrObjectMetaData.hh"

namespace FrameCPP
{
    namespace Version_8
    {
        namespace Impl
        {
            template < typename Object_T >
            using FrObjectMetaData = v3::FrObjectMetaData< Object_T >;

        } // namespace Impl

    } // namespace Version_8
} // namespace FrameCPP

#define FR_OBJECT_META_DATA_DECLARE( OBJECT_T )                                \
    namespace FrameCPP                                                         \
    {                                                                          \
        namespace v3                                                           \
        {                                                                      \
            template <>                                                        \
            FrObjectMetaData< Version_8::OBJECT_T ::Data >::struct_name_type   \
                FrObjectMetaData< Version_8::OBJECT_T ::Data >::struct_name;   \
            template <>                                                        \
            FrObjectMetaData< Version_8::OBJECT_T ::Data >::struct_desc_type   \
                FrObjectMetaData< Version_8::OBJECT_T ::Data >::struct_desc;   \
            template <>                                                        \
            FrObjectMetaData< Version_8::OBJECT_T ::Data >::struct_id_type     \
                FrObjectMetaData< Version_8::OBJECT_T ::Data >::struct_id;     \
        }                                                                      \
    }

#define FR_OBJECT_META_DATA_DEFINE( OBJECT_T, ID, NAME, DESC )                 \
    namespace FrameCPP                                                         \
    {                                                                          \
        namespace v3                                                           \
        {                                                                      \
            using FrameCPP::Version_8::OBJECT_T ::Data;                        \
                                                                               \
            template <>                                                        \
            FrObjectMetaData< Data >::struct_name_type                         \
                FrObjectMetaData< Data >::struct_name = NAME;                  \
            template <>                                                        \
            FrObjectMetaData< Data >::struct_desc_type                         \
                FrObjectMetaData< Data >::struct_desc = DESC;                  \
            template <>                                                        \
            FrObjectMetaData< Data >::struct_id_type                           \
                FrObjectMetaData< Data >::struct_id =                          \
                    Common::FrameSpec::Info::ID;                               \
        }                                                                      \
    }
#endif /* FrameCPP_VERSION_8__IMPL__FrObjectMetaData_HH */
