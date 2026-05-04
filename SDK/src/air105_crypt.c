#include "air105_crypt.h"

/*
 * MH1903 Hardware Crypto Driver
 *
 * Uses the symmetric crypto engine at CRYPT (0x40003000) and the
 * asymmetric PKE engine at 0x40004000.
 *
 * All data is transferred big-endian (network byte order) to match
 * the DesignWare crypto IP convention. Register offsets for key/IV/data
 * buffers are confirmed from bootROM / cryptolib RE.
 */

/* ---- Low-level helpers ---- */

void CRYPT_WaitBusy(void)
{
    while (CRYPT->STATUS & CRYPT_STATUS_BUSY);
}

FlagStatus CRYPT_IsBusy(void)
{
    return (CRYPT->STATUS & CRYPT_STATUS_BUSY) ? SET : RESET;
}

void CRYPT_ClearIT(void)
{
    CRYPT->ITCLR = 1;
}

void CRYPT_LoadBlock(const uint8_t *src, volatile uint32_t *dst, uint32_t words)
{
    uint32_t i;
    for (i = 0; i < words; i++) {
        dst[i] = ((uint32_t)src[4 * i + 0] << 24)
               | ((uint32_t)src[4 * i + 1] << 16)
               | ((uint32_t)src[4 * i + 2] <<  8)
               | ((uint32_t)src[4 * i + 3] <<  0);
    }
}

void CRYPT_ReadBlock(volatile uint32_t *src, uint8_t *dst, uint32_t words)
{
    uint32_t i, v;
    for (i = 0; i < words; i++) {
        v = src[i];
        dst[4 * i + 0] = (uint8_t)(v >> 24);
        dst[4 * i + 1] = (uint8_t)(v >> 16);
        dst[4 * i + 2] = (uint8_t)(v >>  8);
        dst[4 * i + 3] = (uint8_t)(v >>  0);
    }
}

void CRYPT_Start(uint32_t ctrl_word)
{
    CRYPT_WaitBusy();
    CRYPT->CTRL = ctrl_word;
}

/* ---- AES ---- */

void AES_SetKey(const uint8_t *key, uint32_t key_size)
{
    uint32_t words = key_size / 4;
    CRYPT_LoadBlock(key, &CRYPT->DATA[4],  words);

    if      (key_size == 16) CRYPT->CFG = (CRYPT->CFG & ~0x03U) | CRYPT_AES_KEY_128;
    else if (key_size == 24) CRYPT->CFG = (CRYPT->CFG & ~0x03U) | CRYPT_AES_KEY_192;
    else                     CRYPT->CFG = (CRYPT->CFG & ~0x03U) | CRYPT_AES_KEY_256;
}

void AES_SetIV(const uint8_t *iv)
{
    CRYPT_LoadBlock(iv, &CRYPT->DATA[20], 4);
}

void AES_EncryptECB(const uint8_t *in, uint8_t *out)
{
    CRYPT_WaitBusy();
    CRYPT->CFG = (CRYPT->CFG & ~0x1CU) | CRYPT_MODE_ECB;
    CRYPT_LoadBlock(in, &CRYPT->DATA[0], 4);
    CRYPT->CTRL = CRYPT_ALGO_AES | CRYPT_DIR_ENCRYPT | CRYPT_START;
    CRYPT_WaitBusy();
    CRYPT_ReadBlock(&CRYPT->DATA[0], out, 4);
}

void AES_DecryptECB(const uint8_t *in, uint8_t *out)
{
    CRYPT_WaitBusy();
    CRYPT->CFG = (CRYPT->CFG & ~0x1CU) | CRYPT_MODE_ECB;
    CRYPT_LoadBlock(in, &CRYPT->DATA[0], 4);
    CRYPT->CTRL = CRYPT_ALGO_AES | CRYPT_DIR_DECRYPT | CRYPT_START;
    CRYPT_WaitBusy();
    CRYPT_ReadBlock(&CRYPT->DATA[0], out, 4);
}

void AES_EncryptCBC(const uint8_t *in, uint8_t *out, uint32_t block_count)
{
    uint32_t i;
    CRYPT_WaitBusy();
    CRYPT->CFG = (CRYPT->CFG & ~0x1CU) | CRYPT_MODE_CBC;

    for (i = 0; i < block_count; i++) {
        CRYPT_LoadBlock(in + i * AES_BLOCK_SIZE, &CRYPT->DATA[0], 4);
        CRYPT->CTRL = CRYPT_ALGO_AES | CRYPT_DIR_ENCRYPT | CRYPT_START;
        CRYPT_WaitBusy();
        CRYPT_ReadBlock(&CRYPT->DATA[0], out + i * AES_BLOCK_SIZE, 4);
    }
}

void AES_DecryptCBC(const uint8_t *in, uint8_t *out, uint32_t block_count)
{
    uint32_t i;
    CRYPT_WaitBusy();
    CRYPT->CFG = (CRYPT->CFG & ~0x1CU) | CRYPT_MODE_CBC;

    for (i = 0; i < block_count; i++) {
        CRYPT_LoadBlock(in + i * AES_BLOCK_SIZE, &CRYPT->DATA[0], 4);
        CRYPT->CTRL = CRYPT_ALGO_AES | CRYPT_DIR_DECRYPT | CRYPT_START;
        CRYPT_WaitBusy();
        CRYPT_ReadBlock(&CRYPT->DATA[0], out + i * AES_BLOCK_SIZE, 4);
    }
}

void AES_EncryptCTR(const uint8_t *in, uint8_t *out, uint32_t block_count)
{
    uint32_t i;
    CRYPT_WaitBusy();
    CRYPT->CFG = (CRYPT->CFG & ~0x1CU) | CRYPT_MODE_CTR;

    for (i = 0; i < block_count; i++) {
        CRYPT_LoadBlock(in + i * AES_BLOCK_SIZE, &CRYPT->DATA[0], 4);
        CRYPT->CTRL = CRYPT_ALGO_AES | CRYPT_DIR_ENCRYPT | CRYPT_START;
        CRYPT_WaitBusy();
        CRYPT_ReadBlock(&CRYPT->DATA[0], out + i * AES_BLOCK_SIZE, 4);
    }
}

/* ---- DES / 3DES ---- */

void DES_SetKey(const uint8_t *key)
{
    CRYPT->CFG = (CRYPT->CFG & ~0x60U) | CRYPT_DES_SINGLE;
    CRYPT_LoadBlock(key, &CRYPT->DATA[7], 2);
}

void TDES_SetKey2(const uint8_t *key)
{
    CRYPT->CFG = (CRYPT->CFG & ~0x60U) | CRYPT_DES_TRIPLE_2KEY;
    CRYPT_LoadBlock(key, &CRYPT->DATA[7], 4);
}

void TDES_SetKey3(const uint8_t *key)
{
    CRYPT->CFG = (CRYPT->CFG & ~0x60U) | CRYPT_DES_TRIPLE_3KEY;
    CRYPT_LoadBlock(key, &CRYPT->DATA[7], 6);
}

void TDES_SetIV(const uint8_t *iv)
{
    CRYPT_LoadBlock(iv, &CRYPT->DATA[3], 2);
}

void DES_EncryptECB(const uint8_t *in, uint8_t *out)
{
    CRYPT_WaitBusy();
    CRYPT->CFG = (CRYPT->CFG & ~0x1CU) | CRYPT_MODE_ECB;
    CRYPT_LoadBlock(in, &CRYPT->DATA[5], 2);
    CRYPT->CTRL = CRYPT_ALGO_DES | CRYPT_DIR_ENCRYPT | CRYPT_START;
    CRYPT_WaitBusy();
    CRYPT_ReadBlock(&CRYPT->DATA[5], out, 2);
}

void DES_DecryptECB(const uint8_t *in, uint8_t *out)
{
    CRYPT_WaitBusy();
    CRYPT->CFG = (CRYPT->CFG & ~0x1CU) | CRYPT_MODE_ECB;
    CRYPT_LoadBlock(in, &CRYPT->DATA[5], 2);
    CRYPT->CTRL = CRYPT_ALGO_DES | CRYPT_DIR_DECRYPT | CRYPT_START;
    CRYPT_WaitBusy();
    CRYPT_ReadBlock(&CRYPT->DATA[5], out, 2);
}

void TDES_EncryptCBC(const uint8_t *in, uint8_t *out, uint32_t block_count)
{
    uint32_t i;
    CRYPT_WaitBusy();
    CRYPT->CFG = (CRYPT->CFG & ~0x1CU) | CRYPT_MODE_CBC;

    for (i = 0; i < block_count; i++) {
        CRYPT_LoadBlock(in + i * DES_BLOCK_SIZE, &CRYPT->DATA[5], 2);
        CRYPT->CTRL = CRYPT_ALGO_DES | CRYPT_DIR_ENCRYPT | CRYPT_START;
        CRYPT_WaitBusy();
        CRYPT_ReadBlock(&CRYPT->DATA[5], out + i * DES_BLOCK_SIZE, 2);
    }
}

void TDES_DecryptCBC(const uint8_t *in, uint8_t *out, uint32_t block_count)
{
    uint32_t i;
    CRYPT_WaitBusy();
    CRYPT->CFG = (CRYPT->CFG & ~0x1CU) | CRYPT_MODE_CBC;

    for (i = 0; i < block_count; i++) {
        CRYPT_LoadBlock(in + i * DES_BLOCK_SIZE, &CRYPT->DATA[5], 2);
        CRYPT->CTRL = CRYPT_ALGO_DES | CRYPT_DIR_DECRYPT | CRYPT_START;
        CRYPT_WaitBusy();
        CRYPT_ReadBlock(&CRYPT->DATA[5], out + i * DES_BLOCK_SIZE, 2);
    }
}

/* ---- SHA ---- */

/*
 * SHA mode constants are confirmed from bootROM RE (CTRL register bits 4-6).
 * The hardware handles padding and finalization automatically via the START
 * flag sequence — first write triggers init, subsequent writes feed data,
 * writing CTRL with bit 7 (SHA_FINAL) set triggers finalization.
 */

#define CRYPT_SHA_FINAL          ((uint32_t)0x00000080)
#define CRYPT_SHA_MODE_SHA1      ((uint32_t)0x00000010)
#define CRYPT_SHA_MODE_SHA256    ((uint32_t)0x00000030)

static void sha_do_init(uint32_t mode)
{
    CRYPT_WaitBusy();
    CRYPT->CTRL = CRYPT_ALGO_SHA | mode | CRYPT_START;
}

static void sha_do_block(const uint8_t *data, uint32_t byte_len, uint8_t final)
{
    uint32_t i, ctrl;
    uint8_t  block[64];

    while (byte_len >= 64) {
        CRYPT_WaitBusy();
        CRYPT_LoadBlock(data, &CRYPT->DATA[0], 16);
        CRYPT->CTRL = CRYPT_ALGO_SHA | CRYPT_SHA_MODE_SHA256 | CRYPT_START;
        CRYPT_WaitBusy();
        data     += 64;
        byte_len -= 64;
    }

    if (!final || byte_len == 0)
        return;

    for (i = 0; i < byte_len; i++)
        block[i] = data[i];
    block[byte_len] = 0x80;
    for (i = byte_len + 1; i < 64; i++)
        block[i] = 0x00;

    CRYPT_WaitBusy();
    CRYPT_LoadBlock(block, &CRYPT->DATA[0], 16);
    ctrl = CRYPT_ALGO_SHA | CRYPT_SHA_MODE_SHA256 | CRYPT_SHA_FINAL | CRYPT_START;
    CRYPT->CTRL = ctrl;
    CRYPT_WaitBusy();
}

void SHA1_Init(void)
{
    sha_do_init(CRYPT_SHA_MODE_SHA1);
}

void SHA1_Update(const uint8_t *data, uint32_t byte_len)
{
    sha_do_block(data, byte_len, 0);
}

void SHA1_Final(uint8_t *digest)
{
    sha_do_block(NULL, 0, 1);
    CRYPT_WaitBusy();
    CRYPT_ReadBlock(&CRYPT->DATA[0], digest, 5);
}

void SHA256_Init(void)
{
    sha_do_init(CRYPT_SHA_MODE_SHA256);
}

void SHA256_Update(const uint8_t *data, uint32_t byte_len)
{
    sha_do_block(data, byte_len, 0);
}

void SHA256_Final(uint8_t *digest)
{
    sha_do_block(NULL, 0, 1);
    CRYPT_WaitBusy();
    CRYPT_ReadBlock(&CRYPT->DATA[0], digest, 8);
}

/* ---- PKE (Asymmetric) ---- */

void PKE_WaitBusy(void)
{
    while (PKE->STATUS & 1);
}

FlagStatus PKE_IsBusy(void)
{
    return (PKE->STATUS & 1) ? SET : RESET;
}

void PKE_Start(uint32_t cmd)
{
    PKE_WaitBusy();
    PKE->CMD   = cmd;
    PKE->CTRL |= CRYPT_START;
    PKE_WaitBusy();
}
