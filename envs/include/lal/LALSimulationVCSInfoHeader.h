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
 * LALSimulationVCSInfo.h - LALSimulation VCS Information Header
 */

/** \cond DONT_DOXYGEN */

#ifndef _LALSIMULATIONVCSINFOHEADER_H
#define _LALSIMULATIONVCSINFOHEADER_H

#include <lal/LALVCSInfoType.h>
#include <lal/LALSimulationVCSInfo.h>
#include <lal/LALSimulationConfig.h>

#ifdef __cplusplus
extern "C" {
#endif

/* VCS information */
#define LALSIMULATION_VCS_ID "57c31779c344c6abf3c1d294bab00dd58ed17875"
#define LALSIMULATION_VCS_DATE "2024-03-22 17:24:31 +0000"
#define LALSIMULATION_VCS_BRANCH "None"
#define LALSIMULATION_VCS_TAG "lalsimulation-v5.4.0"
#define LALSIMULATION_VCS_AUTHOR "Duncan Macleod <duncan.macleod@ligo.org>"
#define LALSIMULATION_VCS_COMMITTER "Duncan Macleod <duncan.macleod@ligo.org>"
#define LALSIMULATION_VCS_CLEAN "CLEAN"
#define LALSIMULATION_VCS_STATUS "CLEAN: All modifications committed"

#if LALSIMULATION_VERSION_DEVEL != 0
/* VCS header/library mismatch link check function */
#define LALSIMULATION_VCS_LINK_CHECK LALSIMULATION_CLEAN_57c31779c344c6abf3c1d294bab00dd58ed17875_VCS_HEADER_LIBRARY_MISMATCH
void LALSIMULATION_VCS_LINK_CHECK(void);
#endif

#ifdef __cplusplus
}
#endif

#endif /* _LALSIMULATIONVCSINFOHEADER_H */

/** \endcond */
