/**
  * filename:check.h, Data Checking API 
  */
#ifndef  CHECK_H_
#define  CHECK_H_

#include <stdint.h>

uint16_t Checksum_Sum(uint8_t* buf,uint16_t len);	 //��У�� �����ֽ�֮��Ϊ0
uint16_t Checksum_XOR(uint8_t* buf, uint16_t len);	 //���У�飬�����ֽ����
uint16_t Checksum_CRC8(uint8_t *buf,uint16_t len);	 //CRC8 У��
uint16_t Checksum_CRC16(uint8_t *buf,uint16_t len);  //CRC16 У��
uint16_t update_crc(uint16_t crc_accum, uint8_t *data_blk_ptr, uint16_t data_blk_size);
#endif

