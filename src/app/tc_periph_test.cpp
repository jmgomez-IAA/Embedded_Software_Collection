/**
 * @file tc_periph_test.cpp
 * @brief Enables the tc peripheral of the SAM4S.
 * @description The test-unit enables the tc peripheral
 * on the SAM4S device and measures the freq in TIOB
 * using the compare function.
 *
 * @note No interruption, Fpck = 4 MHz.
 * @author Juan Manuel Gómez López <jmgomez@iaa.es>
 * @copyright
 *
 **/

#include <mcal/mcal.h>
#include <hal/hal.h>
#include <util/utility/util_time.h>

#include <array>
#include <iterator>

namespace{
  typedef util::timer<std::uint32_t> timer_type;
  timer_type app_timer(timer_type::seconds(1U));

  void debug_register(const std::array<std::uint8_t, 10> &msg, std::uint32_t* reg)
  {
    mcal::uart::the_uart.send_n(  msg.begin(),  msg.end());
    mcal::uart::the_uart.send( static_cast<std::uint8_t>(((*reg) & 0x0000000F) + 0x30));
    timer_type::blocking_delay(timer_type::milliseconds(100U));
    mcal::uart::the_uart.send('\n');
    timer_type::blocking_delay(timer_type::milliseconds(100U));
    mcal::uart::the_uart.send('\r');
  }

  bool hexify(std::uint32_t n)
  {

    std::array<std::uint8_t, 16> hex_digits = {'0', '1', '2', '3', '4', '5', '6', '7',
                                               '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
    std::array<std::uint8_t, 10> str_number = {'0', 'x', '0','0','0','0',
                                               '0','0','0','0',};

    // Point to the following of the last.
    auto back_iter = str_number.end();

    // Has caido en lo que te aviso Juanpe
    back_iter --;
    for (std::uint32_t it = 0; it < 8; it ++)
      {
        const std::uint8_t digit = (n >> (4*it)) & 0x0000000F;
        (*back_iter) = hex_digits.at(digit);
        back_iter --;
      }

    mcal::uart::the_uart.send_n(  str_number.begin(),  str_number.end());
    timer_type::blocking_delay(timer_type::milliseconds(100U));
    mcal::uart::the_uart.send('\n');
    timer_type::blocking_delay(timer_type::milliseconds(100U));
    mcal::uart::the_uart.send('\r');

    return true;
  }

}

std::uint32_t counter = 0;

int main()
{

  mcal::init();
  hal::init();

  const std::array<std::uint8_t, 10> welcome_msg_s = {'F', 'L', 'W', ' ','T', 'e','s', 't', '\n', '\r'};
  const std::array<std::uint8_t, 10> flow_data_reg_s = {'F', 'L', 'W', ' ','D', 'a', 't', 'a',':', ' '};

  std::uint32_t *countera_value_ptr = reinterpret_cast<std::uint32_t *>(0x40010054);
  std::uint32_t counter_value = 0x00120012;

  mcal::uart::the_uart.send_n( welcome_msg_s.begin(), welcome_msg_s.end());
  mcal::irq::enableIRQ(24);


  mcal::port::port_pin<std::uint32_t,
                       std::uint32_t,
                       mcal::reg::pioa_base,
                       UINT32_C(13) > clk_gen_pin;

  clk_gen_pin.set_direction_output();
  clk_gen_pin.disable_pull_up();
  clk_gen_pin.enable_pull_down();

  app_timer.start_interval(timer_type::seconds(10U));
  while (1)
    {

      if ( app_timer.timeout() )
        {
          counter_value = mcal::ccp::get_freq();
          hexify( counter_value);
          timer_type::blocking_delay(timer_type::milliseconds(100U));
          hexify(  *countera_value_ptr);
          timer_type::blocking_delay(timer_type::milliseconds(100U));
          mcal::uart::the_uart.send_n( flow_data_reg_s.begin(), flow_data_reg_s.end());
          timer_type::blocking_delay(timer_type::milliseconds(100U));
          app_timer.start_interval(timer_type::seconds(10U));
        }

      // LED ON
      hal::led::user_led_pin.set_pin_low();
      clk_gen_pin.set_pin_low();
      timer_type::blocking_delay(timer_type::milliseconds(200U));

      hal::led::user_led_pin.set_pin_high();
      clk_gen_pin.set_pin_high();
      timer_type::blocking_delay(timer_type::milliseconds(200U));
    }

  //Wait forever.
  return 0;
}
