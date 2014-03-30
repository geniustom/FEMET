#include "F332_Lib.h"




char            UART_Buf[UartBufLen];
unsigned int    UART_BufIndex;
RX_QUEUE        F332Queue;
RX_QUEUE        DTMFQueue;

//===================================== L�O �|�e�X�� =====================================
//--------------�������--------------
const char TCMD_HandFreeOn[4]          ={0xFA,0x6C,0xC7,0xAB};             //�}�_�K��
const char TCMD_HandFreeOff[4]         ={0xFA,0x6C,0xCD,0xA1};            //�����K��
const char TCMD_DialOut[4]             ={0xFA,0x65,0xAA,0xCF};                //���X�s�򸹽X
const char TCMD_GetEEPROM[4]           ={0xFA,0x60,0x64,0x04};              //Ū��EEPROM�X�t�]�w��
const char TCMD_DefaultSetting_1[19]   ={0xFA,0x51,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x51};
const char TCMD_DefaultSetting_2[19]   ={0xFA,0x52,0x10,0x03,0x20,0x03,0x00,0x15,0x12,0x99,0x99,0x06,0x01,0x00,0xAA,0x00,0x99,0x99,0xC8};
//--------------�l    �[--------------
const char TCMD_SendDialList[2]        ={0xFA,0x67};                     //�e�@�꼷��list
const char TCMD_SendKEY[3]             ={0xFA,0x61,0x55};                //�e�@��DTMF KEY
//==================================== F332 �n�e�X�� ====================================
//--------------�������--------------
const char TRCMD_DTMFTone[4]           ={0xFA,0x8A,0x00,0x00};                             //������DTMF
//--------------�l    �[--------------
const char TRCMD_DTMFStart[4]          ={0xFA,0x88,0x33,0xBB};                             //��DTMF������}�l
const char TRCMD_DTMFStop[4]           ={0xFA,0x8A,0x55,0xDD};                             //��DTMF�����浲��
const char TRCMD_PhoneOn[5]            ={0xFA,0x80,0x84,0x55,0x51};                             //�d���O����
const char TRCMD_HookON[5]             ={0xFA,0x80,0x81,0x55,0x54};                             //HOOK ON
const char TRCMD_RingEND[5]            ={0xFA,0x80,0x80,0x55,0x55};                             //�T�a����
const char TRCMD_FactorySetting_1[19]  ={0xFA,0xA1,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xA1};
const char TRCMD_FactorySetting_2[19]  ={0xFA,0xA2,0x10,0x03,0x20,0x03,0x00,0x15,0x12,0x99,0x99,0x06,0x01,0x00,0xAA,0x00,0x99,0x99,0x38};
const char TRCMD_FactorySetting_3[19]  ={0xFA,0xA3,0xF4,0x12,0xA8,0x88,0xF4,0x12,0xA8,0x8A,0x00,0x00,0x0E,0x51,0x00,0x00,0x0E,0x5A,0xAA};
const char TRCMD_FactorySetting_4[19]  ={0xFA,0xA4,0x00,0x54,0x45,0x4E,0x54,0x45,0x4C,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xA6};
const char TRCMD_FactorySetting_5[19]  ={0xFA,0xA5,0x48,0x00,0x03,0x09,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xE7};

//=====================================================================================
//const char TCMD_SPKOff[4]={0xFA,0x6C,0xC4,0xA8};                 //����SPK
//const char TCMD_SPKOn[4]={0xFA,0x6C,0xC0,0xAC};                  //�}��SPK
//const char TCMD_TestPhone[4]={0xFA,0x60,0x60,0x00};              //���ոܾ��O�_�^��
//const char TRCMD_DialTone[3]={0x89,0x8d,0x04};                   //�����켷����
//const char TRCMD_BusyTone[3]={0x89,0x89,0x33};                   //�����즣��
//const char TRCMD_DialRing[2]={0xFA,0x80,0x80};                   //�������T�a
//const char TRCMD_TestRequest[1]={0x70};                          //��������ոܾ��^��
//=====================================================================================


char CompareCMD(char const *SCMD,unsigned char Slen,unsigned char Ulen){
  if (Slen>Ulen) return 0;
  unsigned char Same=1;
  for (int i=0;i<Slen;i++){
    if(SCMD[i]!=UART_Buf[i]) {
      Same=0;
    }
  }
  return Same;
}

unsigned char CalChkSum(char *SCMD,unsigned int len){
  unsigned char cks=0;
  for(int i=1;i<len;i++){  //�]��SCMD[0]�O0xFA
    cks^=SCMD[i];
  }
  return cks;
}

unsigned char CMDtoDTMF(unsigned char digi){
  switch (digi)
  {
    case 0xca:    return 0x2a;  //*
    case 0xcb:    return 0x23;  //#
    default:      return digi+0x30;   //other
  }
}

void ClearUartBUF(){
  for(int i=0;i<UartBufLen;i++){
    UART_Buf[i]=0;
  }
  UART_BufIndex=0;
}

void F332_ProcessCMD(char RX){
  //==============�ʥ]�Y�M��
  if(RX==0xFA){
    ClearUartBUF();
  }
  //==============�ˬdChecksum
  UART_Buf[UART_BufIndex]=RX;
  UART_BufIndex++;
  unsigned char ChkSum=CalChkSum(UART_Buf,UART_BufIndex-1);
  //==============�P�_���X�kCMD �}�l����
  if((UART_Buf[UART_BufIndex-1]==ChkSum)&&(UART_BufIndex>=4)){
    //************�}�ҧK��
    if (CompareCMD(TCMD_HandFreeOn,4,UART_BufIndex)){
      F332_PickUp();
      SendTextToUart(F332COM,(char *)TRCMD_PhoneOn,sizeof(TRCMD_PhoneOn));
      SendTextToUart(F332COM,(char *)TRCMD_HookON,sizeof(TRCMD_HookON));
      ClearUartBUF();
    }
    //************�����K��
    else if (CompareCMD(TCMD_HandFreeOff,4,UART_BufIndex)){
      F332_HangUp();
      ClearUartBUF();
    }
    //************�n�D�Ǧ^�t�ιw�]��
    else if (CompareCMD(TCMD_GetEEPROM,4,UART_BufIndex)){
      SendTextToUart(F332COM,(char *)TRCMD_FactorySetting_1,sizeof(TRCMD_FactorySetting_1));
      SendTextToUart(F332COM,(char *)TRCMD_FactorySetting_2,sizeof(TRCMD_FactorySetting_2));
      SendTextToUart(F332COM,(char *)TRCMD_FactorySetting_3,sizeof(TRCMD_FactorySetting_3));
      SendTextToUart(F332COM,(char *)TRCMD_FactorySetting_4,sizeof(TRCMD_FactorySetting_4));
      SendTextToUart(F332COM,(char *)TRCMD_FactorySetting_5,sizeof(TRCMD_FactorySetting_5));
      ClearUartBUF();
    }
    //************�n�D���X�@�qDTMF(���]�w�A�٥���)
    else if (CompareCMD(TCMD_SendDialList,2,UART_BufIndex)){
      if (RX==CalChkSum(UART_Buf,UART_BufIndex-1)){
        unsigned int DTMF_len=UART_BufIndex-3; //�����ʥ]�Y�PCHKSUM
        RX_QUEUE_RESET(DTMFQueue);              //�M��DTMF BUF
        for(int i=0;i<DTMF_len;i++){
          RX_QUEUE_WR(DTMFQueue,CMDtoDTMF(UART_Buf[i+2]));
        }
        ClearUartBUF();
      }
    }
    else if (CompareCMD(TCMD_DialOut,4,UART_BufIndex)){
      while (!RX_QUEUE_EMPTY(DTMFQueue)){
        F332_DTMF_Out(RX_QUEUE_RD(DTMFQueue));
      }
      RX_QUEUE_RESET(DTMFQueue);              //�M��DTMF BUF
      ClearUartBUF();
    }
    //************�n�D���X�@��DTMF
    else if(CompareCMD(TCMD_SendKEY,3,UART_BufIndex)) {
      if (UART_BufIndex==5){
        F332_DTMF_Out(CMDtoDTMF(UART_Buf[3]));
        ClearUartBUF();
      }
    }
  }
}


void F332_RX(char RX){
  RX_QUEUE_WR(F332Queue,RX);
}


void CMD_GetDTMF(unsigned char Digi){
  unsigned char DTMF[16]={'D','1','2','3','4','5','6','7','8','9','0','*','#','A','B','C'};
  char CMD[4];
  CMD[0]=TRCMD_DTMFTone[0];
  CMD[1]=TRCMD_DTMFTone[1];
  CMD[2]=DTMF[Digi];
  CMD[3]= CMD[1]^CMD[2];
  SendTextToUart(F332COM,CMD,4);
}


                            


