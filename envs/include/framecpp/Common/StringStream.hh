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

#ifndef COMMON__STRINGSTREAM_HH
#define COMMON__STRINGSTREAM_HH

#include <iostream>
#include <sstream>

#include "ldastoolsal/reverse.hh"

#include "framecpp/Common/STRING.hh"

namespace FrameCPP
{
    namespace Common
    {
        class IStringStream
        {
        public:
            typedef std::istringstream          base_stream_type;
            typedef base_stream_type::char_type char_type;
            typedef std::streamsize             streamsize_type;
            typedef std::streamoff              streamoff_type;
            typedef std::ios_base::seekdir      seekdir_type;

            IStringStream( const std::string& Source, bool ByteSwap );

            IStringStream( const char_type* Source,
                           streamsize_type  SourceSize,
                           bool             ByteSwap );

            bool good( ) const;

            IStringStream& seekg( streamsize_type Position );

            IStringStream& seekg( streamoff_type Offset, seekdir_type Way );

            streamsize_type tellg( );

            template < typename L >
            IStringStream& operator>>( STRING< L >& Data );

            template < typename DT >
            IStringStream& operator>>( DT& Data );

        private:
            static const std::string SOURCE_STRING_NULL;
            const std::string&       source_string;
            const char_type*         source_char_array;
            const streamsize_type    source_char_array_size;
            mutable base_stream_type stream;
            bool                     byte_swap;
            mutable bool             initialized;

            void initialize( ) const;
        };

        inline IStringStream::IStringStream( const std::string& Source,
                                             bool               ByteSwap )
            : source_string( Source ), source_char_array( NULL ),
              source_char_array_size( 0 ), byte_swap( ByteSwap ),
              initialized( false )
        {
        }

        inline IStringStream::IStringStream( const char_type* Source,
                                             streamsize_type  SourceSize,
                                             bool             ByteSwap )
            : source_string( SOURCE_STRING_NULL ), source_char_array( Source ),
              source_char_array_size( SourceSize ), byte_swap( ByteSwap ),
              initialized( false )
        {
        }

        inline bool
        IStringStream::good( ) const
        {
            initialize( );
            return stream.good( );
        }

        inline IStringStream&
        IStringStream::seekg( streamsize_type Position )
        {
            initialize( );
            stream.seekg( Position );
            return *this;
        }

        inline IStringStream&
        IStringStream::seekg( streamoff_type Offset, seekdir_type Way )
        {
            initialize( );
            stream.seekg( Offset, Way );
            return *this;
        }

        inline IStringStream::streamsize_type
        IStringStream::tellg( )
        {
            initialize( );
            return stream.tellg( );
        }

        template < typename L >
        inline IStringStream&
        IStringStream::operator>>( STRING< L >& Data )
        {
            initialize( );

            L                               len;
            typename STRING< L >::char_type buffer[ 4096 ];

            *this >> len;
            stream.read( buffer, len );
            Data = std::string( buffer, len - 1 );
            return *this;
        }

        template < typename DT >
        inline IStringStream&
        IStringStream::operator>>( DT& Data )
        {
            initialize( );

            stream.read( reinterpret_cast< char_type* >( &Data ),
                         std::streamsize( sizeof( Data ) ) );
            if ( byte_swap )
            {
                reverse< sizeof( DT ) >( &Data, 1 );
            }
            return *this;
        }

        inline void
        IStringStream::initialize( ) const
        {
            if ( !initialized )
            {
                if ( source_char_array )
                {
                    stream.str( std::string( source_char_array,
                                             source_char_array_size ) );
                }
                else
                {
                    stream.str( source_string );
                }
                initialized = true;
            }
        }
    } // namespace Common
} // namespace FrameCPP

#endif /* COMMON__STRINGSTREAM_HH */
