/**
 * @file platform.cpp
 * @brief platform abstraction layer
 * @description Include the initialization and hardware
 * abstraction for the microcontroller.
 * @author Juan Manuel Gomez Lopez <jmgomez@iaa.es>
 * @copyright 
 */

#include <hal/hal.h>

void hal::init()
{

  hal::led::init(nullptr);
  hal::sw::init(nullptr);

}
