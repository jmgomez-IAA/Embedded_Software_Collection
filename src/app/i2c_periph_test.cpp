/**
 * @file i2c_periph_test.cpp
 * @brief Enables the twi peripheral as a i2c interface.
 * @description The test-unit enables the TWI1 peripheral
 * on the SAM4S device.
 * The conversion from temp bytes received to float is
 * int temp = (high_byte << 8) + (low_byte & 0xFF)  and then
 * tempC = -46.85 + 175.72 * temp/655536.
 * humidity = -6 + 125*rh/65536.
 *
 * It transmits the "Hello World" sentence
 * and each time it receive a byte, it binks the LED and
 * forwards it to the output.
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
  timer_type app_timer(timer_type::seconds(1U));

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

  const std::array<std::uint8_t, 10> welcome_msg_s = {'I', '2', 'C', ' ','T', 'e','s', 't', '\n', '\r'};
  const std::array<std::uint8_t, 10> i2c_status_s = {'I', '2', 'C', ' ','S', 't','a', 't', ':', '\t'};
  const std::array<std::uint8_t, 10> temp_msg_s = {'I', '2', 'C', ' ','T', 'e','m', 'p', ':', '\t'};

  unsigned char byte_to_recv = 0;
  std::uint32_t value_received = 0x2;

  std::uint32_t *i2c_status = reinterpret_cast<std::uint32_t *>(0x40018020);

  mcal::uart::the_uart.send_n( welcome_msg_s.begin(), welcome_msg_s.end());
  timer_type::blocking_delay(timer_type::milliseconds(100U));
  //  mcal::irq::enableIRQ(24);

  app_timer.start_interval(timer_type::seconds(5U));
  //  while (1)
  //  {

      byte_to_recv = 0;
      if ( app_timer.timeout() )
        {

          //mcal::i2c::the_i2c_0.send_read_cmd ();
          mcal::i2c::the_i2c_0.send_write_cmd ();
          mcal::i2c::the_i2c_0.send_start_bit();
          mcal::i2c::the_i2c_0.send_stop_bit ();
          mcal::i2c::the_i2c_0.send(0xF3);

          //          for(std::uint32_t i=0; i< 100; ++i)
          //  mcal::cpu::nop();

          do{

            mcal::i2c::the_i2c_0.send_read_cmd ();
            mcal::i2c::the_i2c_0.send_start_bit();
            mcal::i2c::the_i2c_0.send(0x00);
          //      mcal::i2c::the_i2c_0.send(0x00);
          //      while(counter < 8)
          //  {

          if (mcal::i2c::the_i2c_0.receive_ready() )
            {
              //          std::uint32_t byte_to_recv = 0;
              mcal::i2c::the_i2c_0.recv(byte_to_recv);

              counter ++;
              mcal::uart::the_uart.send(byte_to_recv);


            }
          //  }

            mcal::i2c::the_i2c_0.send_stop_bit ();

          }while((*i2c_status) & 0x100);
          counter = 0;

          // Show results
          mcal::uart::the_uart.send_n( i2c_status_s.begin(), i2c_status_s.end());
          timer_type::blocking_delay(timer_type::milliseconds(100U));
          hexify((*i2c_status));

          app_timer.start_interval(timer_type::seconds(5U));

        }

      // LED OFF
      hal::led::user_led_pin.set_pin_low();
      timer_type::blocking_delay(timer_type::milliseconds(100U));
      // LED ON
      hal::led::user_led_pin.set_pin_high();
      timer_type::blocking_delay(timer_type::milliseconds(100U));

      //}

  //Wait forever.
  return 0;
}
