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

#ifndef _LALBURSTVCSINFO_H
#define _LALBURSTVCSINFO_H

#include <lal/LALVCSInfoType.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \defgroup LALBurstVCSInfo_h Header LALBurstVCSInfo.h
 * \ingroup lalburst_general
 * \brief VCS and build information for LALBurst
 */
/*@{*/

/** VCS and build information for LALBurst */
extern const LALVCSInfo lalBurstVCSInfo;

/** Identable VCS and build information for LALBurst */
extern const LALVCSInfo lalBurstVCSIdentInfo;

/** <tt>NULL</tt>-terminated list of VCS and build information for LALBurst and its dependencies */
extern const LALVCSInfoList lalBurstVCSInfoList;

/*@}*/

#ifdef __cplusplus
}
#endif

#endif /* _LALBURSTVCSINFO_H */
