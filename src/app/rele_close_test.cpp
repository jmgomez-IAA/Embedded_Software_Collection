/**
 * @file rele_close_test.cpp
 * @brief Manages the PIO Controller of the SAM4S processor.
 * @description Implement the unit test case to test the
 * rele.
 *
 * There is a makefile to build.
 * make  clean
 * make pio_periph
 *
 * @author Juan Manuel Gómez López <jmgomez@iaa.es>
 * @copyright
 *
 **/

#include <mcal/mcal.h>
#include <hal/hal.h>
#include <util/utility/util_time.h>

namespace{
  typedef util::timer<std::uint32_t> timer_type;
}

int main()
{
  mcal::init();
  hal::init();

  while (1)
    {
      //LED OFF
      hal::led::user_led_pin.set_pin_high();
      hal::rele::rele_q4_pin.set_pin_high();
      timer_type::blocking_delay(timer_type::seconds(1U));


      while(! hal::sw::user_button_pin.read_input_value() )
        {

          hal::rele::rele_q4_pin.set_pin_low();
          // LED OFF
          hal::led::user_led_pin.set_pin_high();
          timer_type::blocking_delay(timer_type::milliseconds(300U));

          // LED ON
          hal::led::user_led_pin.set_pin_low();
          timer_type::blocking_delay(timer_type::milliseconds(300U));
        }
    }

  //Wait forever.
  return 0;
}
