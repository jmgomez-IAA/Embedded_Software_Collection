/**
 * @file mcal_irq.cpp
 * @brief Manages the interrupt controller. (nvic)
 * @description
 * @author Juan Manuel Gomez Lopez <jmgomez@iaa.es>
 * @copyright
 */

#include <mcal_irq.h>

void mcal::irq::init(const config_type*)
{
  // Enable all global interrupts.
    enable_all();
  //disable_all();

}


void mcal::irq::enableIRQ(mcal::irq::IRQn_t IRQn)
{
  //Enable Interrupts for IRQn
  /*
  mcal::reg::access<std::uint32_t,
                    std::uint32_t,
                    mcal::reg:::nvic_iser0,
                    static_cast<std::uint32_t>(UINT32_C(0x01 << IRQn))>::reg_or();
  */
  mcal::reg::dynamic_access<std::uint32_t,
                            std::uint32_t>::reg_set(mcal::reg::nvic_iser0, (0x01 << IRQn));

}

void mcal::irq::disableIRQ(mcal::irq::IRQn_t  IRQn)
{
  //Disable Interrupts for IRQn
  /*
  mcal::reg::access<std::uint32_t,
                    std::uint32_t,
                    mcal::reg:::nvic_icer0,
                    static_cast<std::uint32_t>(UINT32_C(0x01 << IRQn))>::reg_or();
*/
  mcal::reg::dynamic_access<std::uint32_t,
                            std::uint32_t>::reg_set(mcal::reg::nvic_icer0, static_cast<std::uint32_t>(0x01 << IRQn));
}
