/**
 * @file mcal_flash.h
 * @brief Microcontroller EEFC abstraction layer for the SAM4S ARM
 * @description Inicialization and definitions for the management of
 * the internal flash of the SAM4S ARM Cortex M4.
 *
 * The flash memory structure and organizatio is described in
 * datasheet pag. 41.
 *
 *
 * Maybe I could use the same interface as transmissions?
 * @author Juan Manuel Gomez Lopez <jmgomez@iaa.es>
 * @copyright 
 */

#ifndef _MCAL_EEFC_SAM4SD32C_ESC_
#define _MCAL_EEFC_SAM4SD32C_ESC_

#include <mcal/mcal.h>
#include <algorithm>

namespace mcal
{
  namespace flash
  {

    typedef std::uint32_t addr_type;
    typedef std::uint32_t reg_type;
    typedef std::uint32_t bval_type;
    typedef void config_type;

    constexpr std::uint32_t flash_cmd_reg       = mcal::reg::eefc0_base + 0;
    constexpr std::uint32_t flash_status_reg    = mcal::reg::eefc0_base + 8;
    constexpr std::uint32_t flash_base_addr     = 0x400000;
    constexpr std::uint32_t flash_page_size     = 0x200;


    /**
     *  unscoped can be directly converted to interger!!
     */
    enum  cmd : std::uint32_t { getd  = 0x00,  wp   = 0x01, wpl   = 0x02,
                                ewp   = 0x03,  ewpl = 0x04, ea    = 0x05,
                                epa   = 0x07,  slb  = 0x08, clb   = 0x09,
                                glb   = 0x0A,  sgpb = 0x0B, cgpb  = 0x0C,
                                ggpb  = 0x0D,  stui = 0x0E, spui  = 0x0F,
                                gcalb = 0x10,  es   = 0x11, wus   = 0x12,
                                eus   = 0x13,  stus = 0x14, spus  = 0x15};

    /**
     * @brief Get the descriptor with the information of the flash.
     */
    void init(const config_type*);

    /**
     * @brief Erase all the information of the flash.
     */
    void  erase_all();


    template <typename addr_type,// std::uint32_t
              typename bval_type,// std::uint32_t
              addr_type port,
              bval_type page_size = 0x80>
    struct flash_access
    {

      template<typename write_iterator_type, typename flash_iterator_type>
      static bval_type pag_write(write_iterator_type first, write_iterator_type last, flash_iterator_type flash_page_begin)
      {
        //First charge flash latch register, going through the page we want to write.
        //const std::uint32_t offset = reinterpret_cast<std::uint32_t>(flash_page_begin - flash_base_addr);
        //std::uint32_t page_number = UINT32_C( ( offset / flash_page_size) << 8);

        std::uint32_t page_number = 128 << 8; // (0x82 << 8);
        constexpr std::uint32_t flash_cmd_key   = UINT32_C(0x5A << 24);

        const std::uint32_t flash_cmd = flash_cmd_key | page_number | mcal::flash::cmd::wp;

        // Get the Status flag and return te result.
        bval_type flash_status;
        const bval_type flash_bussy = mcal::reg::access<addr_type,
                                                        reg_type,
                                                        port + 8>::reg_get();
        std::copy(first, last, flash_page_begin);

        //Send the Write Command.
        mcal::reg::dynamic_access<addr_type,
                                  reg_type>::reg_set(port+4, static_cast<bval_type>(flash_cmd));

        // This statis is not ready, so fast.
        // Get the Status flag and return te result.
        flash_status = mcal::reg::access<addr_type,
                                         reg_type,
                                         port + 8>::reg_get();

        return flash_status;

      }

      /**
       * @brief Check if the Flash is bussy
       * @description Probably inline.
       * @return true if flash is busy.
       */


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
    };
  }
}

#endif  //_MCAL_EEFC_SAM4SD32C_ESC_
