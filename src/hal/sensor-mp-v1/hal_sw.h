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

      extern mcal::port::port_pin<std::uint32_t,
        std::uint32_t,
        mcal::reg::pioa_base,
        hal::reg::sw3_button_id > sw3_button_pin;

      extern mcal::port::port_pin<std::uint32_t,
        std::uint32_t,
        mcal::reg::pioa_base,
        hal::reg::addr0_button_id >  addr0_pin;

      extern mcal::port::port_pin<std::uint32_t,
        std::uint32_t,
        mcal::reg::pioa_base,
        hal::reg::addr1_button_id >  addr1_pin;

      extern mcal::port::port_pin<std::uint32_t,
        std::uint32_t,
        mcal::reg::pioa_base,
        hal::reg::addr2_button_id >  addr2_pin;

      extern mcal::port::port_pin<std::uint32_t,
        std::uint32_t,
        mcal::reg::pioa_base,
        hal::reg::addr3_button_id >  addr3_pin;

      extern mcal::port::port_pin<std::uint32_t,
        std::uint32_t,
        mcal::reg::pioa_base,
        hal::reg::addr4_button_id >  addr4_pin;

      extern mcal::port::port_pin<std::uint32_t,
        std::uint32_t,
        mcal::reg::pioa_base,
        hal::reg::addr5_button_id >  addr5_pin;

      extern mcal::port::port_pin<std::uint32_t,
        std::uint32_t,
        mcal::reg::pioa_base,
        hal::reg::addr6_button_id >  addr6_pin;

      extern mcal::port::port_pin<std::uint32_t,
        std::uint32_t,
        mcal::reg::pioa_base,
        hal::reg::addr7_button_id >  addr7_pin;
    }
  }

#endif // HAL_SW_SENSORMPV1_ESC_H_
