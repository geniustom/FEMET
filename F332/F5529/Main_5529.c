#include <stdint.h>
#include "msp430.h"
//==============================Hardware Layer===========================
#include "HAL_PMM.h"
#include "HAL_UCS.h"
#include "HAL_Board.h"
#include "HAL_Buttons.h"
#include "HAL_Dogs102x6.h"
#include "HAL_Menu.h"
#include "HAL_Wheel.h"
#include "HAL_Uart.h"
//============================Application Layer==========================
#include "SdCard.h"
#include "Bluetooth.h"



static const char *const mainMenu[] = {
    "=MSP-EXP430F5529=",
    "1. Continue Write",
    "2. SD Card Write ",
    "3. SD Card Read  ",
    "4. BlueToothWrite",
    "5. Reserve       ",
    "6. Reserve       ",
};

void System_Init(void){
    // Stop WDT
    WDTCTL = WDTPW + WDTHOLD;
    // Basic GPIO initialization
    Board_init();
    // Set Vcore to accomodate for max. allowed system speed
    SetVCore(3);
    // Use 32.768kHz XTAL as reference
    LFXT_Start(XT1DRIVE_0);
    // Set system clock to max (25MHz)
    Init_FLL_Settle(25000, 762);
    SFRIFG1 = 0;
    SFRIE1 |= OFIE;
    // Globally enable interrupts
    __enable_interrupt();
}

void LCD_Init(void){
    // Set up LCD
    Dogs102x6_init();
    Dogs102x6_backlightInit();
    //Dogs102x6_setBacklight(05);
    //Dogs102x6_setContrast(11);
    Dogs102x6_clearScreen(); 
}

void main(void)
{
    System_Init();
    LCD_Init();
    Bluetooth_init();

    // Set up wheel
    Wheel_init();
    Buttons_init(BUTTON_ALL);
    Buttons_interruptEnable(BUTTON_ALL);
    buttonsPressed = 0;
    
    // Main loop
    while (1)
    {
      BlueToothWrite("Hello~~\r\n",9);
/*      
        Dogs102x6_stringDraw(7, 0, "*S1=Enter S2=Esc*", DOGS102x6_DRAW_NORMAL);
        switch (Menu_active((char **)mainMenu, 4))
        {
            case 1: ContinueWriteTest();   break;
            case 2: WriteTest();   break;
            case 3: SDCard();    break;
            case 4: BlueToothWrite("Hello~~\r\n",9); break;
            default: break;
        }
*/
    }
}
