/**
 * @file hal_rele.h
 * @brief Interface definition for the board.
 * @description Defines the platform ports.
 */

#ifndef _HAL_RELE_ATSAM4SXPRO_ESC_H_
#define _HAL_RELE_ATSAM4SXPRO_ESC_H_

#include <mcal/mcal.h>
#include <hal_reg.h>

namespace hal
  {
    namespace rele
    {
      typedef void config_type;
      void init(const config_type*);

      // Rele on port PIOA_20:
      extern mcal::port::port_pin<std::uint32_t,
        std::uint32_t,
        mcal::reg::pioa_base,
        hal::reg::rele_id > rele_q4_pin;
    }
  }

#endif // HAL_RELE_ATSAM4SXPRO_ESC_H_
