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

	struct frame_data dst_bufs[DST_BUFFER_COUNT];
	struct frame_data src_bufs[SRC_BUFFER_COUNT];
};

////////////////////////////////////////////////

typedef struct {
	int width;
	int height;
	int src_stride_factor;
	int dst_stride_factor;
	int format_type;
} CONTEXT;

typedef struct __EXE_CONTEXT{
	int dq_sync_timeline_fd;
	int q_sync_timeline_fd;
} EXE_CONTEXT;


typedef struct {
	int fence_fd;
	int fence_idx;
	unsigned long src_phys[3];
	unsigned char* src_virt[3];

	struct sync_pt *pt;
	struct sync_fence *fence;
} Q_BUF;

typedef struct {
	int fence_fd;
	int fence_idx;
	unsigned long dst_phys[3];
	unsigned char* dst_virt[3];

	struct sync_pt *pt;
	struct sync_fence *fence;
} DQ_BUF;

typedef struct {
	  DQ_BUF dst_buf[DST_BUFFER_POOL_COUNT];
} DST_BUF;

typedef struct {
	DST_BUF *dst_buf;
	int buf_cnt;
} DQ_SET;

struct deinter_context {
	unsigned int width;
	unsigned int height;
	unsigned int src_type;
	unsigned int src_field;
	unsigned int deinter_mode;
};

//////////////////////////////////////////////////////////////

typedef enum
{
	ACT_COPY = 0,
	ACT_DIRECT,
	ACT_DIRECT_FD,
	ACT_THREAD,
} ACT_MODE;

enum
{
	FRAME_SRC = 1,
	FRAME_DST
};

enum nx_deinter_src_field {
	FIELD_EVEN = 0,
	FIELD_ODD
};

enum nx_deinter_mode {
	SINGLE_FRAME = 0ul,
	DOUBLE_FRAME	
};

enum
{
	PLANE2 = 2,
	PLANE3,
};

int nx_deinter_open(void);
int nx_deinter_set_and_run(int deinter_fd, struct frame_data_info *frame);
void nx_deinter_close(int handle);

#if defined(__cplusplus)
}
#endif

#endif
