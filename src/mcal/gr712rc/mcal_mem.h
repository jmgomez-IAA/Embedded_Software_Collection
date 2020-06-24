/**
 * @file mcal_mem.h
 * @brief Microcontroller abstraction layer for SAM4S ARM Cortex M CPU
 * @description Inicialization and definitions for the sdram memory
 * of the ED31 board.
 * @author Juan Manuel Gomez Lopez <jmgomez@iaa.es>
 * @copyright 
 */

#ifndef _MCAL_MEM_GR712RC_ESC_H_
#define _MCAL_MEM_GR712RC_ESC_H_

#include <cstdint>
#include <util/memory/util_ring_allocator.h>

namespace mcal
{
namespace mem
{

typedef void config_type;


void init(config_type *);

}
}

#endif  // _MCAL_MEM_GR712RC_ESC_H_
