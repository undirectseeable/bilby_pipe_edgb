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
 * LALVCSInfo.h - LAL VCS Information Header
 */

/** \cond DONT_DOXYGEN */

#ifndef _LALVCSINFOHEADER_H
#define _LALVCSINFOHEADER_H

#include <lal/LALVCSInfoType.h>
#include <lal/LALVCSInfo.h>
#include <lal/LALConfig.h>

#ifdef __cplusplus
extern "C" {
#endif

/* VCS information */
#define LAL_VCS_ID "edd3f4e61431c1a0c6a7be13c0be9644be1f6745"
#define LAL_VCS_DATE "2024-03-22 17:24:29 +0000"
#define LAL_VCS_BRANCH "None"
#define LAL_VCS_TAG "lal-v7.5.0"
#define LAL_VCS_AUTHOR "Duncan Macleod <duncan.macleod@ligo.org>"
#define LAL_VCS_COMMITTER "Duncan Macleod <duncan.macleod@ligo.org>"
#define LAL_VCS_CLEAN "CLEAN"
#define LAL_VCS_STATUS "CLEAN: All modifications committed"

#if LAL_VERSION_DEVEL != 0
/* VCS header/library mismatch link check function */
#define LAL_VCS_LINK_CHECK LAL_CLEAN_edd3f4e61431c1a0c6a7be13c0be9644be1f6745_VCS_HEADER_LIBRARY_MISMATCH
void LAL_VCS_LINK_CHECK(void);
#endif

#ifdef __cplusplus
}
#endif

#endif /* _LALVCSINFOHEADER_H */

/** \endcond */
