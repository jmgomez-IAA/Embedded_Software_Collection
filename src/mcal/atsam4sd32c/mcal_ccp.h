/**
 * @file mcal_ccp.h
 * @brief General purpose timer Capture Mode.
 * @description Provides functions to initialize and 
 * control the Capture Mode of the Timer. Section 37.6.7.
 *
 * Configuration Sequence
 * ======================
 * 1.- Program Reload Value
 * 2.- Clear the current value.
 * 3.- Program Ctrl and Status
 *
 * NOTE: Interrupts should be enabled.
 * @author Juan Manuel Gomez Lopez <jmgomez@iaa.es>
 *
 * @copyright
 *
 * Registros afectado: SYST_CSR, SYST_RVR, SYST_CVR, SYST_CALIB.
 */

#ifndef _MCAL_CCP_ESC_H_
#define _MCAL_CCP_ESC_H_

#include <cstdint>
#include <mcal/mcal.h>

// namespace util
// {
//   template <typename unsigned_tick_type>
//   class timer;
// }

namespace mcal
{
  namespace ccp
  {
    typedef void config_type;
    typedef std::uint32_t value_type;

    void init(const config_type*);

    uint32_t get_freq ();

    // class secure final
    // {

    // private:
    //   static value_type get_time_elapsed();
    //   friend std::chrono::high_resolution_clock::time_point std::chrono::high_resolution_clock::now();

    //   template <typename unsigned_tick_type>
    //       friend class util::timer;

    // };

    extern mcal::port::port_pin<std::uint32_t,
      std::uint32_t,
      mcal::reg::pioa_base,
      UINT32_C(15) > tioa1_pin;


  }
}

#endif // _MCAL_CCP_ESC_H_
