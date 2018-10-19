/**
 * @file pio_periph_test.cpp
 * @brief Manages the PIO Controller of the Device.
 * @description Implement the unit test case, pio_periph,
 * which blinks the USER LED with a 1 second frequency and
 * reads the value of the user switch. While  it is presed,
 * the test blinks the USER LED with a 1/10 second frequency.
 *
 * When the Switch button SW2 (PA) is pressed/released
 * the an ISR is generated, and NVIC manages it. The ISR handler
 * increments the ISR counter in 1.
 *
 * When the counter, reaches 10 (5 time pressed) the leds remain
 * enabled forever.
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
  //  typedef util::timer<std::uint32_t> timer_type;
  void delay()
  {
    for (int i=0; i< 10000; i++)
      for (int j=0; j< 100; j++)
        mcal::cpu::nop();
  }

}

int main()
{
  mcal::init();
  hal::init();

  while (1)
    {
      //LED OFF
      hal::led::user_led_pin.set_pin_high();
      //timer_type::blocking_delay(timer_type::seconds(1U));
      // LED ON
      delay();
      hal::led::user_led_pin.set_pin_low();
      //timer_type::blocking_delay(timer_type::seconds(1U));
      delay();

      while(! hal::sw::user_button_pin.read_input_value() )
        {
          // LED OFF
          hal::led::user_led_pin.set_pin_high();
          //          timer_type::blocking_delay(timer_type::milliseconds(300U));
          delay();
          // LED ON
          hal::led::user_led_pin.set_pin_low();
          //          timer_type::blocking_delay(timer_type::milliseconds(300U));
          delay();
        }
    }

  //Wait forever.
  return 0;
}
