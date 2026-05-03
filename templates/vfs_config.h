/*
 * VFS Configuration for MH190X
 *
 * Supported filesystems:
 *   LFS:    littlefs by ARM Mbed (https://github.com/littlefs-project/littlefs)
 *   FATFS:  FatFs by ChaN (http://elm-chan.org/fsw/ff/00index_e.html)
 */

#define MAX_OPEN_FILES  4

#define USE_LFS         /* Enable littlefs                       */
#define USE_LFS_RAM     /* Use RAM disk                          */
#define USE_LFS_ROM     /* Use ROM disk (internal flash)         */
#define USE_FATFS       /* Enable FatFS                          */

