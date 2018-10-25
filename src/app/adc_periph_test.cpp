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
}

std::uint32_t counter = 0;

int main()
{

  mcal::init();
  hal::init();

  const std::array<std::uint8_t, 10> welcome_msg_s = {'A', 'D', 'C', ' ','T', 'e','s', 't', '\n', '\r'};
  const std::array<std::uint8_t, 10> pio_reg_s = {'P', 'I', 'O', ' ','S', 't','a', 't', ':', ' '};
  const std::array<std::uint8_t, 10> ctrl_reg_s = {'a','d', 'c', ' ','c', 't', 'r', 'l',':', ' '};
  const std::array<std::uint8_t, 10> status_reg_s = {'a','d', 'c', ' ','S', 't', 'a', 't',':', ' '};
  const std::array<std::uint8_t, 10> interrupt_reg_s = {'a','d', 'c', ' ', 'I', 'S', 'R', ' ',':', ' '};
  const std::array<std::uint8_t, 10> ch0data_reg_s = {'a','d', 'c', ' ', 'D', 'a', 't', 'a',':', ' '};

  unsigned char byte_to_recv = 0;

  std::uint32_t *status_reg = reinterpret_cast<std::uint32_t *>(0x40038018);
  std::uint32_t *isr_reg = reinterpret_cast<std::uint32_t *>(0x40038030);
  std::uint32_t *ctrl_reg = reinterpret_cast<std::uint32_t *>(0x40038000);
  std::uint32_t *ch0_reg = reinterpret_cast<std::uint32_t *>(0x40038050);
  std::uint32_t *piob_status_reg = reinterpret_cast<std::uint32_t *>(0x400E1018); //(0x400E1038);

  mcal::adc::adc_mux0_pin.set_pin_high();
  mcal::adc::adc_mux1_pin.set_pin_high();
  mcal::adc::adc_mux2_pin.set_pin_high();

  mcal::uart::the_uart.send_n( welcome_msg_s.begin(), welcome_msg_s.end());

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

      debug_register( pio_reg_s, piob_status_reg);
      debug_register(ctrl_reg_s, ctrl_reg);
      debug_register(status_reg_s, status_reg);
      debug_register(interrupt_reg_s, isr_reg);
      debug_register(ch0data_reg_s, ch0_reg);


      //      mcal::adc::the_adc.read();
      //      mcal::uart::the_uart.send( mcal::adc::adc_value + 0x30);

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
