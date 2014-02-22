#include "RangBuffer.h"


unsigned char CreatRangBuffer(RANG_BUFFER *rb,unsigned char *StaticBuf,unsigned int buffer_size)
{
  rb->Buffer = StaticBuf;
  rb->r_front = 0;
  rb->r_rear = 0;
  rb->UsedByte = 0;
  rb->Length = buffer_size - 1;               //in order to the convenience
  for(int i=0;i<buffer_size;i++) rb->Buffer[i] = 0;
  return 1;
}

void SkipByte(RANG_BUFFER *rb,unsigned char skip)
{
    while(skip-- > 0 && rb->UsedByte > 0){
        rb->Buffer[rb->r_rear]=0x00;
        rb->r_rear++;
        rb->r_rear &= rb->Length;
        rb->UsedByte--;
    }
}
void PutByte(RANG_BUFFER *rb,unsigned char d)
{
    rb->Buffer[rb->r_front] = d;
    rb->r_front++;
    rb->r_front &= rb->Length;            //forms a ringed buffer
    if(rb->r_front == rb->r_rear){         //The data is overflow
        //rb->r_rear++;
        //rb->r_rear &= rb->Length;
        rb->UsedByte = rb->Length + 1;
    }
    else rb->UsedByte++;                    //either overflow or increase UsedByte
    //rb->UsedByte++;
}



/*           |<----------------------IN_BUF_LEN--------------------->|
      buffer   + + + + + + + + * * * * * * * * * * * * * - - - - - -
                  ^            ^                       ^     ^
              already read    rear                    front empty
*/

unsigned char GetByte(RANG_BUFFER *rb)
{
    unsigned char ReturnValue=0;
    if(rb->UsedByte!=0){
        ReturnValue = rb->Buffer[rb->r_rear];
        rb->UsedByte--;
        rb->r_rear++;
        rb->r_rear &= rb->Length;
    }
    return ReturnValue;
}

unsigned char IsEmpty(RANG_BUFFER *rb)
{
    //return rb->UsedByte;
    if (rb->UsedByte==0){return 1;}
    else{return 0;}
}

unsigned char IsFull(RANG_BUFFER *rb)
{
    if (rb->UsedByte==rb->Length+1){return 1;}
    else{return 0;}
}

void SetFull(RANG_BUFFER *rb)  //將buffer設成滿的狀態
{
   rb->r_front = rb->Length;
   rb->r_rear = 0;
   rb->UsedByte = rb->Length+1;
}

void ClearAll(RANG_BUFFER *rb){
  for(unsigned int i=0;i<rb->Length;i++)
      rb->Buffer[i]=0;
}

unsigned char SkipALL(RANG_BUFFER *rb)
{
    rb->r_rear = 0;
    rb->r_front = 0;
    rb->UsedByte = 0;
    //ClearAll(rb);
    return 1;
}

unsigned int GetInteger(RANG_BUFFER *rb)
{
    unsigned int ReturnValue;
//    if (rb->UsedByte < 2) return 0;
    ReturnValue = rb->Buffer[rb->r_rear];
    rb->r_rear++;
    ReturnValue |= (unsigned int)(rb->Buffer[rb->r_rear]) << 8;
    rb->r_rear++;
    rb->r_rear &= rb->Length;
    rb->UsedByte-=2;
    return ReturnValue;
}

void GetAllData(RANG_BUFFER *rb,unsigned char *Str){
  unsigned long Length=rb->Length;
  unsigned long Rear=rb->r_rear;
  for (int i=0;i<=Length;i++){
    Str[i]=rb->Buffer[Rear];
    Rear++;
    Rear&= rb->Length;
  }
}