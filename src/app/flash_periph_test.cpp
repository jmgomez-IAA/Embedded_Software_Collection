/**
 * @file flash_periph_test.cpp
 * @brief Manages the EEFC Controller of the SAM4S processor.
 * @description Modifies a value stored in the Flash and verifies
 * the value is already there after reset.
 *
 * make  clean
 * make  flash_periph
 *
 * To verify erase, flash and dump the eeprom with edbg:
 * ~]# sudo /opt/edbg/edbg -be -t atmel_cm4
 * ~]# sudo /opt/edbg/edbg -bpv -t atmel_cm4 -f bin/flash_periph_test.elf.bin
 * ~]# sudo /opt/edbg/edbg -br -t atmel_cm4 -f bin/flash_periph_test_vfy.bin
 *
 * Search in the Dump file for the offset 0x00010000, where we wrote:
 * ~]# hexdump -C bin/flash_periph_test_vfy.bin | grep -n 010000
 * 82:00010000  00 ef cd ab 01 ef cd ab  02 ef cd ab 03 ef cd ab  |................|
 *
 * Our offset is at line 82, we wrote (128 word)/(4 words/line) = 32.
 * ~]# hexdump -C bin/flash_periph_test_vfy.bin | head -n (82 + 32)
 * ~]# hexdump -C bin/flash_periph_test_vfy.bin | head -n 115| tail -n 34
 *
 * 00010000  00 ef cd ab 01 ef cd ab  02 ef cd ab 03 ef cd ab  |................|
 * 00010010  04 ef cd ab 05 ef cd ab  06 ef cd ab 07 ef cd ab  |................|
 * 00010020  08 ef cd ab 09 ef cd ab  0a ef cd ab 0b ef cd ab  |................|
 *
 * 00010200  ff ff ff ff ff ff ff ff  ff ff ff ff ff ff ff ff  |................|
 *
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

  constexpr std::uint32_t pattern = 0xABCDEF00;

  volatile std::uint32_t *eefc_fmr= reinterpret_cast<std::uint32_t*>(0x400E0A00);
  volatile std::uint32_t *eefc_fcr= reinterpret_cast<std::uint32_t*>(0x400E0A04);
  volatile std::uint32_t *eefc_fsr= reinterpret_cast<std::uint32_t*>(0x400E0A08);
  volatile std::uint32_t *eefc_frr= reinterpret_cast<std::uint32_t*>(0x400E0A0C);

  std::uint32_t get_descriptor_cmd = 0x0;
  std::uint32_t write_page_cmd = 0x1;

  std::uint32_t flash_cmd_key = (0x5A << 24);
  std::uint32_t *page_buffer= reinterpret_cast<std::uint32_t*>(0x00410000);


  std::uint32_t page_number = 128 << 8; // (0x82 << 8);


  mcal::init();
  hal::init();

  std::array<std::uint32_t, 128> flash_write_buffer;

  for(auto &it: flash_write_buffer)
    {
      it = 0xabcdef41;
    }


    mcal::uart::the_uart.send_n( flash_write_buffer.begin(), flash_write_buffer.end());
    timer_type::blocking_delay(timer_type::milliseconds(100U));



  // Start with led OFF.
  hal::led::user_led_pin.set_pin_high();

  /**
   * Latch Buffer is the buffer, it is only accesign the addresses
   */
  volatile std::uint32_t *latch_buffer_start= page_buffer;

  const std::uint32_t op_status = mcal::flash::flash_access<std::uint32_t,
                                                            std::uint32_t,
                                                            mcal::reg::eefc0_base,
                                                            0x80>::pag_write(flash_write_buffer.begin(),
                                                                             flash_write_buffer.end(),
                                                                             reinterpret_cast<std::uint32_t *>(0x410000));


  //Wait for the operation to be executed.
  timer_type::blocking_delay(timer_type::seconds(1U));

  if (*eefc_fsr & 0x01)
    //  if (op_status & 0x01)
    {
      //LED ON: Success
      hal::led::user_led_pin.set_pin_low();
      timer_type::blocking_delay(timer_type::seconds(1U));
    }
  else
    {
      // LED OFF
      hal::led::user_led_pin.set_pin_high();
      timer_type::blocking_delay(timer_type::seconds(1U));
    }


  //Wait forever.
  return 0;
}
