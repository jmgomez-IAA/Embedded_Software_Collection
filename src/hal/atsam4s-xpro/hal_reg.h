/**
 * @file hal_reg.h
 * @brief SAM4S Explainned pro board abstraction layer.
 * @description
 * @author Juan Manuel Gomez Lopez <jmgomez@iaa.es>
 * @copyright 
 */

#ifndef HAL_REG_ESC_H_
#define HAL_REG_ESC_H_

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

      //
      constexpr std::uint32_t user_led_id        =  UINT32_C(23);
      constexpr std::uint32_t user_button_id     =  UINT32_C(2);

      // Define the Flow metter pin.
      constexpr std::uint32_t flow_sensor_id =   UINT32_C(16); // PA16
    }
  }
#endif //HAL_REG_ESC_H_
