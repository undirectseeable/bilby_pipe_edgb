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
 * LALInferenceVCSInfo.h - LALInference VCS Information Header
 */

/** \cond DONT_DOXYGEN */

#ifndef _LALINFERENCEVCSINFOHEADER_H
#define _LALINFERENCEVCSINFOHEADER_H

#include <lal/LALVCSInfoType.h>
#include <lal/LALInferenceVCSInfo.h>
#include <lal/LALInferenceConfig.h>

#ifdef __cplusplus
extern "C" {
#endif

/* VCS information */
#define LALINFERENCE_VCS_ID "575bd202e1d9b1c38b7486d282f843209423fa34"
#define LALINFERENCE_VCS_DATE "2024-03-22 17:24:32 +0000"
#define LALINFERENCE_VCS_BRANCH "None"
#define LALINFERENCE_VCS_TAG "lalinference-v4.1.6"
#define LALINFERENCE_VCS_AUTHOR "Duncan Macleod <duncan.macleod@ligo.org>"
#define LALINFERENCE_VCS_COMMITTER "Duncan Macleod <duncan.macleod@ligo.org>"
#define LALINFERENCE_VCS_CLEAN "CLEAN"
#define LALINFERENCE_VCS_STATUS "CLEAN: All modifications committed"

#if LALINFERENCE_VERSION_DEVEL != 0
/* VCS header/library mismatch link check function */
#define LALINFERENCE_VCS_LINK_CHECK LALINFERENCE_CLEAN_575bd202e1d9b1c38b7486d282f843209423fa34_VCS_HEADER_LIBRARY_MISMATCH
void LALINFERENCE_VCS_LINK_CHECK(void);
#endif

#ifdef __cplusplus
}
#endif

#endif /* _LALINFERENCEVCSINFOHEADER_H */

/** \endcond */
