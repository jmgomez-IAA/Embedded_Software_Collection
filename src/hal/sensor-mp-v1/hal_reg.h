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

      //pioa_base, pin
      // Define as led_d13, using its label and create an Alias for user_led!!
      constexpr std::uint32_t user_led_id     =  UINT32_C(14);
      constexpr std::uint32_t d14_led_id      =  UINT32_C(15);

      // Define as sw2, its label and create an Alias for user_button!!
      constexpr std::uint32_t user_button_id  =  UINT32_C(13); // sw2_button_pin;
      constexpr std::uint32_t sw3_button_id   =  UINT32_C(26); // sw3_button_pin;

      // Define Sw, address switch
      constexpr std::uint32_t addr0_button_id = UINT32_C(0);
      constexpr std::uint32_t addr1_button_id = UINT32_C(1);
      constexpr std::uint32_t addr2_button_id = UINT32_C(2);
      constexpr std::uint32_t addr3_button_id = UINT32_C(30);
      constexpr std::uint32_t addr4_button_id = UINT32_C(28);
      constexpr std::uint32_t addr5_button_id = UINT32_C(27);
      constexpr std::uint32_t addr6_button_id = UINT32_C(11);
      constexpr std::uint32_t addr7_button_id = UINT32_C(12);

      // Define Rele, pin as PA20.
      constexpr std::uint32_t rele_id   =  UINT32_C(20); // PA20
    }
  }
#endif //HAL_REG_ESC_H_
