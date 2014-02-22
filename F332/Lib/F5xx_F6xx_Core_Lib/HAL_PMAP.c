#include "msp430.h"
#include "HAL_PMAP.h" 

// Check and define PMAP function only if the device has port mapping capability
// Note: This macro is defined in the device-specific header file if this
// feature is available on a given MSP430.
#ifdef __MSP430_HAS_PORT_MAPPING__ 

void configure_ports(const uint8_t *port_mapping, uint8_t *PxMAPy, 
                    uint8_t num_of_ports, uint8_t port_map_reconfig)
{
  uint16_t i;
  
  // Store current interrupt state, then disable all interrupts
  uint16_t globalInterruptState = __get_SR_register() & GIE;
  __disable_interrupt();
  
  // Get write-access to port mapping registers:
  PMAPPWD = PMAPPW;
  
  if (port_map_reconfig) {
    // Allow reconfiguration during runtime:
    PMAPCTL = PMAPRECFG;
  }
  
  // Configure Port Mapping: 
  for (i = 0; i < num_of_ports * 8; i++) {
    PxMAPy[i] = port_mapping[i];
  }
  
  // Disable write-access to port mapping registers:
  PMAPPWD = 0;
  
  // Restore previous interrupt state
  __bis_SR_register(globalInterruptState);
}

#endif  /* __MSP430_HAS_PORT_MAPPING__ */
