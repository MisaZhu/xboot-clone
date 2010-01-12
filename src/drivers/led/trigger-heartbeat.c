/*
 * drivers/led/trigger-heartbeat.c
 *
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
#include <malloc.h>
#include <xboot/printk.h>
#include <xboot/initcall.h>
#include <xboot/platform_device.h>
#include <time/tick.h>
#include <time/timer.h>
#include <led/led-trigger.h>


struct heartbeat_data {
	x_u32 phase;
	x_u32 period;
	struct timer_list timer;
};

static void heartbeat_function(x_u32 data)
{
	struct trigger * trigger = (struct trigger *)(data);
	struct heartbeat_data * hb = (struct heartbeat_data *)(trigger->priv);
	struct led * led = (struct led *)(trigger->led);

	x_u8 brightness = LED_BRIGHTNESS_OFF;
	x_u32 delay = 0;

	/* acts like an actual heart beat -- thump-thump-pause ... */
	switch(hb->phase)
	{
	case 0:
		hb->period = 1260 * get_system_hz() / 1000;
		delay = 70 * get_system_hz() / 1000;
		hb->phase++;
		brightness = LED_BRIGHTNESS_FULL;
		break;

	case 1:
		delay = hb->period / 4 - (70 * get_system_hz() / 1000);
		hb->phase++;
		brightness = LED_BRIGHTNESS_OFF;
		break;

	case 2:
		delay = 70 * get_system_hz() / 1000;
		hb->phase++;
		brightness = LED_BRIGHTNESS_FULL;
		break;

	default:
		delay = hb->period - hb->period / 4 - (70 * get_system_hz() / 1000);
		hb->phase = 0;
		brightness = LED_BRIGHTNESS_OFF;
		break;
	}

	led->set(brightness);
	mod_timer(&(hb->timer), jiffies + delay);
}

static void heartbeat_activate(struct trigger * trigger)
{
	struct heartbeat_data * hb = (struct heartbeat_data *)(trigger->priv);

	hb = malloc(sizeof(struct heartbeat_data));
	if(!hb)
		return;

	trigger->priv = hb;
	setup_timer(&hb->timer, heartbeat_function, (x_u32)trigger);
	hb->phase = 0;
	heartbeat_function(hb->timer.data);
}

static void heartbeat_deactivate(struct trigger * trigger)
{
	struct heartbeat_data * hb = (struct heartbeat_data *)(trigger->priv);

	if(hb)
	{
		del_timer(&(hb->timer));
		free(hb);
	}
}

static struct trigger heartbeat_trigger = {
	.name     		= "led-heartbeat",
	.activate 		= heartbeat_activate,
	.deactivate		= heartbeat_deactivate,
	.led			= NULL,
	.priv			= NULL,
};

static __init void heartbeat_trigger_init(void)
{
	struct led * led;

	led = (struct led *)platform_device_get_data(heartbeat_trigger.name);
	if(led && led->set)
	{
		if(led->init)
			(led->init)();

		heartbeat_trigger.led = led;
		trigger_register(&heartbeat_trigger);
	}
}

static __exit void heartbeat_trigger_exit(void)
{
	trigger_unregister(&heartbeat_trigger);
}

module_init(heartbeat_trigger_init, LEVEL_DRIVER);
module_exit(heartbeat_trigger_exit, LEVEL_DRIVER);