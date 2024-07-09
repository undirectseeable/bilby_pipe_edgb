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

#ifndef FrameCPP_VERSION_4_FrEndOfFile_HH
#define FrameCPP_VERSION_4_FrEndOfFile_HH

#include "ldastoolsal/types.hh"

#include "framecpp/Version4/FrameSpec.hh"

#include "framecpp/Common/FrEndOfFile.hh"

namespace FrameCPP
{
    namespace Version_4
    {
        class FrEndOfFile : public Common::FrEndOfFile
        {
        public:
            typedef INT_4U nFrames_type;
            typedef INT_4U nBytes_type;
            typedef INT_4U chkFlag_type;
            typedef INT_4U chkSum_type;
            typedef INT_4U seekTOC_type;

            FrEndOfFile( );
            virtual ~FrEndOfFile( );

            static const char* StructName( );

            static const Common::Description* StructDescription( );

            virtual Common::FrameSpec::size_type
            Bytes( const Common::StreamBase& Stream ) const;

            virtual FrEndOfFile* Clone( ) const;

            virtual FrEndOfFile* Create( istream_type& Stream ) const;

            virtual const char* ObjectStructName( ) const;

            virtual void Write( ostream_type& Stream ) const;

            /// \brief comparison operator
            bool operator==( const FrEndOfFile& RHS ) const;

            /// \brief comparison operator
            virtual bool
            operator==( const Common::FrameSpec::Object& Obj ) const;

            static const Common::FrameSpec::Info::frame_object_types
                s_object_id = Common::FrameSpec::Info::FSI_FR_END_OF_FILE;

            virtual nBytes_cmn_type NBytes( ) const;

            virtual nFrames_cmn_type NFrames( ) const;

            FrEndOfFile::seekTOC_type GetSeekTOC( ) const;

            virtual FrEndOfFile::seekTOC_cmn_type SeekTOC( ) const;

            virtual void VerifyObject( Common::Verify&       Verifier,
                                       Common::IFrameStream& Stream ) const;

        protected:
            nFrames_type m_nFrames;
            nBytes_type  m_nBytes;
            chkFlag_type m_chkFlag;
            chkSum_type  m_chkSum;
            seekTOC_type m_seekTOC;

            //-----------------------------------------------------------------
            /// \brief Assign the contents of the instance
            ///
            /// \param[in] Stream
            ///     An input stream from which to read information for
            ///     the instance.
            ///
            //-----------------------------------------------------------------
            virtual void assign( assign_stream_type& Stream );

            /// \brief Down grade an object
            virtual demote_ret_type demote( INT_2U          Target,
                                            demote_arg_type Obj,
                                            istream_type*   Stream ) const;

            /// \brief Upgrade an object
            virtual promote_ret_type promote( INT_2U           Target,
                                              promote_arg_type Obj,
                                              istream_type*    Stream ) const;

        private:
            using Common::FrameSpec::Object::Create;

            FrEndOfFile( istream_type& Source );

            virtual chkSum_cmn_type Filter( const istream_type& Stream,
                                            Common::CheckSum&   Filt,
                                            chkType_cmn_type&   Type,
                                            void*               Buffer,
                                            INT_8U              Size ) const;

        }; // class - FrEndOfFile

        inline const char*
        FrEndOfFile::StructName( )
        {
            static const CHAR* class_name( "FrEndOfFile" );
            return class_name;
        }

        inline FrEndOfFile::seekTOC_type
        FrEndOfFile::GetSeekTOC( ) const
        {
            return m_seekTOC;
        }

        inline Common::FrEndOfFile::seekTOC_cmn_type
        FrEndOfFile::SeekTOC( ) const
        {
            return GetSeekTOC( );
        }
    } // namespace Version_4
} // namespace FrameCPP

#endif /* FrameCPP_VERSION_4_FrEndOfFile_HH */
