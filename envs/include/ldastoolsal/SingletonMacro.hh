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

#ifndef GENERAL__SINGLETON_MACRO_HH
#define GENERAL__SINGLETON_MACRO_HH

/* :TODO: Doxygen document Singleton.hh */

//// \cond EXCLUDE

///!ignore_begin:
/// This provides the definition for the singleton portion of the class
///
/// The only interface exposed to the developer is the Instance() function.
///
/// The default constructor being private ensures that this class cannot
///   be used as the base of any other class.
///
/// The copy constructor being private prevents asignment.
///
/// An example of the use of this class would be:
///
/// class a
/// {
///  SINGLETON_DECL( a ); // Important declarations for a singleton
///
///  public:
///    void x( );  // Method to do some work
///
///  private:
///    // Data members and other methods
/// };
///
/// SINGLETON_INST( a ); // Create code for Instance( ) method.
///
/// a::
/// a( )
/// {
///   // Do initialization code here
/// }
///
/// void a::
/// x( )
/// {
///   // Do something here
/// }
#define SINGLETON_DECL( Class_ )                                               \
public:                                                                        \
    inline static Class_& Instance( )                                          \
    {                                                                          \
        return SSelf( true );                                                  \
    }                                                                          \
    static Class_& SSelf( bool Create = true );                                \
                                                                               \
private:                                                                       \
    Class_( );                                                                 \
    Class_( const Class_& );                                                   \
                                                                               \
    static void    singleton_suicide( );                                       \
    static bool    xxyyzz_singleton_created;                                   \
    static Class_* xxyyzz_singleton_instance

/// Providing a seperate mutex lock for each singleton prevents most cases
///    of deadlock. The only case that still exists (in its simplest form)
///    is if class A requires class B and class B requires class A and
///    both class A is a singleton. This case, however, is bad coding and
///    needs to be avoided.
///
#define SINGLETON_TS_DECL( Class_ )                                            \
    SINGLETON_DECL( Class_ );                                                  \
                                                                               \
private:                                                                       \
    static LDASTools::AL::MutexLock::baton_type xxyyzz_singleton_lock( )

/// This provides the code for the singleton portion of the class
#define SINGLETON_INST( Class_ )                                               \
                                                                               \
    Class_& Class_::SSelf( bool Create )                                       \
    {                                                                          \
        if ( ( xxyyzz_singleton_instance == 0 ) &&                             \
             ( xxyyzz_singleton_created == false ) && ( Create ) )             \
        {                                                                      \
            xxyyzz_singleton_instance = new Class_;                            \
            xxyyzz_singleton_created = true;                                   \
        }                                                                      \
        if ( xxyyzz_singleton_instance )                                       \
        {                                                                      \
            return *xxyyzz_singleton_instance;                                 \
        }                                                                      \
        throw std::runtime_error( "The singleton class " #Class_               \
                                  " has already been destroyed" );             \
    }                                                                          \
                                                                               \
    void Class_::singleton_suicide( )                                          \
    {                                                                          \
        Class_* i = xxyyzz_singleton_instance;                                 \
        xxyyzz_singleton_instance = (Class_*)NULL;                             \
        delete i;                                                              \
    }                                                                          \
                                                                               \
    Class_* Class_::_single_instance = 0;                                      \
    bool    Class_::xxyyzz_singleton_created = false

/// This provides the code for the singleton portion of the class
#define SINGLETON_TS_INST( Class_ )                                            \
                                                                               \
    Class_& Class_::SSelf( bool Create )                                       \
    {                                                                          \
        if ( ( xxyyzz_singleton_instance == 0 ) &&                             \
             ( xxyyzz_singleton_created == false ) && ( Create ) )             \
        {                                                                      \
            LDASTools::AL::MutexLock lock(                                     \
                xxyyzz_singleton_lock( ), __FILE__, __LINE__ );                \
                                                                               \
            if ( ( xxyyzz_singleton_instance == 0 ) &&                         \
                 ( xxyyzz_singleton_created == false ) )                       \
            {                                                                  \
                xxyyzz_singleton_instance = new Class_;                        \
                xxyyzz_singleton_created = true;                               \
            }                                                                  \
        }                                                                      \
        if ( xxyyzz_singleton_instance )                                       \
        {                                                                      \
            return *xxyyzz_singleton_instance;                                 \
        }                                                                      \
        throw std::runtime_error( "The singleton class " #Class_               \
                                  " has already been destroyed" );             \
    }                                                                          \
                                                                               \
    void Class_::singleton_suicide( )                                          \
    {                                                                          \
        Class_* i = (Class_*)NULL;                                             \
        {                                                                      \
            LDASTools::AL::MutexLock lock(                                     \
                xxyyzz_singleton_lock( ), __FILE__, __LINE__ );                \
                                                                               \
            i = xxyyzz_singleton_instance;                                     \
            xxyyzz_singleton_instance = (Class_*)NULL;                         \
        }                                                                      \
        if ( i )                                                               \
        {                                                                      \
            delete i;                                                          \
        }                                                                      \
    }                                                                          \
                                                                               \
    LDASTools::AL::MutexLock::baton_type Class_::xxyyzz_singleton_lock( )      \
    {                                                                          \
        static LDASTools::AL::MutexLock::baton_type retval( __FILE__,          \
                                                            __LINE__ );        \
                                                                               \
        return retval;                                                         \
    }                                                                          \
                                                                               \
    Class_* Class_::xxyyzz_singleton_instance = 0;                             \
    bool    Class_::xxyyzz_singleton_created = false

///!ignore_end:

//// \endcond EXCLUDE
#endif /* GENERAL__SINGLETON_MACRO_HH */
