/**
 * @file addr_value_test.cpp
 * @brief Enables the uart peripheral, and
 * the value on the address switch SW1.
 * @description The test-unit enables the UART1 peripheral
 * on the SAM4S device. It transmits the "Address Value:" sentence
 * followed by the value in Sw1. Each time it receive a byte,
 * it binks the LED and forwards it to the output.
 *
 *
 * The Configuration is Baudrate 9600, 8N1.
 * To Build the application.
 * sudo make addr-test
 *
 * For verification, a ttyUSB0 adaptor:
 * sudo screen 9600,cs0
 * Ctrl + a, k -> To exit.
 * To transmit to the device a char:
 * su
 * echo -ne '\33' > /dev/ttyUSB0
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
}

int main()
{

  mcal::init();
  hal::init();

  const std::array<std::uint8_t, 10> send_buffer = {'A', 'd', 'd', 'r',' ', 'v','a', 'l', ':', ' '};
  unsigned char byte_to_receive = 0;

  std::uint8_t addr_value = 0;

  while (1)
    {

      addr_value = hal::sw::addr0_pin.read_input_value() |
        hal::sw::addr1_pin.read_input_value() << 1       |
        hal::sw::addr2_pin.read_input_value() << 2       |
        hal::sw::addr3_pin.read_input_value() << 3       |
        hal::sw::addr4_pin.read_input_value() << 4       |
        hal::sw::addr5_pin.read_input_value() << 5       |
        hal::sw::addr6_pin.read_input_value() << 6       |
        hal::sw::addr7_pin.read_input_value() << 7;


      if ( mcal::uart::the_uart.receive_ready())
        {
          // LED OFF
          hal::led::user_led_pin.set_pin_high();
          timer_type::blocking_delay(timer_type::seconds(1U));
          mcal::uart::the_uart.recv(byte_to_receive);
          // LED ON
          hal::led::user_led_pin.set_pin_low();
          mcal::uart::the_uart.send(byte_to_receive);
          timer_type::blocking_delay(timer_type::seconds(1U));

        }

      timer_type::blocking_delay(timer_type::milliseconds(100U));
      mcal::uart::the_uart.send_n( send_buffer.begin(), send_buffer.end());
      timer_type::blocking_delay(timer_type::milliseconds(100U));
      mcal::uart::the_uart.send(addr_value + 0x30);
      timer_type::blocking_delay(timer_type::milliseconds(100U));
      mcal::uart::the_uart.send('\n');
      timer_type::blocking_delay(timer_type::milliseconds(100U));
      mcal::uart::the_uart.send('\r');
      timer_type::blocking_delay(timer_type::milliseconds(100U));

    }

  //Wait forever.
  return 0;
}
