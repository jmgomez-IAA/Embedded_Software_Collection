/**
 * @file mcal_uart.h
 * @brief Microcontroller abstraction layer for the LED on PC4 SAM4S.
 * @description Inicialization and definitions for the LED on PC4 pin
 * of the SAM4S board.
 * @note embedntks.com/sam4s-uart-and-usart/
 * @author Juan Manuel Gomez Lopez <jmgomez@iaa.es>
 * @copyright 
 */

#ifndef _MCAL_UART_SAM4S_EMBEDDED_2018_
#define _MCAL_UART_SAM4S_EMBEDDED_2018_

#include <mcal/mcal.h>
#include <cstdint>

#include <util/utility/util_circular_buffer.h>

#include <array>
#include <algorithm>


extern "C" void __vector_uart1_rx_tx_handler() __attribute__((used, noinline));

namespace mcal
{
  namespace uart
  {
    typedef void config_type;

    void init(const config_type*);

    // Hay que habilitar en PMC
    // Hay que configurar en PIO_Controller.
    template <typename port_type,// std::uint32_t
              typename bval_type,// std::uint8_t
              port_type port>
    class uart_communication
    {
    public:
      typedef std::uint32_t addr_type;
      typedef std::uint32_t reg_type;
      typedef util::circular_buffer<std::uint8_t,32> data_type;

      uart_communication() : send_is_active(false), recv_ready(false)
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

        // Enable interrupts:
        // Receive task is the only one.
        mcal::reg::access<addr_type,
                          reg_type,
                          interrupt_enable_register,
                          static_cast<std::uint32_t>(UINT32_C(0x00000001))>::reg_set();
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


            volatile std::uint32_t uart_status = mcal::reg::access<std::uint32_t,
                                                                   std::uint32_t,
                                                                   uart_status_register>::reg_get();
            while (! (uart_status & 0x00000002) )
              {
                uart_status = mcal::reg::access<std::uint32_t,
                                                std::uint32_t,
                                                uart_status_register>::reg_get();

              }

            ++first;
          }

        return send_result;
      }

      /**
       *
       */
      template<typename recv_iterator_type>
      bool recv_n(recv_iterator_type first,
                  recv_iterator_type last)
      {
        bool recv_result = true;

        std::copy(recv_buffer.rbegin(), recv_buffer.rend(), first);
        recv_buffer.clear();
        return true;

      }

      /**
       *
       */
      bool recv(bval_type &byte_to_recv)
      {

        const std::uint32_t received_elements = receive_ready();
        if (received_elements != 0)
          {
            byte_to_recv = recv_buffer.front();
            //recv_buffer.pop_back();
            //            byte_to_recv = 'F';
            return true;
          }
        else
          {
            return false;
          }
      }

      //Checks if there is data to receive.
      std::uint32_t receive_ready()
      {
        return recv_buffer.size();
      }

  private:
      volatile bool send_is_active;
      volatile bool recv_ready;
      data_type send_buffer;
      data_type recv_buffer;

      static constexpr addr_type uart_ctrl_register         = addr_type(port + 0x00UL);
      static constexpr addr_type uart_mode_register         = addr_type(port + 0x04UL);
      static constexpr addr_type uart_status_register       = addr_type(port + 0x14UL);
      static constexpr addr_type baud_rate_gen_register     = addr_type(port + 0x20UL);

      static constexpr addr_type interrupt_enable_register  = addr_type(port + 0x08UL);
      static constexpr addr_type interrupt_disable_register = addr_type(port + 0x0CUL);
      static constexpr addr_type interrupt_mask_register    = addr_type(port + 0x10UL);

      static constexpr addr_type output_data_register       = addr_type(port + 0x1CUL);
      static constexpr addr_type input_data_register        = addr_type(port + 0x18UL);

      friend void ::__vector_uart1_rx_tx_handler();

  };

    extern mcal::port::port_pin<std::uint32_t,
                                std::uint32_t,
                                mcal::reg::piob_base,
                                UINT32_C(3) > aurt1_tx_pin;

    extern uart_communication<std::uint32_t,
                              std::uint8_t,
                              mcal::reg::uart1_base> the_uart;

}

}

#endif  //_MCAL_UART_SAM4S_EMBEDDED_2018
