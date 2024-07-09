#ifndef GENERAL__REVERSE_HH
#define GENERAL__REVERSE_HH

#if !defined( SWIGIMPORTED )
#include <assert.h>

/* clang-format off */
#if 1 // HAVE_BYTESWAP_H
#include <byteswap.h>
#else /* HAVE_BYTESWAP_H */
#include <sys/types.h>
#if 0 // HAVE_SYS_BYTEORDER_H
#include <sys/byteorder.h>
#endif /* HAVE_SYS_BYTEORDER_H */
#if 0 // HAVE_MACHINE_BSWAP_H
#include <machine/bswap.h>
#endif /* HAVE_MACHINE_BSWAP_H */
#if 0 // HAVE_LIBKERN_OSBYTEORDER_H
#include <libkern/OSByteOrder.h>
#endif /* HAVE_LIBKERN_OSBYTEORDER_H */
#endif /* HAVE_BYTESWAP_H */
/* clang-format on */

#include <stdint.h>
#endif /* defined(SWIGIMPORTED) */

#ifndef BSWAP_8
#define BSWAP_8( x ) ( (x)&0xff )
#endif /* BSWAP_8 */

/* clang-format off */
#if !1 // HAVE_BSWAP_16
#if 0 // HAVE_BSWAP16
#define bswap_16( x ) bswap16( x )
#elif 0 // HAVE_BSWAP_16_MACRO
#define bswap_16( x ) BSWAP_16( x )
#elif 0 // HAVE_OSSWAPINT16
#define bswap_16( x ) OSSwapInt16( x )
#else
#define bswap_16( x ) ( ( BSWAP_8( x ) << 8 ) | BSWAP_8( ( x ) >> 8 ) )
#endif /* HAVE_BSWAP16*/
#endif /* ! HAVE_BSWAP_16 */

#if !1 // HAVE_BSWAP_32
#if 0 // HAVE_BSWAP32
#define bswap_32( x ) bswap32( x )
#elif 0 // HAVE_BSWAP_32_MACRO
#define bswap_32( x ) BSWAP_32( x )
#elif 0 // HAVE_OSSWAPINT32
#define bswap_32( x ) OSSwapInt32( x )
#else
#define bswap_32( x ) ( ( bswap_16( x ) << 16 ) | bswap_16( ( x ) >> 16 ) )
#endif /* HAVE_BSWAP32*/
#endif /* ! HAVE_BSWAP_32 */

#if !1 // HAVE_BSWAP_64
#if 0 // HAVE_BSWAP64
#define bswap_64( x ) bswap64( x )
#elif 0 // HAVE_BSWAP_64_MACRO
#define bswap_64( x ) BSWAP_64( x )
#elif 0 // HAVE_OSSWAPINT64
#define bswap_64( x ) OSSwapInt64( x )
#else
#define bswap_64( x ) ( ( bswap_32( x ) << 32 ) | bswap_32( ( x ) >> 32 ) )
#endif /* HAVE_BSWAP64*/
#endif /* ! HAVE_BSWAP_64 */
/* clang-format on */

#include "ldastoolsal/types.hh"

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
template < typename T >
T bswap( T Source );

template <>
inline uint32_t
bswap( uint32_t Source )
{
    return bswap_32( Source );
}

//-----------------------------------------------------------------------------
/// \brief  Reverse Byte Order
///
/// \param s
/// \param n
///
template < size_t SIZE >
void reverse( void* s, size_t n );

//-----------------------------------------------------------------------------
/// \brief  Reverse 1 byte
///
/// This does nothing.
///
/// \param dest
/// \param n
///
template <>
inline void
reverse< 1 >( void* dest, size_t n )
{
    return;
}

//-----------------------------------------------------------------------------
/// \brief  Reverse 2 bytes
///
/// Reverses the order of two bytes.  This is a template specialization.
///
/// \param[in,out] dest
///     This is the collection of data on which the bytes need to be swapped.
///
/// \param[in] n
///     The number of elements in the collection.
///
template <>
inline void
reverse< 2 >( void* dest, size_t n )
{
    INT_2U* d = reinterpret_cast< INT_2U* >( dest );
    INT_2U* end = d + n;

    while ( d != end )
    {
        *d = bswap_16( *d );
        ++d;
    }
}

//-----------------------------------------------------------------------------
/// \brief  Reverse 4 bytes
///
/// Reverses the order of four bytes.  This is a template specialization.
///
/// \param[in,out] dest
///     This is the collection of data on which the bytes need to be swapped.
///
/// \param[in] n
///     The number of elements in the collection.
///
template <>
inline void
reverse< 4 >( void* dest, size_t n )
{
    INT_4U* d = reinterpret_cast< INT_4U* >( dest );
    INT_4U* end = d + n;

    while ( d != end )
    {
        *d = bswap_32( *d );
        ++d;
    }
}

//-----------------------------------------------------------------------------
/// \brief  Reverse 8 bytes
///
/// Reverses the order of eight bytes.  This is a template specialization.
///
/// \param[in,out] dest
///     This is the collection of data on which the bytes need to be swapped.
///
/// \param[in] n
///     The number of elements in the collection.
///
template <>
inline void
reverse< 8 >( void* dest, size_t n )
{
    INT_8U* cur = reinterpret_cast< INT_8U* >( dest );
    INT_8U* end = cur + n;

    while ( cur != end )
    {
        *cur = bswap_64( *cur );
        ++cur;
    }
}

//-----------------------------------------------------------------------------
/// \brief  Reverse 12 bytes
///
/// Reverses the order of twelve bytes.  This is a template specialization.
///
/// \param[in,out] s
///     This is the collection of data on which the bytes need to be swapped.
///
/// \param[in] n
///     The number of elements in the collection.
///
template <>
inline void
reverse< 12U >( void* s, size_t n )
{
    assert( 0 );
}

//-----------------------------------------------------------------------------
/// \brief  Reverse 16 bytes
///
/// Reverses the order of sixteen bytes.  This is a template specialization.
///
/// \param[in,out] s
///     This is the collection of data on which the bytes need to be swapped.
///
/// \param[in] n
///     The number of elements in the collection.
///
template <>
inline void
reverse< 16U >( void* s, size_t n )
{
    assert( 0 );
}

//-----------------------------------------------------------------------------
/// \brief  Reverse 36 bytes
///
/// Reverses the order of thirty six bytes.  This is a template specialization.
///
/// \param[in,out] s
///     This is the collection of data on which the bytes need to be swapped.
///
/// \param[in] n
///     The number of elements in the collection.
///
template <>
inline void
reverse< 36U >( void* s, size_t n )
{
    assert( 0 );
}

#endif /* GENERAL__REVERSE_HH */
