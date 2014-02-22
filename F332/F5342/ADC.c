#include <msp430f5342.h>
#include "ADC.h"


void Config_SPI(void)
{
// SPI initialization
ADCSPI_SEL = ADCSPI_SIMO|ADCSPI_SOMI|ADCSPI_SCLK;                   // Set Pin Function for SPI Mode
UCB0CTL1 |= UCSWRST;                      // **Put state machine in reset**
UCB0CTL0 |= UCMST+UCSYNC+UCMSB;           // 3-pin, 8-bit SPI master
                                          // Clock polarity high, MSB
UCB0CTL1 |= UCSSEL_2;                     // SMCLK
UCB0BR0 = 0x61;                           // /2
UCB0BR1 = 0;                              //
//UCB0MCTL = 0;                           // No modulation
UCB0CTL1 &= ~UCSWRST;                     // **Initialize USCI state machine**
}


void ADS1292R_Init(void)
{
    Config_SPI();

    unsigned char dat[3];
    // set related pins with ADS1292R
    ADCGPIO_SEL |= ADCCLK_SEL;                 // P2.3 -> CLK_SEL
    ADCGPIO_SEL |= ADC_RESET + ADC_START + ADC_CS;   // P8.0 -> RESET', P8.1 -> START, P8.2 -> CS'


    // indicate ADS1292R use internal clock
    ADCGPIO_OUT |= ADCCLK_SEL;              // indicate ADS1292R use internal clock
    __delay_cycles(2000);       // wait for oscillator to wake up

    // wait for 1s for ADS1292R's power-on reset
    ADCGPIO_OUT |= ADC_RESET;				 // set RESET'=1
    delay_ms(1000);             // wait for 1s for power-on reset


    // reset ADS1292R & CS' pin tied low
    ADCGPIO_OUT &= ~ADC_RESET;			 // issue reset pulse
    __delay_cycles(720);         // wait 0.1s
    ADCGPIO_OUT |= ADC_RESET;              // clear reset
    ADCGPIO_OUT &= ~ADC_CS;             // CS' tied permanently low

    // send command
    Send_CMD(0x11);			 		 // sent SDATAC command
    __delay_cycles(160);
    dat[0]=0x00,dat[1]=0xA8;                        // CONFIG2 = A0;
    Send_CMD_Multi(0x40+0x01, 2, dat);  // Config. CONFIG2 = 0xA0 to use internal reference
    dat[0]=0x2C;						 // RLDSENS = 2C;
    Send_CMD_Multi(0x40+0x06, 1, dat);  // right leg drive

    // DRDY' interrupt
	ADCDRDY_enable |= ADCDRDY_SEL;              // P1.0 interrupt enabled
	ADCDRDY_edge |= ADCDRDY_SEL;             // P1.0 Hi/lo edge
	ADCDRDY_clear &= ~ADCDRDY_SEL;            // P1.0 IFG cleared

    // START = 1
    ADCGPIO_OUT |= ADC_START;						 // START = 1

    // send continue mode command
    Send_CMD(0x10);					 // enter the continue mode
}

void Send_CMD(unsigned char cmd)
{
     while (!(UCB0IFG&UCTXIFG));                         // USCI_B0 TX buffer ready?
     UCB0TXBUF = cmd;                                    // Transmit data
}

void Send_CMD_Multi(unsigned char cmd,unsigned char len,unsigned char dat[])
{
     unsigned char i;
     Send_CMD(cmd);
     Send_CMD(len-1);
     for(i=0;i<len;i++)
     {
         Send_CMD(dat[i]);
     }
}