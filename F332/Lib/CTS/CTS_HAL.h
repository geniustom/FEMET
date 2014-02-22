/***************************************************************************//**
 * @file   CTS_HAL.h
 *
 * @brief       
 *
 * @par    Project:
 *             MSP430 Capacitive Touch Library 
 *
 * @par    Developed using:
 *             IAR Version : 5.10.6 [Kickstart] (5.10.6.30180)
 *             CCS Version : 4.2.1.00004, w/support for GCC extensions (--gcc)
 *
 *
 * @version     1.0.0 Initial Release
 *
 * @par    Supported Hardware Configurations:
 *              - TI_CTS_RO_COMPAp_TA0_WDTp_HAL()
 *              - TI_CTS_fRO_COMPAp_TA0_SW_HAL()
 *              - TI_CTS_fRO_COMPAp_SW_TA0_HAL()
 *              - TI_CTS_RO_COMPAp_TA1_WDTp_HAL()
 *              - TI_CTS_fRO_COMPAp_TA1_SW_HAL()
 *              - TI_CTS_RC_PAIR_TA0_HAL()
 *              - TI_CTS_RO_PINOSC_TA0_WDTp_HAL()
 *              - TI_CTS_RO_PINOSC_TA0_HAL()
 *              - TI_CTS_fRO_PINOSC_TA0_SW_HAL()
 *              - TI_CTS_RO_COMPB_TA0_WDTA_HAL()
 *              - TI_CTS_RO_COMPB_TA1_WDTA_HAL()
 *              - TI_CTS_fRO_COMPB_TA0_SW_HAL()
 *              - TI_CTS_fRO_COMPB_TA1_SW_HAL()
 ******************************************************************************/

#ifndef CAP_TOUCH_HAL
#define CAP_TOUCH_HAL

#include "structure.h"

void TI_CTS_RO_COMPAp_TA0_WDTp_HAL(const struct Sensor *, uint16_t *);

void TI_CTS_fRO_COMPAp_TA0_SW_HAL(const struct Sensor *, uint16_t *);

void TI_CTS_fRO_COMPAp_SW_TA0_HAL(const struct Sensor *, uint16_t *);

void TI_CTS_RO_COMPAp_TA1_WDTp_HAL(const struct Sensor *, uint16_t *);

void TI_CTS_fRO_COMPAp_TA1_SW_HAL(const struct Sensor *, uint16_t *);

void TI_CTS_RC_PAIR_TA0_HAL(const struct Sensor *, uint16_t *);

void TI_CTS_RO_PINOSC_TA0_WDTp_HAL(const struct Sensor *, uint16_t *);

void TI_CTS_RO_PINOSC_TA0_HAL(const struct Sensor *, uint16_t *);

void TI_CTS_fRO_PINOSC_TA0_SW_HAL(const struct Sensor *, uint16_t *);

void TI_CTS_RO_COMPB_TA0_WDTA_HAL(const struct Sensor *, uint16_t *);

void TI_CTS_fRO_COMPB_TA0_SW_HAL(const struct Sensor *, uint16_t *);

void TI_CTS_RO_COMPB_TA1_WDTA_HAL(const struct Sensor *, uint16_t *);

void TI_CTS_fRO_COMPB_TA1_SW_HAL(const struct Sensor *, uint16_t *);

#endif
