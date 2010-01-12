/*
 * kernel/fs/fs.c
 *
 * Copyright (c) 2007-2009  jianjun jiang <jerryjianjun@gmail.com>
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
#include <macros.h>
#include <malloc.h>
#include <hash.h>
#include <vsprintf.h>
#include <xboot/printk.h>
#include <xboot/initcall.h>
#include <xboot/list.h>
#include <xboot/proc.h>
#include <fs/fs.h>

/*
 * the list of filesystem
 */
static struct fs_list __fs_list = {
	.entry = {
		.next	= &(__fs_list.entry),
		.prev	= &(__fs_list.entry),
	},
};
struct fs_list * fs_list = &__fs_list;

/*
 * search filesystem by name
 */
struct filesystem * filesystem_search(const char * name)
{
	struct fs_list * list;
	struct list_head * pos;

	if(!name)
		return NULL;

	for(pos = (&fs_list->entry)->next; pos != (&fs_list->entry); pos = pos->next)
	{
		list = list_entry(pos, struct fs_list, entry);
		if(strcmp((x_s8*)list->fs->name, (const x_s8 *)name) == 0)
			return list->fs;
	}

	return NULL;
}

/*
 * register a filesystem into fs_list
 * return true is successed, otherwise is not.
 */
x_bool filesystem_register(struct filesystem * fs)
{
	struct fs_list * list;

	list = malloc(sizeof(struct fs_list));
	if(!list || !fs)
	{
		free(list);
		return FALSE;
	}

	if(!fs->name || filesystem_search(fs->name))
	{
		free(list);
		return FALSE;
	}

	list->fs = fs;
	list_add(&list->entry, &fs_list->entry);

	return TRUE;
}

/*
 * unregister platform from platform_list
 */
x_bool filesystem_unregister(struct filesystem * fs)
{
	struct fs_list * list;
	struct list_head * pos;

	if(!fs || !fs->name)
		return FALSE;

	for(pos = (&fs_list->entry)->next; pos != (&fs_list->entry); pos = pos->next)
	{
		list = list_entry(pos, struct fs_list, entry);
		if(list->fs == fs)
		{
			list_del(pos);
			free(list);
			return TRUE;
		}
	}

	return FALSE;
}

/*
 * filesystem proc interface
 */
static x_s32 filesystem_proc_read(x_u8 * buf, x_s32 offset, x_s32 count)
{
	struct fs_list * list;
	struct list_head * pos;
	x_s8 * p;
	x_s32 len = 0;

	if((p = malloc(SZ_4K)) == NULL)
		return 0;

	len += sprintf((x_s8 *)(p + len), (const x_s8 *)"[filesystem]");

	for(pos = (&fs_list->entry)->next; pos != (&fs_list->entry); pos = pos->next)
	{
		list = list_entry(pos, struct fs_list, entry);
		len += sprintf((x_s8 *)(p + len), (const x_s8 *)"\r\n %s", list->fs->name);
	}

	len -= offset;

	if(len < 0)
		len = 0;

	if(len > count)
		len = count;

	memcpy(buf, (x_u8 *)(p + offset), len);
	free(p);

	return len;
}

static struct proc filesystem_proc = {
	.name	= "filesystem",
	.read	= filesystem_proc_read,
};

/*
 * filesystem pure sync init
 */
static __init void filesystem_pure_sync_init(void)
{
	/* register filesystem proc interface */
	proc_register(&filesystem_proc);
}

static __exit void filesystem_pure_sync_exit(void)
{
	/* unregister filesystem proc interface */
	proc_unregister(&filesystem_proc);
}

module_init(filesystem_pure_sync_init, LEVEL_PURE_SYNC);
module_exit(filesystem_pure_sync_exit, LEVEL_PURE_SYNC);