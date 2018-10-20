/**
 * @file sys_tick_chrono_test.cpp
 * @brief Enables the interrups of the sys_tick, and
 * manages it from chrono class.
 * @author Juan Manuel Gómez López <jmgomez@iaa.es>
 * @copyright
 *
 **/

#include <mcal/mcal.h>
#include <hal/hal.h>
#include <util/utility/util_time.h>

namespace{
  typedef util::timer<std::uint32_t> timer_type;

  // Let's create a timer of 1 second.
  timer_type app_timer(timer_type::seconds(1U));
}


int main()
{
  mcal::init();
  hal::init();

  // Each 2 seconds blinks the led, unless someone
  //hits the user_sw button!!
  app_timer.start_interval(timer_type::seconds(2U));
  while (1)
    {
      // LED Off.
      if ( app_timer.timeout() | ! hal::sw::user_button_pin.read_input_value())
        {
          hal::led::user_led_pin.set_pin_low();
          timer_type::blocking_delay(timer_type::milliseconds(300U));

          hal::led::user_led_pin.set_pin_high();
          timer_type::blocking_delay(timer_type::milliseconds(300U));

          app_timer.start_interval(timer_type::seconds(2U));
        }
    }

  //Wait forever.
   return 0;
}
