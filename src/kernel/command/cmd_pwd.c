/*
 * kernel/command/cmd_pwd.c
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
#include <malloc.h>
#include <xboot/log.h>
#include <xboot/list.h>
#include <xboot/printk.h>
#include <xboot/initcall.h>
#include <shell/command.h>
#include <fs/vfs/vfs.h>
#include <fs/fsapi.h>


#if	defined(CONFIG_COMMAND_PWD) && (CONFIG_COMMAND_PWD > 0)

static x_s32 do_pwd(x_s32 argc, const x_s8 **argv)
{
	x_s8 cwd[MAX_PATH];

	if(getcwd((char *)cwd, sizeof(cwd)))
	{
		printk("%s\r\n", (char *)cwd);
		return 0;
	}

	return -1;
}

static struct command pwd_cmd = {
	.name		= "pwd",
	.func		= do_pwd,
	.desc		= "print the current working directory\r\n",
	.usage		= "pwd\r\n",
	.help		= "    print the current working directory.\r\n"
};

static __init void pwd_cmd_init(void)
{
	if(!command_register(&pwd_cmd))
		LOG_E("register 'pwd' command fail");
}

static __exit void pwd_cmd_exit(void)
{
	if(!command_unregister(&pwd_cmd))
		LOG_E("unregister 'pwd' command fail");
}

module_init(pwd_cmd_init, LEVEL_COMMAND);
module_exit(pwd_cmd_exit, LEVEL_COMMAND);

#endif