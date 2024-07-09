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

#ifndef FRAME_CPP_INTERFACE__IFrameStream_HH
#define FRAME_CPP_INTERFACE__IFrameStream_HH

#if !defined( SWIG )
#include <boost/pointer_cast.hpp>
#include <boost/shared_array.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>

#include "framecpp/Common/FrameBuffer.hh"

#include "framecpp/FrameCPP.hh"
#include "framecpp/FrameStream.hh"
#include "framecpp/FrameH.hh"
#include "framecpp/FrAdcData.hh"
#include "framecpp/FrDetector.hh"
#include "framecpp/FrEvent.hh"
#include "framecpp/FrProcData.hh"
#include "framecpp/FrSerData.hh"
#include "framecpp/FrSimData.hh"
#include "framecpp/FrSimEvent.hh"
#include "framecpp/FrTOC.hh"

#endif /* !defined(SWIG) */

namespace FrameCPP
{
    typedef Version::IFrameStream IFrameStream;

    //---------------------------------------------------------------------
    //
    //---------------------------------------------------------------------
    class IFrameFStream
    {
    public:
        enum sub_element_type
        {
            HISTORY = FrameCPP::FrameH::HISTORY,
            DETECT_SIM = FrameCPP::FrameH::DETECT_SIM,
            DETECT_PROC = FrameCPP::FrameH::DETECT_PROC,
            AUX_DATA = FrameCPP::FrameH::AUX_DATA,
            AUX_TABLE = FrameCPP::FrameH::AUX_TABLE,
            TYPE = FrameCPP::FrameH::TYPE,
            USER = FrameCPP::FrameH::USER
        };

        typedef FrameCPP::FrameH::history_type           fr_history_type;
        typedef Common::IFrameStream::frame_library_type frame_library_type;
        typedef Common::IFrameStream::library_revision_type
                                                   library_revision_type;
        typedef Common::IFrameStream::size_type    size_type;
        typedef Common::IFrameStream::version_type version_type;
        typedef boost::shared_ptr< FrameH >        frame_h_type;
        typedef boost::shared_ptr< FrDetector >    fr_detector_type;
        typedef boost::shared_ptr< FrEvent >       fr_event_type;
        typedef INT_4U                             fr_event_offset_type;
        typedef boost::shared_ptr< FrAdcData >     fr_adc_data_type;
        typedef boost::shared_ptr< FrProcData >    fr_proc_data_type;
        typedef boost::shared_ptr< FrSerData >     fr_ser_data_type;
        typedef boost::shared_ptr< FrSimData >     fr_sim_data_type;
        typedef boost::shared_ptr< FrSimEvent >    fr_sim_event_type;
        typedef INT_4U                             fr_sim_event_offset_type;
        typedef boost::shared_ptr< const FrTOC >   toc_ret_type;

        //-------------------------------------------------------------------
        /// \brief Constructor
        ///
        /// \param[in] Filename
        ///     Name of the input frame file
        //-------------------------------------------------------------------
        IFrameFStream( const char* Filename );

        //-------------------------------------------------------------------
        /// \brief Constructor
        ///
        /// \param[in] Filename
        ///     Name of the input frame file
        ///
        /// \param[in] MemoryMappedIO
        ///     True if memory mapped io should be used, false otherwise.
        ///
        /// \param[in] BufferSize
        ///     Number of bytes to use for file buffering.
        //-------------------------------------------------------------------
        IFrameFStream( const char* Filename,
                       bool        MemoryMappedIO,
                       size_t      BufferSize );

        std::string Filename( ) const;

        frame_library_type FrameLibrary( ) const;

        std::string FrameLibraryName( ) const;

        size_type GetNumberOfFrames( ) const;

        toc_ret_type GetTOC( ) const;

        library_revision_type LibraryRevision( ) const;

        fr_detector_type ReadDetector( const std::string& Name );

        fr_adc_data_type ReadFrAdcData( INT_4U             Frame,
                                        const std::string& Channel );

        fr_event_type ReadFrEvent( INT_4U Frame, const std::string& Channel );

        fr_event_type ReadFrEvent( const std::string&   Channel,
                                   fr_event_offset_type Offset );

        fr_history_type ReadFrHistory( INT_4U Frame );

        fr_proc_data_type ReadFrProcData( INT_4U             Frame,
                                          const std::string& Channel );

        fr_ser_data_type ReadFrSerData( INT_4U             Frame,
                                        const std::string& Channel );

        fr_sim_data_type ReadFrSimData( INT_4U             Frame,
                                        const std::string& Channel );

        fr_sim_event_type ReadFrSimEvent( INT_4U             Frame,
                                          const std::string& Channel );

        fr_sim_event_type ReadFrSimEvent( const std::string&       Channel,
                                          fr_sim_event_offset_type Offset );

        frame_h_type ReadFrameN( INT_4U Index );

        frame_h_type ReadFrameNSubset( INT_4U Index, INT_4U Elements );

        frame_h_type ReadNextFrame( );

        version_type Version( ) const;

        static const int  BUFFER_SIZE = 1024 * 1024;
        static const bool MEMORY_MAPPED_IO = false;

    private:
        class iframe_stream_type : public FrameCPP::IFrameStream
        {
        public:
            using FrameCPP::IFrameStream::getTOC;

            iframe_stream_type( buffer_type* Stream )
                : FrameCPP::IFrameStream( Stream ){};

            iframe_stream_type( bool AutoDelete, buffer_type* Stream )
                : FrameCPP::IFrameStream( AutoDelete, Stream ){};
        };

        typedef LDASTools::AL::filebuf                 filebuf_type;
        typedef Common::FrameBuffer< filebuf_type >    frame_buffer_type;
        typedef iframe_stream_type                     frame_stream_type;
        typedef boost::weak_ptr< const Common::FrTOC > toc_type;

        boost::shared_array< CHAR >          m_buffer;
        std::string                          m_filename;
        std::unique_ptr< frame_buffer_type > m_frame_buffer;
        std::unique_ptr< frame_stream_type > m_frame_stream;
        toc_type                             m_toc;
    };

    inline IFrameFStream::IFrameFStream( const char* Filename )
        : m_filename( Filename )
    {
        m_buffer.reset( new CHAR[ BUFFER_SIZE ] );

        m_frame_buffer.reset( new frame_buffer_type( std::ios::in ) );
        m_frame_buffer->pubsetbuf( m_buffer.get( ), BUFFER_SIZE );
        m_frame_buffer->UseMemoryMappedIO( MEMORY_MAPPED_IO );
        m_frame_buffer->open( Filename, std::ios::in | std::ios::binary );

        m_frame_stream.reset(
            new frame_stream_type( false, m_frame_buffer.get( ) ) );
    }

    inline std::string
    IFrameFStream::Filename( ) const
    {
        return m_filename;
    }

    inline IFrameFStream::IFrameFStream(
        const char* Filename,
        bool        MemoryMappedIO,
        size_t      BufferSize = IFrameFStream::BUFFER_SIZE )
    {
        m_buffer.reset( new CHAR[ BufferSize ] );

        m_frame_buffer.reset( new frame_buffer_type( std::ios::in ) );
        m_frame_buffer->pubsetbuf( m_buffer.get( ), BufferSize );
        m_frame_buffer->UseMemoryMappedIO( MemoryMappedIO );
        m_frame_buffer->open( Filename, std::ios::in | std::ios::binary );

        m_frame_stream.reset(
            new frame_stream_type( false, m_frame_buffer.get( ) ) );
        if ( m_frame_stream )
        {
            m_toc = boost::const_pointer_cast< const toc_type::element_type >(
                m_frame_stream->getTOC( ) );
        }
    }

    inline IFrameFStream::frame_library_type
    IFrameFStream::FrameLibrary( ) const
    {
        return m_frame_stream->FrameLibrary( );
    }

    inline std::string
    IFrameFStream::FrameLibraryName( ) const
    {
        return m_frame_stream->FrameLibraryName( );
    }

    inline IFrameFStream::size_type
    IFrameFStream::GetNumberOfFrames( ) const
    {
        return m_frame_stream->GetNumberOfFrames( );
    }

    inline IFrameFStream::toc_ret_type
    IFrameFStream::GetTOC( ) const
    {
        try
        {
            // Ensure the table of contents has been loaded
            m_frame_stream->GetTOC( );
        }
        catch ( ... )
        {
            // case where no talbe of contents was created
        }

        //-----------------------------------------------------------------
        //
        //-----------------------------------------------------------------
        toc_ret_type retval =
            boost::dynamic_pointer_cast< const toc_ret_type::element_type >(
                m_frame_stream->getTOC( ) );

        if ( retval )
        {
            return retval;
        }
        throw std::runtime_error( "No Table of Contents object for Stream" );
    }

    inline IFrameFStream::library_revision_type
    IFrameFStream::LibraryRevision( ) const
    {
        return m_frame_stream->LibraryRevision( );
    }

    inline IFrameFStream::fr_detector_type
    IFrameFStream::ReadDetector( const std::string& Name )
    {

        Common::FrameSpec::ObjectInterface::object_type od(
            m_frame_stream->ReadDetector( Name ) );

        fr_detector_type detector(
            boost::dynamic_pointer_cast< FrDetector >( od ) );

        if ( !detector )
        {
            throw std::range_error( "Unable to read detector" );
        }
        return detector;
    }

    inline IFrameFStream::fr_event_type
    IFrameFStream::ReadFrEvent( INT_4U Frame, const std::string& Channel )
    {
        typedef fr_event_type retval_type;

        Common::FrameSpec::ObjectInterface::object_type o(
            m_frame_stream->ReadFrEvent( Frame, Channel ) );

        retval_type retval(
            boost::dynamic_pointer_cast< retval_type::element_type >( o ) );

        if ( retval )
        {
            return retval;
        }
        throw std::range_error( "Unable to read FrEvent" );
    }

    inline IFrameFStream::fr_event_type
    IFrameFStream::ReadFrEvent( const std::string&   EventType,
                                fr_event_offset_type Offset )
    {
        typedef fr_event_type retval_type;

        Common::FrameSpec::ObjectInterface::object_type o(
            m_frame_stream->ReadFrEvent( EventType, Offset ) );

        retval_type retval(
            boost::dynamic_pointer_cast< retval_type::element_type >( o ) );

        if ( retval )
        {
            return retval;
        }
        throw std::range_error( "Unable to read FrEvent" );
    }

    inline IFrameFStream::fr_adc_data_type
    IFrameFStream::ReadFrAdcData( INT_4U Frame, const std::string& Channel )
    {
        typedef fr_adc_data_type retval_type;

        Common::FrameSpec::ObjectInterface::object_type o(
            m_frame_stream->ReadFrAdcData( Frame, Channel ) );

        retval_type retval(
            boost::dynamic_pointer_cast< retval_type::element_type >( o ) );

        if ( retval )
        {
            return retval;
        }
        throw std::range_error( "Unable to read FrAdcData" );
    }

    inline IFrameFStream::fr_history_type
    IFrameFStream::ReadFrHistory( INT_4U Index )
    {
        typedef IFrameFStream::fr_history_type retval_type;

        Common::FrameSpec::ObjectInterface::object_type o(
            m_frame_stream->ReadFrameNSubset(
                Index, frame_h_type::element_type::HISTORY ) );

        if ( o )
        {
            retval_type retval(
                boost::dynamic_pointer_cast< frame_h_type::element_type >( o )
                    ->RefHistory( ) );

            return retval;
        }
        throw std::range_error( "Unable to read next frame" );
    }

    inline IFrameFStream::fr_proc_data_type
    IFrameFStream::ReadFrProcData( INT_4U Frame, const std::string& Channel )
    {
        return m_frame_stream->ReadFrProcData( Frame, Channel );
    }

    inline IFrameFStream::fr_ser_data_type
    IFrameFStream::ReadFrSerData( INT_4U Frame, const std::string& Channel )
    {
        return m_frame_stream->ReadFrSerData( Frame, Channel );
    }

    inline IFrameFStream::fr_sim_data_type
    IFrameFStream::ReadFrSimData( INT_4U Frame, const std::string& Channel )
    {
        return m_frame_stream->ReadFrSimData( Frame, Channel );
    }

    inline IFrameFStream::fr_sim_event_type
    IFrameFStream::ReadFrSimEvent( INT_4U Frame, const std::string& Channel )
    {
        return m_frame_stream->ReadFrSimEvent( Frame, Channel );
    }

    inline IFrameFStream::fr_sim_event_type
    IFrameFStream::ReadFrSimEvent( const std::string&       SimEventType,
                                   fr_sim_event_offset_type Offset )
    {
        return m_frame_stream->ReadFrSimEvent( SimEventType, Offset );
    }

    inline IFrameFStream::frame_h_type
    IFrameFStream::ReadFrameN( INT_4U Index )
    {
        typedef frame_h_type retval_type;

        Common::FrameSpec::ObjectInterface::object_type o(
            m_frame_stream->ReadFrameN( Index ) );

        retval_type retval(
            boost::dynamic_pointer_cast< retval_type::element_type >( o ) );

        if ( retval )
        {
            return retval;
        }
        throw std::range_error( "Unable to read next frame" );
    }

    inline IFrameFStream::frame_h_type
    IFrameFStream::ReadFrameNSubset( INT_4U Index, INT_4U Elements )
    {
        typedef frame_h_type retval_type;

        Common::FrameSpec::ObjectInterface::object_type o(
            m_frame_stream->ReadFrameNSubset( Index, Elements ) );

        retval_type retval(
            boost::dynamic_pointer_cast< retval_type::element_type >( o ) );

        if ( retval )
        {
            return retval;
        }
        throw std::range_error( "Unable to read frame" );
    }

    inline IFrameFStream::frame_h_type
    IFrameFStream::ReadNextFrame( )
    {
        typedef frame_h_type retval_type;

        Common::FrameSpec::ObjectInterface::object_type o(
            m_frame_stream->ReadNextFrame( ) );

        retval_type retval(
            boost::dynamic_pointer_cast< retval_type::element_type >( o ) );

        if ( retval )
        {
            return retval;
        }
        throw std::range_error( "Unable to read next frame" );
    }

    inline IFrameFStream::version_type
    IFrameFStream::Version( ) const
    {
        return m_frame_stream->Version( );
    }
} // namespace FrameCPP

#endif /* FRAME_CPP_INTERFACE__IFrameStream_HH */
