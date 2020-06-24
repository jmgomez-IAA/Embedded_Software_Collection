/**
 * @file mcal_uart.cpp
 * @brief Implementation of microcontroller abstraction layer for UART0 port of GR718RC.
 * @description Instantiates an UART object toma manage uart0.
 * on the board.
 * @author Juan Manuel Gomez Lopez <jmgomez@iaa.es>
 * @copyright
 */

#include <mcal_uart.h>
#include <mcal_cpu.h>
#include <mcal_port.h>
#include <mcal_reg_access.h>


void mcal::uart::init(const config_type *)
{

  //Enable UART1
  mcal::reg::access<std::uint32_t,
                    std::uint32_t,
                    mcal::reg::pmc_pcer0,
                    static_cast<std::uint32_t>(UINT32_C(0x1 << 9))>::reg_or();


  mcal::port::aurt1_tx_pin.periphA_manage_pin();

}


mcal::uart::uart_communication<std::uint32_t,
                               std::uint8_t,
                               mcal::reg::uart1_base> mcal::uart::the_uart;


/*
extern "C" void __vector_uart1_rx_tx_handler() __attribute__((used, noinline));
void __vector_uart1_rx_tx_irq()
{
  mcal::cpu::nop();
*/
  /*
  const std::uint32_t uart_status = mcal::reg::access<std::uint32_t,
                                                      std::uint32_t,
                                                      mcal::uart::the_uart.uart_status_register>::reg_get();

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
    }
  */

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
