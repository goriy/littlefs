/*
 * Block device emulated on standard files
 *
 * Copyright (c) 2017, Arm Limited. All rights reserved.
 * SPDX-License-Identifier: BSD-3-Clause
 */
#include "emufile/lfs_emufile.h"

#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <stdbool.h>
#include <inttypes.h>

uint8_t Image[LFS_EMUFILE_TOTAL_SIZE];

// Block device emulated on existing filesystem
int lfs_emufile_create(const struct lfs_config *cfg, const char *path)
{
    (void)cfg;
    (void)path;
    FILE *o = fopen("blocks", "rb");
    if (o)  {
      fread(Image, 1, sizeof(Image), o);
      fclose(o);
    }
    else  {
      memset(Image, 0xFF, sizeof(Image));
    }
    return 0;
}

void lfs_emufile_destroy(const struct lfs_config *cfg) {
    (void)cfg;
}


int lfs_emufile_read(const struct lfs_config *cfg, lfs_block_t block,
        lfs_off_t off, void *buffer, lfs_size_t size) {

    uint8_t *data = buffer;

    // Check if read is valid
    assert(off  % cfg->read_size == 0);
    assert(size % cfg->read_size == 0);
    assert(block < cfg->block_count);

    // Zero out buffer for debugging
    //memset(data, 0, size);

    // Read data
    if (off != 0)  {
      //fprintf(stderr, "\033[33mread: block=%u, off=%u, size=%u\033[0m\n", block, off, size);
    }
    else  {
      //fprintf(stderr, "read: block=%u, off=%u, size=%u\n", block, off, size);
    }
    memcpy(data, Image + (block * LFS_EMUFILE_ERASE_SIZE) + off, size);

    return 0;
}

int lfs_emufile_prog(const struct lfs_config *cfg, lfs_block_t block,
        lfs_off_t off, const void *buffer, lfs_size_t size) {
    const uint8_t *data = buffer;

    // Check if write is valid
    assert(off  % cfg->prog_size == 0);
    assert(size % cfg->prog_size == 0);
    assert(block < cfg->block_count);

    if (off != 0)  {
      //fprintf(stderr, "\033[32mwrite: block=%u, off=%u, size=%u\033[0m\n", block, off, size);
    }
    else  {
      // Program data
      //fprintf(stderr, "write: block=%u, off=%u, size=%u\n", block, off, size);
    }
    memcpy(Image + (block * LFS_EMUFILE_ERASE_SIZE) + off, data, size);

    return 0;
}

int lfs_emufile_erase(const struct lfs_config *cfg, lfs_block_t block) {

    // Check if erase is valid
    assert(block < cfg->block_count);

    // Erase the block
    //fprintf(stderr, "erase: block=%u, size=%u\n", block, LFS_EMUFILE_ERASE_SIZE);
    memset(Image + (block * LFS_EMUFILE_ERASE_SIZE), 0xFF, LFS_EMUFILE_ERASE_SIZE);

    return 0;
}

int lfs_emufile_sync(const struct lfs_config *cfg) {
    (void)cfg;
    //fprintf(stderr, "sync:\n");
    FILE *o = fopen("blocks", "wb");
    if (o)  {
      fwrite(Image, 1, sizeof(Image), o);
      fclose(o);
    }
    return 0;
}
