/**
 * @file hal_port.h
 * @brief Interface definition for the board.
 * @description Defines the platform ports.
 */

#ifndef _HAL_LED_ATSAM4SXPRO_ESC_H_
#define _HAL_LED_ATSAM4SXPRO_ESC_H_

#include <mcal/mcal.h>
#include <hal_reg.h>

namespace hal
  {
    namespace led
    {
      typedef void config_type;
      void init(const config_type*);

      extern mcal::port::port_pin<std::uint32_t,
                                  std::uint32_t,
                                  mcal::reg::pioc_base,
                                  hal::reg::user_led_id > user_led_pin;
    }
  }

#endif // HAL_LED_ATSAM4SXPRO_ESC_H_
