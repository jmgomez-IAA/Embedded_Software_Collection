/**
 * @file mcal_i2c.h
 * @brief Microcontroller abstraction layer for the I2C on PC4 SAM4S.
 * @description Inicialization and definitions for the LED on PC4 pin
 * of the SAM4S board.
 * The port_pin and the peripheral should be configured. The pull-ups for Data should be enabled??
 * @note embedntks.com/sam4s-uart-and-usart/
 * @author Juan Manuel Gomez Lopez <jmgomez@iaa.es>
 * @copyright 
 */

#ifndef _MCAL_I2C_SAM4S_EMBEDDED_2018_
#define _MCAL_I2C_SAM4S_EMBEDDED_2018_


#include <mcal/mcal.h>
#include <cstdint>
#include <mcal_reg_access.h>
#include <algorithm>


//extern "C" void __vector_uart1_rx_tx_handler() __attribute__((used, noinline));

namespace mcal
{
  namespace i2c
  {
    typedef void config_type;

    void init(const config_type*);

    // Hay que habilitar en PMC
    // Hay que configurar en PIO_Controller.
    template <typename port_type,// std::uint32_t
              typename bval_type,// std::uint8_t
              port_type port>
    class i2c_communication
    {
    public:
      typedef std::uint32_t addr_type;
      typedef std::uint32_t reg_type;

      i2c_communication() : send_is_active(false)
      {

        // TWI Set address 0x8 << 15 for slave.
        mcal::reg::access<addr_type,
                          reg_type,
                          master_mode_register,
                          static_cast<std::uint32_t>(UINT32_C(0x00400000))>::reg_set();

        // TWI set baudrate
        //0x11 => 10 us = 100 KHz =
        mcal::reg::access<addr_type,
                          reg_type,
                          clock_generator_register,
                          static_cast<std::uint32_t>(UINT32_C(0x00001111))>::reg_set();

        // Set interrupts
        mcal::reg::access<addr_type,
                          reg_type,
                          interrupt_enable_register,
                          static_cast<std::uint32_t>(UINT32_C(0x00000000))>::reg_set();

        // Twi Slave mode disabled;
        mcal::reg::access<addr_type,
                          reg_type,
                          ctrl_register,
                          static_cast<std::uint32_t>(UINT32_C(0x00000020))>::reg_set();


        // Twi Master mode enabled;
        mcal::reg::access<addr_type,
                          reg_type,
                          ctrl_register,
                          static_cast<std::uint32_t>(UINT32_C(0x00000004))>::reg_set();

      }

      void send_start_bit ()
      {
        // Send Start Bit
        mcal::reg::access<addr_type,
                          reg_type,
                          ctrl_register,
                          static_cast<std::uint32_t>(UINT32_C(0x00000001))>::reg_set();
      }

      void send_stop_bit ()
      {
        // Send Stop Bit
        mcal::reg::access<addr_type,
                          reg_type,
                          ctrl_register,
                          static_cast<std::uint32_t>(UINT32_C(0x00000002))>::reg_set();
      }

      void send_read_cmd()
      {
        // TWI Set address for slave.
        mcal::reg::access<addr_type,
                          reg_type,
                          master_mode_register,
                          static_cast<std::uint32_t>(UINT32_C(0x00001000))>::reg_or();
      }

      /**
       * @brief Send a write command to the device.
       */
      void send_write_cmd()
      {
        // TWI Set address for slave.
        mcal::reg::access<addr_type,
                          reg_type,
                          master_mode_register,
                          static_cast<std::uint32_t>(UINT32_C(0x00000000))>::reg_or();
      }

      /**
       * @brief Transmit a byte.  ¿Multi-byte transmission shpuld manage the START and STOP.!!
       */
      bool send(const bval_type byte_to_send)
      {

        if ( send_is_active )
          {
            return false;
          }
        else{
          send_is_active = true;

          //Send Data.
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

        // TWI Set address for slave.
        mcal::reg::access<addr_type,
                          reg_type,
                          master_mode_register,
                          static_cast<std::uint32_t>(UINT32_C(0x00401000))>::reg_set();

        // Send Start Bit
        mcal::reg::access<addr_type,
                          reg_type,
                          ctrl_register,
                          static_cast<std::uint32_t>(UINT32_C(0x00000001))>::reg_set();
        // Twi Master mode enabled;
        /*        mcal::reg::access<addr_type,
                          reg_type,
                          ctrl_register,
                          static_cast<std::uint32_t>(UINT32_C(0x00000004))>::reg_set();*/
        while(first != last)
          {
            typedef typename
              std::iterator_traits<send_iterator_type>::value_type
              send_value_type;

            const send_value_type value(*first);

            send_result &= send(std::uint8_t(value));

            for (int i=0; i < 1000; ++i)
              for (int j=0; j< 1; ++j)
              {
                mcal::cpu::nop();
              }

            ++first;
          }

        // Send Stop Bit
        mcal::reg::access<addr_type,
                          reg_type,
                          ctrl_register,
                          static_cast<std::uint32_t>(UINT32_C(0x00000002))>::reg_set();

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
        reg_type periph_status = mcal::reg::access<addr_type,
                                         reg_type,
                                         status_register>::reg_get();
        return (periph_status & (0x1 << 1));
      }

  private:
      static constexpr std::uint8_t slave_addr = 0x80UL;

      volatile bool send_is_active;

      static constexpr addr_type ctrl_register                = addr_type(port + 0x00UL);
      static constexpr addr_type master_mode_register         = addr_type(port + 0x04UL);
      static constexpr addr_type slave_mode_register          = addr_type(port + 0x08UL);
      static constexpr addr_type internal_addr_register       = addr_type(port + 0x0CUL);
      static constexpr addr_type clock_generator_register     = addr_type(port + 0x10UL);
      //static constexpr addr_type baudrate_gen_register     = addr_type(port + 0x20UL);

      static constexpr addr_type status_register              = addr_type(port + 0x20UL);

      static constexpr addr_type interrupt_enable_register  = addr_type(port + 0x24UL);
      static constexpr addr_type interrupt_disable_register = addr_type(port + 0x28UL);
      static constexpr addr_type interrupt_mask_register    = addr_type(port + 0x2CUL);

      static constexpr addr_type input_data_register        = addr_type(port + 0x30UL);
      static constexpr addr_type output_data_register       = addr_type(port + 0x34UL);

      //      static constexpr addr_type pdc_register        = addr_type(port + 0x100UL);


      //      friend void __vector_uart1_rx_tx_irq();

  };

    /*    extern i2c_communication<std::uint32_t,
                             std::uint8_t,
                             mcal::reg::twi0_base> the_i2c_0;
    */
    extern mcal::port::port_pin<std::uint32_t,
                                std::uint32_t,
                                mcal::reg::pioa_base,
                                UINT32_C(4) > twi0_clock_pin;

    extern mcal::port::port_pin<std::uint32_t,
                                std::uint32_t,
                                mcal::reg::pioa_base,
                                UINT32_C(3) > twi0_data_pin;
    /*
    extern mcal::port::port_pin<std::uint32_t,
                    std::uint32_t,
                    mcal::reg::piob_base,
                    UINT32_C(5) > twi1_clock_pin;

    extern mcal::port::port_pin<std::uint32_t,
                    std::uint32_t,
                    mcal::reg::piob_base,
                    UINT32_C(4) > twi1_data_pin;
    */
}

}

#endif  //_MCAL_UART_SAM4S_EMBEDDED_2018
