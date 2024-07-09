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

#ifndef FrameCPP_VERSION_4_FrTOCPosition_HH
#define FrameCPP_VERSION_4_FrTOCPosition_HH

#include <algorithm>

#include "framecpp/Version4/STRING.hh"

namespace FrameCPP
{
    namespace Common
    {
        class TOCInfo;
    }

    namespace Version_4
    {
        //===================================================================
        //===================================================================
        class FrTOCPosition
        {
        public:
            Common::FrameSpec::size_type
            Bytes( const Common::StreamBase& Stream ) const;

            typedef INT_4U frame_count_type;
            typedef INT_4U n_type;
            typedef STRING name_type;
            typedef INT_8U position_type;

            typedef std::vector< position_type >     info_type;
            typedef std::map< name_type, info_type > Map_type;
            typedef std::vector< name_type >         key_container_type;

            const key_container_type& GetPositionKeys( ) const;

            const FrTOCPosition& operator=( const FrTOCPosition& Source );

        protected:
            key_container_type m_keys;
            Map_type           m_info;

            FrTOCPosition( );

            FrTOCPosition( Common::IStream& Stream,
                           frame_count_type FrameCount );

            const Map_type& getInfo( ) const;

            Map_type::const_iterator getInfo( const std::string& Name ) const;

            Map_type::const_iterator getInfo( INT_4U Index ) const;

            bool operator==( const FrTOCPosition& RHS ) const;

            void write( Common::OStream& Stream ) const;

            class input_iterator
            {
            public:
                input_iterator( Map_type&                 Destination,
                                info_type::const_iterator Position,
                                frame_count_type          FrameCount )
                    : destination( Destination ), cur_position( Position ),
                      frame_count( FrameCount ), it( Destination.begin( ) )
                {
                }

                void
                operator( )( const Map_type::key_type& Name )
                {
                    typedef Map_type::value_type  value_type;
                    typedef Map_type::mapped_type mapped_type;

                    it = destination.insert(
                        it,
                        value_type(
                            Name,
                            mapped_type( cur_position,
                                         cur_position + frame_count ) ) );
                    cur_position += frame_count;
                }

            private:
                Map_type&                 destination;
                info_type::const_iterator cur_position;
                frame_count_type          frame_count;
                Map_type::iterator        it;
            };
        };

        inline FrTOCPosition::FrTOCPosition( )
        {
        }

        inline FrTOCPosition::FrTOCPosition( Common::IStream& Stream,
                                             INT_4U           FrameCount )
        {
            n_type n;
            Stream >> n;
            if ( n && ( n != ~n_type( 0 ) ) )
            {
                //---------------------------------------------------------------
                // Read in the information
                //---------------------------------------------------------------
                key_container_type::size_type s( n );
                std::vector< position_type >  positions( s * FrameCount );

                m_keys.resize( s );

                Stream >> m_keys >> positions;
                //---------------------------------------------------------------
                // Move into structure.
                //---------------------------------------------------------------
                input_iterator f( m_info, positions.begin( ), FrameCount );

                std::for_each( m_keys.begin( ), m_keys.end( ), f );
            }
        }

        inline Common::FrameSpec::size_type
        FrTOCPosition::Bytes( const Common::StreamBase& Stream ) const
        {
            Common::FrameSpec::size_type retval = sizeof( n_type );
            if ( m_info.size( ) )
            {
                retval += ( m_info.size( ) *
                            ( sizeof( position_type ) *
                              m_info.begin( )->second.size( ) ) );
            }
            for ( Map_type::const_iterator cur = m_info.begin( ),
                                           last = m_info.end( );
                  cur != last;
                  ++cur )
            {
                retval += cur->first.Bytes( );
            }
            return retval;
        }

        inline const FrTOCPosition::key_container_type&
        FrTOCPosition::GetPositionKeys( ) const
        {
            return m_keys;
        }

        inline const FrTOCPosition&
        FrTOCPosition::operator=( const FrTOCPosition& Source )
        {
            m_keys = Source.m_keys;
            m_info = Source.m_info;

            return *this;
        }

        inline const FrTOCPosition::Map_type&
        FrTOCPosition::getInfo( ) const
        {
            return m_info;
        }

        inline FrTOCPosition::Map_type::const_iterator
        FrTOCPosition::getInfo( const std::string& Channel ) const
        {
            return getInfo( ).find( Channel );
        }

        inline FrTOCPosition::Map_type::const_iterator
        FrTOCPosition::getInfo( INT_4U Channel ) const
        {
            const FrTOCPosition::Map_type& i( getInfo( ) );

            if ( Channel >= i.size( ) )
            {
                return i.end( );
            }
            return i.find( m_keys[ Channel ] );
        }

        inline void
        FrTOCPosition::write( Common::OStream& Stream ) const
        {
            //-----------------------------------------------------------------
            // Flatten data so it is streamable
            //-----------------------------------------------------------------
            std::vector< name_type >::size_type s( m_info.size( ) );
            if ( s )
            {
                std::vector< name_type >::size_type fc(
                    m_info.begin( )->second.size( ) );

                std::vector< name_type >     names( s );
                std::vector< position_type > positions( s * fc );
                //---------------------------------------------------------------
                // Copy data for streaming
                //---------------------------------------------------------------
                std::vector< name_type >::iterator cur_name = names.begin( );
                std::vector< position_type >::iterator cur_position =
                    positions.begin( );

                for ( Map_type::const_iterator cur = m_info.begin( ),
                                               last = m_info.end( );
                      cur != last;
                      ++cur, ++cur_name, cur_position += fc )
                {
                    *cur_name = cur->first;
                    std::copy( cur->second.begin( ),
                               cur->second.end( ),
                               cur_position );
                }
                //---------------------------------------------------------------
                // Stream out
                //---------------------------------------------------------------
                Stream << n_type( s ) << names << positions;
            }
            else
            {
                Stream << ~n_type( 0 );
            }
        }
    } // namespace Version_4
} // namespace FrameCPP

#endif /* FrameCPP_VERSION_4_FrTOCPosition_HH */
