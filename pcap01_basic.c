/*
 * pcap01_basic.c
 *
 *  Created on: Oct 17, 2025
 *      Author: shanhao
 */
#include "pcap01.h"
#include "pcap01_interface.h"
#include "pcap01_basic.h"

pcap01_handle_t pcap = {
    .spi_cs_enable = pcap_spi_cs_enable,
    .spi_cs_disable = pcap_spi_cs_disable,
    .spi_write = pcap_spi_write,
    .spi_write_read = pcap_spi_write_read,
};

void pcap_basic_init(pcap01_handle_t *pcap)
{
    pcap01_cmd8(pcap, PCAP01_CMD8_ALL_RESET);
    HAL_Delay(10);

    pcap01_write_sram(pcap, PCap01_standard_firmware);
    pcap01_write_config(pcap, PCap01_standard_config_reg);
    pcap01_set_runbit(pcap, PCAP01_PARA_DSP_RUN);

    pcap01_cmd8(pcap, PCAP01_CMD8_PART_RESET);
    HAL_Delay(10);
    pcap01_cmd8(pcap, PCAP01_CMD8_START_MEASURE);
}

uint8_t pcap_basic_read_diff(pcap01_handle_t *pcap, uint8_t addr, float *capacity)
{
    uint8_t ret;
    uint32_t rx_data;
    float capacity_raw;
    ret = pcap01_cmd32(pcap, PCAP01_CMD32_READ_RESULTS, addr, DUMMY_WRITE, &rx_data);
    if (ret == 0)
    {
        capacity_raw = (float)rx_data * INV_SCALE_FACTOR;
        *capacity = capacity_raw * 220 - 5.9;
    }
    return ret;
}
