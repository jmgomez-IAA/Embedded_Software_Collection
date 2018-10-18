
#include <hal_led.h>

/**
 * User led LED0, yellow color, when the pin is driven to GND the led turn on.
 */
mcal::port::port_pin<std::uint32_t,
                     std::uint32_t,
                     mcal::reg::pioc_base,
                     hal::reg::user_led_id > hal::led::user_led_pin;

void hal::led::init(const config_type*)
{

  // Define the led pin as an output
  user_led_pin.set_direction_output();
}
