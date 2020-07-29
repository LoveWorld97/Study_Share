
#ifndef __USER_FLASH_H
#define __USER_FLASH_H
#include "main.h"

#define BYTE_SIZE 0x08	/*设置一个字节大小*/ 

extern void flash_write(uint32_t add, uint8_t data);
extern uint8_t flash_read(uint32_t add);
extern void flash_write_buf(uint32_t add, uint8_t *data, uint8_t len);
extern void flash_read_buf(uint32_t add, uint8_t *data, uint8_t len);

#endif	/*__USER_FLASH_H*/ 
