/**
 * @file mcal_ccp.cpp
 * @brief General purpose timer abstraction layer.
 * @description Provides functions to initialize and
 * control the general purpose timer as Compare Mode.
 * @author Juan Manuel Gomez Lopez <jmgomez@iaa.es>
 * @copyright
 */


#include <mcal_ccp.h>
#include <mcal_reg_access.h>

namespace
{
  volatile std::uint32_t flow_freq;

  std::uint32_t temp_value;
  bool& ccp_is_initialized()
  {
    static bool is_init = bool(false);

    return is_init;
  }
}


mcal::port::port_pin<std::uint32_t,
                     std::uint32_t,
                     mcal::reg::pioa_base,
                     UINT32_C(15) > mcal::ccp::tioa1_pin;

uint32_t mcal::ccp::get_freq ()
{
  const std::uint32_t actual_freq = flow_freq;
  flow_freq = 0;
  return actual_freq;
}

void mcal::ccp::init(const config_type*)
{
  if(ccp_is_initialized() == false)
    {

      mcal::ccp::tioa1_pin.set_direction_input();
      mcal::ccp::tioa1_pin.disable_pull_up();
      mcal::ccp::tioa1_pin.enable_pull_down();
      mcal::ccp::tioa1_pin.periphB_manage_pin();


      //Enable TC Channel 1 peripheral on PMC
      mcal::reg::access<std::uint32_t,
                        std::uint32_t,
                        mcal::reg::pmc_pcer0,
                        static_cast<std::uint32_t>(UINT32_C(0x1 << 24))>::reg_or();

      // Disable Timer Module 1, channel 1 to conifgure.
      // ABETRG = 0 => TIOB1
      // ETRGEDG = 1 => Rising
      mcal::reg::access<std::uint32_t, std::uint32_t, mcal::reg::tc01_base, 0x00000002>::reg_set();

      // Set the conf of the Timer Compare mode.
      mcal::reg::access<std::uint32_t, std::uint32_t, mcal::reg::tc01_base+4, 0x00000000>::reg_set();

      // Set the conf of the Timer Compare mode.
      // Reset the counter on zero.
      // Load value on TIA1 rising edge.
      mcal::reg::access<std::uint32_t, std::uint32_t, mcal::reg::tc01_base+4, 0x00050500>::reg_set();

      // Interruts enable con Compare with TIOB, CPBS.
      mcal::reg::access<std::uint32_t, std::uint32_t, mcal::reg::tc01_base+0x24, 0x00000020>::reg_set();

      /*
      // Register C for Capture,
      mcal::reg::access<std::uint32_t, std::uint32_t, mcal::reg::tc01_base+0x1C, 0x07270e00>::reg_set();
      */

      flow_freq = 0xabcdef12;
      // Enable Timer Module 1, channel 1, which manages TIOB1
      mcal::reg::access<std::uint32_t, std::uint32_t, mcal::reg::tc01_base,0x0000001 >::reg_set();

      // Enable Timer Module 1, channel 1, which manages TIOB1
      mcal::reg::access<std::uint32_t, std::uint32_t, mcal::reg::tc01_base,0x0000004 >::reg_or();

      //Enable the interrupt for the swhtich pin.
      // mcal::irq::enableIRQ(24);

      // Set the is-initialized indication flag.
      ccp_is_initialized() = true;
    }
}

extern "C" void  __vector_tc1_handler() __attribute__((used, noinline));
void __vector_tc1_handler() //__attribute__((used, noinline))
 {

   const std::uint32_t timer1_status =  mcal::reg::access<std::uint32_t,
                                                          std::uint32_t,
                                                          mcal::reg::tc01_base+0x20 >::reg_get();

   if (timer1_status & 0x00000020)
     {

       flow_freq += mcal::reg::access<std::uint32_t,
                                     std::uint32_t,
                                     mcal::reg::tc01_base+0x14 >::reg_get()/2;

       //temp_value = (*reinterpret_cast<volatile std::uint32_t *>(0x40010050));

       //       flow_freq = ( temp_value - flow_freq );

     }

 }
