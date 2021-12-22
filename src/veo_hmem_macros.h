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
 * @file veo_hmem_macros.h
 */
#ifndef _HMEM_MACROS_H_
#define _HMEM_MACROS_H_


#define VEO_MAX_HMEM_PROCS 16
#define IDENT_OFFSET_BITS 59 // bit 62:59 is used as VE process identifier.
#define VEADDR_MBITS    0x8000000000000000 // bit 63 VE virtual adress mask bits
#define PIDENT_MBITS    0x7800000000000000 // bit 62:59 VE process identifier mask bits
#define VEIDENT_MBITS   (VEADDR_MBITS | PIDENT_MBITS)
#define SET_VE_FLAG(addr)       (VEADDR_MBITS | (uint64_t)addr)
#define IS_VE(addr)             (VEADDR_MBITS & (uint64_t)addr)
#define VIRT_ADDR_VE(addr)      (~VEIDENT_MBITS & (uint64_t)addr)
#define SET_PROC_IDENT(addr, proc_ident) ((uint64_t)addr | (uint64_t)proc_ident \
                                        <<(int)IDENT_OFFSET_BITS)
#define GET_PROC_IDENT(addr)    (((uint64_t)addr & PIDENT_MBITS) \
                                >>(int)IDENT_OFFSET_BITS)

#endif
