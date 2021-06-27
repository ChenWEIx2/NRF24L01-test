#include "flash.h"


void FlashRead(uint32_t address, uint8_t* buffer, uint32_t size)
{
    uint8_t i;
    for(i = 0;i < size;i++)
    {
        buffer[i] = *(volatile uint8_t*) (address + i);
    }
    printf("Read Successfully!\r\n");
}

uint8_t FlashEraseSector5()
{
    FLASH_EraseInitTypeDef erase_init;
    HAL_StatusTypeDef      hal_sta;
    uint32_t               sector_error;

    erase_init.Banks = FLASH_BANK_1;
    erase_init.NbSectors = 1;
    erase_init.Sector = FLASH_SECTOR_5;
    erase_init.VoltageRange = FLASH_VOLTAGE_RANGE_3;
    erase_init.TypeErase = FLASH_TYPEERASE_SECTORS;

    hal_sta = HAL_FLASHEx_Erase(&erase_init,&sector_error);

    if(hal_sta != HAL_OK || sector_error != 0xFFFFFFFFU) 
    {
        printf("Erase Fail!\r\n");
        return 0;
    }
    else 
    {
        printf("Erase Success!\r\n");
        return 1;
    }
}

uint8_t FlashWriteWithoutErase(uint32_t address, uint8_t* buffer, uint32_t size)
{
    HAL_StatusTypeDef hal_sta = HAL_OK;
	uint32_t          pos = 0;

    while((size > pos) && (hal_sta == HAL_OK))
    {
		hal_sta = HAL_FLASH_Program(FLASH_TYPEPROGRAM_BYTE, address + pos, buffer[pos]);
		pos++;
	}

	if(hal_sta == HAL_OK) return 1;
	else return 0;
}

uint8_t FlashWrite(uint32_t address, uint8_t* buffer, uint32_t size)
{
    uint8_t write_flag;
    
    HAL_FLASH_Unlock();
    FlashEraseSector5();
    write_flag = FlashWriteWithoutErase(address,buffer,size);
    HAL_FLASH_Lock();
    printf("Write Successfully!\r\n");

    return write_flag;
}