
#define CPU_F ((double)1000000)
#define delay_us(x) __delay_cycles((long)(CPU_F*(double)x/1000000.0))
#define delay_ms(x) __delay_cycles((long)(CPU_F*(double)x/1000.0))
#define ADCSPI_SEL P3SEL
#define ADCSPI_SIMO BIT0
#define ADCSPI_SOMI BIT1
#define ADCSPI_SCLK BIT2
#define ADCGPIO_SEL P6DIR
#define ADCGPIO_OUT P6OUT
#define ADCCLK_SEL BIT3
#define ADC_RESET BIT1
#define ADC_START BIT2
#define ADC_CS BIT4
#define ADCDRDY_enable P2IE
#define ADCDRDY_edge P2IES
#define ADCDRDY_clear P2IFG
#define ADCDRDY_SEL BIT7

extern void Config_SPI(void);
extern void ADS1292R_Init(void);
extern void Send_CMD(unsigned char);
extern void Send_CMD_Multi(unsigned char, unsigned char, unsigned char dat[]);
