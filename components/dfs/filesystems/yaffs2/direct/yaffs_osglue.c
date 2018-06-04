/*
 * YAFFS: Yet Another Flash File System. A NAND-flash specific file system.
 *
 * Copyright (C) 2002-2011 Aleph One Ltd.
 *   for Toby Churchill Ltd and Brightstar Engineering
 *
 * Created by Charles Manning <charles@aleph1.co.uk>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */


#include "yaffscfg.h"
#include "../yaffs_guts.h"
#include "yaffsfs.h"
#include "../yaffs_trace.h"

#include <dfs.h>
#include <dfs_fs.h>
#include <dfs_file.h>

unsigned int yaffs_trace_mask = 0;

static int yaffsfs_lastError;

void yaffsfs_SetError(int err)
{
	//Do whatever to set error
	yaffsfs_lastError = err;
}

int yaffsfs_GetLastError(void)
{
	return yaffsfs_lastError;
}

void yaffsfs_Lock(void)
{
     
}

void yaffsfs_Unlock(void)
{
     
}

void yaffsfs_LockInit(void)
{
     
}
 

u32 yaffsfs_CurrentTime(void)
{
	return 0;
}

void *yaffsfs_malloc(size_t size)
{
	void *m = NULL;

	m = rt_malloc(size);
	
	return m;
}

void yaffsfs_free(void *ptr)
{
    rt_free(ptr);
}

void yaffsfs_OSInitialisation(void)
{
	yaffsfs_LockInit();
}

int yaffsfs_CheckMemRegion(const void *addr, size_t size, int write_request)
{
    return 0;
}

void yaffs_bug_fn(const char *file_name, int line_no)
{

}

size_t strnlen(const char* s, size_t m)
{
	int n;
	
	for (n = 0; n < m; n ++)
	{
	    if (s[n] == '\0')
		{
			n++;
		    break;
		}	
	}

    return n;
}

static int dfs_yaffs2_open(struct dfs_fd *file)
{
	int ret;

    ret = yaffs_open(file->path, file->flags, 0);
    if (ret >= 0)
	{
	    file->data = (void*)ret;
	}

	return ret;
}

static int dfs_yaffs2_mount(struct dfs_filesystem *fs, unsigned long rwflag, const void *data)
{
    return 0;
}

static const struct dfs_filesystem_ops _yaffs2 = 
{
    "yaffs2",
    DFS_FS_FLAG_DEFAULT,
    0,

    dfs_yaffs2_mount,
    RT_NULL,
    RT_NULL,
    RT_NULL,

    RT_NULL,
    0,
    RT_NULL,
};

int yaffs2_init(void)
{
    /* register rom file system */
    dfs_register(&_yaffs2);

    return 0;
}
INIT_COMPONENT_EXPORT(yaffs2_init);
