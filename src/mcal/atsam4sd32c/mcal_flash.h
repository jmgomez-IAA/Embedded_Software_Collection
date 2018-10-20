/**
 * @file mcal_flash.h
 * @brief Microcontroller EEFC abstraction layer for the SAM4S ARM
 * @description Inicialization and definitions for the management of
 * the internal flash of the SAM4S ARM Cortex M4.
 *
 * Maybe I could use the same interface as transmissions?
 * @author Juan Manuel Gomez Lopez <jmgomez@iaa.es>
 * @copyright 
 */

#ifndef _MCAL_EEFC_SAM4SD32C_ESC_
#define _MCAL_EEFC_SAM4SD32C_ESC_

#include <mcal/mcal.h>

namespace mcal
{
  namespace flash
  {

    typedef void config_type;

    /**
     * @brief Get the descriptor with the information of the flash.
     */
    void init(const config_type*);

    /**
     * @brief Erase all the information of the flash.
     */
    void  erase_all();

    /**
     * @brief Disable the interrupts
     * template<typename send_iterator_type>
     * bool send_n(send_iterator_type first, send_iterator_type last)
     *
     */
    template<typename write_iterator_type>
      void write_to_flash(write_iterator_type first, write_iterator_type last);

    /**
     * @brief
     * @param
     *
     */
    template<typename read_iterator_type>
      void read_from_flash(read_iterator_type first, read_iterator_type last);
  }
}

#endif  //_MCAL_EEFC_SAM4SD32C_ESC_
