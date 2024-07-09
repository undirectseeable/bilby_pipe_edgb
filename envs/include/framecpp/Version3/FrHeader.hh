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

#ifndef FrameCPP__VERSION_3__FrHeader_HH
#define FrameCPP__VERSION_3__FrHeader_HH

#include <vector>

#include "ldastoolsal/types.hh"

#include "framecpp/Common/FrameSpec.hh"
#include "framecpp/Common/FrHeader.hh"

namespace FrameCPP
{
    namespace Version_3
    {
        class FrHeader : public Common::FrameSpec::Object,
                         public Common::FrHeader
        {
        public:
            static const char* ORIGINATOR_IGWD;

            FrHeader( );

            virtual ~FrHeader( );

            virtual FrHeader* Clone( ) const;

            /// \brief Retrieve the buffer holding the endian bytes for an 8
            /// byte quantity
            const unsigned char* Get8ByteEndianness( ) const;

            /// \brief Return the byte order of the frame
            int GetByteOrder( ) const;

            /// \brief Establish the originator of the frame.
            void SetOriginator( const std::string& Originator );

            virtual Common::FrameSpec::size_type Bytes( ) const;

            virtual Common::FrameSpec::size_type
            Bytes( const Common::StreamBase& Stream ) const;

            virtual bool ByteSwapping( ) const;

            virtual const Common::FrameSpec::Object* Description( ) const;

            //-----------------------------------------------------------------
            /// \brief Constructor - virtual
            //-----------------------------------------------------------------
            virtual FrHeader* Create( istream_type& Stream ) const;

            //-----------------------------------------------------------------
            /// \brief Constructor - virtual
            //-----------------------------------------------------------------
            virtual FrHeader* Create( std::istream& Stream ) const;

            void Filter( Common::StreamFilter& SFilter ) const;

            virtual const char* ObjectStructName( ) const;

            virtual void VerifyObject( Common::Verify&       Verifier,
                                       Common::IFrameStream& Stream ) const;

            /// \brief Write Header to stream
            void Write( Common::OStream& Stream ) const;

            /// \brief comparison operator
            virtual bool
            operator==( const Common::FrameSpec::Object& Obj ) const;

        protected:
            FrHeader( const FrHeader& Source );

            FrHeader( std::istream& Source );

            /// \brief Down grade an object
            virtual demote_ret_type demote( INT_2U          Target,
                                            demote_arg_type Obj,
                                            istream_type*   Stream ) const;

            /// \brief Upgrade an object
            virtual promote_ret_type promote( INT_2U Target,
                                              promote_arg_type,
                                              istream_type* Stream ) const;

        private:
            using Common::FrameSpec::Object::Create;

            static const Common::FrameSpec::Info::frame_object_types
                s_object_id = Common::FrameSpec::Info::FSI_FR_HEADER;

            union FrHeader_type
            {
                struct raw_type
                {
                    unsigned char sizeInt2;
                    unsigned char sizeInt4;
                    unsigned char sizeInt8;
                    unsigned char sizeReal4;
                    unsigned char sizeReal8;

                    unsigned char x1234[ 2 ];
                    unsigned char x12345678[ 4 ];
                    unsigned char x123456789abcdef[ 8 ];

                    unsigned char smallPi[ 4 ];
                    unsigned char bigPi[ 8 ];

                    unsigned char AZ[ 2 ];
                } raw; // struct
                unsigned char block[ sizeof( raw_type ) ];
            } m_data; // union - FrHeader_type

            bool m_reorder_bytes;
            int  m_byte_order;

            FrHeader( istream_type& Stream );
        }; // class - FrHeader

        inline void
        FrHeader::Filter( Common::StreamFilter& SFilter ) const
        {
            Common::FrHeader::Filter( SFilter );
            SFilter.pubfilter( reinterpret_cast< const char* >( &m_data.block ),
                               sizeof( m_data.block ) );
        }

        inline const unsigned char*
        FrHeader::Get8ByteEndianness( ) const
        {
            return m_data.raw.x123456789abcdef;
        }

        inline int
        FrHeader::GetByteOrder( ) const
        {
            return m_byte_order;
        }

    } // namespace Version_3
} // namespace FrameCPP

#endif /* FrameCPP__VERSION_3__FrHeader_HH */
