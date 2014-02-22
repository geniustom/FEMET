#include "msp430.h"
#include "HAL_PMM.h"
#include "HAL_UCS.h"
#include "HAL_Board.h"
#include "HAL_Uart.h"


extern void DTMFGen_init();
extern void DTMFRecv_init();
extern void Delayms(unsigned int t);


extern void F332_init();
extern void F332_PickUp();
extern void F332_HangUp();
extern void F332_SetMute(int m);
extern void F332_DTMF_Out(unsigned char Digi);
extern void F332_DTMF_OutList(unsigned char *Digi,unsigned int Len);