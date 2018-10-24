/**
 * @file mcal_wdt.cpp
 * @brief
 * @description
 * @author Juan Manuel Gomez Lopez <jmgomez@iaa.es>
 * @copyright
 */

#include <mcal_wdt.h>
#include <mcal_reg_access.h>

//#include <mcal_osc.h>
//#include <mcal_port.h>

void mcal::wdt::init(const config_type*){}

void mcal::wdt::enable(const config_type*){}

void mcal::wdt::disable()
{

  //Disable the Watchdog
  mcal::reg::access<std::uint32_t,
                    std::uint32_t,
                    mcal::reg::wdt_mr,
                    UINT32_C(0x00008000)>::reg_set();
}
