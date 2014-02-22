#include "msp430.h"
#include "HAL_PMM.h"

#define _HAL_PMM_DISABLE_SVML_
#define _HAL_PMM_DISABLE_SVSL_
#define _HAL_PMM_DISABLE_FULL_PERFORMANCE_

#ifdef _HAL_PMM_DISABLE_SVML_
#define _HAL_PMM_SVMLE  SVMLE
#else
#define _HAL_PMM_SVMLE  0
#endif

#ifdef _HAL_PMM_DISABLE_SVSL_
#define _HAL_PMM_SVSLE  SVSLE
#else
#define _HAL_PMM_SVSLE  0
#endif

#ifdef _HAL_PMM_DISABLE_FULL_PERFORMANCE_
#define _HAL_PMM_SVSFP  SVSLFP
#define _HAL_PMM_SVMFP  SVMLFP
#else
#define _HAL_PMM_SVSFP  0
#define _HAL_PMM_SVMFP  0
#endif

/*******************************************************************************
 * \brief   Increase Vcore by one level
 *
 * \param level     Level to which Vcore needs to be increased
 * \return status   Success/failure
 ******************************************************************************/
static uint16_t SetVCoreUp(uint8_t level)
{
  uint16_t PMMRIE_backup, SVSMHCTL_backup, SVSMLCTL_backup;
   
  // The code flow for increasing the Vcore has been altered to work around
  // the erratum FLASH37. 
  // Please refer to the Errata sheet to know if a specific device is affected
  // DO NOT ALTER THIS FUNCTION

  // Open PMM registers for write access   
  PMMCTL0_H = 0xA5;
  
  // Disable dedicated Interrupts
  // Backup all registers
  PMMRIE_backup = PMMRIE;
  PMMRIE &= ~(SVMHVLRPE | SVSHPE | SVMLVLRPE | SVSLPE | SVMHVLRIE |
        SVMHIE | SVSMHDLYIE | SVMLVLRIE | SVMLIE | SVSMLDLYIE );
  SVSMHCTL_backup = SVSMHCTL;
  SVSMLCTL_backup = SVSMLCTL;

  // Clear flags
  PMMIFG = 0;

  // Set SVM highside to new level and check if a VCore increase is possible
  SVSMHCTL = SVMHE | SVSHE | (SVSMHRRL0 * level);    

  // Wait until SVM highside is settled
  while ((PMMIFG & SVSMHDLYIFG) == 0); 

  // Clear flag
  PMMIFG &= ~SVSMHDLYIFG;
  
  // Check if a VCore increase is possible
  if ((PMMIFG & SVMHIFG) == SVMHIFG) {      // -> Vcc is too low for a Vcore increase
  	// recover the previous settings
  	PMMIFG &= ~SVSMHDLYIFG;
  	SVSMHCTL = SVSMHCTL_backup;

  	// Wait until SVM highside is settled
  	while ((PMMIFG & SVSMHDLYIFG) == 0);

  	// Clear all Flags
  	PMMIFG &= ~(SVMHVLRIFG | SVMHIFG | SVSMHDLYIFG | SVMLVLRIFG | SVMLIFG | SVSMLDLYIFG);

  	PMMRIE = PMMRIE_backup;                 // Restore PMM interrupt enable register
  	PMMCTL0_H = 0x00;                       // Lock PMM registers for write access
  	return PMM_STATUS_ERROR;                // return: voltage not set
  }
  
  // Set also SVS highside to new level	    
  // Vcc is high enough for a Vcore increase
  SVSMHCTL |= (SVSHRVL0 * level);

  // Wait until SVM highside is settled
  while ((PMMIFG & SVSMHDLYIFG) == 0);    

  // Clear flag
  PMMIFG &= ~SVSMHDLYIFG;
  
  // Set VCore to new level
  PMMCTL0_L = PMMCOREV0 * level;

  // Set SVM, SVS low side to new level
  SVSMLCTL = SVMLE | (SVSMLRRL0 * level) | SVSLE | (SVSLRVL0 * level);

  // Wait until SVM, SVS low side is settled
  while ((PMMIFG & SVSMLDLYIFG) == 0);

  // Clear flag
  PMMIFG &= ~SVSMLDLYIFG;
  // SVS, SVM core and high side are now set to protect for the new core level
  
  // Restore Low side settings
  // Clear all other bits _except_ level settings
  SVSMLCTL &= (SVSLRVL0+SVSLRVL1+SVSMLRRL0+SVSMLRRL1+SVSMLRRL2);

  // Clear level settings in the backup register,keep all other bits
  SVSMLCTL_backup &= ~(SVSLRVL0+SVSLRVL1+SVSMLRRL0+SVSMLRRL1+SVSMLRRL2);
  
  // Restore low-side SVS monitor settings
  SVSMLCTL |= SVSMLCTL_backup;
  
  // Restore High side settings
  // Clear all other bits except level settings
  SVSMHCTL &= (SVSHRVL0+SVSHRVL1+SVSMHRRL0+SVSMHRRL1+SVSMHRRL2);

  // Clear level settings in the backup register,keep all other bits
  SVSMHCTL_backup &= ~(SVSHRVL0+SVSHRVL1+SVSMHRRL0+SVSMHRRL1+SVSMHRRL2);

  // Restore backup 
  SVSMHCTL |= SVSMHCTL_backup;
  
  // Wait until high side, low side settled
  while (((PMMIFG & SVSMLDLYIFG) == 0) && ((PMMIFG & SVSMHDLYIFG) == 0));

  // Clear all Flags
  PMMIFG &= ~(SVMHVLRIFG | SVMHIFG | SVSMHDLYIFG | SVMLVLRIFG | SVMLIFG | SVSMLDLYIFG);

  PMMRIE = PMMRIE_backup;                   // Restore PMM interrupt enable register
  PMMCTL0_H = 0x00;                         // Lock PMM registers for write access

  return PMM_STATUS_OK;  
}

/*******************************************************************************
 * \brief  Decrease Vcore by one level
 *
 * \param  level    Level to which Vcore needs to be decreased
 * \return status   Success/failure
 ******************************************************************************/
static uint16_t SetVCoreDown(uint8_t level)
{
  uint16_t PMMRIE_backup, SVSMHCTL_backup, SVSMLCTL_backup;
  
  // The code flow for decreasing the Vcore has been altered to work around
  // the erratum FLASH37. 
  // Please refer to the Errata sheet to know if a specific device is affected
  // DO NOT ALTER THIS FUNCTION
  
  // Open PMM registers for write access
  PMMCTL0_H = 0xA5;

  // Disable dedicated Interrupts 
  // Backup all registers
  PMMRIE_backup = PMMRIE;
  PMMRIE &= ~(SVMHVLRPE | SVSHPE | SVMLVLRPE | SVSLPE | SVMHVLRIE |
        SVMHIE | SVSMHDLYIE | SVMLVLRIE | SVMLIE | SVSMLDLYIE );
  SVSMHCTL_backup = SVSMHCTL;
  SVSMLCTL_backup = SVSMLCTL;

  // Clear flags
  PMMIFG &= ~(SVMHIFG | SVSMHDLYIFG | SVMLIFG | SVSMLDLYIFG);
  
  // Set SVM, SVS high & low side to new settings in normal mode
  SVSMHCTL = SVMHE | (SVSMHRRL0 * level) | SVSHE | (SVSHRVL0 * level);
  SVSMLCTL = SVMLE | (SVSMLRRL0 * level) | SVSLE | (SVSLRVL0 * level);
  
  // Wait until SVM high side and SVM low side is settled
  while ((PMMIFG & SVSMHDLYIFG) == 0 || (PMMIFG & SVSMLDLYIFG) == 0);
  
  // Clear flags
  PMMIFG &= ~(SVSMHDLYIFG + SVSMLDLYIFG);
  // SVS, SVM core and high side are now set to protect for the new core level
  
  // Set VCore to new level
  PMMCTL0_L = PMMCOREV0 * level;
  
  // Restore Low side settings
  // Clear all other bits _except_ level settings
  SVSMLCTL &= (SVSLRVL0+SVSLRVL1+SVSMLRRL0+SVSMLRRL1+SVSMLRRL2);
  
  // Clear level settings in the backup register,keep all other bits
  SVSMLCTL_backup &= ~(SVSLRVL0+SVSLRVL1+SVSMLRRL0+SVSMLRRL1+SVSMLRRL2);
  
  // Restore low-side SVS monitor settings
  SVSMLCTL |= SVSMLCTL_backup;
  
  // Restore High side settings
  // Clear all other bits except level settings
  SVSMHCTL &= (SVSHRVL0+SVSHRVL1+SVSMHRRL0+SVSMHRRL1+SVSMHRRL2);
  
  // Clear level settings in the backup register, keep all other bits
  SVSMHCTL_backup &= ~(SVSHRVL0+SVSHRVL1+SVSMHRRL0+SVSMHRRL1+SVSMHRRL2);
  
  // Restore backup 
  SVSMHCTL |= SVSMHCTL_backup;
  
  // Wait until high side, low side settled
  while (((PMMIFG & SVSMLDLYIFG) == 0) && ((PMMIFG & SVSMHDLYIFG) == 0));	
  
  // Clear all Flags
  PMMIFG &= ~(SVMHVLRIFG | SVMHIFG | SVSMHDLYIFG | SVMLVLRIFG | SVMLIFG | SVSMLDLYIFG);
  
  PMMRIE = PMMRIE_backup;                   // Restore PMM interrupt enable register
  PMMCTL0_H = 0x00;                         // Lock PMM registers for write access
  return PMM_STATUS_OK;		                // Return: OK
}

uint16_t SetVCore(uint8_t level)
{
  uint16_t actlevel;
  uint16_t status = 0;
  
  level &= PMMCOREV_3;                       // Set Mask for Max. level
  actlevel = (PMMCTL0 & PMMCOREV_3);         // Get actual VCore
                                             // step by step increase or decrease
  while (((level != actlevel) && (status == 0)) || (level < actlevel)) {
    if (level > actlevel) {
      status = SetVCoreUp(++actlevel);
    }
    else {
      status = SetVCoreDown(--actlevel);
    }
  }
  
  return status;
}
