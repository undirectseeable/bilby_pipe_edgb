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

#ifndef FrameCPP__COMMON__TOC_INFO_HH
#define FrameCPP__COMMON__TOC_INFO_HH

#if !defined( SWIGIMPORTED )
#include <cstdarg>
#endif /* ! defined(SWIGIMPORTED) */

#include "ldastoolsal/types.hh"
#include "framecpp/Common/FrameSpec.hh"
#include "framecpp/Common/STRING.hh"

#if !defined( SWIG )

#define WORKING_VIRTUAL_TOCQUERY 0

namespace FrameCPP
{
    namespace Common
    {
        class TOCInfo
        {
        public:
            typedef STRING< INT_2U > string_2_type;

            enum
            {
                DT_CHAR_PTR,
                DT_STRING_2,
                DT_INT_2S,
                DT_INT_2U,
                DT_INT_4S,
                DT_INT_4U,
                DT_INT_8S,
                DT_INT_8U,
                DT_REAL_4,
                DT_REAL_8
            };
            enum
            {
                IC_EOQ, /* End Of Query */
                IC_AMPLITUDE,
                IC_CHANNEL_ID,
                IC_DATA_QUALITY,
                IC_DATA_VALID,
                IC_DETECTOR,
                IC_DETECTOR_PREFIX,
                IC_DT,
                IC_END,
                IC_FRAME,
                IC_GROUP_ID,
                IC_GTIME_N,
                IC_GTIME_S,
                IC_ID,
                IC_LOCAL_TIME,
                IC_NAME,
                IC_RUN,
                IC_START,
                IC_ULEAP_S,
                IC_VERSION
            };

            virtual ~TOCInfo( );

#if WORKING_VIRTUAL_TOCQUERY
            virtual void TOCQuery( int InfoClass, ... ) const = 0;
#else /* WORKING_VIRTUAL_TOCQUERY */
            void TOCQuery( int InfoClass, ... ) const;
#endif /* WORKING_VIRTUAL_TOCQUERY */

            template < class T >
            static int DataType( const T* Data );

            template < class T >
            static int DataType( const T& Data );

        protected:
#if !WORKING_VIRTUAL_TOCQUERY
            virtual void vTOCQuery( int InfoClass, va_list vl ) const = 0;
#endif /* WORKING_VIRTUAL_TOCQUERY */
        };

        inline TOCInfo::~TOCInfo( )
        {
        }

#if !WORKING_VIRTUAL_TOCQUERY
        inline void
        TOCInfo::TOCQuery( int InfoClass, ... ) const
        {
            va_list ap;

            va_start( ap, InfoClass );
            vTOCQuery( InfoClass, ap );
            va_end( ap );
        }
#endif /* ! WORKING_VIRTUAL_TOCQUERY */

        //-------------------------------------------------------------------
        /// \cond ignore
        // Do not process these lines for documentation
        //-------------------------------------------------------------------
        template <>
        inline int
        TOCInfo::DataType< char >( const char* Data )
        {
            return DT_CHAR_PTR;
        }

        template <>
        inline int
        TOCInfo::DataType< TOCInfo::string_2_type >(
            const TOCInfo::string_2_type& Data )
        {
            return DT_STRING_2;
        }

        template <>
        inline int
        TOCInfo::DataType< INT_2U >( const INT_2U& Data )
        {
            return DT_INT_2U;
        }

        template <>
        inline int
        TOCInfo::DataType< INT_2S >( const INT_2S& Data )
        {
            return DT_INT_2S;
        }

        template <>
        inline int
        TOCInfo::DataType< INT_4U >( const INT_4U& Data )
        {
            return DT_INT_4U;
        }

        template <>
        inline int
        TOCInfo::DataType< INT_4S >( const INT_4S& Data )
        {
            return DT_INT_4S;
        }

        template <>
        inline int
        TOCInfo::DataType< INT_8U >( const INT_8U& Data )
        {
            return DT_INT_8U;
        }

        template <>
        inline int
        TOCInfo::DataType< INT_8S >( const INT_8S& Data )
        {
            return DT_INT_8S;
        }

        template <>
        inline int
        TOCInfo::DataType< REAL_4 >( const REAL_4& Data )
        {
            return DT_REAL_4;
        }

        template <>
        inline int
        TOCInfo::DataType< REAL_8 >( const REAL_8& Data )
        {
            return DT_REAL_8;
        }
        //-------------------------------------------------------------------
        // Stop ignorning the generation of documentation
        /// \endcond
        //-------------------------------------------------------------------
    } // namespace Common
} // namespace FrameCPP
#endif /* ! defined(SWIG) */

#endif /* FrameCPP__COMMON__TOC_INFO_HH */
