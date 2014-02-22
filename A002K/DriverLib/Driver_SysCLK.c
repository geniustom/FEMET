#include "DriverLib.h"


void SetVCoreUp (unsigned char VCore)
{
  PMMCTL0_H = 0xA5;                         // Open PMM module registers for write access
  PMMCTL0 = 0xA500 + (VCore * PMMCOREV0);   // Set VCore to new VCore
  SVSMLCTL = (SVSMLCTL & ~(3 * SVSMLRRL0)) + SVMLE + (VCore * SVSMLRRL0);  // Set SVM new Level    
  while ((PMMIFG & SVSMLDLYIFG) == 0);      // Wait till SVM is settled (Delay)
  PMMIFG &= ~(SVMLVLRIFG + SVMLIFG);        // Clear already set flags
  if ((PMMIFG & SVMLIFG))
    while ((PMMIFG & SVMLVLRIFG) == 0);     // Wait till level is reached
  SVSMLCTL &= ~SVMLE;                       // Disable Low side SVM
  PMMCTL0_H = 0x00;                         // Lock PMM module registers for write access
}


//****************************************************************************//
// Set VCore down 
//****************************************************************************//
void SetVCoreDown (unsigned char VCore)
{
  PMMCTL0_H = 0xA5;                         // Open PMM module registers for write access
  SVSMLCTL = (SVSMLCTL & ~(3 * SVSMLRRL0)) + SVMLE + (VCore * SVSMLRRL0);  // Set SVM new Level    
  while ((PMMIFG & SVSMLDLYIFG) == 0);      // Wait till SVM is settled (Delay)
  PMMCTL0 = 0xA500 + (VCore * PMMCOREV0);   // Set VCore to 1.85 V for Max Speed.
  SVSMLCTL &= ~SVMLE;                       // Disable Low side SVM
  PMMCTL0_H = 0x00;                         // Lock PMM module registers for write access
}


void SetVCore (unsigned char VCore)
{
  unsigned int currentVCore;

  currentVCore = PMMCTL0 & PMMCOREV_3;      // Get actual VCore  
  while (VCore != currentVCore) 
  {   
    if (VCore > currentVCore) 
      SetVCoreUp(++currentVCore);
    else
      SetVCoreDown(--currentVCore);
  }
  
}

void GetSystemClockSettings(unsigned char systemClockSpeed,
                            unsigned char *setDcoRange,
                            unsigned char *setVCore,
                            unsigned int *setMultiplier){
	switch (systemClockSpeed)
	{
		case SYSCLK_1MHZ: 
	    *setDcoRange = DCORSEL_1MHZ;
	    *setVCore = VCORE_1MHZ;
	    *setMultiplier = DCO_MULT_1MHZ;
	    break;
		case SYSCLK_4MHZ: 
	    *setDcoRange = DCORSEL_4MHZ;
	    *setVCore = VCORE_4MHZ;
	    *setMultiplier = DCO_MULT_4MHZ;
	    break;
		case SYSCLK_8MHZ: 
	    *setDcoRange = DCORSEL_8MHZ;
	    *setVCore = VCORE_8MHZ;
	    *setMultiplier = DCO_MULT_8MHZ;
	    break;
		case SYSCLK_12MHZ: 
	    *setDcoRange = DCORSEL_12MHZ;
	    *setVCore = VCORE_12MHZ;
	    *setMultiplier = DCO_MULT_12MHZ;
	    break;
		case SYSCLK_16MHZ: 
	    *setDcoRange = DCORSEL_16MHZ;
	    *setVCore = VCORE_16MHZ;
	    *setMultiplier = DCO_MULT_16MHZ;
	    break;
		case SYSCLK_20MHZ: 
	    *setDcoRange = DCORSEL_20MHZ;
	    *setVCore = VCORE_20MHZ;
	    *setMultiplier = DCO_MULT_20MHZ;
	    break;
		case SYSCLK_25MHZ: 
	    *setDcoRange = DCORSEL_25MHZ;
	    *setVCore = VCORE_25MHZ;
	    *setMultiplier = DCO_MULT_25MHZ;
	    break;	     
	}	
}


void StartXT1()
{
	// Set up XT1 Pins to analog function, and to lowest drive	
  P7SEL |= 0x03;                            
  UCSCTL6 &= ~XT1DRIVE_3;
  UCSCTL6 |= XCAP_3 ;
  while ( (SFRIFG1 &OFIFG))
  {    
    UCSCTL7 &= ~(XT1LFOFFG + DCOFFG);
    SFRIFG1 &= ~OFIFG;
  }
}


void SetSystemClock(unsigned char systemClockSpeed){
  unsigned char setDcoRange, setVCore;
  unsigned int setMultiplier;

  GetSystemClockSettings( systemClockSpeed, &setDcoRange, &setVCore, &setMultiplier);
  	
  if (setVCore > (PMMCTL0 & PMMCOREV_3))		// Only change VCore if necessary
    SetVCore( setVCore );   
  UCSCTL0 = 0x00;                           // Set lowest possible DCOx, MODx
  UCSCTL1 = setDcoRange;                    // Select suitable range
  
  UCSCTL2 = setMultiplier + FLLD_1;         // Set DCO Multiplier
  UCSCTL4 = SELA__XT1CLK | SELS__DCOCLKDIV  |  SELM__DCOCLKDIV ;
}

