#include "DriverLib.h"


void SetVoice(unsigned char VLevel){
  P11DIR  =  BIT0 | BIT1 | BIT2;
  P11OUT  =  (VLevel & 0x07);
}

unsigned char GetVoice(){
  return (P11OUT & 0x07);
}
