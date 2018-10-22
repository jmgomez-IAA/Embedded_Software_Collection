/**
 * @file mcal.h
 * @brief Microcontroller abstraction layer
 * @description Include the initialization and hardware
 * abstraction for the microcontroller.
 * @author Juan Manuel Gomez Lopez <jmgomez@iaa.es>
 * @copyright 
 */

#ifndef _MCAL_ESC_2018_
#define _MCAL_ESC_2018_

#include <mcal_cpu.h>
#include <mcal_port.h>
#include <mcal_spw.h>

namespace mcal
{
  void init();
}

#endif //_MCAL_ESC_2018_
