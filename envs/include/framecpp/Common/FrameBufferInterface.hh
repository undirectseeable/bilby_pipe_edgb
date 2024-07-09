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

#ifndef FrameCPP__COMMON__FRAME_BUFFER_INTERFACE_HH
#define FrameCPP__COMMON__FRAME_BUFFER_INTERFACE_HH

#if !defined( SWIGIMPORTED )
#include <iostream>
#include <list>

#include <boost/shared_ptr.hpp>
#endif /* !defined(SWIGIMPORTED) */

#include "ldastoolsal/types.hh"

#include "framecpp/Common/FrameSpec.hh"
#include "framecpp/Common/StreamFilter.hh"

namespace FrameCPP
{
    namespace Common
    {
        //-------------------------------------------------------------------
        // Forward Declarations
        /// \cond EXCLUDE
        //-------------------------------------------------------------------
        class FrameH;
        class FrEndOfFile;
        class FrHeader;
        class FrSH;
        class StreamRefInterface;

        //-------------------------------------------------------------------
        // Forward Declarations
        /// \endcond
        //-------------------------------------------------------------------

        //===================================================================
        // \brief Interface definition to Frame Buffer
        //===================================================================
        class FrameBufferInterface
        {
        public:
            //-----------------------------------------------------------------
            /// \brief Scan buffers conforming to the frame specification
            //-----------------------------------------------------------------
            class Scanner
            {
            public:
                typedef start_time_normalized_type start_time_type;
                typedef delta_t_normalized_type    delta_t_type;

                //---------------------------------------------------------------
                /// \brief Constructor
                //---------------------------------------------------------------
                Scanner( );

                //---------------------------------------------------------------
                /// \brief Destructor
                ///
                /// \note
                ///   Need to have an explicit destructor since there are
                ///   virtual functions.
                //---------------------------------------------------------------
                virtual ~Scanner( );

                //---------------------------------------------------------------
                /// \brief type for number of bytes to read and size of buffer
                //---------------------------------------------------------------
                typedef INT_8U size_type;

                //---------------------------------------------------------------
                /// \brief Retrieve the duration of the stream
                //---------------------------------------------------------------
                delta_t_type DeltaT( ) const;

                //---------------------------------------------------------------
                /// \brief Add a buffer to the frame file memory image
                ///
                /// \param[in] Buffer
                ///     The buffer to scan
                /// \param[in] Size
                ///     The number of bytes in Buffer
                //---------------------------------------------------------------
                virtual void NextBlock( const char* Buffer, size_type Size );

                //---------------------------------------------------------------
                /// \brief Return the number of bytes to be made available
                //---------------------------------------------------------------
                size_type NextBlockSize( ) const;

                //---------------------------------------------------------------
                /// \brief Return the current position in the stream being
                /// scanned
                //---------------------------------------------------------------
                size_type Position( ) const;

                //---------------------------------------------------------------
                /// \brief Check if a complete frame file is ready for
                /// processing
                //---------------------------------------------------------------
                bool Ready( ) const;

                //---------------------------------------------------------------
                /// \brief Initialize buffer to accumulate a frame file
                //---------------------------------------------------------------
                virtual void Reset( );

                //---------------------------------------------------------------
                /// \brief Retrieve the start time of the stream
                //---------------------------------------------------------------
                start_time_type StartTime( ) const;

            private:
                static const size_type RESET_NEXT_BLOCK_SIZE;

                boost::shared_ptr< FrHeader >           file_header;
                boost::shared_ptr< FrHeader >           file_header_base;
                bool                                    frame_file_cached;
                FrameSpec::Info*                        frame_spec;
                boost::shared_ptr< FrameH >             frame_h;
                FrameSpec::Info::frame_object_types     frame_h_id;
                const char*                             frame_h_name;
                boost::shared_ptr< FrEndOfFile >        fr_end_of_file;
                FrameSpec::Info::frame_object_types     fr_end_of_file_id;
                const char*                             fr_end_of_file_name;
                boost::shared_ptr< FrSH >               fr_sh;
                boost::shared_ptr< StreamRefInterface > stream_ref;
                size_type                               next_block_size;
                size_type                               position;
                INT_2U                                  frame_count;

                start_time_type start_time;
                start_time_type end_time;
            };

            typedef std::streambuf::char_type char_type;
            typedef INT_4U                    buffer_size_type;

            /// \brief The default size for buffered input and output.
            static const buffer_size_type M_BUFFER_SIZE_DEFAULT;
            static const buffer_size_type M_BUFFER_SIZE_SYSTEM =
                ~buffer_size_type( 0 );

            FrameBufferInterface( );

            virtual ~FrameBufferInterface( );

            bool AutoDelete( ) const;

            void AutoDelete( bool Value );

            //-----------------------------------------------------------------
            /// \brief Adds a filter to the stream
            ///
            /// \param[in] Filter
            ///     Filter function to add to the stream
            //-----------------------------------------------------------------
            virtual void FilterAdd( FrameCPP::Common::StreamFilter* Filter );

            //-----------------------------------------------------------------
            /// \brief Removes a filter from the stream
            ///
            /// \param[in] Filter
            ///     Filter function to remove from the stream
            //-----------------------------------------------------------------
            virtual void FilterRemove( FrameCPP::Common::StreamFilter* Filter );

            virtual bool FilterInternally( ) const = 0;
            virtual void buffer( ) = 0;

            template < class DT >
            void         filter( const DT& Data );
            virtual void filter( const char_type* Start,
                                 const char_type* End ) = 0;

            void FilterBuffer( const char* Begin, const char* End );

            //-----------------------------------------------------------------
            /// \brief Retrieve the string identification of the buffer.
            ///
            /// \return
            ///     An identifier associated with the open buffer.
            //-----------------------------------------------------------------
            const std::string& BufferId( ) const;

        protected:
            /// \brief Type specifying the container holding the active filters.
            typedef std::list< FrameCPP::Common::StreamFilter* > filters_type;

            /// \brief Container holding all active filters
            filters_type m_filters;

            void bufferId( const std::string& Id );

        private:
            bool m_auto_delete;

            std::string m_stream_id;
        };

        //-------------------------------------------------------------------
        //-------------------------------------------------------------------
        inline FrameBufferInterface::Scanner::~Scanner( )
        {
        }

        //-------------------------------------------------------------------
        //-------------------------------------------------------------------
        inline FrameBufferInterface::Scanner::delta_t_type
        FrameBufferInterface::Scanner::DeltaT( ) const
        {
            return end_time - start_time;
        }

        //-------------------------------------------------------------------
        //-------------------------------------------------------------------
        inline FrameBufferInterface::Scanner::size_type
        FrameBufferInterface::Scanner::NextBlockSize( ) const
        {
            return next_block_size;
        }

        //-------------------------------------------------------------------
        //-------------------------------------------------------------------
        inline FrameBufferInterface::Scanner::size_type
        FrameBufferInterface::Scanner::Position( ) const
        {
            return position;
        }

        //-------------------------------------------------------------------
        //-------------------------------------------------------------------
        inline bool
        FrameBufferInterface::Scanner::Ready( ) const
        {
            return frame_file_cached;
        }

        //-------------------------------------------------------------------
        //-------------------------------------------------------------------
        inline FrameBufferInterface::Scanner::start_time_type
        FrameBufferInterface::Scanner::StartTime( ) const
        {
            return start_time;
        }

        //-------------------------------------------------------------------
        //-------------------------------------------------------------------
        inline bool
        FrameBufferInterface::AutoDelete( ) const
        {
            return m_auto_delete;
        }

        //-------------------------------------------------------------------
        //-------------------------------------------------------------------
        inline void
        FrameBufferInterface::AutoDelete( bool Value )
        {
            m_auto_delete = Value;
        }

        //-------------------------------------------------------------------
        //-------------------------------------------------------------------
        inline const std::string&
        FrameBufferInterface::BufferId( ) const
        {
            return m_stream_id;
        }

        //-------------------------------------------------------------------
        //-------------------------------------------------------------------
        inline void
        FrameBufferInterface::bufferId( const std::string& Id )
        {
            m_stream_id = Id;
        }

        //-------------------------------------------------------------------
        //-------------------------------------------------------------------
        template < class DT >
        inline void
        FrameBufferInterface::filter( const DT& Data )
        {
            filter( reinterpret_cast< const char_type* >( &Data ),
                    reinterpret_cast< const char_type* >( &Data +
                                                          sizeof( Data ) ) );
        }
    } // namespace Common
} // namespace FrameCPP

#endif /* FrameCPP__COMMON__FRAME_BUFFER_INTERFACE_HH */
