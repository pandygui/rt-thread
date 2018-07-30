#include <rtthread.h>
#include <rtdevice.h>
#include <xipfs.h>

int drv_xipfs_init(void);

INIT_DEVICE_EXPORT(drv_xipfs_init);

#include <board.h>
#include "flash_api.h"

struct stmflash
{
    struct rt_device parent;
	struct xipfs_dev xip;
};
 
static struct stmflash _inflash;
static flash_t _flash;

#define W25Q16_SECTOR_SIZE    4096

static int flash_erase(uint32_t addr, uint32_t len)
{
	uint32_t s, l;
    
	s = addr - 0x8000000;

	for (l = 0; l < len;)
	{
		flash_erase_sector(&_flash, s);
		s += W25Q16_SECTOR_SIZE;
		l += W25Q16_SECTOR_SIZE;
	}
     
	return len;
}

static int flash_write(uint32_t addr, void *buf, uint32_t size)
{
    addr -= 0x8000000;
    flash_stream_write(&_flash, addr, size, buf);
	
    return size;
}

static int flash_mutex(void *userdata, int lock)
{
    return 0;
}

static const struct xipfs_nfops _ops =
{
    flash_erase,
    flash_write,
    flash_mutex
};

int drv_xipfs_init(void)
{
    _inflash.xip.start = 0x80F5000;
    _inflash.xip.blksize = 4*1024;
    _inflash.xip.nblk = 64;
    _inflash.xip.ops = &_ops;
    _inflash.parent.user_data = &_inflash.xip;
    _inflash.xip.writer = 0;

    return rt_device_register(&_inflash.parent, "nor0", 0);
}

