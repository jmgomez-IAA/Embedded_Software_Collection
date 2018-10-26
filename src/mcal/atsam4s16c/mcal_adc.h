/**
 * @file mcal_adc.h
 * @brief Microcontroller abstraction layer for the ADC on PC4 SAM4S.
 * @description Inicialization and definitions for the ADC on ___  pin
 * of the SAM4S board.
 * @note The ADC are all inputs, no periphreal is need??
 * @author Juan Manuel Gomez Lopez <jmgomez@iaa.es>
 * @copyright 
 */
#ifndef MCAL_ADC_SAM4SD32C_ESC_H_
#define MCAL_ADC_SAM4SD32C_ESC_H_

#include <cstdint>
#include <mcal/mcal.h>
#include <mcal_reg_access.h>
#include <algorithm>

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

      adc_device() : conversion_is_active(false)
      {
        // Enable Rx and Tx
        mcal::reg::access<addr_type,
                          reg_type,
                          adc_ctrl_register,
                          static_cast<std::uint32_t>(UINT32_C(0x00000050))>::reg_set();


        // Enable channel 0, which is the only one in use.
        mcal::reg::access<addr_type,
                          reg_type,
                          channel_enable_register,
                          static_cast<std::uint32_t>(UINT32_C(0x00000001))>::reg_set();

        // Set ADC CLock 1 MHz
        mcal::reg::access<addr_type,
                          reg_type,
                          analog_ctrl_register,
                          static_cast<std::uint32_t>(UINT32_C(0x00010000))>::reg_set();

        // Set prescaler: clk = (fcpu / (2*adc_freq)) -1 => (4000000 / (2*1000000))-1
        mcal::reg::access<addr_type,
                          reg_type,
                          adc_mode_register,
                          UINT32_C(0x00000100)>::reg_set();

        // Set interrupts
        mcal::reg::access<addr_type,
                          reg_type,
                          interrupt_enable_register,
                          static_cast<std::uint32_t>(UINT32_C(0x00000001))>::reg_set();
      }

      bool read(bval_type &byte_to_send)
      {

        /*
        const adc_conversion_status =  mcal::reg::access<addr_type,
                                                         reg_type,
                                                         interrupt_status_register>::reg_get();*/
        // Conversion is active.
        if (conversion_is_active )
          {
            return false;
          }
        else{

          const reg_type channel0_conversion_value = mcal::reg::access<addr_type,
                                                                       reg_type,
                                                                       ad0_data_register>::reg_get();

          byte_to_send = static_cast<bval_type>(channel0_conversion_value);
          return true;
        }
      }

      bool start()
      {

        if (conversion_is_active)
          return false;

        mcal::reg::access<addr_type,
                          reg_type,
                          adc_ctrl_register,
                          static_cast<std::uint32_t>(UINT32_C(0x00000002))>::reg_set();

        conversion_is_active = true;
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

      //    protected:

      volatile bool conversion_is_active;
    private:


      static constexpr addr_type adc_ctrl_register         = addr_type(port + 0x00UL);
      static constexpr addr_type adc_mode_register         = addr_type(port + 0x04UL);

      static constexpr addr_type channel_enable_register   = addr_type(port + 0x10UL);
      static constexpr addr_type channel_disable_register   = addr_type(port + 0x14UL);
      static constexpr addr_type channel_status_register   = addr_type(port + 0x18UL);


      //      static constexpr addr_type baud_rate_gen_register     = addr_type(port + 0x20UL);

      static constexpr addr_type interrupt_enable_register  = addr_type(port + 0x24UL);
      static constexpr addr_type interrupt_disable_register = addr_type(port + 0x28UL);
      static constexpr addr_type interrupt_mask_register    = addr_type(port + 0x2CUL);
      static constexpr addr_type interrupt_status_register  = addr_type(port + 0x30UL);

      // Last converted data register
      static constexpr addr_type output_data_register       = addr_type(port + 0x50UL);

      // Contorl Freq
      static constexpr addr_type analog_ctrl_register       = addr_type(port + 0x94UL);

      // Specific channel data register.
      static constexpr addr_type ad0_data_register          = addr_type(port + 0x50UL);
      static constexpr addr_type ad1_data_register          = addr_type(port + 0x54UL);
      static constexpr addr_type ad2_data_register          = addr_type(port + 0x58UL);

      static constexpr addr_type ad15_data_register         = addr_type(port + 0x8CUL);


      //      friend void __vector_uart1_rx_tx_irq();
      //extern "C" void __vector_adc_handler() __attribute__((used, noinline));
      friend void __vector_adc_handler();

  };

    // ADC Input pin.
    extern mcal::port::port_pin<std::uint32_t,
                                std::uint32_t,
                                mcal::reg::pioa_base,
                                UINT32_C(17) > adc_input_pin;

    //Multiplexor pins for ADC signal.
    extern mcal::port::port_pin<std::uint32_t,
                                std::uint32_t,
                                mcal::reg::pioa_base,
                                UINT32_C(18) > adc_mux0_pin;

    //Multiplexor pins for ADC signal.
    extern mcal::port::port_pin<std::uint32_t,
                                std::uint32_t,
                                mcal::reg::piob_base,
                                UINT32_C(1) > adc_mux1_pin;

    //Multiplexor pins for ADC signal.
    extern mcal::port::port_pin<std::uint32_t,
                                std::uint32_t,
                                mcal::reg::piob_base,
                                UINT32_C(0) > adc_mux2_pin;

    extern adc_device<std::uint32_t,
                          std::uint32_t,
                          mcal::reg::adc_base> the_adc;

    extern std::uint32_t adc_value;
}

}

#endif  //MCAL_ADC_SAM4SD32C_ESC_H_
