#ifndef __NAND_H__
#define __NAND_H__

#include <configs.h>
#include <default.h>
#include <string.h>
#include <xboot/list.h>
#include <mtd/nand/nand_ids.h>
#include <mtd/nand/nfc.h>

/*
 * nand flash commands
 */
enum
{
	/* standard */
	NAND_CMD_READ0			= 0x00,
	NAND_CMD_READ1			= 0x01,
	NAND_CMD_RNDOUT			= 0x05,
	NAND_CMD_PAGEPROG		= 0x10,
	NAND_CMD_READOOB		= 0x50,
	NAND_CMD_ERASE1			= 0x60,
	NAND_CMD_STATUS			= 0x70,
	NAND_CMD_STATUS_MULTI	= 0x71,
	NAND_CMD_SEQIN			= 0x80,
	NAND_CMD_RNDIN			= 0x85,
	NAND_CMD_READID			= 0x90,
	NAND_CMD_ERASE2			= 0xd0,
	NAND_CMD_RESET			= 0xff,

	/* extended */
	NAND_CMD_READSTART		= 0x30,
	NAND_CMD_RNDOUTSTART	= 0xE0,
	NAND_CMD_CACHEDPROG		= 0x15,
};

/* status bits */
enum
{
	NAND_STATUS_FAIL		= 0x01,
	NAND_STATUS_FAIL_N1		= 0x02,
	NAND_STATUS_TRUE_READY	= 0x20,
	NAND_STATUS_READY		= 0x40,
	NAND_STATUS_WP			= 0x80,
};

/* oob data formats */
enum oob_formats
{
	NAND_OOB_NONE			= 0x0,		/* no oob data at all */
	NAND_OOB_RAW			= 0x1,		/* raw oob data (16 bytes for 512b page sizes, 64 bytes for 2048b page sizes) */
	NAND_OOB_ONLY			= 0x2,		/* only oob data */
	NAND_OOB_SW_ECC			= 0x10,		/* when writing, use software ecc */
	NAND_OOB_HW_ECC			= 0x20, 	/* when writing, use hardware ecc */
	NAND_OOB_SW_ECC_KW		= 0x40, 	/* when writing, use marvell's kirkwood bootrom format */
	NAND_OOB_JFFS2			= 0x100,	/* when writing, use jffs2 oob layout */
	NAND_OOB_YAFFS2			= 0x100,	/* when writing, use yaffs2 oob layout */
};

/*
 * representation of a single nand block in a nand device.
 */
struct nand_block
{
	/* offset to the block */
	x_off offset;

	/* size of the block. */
	x_size size;

	/* true if the block has been erased */
	x_bool is_erased;

	/* true if the block is bad */
	x_bool is_bad;
};

/*
 * ecc layout structure
 */
struct nand_ecclayout
{
	x_s32 eccbytes;
	x_s32 eccpos[64];
	x_s32 oobavail;

	struct nand_oobfree	{
		x_s32 offset;
		x_s32 length;
	} oobfree[2];
};

/*
 * nand device of structure
 */
struct nand_device
{
	/* the name of nand flash */
	const char * name;

	/* nand manufacturer */
	struct nand_manufacturer * manufacturer;

	/* nand information */
	struct nand_info * device;

	/* bus width */
	x_s32 bus_width;

	/* address cycles */
	x_s32 address_cycles;

	/* page size */
	x_s32 page_size;

	/* erase size */
	x_s32 erase_size;

	/* raw access */
	x_bool use_raw;

	/* the number of blocks */
	x_s32 num_blocks;

	/* nand blocks */
	struct nand_block * blocks;

	/* the driver of nand flash controller */
	struct nfc * nfc;

	/* priv data */
	void * priv;
};

/*
 * the list of nand device
 */
struct nand_list
{
	struct nand_device * nand;
	struct list_head entry;
};


struct nand_device * search_nand_device(const char * name);
x_bool register_nand_device(struct nand_device * nand);
x_bool unregister_nand_device(struct nand_device * nand);

#endif /* __NAND_H__ */