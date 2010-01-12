#ifndef __REALVIEW_REG_TIMER_H__
#define __REALVIEW_REG_TIMER_H__

#include <configs.h>
#include <default.h>

/*
 * timer 0
 */
#define REALVIEW_T0_LOAD			(0x10011000 + 0x00)
#define REALVIEW_T0_VALUE			(0x10011000 + 0x04)
#define REALVIEW_T0_CTRL			(0x10011000 + 0x08)
#define REALVIEW_T0_ICLR			(0x10011000 + 0x0c)
#define REALVIEW_T0_RIS				(0x10011000 + 0x10)
#define REALVIEW_T0_MIS				(0x10011000 + 0x14)
#define REALVIEW_T0_BGLOAD			(0x10011000 + 0x18)

/*
 * timer 1
 */
#define REALVIEW_T1_LOAD			(0x10011000 + 0x20)
#define REALVIEW_T1_VALUE			(0x10011000 + 0x24)
#define REALVIEW_T1_CTRL			(0x10011000 + 0x28)
#define REALVIEW_T1_ICLR			(0x10011000 + 0x2c)
#define REALVIEW_T1_RIS				(0x10011000 + 0x30)
#define REALVIEW_T1_MIS				(0x10011000 + 0x34)
#define REALVIEW_T1_BGLOAD			(0x10011000 + 0x38)

/*
 * timer 2
 */
#define REALVIEW_T2_LOAD			(0x10012000 + 0x00)
#define REALVIEW_T2_VALUE			(0x10012000 + 0x04)
#define REALVIEW_T2_CTRL			(0x10012000 + 0x08)
#define REALVIEW_T2_ICLR			(0x10012000 + 0x0c)
#define REALVIEW_T2_RIS				(0x10012000 + 0x10)
#define REALVIEW_T2_MIS				(0x10012000 + 0x14)
#define REALVIEW_T2_BGLOAD			(0x10012000 + 0x18)

/*
 * timer 3
 */
#define REALVIEW_T3_LOAD			(0x10012000 + 0x20)
#define REALVIEW_T3_VALUE			(0x10012000 + 0x24)
#define REALVIEW_T3_CTRL			(0x10012000 + 0x28)
#define REALVIEW_T3_ICLR			(0x10012000 + 0x2c)
#define REALVIEW_T3_RIS				(0x10012000 + 0x30)
#define REALVIEW_T3_MIS				(0x10012000 + 0x34)
#define REALVIEW_T3_BGLOAD			(0x10012000 + 0x38)


#define REALVIEW_TC_ONESHOT			(1 << 0)
#define REALVIEW_TC_32BIT			(1 << 1)
#define REALVIEW_TC_DIV1			(0 << 2)
#define REALVIEW_TC_DIV16			(1 << 2)
#define REALVIEW_TC_DIV256			(2 << 2)
#define REALVIEW_TC_IE				(1 << 5)
#define REALVIEW_TC_PERIODIC		(1 << 6)
#define REALVIEW_TC_ENABLE			(1 << 7)


#endif /* __REALVIEW_REG_TIMER_H__ */