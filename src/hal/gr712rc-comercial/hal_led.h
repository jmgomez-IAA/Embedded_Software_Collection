/**
 * @file hal_led.h
 * @brief Interface LED definition for the board.
 * @description Defines LED present in the platform ports.
 */


#ifndef _HAL_LED_GR712RCCOMERCIAL_ESC_H_
#define _HAL_LED_GR712RCCOMERCIAL_ESC_H_

#include <hal/hal.h>
#include <hal_reg.h>

namespace hal
{
namespace led
{

typedef void config_type;
void init(const config_type*);

extern mcal::port::port_pin<std::uint32_t,
                            std::uint32_t,
                            mcal::reg::grgpio1_base_address,
                            hal::reg::user_led_id > user_led_pin;

}
}

#endif //  _HAL_LED_GR712RCCOMERCIAL_ESC_H_
