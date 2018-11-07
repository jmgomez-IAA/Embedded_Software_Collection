///////////////////////////////////////////////////////////////////////////////
//  Copyright Juan Manuel Gómez 2018

#include <array>
#include <cstddef>
#include <mcal_cpu.h>

extern "C" void __initial_stack_pointer();

extern "C" void __my_startup         () __attribute__((used, noinline));
extern "C" void __vector_unused_irq  () __attribute__((used, noinline));
extern "C" void __nmi_handler        () __attribute__((used, noinline));
extern "C" void __hard_fault_handler () __attribute__((used, noinline));
extern "C" void __mem_manage_handler () __attribute__((used, noinline));
extern "C" void __bus_fault_handler  () __attribute__((used, noinline));
extern "C" void __usage_fault_handler() __attribute__((used, noinline));
extern "C" void __svc_handler        () __attribute__((used, noinline));
extern "C" void __debug_mon_handler  () __attribute__((used, noinline));
extern "C" void __pend_sv_handler    () __attribute__((used, noinline));
extern "C" void __sys_tick_handler   () __attribute__((used, noinline, weak));
extern "C" void __vector_timer4      () __attribute__((used, noinline));
extern "C" void __vector_uart1_rx_tx_handler() __attribute__((used, noinline, weak));
extern "C" void __vector_pio_a_handler() __attribute__((used, noinline, weak));
extern "C" void __vector_adc_handler() __attribute__((used, noinline, weak));

// Unused irq simply halts.

extern "C" void __vector_unused_irq  () { for(;;) { mcal::cpu::nop(); } }
extern "C" void __nmi_handler        () { for(;;) { mcal::cpu::nop(); } }
extern "C" void __hard_fault_handler () { for(;;) { mcal::cpu::nop(); } }
extern "C" void __mem_manage_handler () { for(;;) { mcal::cpu::nop(); } }
extern "C" void __bus_fault_handler  () { for(;;) { mcal::cpu::nop(); } }
extern "C" void __usage_fault_handler() { for(;;) { mcal::cpu::nop(); } }
extern "C" void __svc_handler        () { for(;;) { mcal::cpu::nop(); } }
extern "C" void __debug_mon_handler  () { for(;;) { mcal::cpu::nop(); } }
extern "C" void __pend_sv_handler    () { for(;;) { mcal::cpu::nop(); } }
extern "C" void __sys_tick_handler   () { for(;;) { mcal::cpu::nop(); } }
extern "C" void __vector_uart1_rx_tx_handler () {  mcal::cpu::nop();  }
extern "C" void __vector_pio_a_handler () {  for (;;) {mcal::cpu::nop();}  }
extern "C" void __vector_adc_handler () {  for (;;) {mcal::cpu::nop();}  }
namespace
{
  typedef void (*isr_type)();

  //There are 16-Expception + 35 IRQ, pag 196 datasheet, so the Total vector size is 51.
  constexpr std::size_t number_of_interrupts = 51U;
}

extern "C"
const volatile std::array<isr_type, number_of_interrupts> __isr_vector __attribute__((section(".isr_vector")));

extern "C"
const volatile std::array<isr_type, number_of_interrupts> __isr_vector =
{{
  __initial_stack_pointer,   // 0x0000, 0, initial stack pointer
  __my_startup,              // 0x0004, 1, reset
  __nmi_handler,             // 0x0008, 2, nmi exception
  __hard_fault_handler,      // 0x000C, 3, hard fault exception
  __mem_manage_handler,      // 0x0010, 4, memory management exception
  __bus_fault_handler,       // 0x0014, 5, bus fault exception
  __usage_fault_handler,     // 0x0018, 6, usage fault exception
  __vector_unused_irq,       // 0x001C, 7, reserved
  __vector_unused_irq,       // 0x0020, 8, reserved
  __vector_unused_irq,       // 0x0024, 9, reserved
  __vector_unused_irq,       // 0x0028, 10, reserved
  __svc_handler,             // 0x002C, 11, svc handler
  __debug_mon_handler,       // 0x0030, 12, debug monitor
  __vector_unused_irq,       // 0x0034, 13, reserved
  __pend_sv_handler,         // 0x0038, 14, pending svc,
  __sys_tick_handler,        // 0x003C, 15, system tick handler
  __vector_unused_irq,       // 0x0040, 16, wwdg irq handler, 0_supplyCtrl
  __vector_unused_irq,       // 0x0044, 17, pvd irq handler, 1_rstCtrl
  __vector_unused_irq,       // 0x0048, 18, tamper irq handler, 2 RTC
  __vector_unused_irq,       // 0x004C, 19, rtc irq handler, 3 RTT
  __vector_unused_irq,       // 0x0050, 20, flash irq handler, 4 wdg
  __vector_unused_irq,       // 0x0054, 21, rcc irq handler, 5 pmc
  __vector_unused_irq,       // 0x0058, 22, exti0 irq handler, 6 eefc0
  __vector_unused_irq,       // 0x005C, 23, exti1 irq handler, 7 eefc1
  __vector_unused_irq,       // 0x0060, 24, exti2 irq handler, uart0   <--
  __vector_uart1_rx_tx_handler,   // 0x0064, 25,  exti3 irq handler, uart1
  __vector_unused_irq,       // 0x0068, 26, exti4 irq handler,
  __vector_pio_a_handler,    // 0x006C, 27, dma_channel1 irq handler, PIOA   <--
  __vector_unused_irq,       // 0x0070, 28, dma_channel2 irq handler, PIOB
  __vector_unused_irq,       // 0x0074, 29, dma_channel3 irq handler, PIOC
  __vector_unused_irq,       // 0x0078, 30, dma_channel4 irq handler, USART0
  __vector_unused_irq,       // 0x007C, 31, dma_channel5 irq handler, USART1
  __vector_unused_irq,       // 0x0080, 32, dma_channel6 irq handler,16
  __vector_unused_irq,       // 0x0084, 33, dma_channel7 irq handler,17
  __vector_unused_irq,       // 0x0088, 34, adc irq handler, mci 18
  __vector_unused_irq,       // 0x008C, 35, usb_hp_can_tx irq handler, twi0 19
  __vector_unused_irq,       // 0x0090, 36, usb_lp_can_rx0 irq handler, twi1 20
  __vector_unused_irq,       // 0x0094, 37, can_rx1 irq handler, spi 21
  __vector_unused_irq,       // 0x0098, 38, can_sce irq handler, ssc <- 22
  __vector_unused_irq,       // 0x009C, 39, exti9_5 irq handler, tc0 23
  __vector_unused_irq,       // 0x00A0, 40, tim1_brk irq handler,tc1 24
  __vector_unused_irq,       // 0x00A4, 41, tim1_up irq handler, tc2 25
  __vector_unused_irq,       // 0x00A8, 42, tim1_trg_com irq handler, tc3 26
  __vector_unused_irq,       // 0x00AC, 43, tim1_cc irq handler, tc4 27
  __vector_unused_irq,       // 0x00B0, 44, tim2 irq handler, tc5 28
  __vector_adc_handler,       // 0x00B4, 45, tim3 irq handler, 29  adc        <---
  __vector_unused_irq,       // 0x00B8, 46, tim4 irq handler, dac
  __vector_unused_irq,       // 0x00BC, 47, i2c1_ev irq handler, pwm
  __vector_unused_irq,       // 0x00C0, 48, i2c1_er irq handler, crc
  __vector_unused_irq,       // 0x00C4, 49, i2c2_ev irq handler, analog
  __vector_unused_irq       // 0x00C8, 50, i2c2_er irq handler, usb dev port
}};
