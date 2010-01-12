/*
 * kernel/command/cmd_memtest.c
 *
 *
 * Copyright (c) 2007-2008  jianjun jiang <jjjstudio@gmail.com>
 * website: http://xboot.org
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 */

#include <configs.h>
#include <default.h>
#include <types.h>
#include <string.h>
#include <version.h>
#include <vsprintf.h>
#include <time/delay.h>
#include <xboot/log.h>
#include <xboot/printk.h>
#include <xboot/initcall.h>
#include <xboot/machine.h>
#include <shell/ctrlc.h>
#include <shell/command.h>


#if	defined(CONFIG_COMMAND_MEMTEST) && (CONFIG_COMMAND_MEMTEST > 0)

static x_s32 memtest(x_s32 argc, const x_s8 **argv)
{
	x_u32 base, size;
	x_u32 * start, * end;
	x_u32 walker, readback, *i;
	x_s32 errcnt = 0;

	if(argc == 1)
	{
		base = 0;
		base = base & (~0x00000003);
		size = 0;
		size = size & (~0x00000003);
	}
	else if(argc == 3)
	{
		base = simple_strtou32(argv[1], NULL, 0);
		base = base & (~0x00000003);
		size = simple_strtou32(argv[2], NULL, 0);
		size = size & (~0x00000003);
	}
	else
	{
		printk("usage:\r\n    memtest <address> <size>\r\n");
		return (-1);
	}

	printk("testing 0x%08lx .. 0x%08lx\r\n", base, base + size);
	start = (x_u32 *)base;

	if(size == 0)
	{
		printk("not do any testing\r\n");
		return 0;
	}

	/* walker one test */
	walker = 0x1;
	end = start + 32;
	for(i = start; i < end; i++)
	{
		*i = walker;
		walker <<= 1;
	}

	walker = 0x1;
	for(i = start; i < end; i++)
	{
		readback = *i;
		if(readback != walker)
		{
			errcnt++;
			printk("error at 0x%08lx: read 0x%lx expected x%lx\r\n", (x_u32)i, readback, walker);
			break;
		}
		walker <<= 1;
	}

	/* address in address test */
	end = (x_u32 *)((x_u32)start + size);
	for(i = start; i < end; i++)
	{
		if(((x_u32)i & 0x3ffff) == 0)
		{
			if(ctrlc())
				return -1;
		}

		*i = (x_u32)i;
	}

	for(i = start; i < end; i++)
	{
		if(((x_u32)i & 0x3ffff) == 0)
		{
			if(ctrlc())
				return -1;
		}

		readback = *i;
		if(readback != (x_u32)i)
		{
			errcnt++;
			printk("error at 0x%08lx: read 0x%08lx expected 0x%08lx\r\n", (x_u32)i, readback, (x_u32)i);
			break;
		}
	}

	if(errcnt > 0)
		printk("found %d errors\r\n", errcnt);
	else
		printk("no found any errors\r\n");

	return 0;
}

static struct command memtest_cmd = {
	.name		= "memtest",
	.func		= memtest,
	.desc		= "system memory testing\r\n",
	.usage		= "memtest <address> <size>\r\n",
	.help		= "    checking system memory\r\n"
				  "    default for auto checking memory\r\n"
};

static __init void memtest_cmd_init(void)
{
	if(!command_register(&memtest_cmd))
		LOG_E("register 'memtest' command fail");
}

static __exit void memtest_cmd_exit(void)
{
	if(!command_unregister(&memtest_cmd))
		LOG_E("unregister 'memtest' command fail");
}

module_init(memtest_cmd_init, LEVEL_COMMAND);
module_exit(memtest_cmd_exit, LEVEL_COMMAND);

#endif