//
// LDASTools AL - A library collection to provide an abstraction layer
//
// Copyright (C) 2018 California Institute of Technology
//
// LDASTools AL is free software; you may redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 (GPLv2) of the
// License or at your discretion, any later version.
//
// LDASTools AL is distributed in the hope that it will be useful, but
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

#ifndef GeneralObjectRegistryHH
#define GeneralObjectRegistryHH

#define OBJECT_REGISTRY_USE_UNORDERED_MAP 1

#include <string>

#include "ldastoolsal/ReadWriteLock.hh"
#include "ldastoolsal/types.hh"
#if OBJECT_REGISTRY_USE_UNORDERED_MAP
#include "ldastoolsal/unordered_map.hh"
#else /* OBJECT_REGISTRY_USE_UNORDERED_MAP */
#include <map>
#endif /* OBJECT_REGISTRY_USE_UNORDERED_MAP */

// forward declaration
typedef const char* ORRLExceptionDesc;

template < typename T >
class ObjectRegistry;

template < typename T,
           ObjectRegistry< T >& R,
           ORRLExceptionDesc&   ExceptionDesc,
           typename ExceptionType >
class ObjectRegistryResourceLock;

//-----------------------------------------------------------------------
/// \brief  Object Registry
///
/// This class implements a registry for objects.  The registry provides a
/// mechanism for keeping track of pointers.  The class contains methods to
/// add/remove pointers to the registry, as well as to check for the existence
/// of a pointer in the registry.
///
/// <p>The registry owns its objects.  That is, when the registry is destructed
/// it destructs any objects which are registered with it.
///
/// <p>A STL set is used to store pointers to the registered objects.
///
/// <p>This class is used by the LDAS API's to keep track of pointer objects
/// returned to the TCL layer.  To avoid segmentation faults,
/// when the C++ layer receives a pointer from TCL,
/// the appropriate ObjectRegistry object is
/// checked to ensure that the pointer exists.  Furthermore, the resetApi
/// command causes the C++ layer to empty the ObjectRegistry objects, thereby
/// ensuring that memory isn't leaked by the TCL layer failing to destruct C+
/// objects.
//-----------------------------------------------------------------------
template < class T >
class ObjectRegistry
{
private:
    //-------------------------------------------------------------------
    /// \brief State information for registered object
    ///
    /// Keep track of requests that have been made concearning a
    /// resource.
    //-------------------------------------------------------------------
    struct StateInfo
    {
    public:
        //---------------------------------------------------------------
        /// \brief Constructor (Default)
        ///
        /// Explicately initializes member of the structure.
        //---------------------------------------------------------------
        StateInfo( )
            : m_reference_count( 0 ), m_delete_object( false ),
              m_remove_object( false )
        {
        }

        //---------------------------------------------------------------
        /// \brief Counter of active tasks referencing the object.
        ///
        /// In the usual situation, there is zero or one task using
        /// the object. The object is considered to be in use
        /// when a function call is either reading or writing
        /// the contents of the object.
        //---------------------------------------------------------------
        INT_2U m_reference_count;

        //---------------------------------------------------------------
        /// \brief State of object deletion
        ///
        /// If m_delete_object is true, then the object has been
        /// requested to be deleted once m_reference_count is 0;
        /// false otherwise.
        //---------------------------------------------------------------
        bool m_delete_object;

        //---------------------------------------------------------------
        /// \brief State of object in registry
        ///
        /// If m_remove_object is true, then the object has been
        /// requested to be removed once m_reference_count is 0;
        /// false otherwise.
        //---------------------------------------------------------------
        bool m_remove_object;
    };

    //-------------------------------------------------------------------
    /// \brief Container of managed pointer data.
    ///
    /// This container type holds the collection of managed pointers
    /// and their related meta data.
    //-------------------------------------------------------------------
    typedef
#if OBJECT_REGISTRY_USE_UNORDERED_MAP
        typename LDASTools::AL::
            unordered_map< T*, StateInfo, LDASTools::AL::hash< const void* > >
#else /* OBJECT_REGISTRY_USE_UNORDERED_MAP */
        typename std::map< T*, StateInfo >
#endif /* OBJECT_REGISTRY_USE_UNORDERED_MAP */
                data_container_type;

public:
    //-------------------------------------------------------------------
    /// \brief Ensure release of resource lock
    ///
    /// This class ensures the release of a lock by performing the
    /// release within the destructor.
    /// By releasing in the destructor, the lock is release when
    /// the object goes out of scope, either by normal exit or via
    /// an exception.
    //-------------------------------------------------------------------
    class AutoLock
    {
    public:
        //---------------------------------------------------------------
        /// \brief Constructor
        ///
        /// The constructor is responsible for locking the resouce.
        ///
        /// \param Resource
        ///     The address of the resource that should be locked
        /// \param Registry
        ///     This is the list of registered objects being managed.
        ///     Resource should be managed within Registry.
        ///
        /// \exception std::range_error
        ///     This exception is throw if Resource is not being
        ///     managed by Registry.
        //---------------------------------------------------------------
        inline AutoLock( T* Resource, ObjectRegistry< T >& Registry )
            : m_resource( Resource ), m_registry( Registry )
        {
            m_registry.lock( m_resource );
        }

        //---------------------------------------------------------------
        /// \brief Desctructor
        ///
        /// Unlock the resouce.
        //---------------------------------------------------------------
        inline ~AutoLock( )
        {
            m_registry.unlock( m_resource );
        }

    private:
        //---------------------------------------------------------------
        /// \brief Resource object
        ///
        /// This is the resource that is being locked.
        //---------------------------------------------------------------
        T* m_resource;
        //---------------------------------------------------------------
        /// \brief Registry object
        ///
        /// This is the registry that should contain the resouce.
        //---------------------------------------------------------------
        ObjectRegistry< T >& m_registry;
    };

    //===================================================================
    // Constructor/Destructor
    //===================================================================
    //-------------------------------------------------------------------
    /// \brief Constructor
    //-------------------------------------------------------------------
    ObjectRegistry( );
    //-------------------------------------------------------------------
    /// \brief Destructor
    //-------------------------------------------------------------------
    ~ObjectRegistry( );

    //===================================================================
    // Accessors
    //===================================================================
    //-------------------------------------------------------------------
    /// \brief Check if the object is one of managed objects
    //-------------------------------------------------------------------
    bool isRegistered( const T* o ) const;
    //-------------------------------------------------------------------
    /// \brief The number of objects being managed
    //-------------------------------------------------------------------
    size_t size( ) const;

    //===================================================================
    // Manipulators
    //===================================================================
    //-------------------------------------------------------------------
    /// \brief Clears the list of managed objects
    //-------------------------------------------------------------------
    void reset( );
    //-------------------------------------------------------------------
    /// \brief Add an object to the list of managed objects
    //-------------------------------------------------------------------
    void registerObject( T* o );
    //-------------------------------------------------------------------
    /// \brief Remove an object from the list and deletes the object
    //-------------------------------------------------------------------
    bool destructObject( T* o );
    //-------------------------------------------------------------------
    /// \brief Remove an object from the list of managed objects
    //-------------------------------------------------------------------
    bool removeObject( T* o );

    //===================================================================
    // Algorithms
    //===================================================================
    //-------------------------------------------------------------------
    /// \brief Execute a function for each member of the list
    //-------------------------------------------------------------------
    template < class Op >
    Op for_each( Op Function ) const;

protected:
    /* typedefs */
    typedef typename data_container_type::const_iterator const_iterator;

    //-------------------------------------------------------------------
    /// \brief  Ensure only one thread accesses the registry at a time
    //-------------------------------------------------------------------
    mutable LDASTools::AL::ReadWriteLock::baton_type m_lock;

    //-------------------------------------------------------------------
    /// \brief  Obtain the start of the list (read-only)
    //-------------------------------------------------------------------
    const_iterator begin( ) const;
    //-------------------------------------------------------------------
    /// \brief  Obtain the end of the list (read-only)
    //-------------------------------------------------------------------
    const_iterator end( ) const;

private:
    friend class AutoLock;

    typedef typename data_container_type::iterator iterator;

    //-------------------------------------------------------------------
    /// \brief  Obtain the start of the list
    //-------------------------------------------------------------------
    iterator begin( );
    //-------------------------------------------------------------------
    /// \brief  Obtain the end of the list
    //-------------------------------------------------------------------
    iterator end( );

    //-------------------------------------------------------------------
    /// \brief Lock an object
    //-------------------------------------------------------------------
    void lock( T* Object );

    //-------------------------------------------------------------------
    /// \brief Unlock an object
    //-------------------------------------------------------------------
    void unlock( T* Object );

    //-------------------------------------------------------------------
    /// \brief  Collection of data members
    //-------------------------------------------------------------------
    data_container_type mData;
};

//-----------------------------------------------------------------------
/// \brief Resource lock management
///
/// This is the public class to be used when defining objects for locking
/// resources.
///
/// \tparam T
///     The type of the resource to be locked/unlocked
/// \tparam R
///     The registry which should contain the resouce to be locked/unlocked.
/// \tparam ExceptionDesc
///     The parameter to be passed to the ExceptionType when a range_error
///     happens.
/// \tparam ExceptionType
///     The type of exception to throw on range_errors
//-----------------------------------------------------------------------
template < typename T,
           ObjectRegistry< T >& R,
           ORRLExceptionDesc&   ExceptionDesc,
           typename ExceptionType >
class ObjectRegistryResourceLock : private ObjectRegistry< T >::AutoLock
{
public:
    //-------------------------------------------------------------------
    /// \brief Constructor
    ///
    /// Initialize by locking the object.
    ///
    /// \exception ExceptionType
    ///     If a range error occurs which indicates that the Resource
    ///     is not being managed by R, then throw as ExceptionType
    ///     instead.
    //-------------------------------------------------------------------
    inline ObjectRegistryResourceLock( T* Resource ) try : ObjectRegistry
        < T >::AutoLock( Resource, R )
        {
        }
    catch ( const std::range_error& Except )
    {
        throw ExceptionType( ExceptionDesc );
    }
};

//-----------------------------------------------------------------------
/// \brief  Get Beginning Iterator
///
/// Returns an iterator positioned at the beginning of the registry.
///
/// \return iterator
//-----------------------------------------------------------------------
template < class T >
inline typename ObjectRegistry< T >::iterator
ObjectRegistry< T >::begin( )
{
    return mData.begin( );
}

//-----------------------------------------------------------------------
/// \brief  Get End Iterator
///
/// Returns an iterator positioned at the end of the registry.
///
/// \return iterator
//-----------------------------------------------------------------------
template < class T >
inline typename ObjectRegistry< T >::iterator
ObjectRegistry< T >::end( )
{
    return mData.end( );
}

//-----------------------------------------------------------------------
/// \brief  Get Beginning Const Iterator
///
/// Returns a constant iterator positioned at the beginning of the registry.
///
/// \return const_iterator
//-----------------------------------------------------------------------
template < class T >
inline typename ObjectRegistry< T >::const_iterator
ObjectRegistry< T >::begin( ) const
{
    return mData.begin( );
}

//-----------------------------------------------------------------------
/// \brief  Get End Const Iterator
///
/// Returns a constant iterator positioned at the end of the registry.
///
/// \return const_iterator
//-----------------------------------------------------------------------
template < class T >
inline typename ObjectRegistry< T >::const_iterator
ObjectRegistry< T >::end( ) const
{
    return mData.end( );
}

#include "objectregistry.icc"

#endif // GeneralObjectRegistryHH
