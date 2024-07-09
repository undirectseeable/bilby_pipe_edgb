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

#ifndef FrameCPP__COMMON__StreamRef_HH
#define FrameCPP__COMMON__StreamRef_HH

#include "ldastoolsal/types.hh"
#include "ldastoolsal/reverse.hh"

#include "framecpp/Common/FrameSpec.hh"
#include "framecpp/Common/StringStream.hh"
#include "framecpp/Common/IOStream.hh"
#include "framecpp/Common/StreamRefInterface.hh"

namespace FrameCPP
{
    namespace Common
    {
        template < class LT, class CT, class IT >
        class StreamRef : public StreamRefInterface
        {
        public:
            typedef StreamRefInterface::length_type   length_type;
            typedef StreamRefInterface::class_type    class_type;
            typedef StreamRefInterface::instance_type instance_type;

            /// \brief Constructor
            StreamRef( );

            /// \brief Destructor
            virtual ~StreamRef( );

            virtual FrameSpec::size_type SizeOf( ) const;

            FrameSpec::size_type Bytes( const StreamBase& Stream ) const;

            virtual class_type GetClass( ) const;

            virtual instance_type GetInstance( ) const;

            virtual length_type GetLength( ) const;

            virtual void SetClass( class_type Class );

            virtual void SetInstance( instance_type Instance );

            virtual void SetLength( length_type Length );

            virtual StreamRef< LT, CT, IT >* Create( IStream& Stream ) const;

            virtual StreamRef< LT, CT, IT >* Clone( ) const;

            virtual const char* ObjectStructName( ) const;

            virtual void Write( OStream& Stream ) const;

            /// \brief comparison operator
            virtual bool operator==( const StreamRef< LT, CT, IT >& RHS ) const;

            /// \brief comparison operator
            virtual bool
            operator==( const Common::FrameSpec::Object& Obj ) const;

        protected:
            virtual void assign( IStringStream& Stream );

            /// \brief Down grade an object
            virtual FrameSpec::ObjectInterface::demote_ret_type
            demote( INT_2U Target, demote_arg_type Obj, IStream* Stream ) const;

            /// \brief Upgrade an object
            virtual FrameSpec::ObjectInterface::promote_ret_type
            promote( INT_2U                                       Target,
                     FrameSpec::ObjectInterface::promote_arg_type Obj,
                     IStream* Stream ) const;

        private:
            using Object::Create;

            typedef LT internal_length_type;
            typedef CT internal_class_type;
            typedef IT internal_instance_type;

            internal_length_type   m_length;
            internal_class_type    m_class;
            internal_instance_type m_instance;

            StreamRef( IStream& Stream );
            StreamRef( const StreamRef& Source );

        }; // class - StreamRef

        template < typename LT, typename CT, typename IT >
        StreamRef< LT, CT, IT >::StreamRef( )
            : m_length( 0 ), m_class( 0 ), m_instance( 0 )
        {
        }

        template < typename LT, typename CT, typename IT >
        StreamRef< LT, CT, IT >::StreamRef( IStream& Stream )
            : m_length( 0 ), m_class( 0 ), m_instance( 0 )
        {
            Stream >> m_length >> m_class >> m_instance;
        }

        template < typename LT, typename CT, typename IT >
        StreamRef< LT, CT, IT >::StreamRef( const StreamRef& Source )
            : StreamRefInterface( Source ), m_length( Source.m_length ),
              m_class( Source.m_class ), m_instance( Source.m_instance )
        {
        }

        template < typename LT, typename CT, typename IT >
        StreamRef< LT, CT, IT >::~StreamRef( )
        {
        }

        template < typename LT, typename CT, typename IT >
        inline cmn_streamsize_type
        StreamRef< LT, CT, IT >::SizeOf( ) const
        {
            return sizeof( m_length ) + sizeof( m_class ) +
                sizeof( m_instance );
        }

        template < typename LT, typename CT, typename IT >
        cmn_streamsize_type
        StreamRef< LT, CT, IT >::Bytes( const StreamBase& Stream ) const
        {
            return SizeOf( );
        }

        template < typename LT, typename CT, typename IT >
        inline typename StreamRef< LT, CT, IT >::class_type
        StreamRef< LT, CT, IT >::GetClass( ) const
        {
            return m_class;
        }

        template < typename LT, typename CT, typename IT >
        inline typename StreamRef< LT, CT, IT >::instance_type
        StreamRef< LT, CT, IT >::GetInstance( ) const
        {
            return m_instance;
        }

        template < typename LT, typename CT, typename IT >
        inline typename StreamRef< LT, CT, IT >::length_type
        StreamRef< LT, CT, IT >::GetLength( ) const
        {
            return m_length;
        }

        template < typename LT, typename CT, typename IT >
        inline void
        StreamRef< LT, CT, IT >::SetClass( class_type Class )
        {
            m_class = Class;
        }

        template < typename LT, typename CT, typename IT >
        inline void
        StreamRef< LT, CT, IT >::SetInstance( instance_type Instance )
        {
            m_instance = Instance;
        }

        template < typename LT, typename CT, typename IT >
        inline void
        StreamRef< LT, CT, IT >::SetLength( length_type Length )
        {
            m_length = Length;
        }

        template < typename LT, typename CT, typename IT >
        inline StreamRef< LT, CT, IT >*
        StreamRef< LT, CT, IT >::Create( IStream& Stream ) const
        {
            return new StreamRef( Stream );
        }

        template < typename LT, typename CT, typename IT >
        inline StreamRef< LT, CT, IT >*
        StreamRef< LT, CT, IT >::Clone( ) const
        {
            return new StreamRef( *this );
        }

        template < typename LT, typename CT, typename IT >
        inline const char*
        StreamRef< LT, CT, IT >::ObjectStructName( ) const
        {
            const char* const name = "StreamRef";
            return name;
        }

        template < typename LT, typename CT, typename IT >
        inline void
        StreamRef< LT, CT, IT >::Write( OStream& Stream ) const
        {
            Stream << m_length << m_class << m_instance;
        }

        template < typename LT, typename CT, typename IT >
        inline bool
        StreamRef< LT, CT, IT >::
        operator==( const StreamRef< LT, CT, IT >& RHS ) const
        {
            return ( ( m_length == RHS.m_length ) &&
                     ( m_class == RHS.m_class ) &&
                     ( m_instance == RHS.m_instance ) );
        }

        template < typename LT, typename CT, typename IT >
        inline bool
        StreamRef< LT, CT, IT >::
        operator==( const Common::FrameSpec::Object& Obj ) const
        {
            typedef StreamRef< LT, CT, IT > data_type;

            try
            {
                const data_type& robj =
                    reinterpret_cast< const data_type& >( Obj );
                return ( *this == robj );
            }
            catch ( ... )
            {
            }
            return ( false );
        }

        template < typename LT, typename CT, typename IT >
        inline void
        StreamRef< LT, CT, IT >::assign( IStringStream& Stream )
        {
            Stream >> m_length >> m_class >> m_instance;
        }

        /// \brief Down grade an object
        template < typename LT, typename CT, typename IT >
        FrameSpec::ObjectInterface::demote_ret_type
        StreamRef< LT, CT, IT >::demote( INT_2U          Target,
                                         demote_arg_type Obj,
                                         IStream*        Stream ) const
        {
            throw Unimplemented(
                "Object* StreamRef::demote( Object* Obj ) const",
                0,
                __FILE__,
                __LINE__ );
        }

        /// \brief Upgrade an object
        template < typename LT, typename CT, typename IT >
        FrameSpec::ObjectInterface::promote_ret_type
        StreamRef< LT, CT, IT >::promote(
            INT_2U                                       Target,
            FrameSpec::ObjectInterface::promote_arg_type Obj,
            IStream*                                     Stream ) const
        {
            throw Unimplemented(
                "Object* StreamRef::promote( Object* Obj ) const",
                0,
                __FILE__,
                __LINE__ );
        }

        //-------------------------------------------------------------------
        /// \brief Generalized common elements of frame structure.
        ///
        /// This templated implementation simplifies the actual
        /// implementation of the common elements of all frame structures
        /// by having each of the storage elements have a separate
        /// template parameter.
        ///
        /// This implementation supports versions of the frame
        /// specification which require the chkType field.
        ///
        /// \tparam LT
        ///     Data type for the length field.
        /// \tparam CKT
        ///     Data type for the chkType field.
        /// \tparam CT
        ///     Data type for the class field.
        /// \tparam IT
        ///     Data type for the instance field.
        //-------------------------------------------------------------------
        template < class LT, class CKT, class CT, class IT >
        class StreamRef2 : public StreamRefInterface
        {
        public:
            typedef StreamRef2< LT, CKT, CT, IT > self_type;
            //-----------------------------------------------------------------
            /// \brief Constructor
            //-----------------------------------------------------------------
            StreamRef2( );

            //-----------------------------------------------------------------
            /// \brief Destructor
            //-----------------------------------------------------------------
            virtual ~StreamRef2( );

            static FrameSpec::size_type Bytes( );

            FrameSpec::size_type Bytes( const StreamBase& Stream ) const;

            virtual FrameSpec::size_type SizeOf( ) const;

            virtual INT_2U GetChkType( ) const;

            virtual class_type GetClass( ) const;

            virtual instance_type GetInstance( ) const;

            virtual length_type GetLength( ) const;

            virtual void SetChkType( INT_2U ChkType );

            virtual void SetClass( class_type Class );

            virtual void SetInstance( instance_type Instance );

            virtual void SetLength( length_type Length );

            virtual self_type* Create( IStream& Stream ) const;

            virtual self_type* Clone( ) const;

            virtual const char* ObjectStructName( ) const;

            virtual void Write( OStream& Stream ) const;

            /// \brief comparison operator
            virtual bool
            operator==( const StreamRef2< LT, CKT, CT, IT >& RHS ) const;

            /// \brief comparison operator
            virtual bool
            operator==( const Common::FrameSpec::Object& Obj ) const;

        protected:
            virtual void assign( IStringStream& Stream );

            /// \brief Down grade an object
            virtual demote_ret_type
            demote( INT_2U Target, demote_arg_type Obj, IStream* Stream ) const;

            /// \brief Upgrade an object
            virtual promote_ret_type promote( INT_2U           Target,
                                              promote_arg_type Obj,
                                              IStream*         Stream ) const;

        private:
            using Object::Create;

            typedef LT  internal_length_type;
            typedef CKT internal_chkType_type;
            typedef CT  internal_class_type;
            typedef IT  internal_instance_type;

            internal_length_type   m_length;
            internal_chkType_type  m_chkType;
            internal_class_type    m_class;
            internal_instance_type m_instance;

            StreamRef2( IStream& Stream );
            StreamRef2( const StreamRef2& Source );

        }; // class - StreamRef2

        template < typename LT, typename CKT, typename CT, typename IT >
        StreamRef2< LT, CKT, CT, IT >::StreamRef2( )
            : m_length( 0 ), m_chkType( 0 ), m_class( 0 ), m_instance( 0 )
        {
        }

        template < typename LT, typename CKT, typename CT, typename IT >
        StreamRef2< LT, CKT, CT, IT >::StreamRef2( IStream& Stream )
            : m_length( 0 ), m_chkType( 0 ), m_class( 0 ), m_instance( 0 )
        {
            Stream >> m_length >> m_chkType >> m_class >> m_instance;

            if ( m_chkType )
            {
                char buffer[ sizeof( LT ) + sizeof( CKT ) + sizeof( CT ) +
                             sizeof( IT ) ];

                {
                    char* pos = buffer;

#define COPY( var )                                                            \
    {                                                                          \
        char* p( reinterpret_cast< char* >( &var ) );                          \
                                                                               \
        std::copy( p, p + sizeof( var ), pos );                                \
        pos += sizeof( var );                                                  \
    }

                    COPY( m_length );
                    COPY( m_chkType );
                    COPY( m_class );
                    COPY( m_instance );
#undef COPY
                }

                if ( Stream.ByteSwapping( ) )
                {
#if LM_DEBUG_INPUT
                    std::cerr << "DEBUG: Read StreamRef2:"
                              << " swapping bytes"
                              << " [ " << __LINE__ << ": " << __FILE__ << " ]"
                              << std::endl;
#endif /* LM_DEBUG_INPUT */
                    char* pos = buffer;

                    reverse< sizeof( m_length ) >( pos, 1 );
                    pos += sizeof( m_length );

                    reverse< sizeof( m_chkType ) >( pos, 1 );
                    pos += sizeof( m_chkType );

                    reverse< sizeof( m_class ) >( pos, 1 );
                    pos += sizeof( m_class );

                    reverse< sizeof( m_instance ) >( pos, 1 );
                }

                Stream.SetCheckSumObject(
                    (const CheckSum::kind_type)m_chkType );
                Stream.GetCheckSumObject( )->Filter( &( buffer[ 0 ] ),
                                                     sizeof( buffer ) );

#if LM_DEBUG_INPUT
                std::cerr << "DEBUG: Read StreamRef2:"
                          << " size: " << sizeof( buffer ) << std::endl
#endif /* LM_DEBUG_INPUT */
                    ;
            }
#if LM_DEBUG_INPUT
            std::cerr << "DEBUG: Read StreamRef2:"
                      << " m_length:" << m_length
                      << " m_chkType: " << (int)m_chkType
                      << " m_class: " << (int)m_class
                      << " m_instance: " << m_instance << " [ " << __LINE__
                      << ": " << __FILE__ " ]" << std::endl;
#endif /* LM_DEBUG_INPUT */
        }

        template < typename LT, typename CKT, typename CT, typename IT >
        StreamRef2< LT, CKT, CT, IT >::StreamRef2( const StreamRef2& Source )
            : Common::StreamRefInterface( Source ), m_length( Source.m_length ),
              m_chkType( Source.m_chkType ), m_class( Source.m_class ),
              m_instance( Source.m_instance )
        {
        }

        template < typename LT, typename CKT, typename CT, typename IT >
        StreamRef2< LT, CKT, CT, IT >::~StreamRef2( )
        {
        }

        template < typename LT, typename CKT, typename CT, typename IT >
        inline cmn_streamsize_type
        StreamRef2< LT, CKT, CT, IT >::Bytes( )
        {
            return sizeof( LT ) + sizeof( CKT ) + sizeof( CT ) + sizeof( IT );
        }

        template < typename LT, typename CKT, typename CT, typename IT >
        cmn_streamsize_type
        StreamRef2< LT, CKT, CT, IT >::Bytes( const StreamBase& Stream ) const
        {
            return Bytes( );
        }

        template < typename LT, typename CKT, typename CT, typename IT >
        FrameSpec::size_type
        StreamRef2< LT, CKT, CT, IT >::SizeOf( ) const
        {
            return Bytes( );
        }

        template < typename LT, typename CKT, typename CT, typename IT >
        inline typename StreamRef2< LT, CKT, CT, IT >::class_type
        StreamRef2< LT, CKT, CT, IT >::GetChkType( ) const
        {
            return m_chkType;
        }

        template < typename LT, typename CKT, typename CT, typename IT >
        inline typename StreamRef2< LT, CKT, CT, IT >::class_type
        StreamRef2< LT, CKT, CT, IT >::GetClass( ) const
        {
            return m_class;
        }

        template < typename LT, typename CKT, typename CT, typename IT >
        inline typename StreamRef2< LT, CKT, CT, IT >::instance_type
        StreamRef2< LT, CKT, CT, IT >::GetInstance( ) const
        {
            return m_instance;
        }

        template < typename LT, typename CKT, typename CT, typename IT >
        inline typename StreamRef2< LT, CKT, CT, IT >::length_type
        StreamRef2< LT, CKT, CT, IT >::GetLength( ) const
        {
            return m_length;
        }

        template < typename LT, typename CKT, typename CT, typename IT >
        inline void
        StreamRef2< LT, CKT, CT, IT >::assign( IStringStream& Stream )
        {
#if 0 || 1
      Stream
	>> m_length
	>> m_chkType
	>> m_class
	>> m_instance
	;
#else
            Stream >> m_length;
            std::cerr << "DEBUG: Common::StreamRef:"
                      << " Stream.tellg( ): " << Stream.tellg( )
                      << " m_length: " << m_length << std::endl;
            Stream >> m_chkType;
            std::cerr << "DEBUG: Common::StreamRef:"
                      << " Stream.tellg( ): " << Stream.tellg( ) << std::endl;
            Stream >> m_class;
            std::cerr << "DEBUG: Common::StreamRef:"
                      << " Stream.tellg( ): " << Stream.tellg( ) << std::endl;
            Stream >> m_instance;
            std::cerr << "DEBUG: Common::StreamRef:"
                      << " Stream.tellg( ): " << Stream.tellg( ) << std::endl;
#endif
        }

        template < typename LT, typename CKT, typename CT, typename IT >
        inline void
        StreamRef2< LT, CKT, CT, IT >::SetChkType( INT_2U ChkType )
        {
            m_chkType = ChkType;
        }

        template < typename LT, typename CKT, typename CT, typename IT >
        inline void
        StreamRef2< LT, CKT, CT, IT >::SetClass( class_type Class )
        {
            m_class = Class;
        }

        template < typename LT, typename CKT, typename CT, typename IT >
        inline void
        StreamRef2< LT, CKT, CT, IT >::SetInstance( instance_type Instance )
        {
            m_instance = Instance;
        }

        template < typename LT, typename CKT, typename CT, typename IT >
        inline void
        StreamRef2< LT, CKT, CT, IT >::SetLength( length_type Length )
        {
            m_length = Length;
        }

        template < typename LT, typename CKT, typename CT, typename IT >
        inline StreamRef2< LT, CKT, CT, IT >*
        StreamRef2< LT, CKT, CT, IT >::Create( IStream& Stream ) const
        {
            return new StreamRef2( Stream );
        }

        template < typename LT, typename CKT, typename CT, typename IT >
        inline StreamRef2< LT, CKT, CT, IT >*
        StreamRef2< LT, CKT, CT, IT >::Clone( ) const
        {
            return new StreamRef2( *this );
        }

        template < typename LT, typename CKT, typename CT, typename IT >
        inline const char*
        StreamRef2< LT, CKT, CT, IT >::ObjectStructName( ) const
        {
            const char* const name = "StreamRef2";
            return name;
        }

        template < typename LT, typename CKT, typename CT, typename IT >
        inline void
        StreamRef2< LT, CKT, CT, IT >::Write( OStream& Stream ) const
        {
            CKT chkType = m_chkType;

            if ( Stream.GetCheckSumObject( ) )
            {
                chkType = Stream.GetCheckSumObject( )->Type( );
            }
            Stream << m_length << chkType << m_class << m_instance;
        }

        template < typename LT, typename CKT, typename CT, typename IT >
        inline bool
        StreamRef2< LT, CKT, CT, IT >::
        operator==( const StreamRef2< LT, CKT, CT, IT >& RHS ) const
        {
            return ( ( m_length == RHS.m_length ) &&
                     ( m_class == RHS.m_class ) &&
                     ( m_instance == RHS.m_instance ) );
        }

        template < typename LT, typename CKT, typename CT, typename IT >
        inline bool
        StreamRef2< LT, CKT, CT, IT >::
        operator==( const Common::FrameSpec::Object& Obj ) const
        {
            typedef StreamRef2< LT, CKT, CT, IT > data_type;

            try
            {
                const data_type& robj =
                    reinterpret_cast< const data_type& >( Obj );
                return ( *this == robj );
            }
            catch ( ... )
            {
            }
            return ( false );
        }

        /// \brief Down grade an object
        template < typename LT, typename CKT, typename CT, typename IT >
        typename StreamRef2< LT, CKT, CT, IT >::demote_ret_type
        StreamRef2< LT, CKT, CT, IT >::demote( INT_2U          Target,
                                               demote_arg_type Obj,
                                               IStream*        Stream ) const
        {
            throw Unimplemented(
                "Object* StreamRef2::demote( Object* Obj ) const",
                0,
                __FILE__,
                __LINE__ );
        }

        /// \brief Upgrade an object
        template < typename LT, typename CKT, typename CT, typename IT >
        typename StreamRef2< LT, CKT, CT, IT >::promote_ret_type
        StreamRef2< LT, CKT, CT, IT >::promote( INT_2U           Target,
                                                promote_arg_type Obj,
                                                IStream*         Stream ) const
        {
            throw Unimplemented(
                "Object* StreamRef2::promote( Object* Obj ) const",
                0,
                __FILE__,
                __LINE__ );
        }

    } // namespace Common
} // namespace FrameCPP
#endif /* FrameCPP__COMMON__StreamRef_HH */
