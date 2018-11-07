/**
 * @file mcal_reg.h
 * @brief SAM4S register memory map.
 * @description Defines the SAM4S registers memory map.
 * @author Juan Manuel Gomez Lopez <jmgomez@iaa.es>
 * @copyright 
 */

#ifndef _MCAL_REG_EMBEDDED_H_
  #define _MCAL_REG_EMBEDDED_H_

  #include <cstdint>

  namespace mcal
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

      // Global base addresses.
      // ==
      constexpr std::uint32_t periph_base     = UINT32_C(0x40000000);
      // System Control Space
      constexpr std::uint32_t scs_base        = UINT32_C(0xE000E000);

      constexpr std::uint32_t apb1periph_base = periph_base     + UINT32_C(0x00000000);
      constexpr std::uint32_t ahb1periph_base = periph_base     + UINT32_C(0x00020000);

      // Individual unit base addresses.
      // ==
      // System Control Block
      constexpr std::uint32_t scb_base        = scs_base        + UINT32_C(0x00000D00);
      constexpr std::uint32_t scb_vtor        = scs_base        + UINT32_C(0x00000D08);

      // Nested Vector Interrupt Controller
      constexpr std::uint32_t nvic_base       = scs_base        + UINT32_C(0x00000100);
      constexpr std::uint32_t nvic_iser0      = scs_base        + UINT32_C(0x00000100);
      constexpr std::uint32_t nvic_iser1      = scs_base        + UINT32_C(0x00000104);
      constexpr std::uint32_t nvic_icer0      = scs_base        + UINT32_C(0x00000180);
      constexpr std::uint32_t nvic_icer1      = scs_base        + UINT32_C(0x00000184);
      constexpr std::uint32_t nvic_ispr0      = scs_base        + UINT32_C(0x00000200);
      constexpr std::uint32_t nvic_ispr1      = scs_base        + UINT32_C(0x00000204);
      constexpr std::uint32_t nvic_icpr0      = scs_base        + UINT32_C(0x00000280);
      constexpr std::uint32_t nvic_icpr1      = scs_base        + UINT32_C(0x00000284);
      constexpr std::uint32_t nvic_iabr0      = scs_base        + UINT32_C(0x00000300);
      constexpr std::uint32_t nvic_iabr1      = scs_base        + UINT32_C(0x00000304);
      constexpr std::uint32_t nvic_ipr0       = scs_base        + UINT32_C(0x00000400);
      constexpr std::uint32_t nvic_ipr1       = scs_base        + UINT32_C(0x00000404);

      constexpr std::uint32_t nvic_stir       = scs_base        + UINT32_C(0x00000F00);


      constexpr std::uint32_t nvic2_base      = scs_base        + UINT32_C(0x00000F00);
      //Sys Timer.
      constexpr std::uint32_t syst_csr        = scs_base        + UINT32_C(0x00000010);
      constexpr std::uint32_t syst_rvr        = scs_base        + UINT32_C(0x00000014);
      constexpr std::uint32_t syst_cvr        = scs_base        + UINT32_C(0x00000018);
      constexpr std::uint32_t syst_calib      = scs_base        + UINT32_C(0x0000001C);

      // Power Management Controller
      constexpr std::uint32_t pmc_base        = periph_base     + UINT32_C(0x000E0400);
      //Peripheral clock register enable 0.
      constexpr std::uint32_t pmc_pcer0       = periph_base     + UINT32_C(0x000E0410);

      constexpr std::uint32_t rcc_base        = ahb1periph_base + UINT32_C(0x00003800);
      constexpr std::uint32_t pwr_base        = apb1periph_base + UINT32_C(0x00007000);

      // Watchdog Control(* reg_wdt_mr) |=  WDT_WDDIS;
      constexpr std::uint32_t wdt_base        = periph_base     + UINT32_C(0x000E1450);
      constexpr std::uint32_t wdt_mr          = periph_base     + UINT32_C(0x000E1454);

      // Parallel Input/Output Controller
      constexpr std::uint32_t pioa_periph_id  = 11;
      constexpr std::uint32_t pioa_base       = periph_base        + UINT32_C(0xE0E00);
      constexpr std::uint32_t piob_periph_id  = 12;
      constexpr std::uint32_t piob_base       = periph_base        + UINT32_C(0xE1000);
      constexpr std::uint32_t pioc_periph_id  = 13;
      constexpr std::uint32_t pioc_base       = periph_base        + UINT32_C(0xE1200);

      constexpr std::uint32_t piob_per        = piob_base       + UINT32_C(0x00);
      constexpr std::uint32_t piob_pdr        = piob_base       + UINT32_C(0x04);
      constexpr std::uint32_t piob_psr        = piob_base       + UINT32_C(0x08);
      constexpr std::uint32_t piob_abcdsr1    = piob_base       + UINT32_C(0x70);
      constexpr std::uint32_t piob_abcdsr2    = piob_base       + UINT32_C(0x74);

      constexpr std::uint32_t pioc_per        = periph_base     + UINT32_C(0x000E1200);
      constexpr std::uint32_t pioc_oer        = periph_base     + UINT32_C(0x000E1210);
      constexpr std::uint32_t pioc_codr       = periph_base     + UINT32_C(0x000E1234);
      constexpr std::uint32_t pioc_sodr       = periph_base     + UINT32_C(0x000E1230);
      constexpr std::uint32_t pioc_odsr       = periph_base     + UINT32_C(0x000E1238);
      constexpr std::uint32_t pioc_pdsr       = periph_base     + UINT32_C(0x000E123C);

      // UART Peripheral Controller
      constexpr std::uint32_t uart0_base      = periph_base     + UINT32_C(0x000E0600);
      constexpr std::uint32_t uart0_periph_id = 8;
      constexpr std::uint32_t uart1_base      = periph_base     + UINT32_C(0x000E0800);
      constexpr std::uint32_t uart1_periph_id = 9;

      // TWI Peripheral Controller
      constexpr std::uint32_t twi0_base       = periph_base     + UINT32_C(0x00018000);
      constexpr std::uint32_t twi1_base       = periph_base     + UINT32_C(0x0001C000);

      // ADC Peripheral Controller
      constexpr std::uint32_t adc_base        = periph_base     + UINT32_C(0x00038000);
      constexpr std::uint32_t ad0_data_register =  adc_base     + UINT32_C(0x00000050);

      constexpr std::uint32_t flash_r_base    = ahb1periph_base + UINT32_C(0x00003C00);

      // EEFC Flash controller registers.
      constexpr std::uint32_t eefc0_base      = periph_base     + UINT32_C(0x000E0A00);
      constexpr std::uint32_t eefc1_base      = periph_base     + UINT32_C(0x000E0C00);
      constexpr std::uint32_t eefc_fmr        = eefc0_base      + UINT32_C(0x00000000);
      constexpr std::uint32_t eefc_fcr        = eefc0_base      + UINT32_C(0x00000004);
      constexpr std::uint32_t eefc_fsr        = eefc0_base      + UINT32_C(0x00000008);
      constexpr std::uint32_t eefc_frr        = eefc0_base      + UINT32_C(0x0000000C);

      // Peripheral Memory Map Registers

      // Port Registers
      constexpr std::uint32_t gpio_base = 0x0;

      // Timer Registers
      constexpr std::uint32_t tim4_base = 0x0;

      // Watchdog Controller Registers
      constexpr std::uint32_t iwdg_ase = 0x0;

    }
  }
#endif // _MCAL_REG_EMBEDDED_H_
