
#include <hal_flow.h>

/**
 * User button SW0, when pressed drive the line to GND.
 */
mcal::port::port_pin<std::uint32_t,
                     std::uint32_t,
                     mcal::reg::pioa_base,
                     hal::reg::flow_sensor_id > hal::flow::flow_sensor_pin;

void hal::flow::init(const config_type*)
{

  // Define the user button as input, with pull down enabled.
  flow_sensor_pin.set_direction_input();
  flow_sensor_pin.disable_pull_up();
  flow_sensor_pin.enable_pull_down();

}
