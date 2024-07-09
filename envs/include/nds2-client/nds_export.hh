/* -*- tab-width:8 c-basic-offset:4  indent-tabs-mode:nil -*- */
/* set vi: ts=8:softtabstop=4,shiftwidth=4,expandtab */

#ifndef NDS_EXPORT_HH
#define NDS_EXPORT_HH

#if WIN32 || WIN64

#if NDS_EXPORT
#define DLL_EXPORT __declspec( dllexport )
#else /* NDS_EXPORT */
#define DLL_EXPORT __declspec( dllimport )
#endif /* NDS_EXPORT */

#else /* WIN32 || WIN64 */

#define DLL_EXPORT

#endif /* WIN32 || WIN64 */

#endif /* NDS_EXPORT_HH */
