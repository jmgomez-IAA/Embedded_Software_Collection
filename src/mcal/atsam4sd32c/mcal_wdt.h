/**
 * @file mcal_wdt.h
 * @brief Microcontroller abstraction layer for SAM4S ARM Cortex M CPU
 * @description Inicialization and definitions for the Watchdog CPU ARM Cortex M4
 * abstraction layer for the microcontroller SAM4S.
 * @author Juan Manuel Gomez Lopez <jmgomez@iaa.es>
 * @copyright 
 */


#ifndef _MCAL_WDT_ESC_
#define _MCAL_WDT_ESC_

#include <mcal_reg.h>

namespace mcal
{
  namespace wdt
  {
    typedef void config_type;
    void init(const config_type*);
    void enable(const config_type*);

    void disable();

  }
}

#endif  //_MCAL_WDT_ESC_
