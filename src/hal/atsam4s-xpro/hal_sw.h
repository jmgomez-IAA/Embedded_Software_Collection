/**
 * @file hal_sw.h
 * @brief Interface definition for the board.
 * @description Defines the platform ports.
 */

#ifndef _HAL_SW_ATSAM4SXPRO_ESC_H_
#define _HAL_SW_ATSAM4SXPRO_ESC_H_

#include <mcal/mcal.h>
#include <hal_reg.h>

namespace hal
  {
    namespace sw
    {
      typedef void config_type;
      void init(const config_type*);

      extern mcal::port::port_pin<std::uint32_t,
                                  std::uint32_t,
                                  mcal::reg::pioa_base,
                                  hal::reg::user_button_id > user_button_pin;
    }
  }

#endif // HAL_SW_ATSAM4SXPRO_ESC_H_
