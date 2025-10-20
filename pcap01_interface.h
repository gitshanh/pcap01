/*
 * pcap01_interface.h
 *
 *  Created on: Oct 17, 2025
 *      Author: shanhao
 */

#ifndef _PCAP01_INTERFACE_H_
#define _PCAP01_INTERFACE_H_

#include "main.h"
#include "stm32f1xx_hal_gpio.h"

#define SPI1_CS_ENABLE()              HAL_GPIO_WritePin(SPI1_CS_GPIO_Port, SPI1_CS_Pin, GPIO_PIN_RESET);
#define SPI1_CS_DISABLE()             HAL_GPIO_WritePin(SPI1_CS_GPIO_Port, SPI1_CS_Pin, GPIO_PIN_SET);

void pcap_spi_cs_enable(void);

void pcap_spi_cs_disable(void);

uint8_t pcap_spi_write(uint8_t *data, uint16_t data_len);

uint8_t pcap_spi_write_read(uint8_t *data, uint8_t *buf, uint16_t len);

#endif /* _PCAP01_INTERFACE_H_ */
