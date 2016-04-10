#include "../TaipeiCity_A002_L.h"


CTIMessageQueue CTIMSGQueue;
StateNode A002State;          //�y�z�ثe�t�Ω��ݪ��A�����c

unsigned long  EncodeDateTime(unsigned char EYear,unsigned char EMonth,unsigned char EDay,unsigned char EHour,unsigned char EMinute){
  unsigned long EncodeData=0;
  EncodeData=((unsigned long)EYear*13*32*24*60)+
             ((unsigned long)EMonth*32*24*60)+
             ((unsigned long)EDay*24*60)+  
             ((unsigned long)EHour*60)+  
             (unsigned long)EMinute;
  return EncodeData;
}

unsigned long  EncodeNowDateTime(){
  unsigned long EncodeData=0;
  EncodeData=((unsigned long)SystemDateTime.Year*13*32*24*60)+
             ((unsigned long)SystemDateTime.Month*32*24*60)+
             ((unsigned long)SystemDateTime.Day*24*60)+  
             ((unsigned long)SystemDateTime.Hour*60)+  
             (unsigned long)SystemDateTime.Minute;
  return EncodeData;
}

void ClearNodeData(CTIMessage *Node){
    Node->GateWayID=0;           //�D���s��
    Node->DeviceID=0;            //�D���O0 ��1~8��������1~8
    Node->MsgType=0;             //�T������
    Node->EncodeDateTime=0;     //�s�X�᪺�ɶ�    
    Node->Data=0; //�̦h9��Ʀr
    Node->RetryCount=0;
    //================================�̫��X�s�X=========
    for(int i=0;i<14;i++){
      Node->MessageStage1[i]=0;     // *(�D���s��)(���)
      Node->MessageStage2[i]=0;     // #(�����s��)(�T������)(�ɶ�)(CHKSUM)
    }
}

unsigned char DTMFToChar(unsigned char Digi){
  if(Digi=='*'){
    return '*';
  }else if(Digi=='#'){
    return '#';
  }else{
    return Digi+0x30;
  }
}

void SendQueueDataToFlash(int *CQ){
  unsigned char BUF[256];
  unsigned char *CTIQueueAddr=(unsigned char *)CQ;
  unsigned int CTIQueueSize=sizeof(CTIMessageQueue);
  
  for(int i=0;i<CTIQueueSize;i++){
    BUF[i%256]= (unsigned char)*CTIQueueAddr;
    if (i%1024==0){
      flash_erase_multi_segments(QueueData_Addr+i,1);
    }else if ((i%256==255)||(i==CTIQueueSize-1)){          //2016/04/10.�̫�@��block���g�y��Queue���׿���
      flash_write_Block(QueueData_Addr+i-255,BUF,256);
      for(int j=0;j<256;j++){   //�C�g���@���n��Buf�M��
        BUF[j]=0;
      }
    }
    *CTIQueueAddr++;
  }
}

void GetQueueDataFromFlash(int *CQ){
  unsigned char *CTIQueueAddr=(unsigned char *)CQ;
  unsigned int CTIQueueSize=sizeof(CTIMessageQueue);
  
  for(int i=0;i<CTIQueueSize;i++){
    *CTIQueueAddr=QueueDataBackup[i];
    *CTIQueueAddr++;
  }
  
}


void SendQueueDataToPc(CTIMessageQueue *CQ){
  unsigned char QueueIndex;
  SendTextToUart(COM3,"GETQU",5);  //DEVICE�Ǹ�Ƶ�MCU
  for(int i=0;i<CTIMessageQueueLength;i++){
    QueueIndex=i;//CQ->QRear-i+7;
    for(int j=0;j<14;j++){
      SendByteToUart(COM3,DTMFToChar(CQ->MSGList[QueueIndex].MessageStage1[j]));
    }
    for(int j=0;j<14;j++){
      SendByteToUart(COM3,DTMFToChar(CQ->MSGList[QueueIndex].MessageStage2[j]));
    }
    if(i<CTIMessageQueueLength-1){
      SendByteToUart(COM3,','); 
    }
  }

}

void SendQueueSizeToPC(CTIMessageQueue *CQ){
  unsigned char QLen=CQ->Length+1;
  SendTextToUart(COM3,"QSIZE",5);  //DEVICE�Ǹ�Ƶ�MCU
  SendByteToUart(COM3,QLen);
}


void DeleteRetryData(CTIMessageQueue *CQ){
  while((CQ->MSGList[CQ->QRear].RetryCount==0)&&(CQ->Length!=0)){  //�M���Ҧ����զ��Ƥw�g��0�����
    DeleteCTIMSG(CQ);
    if(CQ->Length==0){  //�Y��Ƥw�g�M�ŤF�A�N����RESET
      DriverFlag.ResetSystem=1; 
    }
  }
  for(int i=0;i<CTIMessageQueueLength;i++){     //�N�ثe�{�s����Ʀ��ƴ�@
    if(CQ->MSGList[i].RetryCount>0){
      CQ->MSGList[i].RetryCount--;
    }
  }
}



void CreateCTIMSGQueue(CTIMessageQueue *CQ){
  CQ->QRear=0;
  CQ->QFront=0;
  CQ->Length=0;
  for(int i=0;i<CTIMessageQueueLength;i++){
    ClearNodeData(&CQ->MSGList[i]);
  }
}

void DeleteCTIMSG(CTIMessageQueue *CQ){
  if(CQ->Length==0)return;
  ClearNodeData(&CQ->MSGList[CQ->QRear]);
  CQ->QRear++;
  CQ->Length--;
  CQ->QRear%=CTIMessageQueueLength;
  SendQueueSizeToPC(&CTIMSGQueue);
}

void DeleteLastMSG(CTIMessageQueue *CQ){  //�R�����̫�[�J���`�I
  if(CQ->Length==0)return;
  CQ->Length--;
  CQ->QFront+=CTIMessageQueueLength;
  CQ->QFront--;
  CQ->QFront%=CTIMessageQueueLength;
  ClearNodeData(&CQ->MSGList[CQ->QFront]);
  SendQueueSizeToPC(&CTIMSGQueue);
}

void DeleteAllCTIMSG(CTIMessageQueue *CQ){
  CreateCTIMSGQueue(CQ);
  SendQueueSizeToPC(&CTIMSGQueue);
}

CTIMessage GetQueueNode(CTIMessageQueue *CQ){
  return CQ->MSGList[CQ->QRear];
}

void PacketCTIMSG(CTIMessage *CQData){
  //=====================MessageStage1===================
  CQData->MessageStage1[0]='*';
  CQData->MessageStage1[1]= (CQData->GateWayID /1000)%10;
  CQData->MessageStage1[2]= (CQData->GateWayID /100)%10;
  CQData->MessageStage1[3]= (CQData->GateWayID /10)%10;
  CQData->MessageStage1[4]= (CQData->GateWayID /1)%10;
  CQData->MessageStage1[5]= (CQData->Data /100000000)%10;
  CQData->MessageStage1[6]= (CQData->Data /10000000)%10;
  CQData->MessageStage1[7]= (CQData->Data /1000000)%10;
  CQData->MessageStage1[8]= (CQData->Data /100000)%10;
  CQData->MessageStage1[9]= (CQData->Data /10000)%10;
  CQData->MessageStage1[10]=(CQData->Data /1000)%10;
  CQData->MessageStage1[11]=(CQData->Data /100)%10;
  CQData->MessageStage1[12]=(CQData->Data /10)%10;
  CQData->MessageStage1[13]=(CQData->Data /1)%10;
  //=====================MessageStage2=================== 
  CQData->MessageStage2[0]='#';
  CQData->MessageStage2[1]=(CQData->DeviceID /10)%10;
  CQData->MessageStage2[2]=(CQData->DeviceID /1)%10;
  CQData->MessageStage2[3]=(CQData->MsgType /10)%10;
  CQData->MessageStage2[4]=(CQData->MsgType /1)%10;
  
  unsigned long ETime=CQData->EncodeDateTime;
  CQData->MessageStage2[5]= (ETime /10000000)%10;
  CQData->MessageStage2[6]= (ETime /1000000)%10;
  CQData->MessageStage2[7]= (ETime /100000)%10;
  CQData->MessageStage2[8]= (ETime /10000)%10;
  CQData->MessageStage2[9]= (ETime /1000)%10;
  CQData->MessageStage2[10]=(ETime /100)%10;
  CQData->MessageStage2[11]=(ETime /10)%10;
  CQData->MessageStage2[12]=(ETime /1)%10;
  CQData->MessageStage2[13]=0;
  unsigned char Chksum=0;
  for(int i=1;i<14;i++){
    Chksum+=CQData->MessageStage1[i];
    Chksum+=CQData->MessageStage2[i];
  }
  CQData->MessageStage2[13]=Chksum%10;
  SendQueueSizeToPC(&CTIMSGQueue);
}

unsigned char DataCanRepeat(CTIMessageQueue *CQ,unsigned char DeviceID,unsigned char MSGType,unsigned long TimeEncode,unsigned long Data){
  if(MSGType<UniqueMessage){ //�Y�ǤJ���T���ݩ�i���ƪ����O�A�N�����^��1�A�����ˬd�F
    return 1;
  }
  for(int i=0;i<CTIMessageQueueLength;i++){
    if(CTIMSGQueue.MSGList[i].MsgType==MSGType)return 0;  //���F���ƪ����O�A�����\���J���
  }
  return 1; //�Y���Q�L�F�j��A�N����S�����Ƹ�ơA�h�^��1
}

unsigned char QueueNeedSendImportantData(){
  for(int i=0;i<CTIMessageQueueLength;i++){
    if((CTIMSGQueue.MSGList[i].MsgType%100)>SystemConfig_BatchTransfer)return 1;  //�Y�j��s����A�^��1
  }
  return 0; //�Y���Q�L�F�j��A�N����S�����n��ơA�h�^��0
}

void PutCTIMSG(CTIMessageQueue *CQ,unsigned char DeviceID,unsigned char MSGType,unsigned long TimeEncode,unsigned long Data){
  if(DataCanRepeat(CQ,DeviceID,MSGType,TimeEncode,Data)==0)return;  //�Y��Ƥ��i���ơA�N�������X
  
  if(CQ->Length==CTIMessageQueueLength){  //���pQUEUE�w���A�۰ʧR�����ª��@��
    DeleteCTIMSG(CQ);
  }
  
  CQ->MSGList[CQ->QFront].GateWayID=SystemConfig_CustomerID;
  CQ->MSGList[CQ->QFront].MsgType=MSGType;
  CQ->MSGList[CQ->QFront].DeviceID=DeviceID;
  CQ->MSGList[CQ->QFront].EncodeDateTime=TimeEncode;
  CQ->MSGList[CQ->QFront].Data=Data;
  CQ->MSGList[CQ->QFront].RetryCount=SystemConfig_QueueRetryCount;
  
  PacketCTIMSG(&CQ->MSGList[CQ->QFront]);
  CQ->QFront++;
  CQ->Length++;
  CQ->QFront%=CTIMessageQueueLength;
  SendQueueSizeToPC(CQ);
}

//=====================================================================================================


void RunFlow(unsigned char StateID,void (*OnEnter)(void),void (*OnExit)(void),void (*OnWork)(void),void (*OnDTMF)(void)){
//------------------------------
  A002State.State=StateID;
  A002State.OnEnter=OnEnter;
  A002State.OnExit=OnExit;
  A002State.OnWork=OnWork;
  A002State.OnDTMF=OnDTMF;  
//------------------------------
}



void InitFlow(){
  A002State.State=State_SystemCheck;
  A002State.OnEnter=SystemCheck_Enter;
  A002State.OnExit=SystemCheck_Exit;
  A002State.OnWork=SystemCheck_Work;
  
  A002State.Step=0;
}


#define State_NormalStandBy       10          //��l���A���ݾ��Ҧ�
//---------�C���m5�����۰ʱҰ�---------------
#define State_SystemCheck         60          //�t���˴��Ҧ�
//---------�t�Φ^��---------------------------
#define State_SystemReport        40          //�t�Φ^���Ҧ�
//---------�q�T�Ҧ�---------------------------
#define State_StartLine           30          //���X�q�T
//---------���Ĵ���---------------------------
#define State_Alarm               70          //���Ĵ����Ҧ�
//---------�ȪA�Ҧ�---------------------------
#define State_Service             80          //�ȪA�Ҧ�
//---------�Ͳz��ƶǿ�Ҧ�-------------------
#define State_HealthData          90          //�Ͳz��ƶǿ�Ҧ�

void GoToFlow(unsigned char StateID){
  SendQueueSizeToPC(&CTIMSGQueue);
  A002State.PreExit=A002State.OnExit;
  switch(StateID){
    case State_NormalStandBy:
      RunFlow(State_NormalStandBy,NormalStandBy_Enter,NormalStandBy_Exit,NormalStandBy_Work,0);
      break;
    case State_SystemCheck:
      RunFlow(State_SystemCheck,SystemCheck_Enter,SystemCheck_Exit,SystemCheck_Work,0);
      break;
    case State_SystemReport:
      //RunFlow(State_SystemCheck,NormalStandBy_Enter,NormalStandBy_Exit,NormalStandBy_Work,0);
      break;
    case State_StartLine:
      RunFlow(State_StartLine,StartLine_Enter,StartLine_Exit,StartLine_Work,0);
      break;
    case State_Alarm:
      RunFlow(State_Alarm,Alarm_Enter,Alarm_Exit,Alarm_Work,0);
      break;
    case State_Service:
      RunFlow(State_Service,Service_Enter,Service_Exit,Service_Work,0);
      break;
    case State_HealthData:
      //RunFlow(State_NormalPhone,NormalStandBy_Enter,NormalStandBy_Exit,NormalStandBy_Work,0);
      break;
  }
  A002State.Step=3;
}