#ifndef HAL_BOARD_H
#define HAL_BOARD_H

#include <stdint.h>

#define LED1        0x01
#define LED2        0x02
#define LED3        0x04
#define LED4        0x08
#define LED5        0x10
#define LED6        0x20
#define LED7        0x40
#define LED8        0x80
#define LED_ALL     0xFF

extern void Board_init(void);
extern void Board_ledOn(uint8_t ledMask);
extern void Board_ledOff(uint8_t ledMask);
extern void Board_ledToggle(uint8_t ledMask);

#endif /* HAL_BOARD_H */
