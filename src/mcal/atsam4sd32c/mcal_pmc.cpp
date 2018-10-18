/**
 * @file mcal_irq.cpp
 * @brief
 * @description
 * @author Juan Manuel Gomez Lopez <jmgomez@iaa.es>
 * @copyright
 */

#include <mcal_pcm.h>
#include <mcal_reg_access.h>

//#include <mcal_osc.h>
//#include <mcal_port.h>
//#include <mcal_wdg.h>

void mcal::pmc::init()
{


  //Set the vector table address
  constexpr std::uint32_t vtor_base_addr = UINT32_C(0x00400000);
  mcal::reg::access<std::uint32_t,
                    std::uint32_t,
                    mcal::reg::scb_vtor,
                    vtor_base_addr>::reg_set();
}
