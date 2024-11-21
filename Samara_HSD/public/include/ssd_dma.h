#ifndef SSD_DMA_H
#define SSD_DMA_H

#ifdef TEENSY41
#include "mimxrt1062_dma.h"
#else
#error "No DMA included"
#endif

extern struct sal_dma_interface dma;

#endif