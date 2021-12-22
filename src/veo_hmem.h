/**
 * Copyright (C) 2021 NEC Corporation
 * This file is part of the AVEO.
 *
 * The AVEO is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation; either version 2.1
 * of the License, or (at your option) any later version.
 *
 * The AVEO is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with the AVEO; if not, see
 * <http://www.gnu.org/licenses/>.
 */

/**
 * @file veo_hmem.h
 */
#ifndef _VEO_HMEM_H_
#define _VEO_HMEM_H_

#ifdef __cplusplus
extern "C" {
#endif
int veo_is_ve_addr(const void *);
void *veo_get_hmem_addr(void *);
#ifdef __cplusplus
} // extern "C"
#endif
#endif
