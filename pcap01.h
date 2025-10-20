/*
 * pcap01.h
 *
 *  Created on: Sep 4, 2025
 *      Author: shanhao
 */

#ifndef _INC_PCAP01_H_
#define _INC_PCAP01_H_

#include <stdint.h>

//8bit 操作码指令
#define PCAP01_CMD8_ALL_RESET                   0x88    //电源复位，所有都被复位
#define PCAP01_CMD8_PART_RESET                  0x8A    //SRAM和寄存器配置保留，只复位末端和DSP
#define PCAP01_CMD8_START_MEASURE               0x8C    //开始一次电容测量
#define PCAP01_CMD8_END_WRITE_OTP               0x84    //终止write to OPT
#define PCAP01_CMD8_START_TEMP                  0x8E    //开始一次温度测量

//24bit 操作码指令
#define PCAP01_CMD24_WRITE_SRAM                 0x90    //写SRAM
#define PCAP01_CMD24_READ_SRAM                  0x10    //读SRAM
#define PCAP01_CMD24_WRITE_OTP                  0xA0    //写OTP
#define PCAP01_CMD24_READ_OTP                   0x20    //读OTP

//32bit 操作码指令
#define PCAP01_CMD32_WRITE_CONFIG               0xC0    //写配置寄存器
#define PCAP01_CMD32_READ_RESULTS               0x40    //读电容值

//单端和差分传感器
#define PCAP01_PARA_SINGLE                      0x000000
#define PCAP01_PARA_DIFFERENTIAL                0x000001

//run bit位，配置完成后打开
#define PCAP01_PARA_DSP_STOP                    0x000000
#define PCAP01_PARA_DSP_RUN                     0x000001

//读取的24位电容值，高三位为整数位，低21位为小数位，存在缩放倍数
#define FRACTIONAL_BITS                         21
#define SCALE_FACTOR                            (1U << FRACTIONAL_BITS)  // 2^21 = 2097152
#define INV_SCALE_FACTOR                        (1.0f / SCALE_FACTOR)

#define DUMMY_WRITE                             0xFF

/**
 * @brief pcap01 handle structure definition
 */
typedef struct pcap01_handle_s
{
    void (*spi_cs_enable)(void);                                                     //SPI片选使能
    void (*spi_cs_disable)(void);                                                    //SPI片选失能

    uint8_t (*spi_write)(uint8_t *tx_buf, uint16_t len);                             //SPI发送
    uint8_t (*spi_write_read)(uint8_t *tx_buf, uint8_t *rx_buf, uint16_t len);       //SPI发送读取
} pcap01_handle_t;

extern uint32_t PCap01_standard_config_reg[];
extern uint8_t PCap01_standard_firmware[];

uint8_t pcap01_cmd8(pcap01_handle_t *pcap, uint8_t cmd);

uint8_t pcap01_cmd24(pcap01_handle_t *pcap, uint8_t cmd, uint16_t addr,
                           uint8_t tx_data, uint8_t *rx_data);

uint8_t pcap01_cmd32(pcap01_handle_t *pcap, uint8_t cmd, uint16_t addr,
                     uint32_t tx_data, uint32_t *rx_data);

//(Register 0..10)
uint8_t pcap01_write_config(pcap01_handle_t *pcap, uint32_t config[11]);

//配置寄存器最后写入的参数，保证配置中dsp静止,配置完成后打开，进入运行模式
uint8_t pcap01_set_runbit(pcap01_handle_t *pcap, uint32_t run);

//单端或差分传感器
uint8_t pcap01_set_differential(pcap01_handle_t *pcap, uint32_t diff);
uint8_t pcap01_write_sram(pcap01_handle_t *pcap, uint8_t firmware[4096]);

#endif /* _INC_PCAP01_H_ */
