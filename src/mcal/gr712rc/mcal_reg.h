/**
 * @file mcal_reg.h
 * @brief Memory map and configurable registers of the GR712RC.
 * @description Inicialization and definitions of the configuration registers
 * for the abstraction layer of the SoC GR712RC.
 * @author Juan Manuel Gomez Lopez <jmgomez@iaa.es>
 * @copyright  Plato Team CSIC- IAA
 */

 #include <cstdint>

namespace mcal
{
namespace reg
{

// 128MBytes of SDRAM. Memory size in bytes.
constexpr std::uint32_t sdram_memory_size        = (64*1000*1000); 
constexpr std::uint32_t mem_base_addr            = 0x40000000;
constexpr std::uint32_t mem_end_addr             = mem_base_addr + sdram_memory_size;

//FT Memory Controller
constexpr std::uint32_t mem_config_register_base =  0x80000000UL;
constexpr std::uint32_t mem_config_register_1    =  mem_config_register_base;
constexpr std::uint32_t mem_config_register_2    =  mem_config_register_base + 0x00000004UL;
constexpr std::uint32_t mem_config_register_3    =  mem_config_register_base + 0x00000008UL;
constexpr std::uint32_t mem_config_register_4    =  mem_config_register_base + 0x8000000CUL;

//GRGPIO port 1 registers 
constexpr std::uint32_t grgpio1_base_address     =   0x80000900;

//GRGPIO port 2 registers
constexpr std::uint32_t grgpio2_base_address     =   0x80000A00;

//Emplear port_pin.

constexpr std::uint32_t  mem_cfg1_value          = 0x1003c0ffUL;
// SDRAM Column size = b'01 => 512
// SDRAM bank size = b'100 => 64 MiB
// TCAS = 0
// TRFC = 3+b'001
//  8    a    2    0    6    0    0   0
//1000 1010 0010 0000 0110 0000 0000 0000
constexpr std::uint32_t  mem_cfg2_value          = 0x8a206000UL; // Disable SRAM, enable SDRAM
// Read-Solomon is not availble, only 8 bits of EDAC in the Memories.
constexpr std::uint32_t  mem_cfg3_value          = 0x08184000UL; // Disable Reed-Solomon EDAC SDRAM:off;  EDAC SDRAM:off, RAM:off, PROM:off

// CLOCK Gatting Unit
constexpr std::uint32_t pcm_unlock_address       = 0x80000D00UL;
constexpr std::uint32_t pcm_enable_address       = 0x80000D04UL;
constexpr std::uint32_t pcm_reset_address        = 0x80000D08UL;

// UART Peripheral
constexpr std::uint32_t timer_base_address       = 0x80000300UL;
constexpr std::uint32_t timer0_base_address      = 0x80000310UL;
constexpr std::uint32_t timer1_base_address      = 0x80000320UL;
constexpr std::uint32_t timer2_base_address      = 0x80000330UL;
constexpr std::uint32_t watchdog_base_address    = 0x80000340UL;

// UART Peripheral
constexpr std::uint32_t uart0_base_address       = 0x80000100UL;
constexpr std::uint32_t uart1_base_address       = 0x80100100UL;
constexpr std::uint32_t uart2_base_address       = 0x80100200UL;
constexpr std::uint32_t uart3_base_address       = 0x80100300UL;
constexpr std::uint32_t uart4_base_address       = 0x80100400UL;
constexpr std::uint32_t uart5_base_address       = 0x80100500UL;

// SPW Peripheral
constexpr std::uint32_t grspw0_base_address      = 0x80100800UL;
constexpr std::uint32_t grspw1_base_address      = 0x80100900UL;
constexpr std::uint32_t grspw2_base_address      = 0x80100A00UL;
constexpr std::uint32_t grspw3_base_address      = 0x80100B00UL;
constexpr std::uint32_t grspw4_base_address      = 0x80100C00UL;
constexpr std::uint32_t grspw5_base_address      = 0x80100D00UL;


}
}
