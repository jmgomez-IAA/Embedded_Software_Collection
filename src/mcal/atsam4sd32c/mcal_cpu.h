/**
 * @file mcal_cpu.h
 * @brief Microcontroller abstraction layer for SAM4S ARM Cortex M CPU
 * @description Inicialization and definitions for the CPU ARM Cortex M4
 * abstraction layer for the microcontroller SAM4S.
 * @author Juan Manuel Gomez Lopez <jmgomez@iaa.es>
 * @copyright 
 */

#ifndef _MCAL_CPU_ESC_2018_
#define _MCAL_CPU_ESC_2018_

#include <cstdint>
#include <mcal_reg.h>


namespace mcal
{
  namespace cpu
  {

    typedef void config_type;

    void init();

    inline void post_init() {}
    inline void nop() { asm volatile("nop"); }

    inline std::uint8_t read_program_memory(volatile std::uint8_t * pointer_to_program_memory)
    {
      return *pointer_to_program_memory;
    }

  }
}


#endif  // _MCAL_CPU_ESC_2018_
