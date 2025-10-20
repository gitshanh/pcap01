/*
 * pcap01_basic.h
 *
 *  Created on: Oct 17, 2025
 *      Author: shanhao
 */

#ifndef _PCAP01_BASIC_H_
#define _PCAP01_BASIC_H_

#include "pcap01.h"

extern pcap01_handle_t pcap;

void pcap_basic_init(pcap01_handle_t *pcap);

uint8_t pcap_basic_read_diff(pcap01_handle_t *pcap, uint8_t addr, float *capacity);

#endif /* _PCAP01_BASIC_H_ */
