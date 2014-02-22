#ifndef SDCARD_H
#define SDCARD_H

#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include "msp430.h"
#include "HAL_Board.h"
#include "HAL_Buttons.h"
#include "HAL_Dogs102x6.h"
#include "HAL_SDCard.h"
#include "HAL_Wheel.h"
#include "ff.h"

extern void SDCard(void);
extern void WriteTest(void);
extern void ContinueWriteTest(void);
// Function Prototypes
extern FRESULT GetDirectory(char* directoryName);
extern FRESULT GetFile(char* fileName);
extern FRESULT WriteFile(char* fileName, char* text, WORD size);

#endif /* SDCARD_H */



