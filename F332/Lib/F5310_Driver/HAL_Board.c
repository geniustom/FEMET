
/***************************************************************************//**
 * @file       HAL_Board.c
 * @addtogroup HAL_Board
 * @{
 ******************************************************************************/
#include "msp430.h"
#include "HAL_Board.h"
#include "HAL_UCS.h"
#include "HAL_PMM.h"

#define XT1_XT2_PORT_DIR            P5DIR
#define XT1_XT2_PORT_OUT            P5OUT
#define XT1_XT2_PORT_SEL            P5SEL
#define XT1_ENABLE                  (BIT4 + BIT5)
#define XT2_ENABLE                  (BIT2 + BIT3)


/***************************************************************************//**
 * @brief  Initialize the board - configure ports
 * @param  None
 * @return none
 ******************************************************************************/

void Board_init(void)
{
    // Setup XT1 and XT2
    XT1_XT2_PORT_SEL |= XT1_ENABLE + XT2_ENABLE;

 /*   
    // Configure button ports
    PADIR &= ~0x0480;               // Buttons on P1.7/P2.2 are inputs


    // Configure SDCard ports
    P3OUT |= BIT7;                  // SD_CS to high
    P3DIR |= BIT7;


    // Configure unused ports for low power
    P2OUT &= ~(BIT0 + BIT1 + BIT3 + BIT4 + BIT6);
    P2DIR |= BIT0 + BIT1 + BIT3 + BIT4 + BIT6;

    P3OUT &= ~(BIT0 + BIT1 + BIT2);
    P3DIR |= BIT0 + BIT1 + BIT2;

    P4OUT &= ~(BIT0 + BIT6 + BIT7);
    P4DIR |= BIT0 + BIT6 + BIT7;

    P5OUT &= ~BIT1;
    P5DIR |= BIT1;

    P6OUT &= ~(BIT6 + BIT7);
    P6DIR |= BIT6 + BIT7;
*/
}


void DCOClk_init(){
    // Set Vcore to accomodate for max. allowed system speed
    SetVCore(3);
    // Use 32.768kHz XTAL as reference
    LFXT_Start(XT1DRIVE_0);
    // Set system clock to max (25MHz)
    Init_FLL_Settle(25000, 763);
    //Init_FLL_Settle(4000, 122);
    SFRIFG1 = 0;
    SFRIE1 |= OFIE;
}

void XT2Clk_init(void)
{
    SetVCore(3);
 
    P5SEL  |= BIT2 + BIT3;                    // Port select XT2
    UCSCTL6 &= ~XT2OFF;                       // Enable XT2
    UCSCTL3 |= SELREF_2;                      // FLLref = REFO
    UCSCTL4 |= SELA__REFOCLK;                 // ACLK=REFO(32.768kHz),SMCLK=DCO,MCLK=DCO
    do
    {                                         // Clear XT2,XT1,DCO fault flags                                             
        UCSCTL7 &= ~(XT2OFFG + XT1LFOFFG + DCOFFG);                                                    
        SFRIFG1 &= ~OFIFG;                    // Clear fault flags
    }while (SFRIFG1&OFIFG);                   // Test oscillator fault flag

    UCSCTL6 &= ~(XT2DRIVE0 + XT2DRIVE1);      // Decrease XT2 Drive according to expected frequency                                             
    UCSCTL6 |= XT2DRIVE_2;                    // XT2 Drive Level mode: 2, XT2: 16MHz~24MHz                      
    UCSCTL4 |= SELS_5 + SELM_5;               // SMCLK=MCLK=XT2
} 

void REFOClk_Init(void){
  //ACLK = REFO = 32kHz, MCLK = SMCLK = 25MHz  
  UCSCTL3 |= SELREF_2;                      // Set DCO FLL reference = REFO  
  UCSCTL4 |= SELA_2;                        // Set ACLK = REFO  
  
  __bis_SR_register(SCG0);                  // Disable the FLL control loop  
  UCSCTL0 = 0x0000;                         // Set lowest possible DCOx, MODx  
  UCSCTL1 = DCORSEL_7;                      // Select DCO range 25MHz operation  
  UCSCTL2 = 762 + FLLD_1;                   // Set DCO Multiplier for 25MHz  
                                          // (N + 1) * FLLRef = Fdco  
                                          // (762 + 1) * 32768 = 25MHz  
                                          // Set FLL Div = fDCOCLK/2  
  __bic_SR_register(SCG0);                  // Enable the FLL control loop  
  
  // Worst-case settling time for the DCO when the DCO range bits have been  
  // changed is n x 32 x 32 x f_MCLK / f_FLL_reference. See UCS chapter in 5xx  
  // UG for optimization.  
  // 32 x 32 x 25 MHz / 32,768 Hz = 782000 = MCLK cycles for DCO to settle  
  __delay_cycles(782000);  
  
  // Loop until XT1,XT2 & DCO fault flag is cleared  
  do{  
    UCSCTL7 &= ~(XT2OFFG + XT1LFOFFG + DCOFFG);  
                                          // Clear XT2,XT1,DCO fault flags  
    SFRIFG1 &= ~OFIFG;                      // Clear fault flags  
  }while (SFRIFG1&OFIFG);                   // Test oscillator fault flag     
}

/***************************************************************************//**
 * @}
 ******************************************************************************/
