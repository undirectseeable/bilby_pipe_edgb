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

#ifndef FrameCPP__Common__Dictionary_HH
#define FrameCPP__Common__Dictionary_HH

#if !defined( SWIGIMPORTED )
#include <map>
#include <iostream>
#include <typeinfo>

#include <boost/shared_ptr.hpp>
#endif /* ! defined(SWIGIMPORTED) */

#include "ldastoolsal/gpstime.hh"
#include "ldastoolsal/unordered_map.hh"

#include "framecpp/Common/FrameSpec.hh"
#include "framecpp/Common/StreamRefInterface.hh"

#define HASH_STREAMREF_BY_ID 1

namespace FrameCPP
{
    namespace Common
    {
        class OStream;
        class OFrameStream;

        //-------------------------------------------------------------------
        /// \brief Keep track of structures written to or read from stream
        //-------------------------------------------------------------------
        class Dictionary
        {
        public:
            typedef FrameSpec::Object*                      object_ptr_type;
            typedef boost::shared_ptr< FrameSpec::Object >  object_type;
            typedef boost::shared_ptr< StreamRefInterface > streamref_type;
            typedef std::pair< StreamRefInterface::class_type,
                               StreamRefInterface::instance_type >
                ptr_struct_key_type;

            Dictionary( );

            ~Dictionary( );

            void Clear( );

            streamref_type Ref( const ptr_struct_key_type& Key ) const;
            object_type    Ref( streamref_type SR ) const;
            streamref_type Ref( object_type Obj ) const;

            void Ref( streamref_type SR, object_type Obj );

            ///----------------------------------------------------------------
            /// \brief Create a reference
            ///
            /// \param[in] Obj
            ///     Object to be referenced.
            /// \param[in] Stream
            ///     Stream to receive the reference.
            ///
            /// \return
            ///     A reference to Obj appropriate for the Stream.
            ///----------------------------------------------------------------
            streamref_type RefCreate( object_type Obj, const OStream& Stream );

            void Remove( const ptr_struct_key_type& Key );

            void Remove( object_type Key );

            void ResetInstanceCounts( );

            void SetInstance( streamref_type StreamRef );

            void Next( object_type Obj, object_type Next );

            object_type Next( object_type Obj ) const;

            object_type Next( const object_type::element_type* Obj ) const;

        private:
            friend class FrameStream;

            typedef const streamref_type::element_type* const_streamref_type;

            struct object_hash
            {
                inline size_t
                operator( )( const object_type Key ) const
                {
                    return reinterpret_cast< size_t >( Key.get( ) );
                }
            };

            struct object_ptr_hash
            {
                inline size_t
                operator( )( const object_ptr_type Key ) const
                {
                    return reinterpret_cast< size_t >( Key );
                }
            };

            struct streamref_hash
            {
                inline size_t
                operator( )( const streamref_type Key ) const
                {
                    return reinterpret_cast< size_t >( Key.get( ) );
                }
            };

#if HASH_STREAMREF_BY_ID
            struct ptr_struct_hash
            {
                inline size_t
                operator( )( const ptr_struct_key_type& Key ) const
                {
#if SIZEOF_SIZE_T == 4
                    size_t retval = size_t( ( Key.first << 24 ) | Key.second );
                    return retval;
#else
                    return ( ( size_t( Key.second ) << 8 ) | Key.first );
#endif
                }

                inline bool
                operator( )( const ptr_struct_key_type& LHS,
                             const ptr_struct_key_type& RHS ) const
                {
                    return ( ( LHS.first == RHS.first ) &&
                             ( LHS.second == RHS.second ) );
                }
            };
#endif /* HASH_STREAMREF_BY_ID */

            typedef LDASTools::AL::
                unordered_map< object_type, streamref_type, object_hash >
                    streamref_container_type;

            typedef LDASTools::AL::
                unordered_map< streamref_type, object_type, streamref_hash >
                    object_container_type;

            typedef LDASTools::AL::unordered_map< FrameSpec::class_type,
                                                  FrameSpec::instance_type >
                instance_count_container_type;

            typedef struct
            {
                object_type cur;
                object_type next;
            } node_type;

            typedef LDASTools::AL::
                unordered_map< object_ptr_type, node_type, object_ptr_hash >
                    next_container_type;

#if HASH_STREAMREF_BY_ID
            typedef LDASTools::AL::unordered_map< ptr_struct_key_type,
                                                  streamref_type,
                                                  ptr_struct_hash,
                                                  ptr_struct_hash >
                streamref_by_id_container_type;
#else
            typedef std::map< ptr_struct_key_type, streamref_type >
                streamref_by_id_container_type;
#endif

            const_streamref_type m_stream_ref;

            streamref_container_type       m_streamref_container;
            object_container_type          m_object_container;
            instance_count_container_type  m_instance_count_container;
            next_container_type            m_next_container;
            streamref_by_id_container_type m_streamref_by_id_container;
        };

        inline void
        Dictionary::Clear( )
        {
            m_instance_count_container.clear( );
            m_streamref_by_id_container.clear( );
            m_object_container.clear( );
            m_streamref_container.clear( );
        }

        inline void
        Dictionary::Next( object_type Obj, object_type Next )
        {
            next_container_type::mapped_type& n =
                m_next_container[ Obj.get( ) ];
            n.cur = Obj;
            n.next = Next;
        }

        inline Dictionary::object_type
        Dictionary::Next( object_type Obj ) const
        {
            object_type retval;

            next_container_type::const_iterator i(
                m_next_container.find( Obj.get( ) ) );

            if ( i != m_next_container.end( ) )
            {
                retval = i->second.next;
            }

            return retval;
        }

        inline Dictionary::object_type
        Dictionary::Next( const object_type::element_type* Obj ) const
        {
            object_type retval;

            next_container_type::const_iterator i( m_next_container.find(
                const_cast< object_type::element_type* >( Obj ) ) );

            if ( i != m_next_container.end( ) )
            {
                retval = i->second.next;
            }

            return retval;
        }

        inline Dictionary::streamref_type
        Dictionary::Ref( const ptr_struct_key_type& Key ) const
        {
            streamref_type                                 retval;
            streamref_by_id_container_type::const_iterator sr =
                m_streamref_by_id_container.find( Key );
            if ( sr != m_streamref_by_id_container.end( ) )
            {
                return retval = sr->second;
            }
            return retval;
        }

        inline Dictionary::object_type
        Dictionary::Ref( streamref_type SR ) const
        {
            object_container_type::const_iterator retval(
                m_object_container.find( SR ) );

            if ( retval == m_object_container.end( ) )
            {
                return object_type( );
            }
            return retval->second;
        }

        inline Dictionary::streamref_type
        Dictionary::Ref( object_type Object ) const
        {
            streamref_container_type::const_iterator retval(
                m_streamref_container.find( Object ) );

            if ( retval == m_streamref_container.end( ) )
            {
                return streamref_type( );
            }
            return retval->second;
        }

        inline void
        Dictionary::Ref( streamref_type SR, object_type Obj )
        {
            //-----------------------------------------------------------------
            if ( SR )
            {
                ptr_struct_key_type p( SR->GetClass( ), SR->GetInstance( ) );

                m_streamref_by_id_container[ p ] = SR;
            }
            //-----------------------------------------------------------------
            // :TODO: Need to handle creating SR if SR is null
            m_streamref_container[ Obj ] = SR;
            m_object_container[ SR ] = Obj;
        }

        //-------------------------------------------------------------------
        /// This method is used for creating a reference that would be
        ///   appropriate for writing to a stream.
        //-------------------------------------------------------------------
        inline Dictionary::streamref_type
        Dictionary::RefCreate( object_type Obj, const OStream& Stream )
        {
            streamref_type retval = Ref( Obj );

            INT_4U c;

            if ( ( !retval ) && ( ( c = Obj->GetClass( ) ) > 0 ) )
            {
                retval.reset( dynamic_cast< streamref_type::element_type* >(
                    m_stream_ref->Clone( ) ) );
                if ( retval )
                {
                    retval->SetClass( c );
                    retval->SetInstance( m_instance_count_container[ c ]++ );
                    Ref( retval, Obj );
                }
            }
            return retval;
        }

        inline void
        Dictionary::Remove( const ptr_struct_key_type& Key )
        {
            streamref_by_id_container_type::iterator sridi(
                m_streamref_by_id_container.find( Key ) );

            if ( sridi == m_streamref_by_id_container.end( ) )
            {
                return;
            }

            object_container_type::const_iterator oci =
                m_object_container.find( sridi->second );
            if ( oci != m_object_container.end( ) )
            {
                m_streamref_container.erase( oci->second );
            }
            m_object_container.erase( sridi->second );
            m_streamref_by_id_container.erase( sridi );
        }

        inline void
        Dictionary::Remove( object_type Key )
        {
            streamref_container_type::iterator srci =
                m_streamref_container.find( Key );
            if ( srci != m_streamref_container.end( ) )
            {
                //----------------------------------------------------------------
                // Remove from secondary lists
                //----------------------------------------------------------------
                if ( srci->second )
                {
                    ptr_struct_key_type p( srci->second->GetClass( ),
                                           srci->second->GetInstance( ) );

                    m_streamref_by_id_container.erase( p );

                    m_object_container.erase( srci->second );
                }

                //----------------------------------------------------------------
                // Take out of list
                //----------------------------------------------------------------
                m_streamref_container.erase( srci );
            }
        }

        inline void
        Dictionary::ResetInstanceCounts( )
        {
            Clear( );
        }
    } // namespace Common
} // namespace FrameCPP
#endif /* FrameCPP__Common__Dictionary_HH */
