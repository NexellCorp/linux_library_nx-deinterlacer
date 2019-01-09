/*
 * Copyright (C) 2018  Nexell Co., Ltd.
 * Author: Hyejung, Kwon <cjscld15@nexell.co.kr>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef __NX_DEINTERLACER_H
#define __NX_DEINTERLACER_H

#if defined(__cplusplus)
extern "C" {
#endif

#define MAX_PLANE_NUM   3

#define MAX_BUFFER_PLANES	3

#define SRC_BUFFER_COUNT  3
#define DST_BUFFER_COUNT  1

#define DST_BUFFER_POOL_COUNT	4

struct frame_data {
	int frame_num;
	int plane_num;
	int frame_type;
	int frame_factor;

	union {
		struct {
			unsigned char *virt[MAX_BUFFER_PLANES];
			unsigned long sizes[MAX_BUFFER_PLANES];
			unsigned long src_stride[MAX_BUFFER_PLANES];
			unsigned long dst_stride[MAX_BUFFER_PLANES];

			int fds[MAX_BUFFER_PLANES];
			unsigned long phys[MAX_BUFFER_PLANES];
		}plane3;
		struct {
			unsigned char *virt[MAX_BUFFER_PLANES-1];
			unsigned long sizes[MAX_BUFFER_PLANES-1];
			unsigned long src_stride[MAX_BUFFER_PLANES-1];
			unsigned long dst_stride[MAX_BUFFER_PLANES-1];

			int fds[MAX_BUFFER_PLANES-1];
			unsigned long phys[MAX_BUFFER_PLANES-1];
		}plane2;
	};
};

struct frame_data_info {
	int command;
	int width;
	int height;
	int plane_mode;
	int src_type;                                      
	int src_field; 

	struct frame_data dst_bufs[DST_BUFFER_COUNT];
	struct frame_data src_bufs[SRC_BUFFER_COUNT];
};

////////////////////////////////////////////////

enum nx_deinter_src_type {                                                      
	SRC_TYPE_MIPI = 0ul,                                                    
	SRC_TYPE_PARALLEL                                                       
};                                                                              

enum nx_deinter_src_field {
	FIELD_EVEN = 0,
	FIELD_ODD
};

enum
{
	FRAME_SRC = 1,
	FRAME_DST
};

enum
{
	PLANE2 = 1,
	PLANE3,
};

enum nx_deinter_mode {
	SINGLE_FRAME = 0ul,
	DOUBLE_FRAME
};

int nx_deinter_open(void);
int nx_deinter_set_and_run(int deinter_fd, struct frame_data_info *frame);
void nx_deinter_close(int handle);

#if defined(__cplusplus)
}
#endif

#endif
