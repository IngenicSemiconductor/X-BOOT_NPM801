#ifndef __NAND_CONFIG_H
#define __NAND_CONFIG_H

/*
 * This file contains the nand configuration parameters for the cygnus board.
 */
/*-----------------------------------------------------------------------
 * NAND FLASH configuration
 */
#define CFG_NAND_BW8		1               /* Data bus width: 0-16bit, 1-8bit */
#define CFG_NAND_PAGE_SIZE      2048
#define CFG_NAND_ROW_CYCLE	3
#define CFG_NAND_BLOCK_SIZE	(128 << 10)	 /* NAND chip block size		*/
#define CFG_NAND_BADBLOCK_PAGE	0		/* NAND bad block was marked at this page in a block, starting from 0 */
#define CFG_NAND_OOB_SIZE              (CFG_NAND_PAGE_SIZE / 32)

#define X_DELAY_TRR		20
#define X_DELAY_TADL		300
#define X_DELAY_TWHR		120
#endif /* __NAND_CONFIG_H */
