/*
 * LDASTools frameCPP - A library implementing the LIGO/Virgo frame
 * specification
 *
 * Copyright (C) 2018 California Institute of Technology
 *
 * LDASTools frameCPP is free software; you may redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 (GPLv2) of the
 * License or at your discretion, any later version.
 *
 * LDASTools frameCPP is distributed in the hope that it will be useful, but
 * without any warranty or even the implied warranty of merchantability
 * or fitness for a particular purpose. See the GNU General Public
 * License (GPLv2) for more details.
 *
 * Neither the names of the California Institute of Technology (Caltech),
 * The Massachusetts Institute of Technology (M.I.T), The Laser
 * Interferometer Gravitational-Wave Observatory (LIGO), nor the names
 * of its contributors may be used to endorse or promote products derived
 * from this software without specific prior written permission.
 *
 * You should have received a copy of the licensing terms for this
 * software included in the file LICENSE located in the top-level
 * directory of this package. If you did not, you can view a copy at
 * http://dcc.ligo.org/M1500244/LICENSE
 */

#ifndef FrameCPP__COMMON__STRING_HH
#define FrameCPP__COMMON__STRING_HH

#if !defined( SWIGIMPORTED )
#include <stdexcept>
#include <string>
#include <vector>

#include <boost/scoped_array.hpp>
#endif /* ! defined(SWIGIMPORTED) */

#if !defined( SWIGIMPORTED )
#include "ldastoolsal/types.hh"

#include "framecpp/Common/IOStream.hh"
#endif /* ! defined(SWIGIMPORTED) */

#if !defined( SWIG )
namespace FrameCPP
{
    namespace Common
    {
        template < class L >
        class STRING
            /** @cond IGNORE_BY_DOXYGEN */
            : public std::string
        /** @endcond */ /* IGNORE_BY_DOXYGEN */
        {
        public:
            typedef L                       length_type;
            typedef std::string::value_type char_type;

            static const length_type MAX_STRING_LENGTH;

            STRING( );

            STRING( const std::string& Value );

            STRING( const char* Value );

            STRING( const char* Value, size_t Length );

            /* Calculate the number of bytes needed to write this object */
            cmn_streamsize_type Bytes( ) const;

            static cmn_streamsize_type Bytes( const std::string& String );

            STRING& operator=( const std::string& Source );

            STRING& operator=( const char* Source );

            void Read( IStream& Stream );

            static void Read( IStream& Stream, std::string& Source );

            void Write( OStream& Stream ) const;

            static void Write( OStream& Stream, const std::string& Source );

        private:
            static void length_error( const std::string& Value );
            static void length_error( const char* Value );

        }; /* class - STRING */

        template < class L >
        const L STRING< L >::MAX_STRING_LENGTH = ~( L( 0 ) );

        template < class L >
        STRING< L >::STRING( ) : std::string( )
        {
        }

        template < class L >
        STRING< L >::STRING( const std::string& Value )
        {
            length_error( Value );
            std::string::operator=( Value );
        }

        template < class L >
        STRING< L >::STRING( const char* Value )
        {
            length_error( Value );
            std::string::operator=( Value );
        }

        template < class L >
        STRING< L >::STRING( const char* Value, size_t Length )
            : std::string( Value, Length )
        {
            length_error( Value );
        }

        template < class L >
        STRING< L >&
        STRING< L >::operator=( const std::string& Source )
        {
            length_error( Source );
            std::string::operator=( Source );
            return *this;
        }

        template < class L >
        STRING< L >&
        STRING< L >::operator=( const char* Source )
        {
            length_error( Source );
            std::string::operator=( Source );
            return *this;
        }

        template < class L >
        inline cmn_streamsize_type
        STRING< L >::Bytes( ) const
        {
            return Bytes( *this );
        }

        template < class L >
        inline cmn_streamsize_type
        STRING< L >::Bytes( const std::string& String )
        {
            return String.length( ) /* Length of string */
                + 1 /* space for the null character */
                + sizeof( length_type ); /* length to hold the size */
        }

        template < class L >
        inline void
        STRING< L >::Read( IStream& Stream )
        {
            Read( Stream, *this );
        }

        template < class L >
        inline void
        STRING< L >::Read( IStream& Stream, std::string& Source )
        {
            length_type l = 0;
            Stream >> l;
            if ( l > 0 )
            {
                boost::scoped_array< char > c( new char[ l ] );

                Stream.read( c.get( ), l );
                Source.assign( c.get( ) );
            }
            else
            {
                Source.assign( "" );
            }
        }

        template < class L >
        inline void
        STRING< L >::Write( OStream& Stream ) const
        {
            Write( Stream, *this );
        }

        template < class L >
        inline void
        STRING< L >::Write( OStream& Stream, const std::string& Source )
        {
            length_type l( Source.length( ) + 1 );

            Stream << l;
            Stream.write( Source.c_str( ), l );
        }

        template < class L >
        inline void
        STRING< L >::length_error( const std::string& Buffer )
        {
            if ( Buffer.length( ) > MAX_STRING_LENGTH )
            {
                std::ostringstream msg;

                msg << "maximum size of STRING exceeded: " << Buffer.length( )
                    << " > " << MAX_STRING_LENGTH;
                throw std::length_error( msg.str( ) );
            }
        }

        template < class L >
        inline void
        STRING< L >::length_error( const char* Buffer )
        {
            if ( strlen( Buffer ) > MAX_STRING_LENGTH )
            {
                std::ostringstream msg;

                msg << "maximum size of STRING exceeded: " << strlen( Buffer )
                    << " > " << MAX_STRING_LENGTH;
                throw std::length_error( msg.str( ) );
            }
        }

        inline void
        AppendComment( std::string&              Dest,
                       const std::string&        Text,
                       const cmn_streamsize_type MAX = ~( INT_2U( 0 ) ) )
        {
            const cmn_streamsize_type max_allowing_for_null{ MAX - 1 };

            if ( ( Dest.size( ) > 0 ) &&
                 ( Dest == Text ) )
              {
                // When Dest and Text are identical, then just return Dest as Text
                // provides no additional meaningful information.
                return;
              }
            if ( Dest.size( ) )
            {
                // When adding to an existing string, add a newline
                std::string         newline( "\n" );
                cmn_streamsize_type used{ Dest.length( ) };
                cmn_streamsize_type length{ std::min(
                    ( ( max_allowing_for_null < used )
                          ? 0
                          : max_allowing_for_null - used ),
                    newline.length( ) ) };

                Dest += newline.substr( 0, length );
            }
            {
                // Put the Text at the end of Dest
                cmn_streamsize_type used{ Dest.length( ) };
                cmn_streamsize_type length{ std::min(
                    ( ( max_allowing_for_null < used )
                          ? 0
                          : max_allowing_for_null - used ),
                    Text.length( ) ) };

                Dest += Text.substr( 0, length );
            }
        }

        /*===================================================================
        ===================================================================*/

        template < class L >
        class STRING_SHADOW
        {
        public:
            typedef L           length_type;
            typedef std::string element_type;

            static const length_type MAX_STRING_LENGTH;

            STRING_SHADOW( const std::string& Value );

            /* Calculate the number of bytes needed to write this object */
            INT_8U Bytes( ) const;

            void Read( IStream& Stream );

            void Write( OStream& Stream ) const;

        private:
            const element_type& m_string;

            static void length_error( const element_type& Value );

        }; /* class - STRING_SHADOW */

        template < class L >
        const L STRING_SHADOW< L >::MAX_STRING_LENGTH = ~( L( 0 ) );

        template < class L >
        STRING_SHADOW< L >::STRING_SHADOW( const element_type& Value )
            : m_string( Value )
        {
        }

        template < class L >
        INT_8U
        STRING_SHADOW< L >::Bytes( ) const
        {
            return m_string.length( ) /* Length of string */
                + 1 /* space for the null character */
                + sizeof( length_type ); /* length to hold the size */
        }

        template < class L >
        void
        STRING_SHADOW< L >::Read( IStream& Stream )
        {
            length_type l = 0;
            Stream >> l;
            if ( l > 0 )
            {
                boost::scoped_array< char > c( new char[ l ] );

                Stream.read( c.get( ), l );
                const_cast< element_type& >( m_string ).assign( c.get( ) );
            }
            else
            {
                const_cast< element_type& >( m_string ).assign( "" );
            }
        }

        template < class L >
        void
        STRING_SHADOW< L >::Write( OStream& Stream ) const
        {
            length_type l( m_string.length( ) + 1 );
            Stream << l;
            Stream.write( m_string.c_str( ), l );
        }

        template < class L >
        inline void
        STRING_SHADOW< L >::length_error( const element_type& Buffer )
        {
            if ( Buffer.length( ) > MAX_STRING_LENGTH )
            {
                std::ostringstream msg;

                msg << "maximum size of STRING exceeded: " << Buffer.length( )
                    << " > " << MAX_STRING_LENGTH;
                throw std::length_error( msg.str( ) );
            }
        }
    } /* namespace Common */

} /* namespace FrameCPP */
#endif /* ! defined(SWIG) */

#endif /* FrameCPP__COMMON__STRING_HH */
