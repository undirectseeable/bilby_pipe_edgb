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

#ifndef FRAME_CPP_INTERFACE__VERIFY_HH
#define FRAME_CPP_INTERFACE__VERIFY_HH
#include <memory>
#include <set>
#include <stdexcept>
#include <sstream>
#include <string>

#include "ldastoolsal/reverse.hh"
#include "ldastoolsal/types.hh"
#include "ldastoolsal/unordered_map.hh"
#include "ldastoolsal/util.hh"

#include "framecpp/Common/FrameSpec.hh"
#include "framecpp/Common/FrameFilename.hh"

namespace FrameCPP
{
    namespace Common
    {
        class CheckSum;
        class IFrameStream;
        class Verify;
        class FrHeader;

        class VerifyObject
        {
        public:
            virtual ~VerifyObject( );

            virtual void operator( )( Verify&, IFrameStream& ) const = 0;
        };

        class VerifyException : public std::runtime_error
        {
        public:
            enum error_type
            {
                NO_ERROR = 0,
                CHECKSUM_ERROR,
                FILE_OPEN_ERROR,
                UNSUPPORTED_FRAME_SPEC,
                FRAME_SPEC_CONFORMANCE,
                UNSUPPORTED_CHECKSUM_TYPE,
                NO_CHECKSUM,
                INVALID_FRAME_STRUCTURE,
                FILE_TRUNCATION,
                DATA_INVALID,
                METADATA_INVALID,
                DUPLICATE_CHANNEL_NAME,
                MAX_ERROR = DUPLICATE_CHANNEL_NAME
            };

            VerifyException( error_type         ErrorCode,
                             const std::string& What = "" );

            error_type ErrorCode( ) const;

            virtual VerifyException* Clone( ) const;

            //-----------------------------------------------------------
            /// \brief Return string describing error code
            ///
            /// \param[in] ErrorNum
            ///   Error code
            ///
            /// \return
            ///    String describing error code
            //-----------------------------------------------------------
            static std::string StrError( error_type ErrorNum );

            //-----------------------------------------------------------
            /// \brief Retrieve the string representation of the error_type
            ///
            /// \param[in] ErrorNum
            ///   Error code
            ///
            /// \return
            ///    String describing error code
            //-----------------------------------------------------------
            static std::string StrErrorType( const error_type Error );

        protected:
            VerifyException& operator=( const VerifyException& Error );

            void extendError( const std::string& Message );

        private:
            static const char* m_error_strings[];
            static const char* m_error_type_strings[];

            const error_type m_error_code;

            friend class Verify;

            std::string build_error_string( error_type         ErrorCode,
                                            const std::string& Message );
        };

        inline VerifyException::VerifyException( error_type         ErrorCode,
                                                 const std::string& What )
            : std::runtime_error( build_error_string( ErrorCode, What ) ),
              m_error_code( ErrorCode )
        {
        }

        inline VerifyException::error_type
        VerifyException::ErrorCode( ) const
        {
            return m_error_code;
        }

        inline std::string
        VerifyException::build_error_string( error_type         ErrorCode,
                                             const std::string& What )
        {
            static const char lead[] = "VerifyException: ";
            std::string       retval;

            if ( What.length( ) > 0 )
            {
                if ( What.compare( 0, sizeof( lead ) - 1, lead ) != 0 )
                {
                    //-------------------------------------------------------------
                    // Need to add the leader
                    //-------------------------------------------------------------
                    retval += lead + StrErrorType( ErrorCode ) + ": ";
                }
                retval += What;
            }
            return retval;
        }

        class Verify
        {
        public:
            typedef VerifyException::error_type         error_type;
            typedef std::unique_ptr< FrameFilename >    frame_filename_ptr_type;
            typedef boost::shared_ptr< std::exception > error_info_type;
            typedef std::list< error_info_type > error_info_container_type;

            typedef INT_4U chkType_type;
            typedef INT_4U chkSum_type;

            static frame_filename_ptr_type NULL_FRAME_FILENAME;

            //-----------------------------------------------------------------
            /// \brief Default constructor
            ///
            //-----------------------------------------------------------------
            Verify( );

            //-----------------------------------------------------------------
            /// \brief Query the size of the I/O buffer
            ///
            /// \return
            ///   size of the I/O buffer
            //-----------------------------------------------------------------
            INT_8U BufferSize( ) const;

            //-----------------------------------------------------------------
            /// \brief Change the size of the I/O buffer
            ///
            /// \param[in] Bytes
            ///     establish the size in bytes of the I/O buffer.
            ///     A value of 0 sets the buffer size to the
            ///     system specified default.
            //-----------------------------------------------------------------
            void BufferSize( INT_8U Bytes );

            //-----------------------------------------------------------------
            /// \brief Query if the data valid field of the FrAdcData must be
            /// zero
            ///
            /// \return
            ///   true if the data valid field of the FrAdcData must be zero,
            ///   false otherwise
            //-----------------------------------------------------------------
            bool CheckDataValid( ) const;

            //-----------------------------------------------------------------
            /// \brief Change requirement if the data valid field of the
            /// FrAdcData must be zero
            ///
            /// \param[in] Check
            ///   If true, enable checking of the data valid field of the
            ///   FrAdcData structure to be zero.
            ///   If false, not checking of the data valid field is performed.
            //-----------------------------------------------------------------
            void CheckDataValid( bool Check );

            //-----------------------------------------------------------------
            /// \brief Query if the data valid field of all the FrAdcData must
            /// be zero
            ///
            ///  \return
            ///     state of checking that the data valid field is zero
            //-----------------------------------------------------------------
            bool CheckDataValidAll( ) const;

            //-----------------------------------------------------------------
            /// \brief Change requirement to check all channels for dataValid
            ///
            /// \param[in] Check
            ///   True if the data valid field must be zero,
            ///   false otherwise.
            //-----------------------------------------------------------------
            void CheckDataValidAll( bool Check );

            //-----------------------------------------------------------------
            /// \brief Request fast checking
            ///
            /// \param[in] Check
            ///     If true, then fast checking is enabled;
            ///     If false, then fast checking is disabled.
            //-----------------------------------------------------------------
            void CheckFast( bool Check );

            //-----------------------------------------------------------------
            /// \brief Query if fast checking has been requested.
            ///
            /// \return
            ///     True if fast checking should be attempted.
            //-----------------------------------------------------------------
            bool CheckFast( ) const;

            //-----------------------------------------------------------------
            /// \brief Query if checksums will be calculated for a frame file
            ///
            /// \return
            ///   true if checksums for frame files need to be performed,
            ///	  false otherwise.
            //-----------------------------------------------------------------
            bool CheckFileChecksum( ) const;

            //-----------------------------------------------------------------
            /// \brief Change requirement for calculating the checksum of a
            /// frame file
            ///
            /// \param[in] Check
            ///   true if checksums for frame files need to be performed,
            ///	  false otherwise.
            //-----------------------------------------------------------------
            void CheckFileChecksum( bool Check );

            bool CheckFileChecksumOnly( ) const;

            void CheckFileChecksumOnly( bool Check );

            //-----------------------------------------------------------------
            /// \brief Query if duplicate channel name checking has been
            /// requested.
            ///
            /// \return
            ///     True if fast checking should be attempted.
            //-----------------------------------------------------------------
            bool CheckForDuplicateChannelNames( ) const;

            /// \brief Request checking for duplicate channel names
            ///
            void CheckForDuplicateChannelNames( bool Check );

            //-----------------------------------------------------------------
            /// \brief Query if checksums will be calculated for the frames of a
            /// frame file
            ///
            /// \return
            ///   true if checksums for individual frames need to be performed,
            ///   false otherwise.
            //-----------------------------------------------------------------
            bool CheckFrameChecksum( ) const;

            //-----------------------------------------------------------------
            /// \brief Change requirement for calculating the checksum of frames
            /// of a frame file
            ///
            /// \param[in] Check
            ///   true if checksums for individual frames need to be performed,
            ///   false otherwise.
            //-----------------------------------------------------------------
            void CheckFrameChecksum( bool Check );

            //-----------------------------------------------------------------
            /// \brief Query if md5sum will be calculated for the frame file
            ///
            /// \return
            ///   true if md5sum for the frame file will be	performed,
            ///   false otherwise.
            //-----------------------------------------------------------------
            bool CheckMD5Sum( ) const;

            //-----------------------------------------------------------------
            /// \brief Change requirement for calculating the md5sum value for
            /// the frame file
            ///
            /// \param[in] Check
            ///   true if md5sum for the frame file should be	performed,
            ///   false otherwise.
            //-----------------------------------------------------------------
            void CheckMD5Sum( bool Check );

            //-------------------------------------------------------------------------
            /// \brief Establish the Checksum value for the FrHeader
            //-------------------------------------------------------------------------
            void ChecksumHeader( chkSum_type Checksum );

            //-------------------------------------------------------------------------
            /// \brief Retrieve the value for the checksum scheme
            //-------------------------------------------------------------------------
            INT_4U ChecksumScheme( ) const;

            //-------------------------------------------------------------------------
            /// \brief Set the value for the checksum scheme
            //-------------------------------------------------------------------------
            void ChecksumScheme( INT_4U Value );

            //-------------------------------------------------------------------------
            // \brief Retrieve the value for the collect all errors state.
            //-------------------------------------------------------------------------
            bool CollectAllErrors( ) const;

            //-------------------------------------------------------------------------
            /// \brief Set the value for the collect all errors state.
            ///
            /// \param[in] Value
            ///     True if errors should be buffered till the end.
            ///
            /// \note
            ///     With the buffering of errors, there may be a cascading
            ///     effect.
            //-------------------------------------------------------------------------
            void CollectAllErrors( bool Value );

            //-------------------------------------------------------------------------
            /// \brief Retrieve additional infomation about an error.
            //-------------------------------------------------------------------------
            error_info_container_type ErrorInfoQueue( ) const;

            //-------------------------------------------------------------------------
            /// \brief Retrieve the value governing checking of compressed data
            ///
            /// \return
            ///      A value of true if compressed data should be expanded as
            ///      part of data validation. A value of false is returned if
            ///      this data check should not be performed.
            //-------------------------------------------------------------------------
            bool Expandability( ) const;

            //-------------------------------------------------------------------------
            /// \brief Set the value governing validation of compressed data
            ///
            /// \param[in] Value
            ///     If Value is true, then compressed data should be expanded as
            ///     part of data validation. If Value is false, then compressed
            ///     data should not be expanded as part of data validation.
            //-------------------------------------------------------------------------
            void Expandability( bool Value );

            //-------------------------------------------------------------------------
            /// \brief Query if the frame file must have the EOF checksum
            /// structure.
            ///
            /// \return
            ///   true if the frame file must have the EOF checksum structure,
            ///   false otherwise
            //-------------------------------------------------------------------------
            bool MustHaveEOFChecksum( ) const;

            //-------------------------------------------------------------------------
            /// \brief Change requirement of the frame file having the EOF
            /// checksum structure
            ///
            /// \param[in] Conformance
            ///     true if the frame file must have the EOF
            ///     checksum structure, false otherwise
            //-------------------------------------------------------------------------
            void MustHaveEOFChecksum( bool Conformance );

            /// \brief Change status of having seen FrEndOfFile structure
            ///
            void SeenFrEndOfFile( bool Value );

            //-------------------------------------------------------------------------
            /// \brief Query strict conformance requirement
            ///
            /// \return
            ///   State of strictness.
            ///   True for strict conformance to the frame spec; false
            ///   otherwise.
            //-------------------------------------------------------------------------
            bool Strict( ) const;

            //-------------------------------------------------------------------------
            /// \brief Change strict conformance requirement
            ///
            /// \param[in] Strictness
            ///   true if the frame file must conform to all details of the
            ///   frame spec;
            /// false otherwise.
            //-------------------------------------------------------------------------
            void Strict( bool Strictness );

            //-------------------------------------------------------------------------
            /// \brief Query if memory mapped I/O will be used
            ///
            /// \return
            ///   true if memory mapped I/O will be used
            //-------------------------------------------------------------------------
            bool UseMemoryMappedIO( ) const;

            //-------------------------------------------------------------------------
            /// \brief Specify if to use memory mapped I/O.
            ///
            /// \param[in] UseMemoryMappedIO
            ///   true if memory mapped I/O should be used; false otherwise.
            //-------------------------------------------------------------------------
            void UseMemoryMappedIO( bool UseMemoryMappedIO );

            //-------------------------------------------------------------------------
            /// \brief Query if metadata should be validated
            ///
            /// \return
            ///   true if metadata should be validated
            //-------------------------------------------------------------------------
            bool ValidateMetadata( ) const;

            //-------------------------------------------------------------------------
            /// \brief Specify if to validate metadata
            ///
            /// \param[in] ValidateMetadata
            ///   true if frame metadata to be verified against the filename
            //-------------------------------------------------------------------------
            void ValidateMetadata( bool ValidateMetadata );

            //-------------------------------------------------------------------------
            /// \brief Verify a frame file
            ///
            //-------------------------------------------------------------------------
            void operator( )( const std::string& Filename );

            //-------------------------------------------------------------------------
            /// \brief Verify a frame stream
            ///
            //-------------------------------------------------------------------------
            void operator( )(
                IFrameStream&            Stream,
                frame_filename_ptr_type& Filename = NULL_FRAME_FILENAME );

            void ExamineFrEndOfFileChecksum( IFrameStream& Stream,
                                             chkType_type  Type,
                                             chkSum_type   Sum );

            //-----------------------------------------------------------------
            /// \brief Verify the checksum for the FrHeader structure
            ///
            /// \param[in] Checksum
            ///     The value of the expected checksum.
            //-----------------------------------------------------------------
            void ExamineFrHeaderChecksum( chkSum_type Checksum ) const;

            template < int >
            void ExamineMagicNumber( const unsigned char* Source );

        private:
#if 0
      template< typename T > friend
      void VerifyObject( const T&, Verify&, IFrameStream& );
#endif /* 0 */
            typedef boost::shared_ptr< FrHeader > fr_header_type;
            typedef LDASTools::AL::unordered_map< char, int >
                detector_validation_type;
            typedef LDASTools::AL::unordered_map< std::string, std::set< int > >
                name_cache_type;

            friend void FrameSpec::ObjectInterface::VerifyObject(
                Verify& Verifier, IFrameStream& Stream ) const;

            //-----------------------------------------------------------------
            /// \brief Cache of channel names and object class ids
            //-----------------------------------------------------------------
            name_cache_type name_cache;

            detector_validation_type m_detector_validation;
            detector_validation_type m_detector_validation_excess;

            detector_validation_type m_channel_validation;
            detector_validation_type m_channel_validation_excess;

            INT_8U m_buffer_size;
            INT_4U frame_offset;

            //-----------------------------------------------------------------
            /// \brief State of checking for duplicate channel names
            //-----------------------------------------------------------------
            bool check_for_duplicate_channel_names;
            bool m_check_data_valid;
            bool m_check_data_valid_all;
            //-----------------------------------------------------------------
            /// \brief Expandability checking
            ///
            /// When enabled (set to true), data that has been compressed
            /// will be expanded as part of validation.
            ///
            /// This check is enabled by default.
            //-----------------------------------------------------------------
            bool m_check_expandability;
            //-----------------------------------------------------------------
            /// \brief Enable fast checking
            ///
            /// Fast checking is only available for version 8 frames
            /// and beyond since with version 8 frames each structure
            /// contains its own checksum.
            ///
            /// When this option is set, file and frame checksums are not
            /// calculated.
            /// Validation of the other information makes use of the table
            /// of contents.
            //-----------------------------------------------------------------
            bool m_check_fast;
            bool m_check_file_checksum;
            bool m_check_frame_checksum;
            bool m_check_md5sum;
            bool m_checksum_file_only;
            bool collect_all_errors;
            bool m_must_have_eof_checksum;
            bool m_strict;
            bool m_use_memory_mapped_io;
            bool m_validate_metadata;
            bool m_state_has_seen_fr_end_of_file;

            //-------------------------------------------------------------------------
            /// Beginning with version eight frame specification, the
            /// checksum_scheme needs to be recorded from the FrHeader
            /// structure to be used by the FrEndOfFile structure.
            //-------------------------------------------------------------------------
            INT_4U m_checksum_scheme;

            //-------------------------------------------------------------------------
            /// The checksum of the FrHeader structure upon reading the object.
            //-------------------------------------------------------------------------
            chkSum_type m_checksum_frheader;

            error_info_container_type error_info_container;

            //-------------------------------------------------------------------------
            //-------------------------------------------------------------------------
            void crc_file_checksum_only( IStream&       Stream,
                                         fr_header_type Header );

            //-------------------------------------------------------------------------
            /// \brief Verify that an object is uniquely named
            ///
            /// \param[in] ClassId
            ///     The class id that uniquely identifies the class type.
            /// \param[in] Name
            ///     The name of the object.
            //-------------------------------------------------------------------------
            void is_unique( int ClassId, const std::string& Name );

            //-------------------------------------------------------------------------
            /// \brief Handle throwing of exception
            //-------------------------------------------------------------------------
            void thrower( const VerifyException& Except );

            //-------------------------------------------------------------------------
            /// @brief Verify Checksum values
            ///
            /// @param[in] ExpectedCRC
            ///     The checksum that was written to the stream origionally and
            ///     used for comparison to detect changes.
            /// @param[in] CalculatedCRC
            ///     The checksum that was calculated while reading the current
            ///     stream and used for comparison to detect changes.
            /// @param[in] FrStructure
            ///     The name of the structure being verified.
            ///     This allows for better error handling code as this detail
            ///     becomes part of any diagnostic message.
            /// @param[in] MustBeNonZero
            ///     If true, then checksum values of zero are considered to be
            ///     an error. This condition commonly comes into play when no
            ///     checksum information is recorded in the output stream
            ///     usually to provide a minimal performance boost.
            /// @param[in] InFrame
            ///     True if checksum is in frame, false otherwise (checksums
            ///     in FrEndOfFile structure )
            ///
            //-------------------------------------------------------------------------
            void verify_checksum( CheckSum*          ExpectedCRC,
                                  CheckSum*          CalculatedCRC,
                                  const std::string& FrStructure,
                                  bool               MustBeNonZero,
                                  bool               InFrame = true ) const;

            //-------------------------------------------------------------------------
            //-------------------------------------------------------------------------
            void set_channel_site( char Site );

            //-------------------------------------------------------------------------
            //-------------------------------------------------------------------------
            template < class T >
            void check_magic_number( const unsigned char* const Source,
                                     const T                    Ref );
        };

        inline INT_8U
        Verify::BufferSize( ) const
        {
            return m_buffer_size;
        }

        inline void
        Verify::BufferSize( INT_8U Bytes )
        {
            m_buffer_size = Bytes;
        }

        inline bool
        Verify::CheckDataValid( ) const
        {
            return m_check_data_valid;
        }

        inline void
        Verify::CheckDataValid( bool Check )
        {
            m_check_data_valid = Check;
        }

        inline bool
        Verify::CheckDataValidAll( ) const
        {
            return m_check_data_valid_all;
        }

        inline void
        Verify::CheckDataValidAll( bool Check )
        {
            m_check_data_valid_all = Check;
        }

        inline bool
        Verify::CheckFast( ) const
        {
            return m_check_fast;
        }

        inline void
        Verify::CheckFast( bool Value )
        {
            m_check_fast = Value;
        }

        inline bool
        Verify::CheckFileChecksum( ) const
        {
            return m_check_file_checksum;
        }

        inline void
        Verify::CheckFileChecksum( bool Check )
        {
            m_check_file_checksum = Check;
        }

        inline bool
        Verify::CheckFileChecksumOnly( ) const
        {
            return m_checksum_file_only;
        }

        inline void
        Verify::CheckFileChecksumOnly( bool Check )
        {
            m_checksum_file_only = Check;
        }

        inline bool
        Verify::CheckForDuplicateChannelNames( ) const
        {
            return check_for_duplicate_channel_names;
        }

        inline void
        Verify::CheckForDuplicateChannelNames( bool Check )
        {
            check_for_duplicate_channel_names = Check;
        }

        inline bool
        Verify::CheckFrameChecksum( ) const
        {
            return m_check_frame_checksum;
        }

        inline void
        Verify::CheckFrameChecksum( bool Check )
        {
            m_check_frame_checksum = Check;
        }

        inline bool
        Verify::CheckMD5Sum( ) const
        {
            return m_check_md5sum;
        }

        inline void
        Verify::CheckMD5Sum( bool Check )
        {
            m_check_md5sum = Check;
        }

        //---------------------------------------------------------------------------
        /// This estalishes the checksum calculated from the reading of the
        /// FrHeader structure.
        //---------------------------------------------------------------------------
        inline void
        Verify::ChecksumHeader( chkSum_type Checksum )
        {
            m_checksum_frheader = Checksum;
        }

        //---------------------------------------------------------------------------
        /// Retrieve the value for the checksum scheme
        //---------------------------------------------------------------------------
        inline INT_4U
        Verify::ChecksumScheme( ) const
        {
            return m_checksum_scheme;
        }

        //---------------------------------------------------------------------------
        /// Establish the value for the checksum scheme
        //---------------------------------------------------------------------------
        inline void
        Verify::ChecksumScheme( INT_4U Value )
        {
            m_checksum_scheme = Value;
        }

        //---------------------------------------------------------------------------
        /// Retrieve the value for the checksum scheme
        //---------------------------------------------------------------------------
        inline bool
        Verify::CollectAllErrors( ) const
        {
            return collect_all_errors;
        }

        //---------------------------------------------------------------------------
        /// Establish the value for the checksum scheme
        //---------------------------------------------------------------------------
        inline void
        Verify::CollectAllErrors( bool Value )
        {
            collect_all_errors = Value;
        }

        inline Verify::error_info_container_type
        Verify::ErrorInfoQueue( ) const
        {
            return error_info_container;
        }

        template <>
        inline void
        Verify::ExamineMagicNumber< 2 >( const unsigned char* Source )
        {
            if ( m_strict )
            {
                try
                {
                    check_magic_number( Source, INT_2U( 0x1234 ) );
                }
                catch ( ... )
                {
                    throw VerifyException(
                        VerifyException::FRAME_SPEC_CONFORMANCE,
                        "2 bytes container 0x1234" );
                }
            }
        }

        template <>
        inline void
        Verify::ExamineMagicNumber< 4 >( const unsigned char* Source )
        {
            if ( m_strict )
            {
                try
                {
                    check_magic_number( Source, INT_4U( 0x12345678 ) );
                }
                catch ( ... )
                {
                    throw VerifyException(
                        VerifyException::FRAME_SPEC_CONFORMANCE,
                        "4 bytes container 0x12345678" );
                }
            }
        }

        template <>
        inline void
        Verify::ExamineMagicNumber< 8 >( const unsigned char* Source )
        {
            if ( m_strict )
            {
                try
                {
                    check_magic_number( Source,
                                        INT_8U( 0x123456789abcdefULL ) );
                }
                catch ( ... )
                {
                    throw VerifyException(
                        VerifyException::FRAME_SPEC_CONFORMANCE,
                        "8 bytes container 0x123456789abcdef" );
                }
            }
        }

        inline void
        Verify::Expandability( bool Value )
        {
            m_check_expandability = Value;
        }

        inline bool
        Verify::Expandability( ) const
        {
            return m_check_expandability;
        }

        inline bool
        Verify::MustHaveEOFChecksum( ) const
        {
            return m_must_have_eof_checksum;
        }

        inline void
        Verify::MustHaveEOFChecksum( bool Confomance )
        {
            m_must_have_eof_checksum = Confomance;
        }

        inline void
        Verify::SeenFrEndOfFile( bool Value )
        {
            m_state_has_seen_fr_end_of_file = Value;
        }

        inline bool
        Verify::Strict( ) const
        {
            return m_strict;
        }

        inline void
        Verify::Strict( bool Strictness )
        {
            m_strict = Strictness;
        }

        inline void
        Verify::thrower( const VerifyException& Except )
        {
            if ( !collect_all_errors )
            {
                throw( Except );
            }
            error_info_container.push_back(
                error_info_type( Except.Clone( ) ) );
        }

        inline bool
        Verify::UseMemoryMappedIO( ) const
        {
            return m_use_memory_mapped_io;
        }

        inline void
        Verify::UseMemoryMappedIO( bool UseMemoryMappedIO )
        {
            m_use_memory_mapped_io = UseMemoryMappedIO;
        }

        inline bool
        Verify::ValidateMetadata( ) const
        {
            return m_validate_metadata;
        }

        inline void
        Verify::ValidateMetadata( bool ValidateMetadata )
        {
            m_validate_metadata = ValidateMetadata;
        }

        inline void
        Verify::set_channel_site( char Site )
        {
            detector_validation_type::iterator pos =
                m_channel_validation.find( Site );
            if ( pos == m_channel_validation.end( ) )
            {
                m_channel_validation_excess[ Site ]++;
            }
            else
            {
                ( *pos ).second++;
            }
        }

        template < class T >
        inline void
        Verify::check_magic_number( const unsigned char* const Source,
                                    const T                    Ref )
        {
            T buf;

            //-----------------------------------------------------------------
            // Load the buffer
            //-----------------------------------------------------------------
            memcpy( &buf, Source, sizeof( buf ) );
            //-----------------------------------------------------------------
            // Check the bytes
            //-----------------------------------------------------------------
            if ( Ref != buf )
            {
                //---------------------------------------------------------------
                // Reverse the bytes and check again
                //---------------------------------------------------------------
                reverse< sizeof( buf ) >( &buf, 1 );
                if ( Ref != buf )
                {
                    //-------------------------------------------------------------
                    // Pattern does not match either BIGENDIAN or LITTLEENDIAN
                    // so
                    //   it must not be a frame file.
                    //-------------------------------------------------------------
                    throw std::runtime_error( "non-frame frame file" );
                }
            }
        }

    } // namespace Common
} // namespace FrameCPP

#endif /* FRAME_CPP_INTERFACE__VERIFY_HH */
