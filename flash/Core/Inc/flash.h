#ifndef __FLASH_H__
#define __FLASH_H__

#include "stm32f4xx.h"
#include "stm32f4xx_hal_flash.h"
#include "usart.h"
#include "stdio.h"

#define SECTOR5_ADDR                      0x08020000
#define FLASH_READ_SECTOR5(Buffer,Size)   FlashRead(SECTOR5_ADDR,Buffer,Size)
#define FLASH_WRITE_SECTOR5(Buffer,Size)  FlashWrite(SECTOR5_ADDR,Buffer,Size)

uint8_t FlashEraseSector5();
void FlashRead(uint32_t address, uint8_t* buffer, uint32_t size);
uint8_t FlashWrite(uint32_t address, uint8_t* buffer, uint32_t size);
uint8_t FlashWriteWithoutErase(uint32_t address, uint8_t* buffer, uint32_t size);



#endif