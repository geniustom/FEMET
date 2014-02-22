/***************************************************************************//**
 * @file       Bluetooth.c
 * @addtogroup Bluetooth
 * @{
 ******************************************************************************/
#include <stdio.h>
//#include <stdint.h>
#include <string.h>
#include "msp430.h"
#include "HAL_Board.h"
#include "HAL_Uart.h"
#include "Bluetooth.h"
#include "HAL_SDCard.h"
#include "SDCard.h"


/***************************************************************************//**
 * @brief   Initialize Bluetooth
 * @param   None
 * @return  None
 ******************************************************************************/

void Bluetooth_Init(void){
  BT_SEL |= BT_TX+BT_RX;
  BT_DIR |= BT_MA+BT_CS;
  BT_OUT |= BT_MA+BT_CS;
  BT_REN |= BT_CS;              // Pull-Ups on BT_CS
  
  OpenUart(COM2,115200,&BluetoothRXCallBack);
}   

/***************************************************************************//**
 * @brief   BlueTooth Write Test
 * @param   None
 * @return  None
 ******************************************************************************/

void BlueToothWrite(char *Data,int Length){
  SendTextToUart(COM2,Data,Length);
}  


/***************************************************************************//**
 * @brief   BlueTooth RX Callback
 * @param   None
 * @return  None
 ******************************************************************************/
void BluetoothRXCallBack(char RX){
  //char R=(char)RX;
  //Board_ledOn(LED1);
  //WriteFile("BTRX.txt", &R, 1);
  SendTextToUart(COM2,&RX,1);
  //Board_ledOff(LED1);
}

