/**
 * @file mcal.h
 * @brief Microcontroller abstraction layer
 * @description Include the initialization and hardware
 * abstraction for the microcontroller.
 * @author Juan Manuel Gomez Lopez <jmgomez@iaa.es>
 * @copyright 
 */

#ifndef _HAL_ESC_2018_
#define _HAL_ESC_2018_

#include <mcal/mcal.h>
#include <hal_led.h>
#include <hal_sw.h>
#include <hal_rele.h>
#include <hal_flow.h>

namespace hal
{
  void init();
}

#endif // _HAL_ESC_2018_
