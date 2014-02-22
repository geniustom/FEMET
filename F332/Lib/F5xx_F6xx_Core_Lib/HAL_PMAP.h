#ifndef HAL_PMAP_H
#define HAL_PMAP_H

#include <stdint.h>

/*******************************************************************************
 * \brief   Configures the MSP430 Port Mapper
 *
 * \param *port_mapping     Pointer to init Data
 * \param PxMAPy            Pointer start of first Port Mapper to initialize
 * \param num_of_ports      Number of Ports to initialize
 * \param port_map_reconfig Flag to enable/disable reconfiguration
 *
 ******************************************************************************/
extern void configure_ports(const uint8_t *port_mapping, uint8_t *PxMAPy, 
                            uint8_t num_of_ports, uint8_t port_map_reconfig);

#endif /* HAL_PMAP_H */
