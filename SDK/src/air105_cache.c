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

#include "air105_cache.h"

void CACHE_Init(CACHE_TypeDef *Cache, CACHE_InitTypeDef *CACHE_InitStruct) {
    int i;

    if (CACHE_InitStruct->aes_enable == ENABLE) {
        assert_param(IS_CACHE_ENCRYPT_MODE(CACHE_InitStruct->encrypt_mode));

        for (i = 0; i < 5000; i++) {
            if (Cache->CACHE_CS & CACHE_IS_BUSY)  // cache正在从Flash中取指
            {
                continue;
            }
            break;
        }
        Cache->CACHE_CONFIG &= 0xFFFFFF00;  //关闭bypass

        Cache->CACHE_CS = (Cache->CACHE_CS & ~0x10000000) | (CACHE_InitStruct->algorithm << CHCHE_ALGORITHM_SET_POS);  //选择解密算法
        Cache->CACHE_CS = (Cache->CACHE_CS & ~0xFF) | CACHE_KEY_GEN;                                                   //密钥生成模式

        Cache->CACHE_I3 = CACHE_InitStruct->I[3];
        Cache->CACHE_I2 = CACHE_InitStruct->I[2];
        Cache->CACHE_I1 = CACHE_InitStruct->I[1];
        Cache->CACHE_I0 = CACHE_InitStruct->I[0];

        Cache->CACHE_K3 = CACHE_InitStruct->K[3];
        Cache->CACHE_K2 = CACHE_InitStruct->K[2];
        Cache->CACHE_K1 = CACHE_InitStruct->K[1];
        Cache->CACHE_K0 = CACHE_InitStruct->K[0];

        Cache->CACHE_CS |= CACHE_KEY_GEN_START;
        for (i = 0; i < 10000; i++) {
            if ((Cache->CACHE_CS & CACHE_KEY_GEN_START) == 0) {
                Cache->CACHE_CS &= 0x10000000;
                break;
            }
        }
        Cache->CACHE_CS &= 0x10000000;
        Cache->CACHE_CONFIG = (Cache->CACHE_CONFIG & ~0xFF00FFFF);

        if (CACHE_Encrypt_Mode_Zone == CACHE_InitStruct->encrypt_mode) {
            uint32_t saddr_align = CACHE_InitStruct->encrypt_saddr & ~(CACHE_PARTICLE_SIZE - 1);
            uint32_t eaddr_align = CACHE_InitStruct->encrypt_eaddr & ~(CACHE_PARTICLE_SIZE - 1);

            assert_param(IS_CACHE_ADDR_VALID(saddr_align));
            assert_param(IS_CACHE_ADDR_VALID(eaddr_align));
            assert_param(saddr_align <= eaddr_align);

            Cache->CACHE_SADDR = saddr_align;
            Cache->CACHE_EADDR = eaddr_align;
            Cache->CACHE_CONFIG = (Cache->CACHE_CONFIG & ~0xFF000000) | CACHE_ZONE_ENCRYPT;
        }
    } else {
        Cache->CACHE_CONFIG = (Cache->CACHE_CONFIG & ~0xFF00FFFF) | CACHE_AES_BYPASS;
    }
}

/*clean cache flash data/instructions*/
void CACHE_Clean(CACHE_TypeDef *Cache, CACHE_InitTypeDef *CACHE_InitStruct) {
    uint32_t i, address;
    address = (CACHE_InitStruct->Address & ~(CACHE_PARTICLE_SIZE - 1)) & CACHE_ADDRESS_MAX;

    for (i = 0; i < CACHE_InitStruct->size; i += CACHE_PARTICLE_SIZE) {
        Cache->CACHE_REF = (address + i);
        Cache->CACHE_REF |= CACHE_REFRESH;
        while ((Cache->CACHE_REF & CACHE_REFRESH))
            ;
    }
}

void CACHE_CleanAll(CACHE_TypeDef *Cache) {
    while (Cache->CACHE_CS & CACHE_IS_BUSY)
        ;

    Cache->CACHE_REF = CACHE_REFRESH_ALLTAG;
    Cache->CACHE_REF |= CACHE_REFRESH;
    while ((Cache->CACHE_REF & CACHE_REFRESH))
        ;
}
