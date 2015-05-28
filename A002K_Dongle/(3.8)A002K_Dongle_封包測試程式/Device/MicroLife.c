#include "../Driver/Driver.h"
#include "MicroLife.h"


/********************************************************************************
1.�Ĥ@��BYTE����06
2.�ĤG��BYTE���쵧��
3.�q�ĤT��BYTE�}�l�A����C7��BYTE�����@��PART
4.�Ĥ@��PART=PART0�A��byte0=N�A�N���٭n���᦬N��PART
5.PART1 ~ PARTN-1 =��1��~��N-1�����
6.PARTN=�eN��������
7.�̫�@��BYTE=CHECKSUM=���F�Ĥ@��06���~��L�Ҧ�BYTE���`�X�bMOD256
********************************************************************************/


unsigned char MicroLifeBuf[MicroLifeBufLen];
unsigned char MicroLifeCTIData[MicroLifeCTILen];
unsigned int MicroLifeBufIndex=0;
unsigned int MicroLifeDataIndex=0;
unsigned int MicroLifeRecordCount=0;
unsigned int MicroLifeDataLimit=0;
unsigned char MicroLifeCheckSum=0;

const unsigned char MCMD_WakeUP       [5]={0x00,0x00,0x00,0x00,0x00};
const unsigned char MCMD_LinkBP       [4]={0x12,0x16,0x18,0x21};
const unsigned char MCMD_ClearAllData [8]={0x12,0x16,0x18,0x23,0x30,0x30,0x31,0x31};
const unsigned char MCMD_SetTime      [4]={0x12,0x16,0x18,0x27};
const unsigned char MCMD_GetHealthData[4]={0x12,0x16,0x18,0x28};

void ClearMicroLifeBuffer(){
  for(int i=0;i<MicroLifeBufLen;i++){
    MicroLifeBuf[i]=0;
  }
  MicroLifeBufIndex=0;
  MicroLifeDataIndex=0;
  MicroLifeRecordCount=0;
  MicroLifeCheckSum=0;
  MicroLifeDataLimit=0;
}

void SendMicroLifeCMD(unsigned char const *SBUF,unsigned int length){
  ClearMicroLifeBuffer();
  for (long i=0;i<length;i++){
    SentByteToMuxUart(MicroLifeUart,SBUF[i]);
  }
}


void ProcessMicroLifeData(unsigned char UartData){
  MicroLifeDataIndex++;
//===========================================================================�ˬd�Ĥ@��BYTE
  if((MicroLifeDataIndex==1)){  //�Ĥ@��BYTE�O0x06�~���L
    if(UartData!=0x06){
      ClearMicroLifeBuffer();
    }
    return;
  }
//===========================================================================�ˬd�ĤG��BYTE(PAGE��)
  if(MicroLifeDataIndex==2){  //�Ĥ@��BYTE�O0x06�~���L
    MicroLifeRecordCount=UartData;
    MicroLifeDataLimit=(MicroLifeRecordCount*7)+8;
    MicroLifeCheckSum=UartData;
    return;
  }
//===========================================================================�֥[CHECKSUM����̫�@��BYTE
  if((MicroLifeDataIndex>=3)&&(MicroLifeDataIndex<=MicroLifeDataLimit)){
    MicroLifeCheckSum+=UartData;
  }
//===========================================================================�̫�2��PAGE�~�}�l�sBUFFER
  if((MicroLifeDataIndex>(MicroLifeDataLimit-14))&&(MicroLifeDataIndex<=MicroLifeDataLimit)){  //CHECK SUM����J
    MicroLifeBuf[MicroLifeBufIndex]=UartData;
    MicroLifeBufIndex++;
    MicroLifeBufIndex%=MicroLifeBufLen;
  }
//===========================================================================�ˬdCHECKSUM
  if(MicroLifeDataIndex==MicroLifeDataLimit+1){   //�Y���۵�..�N�����M��
    if(UartData!=MicroLifeCheckSum){
      ClearMicroLifeBuffer();
    }
    //�Ycheck sum �ˬdok..�hbuf�����e���A�e7��byte���̫�@�����..��7��byte��������
    return;
  }
}



void ReadMicroLifeData(unsigned long *EnTime,unsigned long *Data){
  ClearMicroLifeBuffer();
  SendMicroLifeCMD(MCMD_WakeUP,5);
  Delayms(100);
  SendMicroLifeCMD(MCMD_LinkBP,4);
  Delayms(100);
//========================���X���====================
  ClearMicroLifeBuffer(); 
  SendMicroLifeCMD(MCMD_GetHealthData,4);
  Delayms(40);                      //�@�}�l30ms
  Delayms(MicroLifeRecordCount*16);  //�̷Ӹ�Ƶ��ưʺA�վ�
  
  unsigned long HealthData=0;
  HealthData=(((unsigned long)MicroLifeBuf[0])*1000000)
                +(((unsigned long)MicroLifeBuf[1])*1000)
                +((unsigned long)MicroLifeBuf[2]);
  
//========================���X�ɶ�====================
  unsigned char Y,M,D,H,m;

  Y=(MicroLifeBuf[3]>>4)+(16*(MicroLifeBuf[6]>>7));
  M=MicroLifeBuf[3]%16;
  D=MicroLifeBuf[4]>>3;
  H=((MicroLifeBuf[4]%8)*4)+(MicroLifeBuf[5]>>6);
  m=MicroLifeBuf[5]%64;

//========================��X========================
  *Data=HealthData;
  *EnTime=EncodeDateTime(Y,M,D,H,m);
}


void WriteTimeToMicroLife(){
  unsigned long MEncodeDate=0;
  unsigned long MEncodeTime=0;
  unsigned int CheckSum=0;
  unsigned char MCMD_SetNowTime[16];

  MEncodeDate=(unsigned long)(SystemDateTime.Year)+
             ((unsigned long)(SystemDateTime.Day)*100)+
             ((unsigned long)(SystemDateTime.Month)*10000);
  MEncodeTime=(unsigned long)(SystemDateTime.Second)+
             ((unsigned long)(SystemDateTime.Minute)*100)+
             ((unsigned long)(SystemDateTime.Hour)*10000);
  
  
  for(int i=0;i<6;i++){
    MCMD_SetNowTime[6-i-1]=(unsigned char)((MEncodeDate % 10)+0x30);
    MEncodeDate=MEncodeDate/10;
  }
  
  MCMD_SetNowTime[6]=0x32;
  MCMD_SetNowTime[7]=0x30; 
  
  for (int i=13;i>7;i--){
    MCMD_SetNowTime[i]=(unsigned char)((MEncodeTime % 10)+0x30);
    MEncodeTime=MEncodeTime/10;
  }
  
  for(int i=0;i<14;i++){
    CheckSum+=MCMD_SetNowTime[i];
  }
  CheckSum=CheckSum%256;
  
  unsigned char HexWord[16]={'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
  MCMD_SetNowTime[14]=HexWord[(CheckSum%16)];
  MCMD_SetNowTime[15]=HexWord[(CheckSum>>4)];
  
  SendMicroLifeCMD(MCMD_SetTime,4);
  SendMicroLifeCMD(MCMD_SetNowTime,16);
}


void ClearMicroLifeFlash(){
  ClearMicroLifeBuffer();
  SendMicroLifeCMD(MCMD_WakeUP,5);
  Delayms(100);
  SendMicroLifeCMD(MCMD_LinkBP,4);
  Delayms(100);
//========================���X���====================
  ClearMicroLifeBuffer(); 
  SendMicroLifeCMD(MCMD_ClearAllData,8);
}

