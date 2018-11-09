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

#include <bcc/bcc.h>

namespace
{

/*
constexpr std::uint32_t max_packet_size = 4*1024*1024;
std::array<std::uint8_t, max_packet_size> spw0_memory_pool;
std::array<std::uint8_t, max_packet_size> spw1_memory_pool;
std::array<std::uint8_t, max_packet_size> spw2_memory_pool;
std::array<std::uint8_t, max_packet_size> spw3_memory_pool;
std::array<std::uint8_t, max_packet_size> spw4_memory_pool;
std::array<std::uint8_t, max_packet_size> spw5_memory_pool;

*/
mcal::port::port_pin<std::uint32_t,
                     std::uint32_t,
                     mcal::reg::grgpio1_base_address,
                     UINT32_C(26) > gpio26_output_pin;


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

  std::array<std::uint32_t,20> spw0_msg = { 0x21000000, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 
                                                     0x0a, 0x0b, 0x0b, 0x0d, 0x0e, 0x0f, 0x10, 0x11, 0x12, 0x13};

  std::array<std::uint32_t,20> spw1_msg = { 0x21000000, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 
                                                     0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19};

  std::array<std::uint32_t,20> spw2_msg = { 0x21000000, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 
                                                     0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19};

  std::array<std::uint32_t,20> spw3_msg = { 0x21000000, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 
                                                     0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19};

  std::array<std::uint32_t,20> spw4_msg = { 0x21000000, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 
                                                     0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19};

  std::array<std::uint32_t,20> spw5_msg = { 0x21000000, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 
                                                     0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19};

int main()
{
  /*
  constexpr std::uint32_t def_pattern = 0x55555500UL;

  constexpr std::array<std::uint8_t,13> welcome_msg = {'\n', '\r', 'U', 'A', 'R', 'T',' ', 'T','e', 's', 't', '\n', '\r'};
  constexpr std::array<std::uint8_t,12> underline_msg = {'=', '=', '=', '=', '=','=', '=','=', '=', '=', '\n', '\r'};
  
  enum class spw_error : uint32_t  {CREDIT_ERR = 0x02, ESCAPE_ERR = 0x04, DISCONNECT_ERR = 0x08, 
      PARITY_ERR = 0x10, INVALID_ADDR_ERR = 0x80, END_OF_PACKET_ERR = 0x100 };
  */

  mcal::init();
  hal::init();

  mcal::spw::spw_communication<std::uint32_t, 
                               std::uint32_t, //Minimal transmission packet 4 bytes.
                               mcal::reg::grspw0_base_address,
                               0x40001000,
                               0x40002000> the_spw0;

  mcal::spw::spw_communication<std::uint32_t, 
                               std::uint32_t, //Minimal transmission packet 4 bytes.
                               mcal::reg::grspw1_base_address,
                               0x40003000,
                               0x40004000> the_spw1;
  
  mcal::spw::spw_communication<std::uint32_t, 
                               std::uint32_t, //Minimal transmission packet 4 bytes.
                               mcal::reg::grspw2_base_address,
                               0x40005000,
                               0x40006000> the_spw2;

  mcal::spw::spw_communication<std::uint32_t, 
                               std::uint32_t, //Minimal transmission packet 4 bytes.
                               mcal::reg::grspw3_base_address,
                               0x40007000,
                               0x40008000> the_spw3;
  /*
  mcal::spw::spw_communication<std::uint32_t, 
                               std::uint32_t, //Minimal transmission packet 4 bytes.
                               mcal::reg::grspw4_base_address,
                               0x40009000,
                               0x4000A000> the_spw4;

  mcal::spw::spw_communication<std::uint32_t, 
                               std::uint32_t, //Minimal transmission packet 4 bytes.
                               mcal::reg::grspw5_base_address,
                               0x4000B000,
                               0x4000C000> the_spw5;

*/
  gpio26_output_pin.set_direction_output();

  std::uint32_t counter = 0 ;

  //LED OFF
  hal::led::user_led_pin.set_pin_high();
  //timer_type::blocking_delay(timer_type::seconds(1U));
  std::uint32_t timecode_to_recv = 0;
  //  while(counter < 20) 
  while(1) 
  {
    // Geet the Spw Link Status
    const std::uint32_t link0_status = the_spw0.get_link_status();
    //const std::uint8_t link_state = (link_status >> 21) & 0x7;
    //    const std::uint8_t link_err = (link_status & 0xF);

    if ((link0_status >> 21) == 0x5U)
    {
      //      the_spw0.send(def_pattern | counter);


      if ( the_spw0.get_timecode(timecode_to_recv) )
      {
        spw0_msg.at(0x11) = 0xAA000000 | timecode_to_recv;   

      spw0_msg.at(1) = counter;
      spw0_msg.at(0x10) = 0x00000001;   

      the_spw0.send_n( spw0_msg.begin(), spw0_msg.end() );
      counter ++;
      }
    }

    const std::uint32_t link1_status = the_spw1.get_link_status();
    if ((link1_status >> 21) == 0x5U)
    {
      spw1_msg.at(1) = counter;
      spw1_msg.at(0x10) = 0x2;   

      the_spw1.send_n( spw1_msg.begin(), spw1_msg.end() );

      counter ++;
    }


    const std::uint32_t link2_status = the_spw2.get_link_status();
    if ((link2_status >> 21) == 0x5U)
    {
      spw2_msg.at(1) = counter;
      spw2_msg.at(0x10) = 0x3;   

      the_spw2.send_n( spw2_msg.begin(), spw2_msg.end() );

      counter ++;
    }

    const std::uint32_t link3_status = the_spw3.get_link_status();
    if ((link3_status >> 21) == 0x5U)
    {
      spw3_msg.at(1) = counter;
      spw3_msg.at(0x10) = 0x4;   

      the_spw3.send_n( spw3_msg.begin(), spw3_msg.end() );

      counter ++;
    }


    delay();    
    gpio26_output_pin.toggle_pin();
          
  }

  the_spw0.disable_link();
  the_spw1.disable_link();
  the_spw2.disable_link();
  the_spw3.disable_link();

  return 0;
}
