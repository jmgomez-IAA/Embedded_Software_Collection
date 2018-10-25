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

  // Let's create a timer of 1 second.
  timer_type app_timer(timer_type::seconds(1U));
}

std::uint32_t counter = 0;

int main()
{

  mcal::init();
  hal::init();

  const std::array<std::uint8_t, 10> pmc_reg_s = {'P', 'M', 'C', ' ','S', 't','a', 't', ':', ' '};
  const std::array<std::uint8_t, 10> pio_reg_s = {'P', 'I', 'O', ' ','S', 't','a', 't', ':', ' '};
  const std::array<std::uint8_t, 10> baud_reg_s = {'i','2', 'c', ' ', 'B', 'a', 'u', 'd',':', ' '};
  const std::array<std::uint8_t, 10> master_reg_s = {'i','2', 'c', ' ','M', 'o', 'd', 'e',':', ' '};
  const std::array<std::uint8_t, 10> status_reg_s = {'i','2', 'c', ' ','S', 't', 'a', 't',':', ' '};
  unsigned char byte_to_recv = 0;

  const std::array<std::uint8_t, 10> i2c_error_s = {'i','2', 'c', ' ','E', 'r', 'r', ':','T', '0'};
  while (1)
    {


      //PMC
      //=====
      timer_type::blocking_delay(timer_type::milliseconds(100U));
      mcal::uart::the_uart.send_n(  pmc_reg_s.begin(), pmc_reg_s.end());
      timer_type::blocking_delay(timer_type::milliseconds(100U));

      constexpr std::uint32_t pmc_status_addr = 0x400E0418UL;;
      std::uint32_t * pmc_status = reinterpret_cast<std::uint32_t *> ( pmc_status_addr);

      if ( (*pmc_status) & (0x1 << 19) )
        mcal::uart::the_uart.send('E');
      else
        mcal::uart::the_uart.send('D');
      timer_type::blocking_delay(timer_type::milliseconds(100U));

      mcal::uart::the_uart.send('\n');
      timer_type::blocking_delay(timer_type::milliseconds(100U));
      mcal::uart::the_uart.send('\r');
      timer_type::blocking_delay(timer_type::milliseconds(100U));

      // PIO
      //===============
      timer_type::blocking_delay(timer_type::milliseconds(100U));
      mcal::uart::the_uart.send_n(  pio_reg_s.begin(),   pio_reg_s.end());
      timer_type::blocking_delay(timer_type::milliseconds(100U));

      constexpr std::uint32_t pio_status_addr = 0x400E0E08UL;;
      std::uint32_t * pio_status = reinterpret_cast<std::uint32_t *> ( pio_status_addr);

      if ( (*pio_status) & (0x1 << 4) )
        mcal::uart::the_uart.send('E');
      else
        mcal::uart::the_uart.send('D');
      timer_type::blocking_delay(timer_type::milliseconds(100U));

      if ( (*pio_status) & (0x1 << 3) )
        mcal::uart::the_uart.send('E');
      else
        mcal::uart::the_uart.send('D');
      timer_type::blocking_delay(timer_type::milliseconds(100U));

      mcal::uart::the_uart.send('\n');
      timer_type::blocking_delay(timer_type::milliseconds(100U));
      mcal::uart::the_uart.send('\r');
      timer_type::blocking_delay(timer_type::milliseconds(100U));

      // I2C STATUS
      mcal::uart::the_uart.send_n( status_reg_s.begin(), status_reg_s.end());
      timer_type::blocking_delay(timer_type::milliseconds(100U));

      constexpr std::uint32_t i2c_status_addr = 0x40018020UL;;
      std::uint32_t * i2c_status = reinterpret_cast<std::uint32_t *> ( i2c_status_addr);

      if ( (*i2c_status) & (0x1 << 0) )
        mcal::uart::the_uart.send('C');
      else
        mcal::uart::the_uart.send('N');
      timer_type::blocking_delay(timer_type::milliseconds(100U));


      if ( (*i2c_status) & (0x1 << 2) )
        mcal::uart::the_uart.send('E');
      else
        mcal::uart::the_uart.send('D');
      timer_type::blocking_delay(timer_type::milliseconds(100U));

      if ((*i2c_status) & (0x1 << 8) )
        mcal::uart::the_uart.send('E');
      else
        mcal::uart::the_uart.send('K');
      timer_type::blocking_delay(timer_type::milliseconds(100U));


      if ((*i2c_status) & (0x1 << 13) )
        mcal::uart::the_uart.send('X');
      else
        mcal::uart::the_uart.send('F');
      timer_type::blocking_delay(timer_type::milliseconds(100U));

      mcal::uart::the_uart.send('\n');
      timer_type::blocking_delay(timer_type::milliseconds(100U));
      mcal::uart::the_uart.send('\r');
      timer_type::blocking_delay(timer_type::milliseconds(100U));

      //===
      //== Master
      //===
      mcal::uart::the_uart.send_n( master_reg_s.begin(), master_reg_s.end());
      timer_type::blocking_delay(timer_type::milliseconds(100U));

      constexpr std::uint32_t i2c_master_addr = 0x40018004UL;;
      std::uint32_t * i2c_master = reinterpret_cast<std::uint32_t *> ( i2c_master_addr);

      if ((*i2c_master) & (0x00400000) )
        mcal::uart::the_uart.send('V');
      else
        mcal::uart::the_uart.send('F');
      timer_type::blocking_delay(timer_type::milliseconds(100U));

      mcal::uart::the_uart.send('\n');
      timer_type::blocking_delay(timer_type::milliseconds(100U));
      mcal::uart::the_uart.send('\r');
      timer_type::blocking_delay(timer_type::milliseconds(100U));

      //===
      //== Baudrate
      //===
      mcal::uart::the_uart.send_n(  baud_reg_s.begin(),  baud_reg_s.end());
      timer_type::blocking_delay(timer_type::milliseconds(100U));

      constexpr std::uint32_t i2c_baud_addr = 0x40018010UL;;
      std::uint32_t * i2c_baud = reinterpret_cast<std::uint32_t *> ( i2c_baud_addr);

      if ( ((*i2c_baud) & (0x00003C3C) ) == (0x00003C3C))
        mcal::uart::the_uart.send('V');
      else
        mcal::uart::the_uart.send('F');
      timer_type::blocking_delay(timer_type::milliseconds(100U));

      mcal::uart::the_uart.send('\n');
      timer_type::blocking_delay(timer_type::milliseconds(100U));
      mcal::uart::the_uart.send('\r');


      byte_to_recv = 0;
      std::uint32_t counter = 0;
      // LED OFF
      hal::led::user_led_pin.set_pin_low();
      timer_type::blocking_delay(timer_type::seconds(1U));

      /*
      mcal::i2c::the_i2c_0.send_read_cmd ();
      mcal::i2c::the_i2c_0.send_start_bit();

      mcal::i2c::the_i2c_0.send(0x00);
      app_timer.start_interval(timer_type::seconds(2U));
      while(counter < 8 && !app_timer.timeout())
        {
          if (mcal::i2c::the_i2c_0.receive_ready() )
            {
              //          std::uint32_t byte_to_recv = 0;
              mcal::i2c::the_i2c_0.recv(byte_to_recv);
              counter ++;

              mcal::uart::the_uart.send(byte_to_recv);
              //              timer_type::blocking_delay(timer_type::milliseconds(100U));
            }
        }

            mcal::i2c::the_i2c_0.send_stop_bit ();
      */
      mcal::i2c::the_i2c_0.send_n(  baud_reg_s.begin(),  baud_reg_s.end());

      while(! hal::sw::user_button_pin.read_input_value() &&  (counter < 8) )
        {
          // LED OFF
          hal::led::user_led_pin.set_pin_high();
          timer_type::blocking_delay(timer_type::milliseconds(300U));

          // LED ON
          hal::led::user_led_pin.set_pin_low();
          timer_type::blocking_delay(timer_type::milliseconds(300U));
        }

      if (counter < 8)
        {
          mcal::uart::the_uart.send_n(i2c_error_s.begin(), i2c_error_s.end());
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
