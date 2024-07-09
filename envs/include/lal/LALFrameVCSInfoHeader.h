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
 * LALFrameVCSInfo.h - LALFrame VCS Information Header
 */

/** \cond DONT_DOXYGEN */

#ifndef _LALFRAMEVCSINFOHEADER_H
#define _LALFRAMEVCSINFOHEADER_H

#include <lal/LALVCSInfoType.h>
#include <lal/LALFrameVCSInfo.h>
#include <lal/LALFrameConfig.h>

#ifdef __cplusplus
extern "C" {
#endif

/* VCS information */
#define LALFRAME_VCS_ID "06b8cefe05741f779259cce6435b251090e76048"
#define LALFRAME_VCS_DATE "2024-03-22 17:24:30 +0000"
#define LALFRAME_VCS_BRANCH "None"
#define LALFRAME_VCS_TAG "lalframe-v3.0.4"
#define LALFRAME_VCS_AUTHOR "Duncan Macleod <duncan.macleod@ligo.org>"
#define LALFRAME_VCS_COMMITTER "Duncan Macleod <duncan.macleod@ligo.org>"
#define LALFRAME_VCS_CLEAN "CLEAN"
#define LALFRAME_VCS_STATUS "CLEAN: All modifications committed"

#if LALFRAME_VERSION_DEVEL != 0
/* VCS header/library mismatch link check function */
#define LALFRAME_VCS_LINK_CHECK LALFRAME_CLEAN_06b8cefe05741f779259cce6435b251090e76048_VCS_HEADER_LIBRARY_MISMATCH
void LALFRAME_VCS_LINK_CHECK(void);
#endif

#ifdef __cplusplus
}
#endif

#endif /* _LALFRAMEVCSINFOHEADER_H */

/** \endcond */
