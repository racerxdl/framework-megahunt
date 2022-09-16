////////////////////////////////////////////////////////////////////////////////////////
//
//      2022 Lucas Teske
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
////////////////////////////////////////////////////////////////////////////////////////

#ifndef _MEGAHUNT_H
#define _MEGAHUNT_H
#ifdef __cplusplus
extern "C" {
#endif

#include <assert.h>
#include <ctype.h>
#include <errno.h>
#include <fcntl.h>
#include <limits.h>
#include <math.h>
#include <reent.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include "air105.h"
#include "air105_conf.h"

#define PRE_INIT_FUNC(F) static __attribute__((section(".preinit_array"))) void (*__##F)(void) = F
#define INLINE inline __attribute__((always_inline))

#define ENTER_CRITICAL() uint32_t _prim = save_and_disable_interrupts()
#define EXIT_CRITICAL() restore_interrupts(_prim)

#define MUTEX_PTYPE (mutex_t *)
#define MUTEX_INIT(pM)                           \
    pM = MUTEX_PTYPE calloc(1, sizeof(mutex_t)); \
    mutex_init(pM)
#define MUTEX_LOCK(pM) mutex_enter_blocking(MUTEX_PTYPE pM)
#define MUTEX_UNLOCK(pM) mutex_exit(MUTEX_PTYPE pM)

unsigned int strhash(const void *p);

#ifdef __cplusplus
}
#endif
#endif  //_MEGAHUNT_H