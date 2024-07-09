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

#ifndef FrameCPP__COMMON__DYNAMIC_MEMORY_BUFFER_HH
#define FrameCPP__COMMON__DYNAMIC_MEMORY_BUFFER_HH

#if !defined( SWIGIMPORTED )
#include <list>
#include <iosfwd>
#endif /* !defined(SWIGIMPORTED) */

#include "ldastoolsal/types.hh"
#include "ldastoolsal/System.hh"

#include "framecpp/Common/MemoryBuffer.hh"

namespace FrameCPP
{
    namespace Common
    {
        //===================================================================
        /// \brief Buffer appropriate for caching frame data
        ///
        /// If the buffer is for input, then the buffer needs to be
        /// initialized with the contents.
        /// The initialization needs to be done as via by reading
        /// chuncks of data and having the class stitch them together
        /// until a complete frame file object is available for
        /// processing.
        ///
        /// \code
        /// //---------------------------------------------------------------
        /// // The following example uses input from a file to show how
        /// // chuncks of data would be requested and then supplied
        /// // to the class for inclussion in the in memory frame file
        /// // stream.
        /// //===============================================================
        /// // Make sure that everything is reset to the initial conditions
        /// //---------------------------------------------------------------
        /// mb.Reset( );
        ///
        /// boost::scoped_array			read_buffer;
        /// DynamicMemoryBuffer::size_type		read_buffer_size = 0;
        /// DynamicMemoryBuffer::size_type		read_size = 0;
        /// std::ifstream				s;
        ///
        /// s.open( filename.c_str( ) );
        /// //---------------------------------------------------------------
        /// // Keep looping till we are informed that a complete frame file
        /// // image is ready for processing
        /// //---------------------------------------------------------------
        /// while ( ! mb.Ready( ) )
        /// {
        ///   //-------------------------------------------------------------
        ///   // Request the number of bytes upon which to wait
        ///   //-------------------------------------------------------------
        ///   read_size = mb.NextBlockSize( );
        ///   //-------------------------------------------------------------
        ///   // Make sure the buffer which hold the temporary results is
        ///   // large enough for the results.
        ///   //-------------------------------------------------------------
        ///   if ( read_buffer_size < read_size )
        ///   {
        ///     read_buffer.reset( new char[ read_size ] );
        ///     read_buffer_size = read_size;
        ///   }
        ///   //-------------------------------------------------------------
        ///   // Read the requested number of bytes, blocking if need be
        ///   //-------------------------------------------------------------
        ///   s.read( read_buffer.get( ), read_size );
        ///   //-------------------------------------------------------------
        ///   // Send them off for processing
        ///   //-------------------------------------------------------------
        ///   mb.NextBlock( read_buffer.get( ), read_size );
        /// }
        /// s.close( );
        ///
        /// \endcode
        ///
        //===================================================================
        template < typename BT = std::stringbuf >
        class DynamicMemoryBufferT : public MemoryBufferT< BT >,
                                     public FrameBufferInterface::Scanner
        {
        public:
            //-----------------------------------------------------------------
            /// \brief Default constructor
            ///
            /// \param[in] ParentAutoDelete
            ///     True if dynamic memory associated with the temporary
            ///     buffer should be release once this object goes out
            ///     of scope.
            ///
            /// \return
            ///     A new class instance.
            //-----------------------------------------------------------------
            DynamicMemoryBufferT( bool ParentAutoDelete = true );

            //-----------------------------------------------------------------
            /// \brief Destructor
            //-----------------------------------------------------------------
            virtual ~DynamicMemoryBufferT( );

            //-----------------------------------------------------------------
            /// \brief Add a buffer to the frame file memory image
            ///
            /// \param[in] Buffer
            ///     The buffer to scan
            /// \param[in] Size
            ///     The number of bytes in Buffer
            //-----------------------------------------------------------------
            virtual void NextBlock( const char* Buffer, size_type Size );

            //-----------------------------------------------------------------
            /// \brief Initialize buffer to accumulate a frame file
            //-----------------------------------------------------------------
            virtual void Reset( );

        private:
            typedef FrameBufferInterface::Scanner scanner_type;

            std::ostringstream accumulated_buffer;
        };

        //-------------------------------------------------------------------
        // Backwards compatability
        //-------------------------------------------------------------------
        typedef DynamicMemoryBufferT<> DynamicMemoryBuffer;

    } // namespace Common
} // namespace FrameCPP

#endif /* FrameCPP__COMMON__DYNAMIC_MEMORY_BUFFER_HH */
