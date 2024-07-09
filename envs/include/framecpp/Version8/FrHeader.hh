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

#ifndef FrameCPP__VERSION_8__FrHeader_HH
#define FrameCPP__VERSION_8__FrHeader_HH

#include <memory>
#include <vector>

#include "ldastoolsal/types.hh"

#include "framecpp/Common/FrameSpec.hh"
#include "framecpp/Common/FrHeader.hh"

#include "framecpp/Version8/FrEndOfFile.hh"

namespace FrameCPP
{
    namespace Version_8
    {
        //-------------------------------------------------------------------
        /// \brief Implementation of the frame header structure
        ///
        /// This structure is described in section 4.3.1 of the frame
        /// specification.
        /// Its purpose is to provide a table of standard information
        /// in the host order so the reader can determine what
        /// translations need to occur.
        //-------------------------------------------------------------------
        class FrHeader : public Common::FrameSpec::Object,
                         public Common::FrHeader
        {
        public:
            //-----------------------------------------------------------------
            /// \brief Libraries known to implement the frame specification.
            ///
            /// This enumeration is intended to supply a unique identity for
            /// each library implementing the frame specification.
            /// This information along with the version of the library
            /// and the frame specification,
            /// uniquely identifies an implementation of the frame
            /// specification and can be used to code around problems
            /// with the implementation.
            //-----------------------------------------------------------------
            enum
            {
                //---------------------------------------------------------------
                /// \brief Unknown frame library.
                //---------------------------------------------------------------
                FRAME_LIBRARY_UNKNOWN = 0,
                //---------------------------------------------------------------
                /// \brief Virgo's frameL C implementation of the frame spec.
                //---------------------------------------------------------------
                FRAME_LIBRARY_FRAMEL = 1,
                //---------------------------------------------------------------
                /// \brief LIGO's frameCPP C++ implementation of the frame spec.
                //---------------------------------------------------------------
                FRAME_LIBRARY_FRAMECPP = 2
            };

            typedef FrEndOfFile::chkSumFrHeader_type checksum_type;

            //-----------------------------------------------------------------
            /// \brief File type
            ///
            /// The string "IGWD" to identify the file as an Interferometric
            /// Gravitational Wave Detectors frame file.
            //-----------------------------------------------------------------
            static const char* ORIGINATOR_IGWD;

            //-----------------------------------------------------------------
            /// \brief Constructor
            //-----------------------------------------------------------------
            FrHeader( );

            //-----------------------------------------------------------------
            /// \brief Desctructor
            //-----------------------------------------------------------------
            virtual ~FrHeader( );

            //-----------------------------------------------------------------
            /// \brief Copy Constructor (virtual)
            //-----------------------------------------------------------------
            virtual FrHeader* Clone( ) const;

            //-----------------------------------------------------------------
            /// \brief  Buffer holding the endian bytes for an 8 byte quantity
            //-----------------------------------------------------------------
            const unsigned char* Get8ByteEndianness( ) const;

            //-----------------------------------------------------------------
            /// \brief Return the byte order of the frame
            //-----------------------------------------------------------------
            int GetByteOrder( ) const;

            //-----------------------------------------------------------------
            /// \brief Establish the originator of the frame.
            //-----------------------------------------------------------------
            void SetOriginator( const std::string& Originator );

            //-----------------------------------------------------------------
            /// \brief Calculate the streaming size of the object
            //-----------------------------------------------------------------
            virtual Common::FrameSpec::size_type Bytes( ) const;

            //-----------------------------------------------------------------
            /// \brief Calculate the streaming size of the object
            //-----------------------------------------------------------------
            virtual Common::FrameSpec::size_type
            Bytes( const Common::StreamBase& Stream ) const;

            //-----------------------------------------------------------------
            /// \brief Check if byte swapping is needed.
            //-----------------------------------------------------------------
            virtual bool ByteSwapping( ) const;

            //-----------------------------------------------------------------
            // \brief Retrieve the checksum value
            //-----------------------------------------------------------------
            checksum_type Checksum( ) const;

            //-----------------------------------------------------------------
            /// \brief Retrieve the objects stream description.
            //-----------------------------------------------------------------
            virtual const Common::FrameSpec::Object* Description( ) const;

            //-----------------------------------------------------------------
            /// \brief Constructor ( virtual )
            //-----------------------------------------------------------------
            virtual FrHeader* Create( istream_type& Stream ) const;

            //-----------------------------------------------------------------
            /// \brief Constructor ( virtual )
            //-----------------------------------------------------------------
            virtual FrHeader* Create( std::istream& Stream ) const;

            //-----------------------------------------------------------------
            /// \brief Perform the filter over the bytes streamed.
            ///
            /// \param[in] SFilter
            ///     Filter to be applied to the stream.
            //-----------------------------------------------------------------
            void Filter( Common::StreamFilter& SFilter ) const;

            //-----------------------------------------------------------------
            /// \brief Retrieve the name of the frame structure.
            //-----------------------------------------------------------------
            virtual const char* ObjectStructName( ) const;

            //-----------------------------------------------------------------
            /// \brief Perform verification of the object.
            //-----------------------------------------------------------------
            virtual void VerifyObject( Common::Verify&       Verifier,
                                       Common::IFrameStream& Stream ) const;

            //-----------------------------------------------------------------
            /// \brief Write object to the stream.
            //-----------------------------------------------------------------
            void Write( ostream_type& Stream ) const;

            //-----------------------------------------------------------------
            /// \brief comparison operator
            //-----------------------------------------------------------------
            virtual bool
            operator==( const Common::FrameSpec::Object& Obj ) const;

        protected:
            //-----------------------------------------------------------------
            /// \brief Copy Constructor
            //-----------------------------------------------------------------
            FrHeader( const FrHeader& Source );

            //-----------------------------------------------------------------
            // \brief Construtor where souce is a C++ stream
            //-----------------------------------------------------------------
            FrHeader( std::istream& Source );

            //-----------------------------------------------------------------
            /// \brief calculate values since the object is now complete
            //-----------------------------------------------------------------
            virtual void complete( );

            //-----------------------------------------------------------------
            /// \brief Down grade an object
            //-----------------------------------------------------------------
            virtual demote_ret_type demote( INT_2U          Target,
                                            demote_arg_type Obj,
                                            istream_type*   Stream ) const;

            //-----------------------------------------------------------------
            /// \brief Upgrade an object
            //-----------------------------------------------------------------
            virtual promote_ret_type promote( INT_2U           Target,
                                              promote_arg_type Obj,
                                              istream_type*    Stream ) const;

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

                    unsigned char frameLibrary;
                    unsigned char frameChecksumScheme;
                } raw; // struct
                unsigned char block[ sizeof( raw_type ) ];
            } m_data; // union - FrHeader_type

            //-----------------------------------------------------------------
            /// \brief State of reordering.
            ///
            /// This variable is true if the stream endianness is not the same
            /// as the host endianness.
            //-----------------------------------------------------------------
            bool m_reorder_bytes;
            //-----------------------------------------------------------------
            /// \todo need to lookup how this variable is used.
            //-----------------------------------------------------------------
            int m_byte_order;

            //-----------------------------------------------------------------
            /// \brief Object checksum
            ///
            /// This is the storage space for the checksum associated with
            /// the FrHeader structure.
            /// It is calculated at the beginning and written at the end
            /// as part of the FrEndOfFile structure.
            //-----------------------------------------------------------------
            mutable FrEndOfFile::chkSumFrHeader_type m_checksum;

            //-----------------------------------------------------------------
            /// The checksum as calculated from reading the object from the
            /// stream.
            //-----------------------------------------------------------------
            INT_4U m_checksum_value;

            //-----------------------------------------------------------------
            /// \brief Constructor
            ///
            /// \param Stream
            ///     Create an instance of the object from an input stream.
            //-----------------------------------------------------------------
            FrHeader( istream_type& Stream );
        }; // class - FrHeader

        //-------------------------------------------------------------------
        /// Retieve the value of the checksum associated with this FrHeader
        /// structure.
        //-------------------------------------------------------------------
        inline FrHeader::checksum_type
        FrHeader::Checksum( ) const
        {
            return m_checksum;
        }

        //-------------------------------------------------------------------
        /// This performs the filtering operation over the raw bytes of
        /// the structure.
        /// A typical use would be to calculate the CRC checksum of
        /// this object.
        //-------------------------------------------------------------------
        inline void
        FrHeader::Filter( Common::StreamFilter& SFilter ) const
        {
            Common::FrHeader::Filter( SFilter );
            SFilter.pubfilter( reinterpret_cast< const char* >( &m_data.block ),
                               sizeof( m_data.block ) );
        }

        //-------------------------------------------------------------------
        //-------------------------------------------------------------------
        inline const unsigned char*
        FrHeader::Get8ByteEndianness( ) const
        {
            return m_data.raw.x123456789abcdef;
        }

        //-------------------------------------------------------------------
        //-------------------------------------------------------------------
        inline int
        FrHeader::GetByteOrder( ) const
        {
            return m_byte_order;
        }

    } // namespace Version_8
} // namespace FrameCPP

#endif /* FrameCPP__VERSION_8__FrHeader_HH */
