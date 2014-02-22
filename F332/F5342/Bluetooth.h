
#ifndef HAL_BT_H
#define HAL_BT_H

#include <stdint.h>

// Pins from MSP430 connected to the Bluetooth
#define BT_TX           BIT4
#define BT_RX           BIT5
#define BT_MA           BIT6
#define BT_CS           BIT7

// Ports
#define BT_SEL          P4SEL
#define BT_DIR          P4DIR
#define BT_OUT          P4OUT
#define BT_REN          P4REN

extern void Bluetooth_Init(void);
extern void BluetoothRXCallBack(char RX);
extern void BlueToothWrite(char *Data,int Length);

#endif /* HAL_BT_H */