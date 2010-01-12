#ifndef __REALVIEW_REG_SYSTEM_H__
#define __REALVIEW_REG_SYSTEM_H__

#include <configs.h>
#include <default.h>

/*
 * system registers
 */
#define REALVIEW_SYS_ID				(0x10000000 + 0x00)
#define REALVIEW_SYS_SW				(0x10000000 + 0x04)
#define REALVIEW_SYS_LED			(0x10000000 + 0x08)
#define REALVIEW_SYS_OSC0			(0x10000000 + 0x0c)
#define REALVIEW_SYS_OSC1			(0x10000000 + 0x10)
#define REALVIEW_SYS_OSC2			(0x10000000 + 0x14)
#define REALVIEW_SYS_OSC3			(0x10000000 + 0x18)
#define REALVIEW_SYS_OSC4			(0x10000000 + 0x1c)
#define REALVIEW_SYS_LOCK			(0x10000000 + 0x20)
#define REALVIEW_SYS_100HZ			(0x10000000 + 0x24)

/*
 * system controller
 */
#define REALVIEW_SYS_CTRL			(0x10001000 + 0x00)
#define REALVIEW_SYS_STATUS			(0x10001000 + 0x04)


#endif /* __REALVIEW_REG_SYSTEM_H__ */