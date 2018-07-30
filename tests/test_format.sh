#!/bin/bash
set -eu

echo "=== Formatting tests ==="
rm -rf blocks

echo "--- Basic formatting ---"
tests/test.py << TEST
    lfs_format(&lfs, &cfg) => 0;
TEST

echo "--- Basic mounting ---"
tests/test.py << TEST
    lfs_format(&lfs, &cfg) => 0;
TEST
tests/test.py << TEST
    lfs_mount(&lfs, &cfg) => 0;
    lfs_unmount(&lfs) => 0;
TEST

echo "--- Results ---"
tests/stats.py
