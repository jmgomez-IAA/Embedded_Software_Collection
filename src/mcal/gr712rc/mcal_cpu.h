/**
 * @file mcal_cpu.h
 * @brief Microcontroller abstraction layer for GR712RC CPU
 * @description Inicialization and definitions for the CPU GR712RC
 * abstraction layer for the microcontroller GR712RC.
 *
 * @author Juan Manuel Gomez Lopez <jmgomez@iaa.es>
 * @copyright 
 */

#ifndef  _MCAL_CPU_GR712RC_ESC_H_
#define  _MCAL_CPU_GR712RC_ESC_H_

#include <cstdint>

namespace mcal
{
namespace cpu
{

typedef void config_type;

void init();

inline void nop() { asm volatile("nop"); }

//There are four types of flush, may we should implement all.
// Verify this functions in the asm.
inline void flush() { asm volatile("flush"); }

//Necesita un template y una fordware declaration.
inline std::uint32_t read_program_memory(volatile std::uint32_t * pointer_to_program_memory)
{
  return *pointer_to_program_memory;
}


}
}

#endif  // _MCAL_CPU_GR712RC_ESC_H_
