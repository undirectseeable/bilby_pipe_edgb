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

#ifndef FrameCPP__Common__FrHeader_HH
#define FrameCPP__Common__FrHeader_HH

#if !defined( SWIGIMPORTED )
#include <algorithm>
#include <string>

#include "ldastoolsal/types.hh"

#include "framecpp/Common/FrameSpec.hh"

#include "framecpp/Common/IOStream.hh"
#endif /* ! defined(SWIGIMPORTED) */

#define FR_HEADER__FRAME_LIBRARY_TYPE INT_2U
#define FR_HEADER__VERSION_TYPE INT_2U
#define FR_HEADER__LIBRARY_REVISION_TYPE INT_2U

#if !defined( SWIGIMPORTED )
namespace FrameCPP
{
    namespace Common
    {
        class FrHeader
        {
        public:
            enum frame_library_type
            {
                FRAME_LIBRARY_UNKNOWN = 0,
                FRAME_LIBRARY_FRAMEL = 1,
                FRAME_LIBRARY_FRAMECPP = 2
            };

            typedef FR_HEADER__VERSION_TYPE          version_type;
            typedef FR_HEADER__LIBRARY_REVISION_TYPE library_revision_type;
            typedef CHAR*                            originator_type;

            FrHeader( IStream& Stream );
            FrHeader( std::istringstream& Source );

            virtual ~FrHeader( );
            virtual cmn_streamsize_type Bytes( ) const;

            static cmn_streamsize_type SizeOf( );

            virtual bool ByteSwapping( ) const;

            virtual void Filter( StreamFilter& SFilter ) const;

            /// \brief Retrieve the library used to generate the frame stream
            frame_library_type GetFrameLibrary( ) const;

            /// \brief Retrieve the library used to generate the frame stream
            std::string GetFrameLibraryName( ) const;

            /// \brief Retrieve the library used to generate the frame stream
            static std::string
            GetFrameLibraryName( frame_library_type LibraryId );

            library_revision_type GetLibraryRevision( ) const;

            version_type GetVersion( ) const;

            originator_type GetOriginator( ) const;

            virtual bool IsValid( ) const;

            /// \brief Establish the version of the Library used
            void SetLibraryVersion( INT_2U Version );

            /// \brief Establish the originator of the frame.
            void SetOriginator( const std::string& Originator );

            /// \brief Establish the version of the frame specification.
            void SetVersion( INT_2U Version );

            void Write( OStream& Stream ) const;

            const FrHeader& operator=( const FrHeader& Source );

        protected:
            FrHeader( );
            FrHeader( const FrHeader& Source );

            //-----------------------------------------------------------------
            /// \brief Entry point to do extra processing
            //-----------------------------------------------------------------
            virtual void complete( );

            frame_library_type m_frame_library;

        private:
            union data_type
            {
                struct raw_type
                {
                    CHAR   originator[ 5 ];
                    CHAR_U version;
                    CHAR_U version_minor;
                } raw;
            };

            data_type m_data;

            //-----------------------------------------------------------------
            /// \brief Initialize the class
            ///
            /// \param[in,out] Source
            ///     The source stream from which to initialize the instance.
            //-----------------------------------------------------------------
            void initialize( std::istream& Source );
        }; // class - FrHeader

        inline FrHeader::FrHeader( const FrHeader& Source )
            : m_frame_library( Source.m_frame_library )
        {
            const char* s =
                reinterpret_cast< const char* >( &( Source.m_data.raw ) );
            char* d = reinterpret_cast< char* >( &( m_data.raw ) );

            std::copy( s, s + sizeof( m_data.raw ), d );
        }

        inline FrHeader::FrHeader( ) : m_frame_library( FRAME_LIBRARY_UNKNOWN )
        {
        }

        inline FrHeader::~FrHeader( )
        {
        }

        inline cmn_streamsize_type
        FrHeader::Bytes( ) const
        {
            return SizeOf( );
        }

        inline cmn_streamsize_type
        FrHeader::SizeOf( )
        {
#if ( ( __GNUC__ == 4 ) &&                                                     \
      ( ( __GNUC_MINOR__ < 2 ) ||                                              \
        ( ( __GNUC_MINOR__ == 2 ) && ( __GNUC_PATCHLEVEL__ == 1 ) ) ) )
            //----------------------------------
            // This ugly hack is needed for GCC
            //  4.2.1 as used by OSX
            //----------------------------------

            data_type d;

            return sizeof( d.raw.originator ) + sizeof( d.raw.version ) +
                sizeof( d.raw.version_minor );
#else
            return sizeof( m_data.raw.originator ) +
                sizeof( m_data.raw.version ) +
                sizeof( m_data.raw.version_minor );
#endif
        }

        inline void
        FrHeader::Filter( StreamFilter& SFilter ) const
        {
            SFilter.pubfilter( reinterpret_cast< const char* >( &m_data.raw ),
                               sizeof( m_data.raw ) );
        }

        inline FrHeader::frame_library_type
        FrHeader::GetFrameLibrary( ) const
        {
            return m_frame_library;
        }

        inline std::string
        FrHeader::GetFrameLibraryName( ) const
        {
            return GetFrameLibraryName( GetFrameLibrary( ) );
        }

        inline std::string
        FrHeader::GetFrameLibraryName( frame_library_type LibraryId )
        {
            switch ( LibraryId )
            {
            case FRAME_LIBRARY_FRAMEL:
                return "frameL";
            case FRAME_LIBRARY_FRAMECPP:
                return "frameCPP";
            default:
                return "UNKNOWN";
            }
        }

        inline FrHeader::originator_type
        FrHeader::GetOriginator( ) const
        {
            return ( FrHeader::originator_type )(
                &( m_data.raw.originator[ 0 ] ) );
        }
        inline FrHeader::library_revision_type
        FrHeader::GetLibraryRevision( ) const
        {
            return m_data.raw.version_minor;
        }

        inline FrHeader::version_type
        FrHeader::GetVersion( ) const
        {
            return m_data.raw.version;
        }

        inline void
        FrHeader::SetLibraryVersion( INT_2U Version )
        {
            m_data.raw.version_minor = Version;
        }

        inline void
        FrHeader::SetVersion( INT_2U Version )
        {
            m_data.raw.version = Version;
        }

        inline const FrHeader&
        FrHeader::operator=( const FrHeader& Source )
        {
            const char* sptr =
                reinterpret_cast< const char* >( &Source.m_data.raw );
            std::copy( sptr,
                       sptr + sizeof( m_data.raw ),
                       reinterpret_cast< char* >( &m_data.raw ) );
            complete( );
            return *this;
        }

    } // namespace Common
} // namespace FrameCPP

#endif /* ! defined(SWIGIMPORTED) */

#endif /* FrameCPP__Common__FrHeader_HH */
