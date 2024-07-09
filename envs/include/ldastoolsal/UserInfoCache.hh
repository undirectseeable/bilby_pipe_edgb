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

#ifndef GENERAL__USER_INFO_CACHE_HH
#define GENERAL__USER_INFO_CACHE_HH

#include <string>

#include "ldastoolsal/unordered_map.hh"
#include "ldastoolsal/mutexlock.hh"
#include "ldastoolsal/Singleton.hh"
#include "ldastoolsal/types.hh"

namespace LDASTools
{
    namespace AL
    {
        //---------------------------------------------------------------------
        /// \brief Cache system information about users
        ///
        /// The information stored within this class contains information
        /// about the users that have access to current machine.
        ///
        /// \note
        ///     This information is currently static.
        ///     It is gathered when the shared object is loaded and is
        ///     never updated.
        //---------------------------------------------------------------------
        class UserInfoCache
        {
            SINGLETON_TS_DECL( UserInfoCache );

        public:
            //-------------------------------------------------------------------
            /// \brief Class to manage information about a single user.
            //-------------------------------------------------------------------
            class UserInfo
            {
            public:
                typedef INT_4U uid_type;
                typedef INT_4U gid_type;

                //-----------------------------------------------------------------
                /// \brief constructor
                //-----------------------------------------------------------------
                UserInfo( );

                //-----------------------------------------------------------------
                /// \brief constructor
                //-----------------------------------------------------------------
                UserInfo( const char*    Name,
                          const char*    Password,
                          const uid_type UID,
                          const gid_type GID,
                          const char*    Gecos,
                          const char*    HomeDir,
                          const char*    Shell );

                //-----------------------------------------------------------------
                /// \brief Supply the system name of the user.
                //-----------------------------------------------------------------
                const std::string& Name( ) const;

                //-----------------------------------------------------------------
                /// \brief Supply the caller with the user's group id
                //-----------------------------------------------------------------
                gid_type GID( ) const;

                //-----------------------------------------------------------------
                /// \brief Supply the caller with user's id
                //-----------------------------------------------------------------
                uid_type UID( ) const;

            private:
                //-----------------------------------------------------------------
                /// \brief System name of the user
                //-----------------------------------------------------------------
                std::string m_name;
                //-----------------------------------------------------------------
                /// \brief Encrypted password for user
                //-----------------------------------------------------------------
                std::string m_password;
                //-----------------------------------------------------------------
                /// \brief User identification number
                //-----------------------------------------------------------------
                uid_type m_uid;
                //-----------------------------------------------------------------
                /// \brief Group identification number
                //-----------------------------------------------------------------
                gid_type m_gid;
                //-----------------------------------------------------------------
                /// \brief Full name for the user
                //-----------------------------------------------------------------
                std::string m_gecos;
                //-----------------------------------------------------------------
                /// \brief The home directory for the user
                //-----------------------------------------------------------------
                std::string m_home_dir;
                //-----------------------------------------------------------------
                /// \brief The login shell for the user
                //-----------------------------------------------------------------
                std::string m_shell;
            }; // class - UserInfo

            //-------------------------------------------------------------------
            /// \brief Destructor to release system resources
            //-------------------------------------------------------------------
            ~UserInfoCache( );

            //-------------------------------------------------------------------
            /// \brief Locate an entry based on the identification number of the
            /// user
            //-------------------------------------------------------------------
            static const UserInfo& UID( UserInfo::uid_type Id );
            //-------------------------------------------------------------------
            /// \brief Locate an entry based on the system name of the user
            //-------------------------------------------------------------------
            static const UserInfo& Name( const std::string& Name );

        private:
            //-------------------------------------------------------------------
            /// \brief Container to hold cached infomation
            //-------------------------------------------------------------------
            typedef LDASTools::AL::unordered_map< INT_4U, UserInfo > cache_type;
            //-------------------------------------------------------------------
            /// \brief Container to hold mapping from system name to uid
            //-------------------------------------------------------------------
            typedef LDASTools::AL::unordered_map< std::string, INT_4U >
                name_mapping_type;

            //-------------------------------------------------------------------
            /// \brief Storage for the cache
            //-------------------------------------------------------------------
            cache_type m_cache;
            //-------------------------------------------------------------------
            /// \brief Storage for the map between system name and uid
            //-------------------------------------------------------------------
            name_mapping_type m_names;
            //-------------------------------------------------------------------
            /// \brief Baton to control access
            //-------------------------------------------------------------------
            MutexLock::baton_type m_baton;

            //-------------------------------------------------------------------
            /// \brief Create new entry.
            //-------------------------------------------------------------------
            const UserInfo& create( UserInfo::uid_type Id );
            //-------------------------------------------------------------------
            /// \brief Initiazation routine.
            //-------------------------------------------------------------------
            bool init( );

            //-------------------------------------------------------------------
            /// \brief Return the user identifier
            //-------------------------------------------------------------------
            const UserInfo& uid( UserInfo::uid_type Id );

        }; // class - UserInfoCache

        //---------------------------------------------------------------------
        /// This is the default constructor
        //---------------------------------------------------------------------
        inline UserInfoCache::UserInfo::UserInfo( )
            : m_name( ), m_password( ), m_uid( ), m_gid( ), m_gecos( ),
              m_home_dir( ), m_shell( )
        {
        }

        //---------------------------------------------------------------------
        /// This constructor fills in the information suppled by reading
        /// each of the password entries.
        //---------------------------------------------------------------------
        inline UserInfoCache::UserInfo::UserInfo( const char*    Name,
                                                  const char*    Password,
                                                  const uid_type UID,
                                                  const gid_type GID,
                                                  const char*    Gecos,
                                                  const char*    HomeDir,
                                                  const char*    Shell )
            : m_name( Name ), m_password( Password ), m_uid( UID ),
              m_gid( GID ), m_gecos( Gecos ), m_home_dir( HomeDir ),
              m_shell( Shell )
        {
        }

        //---------------------------------------------------------------------
        /// Supply the caller with the System Name.
        //---------------------------------------------------------------------
        inline const std::string&
        UserInfoCache::UserInfo::Name( ) const
        {
            return m_name;
        }

        //---------------------------------------------------------------------
        /// Supply the caller with user's group id
        //---------------------------------------------------------------------
        inline UserInfoCache::UserInfo::gid_type
        UserInfoCache::UserInfo::GID( ) const
        {
            return m_gid;
        }

        //---------------------------------------------------------------------
        /// Supply the caller with user's id
        //---------------------------------------------------------------------
        inline UserInfoCache::UserInfo::uid_type
        UserInfoCache::UserInfo::UID( ) const
        {
            return m_uid;
        }

        //---------------------------------------------------------------------
        /// Supply the caller with the full set of information known about
        /// the user assoicated with the giver user identification number.
        //---------------------------------------------------------------------
        inline const UserInfoCache::UserInfo&
        UserInfoCache::UID( UserInfo::uid_type Id )
        {
            return Instance( ).uid( Id );
        }
    } // namespace AL
} // namespace LDASTools

#endif /* GENERAL__USER_INFO_CACHE_HH */
