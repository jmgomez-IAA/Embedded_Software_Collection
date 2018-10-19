
#include <hal_sw.h>

/**
 * User button SW0, when pressed drive the line to GND.
 */
mcal::port::port_pin<std::uint32_t,
                     std::uint32_t,
                     mcal::reg::grgpio1_base_address,
                     hal::reg::user_button_id > hal::sw::user_button_pin;

void hal::sw::init(const config_type*)
{

  // Define the user button as input, with pull down enabled.
  user_button_pin.set_direction_input();

}
