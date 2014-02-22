#ifndef MeaDevLib
#define MeaDevLib


extern void MEADEV_InitDevice();
extern void MEADEV_SetDeviceTime();
extern void MEADEV_ClearFlash();
extern void MEADEV_GetDeviceVER();
extern unsigned char MEADEV_GetDeviceData(unsigned char User);
extern unsigned char MEADEV_GetDeviceDataMulti(unsigned char User);
#endif