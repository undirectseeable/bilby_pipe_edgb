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

#ifndef FRAMECPPCPP__STORAGE__FR_SH_DATA_HH
#define FRAMECPPCPP__STORAGE__FR_SH_DATA_HH

#include <string>

#include "ldastoolsal/ldas_types.h"

namespace FrameCPP
{
    namespace v3
    {
        //-----------------------------------------------------------
        /// @brief Storage space for FrSH information
        ///
        /// This stores information about an FrSH element that
        /// needs to persist beyond an I/O operation
        //-----------------------------------------------------------
        class FrSH
        {
        public:
            /// Name of structure being described by this dictionary
            /// structure
            typedef std::string name_type;
            /// Comment
            typedef std::string comment_type;
            /// Class number of structure being described
            typedef INT_2U class_type;

            //-----------------------------------------------------------------
            /// \brief Return class of object
            ///
            /// \return
            ///    Class number of structure being described
            //-----------------------------------------------------------------
            class_type GetClass( ) const;

            //-----------------------------------------------------------------
            /// \brief Return comment of object
            ///
            /// \return
            ///   Comment
            //-----------------------------------------------------------------
            const comment_type& GetComment( ) const;

            //-----------------------------------------------------------------
            /// \brief Return name of object
            ///
            /// \return
            ///   Name of structure being described by this dictionary
            ///   structure
            //-----------------------------------------------------------------
            const name_type& GetName( ) const;

        protected:
            name_type name; /**< Name of structure being described by this
                            dictionary structure */
            comment_type comment; /**< Comment */
            class_type klass; /**< Class number of structure being described */
        };

        inline const FrSH::name_type&
        FrSH::GetName( ) const
        {
            return ( name );
        }

        inline const FrSH::comment_type&
        FrSH::GetComment( ) const
        {
            return ( comment );
        }

        inline FrSH::class_type
        FrSH::GetClass( ) const
        {
            return ( klass );
        }
    } // namespace - v3

} // namespace FrameCPP

#endif /* FRAMECPPCPP__STORAGE__FR_SH_DATA_HH */
