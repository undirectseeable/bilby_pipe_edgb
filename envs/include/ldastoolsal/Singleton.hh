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

#ifndef GENERAL__SINGLETON_HH
#define GENERAL__SINGLETON_HH

#include <cassert>

#include <map>
#include <typeinfo>

#include "ldastoolsal/mutexlock.hh"
#if DEPRICATED || 1
#include "ldastoolsal/SingletonMacro.hh"
#endif /* DEPRICATED */

namespace LDASTools
{
    namespace AL
    {
        //-------------------------------------------------------------------
        // This work is derivied from the Loki Library which hold the
        //   following Copywright
        //
        // The Loki Library
        // Copyright (c) 2001 by Andrei Alexandrescu
        // This code accompanies the book:
        // Alexandrescu, Andrei. "Modern C++ Design: Generic Programming and
        // Design
        //     Patterns Applied". Copyright (c) 2001. Addison-Wesley.
        // Permission to use, copy, modify, distribute and sell this software
        // for any
        //     purpose is hereby granted without fee, provided that the above
        //     copyright notice appear in all copies and that both that
        //     copyright notice and this permission notice appear in supporting
        //     documentation.
        // The author or Addison-Wesley Longman make no representations about
        // the
        //     suitability of this software for any purpose. It is provided "as
        //     is"
        //---------------------------------------------------------------------

        typedef void ( *SingletonExitFunction )( );

        void at_exit( SingletonExitFunction Function,
                      const std::string&    Name,
                      int                   Ring );

        template < class T >
        struct CreateUsingNew
        {
            static T*
            Create( )
            {
                return new T;
            }

            static void
            Destroy( T* p )
            {
                delete p;
            }
        };

        template < class T >
        struct DefaultLifetime
        {
            static void
            ScheduleDestruction( T*, SingletonExitFunction pFun )
            {
                std::string name = "Singleton::";

                try
                {
                    name += typeid( T ).name( );
                }
                catch ( ... )
                {
                    name += "unknown";
                }
                at_exit( pFun, name, 0 );
            }

            static void
            OnDeadReference( )
            {
                throw std::logic_error( "Dead Reference Detected" );
            }
        };

        /// \note
        ///     Removed the ThreadingModel and MutexPolicy from the originial
        ///     code
        template < typename T,
                   template < class > class CreationPolicy = CreateUsingNew,
                   template < class > class LifetimePolicy = DefaultLifetime >
        class SingletonHolder
        {
        public:
            typedef T ObjectType;

            static T& Instance( );

        private:
            // Helpers
            static void MakeInstance( );
            static void DestroySingleton( );

            // Protection
            SingletonHolder( );

            // Data
            typedef T*                    PtrInstanceType;
            typedef MutexLock::baton_type baton_type;

            static baton_type      baton;
            static PtrInstanceType pInstance_;
            static bool            destroyed_;
        };

        // SingletonHolder's data

        template < class T,
                   template < class >
                   class C,
                   template < class >
                   class L >
        typename SingletonHolder< T, C, L >::baton_type
            SingletonHolder< T, C, L >::baton;

        template < class T,
                   template < class >
                   class C,
                   template < class >
                   class L >
        typename SingletonHolder< T, C, L >::PtrInstanceType
            SingletonHolder< T, C, L >::pInstance_;

        template < class T,
                   template < class >
                   class C,
                   template < class >
                   class L >
        bool SingletonHolder< T, C, L >::destroyed_;

        // SingletonHolder::Instance

        template < class T,
                   template < class >
                   class CreationPolicy,
                   template < class >
                   class LifetimePolicy >
        inline T&
        SingletonHolder< T, CreationPolicy, LifetimePolicy >::Instance( )
        {
            if ( !pInstance_ )
            {
                MakeInstance( );
            }
            return *pInstance_;
        }

        // SingletonHolder::MakeInstance (helper for Instance)

        template < class T,
                   template < class >
                   class CreationPolicy,
                   template < class >
                   class LifetimePolicy >
        void
        SingletonHolder< T, CreationPolicy, LifetimePolicy >::MakeInstance( )
        {
            MutexLock lock( baton, __FILE__, __LINE__ );

            if ( !pInstance_ )
            {
                if ( destroyed_ )
                {
                    destroyed_ = false;
                    LifetimePolicy< T >::OnDeadReference( );
                }
                pInstance_ = CreationPolicy< T >::Create( );
                LifetimePolicy< T >::ScheduleDestruction( pInstance_,
                                                          &DestroySingleton );
            }
        }

        template < typename T,
                   template < class >
                   class CreationPolicy,
                   template < class >
                   class L >
        void
        SingletonHolder< T, CreationPolicy, L >::DestroySingleton( )
        {
            if ( !destroyed_ && pInstance_ )
            {
                assert( !destroyed_ );
                CreationPolicy< T >::Destroy( pInstance_ );
                pInstance_ = 0;
                destroyed_ = true;
            }
        }

        template < class T >
        class Singleton
        {
        public:
            static T& Instance( );
        };
    } // namespace AL

} // namespace LDASTools
#define SINGLETON_INSTANCE_DEFINITION( SHOLDER )                               \
    namespace LDASTools                                                        \
    {                                                                          \
        namespace AL                                                           \
        {                                                                      \
            template <>                                                        \
            SHOLDER::ObjectType&                                               \
            Singleton< SHOLDER::ObjectType >::Instance( )                      \
            {                                                                  \
                return SHOLDER::Instance( );                                   \
            }                                                                  \
        }                                                                      \
    }

#endif /* GENERAL__SINGLETON_HH */
