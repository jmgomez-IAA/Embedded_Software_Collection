/**
 * @file mcal_port.h
 * @brief Port pin abstraction layer.
 * @description Manages de port pins of the 
 * @note Documentation on schematic pag. 10
 */

#ifndef  _MCAL_PORT_GR712RC_ESC_H_
#define  _MCAL_PORT_GR712RC_ESC_H_

#include <mcal_reg_access.h>

namespace mcal
{
namespace port
{
typedef void config_type;
void init(const config_type*);

template<typename addr_type,
         typename reg_type,
         const addr_type port,
         const reg_type bpos>
class port_pin
{
 public:
  static void set_direction_output()
  {
    // Set the port pin control bits.

    // Set the port pin direction to digital output.
    mcal::reg::access<addr_type,
                      reg_type,
                      port_direction_register,
                      static_cast<std::uint32_t>(UINT32_C(0x01) << (bpos))>::reg_or();

    //Disable interrupts for that pin
    mcal::reg::access<addr_type,
                      reg_type,
                      interrupt_mask_register,
                      ~static_cast<std::uint32_t>(UINT32_C(0x01) << (bpos))>::reg_and();

    //Set output digital 0.
    mcal::reg::access<addr_type,
                      reg_type,
                      output_data_register,
                      ~static_cast<std::uint32_t>(UINT32_C(0x01) << (bpos))>::reg_and();
  }

  static void set_direction_input()
  {


    //Disable interrupts for that pin
    mcal::reg::access<addr_type,
                      reg_type,
                      interrupt_mask_register,
                      ~static_cast<std::uint32_t>(UINT32_C(0x01) << (bpos))>::reg_and();

    //Set poert direction to input
    mcal::reg::access<addr_type,
                      reg_type,
                      port_direction_register,
                      ~static_cast<std::uint32_t>(UINT32_C(0x01) << (bpos))>::reg_and();

    /*
    // Disable Output
    mcal::reg::access<addr_type,
    reg_type,
    output_disable_register,
    static_cast<std::uint32_t>(UINT32_C(0x01) << (bpos))>::reg_or(); */
  }

  static void set_pin_high()
  {
    // Set the port output value to high.
    mcal::reg::access<addr_type,
                      reg_type,
                      output_data_register,
                      bpos>::bit_set();
  }

  static void set_pin_low()
  {
    // Set the port output value to low.
    mcal::reg::access<addr_type,
                      reg_type,
                      output_data_register,
                      bpos>::bit_clr();
  }

  static bool read_input_value()
  {
    // Read the port input value.
    return mcal::reg::access<addr_type,
                             reg_type,
                             input_data_register,
                             bpos>::bit_get();
  }

  static void toggle_pin()
  {
    // Toggle the port output value.
    mcal::reg::access<addr_type,
                      reg_type,
                      output_data_register,
                      bpos>::bit_not();
  }

 private:
  static constexpr addr_type input_data_register          = addr_type(port + 0x00UL);
  static constexpr addr_type output_data_register         = addr_type(port + 0x04UL);
  static constexpr addr_type port_direction_register      = addr_type(port + 0x08UL);

  static constexpr addr_type interrupt_mask_register      = addr_type(port + 0x0CUL);
  static constexpr addr_type interrupt_polarity_register  = addr_type(port + 0x10UL);
  static constexpr addr_type interrupt_edge_register      = addr_type(port + 0x14UL);

};
}
}

#endif //  _MCAL_PORT_GR712RC_ESC_H_
