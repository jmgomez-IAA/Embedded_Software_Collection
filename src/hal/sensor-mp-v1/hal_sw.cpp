
#include <hal_sw.h>

/**
 * User button SW0, when pressed drive the line to GND.
 */
mcal::port::port_pin<std::uint32_t,
                     std::uint32_t,
                     mcal::reg::pioa_base,
                     hal::reg::user_button_id > hal::sw::user_button_pin;

mcal::port::port_pin<std::uint32_t,
                     std::uint32_t,
                     mcal::reg::pioa_base,
                     hal::reg::sw3_button_id > hal::sw::sw3_button_pin;

mcal::port::port_pin<std::uint32_t,
                     std::uint32_t,
                     mcal::reg::pioa_base,
                     hal::reg::addr0_button_id  >  hal::sw::addr0_pin;

mcal::port::port_pin<std::uint32_t,
                     std::uint32_t,
                     mcal::reg::pioa_base,
                     hal::reg::addr1_button_id  >  hal::sw::addr1_pin;

mcal::port::port_pin<std::uint32_t,
                     std::uint32_t,
                     mcal::reg::pioa_base,
                     hal::reg::addr2_button_id  >  hal::sw::addr2_pin;

mcal::port::port_pin<std::uint32_t,
                     std::uint32_t,
                     mcal::reg::pioa_base,
                     hal::reg::addr3_button_id  >  hal::sw::addr3_pin;

mcal::port::port_pin<std::uint32_t,
                     std::uint32_t,
                     mcal::reg::pioa_base,
                     hal::reg::addr4_button_id  >  hal::sw::addr4_pin;

mcal::port::port_pin<std::uint32_t,
                     std::uint32_t,
                     mcal::reg::pioa_base,
                     hal::reg::addr5_button_id  >  hal::sw::addr5_pin;

mcal::port::port_pin<std::uint32_t,
                     std::uint32_t,
                     mcal::reg::pioa_base,
                     hal::reg::addr6_button_id  >  hal::sw::addr6_pin;

mcal::port::port_pin<std::uint32_t,
                     std::uint32_t,
                     mcal::reg::pioa_base,
                     hal::reg::addr7_button_id  >  hal::sw::addr7_pin;


void hal::sw::init(const config_type*)
{

  // Define the user button as input, with pull down enabled.
  user_button_pin.set_direction_input();
  user_button_pin.enable_pull_down();

  sw3_button_pin.set_direction_input();
  sw3_button_pin.enable_pull_down();

  addr0_pin.set_direction_input();
  addr0_pin.enable_pull_down();

  addr1_pin.set_direction_input();
  addr1_pin.enable_pull_down();

  addr2_pin.set_direction_input();
  addr2_pin.enable_pull_down();

  addr3_pin.set_direction_input();
  addr3_pin.enable_pull_down();

  addr4_pin.set_direction_input();
  addr4_pin.enable_pull_down();

  addr5_pin.set_direction_input();
  addr5_pin.enable_pull_down();

  addr6_pin.set_direction_input();
  addr6_pin.enable_pull_down();

  addr7_pin.set_direction_input();
  addr7_pin.enable_pull_down();

  //user_button_pin.enable_pull_up();


}
