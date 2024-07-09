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

#ifndef FRAME_CPP_INTERFACE__OFrameStream_HH
#define FRAME_CPP_INTERFACE__OFrameStream_HH

#if !defined( SWIGIMPORTED )
#include <boost/shared_array.hpp>
#include <boost/shared_ptr.hpp>

#include "framecpp/FrameCPP.hh"

#include "framecpp/Common/IOStream.hh"
#include "framecpp/Common/FrameBuffer.hh"
#include "framecpp/Common/FrameStream.hh"
#include "framecpp/FrameH.hh"
#include "framecpp/FrTOC.hh"
#endif /* ! defined(SWIGIMPORTED) */

namespace FrameCPP
{
    typedef Common::OFrameStream OFrameStream;

    class OFrameFStream
    {
    public:
        typedef OFrameStream                stream_type;
        typedef boost::shared_ptr< FrameH > frameh_type;

        OFrameFStream( const char* Filename );
        const FrTOC& GetTOC( ) const;
        stream_type* Stream( );
        void         WriteFrame( frameh_type Frame );
        void         WriteFrame( frameh_type Frame,
                                 INT_2U      CompressionScheme,
                                 INT_2U      CompressionLevel );

    private:
        typedef LDASTools::AL::filebuf               filebuf_type;
        typedef Common::FrameBuffer< filebuf_type >  frame_buffer_type;
        typedef std::unique_ptr< frame_buffer_type > frame_buffer_ptr_type;
        typedef std::unique_ptr< OFrameStream >      stream_ptr_type;
        typedef boost::shared_array< CHAR >          buffer_ptr_type;

        static const int  BUFFER_SIZE = 1024 * 1024;
        static const bool MEMORY_MAPPED_IO = false;

        buffer_ptr_type       m_buffer;
        frame_buffer_ptr_type m_frame_buffer;
        stream_ptr_type       m_frame_stream;
    };

    inline OFrameFStream::OFrameFStream( const char* Filename )
    {
        m_buffer.reset( new CHAR[ BUFFER_SIZE ] );

        m_frame_buffer.reset( new frame_buffer_type( std::ios::out ) );
        m_frame_buffer->pubsetbuf( m_buffer.get( ), BUFFER_SIZE );
        m_frame_buffer->UseMemoryMappedIO( MEMORY_MAPPED_IO );
        m_frame_buffer->open( Filename, std::ios::out | std::ios::binary );

        m_frame_stream.reset( new OFrameStream( m_frame_buffer.release( ) ) );
    }

    inline OFrameFStream::stream_type*
    OFrameFStream::Stream( )
    {
        return m_frame_stream.get( );
    }

    inline void
    OFrameFStream::WriteFrame( frameh_type Frame )
    {
        m_frame_stream->WriteFrame( Frame );
    }

    inline void
    OFrameFStream::WriteFrame( frameh_type Frame,
                               INT_2U      CompressionScheme,
                               INT_2U      CompressionLevel )
    {
        m_frame_stream->WriteFrame(
            Frame, CompressionScheme, CompressionLevel );
    }
} // namespace FrameCPP

#endif /* FRAME_CPP_INTERFACE__OFrameStream_HH */
