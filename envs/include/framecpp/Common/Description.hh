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

#ifndef FRAMECPP__COMMON__Description_HH
#define FRAMECPP__COMMON__Description_HH

#if !defined( SWIGIMPORTED )
#include <list>

#include <boost/shared_ptr.hpp>
#endif /* ! defined(SWIGIMPORTED) */

#include "ldastoolsal/types.hh"

#include "framecpp/Common/FrameSpec.hh"

namespace FrameCPP
{
    namespace Common
    {
        class OFrameStream;

        class Description
        {
        public:
            typedef boost::shared_ptr< FrameSpec::Object > object_type;

            virtual ~Description( );

            const std::string& GetName( ) const;

            void Write( OFrameStream& Stream ) const;

            void operator( )( object_type Obj );

            void operator( )( const object_type::element_type& Obj );

            INT_4U size( ) const;

            template < typename T >
            static const char* Ascii( );

        private:
            typedef std::list< object_type > description_container;

            description_container m_desc;
        };

        template <>
        inline const char*
        Common::Description::Ascii< INT_2S >( )
        {
            return ( "INT_2S" );
        }

        template <>
        inline const char*
        Common::Description::Ascii< INT_2U >( )
        {
            return ( "INT_2U" );
        }

        template <>
        inline const char*
        Common::Description::Ascii< INT_4S >( )
        {
            return ( "INT_4S" );
        }

        template <>
        inline const char*
        Common::Description::Ascii< INT_4U >( )
        {
            return ( "INT_4U" );
        }

        template <>
        inline const char*
        Common::Description::Ascii< INT_8S >( )
        {
            return ( "INT_8S" );
        }

        template <>
        inline const char*
        Common::Description::Ascii< INT_8U >( )
        {
            return ( "INT_8U" );
        }

        template <>
        inline const char*
        Common::Description::Ascii< REAL_4 >( )
        {
            return ( "REAL_4" );
        }

        template <>
        inline const char*
        Common::Description::Ascii< REAL_8 >( )
        {
            return ( "REAL_8" );
        }

        template <>
        inline const char*
        Common::Description::Ascii< const char* >( )
        {
            return ( "STRING" );
        }

        template <>
        inline const char*
        Common::Description::Ascii< std::string >( )
        {
            return ( "STRING" );
        }

        inline INT_4U
        Common::Description::size( ) const
        {
            return m_desc.size( );
        }

    } // namespace Common
} // namespace FrameCPP

#endif /* FRAMECPP__COMMON__Description_HH */
