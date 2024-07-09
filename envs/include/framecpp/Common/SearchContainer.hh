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

/* -*- mode: C++; c-basic-offset: 2; -*- */
#ifndef FRAME_CPP__COMMON__SearchContainer_HH
#define FRAME_CPP__COMMON__SearchContainer_HH

#if !defined( SWIGIMPORTED )
#include <sstream>
#endif /* ! defined(SWIGIMPORTED) */

#include "ldastoolsal/unordered_map.hh"
#include "ldastoolsal/regexmatch.hh"
#include "ldastoolsal/ldasexception.hh"
#include "ldastoolsal/util.hh"

#include "framecpp/Common/FrameSpec.hh"
#include "framecpp/Common/Container.hh"

namespace FrameCPP
{
    namespace Common
    {

        //-------------------------------------------------------------------
        ///
        /// \brief A searchable container.
        ///
        /// The SearchContainer class allows the user to find an element in the
        /// class based upon an attribute of the contained object.  For this
        /// class, there are two template parameters:
        ///
        /// \tparam T
        ///     The type of object to store.
        /// \tparam F
        ///      A constant method of class T returning a const string&.
        ///      This is used to supply the attribute to query on.
        ///
        // <p>For example, a container holding AdcData objects which searched on
        // the name field would be declared as:
        //
        // <p><code>SearchContainer< AdcData, &AdcData::getName ></code>
        //
        // <p>The SearchContainer class adds 3 ways to search for a contained
        // object:
        //
        // <ol>
        //   <li>Exact match - This is implemented via the find methods.  This
        //       iterates through a container until an exact match is found. The
        //       user may specify the starting location for the search.</li>
        //   <li>Regex match - This is implemented via regexFind.</li>
        //   <li>Hashed search - If the user would like to use a hash to find
        //   objects
        //       in the container, then they can use the hashFind method.  After
        //       a change to the container which would modify an element's key
        //       the user must manually 'rehash' the container.</li>
        // </ol>
        //
        /// \todo Should this be an adaptor class?
        //
        template < class T, const std::string& ( T::*F )( ) const >
        class SearchContainer : public Container< T >
        {
        public:
            /* typedef's */
            typedef typename Container< T >::value_type       value_type;
            typedef typename Container< T >::const_value_type const_value_type;

            typedef typename Container< T >::iterator         iterator;
            typedef typename Container< T >::const_iterator   const_iterator;
            typedef typename Container< T >::reverse_iterator reverse_iterator;
            typedef typename Container< T >::const_reverse_iterator
                const_reverse_iterator;

            typedef typename LDASTools::AL::unordered_multimap<
                std::string,
                value_type,
                LDASTools::AL::hash< std::string >,
                LDASTools::AL::CaseInsensitiveCmp >
                hash_type;

            typedef typename hash_type::const_iterator const_hash_iterator;
            typedef typename hash_type::iterator       hash_iterator;

            /* Constructors / Destructor */
            //-------------------------------------------------------------------
            ///
            /// \brief Default Constructor.
            ///
            /// \param[in] AllowDuplicates
            ///     True if duplicates are allowed in the set
            SearchContainer( bool AllowDuplicates = true );

            //-------------------------------------------------------------------
            ///
            /// \brief Copy Constructor.
            ///
            /// \param[in] sc
            ///     Search container to be copied.
            //
            SearchContainer( const SearchContainer< T, F >& sc );

            //-------------------------------------------------------------------
            ///
            /// \brief Destructor
            virtual ~SearchContainer( );

            /* Operator Overloads */

            //-------------------------------------------------------------------
            ///
            /// \brief Assignment Operator.
            ///
            /// \param[in] sc
            ///     Search container to be assigned.
            ///
            /// \return
            ///     "this" search container.
            //
            const SearchContainer< T, F >&
            operator=( const SearchContainer< T, F >& sc );

            bool AllowDuplicates( ) const;

#if 0
          //-------------------------------------------------------------
          /// \brief Concatenate search containers.
          ///
          /// \param[in] sc
          ///   Search contaier to be concatenated.
          ///
          /// \return
          ///   "this" search container.
          ///
          /// \exception std::bad_alloc
          ///   Memory allocation failed.
          /// \exception frame_mismatch
          ///   `T' mismatch.
          //-------------------------------------------------------------
          const SearchContainer< T, F >&
          operator+=( const SearchContainer< T, F >& sc );
#endif

            /* Accessors */
            //-------------------------------------------------------------------
            ///
            /// \brief Finds an element with the given name.
            ///
            /// \param[in] name
            ///     Name to search for.
            ///
            /// \return
            ///     Iterator pointing to first element found.
            const_iterator find( const std::string& name ) const;

            //-------------------------------------------------------------------
            ///
            /// \brief Finds an element with the given name.
            ///
            /// \param[in] name
            ///     Name to search for.
            /// \param[in] start
            ///     Starting position.
            ///
            /// \return
            ///     Constant iterator pointing to first element found.
            const_iterator find( const std::string& name,
                                 const_iterator     start ) const;

            //-------------------------------------------------------------------
            ///
            /// \brief Finds an element with the given name.
            ///
            /// \param[in] name
            ///     Name to search for.
            ///
            /// \return
            ///     Iterator pointing to first element found.
            ///
            iterator find( const std::string& name );

            //-------------------------------------------------------------------
            //
            /// \brief Finds an element with the given name.
            //
            /// \param[in] name
            ///     Name to search for.
            /// \param[in] start
            ///     Where to begin search.
            //
            /// \return
            ///     Iterator pointing to first element found.
            iterator find( const std::string& name, iterator start );

            //-------------------------------------------------------------------
            ///
            /// \brief Finds an element with a name matching the given regex.
            ///
            /// \param[in] regex
            ///     Regular expression to search for.
            ///
            /// \return
            ///     Iterator pointing to first element found.
            const_iterator regexFind( const std::string& regex ) const;

            //-------------------------------------------------------------------
            ///
            /// \brief Finds an element with a name matching the given regex.
            ///
            /// \param[in] regex
            ///     Regular expression to search for.
            /// \param[in] start
            ///     Where to begin search.
            ///
            /// \return
            ///     Iterator pointing to first element found.
            const_iterator regexFind( const std::string& regex,
                                      const_iterator     start ) const;

            //-------------------------------------------------------------------
            ///
            /// \brief Finds an element with a name matching the given regex.
            ///
            /// \param[in] regex
            ///     Regular expression to search for.
            ///
            /// \return
            ///     Iteartor poiting to the element found.
            iterator regexFind( const std::string& regex );

            //-------------------------------------------------------------------
            ///
            /// \brief Finds an element with a name matching the given regex.
            ///
            /// \param[in] regex
            ///     Regular expression to search for.
            /// \param[in] start
            ///     Where to begin search.
            ///
            /// \return iterator
            ///     Iteartor poiting to the element found.
            iterator regexFind( const std::string& regex, iterator start );

            //-------------------------------------------------------------------
            ///
            /// \brief Finds an element with the given name via a hash.
            ///
            /// \param[in] name
            ///     The name to search for.
            ///
            /// \return
            ///     Iterator range for the elements found.
            std::pair< const_hash_iterator, const_hash_iterator >
            hashFind( const std::string& name ) const;

            //-------------------------------------------------------------------
            ///
            /// \brief Finds an element with a the given name via a hash.
            ///
            /// \param[in] name
            ///    The name to search for.
            ///
            /// \return
            ///    Iterator range for the elements found.
            std::pair< hash_iterator, hash_iterator >
            hashFind( const std::string& name );

            /* Mutators */
            //-------------------------------------------------------------------
            ///
            /// \brief Rehash search container.
            void rehash( ) const;

            //-------------------------------------------------------------------
            ///
            /// \brief Append an item to the container.
            ///
            /// \param[in] data
            ///    An element to append.
            ///
            /// \return
            ///    The iterator correspinding to the appended object.
            iterator
            append( value_type data )
            {
                const std::string k( ( data.get( )->*F )( ) );

                if ( ( !mAllowDuplicates ) &&
                     ( mHash.find( k ) != mHash.end( ) ) )
                {
                    std::ostringstream oss;

                    oss << "Inserting non-unique key: " << k << " into list of "
                        << mHash.size( ) << " element(s)";
                    throw std::logic_error( oss.str( ) );
                }
                iterator iter = Container< T >::append( data );

                mHash.insert( make_pair( k, *iter ) );
                return iter;
            }

            iterator
            append( const T& data )
            {
                const std::string k( ( data.*F )( ) );

                if ( ( !mAllowDuplicates ) &&
                     ( mHash.find( k ) != mHash.end( ) ) )
                {
                    std::ostringstream oss;

                    oss << "Inserting non-unique key: " << k;
                    throw std::logic_error( oss.str( ) );
                }
                iterator iter = Container< T >::append( data );

                mHash.insert( make_pair( k, *iter ) );

                return iter;
            }

            //-------------------------------------------------------------------
            /// \brief Insert an item into the container.
            ///
            /// \param[in] pos
            ///     An iterator pointing to the location where the
            ///     element should be added.
            /// \param[in] data
            ///     The item to add.
            ///
            /// \return
            ///     An iterator pointing to the added item.
            ///
            /// \exception std::bad_alloc
            ///     Memory could not be allocated for the element.
            ///
            iterator
            insert( iterator pos, value_type data )
            {
                iterator iter = Container< T >::insert( pos, data );
                mHash.insert( make_pair( ( ( *iter )->*F )( ), *iter ) );
                return iter;
            }

            //-------------------------------------------------------------------
            ///
            /// \brief Insert an item into the container.
            ///
            /// \param[in] index
            ///    The index at which the element should be added.  If
            ///    the index is out of range then the element will be inserted
            ///    at the end.
            /// \param[in] data
            ///     The item to add.
            ///
            /// \return iterator
            ///     An iterator pointing to the added item.
            iterator
            insert( size_t index, const T& data )
            {
                iterator iter = Container< T >::insert( index, data );
                mHash.insert( make_pair( ( ( *iter )->*F )( ), *iter ) );
                return iter;
            }

#if 0
      //-------------------------------------------------------------------
      ///
      /// \brief Insert an item into the container.
      ///
      /// \param[in] index
      ///     The index at which the element should be added.
      ///     If the index is out of range then the element will be
      ///     inserted at the end.
      /// \param[in] data
      ///     The item to add.
      //
      /// \return
      ///     An iterator pointing to the added item.
      iterator insert( size_t index, const T* data );

      //-------------------------------------------------------------------
      ///
      /// \brief Insert an item into the container.
      ///
      /// \param[in] index
      ///     The index at which the element should be added.
      ///     If the index is out of range then the element will be
      ///     inserted at the end.
      /// \param[in] data
      ///     The item to add.
      /// \param[in] allocate
      ///     Duplicate "data" or not (default: true).
      /// \param[in] owns
      ///     Will destruct "data" when destructed or not (default: true).
      ///
      /// \return iterator
      ///     An iterator pointing to the added item.
      iterator insert( size_t index, T* data, bool allocate = true,
		       bool owns = true );
#endif /* 0 */

            //-------------------------------------------------------------------
            ///
            /// \brief Remove an element from the container.
            ///
            /// If the element is owned, then it will be destructed.
            ///
            /// \param[in] index
            ///     which element to erase.
            void erase( unsigned int index );

            //-------------------------------------------------------------------
            ///
            /// \brief Remove a sequence of elements from the container.
            ///
            /// All owned elements in sequence will be destructed.
            ///
            /// \param[in] start
            ///     Sequence beginning.
            /// \param[in] finish
            ///     Sequence end.
            void erase( iterator start, iterator finish );

            SearchContainer< T, F >&
            Merge( const SearchContainer< T, F >& RHS );

        private:
            /// \brief Element hash.
            mutable hash_type mHash;
            bool              mAllowDuplicates;

            inline const std::string&
            key( const_iterator i ) const
            {
                return ( i->get( )->*F )( );
            }
        };

        template < class T, const std::string& ( T::*F )( ) const >
        inline typename SearchContainer< T, F >::const_iterator
        SearchContainer< T, F >::find( const std::string& name ) const
        {
            return find( name, this->begin( ) );
        }

        template < class T, const std::string& ( T::*F )( ) const >
        inline typename SearchContainer< T, F >::iterator
        SearchContainer< T, F >::find( const std::string& name )
        {
            return find( name, this->begin( ) );
        }

        template < class T, const std::string& ( T::*F )( ) const >
        inline typename SearchContainer< T, F >::const_iterator
        SearchContainer< T, F >::regexFind( const std::string& regex ) const
        {
            return regexFind( regex, this->begin( ) );
        }

        template < class T, const std::string& ( T::*F )( ) const >
        inline typename SearchContainer< T, F >::iterator
        SearchContainer< T, F >::regexFind( const std::string& regex )
        {
            return regexFind( regex, this->begin( ) );
        }
    } // namespace Common
} // namespace FrameCPP

#include "framecpp/Common/SearchContainer.tcc"

#endif // FRAME_CPP__COMMON__SearchContainer_HH
