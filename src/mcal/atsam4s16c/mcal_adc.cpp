/**
 * @file mcal_adc.cpp
 * @brief Implementation of microcontroller abstraction layer for ADC port _ of SAM4S.
 * @description Instantiates an ADC object toma manage adc.
 * on the board.
 * @author Juan Manuel Gomez Lopez <jmgomez@iaa.es>
 * @copyright
 */

#include <mcal_adc.h>
#include <mcal_cpu.h>
#include <mcal_port.h>
#include <mcal_reg_access.h>

namespace
{
  volatile std::uint32_t adc_value;
}

// ADC Input pin.
mcal::port::port_pin<std::uint32_t,
                    std::uint32_t,
                    mcal::reg::pioa_base,
                    UINT32_C(17) > mcal::adc::adc_input_pin;

//Multiplexor pins for ADC signal.
mcal::port::port_pin<std::uint32_t,
                    std::uint32_t,
                    mcal::reg::pioa_base,
                    UINT32_C(18) > mcal::adc::adc_mux0_pin;

//Multiplexor pins for ADC signal.
mcal::port::port_pin<std::uint32_t,
                     std::uint32_t,
                     mcal::reg::piob_base,
                    UINT32_C(1) > mcal::adc::adc_mux1_pin;

//Multiplexor pins for ADC signal.
mcal::port::port_pin<std::uint32_t,
                    std::uint32_t,
                    mcal::reg::piob_base,
                    UINT32_C(0) > mcal::adc::adc_mux2_pin;

// This adc object should be for each pin? And The static for all?
//The ADC1, is for pin 1, ADC2 for pin 2, etc.
mcal::adc::adc_device<std::uint32_t,
                          std::uint32_t,
                          mcal::reg::adc_base> mcal::adc::the_adc;

void mcal::adc::init(const config_type *)
{

  //Enable ADC Peripheral
  mcal::reg::access<std::uint32_t,
                    std::uint32_t,
                    mcal::reg::pmc_pcer0,
                    static_cast<std::uint32_t>(UINT32_C(0x1 << 29))>::reg_or();

  adc_input_pin.set_direction_input();

  // Set all as inputs.
  mcal::adc::adc_mux0_pin.set_direction_output();
  //mcal::adc::adc_mux0_pin.enable_pull_up();

  mcal::adc::adc_mux1_pin.set_direction_output();
  //mcal::adc::adc_mux1_pin.enable_pull_up();

  mcal::adc::adc_mux2_pin.set_direction_output();
  //  mcal::adc::adc_mux2_pin.enable_pull_up();


  //Enable ADC Peripheral Interrupts
  mcal::reg::access<std::uint32_t,
                    std::uint32_t,
                    mcal::reg::nvic_iser0,
                    static_cast<std::uint32_t>(UINT32_C(0x1 << 29))>::reg_or();
}


extern "C" void __vector_adc_handler() __attribute__((used, noinline));
  void __vector_adc_handler()
{

  const std::uint32_t channel0_conversion_value = mcal::reg::access<std::uint32_t,
                                                                    std::uint32_t,
                                                                    mcal::reg::ad0_data_register>::reg_get();

  adc_value = static_cast<std::uint32_t>(channel0_conversion_value);
  mcal::adc::the_adc.conversion_is_active = false;

}
