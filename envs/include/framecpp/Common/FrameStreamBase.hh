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

#ifndef FrameCPP__COMMON__FrameStreamBase_HH
#define FrameCPP__COMMON__FrameStreamBase_HH

#include <iostream>

#include "framecpp/Common/CheckSum.hh"
#include "framecpp/Common/MD5Sum.hh"

namespace FrameCPP
{
    namespace Common
    {
        class FrameStreamBase
        {
        public:
            FrameStreamBase( );

            virtual ~FrameStreamBase( );

            CheckSum& GetCheckSumFile( );

            CheckSum& GetCheckSumFrame( );

            const std::string& GetLastError( ) const;

            MD5Sum& GetMD5Sum( );

            bool IsCalculatingChecksumFile( ) const;

            bool IsCalculatingChecksumFrame( ) const;

            bool IsCalculatingMD5Sum( ) const;

            virtual void
            SetChecksumMethodFile( const CheckSum::kind_type Method );

            virtual void SetChecksumMethodFrame( );

            virtual void
            SetChecksumMethodFrame( const CheckSum::kind_type Method );

            virtual void SetMD5Sum( );
            virtual void SetMD5Sum( MD5Sum& MD5 );

        protected:
            void calcChecksumFile( const void* Buffer, INT_4U NBytes );
            void calcChecksumFrame( const void* Buffer, INT_4U NBytes );
            void calcMD5Sum( const void* Buffer, INT_4U NBytes );
            void calcChecksums( const void* Buffer, INT_4U NBytes );
            void setLastError( const std::string& Message );

        private:
            typedef std::unique_ptr< CheckSum > checksum_type;

            CheckSum::kind_type m_type_of_frame_checksum;
            checksum_type       m_file_checksum;
            checksum_type       m_frame_checksum;
            MD5Sum*             m_md5;
            std::string         m_last_error_message;
        };

        inline CheckSum&
        FrameStreamBase::GetCheckSumFile( )
        {
            if ( m_file_checksum.get( ) )
            {
                return *( m_file_checksum.get( ) );
            }
            throw std::runtime_error( "No checksum being calculated for file" );
        }

        inline CheckSum&
        FrameStreamBase::GetCheckSumFrame( )
        {
            if ( m_frame_checksum.get( ) )
            {
                return *( m_frame_checksum.get( ) );
            }
            throw std::runtime_error(
                "No checksum being calculated for frame" );
        }

        inline const std::string&
        FrameStreamBase::GetLastError( ) const
        {
            return m_last_error_message;
        }

        inline MD5Sum&
        FrameStreamBase::GetMD5Sum( )
        {
            if ( m_md5 != (MD5Sum*)NULL )
            {
                return *( m_md5 );
            }
            throw std::runtime_error( "No md5sum being calculated for frame" );
        }

        inline bool
        FrameStreamBase::IsCalculatingChecksumFrame( ) const
        {
            return m_frame_checksum.get( );
        }

        inline bool
        FrameStreamBase::IsCalculatingChecksumFile( ) const
        {
            return m_file_checksum.get( );
        }

        inline bool
        FrameStreamBase::IsCalculatingMD5Sum( ) const
        {
            return ( m_md5 != (MD5Sum*)NULL );
        }

        inline void
        FrameStreamBase::SetChecksumMethodFrame( )
        {
            SetChecksumMethodFrame( m_type_of_frame_checksum );
        }

        inline void
        FrameStreamBase::SetChecksumMethodFrame(
            const CheckSum::kind_type Method )
        {
            m_type_of_frame_checksum = Method;
            switch ( Method )
            {
            case CheckSum::CRC:
                m_frame_checksum.reset( new CheckSumCRC );
                break;
            default:
                m_frame_checksum.reset( (CheckSum*)NULL );
                break;
            }
        }

        inline void
        FrameStreamBase::SetChecksumMethodFile(
            const CheckSum::kind_type Method )
        {
            switch ( Method )
            {
            case CheckSum::CRC:
                m_file_checksum.reset( new CheckSumCRC );
                break;
            default:
                m_file_checksum.reset( (CheckSum*)NULL );
                break;
            }
        }

        inline void
        FrameStreamBase::SetMD5Sum( )
        {
            m_md5 = (MD5Sum*)NULL;
        }

        inline void
        FrameStreamBase::SetMD5Sum( MD5Sum& MD5 )
        {
            m_md5 = &MD5;
        }

        inline void
        FrameStreamBase::calcChecksumFile( const void* Buffer, INT_4U NBytes )
        {
            m_file_checksum->calc( Buffer, NBytes );
        }

        inline void
        FrameStreamBase::calcChecksumFrame( const void* Buffer, INT_4U NBytes )
        {
            m_frame_checksum->calc( Buffer, NBytes );
        }

        inline void
        FrameStreamBase::calcMD5Sum( const void* Buffer, INT_4U NBytes )
        {
            m_md5->Update( ( MD5Sum::md_type )( Buffer ), NBytes );
        }

        inline void
        FrameStreamBase::calcChecksums( const void* Buffer, INT_4U NBytes )
        {
            if ( m_file_checksum.get( ) )
            {
                calcChecksumFile( Buffer, NBytes );
            }
            if ( m_frame_checksum.get( ) )
            {
                calcChecksumFrame( Buffer, NBytes );
            }
            if ( m_md5 )
            {
                calcMD5Sum( Buffer, NBytes );
            }
        }

        inline void
        FrameStreamBase::setLastError( const std::string& Message )
        {
            m_last_error_message = Message;
        }

    } // namespace Common
} // namespace FrameCPP

#endif /* FrameCPP_COMMON_FrameStreamBase_HH */
