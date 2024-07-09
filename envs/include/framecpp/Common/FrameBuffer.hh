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

#ifndef FrameCPP__COMMON__FRAME_BUFFER_HH
#define FrameCPP__COMMON__FRAME_BUFFER_HH

#if !defined( SWIGIMPORTED )
#include <list>
#include <fstream>

#include <boost/scoped_array.hpp>
#endif /* !defined(SWIGIMPORTED) */

#include "ldastoolsal/types.hh"
#include "ldastoolsal/fstream.hh"
#include "ldastoolsal/System.hh"

#include "framecpp/Common/FrameBufferInterface.hh"

namespace FrameCPP
{
    namespace Common
    {
        //===================================================================
        /// \brief Buffer appropriate for caching frame data
        //===================================================================
        template < typename BT >
        class FrameBuffer : public FrameBufferInterface, public BT
        {
        public:
            /// \brief Type of self
            typedef FrameBuffer< BT > buffer_type;

            typedef BT element_type;

            /// \brief type representing a character in the stream.
            typedef typename BT::char_type char_type;

            /// \brief integer type
            typedef typename BT::int_type int_type;
            /// \brief type appropriate for holding stream position information
            typedef typename BT::pos_type pos_type;
            /// \brief type apprpriate to hold stream offset request
            typedef typename BT::off_type off_type;

            using BT::pubsetbuf;

            using BT::epptr;
            using BT::pbase;
            using BT::pptr;

            using BT::eback;
            using BT::egptr;
            using BT::gptr;

            /// \brief constructor
            FrameBuffer( std::ios::openmode Mode,
                         bool               ParentAutoDelete = true );

            virtual void FilterAdd( FrameCPP::Common::StreamFilter* Filter );

            virtual void FilterRemove( FrameCPP::Common::StreamFilter* Filter );

            /// \brief Returns true if filtering happens internally; false
            /// otherwise
            bool FilterInternally( ) const;

            FrameBuffer< BT >* close( );

            FrameBuffer< BT >* open( const std::string& Filename,
                                     std::ios::openmode Mode );
            void               UseMemoryMappedIO( bool Value );

        protected:
            friend class IStream;
            friend class OStream;

            /// \brief Routine to register if the caller has specified a buffer
            virtual FrameBuffer< BT >* setbuf( char_type*      S,
                                               std::streamsize N );

            /// \brief Establish buffering
            virtual void buffer( );

        private:
            /// \brief Establish the size of the current user buffer.
            void set_user_buf( const char_type* S, std::streamsize N );

            /// \brief Mark the current position in the buffer
            void mark( const char_type* Offset = (const char_type*)0 );

            /// \brief Perform filtering operations on the stream
            virtual void filter( const char_type* Begin, const char_type* End );

            /// \brief State of user supplied buffer
            bool m_buffer_user_supplied;

            boost::scoped_array< typename BT::char_type > m_buffer;

            /// \brief Size of the internal buffer
            std::streamsize m_buffer_size;

            /// \brief Location of the user specified buffer
            const char_type* m_user_buf;
            /// \brief Size of the user specified buffer
            std::streamsize m_user_buf_size;

            INT_8U m_bytes_filtered;

            std::ios::openmode m_mode;
        };

        template < typename BT >
        inline void
        FrameBuffer< BT >::set_user_buf( const char_type* S, std::streamsize N )
        {
            m_user_buf = S;
            m_user_buf_size = N;
        }

        template < typename BT >
        inline void
        FrameBuffer< BT >::filter( const char_type* Begin,
                                   const char_type* End )

        {
#if LM_DEBUG_OUTPUT || LM_DEBUG_INPUT
            if ( 1 )
            {
                std::cerr << "FrameBuffer< BT >::filter:"
                          << " ENTRY"
                          << " [ " << __LINE__ << ": " << __FILE__ << " ]"
                          << std::endl;
            }
#endif /* LM_DEBUG_OUTPUT || LM_DEBUG_INPUT */

            if ( ( Begin == (const char_type*)0 ) || ( Begin == End ) )
            {
#if LM_DEBUG_OUTPUT || LM_DEBUG_INPUT
                if ( 1 )
                {
                    std::cerr << "FrameBuffer< BT >::filter:"
                              << " empty buffer"
                              << " [ " << __LINE__ << ": " << __FILE__ << " ]"
                              << std::endl;
                }
#endif /* LM_DEBUG_OUTPUT || LM_DEBUG_INPUT */
                return;
            }

            if ( FilterInternally( ) )
            {
                m_bytes_filtered += ( End - Begin ) * sizeof( char_type );

#if LM_DEBUG_OUTPUT || LM_DEBUG_INPUT
                if ( 1 )
                {
                    std::cerr << "DEBUG: filter:"
                              << " processing " << m_filters.size( )
                              << " filters"
                              << " [ " << __LINE__ << ": " << __FILE__ << " ]"
                              << std::endl;
                }
#endif /* LM_DEBUG_OUTPUT || LM_DEBUG_INPUT */
                for ( filters_type::const_iterator cur = m_filters.begin( ),
                                                   last = m_filters.end( );
                      cur != last;
                      ++cur )
                {
                    if ( *cur )
                    {
                        INT_8U           length = End - Begin;
                        const char_type* start = Begin;

                        const char_type* pos =
                            reinterpret_cast< const char_type* >(
                                ( *cur )->Offset( ) );

                        if ( m_mode & std::ios::in )
                        {
                            if ( ( start >= eback( ) ) &&
                                 ( start <= egptr( ) ) && ( pos >= start ) &&
                                 ( pos <= egptr( ) ) )
                            {
                                start = ( pos ) ? pos : eback( );
                                length = End - start;
                            }
                        }
                        else if ( m_mode & std::ios::out )
                        {
                            if ( ( start >= pbase( ) ) &&
                                 ( start <= epptr( ) ) && ( pos >= start ) &&
                                 ( pos <= epptr( ) ) )
                            {
                                start = ( pos ) ? pos : pbase( );
                                length = End - start;
                            }
                        }
#if LM_DEBUG_OUTPUT || LM_DEBUG_INPUT
                        if ( 1 )
                        {
                            std::cerr
                                << "DEBUG: filter:"
                                << " m_bytes_filterd: " << m_bytes_filtered
                                << " start: " << (void*)start
                                << " length: " << length << std::endl;
                        }
#endif /* LM_DEBUG_OUTPUT || LM_DEBUG_INPUT */
                        ( *cur )->pubfilter(
                            static_cast< const char* >( start ),
                            length * sizeof( char_type ) );
                    }
                } // if ( FilterInternally( ) )
                mark( );
            }
#if LM_DEBUG_OUTPUT || LM_DEBUG_INPUT
            if ( 1 )
            {
                std::cerr << "FrameBuffer< BT >::filter:"
                          << " EXIT"
                          << " [ " << __LINE__ << ": " << __FILE__ << " ]"
                          << std::endl;
            }
#endif /* LM_DEBUG_OUTPUT || LM_DEBUG_INPUT */
        }

        template < typename BT >
        FrameBuffer< BT >::FrameBuffer( std::ios::openmode Mode,
                                        bool               ParentAutoDelete )
            : m_buffer_user_supplied( false ), m_buffer_size( 0 ),
              m_bytes_filtered( 0 ), m_mode( Mode )
        {
            AutoDelete( ParentAutoDelete );
        }

        template < typename BT >
        void
        FrameBuffer< BT >::FilterAdd( FrameCPP::Common::StreamFilter* Filter )
        {
            if ( Filter )
            {
                if ( FilterInternally( ) )
                {
                    if ( m_mode & std::ios::in )
                    {
                        Filter->Offset( gptr( ) );
                    }
                    else if ( m_mode & std::ios::out )
                    {
                        Filter->Offset( pptr( ) );
                    }
                } // if ( FilterInternally( ) )
            }
            FrameBufferInterface::FilterAdd( Filter );
        }

        template < typename BT >
        void
        FrameBuffer< BT >::FilterRemove(
            FrameCPP::Common::StreamFilter* Filter )
        {
            filters_type::size_type s = m_filters.size( );
            FrameBufferInterface::FilterRemove( Filter );
            if ( FilterInternally( ) )
            {
                if ( m_filters.size( ) < s )
                {
                    const char_type* offset =
                        reinterpret_cast< const char_type* >(
                            Filter->Offset( ) );

                    if ( m_mode & std::ios::in )
                    {
                        if ( offset == (const char_type*)0 )
                        {
                            offset = eback( );
                        }
                        Filter->pubfilter( offset, gptr( ) - offset );
                    }
                    else if ( m_mode & std::ios::out )
                    {
                        if ( offset == (const char_type*)0 )
                        {
                            offset = pbase( );
                        }
                        Filter->pubfilter( offset, pptr( ) - offset );
                    }
                }
            } // if ( FilterInernally( )
        }

        template < typename BT >
        FrameBuffer< BT >*
        FrameBuffer< BT >::setbuf( char_type* S, std::streamsize N )
        {
            if ( N != std::streamsize( M_BUFFER_SIZE_SYSTEM ) )
            {
                m_buffer_user_supplied = true;
                BT::setbuf( S, N );
            }
            return this;
        }

        template < typename BT >
        void
        FrameBuffer< BT >::buffer( )
        {
            if ( m_buffer_user_supplied == false )
            {
                //---------------------------------------------------------------
                // Allocation of the default buffer
                //---------------------------------------------------------------
                m_buffer.reset(
                    new typename BT::char_type[ M_BUFFER_SIZE_DEFAULT ] );
                BT::setbuf( m_buffer.get( ), M_BUFFER_SIZE_DEFAULT );
            }
        }
    } // namespace Common
} // namespace FrameCPP

#include "framecpp/Common/FrameBuffer.icc"

#endif /* FrameCPP__COMMON__FRAME_BUFFER_HH */
