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

#ifndef FrameCPP__COMMON__MEMORY_BUFFER_HH
#define FrameCPP__COMMON__MEMORY_BUFFER_HH

#if !defined( SWIGIMPORTED )
#include <list>
#include <iosfwd>

#include <boost/scoped_array.hpp>
#endif /* !defined(SWIGIMPORTED) */

#include "ldastoolsal/types.hh"
#include "ldastoolsal/System.hh"

#include "framecpp/Common/FrameBufferInterface.hh"

namespace FrameCPP
{
    namespace Common
    {
        //===================================================================
        /// \brief Buffer appropriate for caching frame data
        ///
        /// If the buffer is for input, then the buffer needs to be
        /// initialized with the contents.
        /// The initialization needs to be done as via the call to the
        /// str( ) method before the buffer is associated with an
        /// IFrameStream object.
        ///
        /// \tparam BT
        ///     Internal storage type to hold the buffer contents.
        ///
        /// \code
        /// MemoryBuffer	imb( std::ios:in);
        ///
        /// imb.str( frame_file_data );
        ///
        /// IFrameStream	ifs_mem( false, &imb );
        ///
        /// \endcode
        ///
        //===================================================================
        template < typename BT = std::stringbuf >
        class MemoryBufferT : public FrameBufferInterface, public BT
        {
        public:
            typedef BT                              buffer_type;
            typedef typename buffer_type::char_type char_type;

            //-----------------------------------------------------------------
            /// \brief Seed an input buffer for MemoryBufferT
            //-----------------------------------------------------------------
            class Seeder
            {
            public:
                typedef MemoryBufferT::buffer_type buffer_type;
                Seeder( );

                virtual ~Seeder( );

                void         operator( )( buffer_type& Buffer );
                virtual bool operator( )( void ) = 0;

            private:
                buffer_type* output;
            };

            //-----------------------------------------------------------------
            /// \brief Seed an input buffer for MemoryBufferT from buffers
            //-----------------------------------------------------------------
            class BufferSeeder : public Seeder
            {
            public:
                BufferSeeder( );

                virtual bool operator( )( void );
            };

            //-----------------------------------------------------------------
            /// \brief Default constructor
            ///
            /// \param[in] Seed
            ///     Method use for input buffers to move data into
            ///     the new instance.
            /// \param[in] ParentAutoDelete
            ///     True if dynamic memory associated with the temporary
            ///     buffer should be release once this object goes out
            ///     of scope.
            ///
            /// \return
            ///     New class instance.
            //-----------------------------------------------------------------
            MemoryBufferT( std::ios::openmode Mode,
                           const BT&          Source,
                           bool               ParentAutoDelete = true );

            //-----------------------------------------------------------------
            /// \brief Default constructor
            ///
            /// \param[in] Mode
            ///     Specify the I/O mode of the buffer.
            /// \param[in] ParentAutoDelete
            ///     True if dynamic memory associated with the temporary
            ///     buffer should be release once this object goes out
            ///     of scope.
            ///
            /// \return
            ///     New class instance.
            //-----------------------------------------------------------------
            MemoryBufferT( std::ios::openmode Mode,
                           bool               ParentAutoDelete = true );

            //-----------------------------------------------------------------
            /// \brief Default constructor
            ///
            /// \param[in] Seed
            ///     Method use for input buffers to move data into
            ///     the new instance.
            /// \param[in] ParentAutoDelete
            ///     True if dynamic memory associated with the temporary
            ///     buffer should be release once this object goes out
            ///     of scope.
            ///
            /// \return
            ///     New class instance.
            //-----------------------------------------------------------------
            MemoryBufferT( Seeder& Seed, bool ParentAutoDelete = true );

            //-----------------------------------------------------------------
            /// \brief Destructor
            //-----------------------------------------------------------------
            virtual ~MemoryBufferT( );

            //-----------------------------------------------------------------
            /// \brief Returns true if filtering happens internally; false
            /// otherwise
            //-----------------------------------------------------------------
            bool FilterInternally( ) const;

            std::string str( );

            void str( const std::string& S );

        protected:
            friend class IStream;
            friend class OStream;

            //-----------------------------------------------------------------
            /// \brief Routine to register if the caller has specified a buffer
            //-----------------------------------------------------------------
            virtual MemoryBufferT* setbuf( char_type* S, std::streamsize N );

            //-----------------------------------------------------------------
            /// \brief Initialization of the buffer
            //-----------------------------------------------------------------
            virtual void buffer( );

        private:
            boost::scoped_array< char_type > buffer_cache;

            /// \brief State of user supplied buffer
            bool buffer_user_supplied;

            /// \brief Perform filtering operations on the stream
            virtual void filter( const char_type* Begin, const char_type* End );
        };

        //-------------------------------------------------------------------
        // Backwards compatability
        //-------------------------------------------------------------------
        typedef MemoryBufferT<> MemoryBuffer;

    } // namespace Common
} // namespace FrameCPP

#endif /* FrameCPP__COMMON__MEMORY_BUFFER_HH */
