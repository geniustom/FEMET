#ifndef HAL_WHEEL_H
#define HAL_WHEEL_H

#include <stdint.h>

extern void Wheel_init(void);
extern uint8_t Wheel_getPosition(void);
extern uint16_t Wheel_getValue(void);
extern void Wheel_disable(void);
extern void Wheel_enable(void);

#endif /* HAL_WHEEL_H */
