/**
 * @file mcal_gpt.cpp
 * @brief General purpose timer abstraction layer.
 * @description Provides functions to initialize and
 * control the general purpose timer.
 * Include the now and get_time_elapsed for the std chrono class.
 * @author Juan Manuel Gomez Lopez <jmgomez@iaa.es>
 * @copyright
 */

/**
 * System clock 1 MHz.
 */

#include <mcal_gpt.h>
#include <mcal_reg_access.h>

#include <bcc/bcc.h>
#include <bcc/bcc_param.h>

namespace
{
  volatile mcal::gpt::value_type system_tick;

  bool& gpt_is_initialized()
  {
    static bool is_init = bool(false);

    return is_init;
  }
}

//extern "C" void  __sys_tick_handler();// __attribute__((used, noinline));
void  __sys_tick_handler(void) {

  // Increment the 32-bit system tick with 0x64, representing 100 milliseconds.
  system_tick += static_cast<std::uint8_t>(0x64U);
}


mcal::gpt::value_type mcal::gpt::get_system_time()
{
  return system_tick;
}


void mcal::gpt::init(const config_type*)
{
  if(gpt_is_initialized() == false)
    {

      // Freeze the Timer until configuration is finished.
      mcal::reg::access<std::uint32_t, 
                        std::uint32_t, 
                        mcal::reg::timer_base_address + 0x8, 
                        0x00000200>::reg_set();

      // We set it to the reset value.
      mcal::reg::access<std::uint32_t, 
                        std::uint32_t, 
                        mcal::reg::timer_base_address, 
                        0x0000032>::reg_set();

      // While no more precission is required, we
      // set the timer reload value to overflow each 100 ms.
      // Scaler Reload value = 1ms * 50 MHz = 50 = h'32
      mcal::reg::access<std::uint32_t, 
                        std::uint32_t, 
                        mcal::reg::timer_base_address + 0x4, 
                        0x0000032>::reg_set();

      // Configure Timer 1 reload value for sys_tick.
      // Sys-Tick = 0x64*0x32 = 0x1388 =>  50000 ciclos x20 us/ciclo = 100 ms
      mcal::reg::access<std::uint32_t, 
                        std::uint32_t, 
                        mcal::reg::timer0_base_address+4, 
                        0x00000064>::reg_set();

      // Configure Timer 1 Control Register
      mcal::reg::access<std::uint32_t, 
                        std::uint32_t, 
                        mcal::reg::timer0_base_address+8, 
                        0x0000000F>::reg_set();

      // Independent Interrupts for each Timer.
      mcal::reg::access<std::uint32_t, 
                        std::uint32_t, 
                        mcal::reg::timer_base_address + 0x8, 
                        0x00000300>::reg_set();

      bcc_set_trap(0x10+14, __sys_tick_handler);
      bcc_flush_cache();


      bcc_int_clear(14);
      bcc_int_unmask(14);

      // Set the is-initialized indication flag.
      gpt_is_initialized() = true;
    }
}


//Provide the function get_time_elapsed used by chrono.
mcal::gpt::value_type mcal::gpt::secure::get_time_elapsed()
{
  // Return the system tick using a multiple read to ensure
  // data consistency of the high-byte of the system tick.

  typedef std::uint32_t timer_address_type;
  typedef std::uint32_t timer_register_type;

  // Do the first read of the timer0 counter and the system tick.
  const timer_register_type tim0_cnt_1 = mcal::reg::access<timer_address_type, timer_register_type, mcal::reg::timer0_base_address>::reg_get();

  // Read the system tick.
  const mcal::gpt::value_type sys_tick_1 = system_tick;

  // Do the second read of the timer0 counter and the system tick.
  const timer_register_type tim0_cnt_2 = mcal::reg::access<timer_address_type, timer_register_type, mcal::reg::timer0_base_address>::reg_get();

  // Perform the consistency check and obtain the consistent microsecond tick.
  const mcal::gpt::value_type consistent_microsecond_tick
    = ((tim0_cnt_2 >= tim0_cnt_1) ? mcal::gpt::value_type(sys_tick_1  | std::uint8_t(tim0_cnt_1 >> 1U))
                                  : mcal::gpt::value_type(system_tick | std::uint8_t(tim0_cnt_2 >> 1U)));

  return (gpt_is_initialized() ? consistent_microsecond_tick : mcal::gpt::value_type(0U));

}


