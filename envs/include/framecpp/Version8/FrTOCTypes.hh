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

#ifndef FrameCPP_VERSION_8_FrTOCTypes_HH
#define FrameCPP_VERSION_8_FrTOCTypes_HH

#include <map>
#include <vector>

#include "framecpp/Version6/FrameSpec.hh"
#include "framecpp/Version6/STRING.hh"

namespace FrameCPP
{
    namespace Version_8
    {
        struct FrTOCTypes
        {
        public:
            typedef STRING                       name_type;
            typedef INT_4U                       n_type;
            typedef Version_8::position_type     position_type;
            typedef std::vector< position_type > position_container_type;
            typedef std::map< name_type, position_container_type >
                                             ordered_position_container_type;
            typedef std::vector< name_type > key_container_type;
        };
    } // namespace Version_8
} // namespace FrameCPP

#endif /* FrameCPP_VERSION_8_FrTOCTypes_HH */
