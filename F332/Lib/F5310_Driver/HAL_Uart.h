#ifndef HAL_UART_H
#define HAL_UART_H

#include <stdint.h>

#define COM1  1
#define COM2  2

extern void OpenUart(unsigned char Port,unsigned long Baudrate,void (*CallBackFunction)(char));
extern void SendTextToUart(unsigned char Port,char *SBUF,unsigned int length);
extern void SendByteToUart(unsigned char Port,unsigned char SBUF);



#endif /* HAL_UART_H */