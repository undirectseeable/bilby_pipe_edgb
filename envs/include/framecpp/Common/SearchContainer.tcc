//
// LDASTools frameCPP - A library implementing the LIGO/Virgo frame specification
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
#ifndef FRAME_CPP_INTERFACE__SearchContainer_TCC
#define FRAME_CPP_INTERFACE__SearchContainer_TCC

#include "framecpp/Common/IOStream.hh"
#include "framecpp/Common/PTR_STRUCT.hh"

namespace FrameCPP
{
  namespace Common
  {
    //-------------------------------------------------------------------
    // Constructors / Destructor
    //-------------------------------------------------------------------


    //-------------------------------------------------------------------
    ///
    /// \brief Default Constructor.
    template< class T, const std::string& (T::*F)() const >
    SearchContainer< T, F >::
    SearchContainer( bool AllowDuplicates ) 
      : Container< T >( ), mHash(), mAllowDuplicates( AllowDuplicates )
    {
    }


    //-------------------------------------------------------------------
    ///
    /// \brief Copy Constructor.
    ///
    /// \param[in] sc
    ///   Search container to be copied.
    ///
    /// \exeception std::bad_alloc
    ///   Memory allocation failed.
    template< class T, const std::string& (T::*F)() const >
    SearchContainer< T, F >::
    SearchContainer( const SearchContainer< T, F >& sc ) 
      : Container< T >( sc ),
	mHash( sc.mHash ),
	mAllowDuplicates( sc.mAllowDuplicates )
    {
    }
    

    //-------------------------------------------------------------------
    /// \brief Destructor
    template< class T, const std::string& (T::*F)() const >
    SearchContainer< T, F >::
    ~SearchContainer()
    {
    }

    template< class T, const std::string& (T::*F)() const >
    bool SearchContainer< T, F >::
    AllowDuplicates() const
    {
      return mAllowDuplicates;
    }

    //-------------------------------------------------------------------
    // Operator Overloads
    //-------------------------------------------------------------------


    //-------------------------------------------------------------------
    /// \brief Assignment Operator.
    ///
    /// \param[in] sc
    ///   Search container to be assigned.
    ///
    /// \return
    ///   const SearchContainer< T, F >& -- "this" search container.
    ///
    /// \exception std::bad_alloc
    ///   Memory allocation failed.
    //
    template< class T, const std::string& (T::*F)() const >
    const SearchContainer< T, F >&
    SearchContainer< T, F >::
    operator=( const SearchContainer< T, F >& sc )
    {
      if ( this != &sc )
      {
        Container< T >::operator=( sc );
        mHash = sc.mHash;
	mAllowDuplicates = sc.mAllowDuplicates;
      }

      return *this;
    }

#if 0
    //-------------------------------------------------------------------
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
    //
    template< class T, const std::string& (T::*F)() const >
    const SearchContainer< T, F >&
    SearchContainer< T, F >::
    operator+=(
	       const SearchContainer< T, F >& sc )
    {
      // Both containers must be of equal size
      //
      if ( size() != sc.size() )
      {
	throw frame_mismatch( "Containers have different size" );
      }
      sc.rehash();
      for ( const_iterator iter = begin(); iter != end(); ++iter )
      {
	// Find ADC with the same name
	std::pair< const_hash_iterator, const_hash_iterator > p
	  = sc.hashFind( key( iter ) );
	if ( p.first == p.second )
	{
	  throw frame_mismatch( (*iter)->getClassName() + " " + key( iter )
				+ " not found" );
	}
	**iter += *(p.first->second); // Append
      }

      rehash();
      return *this;
    }
#endif



    //-------------------------------------------------------------------
    // Accessors
    //-------------------------------------------------------------------


    //-------------------------------------------------------------------
    /// \brief Finds an element with the given name.
    ///
    /// \param[in] name
    ///   Name to search for.
    /// \param[in] start
    ///   Where to begin search.
    ///
    /// \return
    ///   Iterator pointing to first element found.
    template< class T, const std::string& (T::*F)() const >
    typename SearchContainer< T, F >::const_iterator
    SearchContainer< T, F >::
    find( const std::string& name, const_iterator start ) const
    {
      static LDASTools::AL::CaseInsensitiveCmp cmp;
    
      const_iterator iter( start );
      while( iter != this->end( )
	     && ( ! cmp( key( iter ), name ) ) )
      {
        ++iter;
      }

      return iter;
    }

    //-------------------------------------------------------------------
    /// \brief Finds an element with the given name.
    ///
    /// \param name
    ///   Name to search for.
    /// \param start
    ///   Where to begin search.
    ///
    /// \return
    ///   Iterator pointing to first element found.
    template< class T, const std::string& (T::*F)() const >
    typename SearchContainer< T, F >::iterator
    SearchContainer< T, F >::
    find( const std::string& name, iterator start )
    {
      static LDASTools::AL::CaseInsensitiveCmp cmp;

      iterator iter( start );
      while( iter != this->end( ) && !cmp( key( iter ), name ) )
      {
        ++iter;
      }

      return iter;
    }


    //-------------------------------------------------------------------
    /// \brief Finds an element with a name matching the given regex.
    ///
    /// \param regex
    ///   Regular expression to search for.
    /// \param[in] start
    ///   Where to begin search.
    ///
    /// \return
    ///   Iterator pointing to first element found.
    ///
    /// \exception LdasException
    template< class T, const std::string& (T::*F)() const >
    typename SearchContainer< T, F >::const_iterator
    SearchContainer< T, F >::
    regexFind( const std::string& regex, const_iterator start ) const
    {
      Regex re( regex.c_str(), REG_EXTENDED | REG_ICASE );
      RegexMatch rm( 0 );

      const_iterator iter( start );
      while( iter != this->end( ) )
      {
	const std::string& k( key( iter ) );
	if( rm.match( re, k.c_str() ) == false )
	{
	  ++iter;
	}
	else
	{
	  break;
	}
      }

      return iter;
    }


    //-------------------------------------------------------------------
    /// \brief Finds an element with a name matching the given regex.
    ///
    /// \param[in] regex
    ///   Regular expression to search for.
    /// \param[in] start
    ///   Where to begin search.
    ///
    /// \return
    ///   Iteartor poiting to the element found.
    ///
    /// \exception LdasException
    template< class T, const std::string& (T::*F)() const >
    typename SearchContainer< T, F >::iterator
    SearchContainer< T, F >::
    regexFind( const std::string& regex, iterator start )
    {
      Regex re( regex.c_str(), REG_EXTENDED | REG_ICASE );
      RegexMatch rm( 0 );

      iterator iter( start );
      while( iter != this->end( ) )
      {
        const std::string& k( key( iter ) );
        if( rm.match( re, k.c_str() ) == false )
        {
	  ++iter;
        }
        else
        {
	  break;
        }
      }

      return iter;
    }


    //-------------------------------------------------------------------
    /// \brief Finds an element with the given name via a hash.
    ///
    /// \param[in] name
    ///   The name to search for.
    ///
    /// \return
    ///   Iterator range for the elements found.
    template< class T, const std::string& (T::*F)() const >
    std::pair< typename SearchContainer< T, F >::const_hash_iterator,
	       typename SearchContainer< T, F >::const_hash_iterator >
    SearchContainer< T, F >::
    hashFind( const std::string& name ) const
    {
      return mHash.equal_range( name );
    }

  
    //-------------------------------------------------------------------
    /// \brief: Finds an element with a the given name via a hash.
    ///
    //!param: const std::string& name - The name to search for.
    ///
    /// \return
    ///   Iterator range for the elements found.
    template< class T, const std::string& (T::*F)() const >
    std::pair< typename SearchContainer< T, F >::hash_iterator,
	       typename SearchContainer< T, F >::hash_iterator >
    SearchContainer< T, F >::
    hashFind( const std::string& name )
    {
      return mHash.equal_range( name );
    }



    //-------------------------------------------------------------------
    // Mutators
    //-------------------------------------------------------------------


    //-------------------------------------------------------------------
    /// \brief Rehash search container.
    template< class T, const std::string& (T::*F)() const >
    void SearchContainer< T, F >::
    rehash() const
    {
      mHash.erase( mHash.begin(), mHash.end() );
      for ( const_iterator iter = this->begin(),
	      last = this->end( );
	    iter != last; ++iter )
      {
        mHash.insert( make_pair( key( iter ), *iter ) );
      }
    }

    //-------------------------------------------------------------------
    //
    /// \brief Remove an element from the container.
    ///
    /// If the element is owned, then it will be destructed.
    ///
    /// \param[in] index
    ///   which element to erase.
    template< class T, const std::string& (T::*F)() const >
    void SearchContainer< T, F >::
    erase( unsigned int index )
    {
      if ( index >= this->size( ) )
      {
        return;
      }
    
      // Create the range of one element to erase
      iterator start( this->begin() );
      std::advance( start, index );
   
      iterator end( start );
      ++end; // point to the next element or to the end()
   
      erase( start, end );
    }


    //-------------------------------------------------------------------
    /// \brief Remove a sequence of elements from the container.
    ///
    /// All owned elements in sequence will be destructed.
    ///
    /// \param[in] start
    ///   Sequence beginning.
    /// \param[in] finish
    ///   Sequence end.
    template< class T, const std::string& (T::*F)() const >
    void SearchContainer< T, F >::
    erase( iterator start, iterator finish )
    {
      for ( iterator target = start; target != finish; ++target )
      {
        std::pair< hash_iterator, hash_iterator > matches =
	  mHash.equal_range( key( target ) );
   
        hash_iterator match( matches.first );
        while( match != matches.second &&
               match->second != *target )
        {
	  ++match;
        }

        if ( match == matches.second )
        {
	  rehash();
	  matches = mHash.equal_range( key( target ) );
	  match = matches.first;
   
	  while( match != matches.second &&
		 match->second != *target )
	  {
	    ++match;
	  }
        }

        // Can't erase end(): points to no valid element
        if( match != mHash.end() )
        {
	  mHash.erase( match );
        }
      }

      Container< T >::erase( start, finish );
    }

    template< class T, const std::string& (T::*F)() const >
    SearchContainer< T, F >& SearchContainer< T, F >::
    Merge( const SearchContainer< T, F >& RHS )
    {
      //-----------------------------------------------------------------
      // Merge data between the two
      //-----------------------------------------------------------------
      const const_iterator slast( RHS.end( ) );
      const_iterator sfind;

      for ( iterator
	      cur = this->begin( ),
	      last = this->end( );
	    cur != last;
	    ++cur )
      {
	sfind = RHS.find( key( cur ) );
	if ( sfind != slast )
	{
	  (*cur)->Merge( *(*sfind) );
	}
      }
      //-----------------------------------------------------------------
      // Add to the Primary everything that only exists in the Secondary
      //-----------------------------------------------------------------
      for ( const_iterator
	      cur = RHS.begin( ),
	      last = RHS.end( );
	    cur != last;
	    ++cur )
      {
	if ( find( key( cur ) ) == this->end( ) )
	{
	  append( *cur );
	}
      }
      return *this;
    } // Merge

#if 0
    template< class T, const std::string& (T::*F)() const >
    IStream&
    operator>>( IStream& Stream, SearchContainer< T, F >& C )
    {
      //-----------------------------------------------------------------
      // Read the PTR_STRUCT from the stream
      //-----------------------------------------------------------------
      std::unique_ptr< PTR_STRUCT_BASE >
	ptr_struct( Stream.ReadPtrStruct( ) );

      //-----------------------------------------------------------------
      // :TODO: Place into dictionary so the container can be
      // :TODO:   reconstructed once all the pieces have been read.
      //-----------------------------------------------------------------
      return Stream;
    }

    template< class T, const std::string& (T::*F)() const >
    OStream&
    operator<<( OStream& Stream, const SearchContainer< T, F >& C )
    {
      //-----------------------------------------------------------------
      // Push objects onto the writing stack and make associations to
      //  create link list in the stream
      //-----------------------------------------------------------------
      const T* previous = (const T*)NULL;

      for ( typename SearchContainer< T, F >::const_iterator
	      cur = C.begin( ),
	      last = C.end( );
	    cur != last;
	    ++cur )
      {
	Stream.Push( *cur, false );
	if ( previous )
	{
	  Stream.Next( previous, *cur );
	}
	previous = *cur;
      }

      //-----------------------------------------------------------------
      // Write the first element to the stream
      //-----------------------------------------------------------------
      const PTR_STRUCT_BASE& ptr_struct
	= ( C.size( ) == 0 )
	? Stream.Reference( (const T*)NULL )
	: Stream.Reference( C.front( ) )
	;

      //-----------------------------------------------------------------
      // Write the reference information to the stream
      //-----------------------------------------------------------------
      ptr_struct.Write( Stream );
      return Stream;
    }
#endif /* 0 */
  } // namespace - Common
} // namespace - FrameCPP

#endif /* FRAME_CPP_INTERFACE__SearchContainer_TCC */
