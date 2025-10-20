/*
 * pcap01_interface.c
 *
 *  Created on: Oct 17, 2025
 *      Author: shanhao
 */
#include "pcap01.h"
#include "pcap01_interface.h"
#include "stm32f1xx.h"
#include "spi.h"

void pcap_spi_cs_enable(void)
{
    SPI1_CS_ENABLE();
}

void pcap_spi_cs_disable(void)
{
    SPI1_CS_DISABLE();
}

uint8_t pcap_spi_write(uint8_t *data, uint16_t data_len)
{
    if (HAL_SPI_Transmit(&hspi1, data, data_len, 1000) != HAL_OK)
    {
        return 1;
    }
    return 0;
}

uint8_t pcap_spi_write_read(uint8_t *data, uint8_t *buf, uint16_t len)
{
    if (HAL_SPI_TransmitReceive(&hspi1, data, buf, len, 1000) != HAL_OK)
    {
        return 1;
    }
    return 0;
}
