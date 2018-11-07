/**
 * @file mcal_uart.cpp
 * @brief Implementation of microcontroller abstraction layer for UART1 port of SAM4S.
 * @description Instantiates an UART object toma manage uart1.
 * on the board.
 * @author Juan Manuel Gomez Lopez <jmgomez@iaa.es>
 * @copyright
 */

#include <mcal_uart.h>
#include <mcal_cpu.h>
#include <mcal_reg_access.h>


// UART1 TX on port pin PIOB_3
mcal::port::port_pin<std::uint32_t,
                     std::uint32_t,
                     mcal::reg::piob_base,
                     UINT32_C(3) > mcal::uart::aurt1_tx_pin;

mcal::uart::uart_communication<std::uint32_t,
                               std::uint8_t,
                               mcal::reg::uart1_base> mcal::uart::the_uart;

void mcal::uart::init(const config_type *)
{

  //Enable UART1
  mcal::reg::access<std::uint32_t,
                    std::uint32_t,
                    mcal::reg::pmc_pcer0,
                    static_cast<std::uint32_t>(UINT32_C(0x1 << 9))>::reg_or();

  mcal::uart::aurt1_tx_pin.periphA_manage_pin();

  //Enable the interrupt for the uart 1 device.
  mcal::irq::enableIRQ(mcal::reg::uart1_periph_id);


}

std::uint32_t isr_counter = 0;
extern "C" void __vector_uart1_rx_tx_handler() __attribute__((used, noinline));
void  __vector_uart1_rx_tx_handler()
{

  const std::uint32_t uart_status = mcal::reg::access<std::uint32_t,
                                                      std::uint32_t,
                                                      0x400E0814>::reg_get();


  if (uart_status & 0x01)
    {

      const std::uint8_t byte_to_recv = mcal::reg::access<std::uint32_t,
                                                          std::uint32_t,
                                                          0x400E0818>::reg_get();
      mcal::uart::the_uart.recv_buffer.push_front(byte_to_recv);

    }
  /*
  const bool send_buffer_is_empty = mcal::uart::the_uart.send_buffer.empty();

  if ( send_buffer_is_empty )
    {
      mcal::uart::the_uart.send_is_active = false;
    }
  else
    {
      std::uint8_t byte_to_send = mcal::uart::the_uart.send_buffer.front();

      mcal::reg::dynamic_access<std::uint32_t,
                                std::uint32_t>::reg_set(mcal::uart::the_uart.output_data_register, static_cast<std::uint32_t>(byte_to_send));
  */
}

  /*


  if ( uart_status & (0x1 << 0) )
  {
  //Packet received.
  mcal::reg::dynamic_access<addr_type,
  reg_type>::reg_set(output_data_register, static_cast<bval_type>(byte_to_send));

  byte_to_recv = mcal::reg::access<addr_type,
  reg_type,
  input_data_register>::reg_get();

  byte_to_recv = mcal::reg::access<addr_type,
  reg_type,
  input_data_register>::reg_get();

  recv_buffer.append(byte_to_recv);

  */
//}
