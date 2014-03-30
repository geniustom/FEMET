#include "msp430.h"
#include "HAL_PMM.h"
#include "HAL_UCS.h"
#include "HAL_Board.h"
#include "HAL_Uart.h"


#define UartBufLen      64
#define F332COM         2


//******* Tommy: Task Queue structure ******
#define RX_QUEUE_SIZE               128
#define RX_QUEUE_MASK               (RX_QUEUE_SIZE-1ul)
#define RX_QUEUE_RESET(rBuf)        (rBuf.rdIdx = rBuf.wrIdx = 0)
#define RX_QUEUE_WR(rBuf, dataIn)   (rBuf.data[RX_QUEUE_MASK & rBuf.wrIdx++] = (dataIn))
#define RX_QUEUE_RD(rBuf)           (rBuf.data[RX_QUEUE_MASK & rBuf.rdIdx++])
#define RX_QUEUE_COUNT(rBuf)        (RX_QUEUE_MASK & (rBuf.wrIdx - rBuf.rdIdx))
#define RX_QUEUE_EMPTY(rBuf)        (RX_QUEUE_COUNT(rBuf) == 0)
#define RX_QUEUE_FULL(rBuf)         (RX_QUEUE_COUNT(rBuf) == RX_QUEUE_MASK)

typedef struct
{
    char data[RX_QUEUE_SIZE];
    unsigned int wrIdx;
    unsigned int rdIdx;
} RX_QUEUE;
//***************************************************



//*********************************  Cmd set Level **************************************
extern RX_QUEUE F332Queue;

extern void F332_RX(char RX);
extern void F332_ProcessCMD(char RX);
extern void CMD_GetDTMF(unsigned char Digi);
//*********************************  Driver Level ***************************************
extern void DTMFGen_init();
extern void DTMFRecv_init();
extern void Delayms(unsigned int t);


extern void F332_init();
extern void F332_PickUp();
extern void F332_HangUp();
extern void F332_SetMute(int m);
extern void F332_DTMF_Out(unsigned char Digi);
extern void F332_DTMF_OutList(unsigned char *Digi,unsigned int Len);
//**************************************************************************************
