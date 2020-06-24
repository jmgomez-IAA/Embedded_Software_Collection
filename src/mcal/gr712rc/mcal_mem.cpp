/**
 * @file mcal_mem.cpp
 * @brief Configure the memory GR712 RC board ED31.
 * @description
 * @author Juan Manuel Gomez Lopez <jmgomez@iaa.es>
 * @copyright
 */

#include <mcal_mem.h>
#include <mcal_reg_access.h>


void mcal::mem::init(config_type *)
{

  //Nothing to do with this. No PROM neither MEMIO.
  mcal::reg::access<std::uint32_t,
                    std::uint32_t,
                    mcal::reg::mem_config_register_1,
                    mcal::reg::mem_cfg1_value>::reg_set();

  // Disable SRAM and enable SDRAM;
  mcal::reg::access<std::uint32_t,
                    std::uint32_t,
                    mcal::reg::mem_config_register_2,
                    mcal::reg::mem_cfg2_value>::reg_set();

  // Disable Reed-Solomon EDAC SDRAM:off;  
  // EDAC SDRAM:off, RAM:off, PROM:off
  mcal::reg::access<std::uint32_t,
                    std::uint32_t,
                    mcal::reg::mem_config_register_3,
                    mcal::reg::mem_cfg3_value>::reg_set();

}
