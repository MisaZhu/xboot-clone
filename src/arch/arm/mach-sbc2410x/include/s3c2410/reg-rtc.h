#ifndef __S3C2410_REG_RTC_H__
#define __S3C2410_REG_RTC_H__

#include <configs.h>
#include <default.h>

#if	defined(__LITTLE_ENDIAN)	/* little endian */

#define S3C2410_RTCCON	  		(0x57000040)
#define S3C2410_TICNT	  		(0x57000044)
#define S3C2410_RTCALM	  		(0x57000050)
#define S3C2410_ALMSEC	  		(0x57000054)
#define S3C2410_ALMMIN	  		(0x57000058)
#define S3C2410_ALMHOUR	  		(0x5700005c)
#define S3C2410_ALMDATE	  		(0x57000060)
#define S3C2410_ALMMON	  		(0x57000064)
#define S3C2410_ALMYEAR	  		(0x57000068)
#define S3C2410_RTCRST	  		(0x5700006c)
#define S3C2410_BCDSEC	  		(0x57000070)
#define S3C2410_BCDMIN	  		(0x57000074)
#define S3C2410_BCDHOUR	  		(0x57000078)
#define S3C2410_BCDDATE	  		(0x5700007c)
#define S3C2410_BCDDAY	  		(0x57000080)
#define S3C2410_BCDMON	  		(0x57000084)
#define S3C2410_BCDYEAR			(0x57000088)

#elif defined(__BIG_ENDIAN)		/* big endian */

#define S3C2410_RTCCON	  		(0x57000043)
#define S3C2410_TICNT	  		(0x57000047)
#define S3C2410_RTCALM	  		(0x57000053)
#define S3C2410_ALMSEC	  		(0x57000057)
#define S3C2410_ALMMIN	  		(0x5700005b)
#define S3C2410_ALMHOUR	  		(0x5700005f)
#define S3C2410_ALMDATE	  		(0x57000063)
#define S3C2410_ALMMON	  		(0x57000067)
#define S3C2410_ALMYEAR	  		(0x5700006b)
#define S3C2410_RTCRST	  		(0x5700006f)
#define S3C2410_BCDSEC	  		(0x57000073)
#define S3C2410_BCDMIN	  		(0x57000077)
#define S3C2410_BCDHOUR	  		(0x5700007b)
#define S3C2410_BCDDATE	  		(0x5700007f)
#define S3C2410_BCDDAY	  		(0x57000083)
#define S3C2410_BCDMON	  		(0x57000087)
#define S3C2410_BCDYEAR			(0x5700008b)

#endif

#endif /* __S3C2410_REG_RTC_H__ */