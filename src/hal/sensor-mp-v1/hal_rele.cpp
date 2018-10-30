
#include <hal_rele.h>

/**
 * Rele actuator, when the pin is driven to 1 rele closes..
 */
mcal::port::port_pin<std::uint32_t,
                     std::uint32_t,
                     mcal::reg::pioa_base,
                     hal::reg::rele_id > hal::rele::rele_q4_pin;

void hal::rele::init(const config_type*)
{

  // Define the led pin as an output
  rele_q4_pin.set_direction_output();
  rele_q4_pin.disable_pull_up();
  rele_q4_pin.enable_pull_down();
}
