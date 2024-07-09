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

#ifndef FrameCPP__COMMON__BASE_MEMORY_BUFFER_HH
#define FrameCPP__COMMON__BASE_MEMORY_BUFFER_HH

#if !defined( SWIGIMPORTED )
#include <list>
#include <iosfwd>
#include <streambuf>
#endif /* !defined(SWIGIMPORTED) */

#include "ldastoolsal/types.hh"
#include "ldastoolsal/System.hh"

#include "framecpp/Common/FrameBufferInterface.hh"

namespace FrameCPP
{
    namespace Common
    {
        //-------------------------------------------------------------------
        /// \brief Handles a read-only memory stream
        ///
        /// This class is to be used with an IFrameStream to provide
        /// a mechanism to read frames that are currently in memory.
        //-------------------------------------------------------------------
        class ROMemoryStreamBuf : public std::streambuf
        {
        public:
            typedef std::streambuf buffer_type;

            typedef buffer_type::char_type char_type;
            typedef buffer_type::pos_type  pos_type;
            typedef buffer_type::off_type  off_type;
            typedef buffer_type::pos_type  size_type;
            typedef buffer_type::int_type  int_type;

            //-----------------------------------------------------------------
            /// \brief Default constructor
            ///
            /// \sa setbuf
            //-----------------------------------------------------------------
            ROMemoryStreamBuf( );

        protected:
            //-----------------------------------------------------------------
            /// \brief Repositions the next pointer in the input sequence
            ///
            /// \param[in] Pos
            ///     Absolute position to set the position indicator to.
            /// \param[in] Which
            ///     Defines which of the input sequences to affect.
            ///     It can be one or a combination of the following constants:
            ///     <Table>
            ///       <TR>
            ///         <TH>Constant</TH>
            ///         <TH>Explanation</TH>
            ///       </TR>
            ///       <TR>
            ///         <TD>in</TD>
            ///         <TD>Affect the input sequence</TD>
            ///       </TR>
            ///       <TR>
            ///         <TD>out</TD>
            ///         <TD>Affect the output sequence</TD>
            ///       </TR>
            ///     </Table>
            ///
            /// \return
            ///     The resulting absolute position as defined by the
            ///     position indicator.
            //-----------------------------------------------------------------
            virtual pos_type seekpos( pos_type                Pos,
                                      std::ios_base::openmode Which );

            //-----------------------------------------------------------------
            /// \brief Repositions the next pointer in the input sequence
            ///
            /// \param[in] Off
            ///     Relative position to set the position indicator to.
            /// \param[in] Way
            ///     Defines base position to apply relative offset to.
            ///     It can be one of the following constants:
            ///     <Table>
            ///       <TR>
            ///         <TH>Constant</TH>
            ///         <TH>Explanation</TH>
            ///       </TR>
            ///       <TR>
            ///         <TD>beg</TD>
            ///         <TD>The beginning of the stream</TD>
            ///       </TR>
            ///       <TR>
            ///         <TD>end</TD>
            ///         <TD>The ending of the stream</TD>
            ///       </TR>
            ///       <TR>
            ///         <TD>cur</TD>
            ///         <TD>The current position of the stream</TD>
            ///       </TR>
            ///     </Table>
            /// \param[in] Which
            ///     Defines which of the input sequences to affect.
            ///     It can be one or a combination of the following constants:
            ///     <Table>
            ///       <TR>
            ///         <TH>Constant</TH>
            ///         <TH>Explanation</TH>
            ///       </TR>
            ///       <TR>
            ///         <TD>in</TD>
            ///         <TD>Affect the input sequence</TD>
            ///       </TR>
            ///       <TR>
            ///         <TD>out</TD>
            ///         <TD>Affect the output sequence</TD>
            ///       </TR>
            ///     </Table>
            ///
            /// \return
            ///     The resulting absolute position as defined by the
            ///     position indicator.
            //-----------------------------------------------------------------
            virtual pos_type seekoff( off_type                Off,
                                      std::ios_base::seekdir  Way,
                                      std::ios_base::openmode Which );

            //-----------------------------------------------------------------
            /// \brief Provides the section of memory from which to read.
            ///
            /// \param[in] S
            ///     Starting address of memory to manage as input buffer.
            /// \param[in] N
            ///     Size of memory buffer.
            ///
            /// \return
            ///     Returns this.
            //-----------------------------------------------------------------
            virtual buffer_type* setbuf( char_type* S, std::streamsize N );

        private:
            //-----------------------------------------------------------------
            /// \brief Returns the current position relative to the start
            ///
            /// \return
            ///     The absolute position as defined by the position
            ///     indicator.
            //-----------------------------------------------------------------
            pos_type position( );
        };

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
        ///
        /// char			buf[256];
        /// BaseMemoryBuffer	imb( );
        ///
        /// imb.pubsetbuf( &(buf[0], sizeof( buf ) );
        ///
        /// IFrameStream	ifs_mem( false, &imb );
        ///
        /// \endcode
        ///
        //===================================================================
        template < typename BT >
        class BaseMemoryBufferT : public FrameBufferInterface, public BT
        {
        public:
            typedef BT                              buffer_type;
            typedef typename buffer_type::char_type char_type;
            typedef typename buffer_type::pos_type  pos_type;
            typedef typename buffer_type::pos_type  size_type;

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
            BaseMemoryBufferT( );

            //-----------------------------------------------------------------
            /// \brief Destructor
            //-----------------------------------------------------------------
            virtual ~BaseMemoryBufferT( );

            //-----------------------------------------------------------------
            /// \brief Returns true if filtering happens internally; false
            /// otherwise
            //-----------------------------------------------------------------
            bool FilterInternally( ) const;

        protected:
            friend class IStream;
            friend class OStream;

            //-----------------------------------------------------------------
            /// \brief Initialization of the buffer
            //-----------------------------------------------------------------
            virtual void buffer( );

        private:
            //-----------------------------------------------------------------
            /// \brief Perform filtering operations on the stream
            //-----------------------------------------------------------------
            virtual void filter( const char_type* Begin, const char_type* End );
        };

        //-------------------------------------------------------------------
        // Simple aliases
        //-------------------------------------------------------------------
        typedef BaseMemoryBufferT< ROMemoryStreamBuf > ReadOnlyMemoryBuffer;

    } // namespace Common
} // namespace FrameCPP

#endif /* FrameCPP__COMMON__BASE_MEMORY_BUFFER_HH */
