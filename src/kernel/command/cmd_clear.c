/*
 * kernel/command/cmd_clear.c
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
#include <terminal/terminal.h>
#include <terminal/curses.h>
#include <shell/command.h>


#if	defined(CONFIG_COMMAND_CLEAR) && (CONFIG_COMMAND_CLEAR > 0)

extern struct hlist_head stdout_list;
extern struct hlist_head stdin_list;

static x_s32 clear(x_s32 argc, const x_s8 **argv)
{
	struct terminal_stdout_list * list;
	struct hlist_node * pos;

	hlist_for_each_entry(list,  pos, &stdout_list, node)
	{
		terminal_clear_screen(list->term);
		terminal_cursor_home(list->term);
	}

	return 0;
}

static struct command clear_cmd = {
	.name		= "clear",
	.func		= clear,
	.desc		= "clear the terminal screen\r\n",
	.usage		= "clear\r\n",
	.help		= "    clear clears your screen if this is possible\r\n"
				  "    clear ignores any command line parameters that may be present.\r\n"
};

static __init void clear_cmd_init(void)
{
	if(!command_register(&clear_cmd))
		LOG_E("register 'clear' command fail");
}

static __exit void clear_cmd_exit(void)
{
	if(!command_unregister(&clear_cmd))
		LOG_E("unregister 'clear' command fail");
}

module_init(clear_cmd_init, LEVEL_COMMAND);
module_exit(clear_cmd_exit, LEVEL_COMMAND);

#endif