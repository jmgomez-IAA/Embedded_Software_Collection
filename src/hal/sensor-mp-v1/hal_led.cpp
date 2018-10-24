
#include <hal_led.h>

/**
 * User led LED0, yellow color, when the pin is driven to GND the led turn on.
 */
mcal::port::port_pin<std::uint32_t,
                     std::uint32_t,
                     mcal::reg::pioa_base,
                     hal::reg::user_led_id > hal::led::user_led_pin;

// LED on port pin PIOA_15 : D14
mcal::port::port_pin<std::uint32_t,
                     std::uint32_t,
                     mcal::reg::pioa_base,
                     hal::reg::d14_led_id > hal::led::led_d14_pin;

void hal::led::init(const config_type*)
{

  // Define the led pin as an output
  user_led_pin.set_direction_output();
}
