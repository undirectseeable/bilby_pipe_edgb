#ifndef GENERAL__UNORDERED_MAP_HH
#define GENERAL__UNORDERED_MAP_HH

#if !defined( SWIG )
#include <string>
#endif /* ! defined(SWIGIMPORTED) */

#if !defined( SWIG )
/* clang-format off */
#if 1 // HAVE_UNORDERED_MAP
#if !defined( WITH_UNORDERED_MAP_NAMESPACE )
#define WITH_UNORDERED_MAP_NAMESPACE std
#endif /* ! defined(WITH_UNORDERED_MAP_NAMESPACE) */
#include <unordered_map>
#define UNORDERED_MAP_NAMESPACE WITH_UNORDERED_MAP_NAMESPACE
#define HASH_NAMESPACE WITH_UNORDERED_MAP_NAMESPACE
#elif 1 // HAVE_TR1_UNORDERED_MAP
#if !defined( WITH_TR1_UNORDERED_MAP_NAMESPACE )
#define WITH_TR1_UNORDERED_MAP_NAMESPACE std::tr1
#endif /* ! defined(WITH_UNORDERED_MAP_NAMESPACE) */
#include <tr1/unordered_map>
#define UNORDERED_MAP_NAMESPACE WITH_TR1_UNORDERED_MAP_NAMESPACE
#define HASH_NAMESPACE WITH_TR1_UNORDERED_MAP_NAMESPACE
#define HASH_NAMESPACE_BEGIN                                                   \
    namespace std                                                              \
    {                                                                          \
        namespace tr1
#define HASH_NAMESPACE_END }
#undef NEED_HASH_UNSIGNED_LONG_LONG
#undef NEED_HASH_LONG_LONG
#elif 1 // hash_map was found
#include <hash_map>
#if defined( __GNUG__ ) && ( __GNUG__ < 3 )
#define HASH_NAMESPACE
#else
#define HASH_MAP_NAMESPACE std
#endif
#elif 1 // ext/hash_map was found
//-----------------------------------------------------------------------
// GNU hash_map
//-----------------------------------------------------------------------
#if !defined( SWIGIMPORTED )
#include <ext/hash_map>
#endif /* ! defined(SWIGIMPORTED) */
#if defined( __GNUG__ )
#define HASH_MAP_NAMESPACE __gnu_cxx
#endif
#define HASH_STRING_VIA_HASH_CHAR_PTR
#else
//-----------------------------------------------------------------------
// Nothing else so just use map
//-----------------------------------------------------------------------
#include <map>
#endif
/* clang-format on */
#endif /* ! defined(SWIG) */

#if !defined( HASH_NAMESPACE ) && defined( HASH_MAP_NAMESPACE )
#define HASH_NAMESPACE HASH_MAP_NAMESPACE
#endif

#if !defined( HASH_NAMESPACE_BEGIN )
#define HASH_NAMESPACE_BEGIN namespace HASH_NAMESPACE
#define HASH_NAMESPACE_END
#endif /* !defined(HASH_NAMESPACE_BEGIN) */

HASH_NAMESPACE_BEGIN
{
#ifndef SWIG
    template <>
    struct hash< const void* >
    {
        size_t
        operator( )( const void* Key ) const
        {
            return reinterpret_cast< size_t >( Key );
        }
    };
#endif /* SWIG */

#ifndef SWIG
#if defined( HASH_STRING_VIA_HASH_CHAR_PTR )
    template <>
    struct hash< std::string >
    {
        size_t
        operator( )( const std::string& S ) const
        {
            HASH_NAMESPACE::hash< const char* > h;
            return h( S.c_str( ) );
        }
    };
#endif /* HASH_STRING_VIA_HASH_CHAR_PTR */
#endif /* SWIG */

#ifndef SWIG
#if NEED_HASH_LONG_LONG
    template <>
    struct hash< long long >
    {
        size_t
        operator( )( long long __x ) const
        {
#if SIZEOF_SIZE_T == 8
            return __x;
#elif SIZEOF_SIZE_T == 4
            size_t r( ( __x >> 32 ) ^ ( 0xFFFFFFFF & __x ) );

            return r;
#endif
        }
    };
#endif /* NEED_HASH_LONG_LONG */
#endif /* SWIG */

#ifndef SWIG
#if NEED_HASH_UNSIGNED_LONG_LONG
    template <>
    struct hash< unsigned long long >
    {
        size_t
        operator( )( unsigned long long __x ) const
        {
#if SIZEOF_LONG == 8
            return __x;
#elif SIZEOF_SIZE_T == 4
            size_t r( ( __x >> 32 ) ^ ( 0xFFFFFFFF & __x ) );

            return r;
#endif
        }
    };
#endif /* NEED_HASH_UNSIGNED_LONG_LONG */
#endif /* SWIG */
}
HASH_NAMESPACE_END

namespace LDASTools
{
    namespace AL
    {
#if !defined( SWIG )
        using HASH_NAMESPACE::hash;
#endif /* ! defined(SWIG) */

        /// \brief  Place unordered_map into General namespace.
        template < class Key,
                   class T,
                   class H = hash< Key >,
                   class EQ = std::equal_to< Key >,
                   class A = std::allocator< std::pair< const Key, T > > >
        class unordered_map :
#if defined( UNORDERED_MAP_NAMESPACE )
            public UNORDERED_MAP_NAMESPACE::unordered_map< Key, T, H, EQ, A >
#elif defined( HASH_MAP_NAMESPACE )
            public HASH_MAP_NAMESPACE::hash_map< Key, T, H, EQ, A >
#else /* UNORDERED_MAP_NAMESPACE */
            public std::map< Key, T, EQ, A >
#endif /* UNORRDERED_MAP_NAMESPACE */
        {
        };

        /// \brief  Place unordered_multimap into General namespace.
        template < class Key,
                   class T,
                   class H = hash< Key >,
                   class EQ = std::equal_to< Key >,
                   class A = std::allocator< std::pair< const Key, T > > >
        class unordered_multimap :
#if defined( UNORDERED_MAP_NAMESPACE )
            public UNORDERED_MAP_NAMESPACE::
                unordered_multimap< Key, T, H, EQ, A >
#elif defined( HASH_MAP_NAMESPACE )
            public HASH_MAP_NAMESPACE::hash_multimap< Key, T, H, EQ, A >
#else /* UNORDERED_MAP_NAMESPACE */
            public std::multimap< Key, T, EQ, A >
#endif /* UNORRDERED_MAP_NAMESPACE */
        {
        };

        template < class T >
        struct hash_pointer
        {
            inline size_t
            operator( )( const T* Key ) const
            {
                return reinterpret_cast< size_t >( Key );
            }
        };
    } // namespace AL
} // namespace LDASTools

#endif /* GENERAL__UNORDERED_MAP_HH */
