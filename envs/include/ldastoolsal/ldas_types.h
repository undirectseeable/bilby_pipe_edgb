#ifndef GENERAL__LDAS_TYPES_H
#define GENERAL__LDAS_TYPES_H

/* System Header Files */
#if !defined( SWIGIMPORTED )
#include <float.h>
#endif /* ! defined(SWIGIMPORTED) */

#if !defined( SWIGIMPORTED )
#ifdef __cplusplus
#include <complex>
#endif /* __cplusplus */
#endif /* ! defined(SWIGIMPORTED) */

/* clang-format off */
typedef short INT_2S;
typedef unsigned short INT_2U;

typedef int INT_4S;
typedef unsigned int INT_4U;

typedef long INT_8S;
typedef unsigned long INT_8U;

typedef float REAL_4;
#define REAL_4_DIGITS FLT_DIG

typedef double REAL_8;
#define REAL_8_DIGITS DBL_DIG

typedef char          CHAR;
typedef unsigned char CHAR_U;

typedef INT_8U MEM_PTR;
/* clang-format on */

#if !defined( SWIGIMPORTED )
#ifdef __cplusplus
typedef std::complex< REAL_4 > COMPLEX_8;
typedef std::complex< REAL_8 > COMPLEX_16;
#else
/*------------------------------------------*/
/** \todo implement complex for C interface */
/*------------------------------------------*/
#endif /* __cplusplus */
#endif /* ! defined(SWIGIMPORTED) */

#endif /* GENERAL__LDAS_TYPES_H */
