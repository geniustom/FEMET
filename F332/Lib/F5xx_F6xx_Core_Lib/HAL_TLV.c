#include "msp430.h"
#include "HAL_TLV.h" 

void Get_TLV_Info(uint8_t tag, uint8_t instance, uint8_t *length, uint16_t **data_address)
{
  char *TLV_address = (char *)TLV_START;         // TLV Structure Start Address

  while((TLV_address < (char *)TLV_END)
        && ((*TLV_address != tag) || instance)   // check for tag and instance
        && (*TLV_address != TLV_TAGEND))         // do range check first
  {
    if (*TLV_address == tag) instance--;         // repeat till requested instance is reached
    TLV_address += *(TLV_address + 1) + 2;       // add (Current TAG address + LENGTH) + 2
  }
  
  if (*TLV_address == tag)                       // Check if Tag match happened..
  {
    *length = *(TLV_address + 1);                  // Return length = Address + 1
    *data_address = (uint16_t *)(TLV_address + 2); // Return address of first data/value info = Address + 2
  }
  else                                           // If there was no tag match and the end of TLV structure was reached..
  {
    *length = 0;                                 // Return 0 for TAG not found
    *data_address = 0;                           // Return 0 for TAG not found
  }
}

uint16_t Get_Device_Type(void)
{
  uint16_t *pDeviceType = (uint16_t *)DEVICE_ID_0;
  return pDeviceType[0];                         // Return Value from TLV Table
}

uint16_t Get_TLV_Memory(uint8_t instance)
{
    uint8_t *pPDTAG;
    uint8_t bPDTAG_bytes;
    uint16_t count;

    instance *= 2;                               // set tag for word access comparison
    
    // TLV access Function Call
    Get_TLV_Info(TLV_PDTAG, 0, &bPDTAG_bytes, (uint16_t **)&pPDTAG); // Get Peripheral data pointer
    
    for (count = 0;count <= instance; count += 2)
    {
      if (pPDTAG[count] == 0) return 0;          // Return 0 if end reached
      if (count == instance) return (pPDTAG[count] | pPDTAG[count+1]<<8);
    }
    
    return 0;                                    // Return 0: not found
}

uint16_t Get_TLV_Peripheral(uint8_t tag, uint8_t instance)
{
    uint8_t *pPDTAG;
    uint8_t bPDTAG_bytes;
    uint16_t count = 0;
    uint16_t pcount = 0;

    Get_TLV_Info(TLV_PDTAG, 0, &bPDTAG_bytes, (uint16_t **)&pPDTAG); // Get Peripheral data pointer

    // read memory configuration from TLV to get offset for Peripherals
    while (Get_TLV_Memory(count)) {
      count++;
    }

    pcount = pPDTAG[count * 2 + 1];              // get number of Peripheral entries
    count++;                                     // inc count to first Periperal
    pPDTAG += count*2;                           // adjust point to first address of Peripheral
    count = 0;                                   // set counter back to 0
    pcount *= 2;                                 // align pcount for work comparision

    // TLV access Function Call
    for (count = 0; count <= pcount; count += 2) {
      if (pPDTAG[count+1] == tag) {              // test if required Peripheral is found
        if (instance > 0) {                       // test if required instance is found
          instance--;
        }
        else {
          return (pPDTAG[count] | pPDTAG[count + 1] << 8); // Return found data
        }
      }
    }
    
    return 0;                                    // Return 0: not found
}

uint8_t Get_TLV_Interrupt(uint8_t tag)
{
    uint8_t *pPDTAG;
    uint8_t bPDTAG_bytes;
    uint16_t count = 0;
    uint16_t pcount = 0;

    Get_TLV_Info(TLV_PDTAG, 0, &bPDTAG_bytes, (uint16_t **)&pPDTAG); // Get Peripheral data pointer
    
    // read memory configuration from TLV to get offset for Peripherals
    while (Get_TLV_Memory(count))
    {
      count++;
    }

    pcount = pPDTAG[count * 2 + 1];
    count++;                                     // inc count to first Periperal
    pPDTAG += (pcount + count) * 2;              // adjust point to first address of Peripheral
    count = 0;                                   // set counter back to 0

    // TLV access Function Call
    for (count = 0; count <= tag; count += 2)
    {
      if (pPDTAG[count] == 0) return 0;          // Return 0: not found/end of table
      if (count == tag) return (pPDTAG[count]);  // Return found data
    }
    
    return 0;                                    // Return 0: not found
}
