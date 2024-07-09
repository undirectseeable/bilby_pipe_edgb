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

#ifndef FrameCPP__COMMON__StreamFilter_HH
#define FrameCPP__COMMON__StreamFilter_HH

#include "ldastoolsal/types.hh"

#define DEBUG_STREAM_FILTER 0

namespace FrameCPP
{
    namespace Common
    {
        class StreamFilter
        {
        public:
            StreamFilter( );

            virtual ~StreamFilter( );

            const void* Offset( ) const;
            /// \brief
            const void* Offset( const void* Pos );

            /// \brief Public filter call
            void pubfilter( const char* Buffer, INT_8U Size );

        protected:
            virtual void filter( const char* Buffer, INT_8U Size ) = 0;

            const void* m_buffer_pos;
#if DEBUG_STREAM_FILTER
            INT_8U m_bytes_filtered;
#endif /* DEBUG_STREAM_FILTER */
        };

        inline const void*
        StreamFilter::Offset( ) const
        {
            return m_buffer_pos;
        }

        inline const void*
        StreamFilter::Offset( const void* Pos )
        {
            const void* retval = m_buffer_pos;

            m_buffer_pos = Pos;
            return retval;
        }
    } // namespace Common
} // namespace FrameCPP
#endif /* FrameCPP__COMMON__StreamFilter_HH */
