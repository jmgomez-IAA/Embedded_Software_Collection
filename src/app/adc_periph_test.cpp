/**
 * @file adc_periph_test.cpp
 * @brief Enables the adc peripheral of the SAM4S.
 * @description The test-unit enables the adc peripheral
 * on the SAM4S device and rel
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

  const std::array<std::uint8_t, 10> welcome_msg_s = {'A', 'D', 'C', ' ','T', 'e','s', 't', '\n', '\r'};
  const std::array<std::uint8_t, 10> ch0data_reg_s = {'A', 'D', 'C', ' ','D', 'a', 't', 'a',':', ' '};

  unsigned char byte_to_recv = 0;

  mcal::adc::adc_mux0_pin.set_pin_high();
  mcal::adc::adc_mux1_pin.set_pin_high();
  mcal::adc::adc_mux2_pin.set_pin_high();

  mcal::uart::the_uart.send_n( welcome_msg_s.begin(), welcome_msg_s.end());

  std::uint32_t adc_conversion_value = 0x12340201;
  while (1)
    {
      byte_to_recv = 0;
      std::uint32_t counter = 0;
      // LED OFF

      hal::led::user_led_pin.set_pin_high();
      timer_type::blocking_delay(timer_type::seconds(1U));

      if (! mcal::adc::the_adc.start() )
        {
          mcal::uart::the_uart.send('e');
          timer_type::blocking_delay(timer_type::milliseconds(100U));
          mcal::uart::the_uart.send('\n');
        }

      timer_type::blocking_delay(timer_type::milliseconds(100U));
      const bool adc_conversion_status = mcal::adc::the_adc.read(adc_conversion_value);

      if (adc_conversion_status){
        mcal::uart::the_uart.send_n( ch0data_reg_s.begin(), ch0data_reg_s.end());
        timer_type::blocking_delay(timer_type::milliseconds(100U));
        hexify(adc_conversion_value);
      }

      // LED ON
      hal::led::user_led_pin.set_pin_low();
      timer_type::blocking_delay(timer_type::seconds(1U));
      mcal::uart::the_uart.send('\n');
      timer_type::blocking_delay(timer_type::milliseconds(100U));
      mcal::uart::the_uart.send('\r');
    }

  //Wait forever.
  return 0;
}
