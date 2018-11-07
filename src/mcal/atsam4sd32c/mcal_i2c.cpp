/**
 * @file mcal_i2c.cpp
 * @brief Implementation of microcontroller abstraction layer for i2c port of SAM4S.
 * @description Instantiates an UART object toma manage i2c1.
 * on the board.
 * @author Juan Manuel Gomez Lopez <jmgomez@iaa.es>
 * @copyright
 */

#include <mcal_i2c.h>
#include <mcal_cpu.h>
#include <mcal_port.h>
#include <mcal_reg_access.h>


// TWI0 Data and CLK pins, which are connected to PIOA, should be multiplexed
// in order to be managed with peripheral A.
mcal::port::port_pin<std::uint32_t,
                     std::uint32_t,
                     mcal::reg::pioa_base,
                     UINT32_C(4) > mcal::i2c::twi0_clock_pin;

mcal::port::port_pin<std::uint32_t,
                     std::uint32_t,
                     mcal::reg::pioa_base,
                     UINT32_C(3) > mcal::i2c::twi0_data_pin;

mcal::i2c::i2c_communication<std::uint32_t,
                             std::uint8_t,
                             mcal::reg::twi0_base> mcal::i2c::the_i2c_0;


/*
// TWI1 Data and CLK pins, which are connected to PIOB, should be multiplexed
// in order to be managed with peripheral A.
mcal::port::port_pin<std::uint32_t,
std::uint32_t,
mcal::reg::piob_base,
UINT32_C(5) > mcal::port::twi1_clock_pin;

mcal::port::port_pin<std::uint32_t,
std::uint32_t,
mcal::reg::piob_base,
UINT32_C(4) > mcal::port::twi1_data_pin;
*/

void mcal::i2c::init(const config_type *)
{
  //Enable TWI0 peripheral on PMC
  mcal::reg::access<std::uint32_t,
                    std::uint32_t,
                    mcal::reg::pmc_pcer0,
                    static_cast<std::uint32_t>(UINT32_C(0x1 << 19))>::reg_or();

  mcal::i2c::twi0_clock_pin.periphA_manage_pin();
  mcal::i2c::twi0_clock_pin.enable_pull_up();

  mcal::i2c::twi0_data_pin.periphA_manage_pin();
  mcal::i2c::twi0_data_pin.enable_pull_up();

  //Enable TWI1 peripheral on PMC.
  /*
  mcal::reg::access<std::uint32_t,
                    std::uint32_t,
                    mcal::reg::pmc_pcer0,
                    static_cast<std::uint32_t>(UINT32_C(0x1 << 20))>::reg_or();

  mcal::port::twi1_clock_pin.periphA_manage_pin();
    mcal::port::twi1_clock_pin.disable_pull_up();

  mcal::port::twi1_data_pin.periphA_manage_pin();
  mcal::port::twi1_data_pin.disable_pull_up();
  */
}



/*
mcal::i2c::i2c_communication<std::uint32_t,
                               std::uint8_t,
                             mcal::reg::twi1_base> mcal::i2c::the_i2c_1;
*/


//extern "C" void __vector_uart1_rx_tx_handler() __attribute__((used, noinline));
//void __vector_uart1_rx_tx_irq()
//{
//  mcal::cpu::nop();
//}
