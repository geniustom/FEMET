#ifndef HAL_BUTTONS_H
#define HAL_BUTTONS_H

#include <stdint.h>

#define BUTTON_S2       0x0400
#define BUTTON_S1       0x0080
#define BUTTON_ALL      0x0480

volatile extern uint16_t buttonsPressed;
volatile extern uint8_t buttonDebounce;

extern void Buttons_init(uint16_t buttonsMask);
extern void Buttons_interruptEnable(uint16_t buttonsMask);
extern void Buttons_interruptDisable(uint16_t buttonsMask);

#endif /* HAL_BUTTONS_H */
