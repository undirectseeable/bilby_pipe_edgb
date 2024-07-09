/*
 * Copyright (C) 2014, 2016 Karl Wette
 * Copyright (C) 2009-2013 Adam Mercer
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or (at
 * your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with with program; see the file COPYING. If not, write to the
 * Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301 USA
 */

/*
 * LALMetaIOVCSInfo.h - LALMetaIO VCS Information Header
 */

/** \cond DONT_DOXYGEN */

#ifndef _LALMETAIOVCSINFOHEADER_H
#define _LALMETAIOVCSINFOHEADER_H

#include <lal/LALVCSInfoType.h>
#include <lal/LALMetaIOVCSInfo.h>
#include <lal/LALMetaIOConfig.h>

#ifdef __cplusplus
extern "C" {
#endif

/* VCS information */
#define LALMETAIO_VCS_ID "acd07ef2b8fc3292838cc99d8317485ba7dfd6af"
#define LALMETAIO_VCS_DATE "2024-03-22 17:24:30 +0000"
#define LALMETAIO_VCS_BRANCH "None"
#define LALMETAIO_VCS_TAG "lalmetaio-v4.0.4"
#define LALMETAIO_VCS_AUTHOR "Duncan Macleod <duncan.macleod@ligo.org>"
#define LALMETAIO_VCS_COMMITTER "Duncan Macleod <duncan.macleod@ligo.org>"
#define LALMETAIO_VCS_CLEAN "CLEAN"
#define LALMETAIO_VCS_STATUS "CLEAN: All modifications committed"

#if LALMETAIO_VERSION_DEVEL != 0
/* VCS header/library mismatch link check function */
#define LALMETAIO_VCS_LINK_CHECK LALMETAIO_CLEAN_acd07ef2b8fc3292838cc99d8317485ba7dfd6af_VCS_HEADER_LIBRARY_MISMATCH
void LALMETAIO_VCS_LINK_CHECK(void);
#endif

#ifdef __cplusplus
}
#endif

#endif /* _LALMETAIOVCSINFOHEADER_H */

/** \endcond */
