/**
 * @file hal_reg.h
 * @brief SAM4S Explainned pro board abstraction layer.
 * @description
 * @author Juan Manuel Gomez Lopez <jmgomez@iaa.es>
 * @copyright 
 */

#ifndef _HAL_REG_GR712RC_ESC_H_
#define _HAL_REG_GR712RC_ESC_H_

#include <cstdint>

namespace hal
{
namespace reg
{

// Bit-position values.
constexpr std::uint8_t bval0  = 1U;
constexpr std::uint8_t bval1  = 1U << 1U;
constexpr std::uint8_t bval2  = 1U << 2U;
constexpr std::uint8_t bval3  = 1U << 3U;
constexpr std::uint8_t bval4  = 1U << 4U;
constexpr std::uint8_t bval5  = 1U << 5U;
constexpr std::uint8_t bval6  = 1U << 6U;
constexpr std::uint8_t bval7  = 1U << 7U;

//Pin definitions on the GPIOs
/**
 * Requires the configuration of the switch matrix.
 */
constexpr std::uint32_t user_led_id        =  UINT32_C(26);
constexpr std::uint32_t user_button_id     =  UINT32_C(25);
}
}
#endif // _HAL_REG_GR712RC_ESC_H_
