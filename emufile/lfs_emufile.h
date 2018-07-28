#ifndef LFS_EMUFILE_H
#define LFS_EMUFILE_H

#include "lfs.h"
#include "lfs_util.h"

#ifdef __cplusplus
extern "C"
{
#endif


// Config options

#if 0

#define LFS_EMUFILE_READ_SIZE  512
#define LFS_EMUFILE_PROG_SIZE  512
#define LFS_EMUFILE_ERASE_SIZE 2048
#define LFS_EMUFILE_BLOCKS     1024UL
#define LFS_EMUFILE_TOTAL_SIZE (LFS_EMUFILE_BLOCKS*LFS_EMUFILE_ERASE_SIZE)

#else

#define LFS_EMUFILE_READ_SIZE  512
#define LFS_EMUFILE_PROG_SIZE  512
#define LFS_EMUFILE_ERASE_SIZE 512
#define LFS_EMUFILE_BLOCKS     8192UL
#define LFS_EMUFILE_TOTAL_SIZE (LFS_EMUFILE_BLOCKS*LFS_EMUFILE_ERASE_SIZE)

#endif


// Create a block device using path for the directory to store blocks
int lfs_emufile_create(const struct lfs_config *cfg, const char *path);

// Clean up memory associated with emu block device
void lfs_emufile_destroy(const struct lfs_config *cfg);

// Read a block
int lfs_emufile_read(const struct lfs_config *cfg, lfs_block_t block,
        lfs_off_t off, void *buffer, lfs_size_t size);

// Program a block
//
// The block must have previously been erased.
int lfs_emufile_prog(const struct lfs_config *cfg, lfs_block_t block,
        lfs_off_t off, const void *buffer, lfs_size_t size);

// Erase a block
//
// A block must be erased before being programmed. The
// state of an erased block is undefined.
int lfs_emufile_erase(const struct lfs_config *cfg, lfs_block_t block);

// Sync the block device
int lfs_emufile_sync(const struct lfs_config *cfg);


#ifdef __cplusplus
} /* extern "C" */
#endif

#endif
