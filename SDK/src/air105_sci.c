#include "air105_sci.h"

#define SCI_CR0_EN              ((uint32_t)0x00000001)
#define SCI_CR0_MODE_EMV        ((uint32_t)0x00000002)
#define SCI_CR0_CARDTYPE        ((uint32_t)0x0000000C)
#define SCI_CR0_CARDTYPE_NONE   ((uint32_t)0x00000000)
#define SCI_CR0_CARDTYPE_ICC    ((uint32_t)0x00000004)
#define SCI_CR0_CARDTYPE_PSAM   ((uint32_t)0x00000008)
#define SCI_CR0_T0              ((uint32_t)0x00000010)
#define SCI_CR1_ATR_EN          ((uint32_t)0x00000001)
#define SCI_CR1_PPS_EN          ((uint32_t)0x00000002)
#define SCI_CR2_RST_LOW         ((uint32_t)0x00000001)
#define SCI_CR2_RST_HIGH        ((uint32_t)0x00000002)
#define SCI_CR2_CLK_EN          ((uint32_t)0x00000004)

static SCI_TypeDef *SCI_GetBase(uint8_t SciIndex)
{
    if (SciIndex == 0) return SCI0;
    if (SciIndex == 2) return SCI2;
    return NULL;
}

int32_t SCI_ConfigEMV(uint8_t SCI_Bitmap, uint32_t SCIx_Clk)
{
    SCI_TypeDef *sci;
    uint32_t sci_clk;

    sci = SCI_GetBase(SCI_Bitmap);
    if (sci == NULL)
        return SCI_UNCONFIG;

    if (SCIx_Clk < 1000000 || SCIx_Clk > 20000000)
        return SCI_ICC_CLOCK_ERR;

    sci->SCI_CR0 = 0;
    sci->SCI_CR1 = 0;
    sci->SCI_CR2 = 0;
    sci->SCI_IER = 0;

    sci->SCI_BLKTIME   = 0xFFFF;
    sci->SCI_CHTIME    = 0xFFFF;
    sci->SCI_BLKGUARD  = 0xFFFF;
    sci->SCI_CHGUARD   = 0xFFFF;
    sci->SCI_RETRY     = 3;
    sci->SCI_STABLE    = 0;

    sci->SCI_ATRSTIME  = 0x1000;
    sci->SCI_ATRDTIME  = 0x1000;
    sci->SCI_RXTIME    = 9600;

    sci->SCI_TIDE      = 12;
    sci->SCI_SYNCCR    = 0;

    sci_clk = SCIx_Clk / 10000;
    sci->SCI_CLKICC    = 0x03FC0000 | (0x100U + (sci_clk * 372U));
    sci->SCI_BAUD      = sci_clk;

    sci->SCI_ATIME     = (SCIx_Clk / 1000000U) * 1000U;
    sci->SCI_DTIME     = (SCIx_Clk / 1000000U) * 20U;

    sci->SCI_CR0 = SCI_CR0_EN | SCI_CR0_MODE_EMV | SCI_CR0_CARDTYPE_ICC | SCI_CR0_T0;
    sci->SCI_CR1 = SCI_CR1_ATR_EN | SCI_CR1_PPS_EN;
    sci->SCI_CR2 = SCI_CR2_RST_LOW | SCI_CR2_CLK_EN;

    return 0;
}
