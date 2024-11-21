#ifndef MIMXRT1062_DMA_H
#define MIMXRT1062_DMA_H

#include <stddef.h>
#include <string.h>

#include "sal_dma_interface.h"
#include "MIMXRT1062.h"

EXTERN_C_START

/**
 * @brief
 * DMA interface
 */
extern const struct sal_dma_interface dma;

EXTERN_C_END

#endif