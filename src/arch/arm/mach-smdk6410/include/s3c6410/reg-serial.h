#ifndef __S3C6410_REG_SERIAL_H__
#define __S3C6410_REG_SERIAL_H__

#include <xboot.h>

/* uart 0 */
#define S3C6410_ULCON0	 	 	(0x7F005000)
#define S3C6410_UCON0	 	 	(0x7F005004)
#define S3C6410_UFCON0	 	 	(0x7F005008)
#define S3C6410_UMON0	 	 	(0x7F00500C)
#define S3C6410_UTRSTAT0		(0x7F005010)
#define S3C6410_UERSTAT0		(0x7F005014)
#define S3C6410_UFSTAT0			(0x7F005018)
#define S3C6410_UMSTAT0			(0x7F00501C)
#define S3C6410_UTXH0			(0x7F005020)
#define S3C6410_URXH0			(0x7F005024)
#define S3C6410_UBRDIV0			(0x7F005028)
#define S3C6410_UDIVSLOT0		(0x7F00502C)
#define S3C6410_UINTP0			(0x7F005030)
#define S3C6410_UINTSP0			(0x7F005034)
#define S3C6410_UINTM0			(0x7F005038)


/* uart 1 */
#define S3C6410_ULCON1	 	 	(0x7F005400)
#define S3C6410_UCON1	 	 	(0x7F005404)
#define S3C6410_UFCON1	 	 	(0x7F005408)
#define S3C6410_UMON1	 	 	(0x7F00540C)
#define S3C6410_UTRSTAT1		(0x7F005410)
#define S3C6410_UERSTAT1		(0x7F005414)
#define S3C6410_UFSTAT1			(0x7F005418)
#define S3C6410_UMSTAT1			(0x7F00541C)
#define S3C6410_UTXH1			(0x7F005420)
#define S3C6410_URXH1			(0x7F005424)
#define S3C6410_UBRDIV1			(0x7F005428)
#define S3C6410_UDIVSLOT1		(0x7F00542C)
#define S3C6410_UINTP1			(0x7F005430)
#define S3C6410_UINTSP1			(0x7F005434)
#define S3C6410_UINTM1			(0x7F005438)


/* uart 2 */
#define S3C6410_ULCON2	 	 	(0x7F005800)
#define S3C6410_UCON2	 	 	(0x7F005804)
#define S3C6410_UFCON2	 	 	(0x7F005808)
#define S3C6410_UTRSTAT2		(0x7F005810)
#define S3C6410_UERSTAT2		(0x7F005814)
#define S3C6410_UFSTAT2			(0x7F005818)
#define S3C6410_UTXH2			(0x7F005820)
#define S3C6410_URXH2			(0x7F005824)
#define S3C6410_UBRDIV2			(0x7F005828)
#define S3C6410_UDIVSLOT2		(0x7F00582C)
#define S3C6410_UINTP2			(0x7F005830)
#define S3C6410_UINTSP2			(0x7F005834)
#define S3C6410_UINTM2			(0x7F005838)


/* uart 3 */
#define S3C6410_ULCON3	 	 	(0x7F005C00)
#define S3C6410_UCON3	 	 	(0x7F005C04)
#define S3C6410_UFCON3	 	 	(0x7F005C08)
#define S3C6410_UTRSTAT3		(0x7F005C10)
#define S3C6410_UERSTAT3		(0x7F005C14)
#define S3C6410_UFSTAT3			(0x7F005C18)
#define S3C6410_UTXH3			(0x7F005C20)
#define S3C6410_URXH3			(0x7F005C24)
#define S3C6410_UBRDIV3			(0x7F005C28)
#define S3C6410_UDIVSLOT3		(0x7F005C2C)
#define S3C6410_UINTP3			(0x7F005C30)
#define S3C6410_UINTSP3			(0x7F005C34)
#define S3C6410_UINTM3			(0x7F005C38)


#define S3C6410_UFSTAT_TXFULL	(1<<14)
#define S3C6410_UFSTAT_RXFULL	(1<<6)
#define S3C6410_UFSTAT_TXCOUNT	(0x3F<<8)
#define S3C6410_UFSTAT_RXCOUNT	(0x3F<<0)

#define S3C6410_UTRSTAT_TXE	  	(1<<2)
#define S3C6410_UTRSTAT_TXFE	(1<<1)
#define S3C6410_UTRSTAT_RXDR	(1<<0)

#define S3C6410_UERSTAT_OVERRUN	(1<<0)
#define S3C6410_UERSTAT_PARITY	(1<<1)
#define S3C6410_UERSTAT_FRAME	(1<<2)
#define S3C6410_UERSTAT_BREAK	(1<<3)

#define S3C6410_UMSTAT_CTS	  	(1<<0)
#define S3C6410_UMSTAT_DCTS		(1<<4)


#endif /* __S3C6410_REG_SERIAL_H__ */
