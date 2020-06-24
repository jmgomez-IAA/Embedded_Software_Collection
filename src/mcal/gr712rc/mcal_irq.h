/**
 * @file mcal_irq.h
 * @brief Microcontroller abstraction layer for GR712RC
 * @description Inicialization and definitions for the GR712RC
 * abstraction layer.
 * @author Juan Manuel Gomez Lopez <jmgomez@iaa.es>
 * @copyright 
 */

//Links: https://arobenko.gitbooks.io/bare_metal_cpp/content/peripherals/
#ifndef _MCAL_IRQ_SAM4SD32C_ESC_
#define _MCAL_IRQ_SAM4SD32C_ESC_

#include <mcal/mcal.h>

namespace mcal
{
  namespace irq
  {

    typedef void config_type;
    typedef std::uint32_t IRQn_t;

    /**
     *
     **/
    void init(const config_type*);

    /**
     * @ brief Enable the interrupts.
     **/
    inline void  enable_all() { asm volatile("cpsie i"); }

    /**
     * @brief Disable the interrupts
     **/
    inline void disable_all() { asm volatile("cpsid i");}

    /**
     * @brief Enables the interruption for the peripheral id.
     * @param IRQn Id of the interrupt, ussaly it is the peripheral
     * id from table 11.1
     */
    void enableIRQ(IRQn_t IRQn);

    /**
     * @brief Enables the interruption for the peripheral id.
     * @param IRQn Id of the interrupt, ussaly it is the peripheral
     * id from table 11.1
     */
    void disableIRQ(IRQn_t IRQn);
  }
}

#endif  //_MCAL_IRQ_SAM4SD32C_ESC_
