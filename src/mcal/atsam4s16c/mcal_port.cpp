#include <mcal_port.h>


void mcal::port::init(const config_type*)
{
  //Enable Periph PIOA on  PMC
  mcal::reg::access<std::uint32_t,
                    std::uint32_t,
                    mcal::reg::pmc_pcer0,
                    static_cast<std::uint32_t>(UINT32_C(0x1 << 11))>::reg_or();

  //Enable Periph PIOB on  PMC
  mcal::reg::access<std::uint32_t,
                    std::uint32_t,
                    mcal::reg::pmc_pcer0,
                    static_cast<std::uint32_t>(UINT32_C(0x1 << 12))>::reg_or();

  //Enable Periph PIOC on  PMC
  mcal::reg::access<std::uint32_t,
                    std::uint32_t,
                    mcal::reg::pmc_pcer0,
                    static_cast<std::uint32_t>(UINT32_C(0x1 << 13))>::reg_or();
}
