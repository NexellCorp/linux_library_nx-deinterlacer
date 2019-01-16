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

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#include <sys/ioctl.h>
#include <sys/types.h>
#include <log/log.h>
#include "deinterlacer.h"
#include "nx-deinterlacer.h"

#define NO_ERROR	0

int nx_deinter_open(void)
{
	int deinter_fd;

	deinter_fd = open("/dev/nx-deinterlacer", O_RDWR);
	if (deinter_fd < 0) {
		ALOGE("failed to open deinterlacer:%d\n", deinter_fd);
		return -ENODEV;
	}

	return deinter_fd;
}

int nx_deinter_set_and_run(int deinter_fd, struct frame_data_info *frame)
{
	int ret = 1;

	ret = ioctl(deinter_fd, IOCTL_DEINTERLACE_SET_AND_RUN, frame);
	if (ret <= 0)
		return -EINVAL;

	return NO_ERROR;
}

void nx_deinter_close(int deinter_fd)
{
	if (deinter_fd)
		close(deinter_fd);
}
