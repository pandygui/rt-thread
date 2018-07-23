#include <rtthread.h>
#include <dfs_posix.h>
#include <stdlib.h>
#include <string.h>

static void usage(void)
{
    rt_kprintf("pin o [devname] [pin] [val]     -    pin ouput\n");
    rt_kprintf("pin ood [devname] [pin] [val]   -    pin ouput with OD\n");
    rt_kprintf("pin i [devname] [pin]           -    pin input\n");
    rt_kprintf("pin ipu [devname] [pin]         -    pin input with pullup\n");
    rt_kprintf("pin ipd [devname] [pin]         -    pin input with pulldown\n");
}

static void pin(int argc, char **argv)
{
    char *dn = "pin";
    char name[32] = {"/dev/"};
    int pin = 1;
    int val = 0;
    int fd;
    struct rt_device_pin_status ps;
    struct rt_device_pin_mode cfg;
    int iswrite = 0;

    if (argc < 2)
    {
        usage();
        return;
    }

    if (!strcmp("i", argv[1]))
    {
        cfg.mode = PIN_MODE_INPUT;
    }
    else if (!strcmp("o", argv[1]))
    {
        cfg.mode = PIN_MODE_OUTPUT;
        iswrite = 1;
    }
    else if (!strcmp("ood", argv[1]))
    {
        cfg.mode = PIN_MODE_OUTPUT_OD;
        iswrite = 1;
    }
    else if (!strcmp("ipu", argv[1]))
    {
        cfg.mode = PIN_MODE_INPUT_PULLUP;
    }
    else if (!strcmp("ipd", argv[1]))
    {
        cfg.mode = PIN_MODE_INPUT_PULLDOWN;
    }
    else
    {
        usage();
        return;
    }

    while (argc)
    {
        switch (argc)
        {
        case 3:
            dn = argv[argc-1];
            break;
        case 4:
            pin = atoi(argv[argc-1]);
            break;
        case 5:
            val = atoi(argv[argc-1]);
            break;
        }

        argc --;
    }

    strcat(name, dn);

    rt_kprintf("dev[%s], pin[%d]\n", name, pin);

    fd = open(name, O_RDWR, 0);
    if (fd < 0)
    {
        rt_kprintf("open fail\n");
        return;
    }
    cfg.pin = pin;
    ioctl(fd, 0, &cfg);

    ps.pin = pin;
    if (iswrite)
    {
        ps.status = val;
        write(fd, &ps, sizeof(ps));
        rt_kprintf("write: %d\n", ps.status);
    }
    else
    {
        read(fd, &ps, sizeof(ps));
        rt_kprintf("read: %d\n", ps.status);
    }

    close(fd);
}
MSH_CMD_EXPORT(pin, pin test);
