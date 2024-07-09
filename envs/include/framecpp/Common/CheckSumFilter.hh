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

#ifndef FrameCPP__COMMON__CheckSumFilter_HH
#define FrameCPP__COMMON__CheckSumFilter_HH

#include <boost/scoped_ptr.hpp>

#include "framecpp/Common/CheckSum.hh"
#include "framecpp/Common/StreamFilter.hh"

namespace FrameCPP
{
    namespace Common
    {
        //-------------------------------------------------------------------
        /// \brief Filtering algorythm for calculating checksums.
        //-------------------------------------------------------------------
        class CheckSumFilter : public StreamFilter
        {
        public:
            //-----------------------------------------------------------------
            /// \brief Constructor
            ///
            /// \param[in] Type
            ///     The type of checksum to be calculated.
            ///
            /// \return
            ///     A new instance of the class.
            //-----------------------------------------------------------------
            CheckSumFilter( CheckSum::kind_type Type );

            //-----------------------------------------------------------------
            /// \brief Filter a sequence of bytes
            ///
            /// \param[in] Buffer
            ///     The sequence of bytes to be filter.
            /// \param[in] Size
            ///     The number of bytes in Buffer.
            //-----------------------------------------------------------------
            void Filter( const void* Buffer, INT_8U Size );

            CheckSum* GetChecksum( ) const;

            CheckSum::kind_type Type( ) const;

            INT_4U Value( );

        protected:
            virtual void filter( const char* Buffer, INT_8U Size );

        private:
            boost::scoped_ptr< CheckSum > m_checksum;
        };

        inline void
        CheckSumFilter::Filter( const void* Buffer, INT_8U Size )
        {
            filter( static_cast< const char* >( Buffer ), Size );
        }

        inline CheckSum*
        CheckSumFilter::GetChecksum( ) const
        {
            return m_checksum.get( );
        }

        inline CheckSum::kind_type
        CheckSumFilter::Type( ) const
        {
            if ( m_checksum.get( ) )
            {
                return m_checksum->GetType( );
            }
            return CheckSum::NONE;
        }

        inline INT_4U
        CheckSumFilter::Value( )
        {
            if ( m_checksum.get( ) )
            {
                return m_checksum->value( );
            }
            return 0;
        }
    } // namespace Common
} // namespace FrameCPP
#endif /* FrameCPP__COMMON__CheckSumFilter_HH */
