/**
 * @file hal_flow.h
 * @brief Interface definition for the board.
 * @description Defines the platform ports.
 */

#ifndef _HAL_FLOW_ATSAM4SXPRO_ESC_H_
#define _HAL_FLOW_ATSAM4SXPRO_ESC_H_

#include <mcal/mcal.h>
#include <hal_reg.h>

namespace hal
  {
    namespace flow
    {
      typedef void config_type;
      void init(const config_type*);

      extern mcal::port::port_pin<std::uint32_t,
        std::uint32_t,
        mcal::reg::pioa_base,
        hal::reg::flow_sensor_id > flow_sensor_pin;
    }
  }

#endif // HAL_SW_SENSORMPV1_ESC_H_
