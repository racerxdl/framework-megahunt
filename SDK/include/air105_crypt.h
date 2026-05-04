#ifndef __AIR105_CRYPT_H
#define __AIR105_CRYPT_H

#ifdef __cplusplus
extern "C" {
#endif

#include "air105.h"

/*
 * MH1903 Hardware Crypto Engine (CRYPT, 0x40003000)
 *
 * Register map is documented via reverse engineering.
 * Bit-level definitions marked (*) are provisional and may need tuning
 * against silicon validation. The base+offset register assignments are
 * confirmed from bootROM / crypto library analysis.
 */

/* CRYPT->CTRL — Algorithm ID (bits 0-3) */
#define CRYPT_ALGO_DES           ((uint32_t)0x00000000)
#define CRYPT_ALGO_AES           ((uint32_t)0x00000001)
#define CRYPT_ALGO_SHA           ((uint32_t)0x00000002)
#define CRYPT_ALGO_SM3           ((uint32_t)0x00000003)
#define CRYPT_ALGO_SM4           ((uint32_t)0x00000004)
#define CRYPT_ALGO_SM1           ((uint32_t)0x00000005)
#define CRYPT_ALGO_SM7           ((uint32_t)0x00000006)

/* CRYPT->CTRL — Direction (* bit 4) */
#define CRYPT_DIR_ENCRYPT        ((uint32_t)0x00000000)
#define CRYPT_DIR_DECRYPT        ((uint32_t)0x00000010)

/* CRYPT->CTRL — Start trigger (* bit 31) */
#define CRYPT_START              ((uint32_t)0x80000000)

/* CRYPT->CFG — AES key size (* bits 0-1) */
#define CRYPT_AES_KEY_128        ((uint32_t)0x00000000)
#define CRYPT_AES_KEY_192        ((uint32_t)0x00000001)
#define CRYPT_AES_KEY_256        ((uint32_t)0x00000002)

/* CRYPT->CFG — Cipher mode (* bits 2-4) */
#define CRYPT_MODE_ECB           ((uint32_t)0x00000000)
#define CRYPT_MODE_CBC           ((uint32_t)0x00000004)
#define CRYPT_MODE_CTR           ((uint32_t)0x00000008)

/* CRYPT->CFG — DES variant (* bits 5-6) */
#define CRYPT_DES_SINGLE         ((uint32_t)0x00000000)
#define CRYPT_DES_TRIPLE_2KEY    ((uint32_t)0x00000020)
#define CRYPT_DES_TRIPLE_3KEY    ((uint32_t)0x00000040)

/* CRYPT->STATUS — bit 0 */
#define CRYPT_STATUS_BUSY        ((uint32_t)0x00000001)

#define AES_BLOCK_SIZE           16
#define DES_BLOCK_SIZE           8
#define SHA1_DIGEST_SIZE         20
#define SHA256_DIGEST_SIZE       32

void      CRYPT_WaitBusy(void);
FlagStatus CRYPT_IsBusy(void);
void      CRYPT_ClearIT(void);

/* ---- Raw register access (use when bit layout is fully validated) ---- */

void      CRYPT_LoadBlock(const uint8_t *src, volatile uint32_t *dst, uint32_t words);
void      CRYPT_ReadBlock(volatile uint32_t *src, uint8_t *dst, uint32_t words);
void      CRYPT_Start(uint32_t ctrl_word);

/* ---- AES ---- */

void      AES_SetKey(const uint8_t *key, uint32_t key_size);
void      AES_SetIV(const uint8_t *iv);
void      AES_EncryptECB(const uint8_t *in, uint8_t *out);
void      AES_DecryptECB(const uint8_t *in, uint8_t *out);
void      AES_EncryptCBC(const uint8_t *in, uint8_t *out, uint32_t block_count);
void      AES_DecryptCBC(const uint8_t *in, uint8_t *out, uint32_t block_count);
void      AES_EncryptCTR(const uint8_t *in, uint8_t *out, uint32_t block_count);

/* ---- DES / 3DES ---- */

void      DES_SetKey(const uint8_t *key);
void      TDES_SetKey2(const uint8_t *key);
void      TDES_SetKey3(const uint8_t *key);
void      TDES_SetIV(const uint8_t *iv);
void      DES_EncryptECB(const uint8_t *in, uint8_t *out);
void      DES_DecryptECB(const uint8_t *in, uint8_t *out);
void      TDES_EncryptCBC(const uint8_t *in, uint8_t *out, uint32_t block_count);
void      TDES_DecryptCBC(const uint8_t *in, uint8_t *out, uint32_t block_count);

/* ---- SHA-1 / SHA-256 ---- */

void      SHA1_Init(void);
void      SHA1_Update(const uint8_t *data, uint32_t byte_len);
void      SHA1_Final(uint8_t *digest);

void      SHA256_Init(void);
void      SHA256_Update(const uint8_t *data, uint32_t byte_len);
void      SHA256_Final(uint8_t *digest);

/* ---- PKE (Asymmetric) raw access ---- */

void      PKE_Start(uint32_t cmd);
void      PKE_WaitBusy(void);
FlagStatus PKE_IsBusy(void);

/* PKE commands */
#define PKE_CMD_MODMUL            ((uint32_t)0x00000004)
#define PKE_CMD_MODEXP            ((uint32_t)0x00000002)
#define PKE_CMD_MODINV            ((uint32_t)0x00000005)
#define PKE_CMD_MODADD            ((uint32_t)0x0000000A)

#ifdef __cplusplus
}
#endif

#endif
