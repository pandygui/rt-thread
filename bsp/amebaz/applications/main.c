/*
 * File      : startup.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006, RT-Thread Develop Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://openlab.rt-thread.com/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2006-08-31     Bernard      first implementation
 * 2018-03-01     flyingcys    add realtek ameba
 */

#include <rthw.h>
#include <rtthread.h>

/**
 * @addtogroup ameba
 */

/*@{*/

int main(void)
{
  int *ad = (int*)0x80FF000;
    rt_kprintf("build time: %s %s\n", __DATE__, __TIME__);
    rt_kprintf("Hello RT-Thread!\n");
    
    dfs_mount("nor0", "/", "xipfs", 0, 0);
    rt_kprintf("xx %X\n", *ad);
    return 0;
}

/*@}*/
