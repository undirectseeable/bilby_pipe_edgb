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

#ifndef FrameCPP__COMMON__IOStream_HH
#define FrameCPP__COMMON__IOStream_HH

#define FRAME_STREAM_FILTER_IN_BUFFER 0

#define LM_DEBUG_OUTPUT 0
#define LM_DEBUG_INPUT 0

#if !defined( SWIGIMPORTED )
#include <iomanip>
#include <iostream>
#include <list>
#include <memory>
#include <string>
#include <typeinfo>
#include <vector>

#include <boost/pointer_cast.hpp>
#include <boost/shared_ptr.hpp>
#endif /* !defined(SWIGIMPORTED) */

#include "ldastoolsal/types.hh"
#include "ldastoolsal/reverse.hh"
#include "ldastoolsal/gpstime.hh"
#include "ldastoolsal/util.hh"
#if !defined( SWIGIMPORTED )
#include "ldastoolsal/Profile.hh"
#endif /* !defined(SWIGIMPORTED) */

#include "framecpp/Common/FrameSpec.hh"

#include "framecpp/Common/CheckSum.hh"
#include "framecpp/Common/CheckSumFilter.hh"
#include "framecpp/Common/Dictionary.hh"
#include "framecpp/Common/FrameBufferInterface.hh"
#include "framecpp/Common/MD5SumFilter.hh"
#include "framecpp/Common/PTR_STRUCT_BASE.hh"
#include "framecpp/Common/StreamFilter.hh"

#if LM_DEBUG_OUTPUT || LM_DEBUG_INPUT
extern bool filter_on;
#endif /* LM_DEBUG_OUTPUT || LM_DEBUG_INPUT */

namespace FrameCPP
{
    namespace Common
    {
        class Dictionary;
        class StreamRefInterface;
        struct PTR_STRUCT_BASE;
        class FrStatData;
        class FrHeader;

        template < typename T >
        class Container;
        template < typename L >
        class STRING;
        template < typename L >
        class STRING_SHADOW;
        template < typename T, const std::string& ( T::*F )( ) const >
        class SearchContainer;

        //===================================================================
        // Forward declaration of some templated classes
        //===================================================================
        class IStream;
        class OStream;

        //===================================================================
        //===================================================================
        class StreamBase
        {
        public:
            typedef boost::shared_ptr< FrameSpec::Object > object_type;
            typedef const Dictionary::streamref_type::element_type*
                                               const_stream_ref_ptr_type;
            typedef Dictionary::streamref_type streamref_type;

            StreamBase( );

            virtual ~StreamBase( );

            virtual void Cleanup( );

            INT_2U GetClassId( const std::string& ClassName ) const;

            INT_2U GetFSIId( INT_2U StreamId ) const;

            cmn_streamsize_type PtrStructBytes( ) const;

            const_stream_ref_ptr_type ReferenceStreamRef( ) const;

            const Dictionary& GetDictionary( ) const;

            Dictionary& GetDictionary( );

        protected:
            typedef std::unique_ptr< CheckSumFilter > checksum_filter_type;
            typedef std::unique_ptr< MD5SumFilter >   md5sum_filter_type;
            typedef LDASTools::AL::unordered_map< INT_2U, INT_2U >
                streamid_to_fsiid_type;

            typedef boost::shared_ptr< PTR_STRUCT_BASE > ptr_struct_base_type;

            Dictionary                     m_dictionary;
            object_type                    m_null_stream_ref;
            ptr_struct_base_type           m_ptr_struct_object;
            mutable streamid_to_fsiid_type m_stream_id_to_fsi_id;

            //-----------------------------------------------------------------
            /// \brief Checksum for file
            //-----------------------------------------------------------------
            checksum_filter_type m_file_checksum;
            //-----------------------------------------------------------------
            /// \brief Checksum for frame
            //-----------------------------------------------------------------
            checksum_filter_type m_frame_checksum;
            //-----------------------------------------------------------------
            /// \brief Checksum for object
            //-----------------------------------------------------------------
            checksum_filter_type m_obj_checksum;
            //-----------------------------------------------------------------
            /// \brief MD5Sum value for the files
            //-----------------------------------------------------------------
            md5sum_filter_type m_file_md5sum;

            const FrameSpec::Info& frameSpecInfo( ) const;

            virtual void frameSpecInfo( const FrameSpec::Info* Spec );

        private:
            typedef LDASTools::AL::unordered_map<
                std::string,
                INT_2U,
                LDASTools::AL::hash< std::string >,
                LDASTools::AL::CaseInsensitiveCmp >
                cntocid_mapping_type;

            const FrameSpec::Info*      m_frame_spec;
            mutable cmn_streamsize_type m_ptr_struct_bytes;

            static const bool           m_initialized;
            static cntocid_mapping_type m_class_name_to_class_id;

            static bool initialize( );

            static void cleanup_at_exit( );
        };

        inline cmn_streamsize_type
        StreamBase::PtrStructBytes( ) const
        {
            if ( m_ptr_struct_bytes == 0 )
            {
                const FrameSpec::Object* o = frameSpecInfo( ).FrameObject(
                    FrameSpec::Info::FSI_PTR_STRUCT );
                if ( o )
                {
                    m_ptr_struct_bytes = o->Bytes( *this );
                }
            }
            return m_ptr_struct_bytes;
        }

        inline const Dictionary&
        StreamBase::GetDictionary( ) const
        {
            return m_dictionary;
        }

        inline Dictionary&
        StreamBase::GetDictionary( )
        {
            return m_dictionary;
        }

        inline INT_2U
        StreamBase::GetFSIId( INT_2U StreamId ) const
        {
            const streamid_to_fsiid_type::const_iterator sid_iter =
                m_stream_id_to_fsi_id.find( StreamId );
            if ( sid_iter == m_stream_id_to_fsi_id.end( ) )
            {
                //---------------------------------------------------------------
                // Report the error
                //---------------------------------------------------------------
                std::ostringstream msg;
                msg << "Unable to map from the stream class id (" << StreamId
                    << ") to internal class id";
                throw std::range_error( msg.str( ) );
            }
            return sid_iter->second;
        }

        inline const FrameSpec::Info&
        StreamBase::frameSpecInfo( ) const
        {
            return *m_frame_spec;
        }

        //===================================================================
        //===================================================================
        class IStream : virtual public StreamBase, public std::istream
        {
        public:
            typedef std::istream::char_type char_type;
            typedef std::istream            istream_type;
            typedef FrameBufferInterface    buffer_type;

            //-----------------------------------------------------------------
            /// \brief Manipulator class for input streams
            ///
            /// This manipulator class allows for the dynamic resizing of
            /// classes that define a resize method.
            ///
            /// \code
            /// typedef
            ///    Common::IStream::Resizer<column_name_container_type>
            ///    resizer;
            ///  nColumn_type			nColumn;
            ///  nRow_type			nRow;
            ///  column_name_container_type	columnName;
            ///
            ///  Stream >> nColumn
            ///	 >> nRow
            ///	 >> resizer( columnName, nColumn )
            ///	 >> columnName
            ///	 >> column
            ///    ;
            /// \endcode
            ///
            /// In the example given above, columnName is an array of strings
            /// that needs to be resized after the number of columns
            /// (nColumn) is known.
            ///
            //-----------------------------------------------------------------
            template < typename T, typename S >
            class Resizer
            {
            public:
                //---------------------------------------------------------------
                /// \brief Constructor
                ///
                /// \param Container
                ///     The container to be resized
                ///
                /// \param NewSize
                ///     The number of elements that the new container
                ///     should have.
                ///
                //---------------------------------------------------------------
                Resizer( T& Container, S& NewSize )
                    : container( Container ), size( NewSize )
                {
                }

                //---------------------------------------------------------------
                /// \brief
                ///
                /// \param In
                ///     Input stream.
                ///
                /// \return
                ///     The input stream.
                //---------------------------------------------------------------
                IStream&
                operator( )( IStream& In )
                {
                    container.resize( size );
                    return In;
                }

            private:
                //---------------------------------------------------------------
                /// \brief Container being resized
                //---------------------------------------------------------------
                T& container;
                //---------------------------------------------------------------
                /// \brief New size for the container.
                //---------------------------------------------------------------
                S& size;
            };

            IStream( buffer_type* Buffer, bool AutoDelete = true );

            virtual ~IStream( );

            virtual void Cleanup( );

            CheckSumFilter* GetCheckSumFile( ) const;

            void SetCheckSumFile( const CheckSum::kind_type Type );

            CheckSumFilter* GetCheckSumFrame( ) const;

            void SetCheckSumFrame( const CheckSum::kind_type Type );

            CheckSumFilter* GetCheckSumObject( ) const;

            void SetCheckSumObject( const CheckSum::kind_type Type );

            virtual const FrHeader& GetFrHeader( ) const;

            Dictionary::ptr_struct_key_type NextLookup( object_type Obj ) const;

            void RemoveResolver( const void* Old, int MaxDepth );

            template < typename T >
            void PushPtr( boost::shared_ptr< T >* Obj );

            template < typename T_NEW, typename T_OLD >
            void ReplacePtr( boost::shared_ptr< T_NEW >* Obj,
                             boost::shared_ptr< T_OLD >* OldPtr,
                             const int                   MaxDepth );

            template < typename T >
            void PushRef( Container< T >& C );

            template < typename T, typename OT >
            void ReplaceRef( Container< T >&        C,
                             const Container< OT >& Old,
                             const int              MaxDepth );

            FrameBufferInterface* rdbuf( ) const;

            IStream& read( char_type* S, std::streamsize N );

            virtual ptr_struct_base_type Next( object_type Obj );

            virtual ptr_struct_base_type Next( object_type::element_type* Obj );

            ptr_struct_base_type ReadPtrStruct( );

            void Resolve( );

            //-----------------------------------------------------------------
            /// \brief Return the size of the stream
            ///
            /// \return
            ///     The number of bytes that compose the stream
            //-----------------------------------------------------------------
            cmn_streamsize_type Size( );

            template < typename T >
            IStream& operator>>( boost::shared_ptr< T >* Data );

            template < typename T, const std::string& ( T::*F )( ) const >
            IStream& operator>>( SearchContainer< T, F >& SC );

            template < typename T >
            IStream& operator>>( Container< T >& C );

            template < typename L >
            IStream& operator>>( STRING< L >& String );

            template < typename L >
            IStream& operator>>( STRING_SHADOW< L >& String );

            template < typename L >
            IStream& operator>>( std::vector< STRING< L > >& String );

            template < typename DT >
            IStream& operator>>( std::vector< DT >& Data );

            template < typename DT >
            IStream& operator>>( DT& Data );

            template < typename T, typename S >
            IStream& operator>>( IStream::Resizer< T, S > Value );

            bool ByteSwapping( ) const;

        protected:
            class resolver
            {
            public:
                resolver( ptr_struct_base_type PtrStruct,
                          const char*          ObjectName );
                resolver( resolver& Source );
                virtual ~resolver( );

                virtual void Resolve( IStream& Stream ) = 0;
                virtual bool operator==( const void* RHS ) const = 0;

                inline const std::string&
                ObjectName( ) const
                {
                    return m_object_name;
                }

                ptr_struct_base_type PtrStruct( ) const;

            protected:
                ptr_struct_base_type m_ptr_struct;
                std::string          m_object_name;
            };

            typedef boost::shared_ptr< resolver > resolver_type;
            typedef std::list< resolver_type >    resolver_container_type;

            bool m_logNextPtr;

            void nextReplace( object_type OldObj, object_type NewObj );

            void byteSwapping( bool Value );

            virtual void pushResolver( resolver_type Resolver );

            object_type objectLookup( object_type::element_type* Pointer );

            const resolver_container_type& resolverContainer( ) const;

            resolver_container_type& resolverContainer( );

            void setAutoDeleteBuffer( const bool Value );

        private:
            template < typename T >
            class ptr_reference : public resolver
            {
            public:
                ptr_reference( boost::shared_ptr< T >* Obj,
                               ptr_struct_base_type    PtrStruct );
                ptr_reference( boost::shared_ptr< T >* Obj, resolver& Source );
                virtual ~ptr_reference( );

                virtual void Resolve( IStream& Stream );

                virtual bool operator==( const void* RHS ) const;

            private:
                boost::shared_ptr< T >* m_object;
            };

            template < typename T >
            class container_reference : public resolver
            {
            public:
                container_reference( Container< T >&      C,
                                     ptr_struct_base_type PtrStruct );
                container_reference( Container< T >& C, resolver& Source );
                ~container_reference( );

                virtual void Resolve( IStream& Stream );

                virtual bool operator==( const void* RHS ) const;

            private:
                Container< T >& m_container;
            };

            template < typename T >
            struct smart_pointer_hash
            {
                inline size_t
                operator( )( const T Key ) const
                {
                    return reinterpret_cast< size_t >( Key.get( ) );
                }
            };

            /// \brief Maintains information to reconstruct linked lists
            typedef LDASTools::AL::unordered_map<
                object_type,
                Dictionary::ptr_struct_key_type,
                smart_pointer_hash< object_type > >
                next_container_type;

            typedef LDASTools::AL::unordered_map<
                object_type::element_type*,
                object_type,
                LDASTools::AL::hash_pointer< object_type::element_type > >
                object_container_type;

            typedef std::unique_ptr< CheckSumFilter > checksum_filter_type;
            typedef std::unique_ptr< buffer_type >    buffer_ptr_type;

            bool                stream_length_valid;
            cmn_streamsize_type stream_length;

            buffer_ptr_type         m_buffer;
            bool                    m_buffer_auto_delete;
            bool                    m_filter_internally;
            next_container_type     m_next_container;
            bool                    m_byte_swapping;
            resolver_container_type m_resolver_container;
            checksum_filter_type    m_file_checksum;
            checksum_filter_type    m_frame_checksum;
            checksum_filter_type    m_obj_checksum;
            object_container_type   m_objects;
        };

        inline bool
        IStream::ByteSwapping( ) const
        {
            return m_byte_swapping;
        }

        inline Dictionary::ptr_struct_key_type
        IStream::NextLookup( object_type Obj ) const
        {
            next_container_type::const_iterator key_iterator =
                m_next_container.find( Obj );

            if ( key_iterator != m_next_container.end( ) )
            {
                return key_iterator->second;
            }
            Dictionary::ptr_struct_key_type key( 0, 0 );
            return key;
        }

        inline cmn_streamsize_type
        IStream::Size( )
        {
            if ( false == stream_length_valid )
            {
                cmn_streamsize_type here( tellg( ) );

                seekg( 0, this->end );
                stream_length = tellg( );
                seekg( here, this->beg );
                stream_length_valid = true;
            }
            return stream_length;
        }

        inline void
        IStream::nextReplace( object_type Old, object_type New )
        {
            next_container_type::const_iterator key_iterator =
                m_next_container.find( Old );

            if ( key_iterator != m_next_container.end( ) )
            {
                m_next_container[ New ] = key_iterator->second;
                m_next_container.erase( Old );
            }
        }

        inline void
        IStream::byteSwapping( bool Value )
        {
            m_byte_swapping = Value;
        }

        inline IStream::object_type
        IStream::objectLookup( object_type::element_type* Pointer )
        {
            object_type retval;

            object_container_type::const_iterator pos =
                m_objects.find( Pointer );
            if ( pos == m_objects.end( ) )
            {
                retval.reset( Pointer );

                m_objects[ Pointer ] = retval;
            }
            else
            {
                retval = pos->second;
            }
            return retval;
        }

        inline const IStream::resolver_container_type&
        IStream::resolverContainer( ) const
        {
            return m_resolver_container;
        }

        inline IStream::resolver_container_type&
        IStream::resolverContainer( )
        {
            return m_resolver_container;
        }

        inline void
        IStream::setAutoDeleteBuffer( const bool Value )
        {
            m_buffer_auto_delete = Value;
        }

        //-------------------------------------------------------------------
        //-------------------------------------------------------------------
        inline IStream::resolver::resolver( resolver& Source )
            : m_ptr_struct( Source.m_ptr_struct ),
              m_object_name( Source.m_object_name )
        {
        }

        inline IStream::ptr_struct_base_type
        IStream::resolver::PtrStruct( ) const
        {
            return m_ptr_struct;
        }

        //===================================================================
        // class IStream::ptr_reference
        //===================================================================

        template < typename T >
        inline IStream::ptr_reference< T >::ptr_reference(
            boost::shared_ptr< T >* Obj, resolver& Source )
            : resolver( Source ), m_object( Obj )
        {
        }

        template < typename T >
        IStream::ptr_reference< T >::ptr_reference(
            boost::shared_ptr< T >* Ptr, ptr_struct_base_type PtrStruct )
            : resolver( PtrStruct, typeid( *this ).name( ) ), m_object( Ptr )
        {
            assert( m_object );
        }

        template < typename T >
        IStream::ptr_reference< T >::~ptr_reference( )
        {
            // Nothing to do here
        }

        template < typename T >
        void
        IStream::ptr_reference< T >::Resolve( IStream& Stream )
        {
            //-----------------------------------------------------------------
            // Get all of the objects that are needed to rebuild list.
            //-----------------------------------------------------------------
            Dictionary& dict( Stream.GetDictionary( ) );

            Dictionary::ptr_struct_key_type key( m_ptr_struct->Class( ),
                                                 m_ptr_struct->Instance( ) );
            Dictionary::streamref_type      sr = dict.Ref( key );
            //-----------------------------------------------------------------
            //
            //-----------------------------------------------------------------
            if ( sr )
            {
                ( *m_object ) =
                    boost::dynamic_pointer_cast< T >( dict.Ref( sr ) );
            }
        }

        template < typename T >
        bool
        IStream::ptr_reference< T >::operator==( const void* RHS ) const
        {
            return ( m_object == RHS );
        }

        //-------------------------------------------------------------------
        //-------------------------------------------------------------------

        template < typename T >
        IStream::container_reference< T >::container_reference(
            Container< T >& C, ptr_struct_base_type PtrStruct )
            : resolver( PtrStruct, typeid( *this ).name( ) ), m_container( C )
        {
        }

        template < typename T >
        IStream::container_reference< T >::container_reference(
            Container< T >& C, resolver& Source )
            : resolver( Source ), m_container( C )
        {
        }

        template < typename T >
        IStream::container_reference< T >::~container_reference( )
        {
        }

        template < typename T >
        void
        IStream::container_reference< T >::Resolve( IStream& Stream )
        {
            //-----------------------------------------------------------------
            // Get all of the objects that are needed to rebuild list.
            //-----------------------------------------------------------------
            Dictionary& dict( Stream.GetDictionary( ) );

            Dictionary::ptr_struct_key_type key( m_ptr_struct->Class( ),
                                                 m_ptr_struct->Instance( ) );
            Dictionary::streamref_type      sr = dict.Ref( key );

            //-----------------------------------------------------------------
            //
            //-----------------------------------------------------------------
            if ( sr )
            {
                object_type obj( dict.Ref( sr ) );

                while ( obj )
                {
                    //-------------------------------------------------------------
                    // Place object into container
                    //-------------------------------------------------------------
                    dict.Remove( obj );
                    boost::shared_ptr< T > c_obj =
                        boost::dynamic_pointer_cast< T >( obj );
                    if ( c_obj )
                    {
                        m_container.append( c_obj );
                    }
                    //-------------------------------------------------------------
                    // Advance to the next object
                    //-------------------------------------------------------------
                    key = Stream.NextLookup( obj );
                    if ( ( key.first == 0 ) && ( key.second == 0 ) )
                    {
                        break;
                    }
                    sr = dict.Ref( key );
                    if ( sr )
                    {
                        obj = dict.Ref( sr );
                    }
                    else
                    {
                        obj.reset( );
                    }
                }
            }
        }

        template < typename T >
        bool
        IStream::container_reference< T >::operator==( const void* RHS ) const
        {
            return ( &m_container == RHS );
        }

        //-------------------------------------------------------------------
        //-------------------------------------------------------------------
        inline IStream::IStream( buffer_type* Buffer, bool AutoDelete )
            : std::istream( dynamic_cast< std::streambuf* >( Buffer ) ),
              m_logNextPtr( true ), stream_length_valid( false ),
              stream_length( 0 ), m_buffer( Buffer ),
              m_buffer_auto_delete( AutoDelete ), m_byte_swapping( false )
        {
            if ( Buffer )
            {
                m_filter_internally = Buffer->FilterInternally( );
            }
        }

        inline IStream::~IStream( )
        {
            istream_type::sync( );
            if ( m_buffer_auto_delete == false )
            {
                m_buffer.release( );
            }
        }

        inline CheckSumFilter*
        IStream::GetCheckSumFile( ) const
        {
            return m_file_checksum.get( );
        }

        inline void
        IStream::SetCheckSumFile( const CheckSum::kind_type Type )
        {
            if ( m_file_checksum.get( ) )
            {
                rdbuf( )->FilterRemove( m_file_checksum.get( ) );
            }
            if ( Type == CheckSum::NONE )
            {
                m_file_checksum.reset( (CheckSumFilter*)NULL );
            }
            else
            {
                m_file_checksum.reset( new CheckSumFilter( Type ) );
                rdbuf( )->FilterAdd( m_file_checksum.get( ) );
            }
        }

        inline CheckSumFilter*
        IStream::GetCheckSumFrame( ) const
        {
            return m_frame_checksum.get( );
        }

        inline void
        IStream::SetCheckSumFrame( const CheckSum::kind_type Type )
        {
            if ( m_frame_checksum.get( ) )
            {
                rdbuf( )->FilterRemove( m_frame_checksum.get( ) );
            }
            if ( Type == CheckSum::NONE )
            {
                m_frame_checksum.reset( (CheckSumFilter*)NULL );
            }
            else
            {
                m_frame_checksum.reset( new CheckSumFilter( Type ) );
                rdbuf( )->FilterAdd( m_frame_checksum.get( ) );
            }
        }

        inline CheckSumFilter*
        IStream::GetCheckSumObject( ) const
        {
            return m_obj_checksum.get( );
        }

        inline void
        IStream::SetCheckSumObject( const CheckSum::kind_type Type )
        {
            if ( m_obj_checksum.get( ) )
            {
                rdbuf( )->FilterRemove( m_obj_checksum.get( ) );
            }
            if ( Type == CheckSum::NONE )
            {
                m_obj_checksum.reset( (CheckSumFilter*)NULL );
            }
            else
            {
                m_obj_checksum.reset( new CheckSumFilter( Type ) );
                rdbuf( )->FilterAdd( m_obj_checksum.get( ) );
            }
        }

        inline void
        IStream::RemoveResolver( const void* Old, int MaxDepth )
        {
            for ( resolver_container_type::iterator
                      cur = m_resolver_container.begin( ),
                      last = m_resolver_container.end( );
                  ( --MaxDepth > 0 ) && ( cur != last );
                  ++cur )
            {
                if ( ( *cur ) && ( *( *cur ) == Old ) )
                {
                    m_resolver_container.erase( cur );
                    break;
                }
            }
        }

        template < typename T >
        inline void
        IStream::PushPtr( boost::shared_ptr< T >* Obj )
        {
            //-----------------------------------------------------------------
            // Read the PTR_STRUCT from the stream
            //-----------------------------------------------------------------
            ptr_struct_base_type ptr_struct( ReadPtrStruct( ) );

            if ( ptr_struct->IsNULL( ) )
            {
                return;
            }

            resolver_type r( new ptr_reference< T >( Obj, ptr_struct ) );

            pushResolver( r );
        }

        template < typename T_NEW, typename T_OLD >
        inline void
        IStream::ReplacePtr( boost::shared_ptr< T_NEW >* Obj,
                             boost::shared_ptr< T_OLD >* OldPtr,
                             const int                   MaxDepth )
        {
            int depth = MaxDepth;

            for ( resolver_container_type::iterator
                      cur = m_resolver_container.begin( ),
                      last = m_resolver_container.end( );
                  ( --depth > 0 ) && ( cur != last );
                  ++cur )
            {
                if ( ( *cur ) && ( *( *cur ) == OldPtr ) )
                {
                    // Create a new reference
                    boost::shared_ptr< ptr_reference< T_NEW > > np(
                        new ptr_reference< T_NEW >( Obj,
                                                    ( *cur )->PtrStruct( ) ) );

                    // Out with the old
                    cur = m_resolver_container.erase( cur );
                    // In with the new
                    m_resolver_container.insert( cur, np );
                    break;
                }
            }
        }

        template < typename T >
        inline void
        IStream::PushRef( Container< T >& C )
        {
            //-----------------------------------------------------------------
            // Read the PTR_STRUCT from the stream
            //-----------------------------------------------------------------
            ptr_struct_base_type ptr_struct( ReadPtrStruct( ) );

            if ( ptr_struct->IsNULL( ) )
            {
                //---------------------------------------------------------------
                // No next object
                //---------------------------------------------------------------
                return;
            }

            resolver_type r( new container_reference< T >( C, ptr_struct ) );

            pushResolver( r );
        }

        template < typename T, typename OT >
        inline void
        IStream::ReplaceRef( Container< T >&        C,
                             const Container< OT >& Old,
                             const int              MaxDepth )
        {
            //-----------------------------------------------------------------
            // Go on beyond MaxDepth since most references have a next pointer.
            //-----------------------------------------------------------------
            int depth =
                ( ( MaxDepth > 0 ) ? ( MaxDepth )
                                   : (int)( m_resolver_container.size( ) ) );

            for ( resolver_container_type::iterator
                      cur = m_resolver_container.begin( ),
                      last = m_resolver_container.end( );
                  ( depth > 0 ) && ( cur != last );
                  --depth, ++cur )
            {
                if ( ( *cur ) && ( *( *cur ) == &Old ) )
                {
                    // Create a new reference
                    boost::shared_ptr< container_reference< T > > ncr(
                        new container_reference< T >(
                            C, ( *cur )->PtrStruct( ) ) );

                    // Out with the old
                    cur = m_resolver_container.erase( cur );
                    // In with the new
                    m_resolver_container.insert( cur, ncr );
                    break;
                }
            }
        }

        inline IStream::buffer_type*
        IStream::rdbuf( ) const
        {
            return m_buffer.get( );
        }

        inline IStream&
        IStream::read( char_type* S, std::streamsize N )
        {
            istream_type::read( S, N );
            if ( m_filter_internally == false )
            {
                m_buffer->FilterBuffer( S, S + this->gcount( ) );
#if LM_DEBUG_INPUT
                if ( filter_on )
                {
                    std::cerr << "DEBUG:"
                              << " filtered withing IStream::read"
                              << " [ " << __LINE__ << ": " << __FILE__ << " ]"
                              << std::endl;
                }
#endif /* LM_DEBUG_INPUT */
            }
            return *this;
        }

        template < typename T >
        inline IStream&
        IStream::operator>>( boost::shared_ptr< T >* Data )
        {
            PushPtr( Data );

            return *this;
        }

        template < typename T, const std::string& ( T::*F )( ) const >
        inline IStream&
        IStream::operator>>( SearchContainer< T, F >& SC )
        {
            return SC.StreamIn( *this );
        }

        template < typename T >
        inline IStream&
        IStream::operator>>( Container< T >& C )
        {
            return C.StreamIn( *this );
        }

        template < typename L >
        inline IStream&
        IStream::operator>>( STRING< L >& String )
        {
            String.Read( *this );
            return *this;
        }

        template < typename L >
        inline IStream&
        IStream::operator>>( STRING_SHADOW< L >& String )
        {
            String.Read( *this );
            return *this;
        }

        template < typename L >
        inline IStream&
        IStream::operator>>( std::vector< STRING< L > >& Strings )
        {
            for ( typename std::vector< STRING< L > >::iterator
                      cur = Strings.begin( ),
                      last = Strings.end( );
                  cur != last;
                  ++cur )
            {
                cur->Read( *this );
            }
            return *this;
        }

        template <>
        inline IStream&
        IStream::operator>>( LDASTools::AL::GPSTime& Data )
        {
            INT_4U seconds;
            INT_4U nanoseconds;

            *this >> seconds >> nanoseconds;

            Data = LDASTools::AL::GPSTime( seconds, nanoseconds );
            return *this;
        }

        template < typename DT >
        inline IStream&
        IStream::operator>>( std::vector< DT >& Data )
        {
            if ( Data.size( ) > 0 )
            {
                read( reinterpret_cast< IStream::char_type* >( &( Data[ 0 ] ) ),
                      std::streamsize( sizeof( DT ) * Data.size( ) ) );
                if ( m_byte_swapping )
                {
                    reverse< sizeof( DT ) >( &( Data[ 0 ] ), Data.size( ) );
                }
            }
            return *this;
        }

        template < typename DT >
        inline IStream&
        IStream::operator>>( DT& Data )
        {
            read( reinterpret_cast< IStream::char_type* >( &Data ),
                  std::streamsize( sizeof( Data ) ) );
            if ( m_byte_swapping )
            {
                reverse< sizeof( DT ) >( &Data, 1 );
            }
            return *this;
        }

        template < typename T, typename S >
        inline IStream&
        IStream::operator>>( IStream::Resizer< T, S > Value )
        {
            return Value( *this );
        }

        //===================================================================
        //===================================================================
        class OStream : virtual public StreamBase, public std::ostream
        {
        public:
            typedef std::ostream            ostream_type;
            typedef ostream_type::char_type char_type;
            typedef FrameBufferInterface    buffer_type;

            class Pointer
            {
            public:
                Pointer( object_type Data );

                object_type GetPointer( ) const;

            private:
                object_type m_pointer;
            };

            OStream( buffer_type* Buffer, bool AutoDelete = true );

            virtual ~OStream( );

            /// param[in,out] CompressionScheme
            /// param[in,out] CompressionType
            void Compression( INT_2U& CompressionScheme,
                              INT_2U& CompressionLevel );

            INT_2U CompressionScheme( ) const;

            INT_2U CompressionLevel( ) const;

            template < typename Header >
            const Header* GetFrHeader( ) const;

            virtual INT_8U GetTOCOffset( ) const;

            void Next( object_type Obj, object_type NextObj );

            object_type Next( object_type Obj ) const;

            const PTR_STRUCT_BASE& Reference( object_type Obj ) const;

            OStream& write( const char_type* S, std::streamsize N );

            //-----------------------------------------------------------------
            /// \brief Get an object from the output queue
            ///
            /// \return
            ///   The next object to be written to the stream.
            //-----------------------------------------------------------------
            object_type Pop( );

            //-----------------------------------------------------------------
            /// \brief Append an object to the output queue
            ///
            /// \param[in] Obj
            ///     The object to be written.
            //-----------------------------------------------------------------
            void PushSingle( object_type Obj );

            //-----------------------------------------------------------------
            /// \brief Append multiple objects to the output queue
            ///
            /// \param[in] Start
            ///     The first element to be added to the queue.
            /// \param[in] End
            ///     The last element to be added to the queue.
            /// \param[in] Size
            ///     The number of elements to be added to the queue.
            //-----------------------------------------------------------------
            template < typename Iter >
            void
            PushMulti( Iter Start, Iter End, size_t Size )
            {
                if ( Size == 0 )
                {
                    return;
                }

                object_queue_type c;

                object_type previous;

                if ( Size == 1 )
                {
                    m_dictionary.RefCreate( *Start, *this );
                    m_write_objects_pos =
                        m_write_objects.insert( m_write_objects_pos, *Start );
                    ++m_write_objects_pos;
                }
                else
                {
                    while ( Start != End )
                    {
                        m_dictionary.RefCreate( *Start, *this );
                        c.push_back( *Start );
                        if ( previous )
                        {
                            Next( previous, *Start );
                        }
                        previous = *Start;
                        ++Start;
                    }
                    m_write_objects.splice( m_write_objects_pos, c );
                }
            }

            /// \brief Create a PTR_STRUCT for next object
            const Common::PTR_STRUCT_BASE&
            NextPtrStruct( object_type Cur ) const;

            /// \brief Create a PTR_STRUCT for next object
            const Common::PTR_STRUCT_BASE&
            NextPtrStruct( const object_type::element_type* Cur ) const;

            virtual INT_4U GetNumberOfFrames( ) const;

            /// \todo support MD5Sum

            OStream& operator<<( object_type Data );

            OStream& operator<<( Pointer Data );

            template < typename T, const std::string& ( T::*F )( ) const >
            inline OStream&
            operator<<( const SearchContainer< T, F >& SC )
            {
                return SC.StreamOut( *this );
            }

            template < typename T >
            inline OStream&
            operator<<( const Container< T >& C )
            {
                return C.StreamOut( *this );
            }

            template < typename L >
            inline OStream&
            operator<<( const STRING< L >& String )
            {
                String.Write( *this );
                return *this;
            }

            template < typename L >
            inline OStream&
            operator<<( const STRING_SHADOW< L >& String )
            {
                String.Write( *this );
                return *this;
            }

            template < typename L >
            inline OStream&
            operator<<( const std::vector< STRING< L > >& Strings )
            {
                for ( typename std::vector< STRING< L > >::const_iterator
                          cur = Strings.begin( ),
                          last = Strings.end( );
                      cur != last;
                      ++cur )
                {
                    cur->Write( *this );
                }
                return *this;
            }

            template < typename DT >
            OStream& operator<<( const std::vector< DT >& N );

            template < typename DT >
            OStream& operator<<( const DT& N );

            inline buffer_type*
            rdbuf( ) const
            {
                return m_buffer.get( );
            }

            CheckSumFilter* GetCheckSumFile( ) const;

            void SetCheckSumFile( const CheckSum::kind_type Type );

            CheckSumFilter* GetCheckSumFrame( ) const;

            void SetCheckSumFrame( const CheckSum::kind_type Type );

            CheckSumFilter* GetCheckSumObject( ) const;

            void SetCheckSumObject( const CheckSum::kind_type Type );

        protected:
            typedef FrameSpec::ObjectInterface::unique_object_type
                unique_object_type;

            void setFrHeader( unique_object_type& Obj );

            //-----------------------------------------------------------------
            /// \brief Establish if the buffer is to be released with the Stream
            ///
            /// \param[in] Value
            ///     If true, then the buffer will be released with the
            ///     destruction of this instance.
            ///     If false, then the buffer will exist even after the
            ///     destruction of this instance.
            //-----------------------------------------------------------------
            void setAutoDeleteBuffer( const bool Value );

        private:
            typedef std::unique_ptr< buffer_type > buffer_ptr_type;
            typedef std::list< object_type >       object_queue_type;

            unique_object_type          m_file_header;
            buffer_ptr_type             m_buffer;
            bool                        m_buffer_auto_delete;
            bool                        m_filter_internally;
            object_queue_type           m_write_objects;
            object_queue_type::iterator m_write_objects_pos;
            INT_2U                      m_compression_scheme;
            INT_2U                      m_compression_level;

            template < typename T >
            const FrameSpec::Object* object_ptr( boost::shared_ptr< T > Obj );

            template < typename T >
            const FrameSpec::Object* object_ptr( const T* Obj );
        };

        //-------------------------------------------------------------------
        //-------------------------------------------------------------------

        inline OStream::Pointer::Pointer( object_type Data ) : m_pointer( Data )
        {
        }

        inline OStream::object_type
        OStream::Pointer::GetPointer( ) const
        {
            return m_pointer;
        }

        //-------------------------------------------------------------------
        //-------------------------------------------------------------------

        inline OStream::OStream( buffer_type* Buffer, bool AutoDelete )
            : std::ostream( dynamic_cast< std::streambuf* >( Buffer ) ),
              m_buffer( Buffer ), m_buffer_auto_delete( AutoDelete ),
              m_compression_scheme( 0 ), m_compression_level( 0 )
        {
            if ( Buffer )
            {
                m_filter_internally = Buffer->FilterInternally( );
            }
            m_write_objects_pos = m_write_objects.begin( );
        }

        inline OStream::~OStream( )
        {
            ostream_type::flush( );
            if ( m_buffer_auto_delete == false )
            {
                m_buffer.release( );
            }
            else
            {
                delete m_buffer.release( );
            }
        }

        inline void
        OStream::Compression( INT_2U& CompressionScheme,
                              INT_2U& CompressionLevel )
        {
            const INT_2U old_scheme( m_compression_scheme );
            const INT_2U old_level( m_compression_level );

            m_compression_scheme = CompressionScheme;
            m_compression_level = CompressionLevel;

            CompressionScheme = old_scheme;
            CompressionLevel = old_level;
        }

        inline INT_2U
        OStream::CompressionScheme( ) const
        {
            return m_compression_scheme;
        }

        inline INT_2U
        OStream::CompressionLevel( ) const
        {
            return m_compression_level;
        }

        inline CheckSumFilter*
        OStream::GetCheckSumFile( ) const
        {
            return m_file_checksum.get( );
        }

        inline void
        OStream::SetCheckSumFile( const CheckSum::kind_type Type )
        {
            if ( m_file_checksum.get( ) )
            {
                rdbuf( )->FilterRemove( m_file_checksum.get( ) );
            }
            if ( Type == CheckSum::NONE )
            {
                m_file_checksum.reset( (CheckSumFilter*)NULL );
            }
            else
            {
                m_file_checksum.reset( new CheckSumFilter( Type ) );
                rdbuf( )->FilterAdd( m_file_checksum.get( ) );
            }
        }

        inline CheckSumFilter*
        OStream::GetCheckSumFrame( ) const
        {
            return m_frame_checksum.get( );
        }

        inline void
        OStream::SetCheckSumFrame( const CheckSum::kind_type Type )
        {
            if ( m_frame_checksum.get( ) )
            {
                rdbuf( )->FilterRemove( m_frame_checksum.get( ) );
            }
            if ( Type == CheckSum::NONE )
            {
                m_frame_checksum.reset( (CheckSumFilter*)NULL );
            }
            else
            {
                m_frame_checksum.reset( new CheckSumFilter( Type ) );
                rdbuf( )->FilterAdd( m_frame_checksum.get( ) );
            }
        }

        inline CheckSumFilter*
        OStream::GetCheckSumObject( ) const
        {
            return m_obj_checksum.get( );
        }

        inline void
        OStream::SetCheckSumObject( const CheckSum::kind_type Type )
        {
            if ( m_obj_checksum.get( ) )
            {
                rdbuf( )->FilterRemove( m_obj_checksum.get( ) );
            }
            if ( Type == CheckSum::NONE )
            {
                m_obj_checksum.reset( (CheckSumFilter*)NULL );
            }
            else
            {
                m_obj_checksum.reset( new CheckSumFilter( Type ) );
                rdbuf( )->FilterAdd( m_obj_checksum.get( ) );
            }
        }

        template < typename Header >
        inline const Header*
        OStream::GetFrHeader( ) const
        {
            return dynamic_cast< const Header* >( m_file_header.get( ) );
        }

        inline OStream&
        OStream::write( const char_type* S, std::streamsize N )
        {
            if ( !m_filter_internally )
            {
                m_buffer->FilterBuffer( S, S + N );
            }
            ostream_type::write( S, N );
            return *this;
        }

        //-------------------------------------------------------------------
        /// This method retieves the next object to be written along with
        ///  information indicating if the object should be deallocated
        ///  once written.
        //-------------------------------------------------------------------
        inline OStream::object_type
        OStream::Pop( )
        {
            object_type retval;

            //-----------------------------------------------------------------
            // Check if there is anything to be done
            //-----------------------------------------------------------------

            if ( m_write_objects.empty( ) == false )
            {
                //---------------------------------------------------------------
                // Always take from the front of the list
                //---------------------------------------------------------------

                retval = m_write_objects.front( );

                //---------------------------------------------------------------
                // Remove the information from the list and reset the insertion
                //  iterator.
                //---------------------------------------------------------------

                m_write_objects_pos =
                    m_write_objects.erase( m_write_objects.begin( ) );
            }

            return retval;
        }

        //-------------------------------------------------------------------
        /// This method adds an object to the queue of objects to be written.
        /// It preserves the order in which the objects should be written
        ///  to the stream by keeping a local iterator indicating the point
        ///  of insertion.
        //-------------------------------------------------------------------
        inline void
        OStream::PushSingle( object_type Obj )
        {
            if ( ( Obj ) && ( !m_dictionary.Ref( Obj ) ) )
            {
                m_dictionary.RefCreate( Obj, *this );
                // Ensure a valid value when starting
                if ( m_write_objects.size( ) == 0 )
                {
                    m_write_objects_pos = m_write_objects.begin( );
                }
                // Insert the information into the queue
                m_write_objects_pos =
                    m_write_objects.insert( m_write_objects_pos, Obj );
                // Advance the iterator to just past the object inserted.
                ++m_write_objects_pos;
            }
        }

        inline OStream&
        OStream::operator<<( object_type Data )
        {
            PushSingle( Data );
            const PTR_STRUCT_BASE& ptr( Reference( Data ) );
            ptr.Write( *this );
            return *this;
        }

        inline OStream&
        OStream::operator<<( Pointer Data )
        {
            PushSingle( Data.GetPointer( ) );
            const PTR_STRUCT_BASE& ptr( Reference( Data.GetPointer( ) ) );
            ptr.Write( *this );
            return *this;
        }

        template <>
        inline OStream&
        OStream::operator<<( const LDASTools::AL::GPSTime& Data )
        {
            *this << Data.GetSeconds( ) << Data.GetNanoseconds( );
            return *this;
        }

        template < typename DT >
        inline OStream&
        OStream::operator<<( const std::vector< DT >& Data )
        {
            if ( Data.size( ) > 0 )
            {
                return write(
                    reinterpret_cast< const char_type* >( &( Data[ 0 ] ) ),
                    sizeof( DT ) * Data.size( ) );
            }
            return *this;
        }

        template < typename DT >
        inline OStream&
        OStream::operator<<( const DT& Data )
        {
            return write( reinterpret_cast< const char_type* >( &Data ),
                          sizeof( Data ) );
        }

        inline INT_4U
        OStream::GetNumberOfFrames( ) const
        {
            return 0;
        }

        inline void
        OStream::setFrHeader( unique_object_type& Obj )
        {
            m_file_header.reset( Obj.release( ) );
        }

        inline void
        OStream::setAutoDeleteBuffer( const bool Value )
        {
            m_buffer_auto_delete = Value;
        }

        template < typename T >
        inline const FrameSpec::Object*
        OStream::object_ptr( typename boost::shared_ptr< T > Obj )
        {
            return Obj.get( );
        }

        template <>
        inline const FrameSpec::Object*
        OStream::object_ptr< FrStatData >( const FrStatData* Obj )
        {
            return reinterpret_cast< const FrameSpec::Object* >( Obj );
        }
    } // namespace Common
} // namespace FrameCPP

#endif /* FrameCPP__COMMON__IOStream_HH */
