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

#ifndef FrameCPP_VERSION_8_FrEndOfFile_HH
#define FrameCPP_VERSION_8_FrEndOfFile_HH

#include "framecpp/Version8/impl/FrEndOfFileClassicIO.hh"
#include "framecpp/Version8/impl/FrEndOfFileSerialIO.hh"

namespace FrameCPP
{
    namespace Version_8
    {
        //-------------------------------------------------------------------
        /// \brief End of File data structure
        //-------------------------------------------------------------------
        class FrEndOfFile : public FrEndOfFileImpl::ClassicIO< FrEndOfFile >,
                            public FrEndOfFileImpl::SerialIO< FrEndOfFile >
        {
        public:
            //-----------------------------------------------------------------
            /// \brief Default constructor
            ///
            /// \return
            ///     A new instance of this object.
            //-----------------------------------------------------------------
            FrEndOfFile( );

            //-----------------------------------------------------------------
            /// \brief Destructor.
            //-----------------------------------------------------------------
            virtual ~FrEndOfFile( );

            //-----------------------------------------------------------------
            /// \brief The name structure name of this object.
            ///
            /// \return
            ///     The name of the structure as specified by the frame
            ///     specification.
            //-----------------------------------------------------------------
            static const char* StructName( );

            //-----------------------------------------------------------------
            /// \brief Number of bytes needed to write this structure
            ///
            /// \param[in] Stream
            ///     The stream from which to the object is being read or
            ///     written.
            ///
            /// \return
            ///     The number of bytes need to read or write this object.
            //-----------------------------------------------------------------
            virtual Common::FrameSpec::size_type
            Bytes( const Common::StreamBase& Stream ) const;

            //-----------------------------------------------------------------
            /// \brief Virtual copy constructor
            //-----------------------------------------------------------------
            virtual FrEndOfFile* Clone( ) const;

            //-----------------------------------------------------------------
            /// \brief Virtual constructor
            ///
            /// \param[in] Stream
            ///     The input stream from where the object is being read.
            //-----------------------------------------------------------------
            virtual FrEndOfFile* Create( istream_type& Stream ) const;

            //-----------------------------------------------------------------
            /// \brief Retrieve the expected size of the stream
            //-----------------------------------------------------------------
            virtual nBytes_cmn_type NBytes( ) const;

            //-----------------------------------------------------------------
            /// \brief Retrieve the number of frames in the stream
            //-----------------------------------------------------------------
            virtual nFrames_cmn_type NFrames( ) const;

            //-----------------------------------------------------------------
            /// \brief The name structure name of this object.
            ///
            /// \return
            ///     The name of the structure as specified by the frame
            ///     specification.
            //-----------------------------------------------------------------
            virtual const char* ObjectStructName( ) const;

            //-----------------------------------------------------------------
            /// \brief Write the structure to the stream
            ///
            /// \param[in] Stream
            ///     The output stream where the object is to be written.
            //-----------------------------------------------------------------
            virtual void Write( ostream_type& Stream ) const;

            //-----------------------------------------------------------------
            /// \brief equality operator
            ///
            /// \param[in] RHS
            ///     The FrAdcData object to be compared.
            ///
            /// \return
            ///     The value true is returned if this object is equivelent
            ///     to the RHS instance; false otherwise.
            //-----------------------------------------------------------------
            bool operator==( const FrEndOfFile& RHS ) const;

            //-----------------------------------------------------------------
            /// \brief equality operator for abstract data type
            ///
            /// \param[in] RHS
            ///     The object to be compared.
            ///
            /// \return
            ///     The value true is returned if this object is equivelent
            ///     to the RHS instance; false otherwise.
            //-----------------------------------------------------------------
            virtual bool
            operator==( const Common::FrameSpec::Object& RHS ) const;

            static const Common::FrameSpec::Info::frame_object_types
                s_object_id = Common::FrameSpec::Info::FSI_FR_END_OF_FILE;

            //-----------------------------------------------------------------
            /// \brief Retrieve the location of the table of contents.
            ///
            /// \return
            ///     The location of the table of contents.
            ///
            /// \todo
            ///     This may be better placed in the protected section.
            //-----------------------------------------------------------------
            virtual FrEndOfFile::seekTOC_cmn_type SeekTOC( ) const;

            //-----------------------------------------------------------------
            /// \brief Verify the object.
            //-----------------------------------------------------------------
            virtual void VerifyObject( Common::Verify&       Verifier,
                                       Common::IFrameStream& Stream ) const;

        protected:
            //-----------------------------------------------------------------
            /// \brief Assign the contents of the instance
            ///
            /// \param[in] Stream
            ///     An input stream from which to read information for
            ///     the instance.
            ///
            //-----------------------------------------------------------------
            virtual void assign( assign_stream_type& Stream );

            //-----------------------------------------------------------------
            /// \brief Demotes object to previous version of the frame spec
            ///
            /// \param[in] Target
            ///     The version of the frame specification to demote too.
            /// \param[in] Obj
            ///     The version of the object to demote.
            /// \param[in] Stream
            ///     The input stream from which the original object was read.
            ///
            /// \return
            ///     An object of the previous generation.
            //-----------------------------------------------------------------
            virtual demote_ret_type demote( INT_2U          Target,
                                            demote_arg_type Obj,
                                            istream_type*   Stream ) const;

            //-----------------------------------------------------------------
            /// \brief Promotes object to another version of the frame spec
            ///
            /// \param[in] Target
            ///     The version of the promoted frame specification.
            /// \param[in] Obj
            ///     The object to be promoted.
            /// \param[in] Stream
            ///     The input stream from which the original object was read.
            ///
            /// \return
            ///     An object promoted to the next generation.
            //-----------------------------------------------------------------
            virtual promote_ret_type promote( INT_2U           Target,
                                              promote_arg_type Obj,
                                              istream_type*    Stream ) const;

        private:
            using Common::FrameSpec::Object::Create;

            FrEndOfFile( istream_type& Source );

            chkSum_cmn_type Filter( const istream_type& Stream,
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

        inline Common::FrEndOfFile::seekTOC_cmn_type
        FrEndOfFile::SeekTOC( ) const
        {
            return GetSeekTOC( );
        }
    } // namespace Version_8
} // namespace FrameCPP

#endif /* FrameCPP_VERSION_8_FrEndOfFile_HH */
