/**
 * @file spw_periph.cpp
 * @title use_case spw0_run_gpio
 * @brief Configures and transmit spacewire data.
 *
 *
 * @return 
 * 
 * @note The program should be linked to be executed on the build-in SRAM of GR712RC: -T linkcmds-ahbram
 *
 * @author Juan Manuel Gómez <jmgomez@iaa.es>
 * @copirigth PLATO Project IAA-CSIC
 */

#include <cstdint>
#include <array>
#include <mcal/mcal.h>
#include <hal/hal.h>

namespace
{

constexpr std::uint32_t max_packet_size = 4*1024*1024;
std::array<std::uint8_t, max_packet_size> spw0_memory_pool;
std::array<std::uint8_t, max_packet_size> spw1_memory_pool;
std::array<std::uint8_t, max_packet_size> spw2_memory_pool;
std::array<std::uint8_t, max_packet_size> spw3_memory_pool;
std::array<std::uint8_t, max_packet_size> spw4_memory_pool;
std::array<std::uint8_t, max_packet_size> spw5_memory_pool;


mcal::port::port_pin<std::uint32_t,
                     std::uint32_t,
                     mcal::reg::grgpio1_base_address,
                     UINT32_C(26) > gpio26_output_pin;

mcal::spw::spw_communication<std::uint32_t, 
                             std::uint32_t, //Minimal transmission packet 4 bytes.
                             mcal::reg::grspw0_base_address> the_spw0;

//Active delay, loops for x time.
void delay()
{
    for (std::uint32_t iter= 0; iter < 4000; ++iter)
      for (std::uint32_t iter2 = 0; iter2 < 100; iter2++)
      {
        mcal::cpu::nop();        
      }
}
}


int main()
{

  constexpr std::uint32_t def_pattern = 0x55555500UL;

  constexpr std::array<std::uint8_t,13> welcome_msg = {'\n', '\r', 'U', 'A', 'R', 'T',' ', 'T','e', 's', 't', '\n', '\r'};
  constexpr std::array<std::uint8_t,12> underline_msg = {'=', '=', '=', '=', '=','=', '=','=', '=', '=', '\n', '\r'};

  std::array<std::uint32_t,20> spw_msg = { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 
                                                     0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19};

  enum class spw_error : uint32_t  {CREDIT_ERR = 0x02, ESCAPE_ERR = 0x04, DISCONNECT_ERR = 0x08, 
      PARITY_ERR = 0x10, INVALID_ADDR_ERR = 0x80, END_OF_PACKET_ERR = 0x100 };

  mcal::init();
  hal::init();

  gpio26_output_pin.set_direction_output();

  std::uint32_t counter = 0 ;

  //LED OFF
  hal::led::user_led_pin.set_pin_high();
  //timer_type::blocking_delay(timer_type::seconds(1U));

  while(1) {


    // Geet the Spw Link Status
    const std::uint32_t link_status = the_spw0.get_link_status();
    const std::uint8_t link_state = (link_status >> 21) & 0x7;
    const std::uint8_t link_err = (link_status & 0xF);

    if ((link_status >> 21) == 0x5U)
    {
      //      the_spw0.send(def_pattern | counter);

      spw_msg.at(0) = counter;
      the_spw0.send_n(spw_msg.begin(), spw_msg.end());
      counter ++;
    }

    delay();    
    gpio26_output_pin.toggle_pin();
          
  }



  return 0;
}
