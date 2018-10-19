
#include <hal_led.h>

/**
 * User led TP22, on pin 190 which is GPIO26, migth be used as a LED.
 */
mcal::port::port_pin<std::uint32_t,
                     std::uint32_t,
                     mcal::reg::grgpio1_base_address,
                     hal::reg::user_led_id > hal::led::user_led_pin;

void hal::led::init(const config_type*)
{

  // Define the led pin as an output
  user_led_pin.set_direction_output();
}
