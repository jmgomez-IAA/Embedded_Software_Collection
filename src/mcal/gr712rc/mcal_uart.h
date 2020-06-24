/**
 * @file mcal_uart.h
 * @brief Microcontroller abstraction layer for the UART preipheral on GR712RC.
 * @description Inicialization and definitions for the LED on PC4 pin
 * of the GR712RC board.
 * uart0_base_address
 * @note embedntks.com/sam4s-uart-and-usart/
 * @author Juan Manuel Gomez Lopez <jmgomez@iaa.es>
 * @copyright 
 */

#ifndef _MCAL_UART_GR712RC_ESC_H_
#define _MCAL_UART_GR712RC_ESC_H_

#include <cstdint>
#include <mcal_cpu.h>
#include <mcal_reg_access.h>
#include <algorithm>


//extern "C" void __vector_uart1_rx_tx_handler() __attribute__((used, noinline));

namespace mcal
{
  namespace uart
  {
    typedef void config_type;

    void init(const config_type*);

    template <typename port_type,// std::uint32_t
              typename bval_type,// std::uint8_t
              port_type port>
    class uart_communication
    {
    public:
      typedef std::uint32_t addr_type;
      typedef std::uint32_t reg_type;

      uart_communication() : send_is_active(false)
      {

        // Set baudrate: Scaler_Reload_value (12bit) = fpck/(8*baud_rate) -1 => 650 = 0x28A
        mcal::reg::access<addr_type,
                          reg_type,
                          baud_rate_gen_register,
                          static_cast<std::uint32_t>(UINT32_C(0x0000028A))>::reg_set();

        // Enable Rx and Tx
        // Transmision 8n1: 8bit, No parity, 1StopBit
        mcal::reg::access<addr_type,
                          reg_type,
                          uart_ctrl_register,
                          static_cast<std::uint32_t>(UINT32_C(0x00000003))>::reg_set();

        // Set interrupts
        /*
        mcal::reg::access<addr_type,
                          reg_type,
                          interrupt_enable_register,
                          static_cast<std::uint32_t>(UINT32_C(0x00000000))>::reg_or();
        */
      }

      bool send(const bval_type byte_to_send)
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

      template<typename send_iterator_type>
      bool send_n(send_iterator_type first,
                  send_iterator_type last)
      {
        bool send_result = true;

        while(first != last)
          {
            typedef typename
              std::iterator_traits<send_iterator_type>::value_type
              send_value_type;

            const send_value_type value(*first);

            send_result &= send(std::uint8_t(value));

            for (int i=0; i < 1000; ++i)
              for (int j=0; j< 100; ++j)
              {
                mcal::cpu::nop();
              }

            ++first;
          }

        return send_result;
      }

      bool recv(bval_type &byte_to_recv)
      {
        byte_to_recv = mcal::reg::access<addr_type,
                          reg_type,
                          input_data_register>::reg_get();

        return true;
      }

      //Checks if there is data to receive.
      bool receive_ready()
      {
        reg_type uart_status = mcal::reg::access<addr_type,
                                         reg_type,
                                         uart_status_register>::reg_get();
        return (uart_status & (0x1 << 0));
      }

  private:
      volatile bool send_is_active;

      static constexpr addr_type uart_ctrl_register         = addr_type(port + 0x08UL);
      static constexpr addr_type uart_status_register       = addr_type(port + 0x04UL);
      static constexpr addr_type baud_rate_gen_register     = addr_type(port + 0x0CUL);

      static constexpr addr_type output_data_register       = addr_type(port + 0x00UL);
      static constexpr addr_type input_data_register        = addr_type(port + 0x00UL);

      static constexpr addr_type uart_fifo_register         = addr_type(port + 0x10UL);

      //      friend void __vector_uart1_rx_tx_irq();

  };

}

}

#endif  //_MCAL_UART_GR712RC_ESC_H_
