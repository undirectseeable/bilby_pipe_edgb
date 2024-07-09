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

#ifndef LDAS_TOOLS_AL__CONFIG_HH
#define LDAS_TOOLS_AL__CONFIG_HH

#include <iosfwd>

namespace LDASTools
{
    namespace AL
    {
        //-------------------------------------------------------------------
        /// \brief Support reading and parsing of configuration streams.
        ///
        /// This class supports reading from a stream and parses.
        //-------------------------------------------------------------------
        class Config
        {
        public:
            //-----------------------------------------------------------------
            /// \brief The various types of parsing understood by the parser
            //-----------------------------------------------------------------
            enum
            {
                ASSIGNMENT, ///< %<var%> = %<value%>
                BLOCK, ///< [%<var%>]
                WORD ///< %<word%>
            };

            //-----------------------------------------------------------------
            /// \brief Constructor
            ///
            //-----------------------------------------------------------------
            Config( );

            //-----------------------------------------------------------------
            /// \brief Parse the input stream
            ///
            /// \param[in] Stream
            ///     Input stream.
            //-----------------------------------------------------------------
            virtual void Parse( std::istream& Stream );

            virtual void ParseBlock( const std::string& Value ) = 0;

            virtual void ParseKeyValue( const std::string& Key,
                                        const std::string& Value ) = 0;

            virtual void ParseWord( const std::string& Value ) = 0;

        private:
        };
    } // namespace AL
} // namespace LDASTools

#endif /* LDAS_TOOLS_AL__CONFIG_HH */
