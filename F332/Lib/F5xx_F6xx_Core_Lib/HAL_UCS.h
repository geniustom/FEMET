#ifndef HAL_UCS_H
#define HAL_UCS_H

#include <stdint.h>
#include "hal_macros.h"

/*******************************************************************************
 * Macros
 ******************************************************************************/

/* Select source for FLLREF  e.g. SELECT_FLLREF(SELREF__XT1CLK) */
#define SELECT_FLLREF(source) st(UCSCTL3 = (UCSCTL3 & ~(SELREF_7)) | (source);) 
/* Select source for ACLK    e.g. SELECT_ACLK(SELA__XT1CLK) */
#define SELECT_ACLK(source)   st(UCSCTL4 = (UCSCTL4 & ~(SELA_7))   | (source);) 
/* Select source for MCLK    e.g. SELECT_MCLK(SELM__XT2CLK) */
#define SELECT_MCLK(source)   st(UCSCTL4 = (UCSCTL4 & ~(SELM_7))   | (source);) 
/* Select source for SMCLK   e.g. SELECT_SMCLK(SELS__XT2CLK) */
#define SELECT_SMCLK(source)  st(UCSCTL4 = (UCSCTL4 & ~(SELS_7))   | (source);) 
/* Select source for MCLK and SMCLK e.g. SELECT_MCLK_SMCLK(SELM__DCOCLK + SELS__DCOCLK) */
#define SELECT_MCLK_SMCLK(sources) st(UCSCTL4 = (UCSCTL4 & ~(SELM_7 + SELS_7)) | (sources);)

/* set ACLK/x */
#define ACLK_DIV(x)         st(UCSCTL5 = (UCSCTL5 & ~(DIVA_7)) | (DIVA__##x);)     
/* set MCLK/x */
#define MCLK_DIV(x)         st(UCSCTL5 = (UCSCTL5 & ~(DIVM_7)) | (DIVM__##x);)     
/* set SMCLK/x */
#define SMCLK_DIV(x)        st(UCSCTL5 = (UCSCTL5 & ~(DIVS_7)) | (DIVS__##x);)     
/* Select divider for FLLREF  e.g. SELECT_FLLREFDIV(2) */
#define SELECT_FLLREFDIV(x) st(UCSCTL3 = (UCSCTL3 & ~(FLLREFDIV_7))|(FLLREFDIV__##x);) 

/*******************************************************************************
 * Defines
 ******************************************************************************/
#define UCS_STATUS_OK     0
#define UCS_STATUS_ERROR  1

/*******************************************************************************
 * \brief   Startup routine for 32kHz Crystal on LFXT1
 *
 * \param xtdrive   Bits defining the LFXT drive mode after startup
 ******************************************************************************/
extern void LFXT_Start(uint16_t xtdrive);

/*******************************************************************************
 * \brief   Startup routine for 32kHz Crystal on LFXT1 with timeout counter
 *
 * \param xtdrive   Bits defining the LFXT drive mode after startup
 * \param timeout   Value for the timeout counter
 ******************************************************************************/
extern uint16_t LFXT_Start_Timeout(uint16_t xtdrive, uint16_t timeout);

/*******************************************************************************
 * \brief   Startup routine for XT1
 *
 * \param xtdrive   Bits defining the XT drive mode
 ******************************************************************************/
extern void XT1_Start(uint16_t xtdrive);

/*******************************************************************************
 * \brief   Startup routine for XT1 with timeout counter
 *
 * \param xtdrive   Bits defining the XT drive mode
 * \param timeout   Value for the timeout counter
 ******************************************************************************/
extern uint16_t XT1_Start_Timeout(uint16_t xtdrive, uint16_t timeout);

/*******************************************************************************
 * \brief   Use XT1 in Bypasss mode
 ******************************************************************************/
extern void XT1_Bypass(void);

/*******************************************************************************
 * \brief   Stop XT1 oscillator
 ******************************************************************************/
extern void XT1_Stop(void);

/*******************************************************************************
 * \brief   Startup routine for XT2
 *
 * \param xtdrive   Bits defining the XT drive mode
 ******************************************************************************/
extern void XT2_Start(uint16_t xtdrive);

/*******************************************************************************
 * \brief   Startup routine for XT2 with timeout counter
 *
 * \param xtdrive   Bits defining the XT drive mode
 * \param timeout   Value for the timeout counter
 ******************************************************************************/
extern uint16_t XT2_Start_Timeout(uint16_t xtdrive, uint16_t timeout);

/*******************************************************************************
 * \brief   Use XT2 in Bypasss mode for MCLK
 ******************************************************************************/
extern void XT2_Bypass(void);

/*******************************************************************************
 * \brief   Stop XT2 oscillator
 ******************************************************************************/
extern void XT2_Stop(void);

/*******************************************************************************
 * \brief   Initializes FLL of the UCS and wait till settled before allowing
 *          code execution to resume. The use of this function is preferred
 *          over the use of Init_FLL().
 *
 * \param fsystem  Required system frequency (MCLK) in kHz
 * \param ratio    Ratio between fsystem and FLLREFCLK
 ******************************************************************************/
extern void Init_FLL_Settle(uint16_t fsystem, uint16_t ratio);

/*******************************************************************************
 * \brief   Initializes FLL of the UCS
 *
 * \param fsystem  Required system frequency (MCLK) in kHz
 * \param ratio    Ratio between fsystem and FLLREFCLK
 ******************************************************************************/
extern void Init_FLL(uint16_t fsystem, uint16_t ratio);

#endif /* HAL_UCS_H */
