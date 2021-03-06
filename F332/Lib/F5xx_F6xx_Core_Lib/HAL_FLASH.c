#include "msp430.h"
#include "HAL_FLASH.h"

void Flash_SegmentErase(uint16_t *Flash_ptr)
{
  FCTL3 = FWKEY;                            // Clear Lock bit
  FCTL1 = FWKEY + ERASE;                    // Set Erase bit
  *Flash_ptr = 0;                           // Dummy write to erase Flash seg
  while (FCTL3 & BUSY);                     // test busy
  FCTL1 = FWKEY;                            // Clear WRT bit
  FCTL3 = FWKEY + LOCK;                     // Set LOCK bit
}

uint8_t Flash_EraseCheck(uint16_t *Flash_ptr, uint16_t len)
{
  uint16_t i;
  
  for (i = 0; i < len; i++) {               // was erasing successfull?
    if (*(Flash_ptr + i) != 0xFF) {
      return FLASH_STATUS_ERROR;
    }
  }

  return FLASH_STATUS_OK;
}

void FlashWrite_8(uint8_t *Data_ptr, uint8_t *Flash_ptr, uint16_t count)
{
  FCTL3 = FWKEY;                            // Clear Lock bit
  FCTL1 = FWKEY+WRT;                        // Enable byte/word write mode
  
  while (count > 0) {
    while (FCTL3 & BUSY);                   // test busy
    *Flash_ptr++ = *Data_ptr++;             // Write to Flash
    count--;
  }

  FCTL1 = FWKEY;                            // Clear write bit
  FCTL3 = FWKEY + LOCK;                     // Set LOCK bit
}

void FlashWrite_16(uint16_t *Data_ptr, uint16_t *Flash_ptr, uint16_t count)
{
  FCTL3 = FWKEY;                            // Clear Lock bit
  FCTL1 = FWKEY+WRT;                        // Enable byte/word write mode
  
  while (count > 0) {
    while (FCTL3 & BUSY);                   // test busy
    *Flash_ptr++ = *Data_ptr++;             // Write to Flash
    count--;
  }

  FCTL1 = FWKEY;                            // Clear Erase bit
  FCTL3 = FWKEY + LOCK;                     // Set LOCK bit
}

void FlashWrite_32(uint32_t *Data_ptr, uint32_t *Flash_ptr, uint16_t count)
{
  FCTL3 = FWKEY;                            // Clear Lock bit
  FCTL1 = FWKEY + BLKWRT;                   // Enable long-word write
  
  while (count > 0) {
    while (FCTL3 & BUSY);                   // test busy
    *Flash_ptr++ = *Data_ptr++;             // Write to Flash
    count--;
  }

  FCTL1 = FWKEY;                            // Clear Erase bit
  FCTL3 = FWKEY + LOCK;                     // Set LOCK bit
}

void FlashMemoryFill_32(uint32_t value, uint32_t *Flash_ptr, uint16_t count)
{
  FCTL3 = FWKEY;                            // Clear Lock bit
  FCTL1 = FWKEY + BLKWRT;                   // Enable long-word write

  while (count > 0) {
    while (FCTL3 & BUSY);                   // test busy
    *Flash_ptr++ = value;                   // Write to Flash
    count--;
  }

  FCTL1 = FWKEY;                            // Clear Erase bit
  FCTL3 = FWKEY + LOCK;                      // Set LOCK bit
}
