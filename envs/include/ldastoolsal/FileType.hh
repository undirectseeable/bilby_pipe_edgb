//
// LDASTools AL - A library collection to provide an abstraction layer
//
// Copyright (C) 2018 California Institute of Technology
//
// LDASTools AL is free software; you may redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 (GPLv2) of the
// License or at your discretion, any later version.
//
// LDASTools AL is distributed in the hope that it will be useful, but
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

#ifndef GENERAL__FILE_TYPE_HH
#define GENERAL__FILE_TYPE_HH

#include <string>

namespace LDASTools
{
    namespace AL
    {
        class FileType
        {
        public:
            enum types
            {
                FT_UNKNOWN_BINARY,
                FT_UNKNOWN_TEXT,
                FT_EPS,
                FT_FRAME,
                FT_GIF,
                FT_GZIP,
                FT_HTML,
                FT_HTML_404,
                FT_HTML_ERROR,
                FT_ILWD,
                FT_ILWD_FRAME,
                FT_JPEG,
                FT_PDF,
                FT_PGP,
                FT_PNG,
                FT_PS,
                FT_SCRIPT,
                FT_TIFF,
                FT_XML,
                FT_XML_DOC
            };

            FileType( const std::string& Filename );
            const std::string& GetFileType( ) const;

        private:
            std::string m_type_desc;
        };

        inline const std::string&
        FileType::GetFileType( ) const
        {
            return m_type_desc;
        }
    } // namespace AL
} // namespace LDASTools

#endif /* GENERAL__FILE_TYPE_HH */
