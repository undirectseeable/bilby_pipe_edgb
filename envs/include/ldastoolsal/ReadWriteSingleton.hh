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

#ifndef DISKCACHE_READ_WRITE_SINGLETON_HH
#define DISKCACHE_READ_WRITE_SINGLETON_HH

// System Header Files
#include <memory>

// General Header Files
#include "ldastoolsal/MemChecker.hh"
#include "ldastoolsal/ReadWriteLock.hh"

// Code generator to declare/instantiate methods, data members
// for singleton class with ReadWriteLock.

//! ignore_begin:
#define EMPTY_DIRECTIVE

#define DECLARE_READ_WRITE_SINGLETON( LM_CLASS )                               \
public:                                                                        \
    static LM_CLASS& Instance( );                                              \
                                                                               \
private:                                                                       \
    LM_CLASS( );                                                               \
    LM_CLASS( const LM_CLASS& );                                               \
    static LDASTools::AL::ReadWriteLock::baton_type initialize( );             \
    static void                                     singleton_suicide( );      \
    static LM_CLASS*                                mInstance;                 \
    static LDASTools::AL::ReadWriteLock::baton_type mLock;                     \
    static int                                      m_exit_ring

#define DEFINE_READ_WRITE_SINGLETON_CONSTRUCTOR_BODY( LM_CLASS )               \
    LDASTools::AL::MemChecker::Append(                                         \
        singleton_suicide, #LM_CLASS, m_exit_ring )

#define DEFINE_READ_WRITE_SINGLETON_NO_CONSTRUCTOR( LM_CLASS, EXIT_RING )        \
                                                                                 \
    int LM_CLASS::m_exit_ring = EXIT_RING;                                       \
                                                                                 \
    LM_CLASS*                                LM_CLASS::mInstance = (LM_CLASS*)0; \
    LDASTools::AL::ReadWriteLock::baton_type LM_CLASS::mLock =                   \
        LM_CLASS::initialize( );                                                 \
                                                                                 \
    LDASTools::AL::ReadWriteLock::baton_type LM_CLASS::initialize( )             \
    {                                                                            \
        static LDASTools::AL::ReadWriteLock::baton_type lock;                    \
        return lock;                                                             \
    }                                                                            \
                                                                                 \
    LM_CLASS& LM_CLASS::Instance( )                                              \
    {                                                                            \
        if ( mInstance == (LM_CLASS*)NULL )                                      \
        {                                                                        \
            LDASTools::AL::ReadWriteLock l(                                      \
                mLock,                                                           \
                LDASTools::AL::ReadWriteLock::WRITE,                             \
                __FILE__,                                                        \
                __LINE__ );                                                      \
                                                                                 \
            if ( mInstance == (LM_CLASS*)NULL )                                  \
            {                                                                    \
                mInstance = new LM_CLASS;                                        \
            }                                                                    \
        }                                                                        \
        return *mInstance;                                                       \
    }                                                                            \
                                                                                 \
    void LM_CLASS::singleton_suicide( )                                          \
    {                                                                            \
        LDASTools::AL::ReadWriteLock l(                                          \
            mLock, LDASTools::AL::ReadWriteLock::WRITE, __FILE__, __LINE__ );    \
        delete mInstance;                                                        \
        mInstance = (LM_CLASS*)NULL;                                             \
    }

#define DEFINE_READ_WRITE_SINGLETON_( LM_CLASS, EXIT_RING )                    \
    DEFINE_READ_WRITE_SINGLETON_NO_CONSTRUCTOR( LM_CLASS, EXIT_RING )          \
    LM_CLASS::LM_CLASS( )                                                      \
    {                                                                          \
        DEFINE_READ_WRITE_SINGLETON_CONSTRUCTOR_BODY( LM_CLASS );              \
    }

#define DEFINE_READ_WRITE_SINGLETON( LM_CLASS, EXIT_RING )                     \
    DEFINE_READ_WRITE_SINGLETON_( LM_CLASS, EXIT_RING )

//! ignore_end:

#endif
