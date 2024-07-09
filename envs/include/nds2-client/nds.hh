/* -*- mode: C++ ; c-basic-offset: 2; indent-tabs-mode: nil -*- */

#ifndef SWIG__COMMON__NDS_HH
#define SWIG__COMMON__NDS_HH

#if WIN32 || WIN64
/* ----------------------------------------------------------------------
 * Windows System
 * ----------------------------------------------------------------------
 */

#ifdef _DEBUG
#undef _SCL_SECURE_NO_WARNINGS
#define _SCL_SECURE_NO_WARNINGS
#endif /* _DEBUG */
#endif /* WIN32 || WIN64 */

// ----------------------------------------------------------------------
/// \namespace NDS
///
/// \brief The NDS client namespace
///
// ----------------------------------------------------------------------

#include "nds_buffer.hh"
#include "nds_channel.hh"
#include "nds_availability.hh"
#include "nds_connection.hh"
#include "nds_version.hh"
#include "nds_standalone.hh"

#endif /* SWIG__COMMON__NDS_HH */
