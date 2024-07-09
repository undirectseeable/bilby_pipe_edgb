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

#ifndef FRAMECPP__COMMON__FrameSpec_TCC
#define FRAMECPP__COMMON__FrameSpec_TCC

#include "framecpp/Common/CheckSum.hh"
#include "framecpp/Common/Verify.hh"

namespace FrameCPP
{
    namespace Common
    {
        //-------------------------------------------------------------------
        //-------------------------------------------------------------------
        template < typename ObjectType, typename ChecksumType >
        FrameSpec::ObjectWithChecksum< ObjectType, ChecksumType >::
            ObjectWithChecksum( )
            : ObjectType( ), m_chkSum( 0 )
        {
        }

        //-------------------------------------------------------------------
        //-------------------------------------------------------------------
        template < typename ObjectType, typename ChecksumType >
        FrameSpec::ObjectWithChecksum< ObjectType, ChecksumType >::
            ObjectWithChecksum( const Description* Description )
            : ObjectType( Description ), m_chkSum( 0 )
        {
        }

        //-------------------------------------------------------------------
        //-------------------------------------------------------------------
        template < typename ObjectType, typename ChecksumType >
        FrameSpec::ObjectWithChecksum< ObjectType, ChecksumType >::
            ObjectWithChecksum( class_type         Class,
                                const Description* Description )
            : ObjectType( Class, Description ), m_chkSum( 0 )
        {
        }

        //-------------------------------------------------------------------
        //-------------------------------------------------------------------
        template < typename ObjectType, typename ChecksumType >
        FrameSpec::ObjectWithChecksum< ObjectType, ChecksumType >::
            ObjectWithChecksum( const ObjectWithChecksum& Source )
            : ObjectType( Source ), m_chkSum( 0 )
        {
        }

        //-------------------------------------------------------------------
        //-------------------------------------------------------------------
        template < typename ObjectType, typename ChecksumType >
        FrameSpec::ObjectWithChecksum< ObjectType, ChecksumType >::
            ObjectWithChecksum( IStream& Stream )
            : ObjectType( Stream ), m_chkSum( 0 )
        {
            //-----------------------------------------------------------------
            // Setup for reading the checksum
            //-----------------------------------------------------------------
            ChecksumType chkSum( 0 );

            //-----------------------------------------------------------------
            // Capture the checksum value before reading the checksum
            // stored in the stream.
            //-----------------------------------------------------------------
            if ( Stream.GetCheckSumObject( ) &&
                 Stream.GetCheckSumObject( )->GetChecksum( ) )
            {
                chkSum = Stream.GetCheckSumObject( )->GetChecksum( )->value( );
            }
            Stream << m_chkSum;

#if LM_DEBUG_INPUT
            std::cerr << "DEBUG:"
                      << " stored checksum: " << chkSum
                      << " calculated checksum: " << m_chkSum << " [ "
                      << __LINE__ << ": " << __FILE__ << " ]" << std::endl;
#endif /* LM_DEBUG_INPUT */
            //-----------------------------------------------------------------
            // Verify the checksum
            //-----------------------------------------------------------------
            if ( ( chkSum != 0 ) // Not calculated at time of reading
                 && ( m_chkSum != 0 ) // Not calculated at the time of writing
                 && ( m_chkSum != chkSum ) )
            {
                std::ostringstream msg;

                msg << "Object checksum failure: "
                    << CheckSum::FormatError( m_chkSum, chkSum )
                    << " for object: ";
                throw VerifyException( VerifyException::CHECKSUM_ERROR,
                                       msg.str( ) );
            }
        }

        //-------------------------------------------------------------------
        //-------------------------------------------------------------------
        template < typename ObjectType, typename ChecksumType >
        FrameSpec::ObjectWithChecksum< ObjectType,
                                       ChecksumType >::~ObjectWithChecksum( )
        {
        }

        //-------------------------------------------------------------------
        //-------------------------------------------------------------------
        template < typename ObjectType, typename ChecksumType >
        FrameSpec::size_type
        FrameSpec::ObjectWithChecksum< ObjectType, ChecksumType >::Bytes(
            const StreamBase& Stream ) const
        {
            return sizeof( ChecksumType ) + pBytes( Stream );
        }

        //-------------------------------------------------------------------
        //-------------------------------------------------------------------
        template < typename ObjectType, typename ChecksumType >
        const char*
        FrameSpec::ObjectWithChecksum< ObjectType,
                                       ChecksumType >::CheckSumDataClass( )
        {
            static const char* d = "INT_4U";

            return d;
        }

        //-------------------------------------------------------------------
        //-------------------------------------------------------------------
        template < typename ObjectType, typename ChecksumType >
        const char*
        FrameSpec::ObjectWithChecksum< ObjectType,
                                       ChecksumType >::CheckSumDataComment( )
        {
            static const char* c = "Struct checksum";

            return c;
        }

        //-------------------------------------------------------------------
        //-------------------------------------------------------------------
        template < typename ObjectType, typename ChecksumType >
        FrameSpec::ObjectWithChecksum< ObjectType, ChecksumType >*
        FrameSpec::ObjectWithChecksum< ObjectType, ChecksumType >::Create(
            Common::IStream& Stream ) const
        {
            self_type* retval = pCreate( Stream );

            ChecksumType checksum = 0;

            if ( retval )
            {
                if ( Stream.GetCheckSumObject( ) )
                {
                    if ( Stream.GetCheckSumObject( )->GetChecksum( ) )
                    {
                        //-----------------------------------------------------------
                        // Do this for the side effect of freezing the checksum
                        // value
                        //-----------------------------------------------------------
#if LM_DEBUG_INPUT
                        std::cerr << "DEBUG:"
                                  << " Location: " << __LINE__ << ": "
                                  << __FILE__ << std::endl;
#endif /* LM_DEBUG_INPUT */
                        checksum = Stream.GetCheckSumObject( )
                                       ->GetChecksum( )
                                       ->value( );
                    }
                    Stream.SetCheckSumObject( CheckSum::NONE );
                }
                Stream >> retval->m_chkSum;
                //---------------------------------------------------------------
                // Verify the checksum
                //---------------------------------------------------------------
#if LM_DEBUG_INPUT
                std::cerr << "DEBUG:"
                          << " stored checksum: " << retval->m_chkSum
                          << " calculated checksum: " << checksum << " [ "
                          << __LINE__ << ": " << __FILE__ << " ]" << std::endl;
#endif /* LM_DEBUG_INPUT */
                if ( ( checksum != 0 ) // Not calculated at time of reading
                     && ( retval->m_chkSum !=
                          0 ) // Not calculated at the time of writing
                     && ( retval->m_chkSum != checksum ) )
                {
                    std::ostringstream msg;

                    msg << "Object checksum failure: "
                        << CheckSum::FormatError( retval->m_chkSum, checksum )
                        << " for object: ";
                    throw VerifyException( VerifyException::CHECKSUM_ERROR,
                                           msg.str( ) );
                }
            }
            return retval;
        }

        //-------------------------------------------------------------------
        //-------------------------------------------------------------------
        template < typename ObjectType, typename ChecksumType >
        void
        FrameSpec::ObjectWithChecksum< ObjectType, ChecksumType >::Write(
            OStream& Stream ) const
        {
            pWrite( Stream );
            ChecksumType chkSum = m_chkSum;
            if ( Stream.GetCheckSumObject( ) &&
                 Stream.GetCheckSumObject( )->GetChecksum( ) )
            {
                chkSum = Stream.GetCheckSumObject( )->GetChecksum( )->value( );
            }
            Stream << chkSum;
        }
    } // namespace Common

} // namespace FrameCPP

#endif /* FRAMECPP__COMMON__FrameSpec_TCC */
