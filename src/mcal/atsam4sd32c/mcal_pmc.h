/**
 * @file mcal_pmc.h
 * @brief Microcontroller abstraction layer for PMC SAM4S ARM Cortex M CPU
 * @description Inicialization and definitions for the CPU ARM Cortex M4
 * abstraction layer for the Power Management Controller of the SAM4S. There
 * manyt clock sources and elements that may be enabled/disabled.
 * @author Juan Manuel Gomez Lopez <jmgomez@iaa.es>
 * @copyright 
 */

#ifndef _MCAL_PMC_SAM4S_EMBEDDED_2018_
#define _MCAL_PMC_SAM4S_EMBEDDED_2018_

#include <cstdint>

namespace mcal
{
  namespace pmc
  {
    typedef void config_type;
    void init(const config_type*);
    void enable_pck(const config_type*);

    static constexpr addr_type  master_clock_controller         = addr_type(port + 0x00UL);;
  }
}


#endif  //_MCAL_PMC_SAM4S_EMBEDDED_2018
