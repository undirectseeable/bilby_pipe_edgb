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

#ifndef FrameCPP__Common__Container_HH
#define FrameCPP__Common__Container_HH

#if !defined( SWIGIMPORTED )
#include <vector>
#include <stdexcept>
#include <string>

#include <boost/shared_ptr.hpp>

#include "framecpp/Common/IOStream.hh"

#endif /* ! defined(SWIGIMPORTED) */

namespace FrameCPP
{
    namespace Common
    {
        class IStream;
        class OStream;

        //-------------------------------------------------------------------
        ///
        /// \brief Container for Frame objects
        ///
        /// This allows for storage of data members of the frame
        /// specification.
        /// The container stores the members as smart pointers.
        ///
        //-------------------------------------------------------------------
        template < class T >
        class Container : public std::vector< boost::shared_ptr< T > >
        {
        public:
            /* Typedef's */
            typedef typename boost::shared_ptr< T >       value_type;
            typedef typename boost::shared_ptr< T > const const_value_type;

            typedef typename std::vector< value_type > container_base_type;

            typedef typename container_base_type::size_type size_type;

            typedef typename container_base_type::iterator       iterator;
            typedef typename container_base_type::const_iterator const_iterator;
            typedef
                typename container_base_type::reverse_iterator reverse_iterator;
            typedef typename container_base_type::const_reverse_iterator
                const_reverse_iterator;

#if !defined( SWIGIMPORTED )
            using container_base_type::begin;
            using container_base_type::end;
            using container_base_type::rbegin;
            using container_base_type::rend;
            using container_base_type::size;

            using container_base_type::push_back;
#endif /* ! defined(SWIGIMPORTED) */

#if !defined( SWIG )
#if 0
      /* Constructors, Destructor */
      //-------------------------------------------------------------------
      ///
      /// \brief Default constructor.
      ///
      /// This just creates an empty container.
      Container();

      //-------------------------------------------------------------------
      //
      /// \brief Container copy constructor.
      ///
      /// This is the copy constructor for this class.  It iterates through source
      /// container, copying its objects into this container.  The manner in which it
      /// copies the elements depends upon their ownership in the source container.
      ///
      /// If the source container owns the element, then a copy of that element is
      /// made and inserted into the new container.  The new container now owns that
      /// element.
      ///
      /// If the source container does not own the element, then the pointer to the
      /// element is inserted into the new container.  A copy is not made, therefore
      /// the new container does NOT own the element.
      ///
      /// In Summary, we have:
      ///
      /// <pre>
      ///   source                                     dest
      ///   ownership      copy method                 ownership
      ///   ---------      -----------                 ---------
      ///   owned     ---> allocate copy          ---> owned
      ///   unowned   ---> assign current pointer ---> unowned
      /// </pre>
      ///
      /// \param[in] c
      ///     The container to copy from
      Container( const Container< T >& c );

      //-------------------------------------------------------------------
      ///
      /// \brief Destructor.
      ///
      /// This deletes all of the owned objects in the container.
      virtual ~Container();

      /* Operator Overloads */
      //-------------------------------------------------------------------
      ///
      /// \brief Assignment operator.
      ///
      /// This copies another container to this one.  Ownership is handled in the same
      /// manner as in the copy constructor.
      ///
      /// \param[in] c
      ///     The container to assign from.
      ///
      /// \return
      ///     This container.
      const Container< T >& operator=( const Container< T >& c );
 
      //-------------------------------------------------------------------
      ///
      /// \brief Increment operator.
      ///
      /// This concatenates another container to this one.  
      ///
      /// \param[in] c
      ///     The container to assign from.
      ///
      /// \return
      ///     This container.
      const Container< T >& operator+=( const Container< T >& c );
#endif /* 0 */

            //-------------------------------------------------------------------
            ///
            /// \brief Equality operator.
            ///
            /// \param[in] c
            ///     The container to compare with.
            ///
            /// \return
            ///     true if the containers are equal.
            bool operator==( const Container< T >& c ) const;

            //-------------------------------------------------------------------
            ///
            /// \brief Inequality operator.
            ///
            /// \param[in] c
            ///     The container to compare with.
            ///
            /// \return
            ///     true if the containers are not equal.
            bool operator!=( const Container< T >& c ) const;

#if 0
      //-------------------------------------------------------------------
      //
      // Array access operator.
      //
      // This returns the element at the specified index or a null pointer if the
      // index is out-of-range.
      //
      /// \param[in] size_t index - The index of the desired element.
      //
      /// \return T* -- A pointer to the object stored at the index.
      /// \return T* -- A constant pointer to the object stored at the index.
      //
      //!exc: None.
      //
      virtual value_type operator[]( size_type index )
      {
	range_check( index );
	return mData[ index ];
      }

      //-------------------------------------------------------------------
      //
      // Array access operator.
      //
      // This returns the element at the specified index or a null pointer if the
      // index is out-of-range.
      //
      /// \param[in] size_t index - The index of the desired element.
      //
      /// \return const T* -- A constant pointer to the object stored at the index.
      //
      //!exc: None.
      //
      virtual const_value_type operator[]( size_type index ) const
      {
	range_check( index );
	return const_value_type( mData[ index ] );
      }
    
      /* Accessors */
      //-------------------------------------------------------------------
      //
      /// \brief Returns the size of the container.
      //
      /// \return size_t -- The number of objects in the container.
      //
      //!exc: None.
      //
      virtual size_type size() const
      {
	return mData.size( );
      }

      //-------------------------------------------------------------------
      //
      /// \brief Returns the first item in the container.
      //
      /// \return T* -- First item.
      //
      //!exc: None.
      //
      value_type front()
      {
	return mData.front( );
      }

      //-------------------------------------------------------------------
      //
      /// \brief Returns the first item in the container.
      //
      /// \return const T* -- First item.
      //
      //!exc: None.
      //
      const_value_type front() const
      {
	return const_value_type( mData.front( ) );
      }

      //-------------------------------------------------------------------
      //
      /// \brief Returns the last item in the container.
      //
      /// \return T* -- Last item.
      //
      //!exc: None.
      //
      value_type back( )
      {
	return mData.back( );
      }

      //-------------------------------------------------------------------
      //
      /// \brief Returns the last item in the container.
      //
      /// \return const T* -- Last item.
      //
      //!exc: None.
      //
      const_value_type back() const
      {
	return const_value_type( mData.back( ) );
      }

      //-------------------------------------------------------------------
      //
      /// \brief Returns an iterator at the beginning of the container.
      //
      /// \return Container< T >::iterator -- Beginning iterator.
      //
      //!exc: None.
      //
      iterator begin( )
      {
	return mData.begin( );
      }

      reverse_iterator rbegin()
      {
	return mData.rbegin( );
      }

      //-------------------------------------------------------------------
      //
      /// \brief Returns an iterator at the beginning of the container.
      //
      /// \return Container< T >::const_iterator -- Beginning iterator.
      //
      //!exc: None.
      //
      const_iterator begin() const
      {
	return mData.begin( );
      }

      const_reverse_iterator rbegin() const
      {
	return mData.rbegin( );
      }


      //-------------------------------------------------------------------
      //
      /// \brief Returns an iterator at the end of the container.
      //
      /// \return Container< T >::iterator -- End iterator.
      //
      //!exc: None.
      //
      iterator end( )
      {
	return mData.end( );
      }

      reverse_iterator rend( )
      {
	return mData.rend( );
      }

      //-------------------------------------------------------------------
      //
      /// \brief Returns an iterator at the end of the container.
      //
      /// \return Container< T >::const_iterator -- End iterator.
      //
      //!exc: None.
      //
      const_iterator end( ) const
      {
	return mData.end( );
      }

      const_reverse_iterator rend( ) const
      {
	return mData.rend( );
      }
#endif /* 0 */
#endif /* SWIG */

            /* Mutators */
            //-------------------------------------------------------------------
            ///
            /// \brief Append an element to the end of the container.
            ///
            /// Memory for the element will be allocated and the container will
            /// own the new element.
            ///
            /// \param[in] data
            ///     The item to append.
            ///
            /// \return
            ///     The iterator correspinding to the appended object.
            iterator
            append( value_type data )
            {
                push_back( data );

                return this->end( ) - 1;
            }

            iterator
            append( const T& data )
            {
                value_type v( new T( data ) );
                push_back( v );

                return this->end( ) - 1;
            }

#if 0
#if !defined( SWIG )
    
      //-------------------------------------------------------------------
      //
      /// \brief Reset to size zero being careful to reclaim resources
      //
      //!exc: None.
      //   
      void clear( );
    
      //-------------------------------------------------------------------
      //
      /// \brief Insert an element into the container.
      //
      // The element will be copied and the container will own the new element.
      //
      /// \param[in] iterator iter - An iterator pointing to the location where the
      //+     element should be added.
      /// \param[in] const T& data - The item to add.
      //
      /// \return iterator -- An iterator pointing to the added item.
      //
      //!exc: std::bad_alloc - Memory could not be allocated for the element.
      //
      iterator insert( iterator iter, value_type data )
      {
	return mData.insert( iter, data );
      }

      //-------------------------------------------------------------------
      //
      /// \brief Insert an element into the container.
      //
      // The element will be copied and the container will own the new element.
      //
      /// \param[in] size_t index - The index at which the element should be added.  If
      //+     the index is out of range then the element will be inserted at the end.
      /// \param[in] const T& data - The item to add.
      //
      /// \return iterator -- An iterator pointing to the added item.
      //
      //!exc: std::bad_alloc - Memory could not be allocated for the element.
      //
      iterator insert( size_t index, value_type data )
      {
	if ( index >= mData.size() )
	{
	  return mData.insert( mData.end(), data );
	}

	return mData.insert( mData.begin() + index, data );
      }


      //-------------------------------------------------------------------
      //
      /// \brief Erase an element.
      //
      // This erases an element at the specified index.  If the index is out of range
      // then nothing happens.
      //
      /// \param[in] unsigned int index - Element index.
      //
      //!exc: None.
      //
      void erase( size_type index );

      //-------------------------------------------------------------------
      //
      /// \brief Erases a range of elements.
      //
      // If end is less thatn start or any of the iterators are out of range
      // then nothing will happen.
      //
      /// \param[in] iterator start - Range start.
      /// \param[in] iterator finish - Range end.
      //
      //!exc: None.
      //   
      void erase( iterator start, iterator finish );
#endif /* SWIG */
#endif /* 0 */

            IStream& StreamIn( IStream& Stream );

            OStream& StreamOut( OStream& Stream ) const;

#if 0
#if !defined( SWIG )
    protected:
      inline void range_check( size_type index ) const
      {
	if ( index < mData.size( ) )
	{
	  return;
	}
	throw std::range_error( "" );
      }

    private:

      /// \brief Contained objects.
      container_type	 mData;

#endif /* ! defined( SWIG ) */
#endif /* 0 */
        };

#if 0
#if !defined( SWIG )
    //-------------------------------------------------------------------
    //
    /// \brief Default constructor.
    //
    // This just creates an empty container.
    //
    //!exc: None.
    //   
    template< class T >
    Container< T >::Container()
      : mData()
    {
    }


    //-------------------------------------------------------------------
    //
    /// \brief Container copy constructor.
    //
    // This is the copy constructor for this class.  It iterates through source
    // container, copying its objects into this container.  The manner in which it
    // copies the elements depends upon their ownership in the source container.
    //
    // If the source container owns the element, then a copy of that element is
    // made and inserted into the new container.  The new container now owns that
    // element.
    //
    // If the source container does not own the element, then the pointer to the
    // element is inserted into the new container.  A copy is not made, therefore
    // the new container does NOT own the element.
    //
    // In Summary, we have:
    //
    // <pre>
    //   source                                     dest
    //   ownership      copy method                 ownership
    //   ---------      -----------                 ---------
    //   owned     ---> allocate copy          ---> owned
    //   unowned   ---> assign current pointer ---> unowned
    // </pre>
    //
    /// \param[in] const Container< T >& c - The container to copy from
    //
    //!exc: std::bad_alloc - Memory allocation failed.
    //
    template< class T >
    Container< T >::
    Container( const Container< T >& c )
      : mData( c.mData )
    {
    }


    //-------------------------------------------------------------------
    //
    /// \brief Destructor.
    //
    // This deletes all of the owned objects in the container.
    //
    //!exc: None.
    //      
    template< class T >
    Container< T >::
    ~Container()
    {
    }
#endif /* ! defined( SWIG ) */
#endif /* 0 */

        template < class T >
        IStream&
        Container< T >::StreamIn( IStream& Stream )
        {
            //-----------------------------------------------------------------
            // :TODO: Place into dictionary so the container can be
            // :TODO:   reconstructed once all the pieces have been read.
            //-----------------------------------------------------------------

            Stream.PushRef( *this );

            //-----------------------------------------------------------------
            // Return back to the caller
            //-----------------------------------------------------------------
            return Stream;
        }

        template < class T >
        OStream&
        Container< T >::StreamOut( OStream& Stream ) const
        {
            //-----------------------------------------------------------------
            // Push objects onto the writing stack and make associations to
            //  create link list in the stream
            //-----------------------------------------------------------------
            if ( this->size( ) > 0 )
            {
                Stream.PushMulti( this->begin( ), this->end( ), this->size( ) );
            }

            //-----------------------------------------------------------------
            // Write the first element to the stream
            //-----------------------------------------------------------------
            const PTR_STRUCT_BASE& ptr_struct = ( this->size( ) == 0 )
                ? Stream.Reference( OStream::object_type( ) )
                : Stream.Reference( this->front( ) );

            //-----------------------------------------------------------------
            // Write the reference information to the stream
            //-----------------------------------------------------------------
            ptr_struct.Write( Stream );

            return Stream;
        }

#if !defined( SWIG )
#if 0
    //-------------------------------------------------------------------
    // Operator Overloads
    //-------------------------------------------------------------------


    //-------------------------------------------------------------------
    //
    /// \brief Assignment operator.
    //
    // This copies another container to this one.  Ownership is handled in the same
    // manner as in the copy constructor.
    //
    /// \param[in] const Container< T >& c - The container to assign from.
    //
    /// \return const Container< T >& -- This container.
    //
    //!exc: std::bad_alloc - Memory allocation failed.
    //
    template< class T >
    const Container< T >& Container< T >::
    operator=( const Container< T >& c )
    {
      if ( this != &c )
      {
	mData = c.mData;
      }
    
      return *this;
    }

    //-------------------------------------------------------------------
    //
    /// \brief += Assignment operator.
    //
    // This concatenates another container to this one.  
    //
    /// \param[in] const Container< T >& c - The container to assign from.
    //
    /// \return const Container< T >& -- This container.
    //
    //!exc: std::bad_alloc - Memory allocation failed.
    //!exc: frame_mismatch - `T' mismatch.
    //
    template< class T >
    const Container< T >& Container< T >::
    operator+=( const Container< T >& c )
    {
      // Both containers must be of equal size
      //
      if ( size() != c.size() )
      {
	throw std::runtime_error( "Containers have different size" );
      }

      const_iterator iter1, iter2;
      for ( iter1 = begin(),  iter2 = c.begin();
	    iter1 != end() && iter2 != c.end(); ++iter1, ++iter2 )
      {
	**iter1 += **iter2;
      }
      return *this;
    }
#endif /* 0 */

        //-------------------------------------------------------------------
        // This checks to see if two containers containe identical elements.
        template < class T >
        bool
        Container< T >::operator==( const Container< T >& c ) const
        {
            bool equal( this->size( ) == c.size( ) );

            if ( equal )
            {
                for ( const_iterator iter1 = begin( ), iter2 = c.begin( );
                      ( iter1 != end( ) ) && equal;
                      ++iter1, ++iter2 )
                {
                    equal = equal && ( **iter1 == **iter2 );
                }
            }

            return equal;
        }

        //-------------------------------------------------------------------
        /// This chacks to see if two containers do not contain
        /// identical elements.
        template < class T >
        bool
        Container< T >::operator!=( const Container< T >& c ) const
        {
            return !( *this == c );
        }

        //-------------------------------------------------------------------
        // Accessors
        //-------------------------------------------------------------------

        //-------------------------------------------------------------------
        // Mutators
        //-------------------------------------------------------------------

#if 0
    //-------------------------------------------------------------------
    //
    /// \brief Append an element to the end of the container.
    //
    // Memory for the element will be allocated and the container will own the
    // new element.
    //
    /// \param[in] const T* data - The item to append.
    //
    /// \return iterator -- The iterator corresponding to the appended object.
    //
    //!exc: std::bad_alloc - Memory allocation failed.
    //   
    template< class T >
    typename Container< T >::iterator Container< T >::
    append( const T* data )
    {
      mData.push_back( new T( *data ) );
      return end() - 1;
    }


    //-------------------------------------------------------------------
    //
    /// \brief Append an element to the end of the container.
    //
    // The user may also specifiy whether or not memory is allocated for the
    // element (i.e., the element is copied) and if the container owns the element.
    //
    /// \param[in] const T& data - The item to append.
    /// \param[in] bool copy - True if memory should be allocated and the element copied
    //+     into the container (default: true).
    /// \param[in] bool owns - True if the container will own the element (default: true).
    //
    /// \return iterator -- The iterator corresponding to the appended object.
    //
    //!exc: std::bad_alloc - Memory allocation failed.
    //   
    template< class T >
    typename Container< T >::iterator Container< T >::
    append( T* data, bool copy, bool owns )
    {
      if ( copy )
      {
        mData.push_back( new T( *data ) );
      }
      else
      {
        mData.push_back( data );
      }

      return end() - 1;
    }

        
    //-------------------------------------------------------------------
    // Remove everything from within the container in such a way as
    // to reclaim system resources.
    //-------------------------------------------------------------------
    template< class T >
    inline void Container< T >::
    clear( )
    {
      erase( begin( ), end( ) );
    }

    //-------------------------------------------------------------------
    //
    /// \brief Erase an element.
    //
    // This erases an element at the specified index.  If the index is out of range
    // then nothing happens.
    //
    /// \param[in] unsigned int index - Element index.
    //
    //!exc: None.
    //   
    template< class T >
    void Container< T >::
    erase( size_type index )
    {
      if ( index >= mData.size() )
      {
        return;
      }

      // Create the range of one element to erase
      iterator start( begin() );
      std::advance( start, index );
   
      iterator end( start );
      ++end; // point to the next element or to the end()
   
      erase( start, end );
    }


    //-------------------------------------------------------------------
    //
    /// \brief Erases a range of elements.
    //
    // If end is less thatn start or any of the iterators are out of range
    // then nothing will happen.
    //
    /// \param[in] iterator start - Range start.
    /// \param[in] iterator finish - Range end.
    //
    //!exc: None.
    //      
    template< class T >
    void Container< T >::
    erase( iterator start, iterator finish )
    {
      if ( finish < start || start < begin() || finish > end() )
      {
        return;
      }
    
      mData.erase( start, finish );
    }
#endif /* 0 */
#endif /* ! defined( SWIG ) */

    } // namespace Common

} // namespace FrameCPP

#endif // FrameCPP__Common__Container_HH
