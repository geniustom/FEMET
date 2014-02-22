#ifndef RangBufferLib
#define RangBufferLib


typedef struct{
    unsigned char    *Buffer;
    unsigned int    r_front,r_rear;
    unsigned int    UsedByte;
    unsigned int    Length;
}RANG_BUFFER;

#define String unsigned char *;

extern unsigned char CreatRangBuffer(RANG_BUFFER *rb,unsigned char *StaticBuf,unsigned int buffer_size);
extern void PutByte(RANG_BUFFER *rb,unsigned char d);
extern unsigned char GetByte(RANG_BUFFER *rb);
extern void SkipByte(RANG_BUFFER *rb,unsigned char skip);
extern unsigned char IsFull(RANG_BUFFER *rb);
extern unsigned char SkipALL(RANG_BUFFER *rb);
extern void GetAllData(RANG_BUFFER *rb,unsigned char *Str);
extern unsigned char SkipALL(RANG_BUFFER *rb);


#endif