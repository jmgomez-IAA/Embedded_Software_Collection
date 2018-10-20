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

namespace
{
  volatile mcal::gpt::value_type system_tick;

  bool& gpt_is_initialized()
  {
    static bool is_init = bool(false);

    return is_init;
  }
}


void mcal::gpt::init(const config_type*)
{
  if(gpt_is_initialized() == false)
    {
      // Set the timer reload value
      //mcal::reg::access<std::uint32_t, std::uint32_t, mcal::reg::syst_rvr, 0x000F8FFF>::reg_set();
      mcal::reg::access<std::uint32_t, std::uint32_t, mcal::reg::syst_rvr, 0x000003FF>::reg_set();

      // Reset the current value
      mcal::reg::access<std::uint32_t, std::uint32_t, mcal::reg::syst_cvr, 0x00000000>::reg_set();

      // Set the system timer clock source to Main Clk and  f_osc/8 = 2MHz and begin counting.
      mcal::reg::access<std::uint32_t, std::uint32_t, mcal::reg::syst_csr, 0x00000007>::reg_set();

      // Set the is-initialized indication flag.
      gpt_is_initialized() = true;
    }
}

extern "C" void  __sys_tick_handler() __attribute__((used, noinline));
void __sys_tick_handler() //__attribute__((used, noinline))
{
  // Increment the 32-bit system tick with 0x80, representing 128 microseconds.
  // Nuestra ISR esta saltando cada 100 ms.
  system_tick += static_cast<std::uint8_t>(0xF0U);
}

//Provide the function get_time_elapsed used by chrono.
mcal::gpt::value_type mcal::gpt::secure::get_time_elapsed()
{
  // Return the system tick using a multiple read to ensure
  // data consistency of the high-byte of the system tick.

  typedef std::uint32_t timer_address_type;
  typedef std::uint32_t timer_register_type;

  // Do the first read of the timer0 counter and the system tick.
  const timer_register_type tim0_cnt_1 = mcal::reg::access<timer_address_type, timer_register_type, mcal::reg::syst_csr>::reg_get();

  // Read the system tick.
  const mcal::gpt::value_type sys_tick_1 = system_tick;

  // Do the second read of the timer0 counter and the system tick.
  const timer_register_type tim0_cnt_2 = mcal::reg::access<timer_address_type, timer_register_type, mcal::reg::syst_csr>::reg_get();

  // Perform the consistency check and obtain the consistent microsecond tick.
  const mcal::gpt::value_type consistent_microsecond_tick
    = ((tim0_cnt_2 >= tim0_cnt_1) ? mcal::gpt::value_type(sys_tick_1  | std::uint8_t(tim0_cnt_1 >> 1U))
                                  : mcal::gpt::value_type(system_tick | std::uint8_t(tim0_cnt_2 >> 1U)));

  return (gpt_is_initialized() ? consistent_microsecond_tick : mcal::gpt::value_type(0U));

}


