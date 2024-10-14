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
#define LALSIMULATION_VCS_ID "5fd08c4d441c0684ae5ab3bffaad442240e30461"
#define LALSIMULATION_VCS_DATE "2024-08-20 15:10:39 +0000"
#define LALSIMULATION_VCS_BRANCH "None"
#define LALSIMULATION_VCS_TAG "lalsimulation-v6.0.0"
#define LALSIMULATION_VCS_AUTHOR "Adam Mercer <adam.mercer@ligo.org>"
#define LALSIMULATION_VCS_COMMITTER "Adam Mercer <adam.mercer@ligo.org>"
#define LALSIMULATION_VCS_CLEAN "CLEAN"
#define LALSIMULATION_VCS_STATUS "CLEAN: All modifications committed"

#if LALSIMULATION_VERSION_DEVEL != 0
/* VCS header/library mismatch link check function */
#define LALSIMULATION_VCS_LINK_CHECK LALSIMULATION_CLEAN_5fd08c4d441c0684ae5ab3bffaad442240e30461_VCS_HEADER_LIBRARY_MISMATCH
void LALSIMULATION_VCS_LINK_CHECK(void);
#endif

#ifdef __cplusplus
}
#endif

#endif /* _LALSIMULATIONVCSINFOHEADER_H */

/** \endcond */
