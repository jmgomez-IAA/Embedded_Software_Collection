/**
 * @file mcal_adc.h
 * @brief Microcontroller abstraction layer for the ADC on PC4 SAM4S.
 * @description Inicialization and definitions for the ADC on ___  pin
 * of the SAM4S board.
 * @note The ADC are all inputs, no periphreal is need??
 * @author Juan Manuel Gomez Lopez <jmgomez@iaa.es>
 * @copyright 
 */

#ifndef _MCAL_ADC_SAM4S_EMBEDDED_2018_
#define _MCAL_ADC_SAM4S_EMBEDDED_2018_


#include <cstdint>
#include <mcal_cpu.h>
#include <mcal_reg_access.h>
#include <algorithm>


//extern "C" void __vector_uart1_rx_tx_handler() __attribute__((used, noinline));

namespace mcal
{
  namespace adc
  {
    typedef void config_type;

    void init(const config_type*);

    // Hay que habilitar en PMC
    // Hay que configurar en PIO_Controller.
    template <typename port_type,// std::uint32_t
              typename bval_type,// std::uint8_t
              port_type port>

    class adc_device
    {
    public:
      typedef std::uint32_t addr_type;
      typedef std::uint32_t reg_type;

      adc_device() : send_is_active(false)
      {
        // Enable Rx and Tx
        mcal::reg::access<addr_type,
                          reg_type,
                          uart_ctrl_register,
                          static_cast<std::uint32_t>(UINT32_C(0x00000050))>::reg_set();


        // Set uart mode: Parity and channel mode
        mcal::reg::access<addr_type,
                          reg_type,
                          uart_mode_register,
                          static_cast<std::uint32_t>(UINT32_C(0x00000800))>::reg_set();

        // Set baudrate: fpck/(16*baud_rate) =>
        mcal::reg::access<addr_type,
                          reg_type,
                          baud_rate_gen_register,
                          static_cast<std::uint32_t>(UINT32_C(0x0000001b))>::reg_set();

        // Set interrupts
        mcal::reg::access<addr_type,
                          reg_type,
                          interrupt_enable_register,
                          static_cast<std::uint32_t>(UINT32_C(0x00000000))>::reg_set();
      }

      bool read(const bval_type byte_to_send)
      {

        if ( send_is_active )
          {
            return false;
          }
        else{
          send_is_active = true;
          mcal::reg::dynamic_access<addr_type,
                                    reg_type>::reg_set(output_data_register, static_cast<bval_type>(byte_to_send));
          send_is_active = false;
        }
        return true;
      }

      bool start(bval_type &byte_to_recv)
      {
        byte_to_recv = mcal::reg::access<addr_type,
                          reg_type,
                          input_data_register>::reg_get();

        return true;
      }

      //Checks if there is data to receive.
      bool conversion_ready()
      {
        reg_type channel_status = mcal::reg::access<addr_type,
                                         reg_type,
                                         channel_status_register>::reg_get();
        return (channel_status & (0x1 << 0));
      }

  private:
      volatile bool send_is_active;

      static constexpr addr_type adc_ctrl_register         = addr_type(port + 0x00UL);
      static constexpr addr_type adc_mode_register         = addr_type(port + 0x04UL);

      static constexpr addr_type channel_enable_register   = addr_type(port + 0x10UL);
      static constexpr addr_type channel_enable_register   = addr_type(port + 0x14UL);
      static constexpr addr_type channel_status_register   = addr_type(port + 0x18UL);


      //      static constexpr addr_type baud_rate_gen_register     = addr_type(port + 0x20UL);

      static constexpr addr_type interrupt_enable_register  = addr_type(port + 0x24UL);
      static constexpr addr_type interrupt_disable_register = addr_type(port + 0x28UL);
      static constexpr addr_type interrupt_mask_register    = addr_type(port + 0x2CUL);
      static constexpr addr_type interrupt_status_register  = addr_type(port + 0x30UL);

      // Last converted data register
      static constexpr addr_type output_data_register       = addr_type(port + 0x20UL);

      // Specific channel data register.
      static constexpr addr_type ad0_data_register          = addr_type(port + 0x50UL);
      static constexpr addr_type ad1_data_register          = addr_type(port + 0x54UL);
      static constexpr addr_type ad2_data_register          = addr_type(port + 0x58UL);

      static constexpr addr_type ad15_data_register         = addr_type(port + 0x8CUL);


      //      friend void __vector_uart1_rx_tx_irq();

  };

    extern adc_peripheral<std::uint32_t,
                          std::uint8_t,
                          mcal::reg::adc_base> the_adc;
}

}

#endif  //_MCAL_ADC_SAM4S_EMBEDDED_2018
