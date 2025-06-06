/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-05-16     shelton      first version
 */

#ifndef _DRV_SDIO_H
#define _DRV_SDIO_H
#include <rtthread.h>
#include "rtdevice.h"
#include <rthw.h>
#include <string.h>
#include <drivers/dev_mmcsd_core.h>
#include <drivers/dev_sdio.h>
#include "drv_common.h"

#define SDCARD_INSTANCE_TYPE                   sdio_type

#define SDCARD_INSTANCE                        SDIO1

#define SDIO_BUFF_SIZE                         4096
#define SDIO_ALIGN_LEN                         32

#ifndef SDIO_BASE_ADDRESS
#define SDIO_BASE_ADDRESS                      SDIO1_BASE
#endif

#ifndef SDIO_CLOCK_FREQ
#define SDIO_CLOCK_FREQ                        (48U * 1000 * 1000)
#endif

#ifndef SDIO_BUFF_SIZE
#define SDIO_BUFF_SIZE                         (4096)
#endif

#ifndef SDIO_ALIGN_LEN
#define SDIO_ALIGN_LEN                         (32)
#endif

#ifndef SDIO_MAX_FREQ
#define SDIO_MAX_FREQ                          (24 * 1000 * 1000)
#endif

#define HW_SDIO_IT_CCRCFAIL                    (0x01U << 0)
#define HW_SDIO_IT_DCRCFAIL                    (0x01U << 1)
#define HW_SDIO_IT_CTIMEOUT                    (0x01U << 2)
#define HW_SDIO_IT_DTIMEOUT                    (0x01U << 3)
#define HW_SDIO_IT_TXUNDERR                    (0x01U << 4)
#define HW_SDIO_IT_RXOVERR                     (0x01U << 5)
#define HW_SDIO_IT_CMDREND                     (0x01U << 6)
#define HW_SDIO_IT_CMDSENT                     (0x01U << 7)
#define HW_SDIO_IT_DATAEND                     (0x01U << 8)
#define HW_SDIO_IT_STBITERR                    (0x01U << 9)
#define HW_SDIO_IT_DBCKEND                     (0x01U << 10)
#define HW_SDIO_IT_CMDACT                      (0x01U << 11)
#define HW_SDIO_IT_TXACT                       (0x01U << 12)
#define HW_SDIO_IT_RXACT                       (0x01U << 13)
#define HW_SDIO_IT_TXFIFOHE                    (0x01U << 14)
#define HW_SDIO_IT_RXFIFOHF                    (0x01U << 15)
#define HW_SDIO_IT_TXFIFOF                     (0x01U << 16)
#define HW_SDIO_IT_RXFIFOF                     (0x01U << 17)
#define HW_SDIO_IT_TXFIFOE                     (0x01U << 18)
#define HW_SDIO_IT_RXFIFOE                     (0x01U << 19)
#define HW_SDIO_IT_TXDAVL                      (0x01U << 20)
#define HW_SDIO_IT_RXDAVL                      (0x01U << 21)
#define HW_SDIO_IT_SDIOIT                      (0x01U << 22)

#define HW_SDIO_ERRORS \
    (HW_SDIO_IT_CCRCFAIL | HW_SDIO_IT_CTIMEOUT | \
     HW_SDIO_IT_DCRCFAIL | HW_SDIO_IT_DTIMEOUT | \
     HW_SDIO_IT_RXOVERR  | HW_SDIO_IT_TXUNDERR)

#define HW_SDIO_POWER_OFF                      (0x00U)
#define HW_SDIO_POWER_UP                       (0x02U)
#define HW_SDIO_POWER_ON                       (0x03U)

#define HW_SDIO_FLOW_ENABLE                    (0x01U << 14)
#define HW_SDIO_BUSWIDE_1B                     (0x00U << 11)
#define HW_SDIO_BUSWIDE_4B                     (0x01U << 11)
#define HW_SDIO_BUSWIDE_8B                     (0x02U << 11)
#define HW_SDIO_BYPASS_ENABLE                  (0x01U << 10)
#define HW_SDIO_IDLE_ENABLE                    (0x01U << 9)
#define HW_SDIO_CLK_ENABLE                     (0x01U << 8)

#define HW_SDIO_SUSPEND_CMD                    (0x01U << 11)
#define HW_SDIO_CPSM_ENABLE                    (0x01U << 10)
#define HW_SDIO_WAIT_END                       (0x01U << 9)
#define HW_SDIO_WAIT_INT                       (0x01U << 8)
#define HW_SDIO_RESPONSE_NO                    (0x00U << 6)
#define HW_SDIO_RESPONSE_SHORT                 (0x01U << 6)
#define HW_SDIO_RESPONSE_LONG                  (0x03U << 6)

#define HW_SDIO_DATA_LEN_MASK                  (0x01FFFFFFU)

#define HW_SDIO_IO_ENABLE                      (0x01U << 11)
#define HW_SDIO_RWMOD_CK                       (0x01U << 10)
#define HW_SDIO_RWSTOP_ENABLE                  (0x01U << 9)
#define HW_SDIO_RWSTART_ENABLE                 (0x01U << 8)
#define HW_SDIO_DBLOCKSIZE_1                   (0x00U << 4)
#define HW_SDIO_DBLOCKSIZE_2                   (0x01U << 4)
#define HW_SDIO_DBLOCKSIZE_4                   (0x02U << 4)
#define HW_SDIO_DBLOCKSIZE_8                   (0x03U << 4)
#define HW_SDIO_DBLOCKSIZE_16                  (0x04U << 4)
#define HW_SDIO_DBLOCKSIZE_32                  (0x05U << 4)
#define HW_SDIO_DBLOCKSIZE_64                  (0x06U << 4)
#define HW_SDIO_DBLOCKSIZE_128                 (0x07U << 4)
#define HW_SDIO_DBLOCKSIZE_256                 (0x08U << 4)
#define HW_SDIO_DBLOCKSIZE_512                 (0x09U << 4)
#define HW_SDIO_DBLOCKSIZE_1024                (0x0AU << 4)
#define HW_SDIO_DBLOCKSIZE_2048                (0x0BU << 4)
#define HW_SDIO_DBLOCKSIZE_4096                (0x0CU << 4)
#define HW_SDIO_DBLOCKSIZE_8192                (0x0DU << 4)
#define HW_SDIO_DBLOCKSIZE_16384               (0x0EU << 4)
#define HW_SDIO_DMA_ENABLE                     (0x01U << 3)
#define HW_SDIO_STREAM_ENABLE                  (0x01U << 2)
#define HW_SDIO_TO_HOST                        (0x01U << 1)
#define HW_SDIO_DPSM_ENABLE                    (0x01U << 0)

#define HW_SDIO_DATATIMEOUT                    (0xF0000000U)

struct at32_sdio
{
    volatile rt_uint32_t power;
    volatile rt_uint32_t clkcr;
    volatile rt_uint32_t arg;
    volatile rt_uint32_t cmd;
    volatile rt_uint32_t respcmd;
    volatile rt_uint32_t resp1;
    volatile rt_uint32_t resp2;
    volatile rt_uint32_t resp3;
    volatile rt_uint32_t resp4;
    volatile rt_uint32_t dtimer;
    volatile rt_uint32_t dlen;
    volatile rt_uint32_t dctrl;
    volatile rt_uint32_t dcount;
    volatile rt_uint32_t sta;
    volatile rt_uint32_t icr;
    volatile rt_uint32_t mask;
    volatile rt_uint32_t reserved0[2];
    volatile rt_uint32_t fifocnt;
    volatile rt_uint32_t reserved1[13];
    volatile rt_uint32_t fifo;
};

typedef rt_err_t (*dma_txconfig)(rt_uint32_t *src, rt_uint32_t *dst, int size);
typedef rt_err_t (*dma_rxconfig)(rt_uint32_t *src, rt_uint32_t *dst, int size);
typedef rt_uint32_t (*sdio_clk_get)(struct at32_sdio *hw_sdio);

#if defined (SOC_SERIES_AT32F435) || defined (SOC_SERIES_AT32F437) || \
    defined (SOC_SERIES_AT32F455) || defined (SOC_SERIES_AT32F456) || \
    defined (SOC_SERIES_AT32F457)
#define SDIO_BUS_CONFIG                                  \
    {                                                    \
        .sdio_x = SDIO1,                                 \
        .dma_rx.dma_x = DMA2,                            \
        .dma_tx.dma_x = DMA2,                            \
        .dma_rx.dma_crm = CRM_DMA2_PERIPH_CLOCK,         \
        .dma_tx.dma_crm = CRM_DMA2_PERIPH_CLOCK,         \
        .dma_rx.dma_channel = DMA2_CHANNEL4,             \
        .dma_tx.dma_channel = DMA2_CHANNEL4,             \
        .dma_rx.dma_irq = DMA2_Channel4_IRQn,            \
        .dma_tx.dma_irq = DMA2_Channel4_IRQn,            \
        .dma_rx.dmamux_channel = DMA2MUX_CHANNEL4,       \
        .dma_tx.dmamux_channel = DMA2MUX_CHANNEL4,       \
        .dma_rx.dmamux_id = DMAMUX_DMAREQ_ID_SDIO1,      \
        .dma_tx.dmamux_id = DMAMUX_DMAREQ_ID_SDIO1,      \
    }
#else
#define SDIO_BUS_CONFIG                                  \
    {                                                    \
        .sdio_x = SDIO1,                                 \
        .dma_rx.dma_crm = CRM_DMA2_PERIPH_CLOCK,         \
        .dma_tx.dma_crm = CRM_DMA2_PERIPH_CLOCK,         \
        .dma_rx.dma_channel = DMA2_CHANNEL4,             \
        .dma_rx.dma_irq = DMA2_Channel4_5_IRQn,          \
        .dma_tx.dma_channel = DMA2_CHANNEL4,             \
        .dma_tx.dma_irq = DMA2_Channel4_5_IRQn,          \
    }
#endif

struct dma_config {
    dma_type *dma_x;
    dma_channel_type *dma_channel;
#if defined (SOC_SERIES_AT32F435) || defined (SOC_SERIES_AT32F437) || \
    defined (SOC_SERIES_AT32F455) || defined (SOC_SERIES_AT32F456) || \
    defined (SOC_SERIES_AT32F457)
    dmamux_channel_type *dmamux_channel;
    dmamux_requst_id_sel_type dmamux_id;
#endif
    crm_periph_clock_type dma_crm;
    IRQn_Type dma_irq;
};

struct at32_sdio_des
{
    struct at32_sdio *hw_sdio;
    dma_txconfig txconfig;
    dma_rxconfig rxconfig;
    sdio_clk_get clk_get;
};

struct at32_sdio_config
{
    SDCARD_INSTANCE_TYPE *sdio_x;
    struct dma_config dma_rx, dma_tx;
};

/* at32 sdio dirver class */
struct at32_sdio_class
{
    struct at32_sdio_des *des;
    const struct at32_sdio_config *cfg;
    struct rt_mmcsd_host host;
    struct
    {
        dma_channel_type* handle_rx;
        dma_channel_type* handle_tx;
    } dma;
};

extern void at32_mmcsd_change(void);

#endif
