/*
	This file contains the entry point (Reset_Handler) of your firmware project.
	The reset handled initializes the RAM and calls system library initializers as well as
	the platform-specific initializer and the main() function.
*/

#include <stddef.h>
extern void *_estack;

void Reset_Handler();
void Default_Handler();

#ifndef DEBUG_DEFAULT_INTERRUPT_HANDLERS

#ifdef DEBUG
#define DEBUG_DEFAULT_INTERRUPT_HANDLERS 1
#else
#define DEBUG_DEFAULT_INTERRUPT_HANDLERS 0
#endif

#endif

#if DEBUG_DEFAULT_INTERRUPT_HANDLERS
void __attribute__ ((weak, naked)) NMI_Handler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void NMI_Handler();
	__asm("bkpt 255");
	__asm("bx lr");
}
void __attribute__ ((weak, naked)) HardFault_Handler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void HardFault_Handler();
	__asm("bkpt 255");
	__asm("bx lr");
}
void __attribute__ ((weak, naked)) MemManage_Handler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void MemManage_Handler();
	__asm("bkpt 255");
	__asm("bx lr");
}
void __attribute__ ((weak, naked)) BusFault_Handler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void BusFault_Handler();
	__asm("bkpt 255");
	__asm("bx lr");
}
void __attribute__ ((weak, naked)) UsageFault_Handler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void UsageFault_Handler();
	__asm("bkpt 255");
	__asm("bx lr");
}
void __attribute__ ((weak, naked)) Bootloader_MainStageTable() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void Bootloader_MainStageTable();
	__asm("bkpt 255");
	__asm("bx lr");
}
void __attribute__ ((weak, naked)) SVC_Handler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void SVC_Handler();
	__asm("bkpt 255");
	__asm("bx lr");
}
void __attribute__ ((weak, naked)) DebugMon_Handler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void DebugMon_Handler();
	__asm("bkpt 255");
	__asm("bx lr");
}
void __attribute__ ((weak, naked)) sl_app_properties() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void sl_app_properties();
	__asm("bkpt 255");
	__asm("bx lr");
}
void __attribute__ ((weak, naked)) PendSV_Handler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void PendSV_Handler();
	__asm("bkpt 255");
	__asm("bx lr");
}
void __attribute__ ((weak, naked)) SysTick_Handler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void SysTick_Handler();
	__asm("bkpt 255");
	__asm("bx lr");
}
void __attribute__ ((weak, naked)) SMU_SECURE_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void SMU_SECURE_IRQHandler();
	__asm("bkpt 255");
	__asm("bx lr");
}
void __attribute__ ((weak, naked)) SMU_PRIVILEGED_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void SMU_PRIVILEGED_IRQHandler();
	__asm("bkpt 255");
	__asm("bx lr");
}
void __attribute__ ((weak, naked)) SMU_NS_PRIVILEGED_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void SMU_NS_PRIVILEGED_IRQHandler();
	__asm("bkpt 255");
	__asm("bx lr");
}
void __attribute__ ((weak, naked)) EMU_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void EMU_IRQHandler();
	__asm("bkpt 255");
	__asm("bx lr");
}
void __attribute__ ((weak, naked)) TIMER0_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void TIMER0_IRQHandler();
	__asm("bkpt 255");
	__asm("bx lr");
}
void __attribute__ ((weak, naked)) TIMER1_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void TIMER1_IRQHandler();
	__asm("bkpt 255");
	__asm("bx lr");
}
void __attribute__ ((weak, naked)) TIMER2_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void TIMER2_IRQHandler();
	__asm("bkpt 255");
	__asm("bx lr");
}
void __attribute__ ((weak, naked)) TIMER3_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void TIMER3_IRQHandler();
	__asm("bkpt 255");
	__asm("bx lr");
}
void __attribute__ ((weak, naked)) TIMER4_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void TIMER4_IRQHandler();
	__asm("bkpt 255");
	__asm("bx lr");
}
void __attribute__ ((weak, naked)) USART0_RX_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void USART0_RX_IRQHandler();
	__asm("bkpt 255");
	__asm("bx lr");
}
void __attribute__ ((weak, naked)) USART0_TX_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void USART0_TX_IRQHandler();
	__asm("bkpt 255");
	__asm("bx lr");
}
void __attribute__ ((weak, naked)) EUSART0_RX_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void EUSART0_RX_IRQHandler();
	__asm("bkpt 255");
	__asm("bx lr");
}
void __attribute__ ((weak, naked)) EUSART0_TX_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void EUSART0_TX_IRQHandler();
	__asm("bkpt 255");
	__asm("bx lr");
}
void __attribute__ ((weak, naked)) EUSART1_RX_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void EUSART1_RX_IRQHandler();
	__asm("bkpt 255");
	__asm("bx lr");
}
void __attribute__ ((weak, naked)) EUSART1_TX_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void EUSART1_TX_IRQHandler();
	__asm("bkpt 255");
	__asm("bx lr");
}
void __attribute__ ((weak, naked)) EUSART2_RX_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void EUSART2_RX_IRQHandler();
	__asm("bkpt 255");
	__asm("bx lr");
}
void __attribute__ ((weak, naked)) EUSART2_TX_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void EUSART2_TX_IRQHandler();
	__asm("bkpt 255");
	__asm("bx lr");
}
void __attribute__ ((weak, naked)) ICACHE0_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void ICACHE0_IRQHandler();
	__asm("bkpt 255");
	__asm("bx lr");
}
void __attribute__ ((weak, naked)) BURTC_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void BURTC_IRQHandler();
	__asm("bkpt 255");
	__asm("bx lr");
}
void __attribute__ ((weak, naked)) LETIMER0_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void LETIMER0_IRQHandler();
	__asm("bkpt 255");
	__asm("bx lr");
}
void __attribute__ ((weak, naked)) SYSCFG_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void SYSCFG_IRQHandler();
	__asm("bkpt 255");
	__asm("bx lr");
}
void __attribute__ ((weak, naked)) MPAHBRAM_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void MPAHBRAM_IRQHandler();
	__asm("bkpt 255");
	__asm("bx lr");
}
void __attribute__ ((weak, naked)) LDMA_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void LDMA_IRQHandler();
	__asm("bkpt 255");
	__asm("bx lr");
}
void __attribute__ ((weak, naked)) LFXO_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void LFXO_IRQHandler();
	__asm("bkpt 255");
	__asm("bx lr");
}
void __attribute__ ((weak, naked)) LFRCO_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void LFRCO_IRQHandler();
	__asm("bkpt 255");
	__asm("bx lr");
}
void __attribute__ ((weak, naked)) ULFRCO_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void ULFRCO_IRQHandler();
	__asm("bkpt 255");
	__asm("bx lr");
}
void __attribute__ ((weak, naked)) GPIO_ODD_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void GPIO_ODD_IRQHandler();
	__asm("bkpt 255");
	__asm("bx lr");
}
void __attribute__ ((weak, naked)) GPIO_EVEN_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void GPIO_EVEN_IRQHandler();
	__asm("bkpt 255");
	__asm("bx lr");
}
void __attribute__ ((weak, naked)) I2C0_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void I2C0_IRQHandler();
	__asm("bkpt 255");
	__asm("bx lr");
}
void __attribute__ ((weak, naked)) I2C1_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void I2C1_IRQHandler();
	__asm("bkpt 255");
	__asm("bx lr");
}
void __attribute__ ((weak, naked)) EMUDG_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void EMUDG_IRQHandler();
	__asm("bkpt 255");
	__asm("bx lr");
}
void __attribute__ ((weak, naked)) HOSTMAILBOX_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void HOSTMAILBOX_IRQHandler();
	__asm("bkpt 255");
	__asm("bx lr");
}
void __attribute__ ((weak, naked)) ACMP0_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void ACMP0_IRQHandler();
	__asm("bkpt 255");
	__asm("bx lr");
}
void __attribute__ ((weak, naked)) ACMP1_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void ACMP1_IRQHandler();
	__asm("bkpt 255");
	__asm("bx lr");
}
void __attribute__ ((weak, naked)) WDOG0_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void WDOG0_IRQHandler();
	__asm("bkpt 255");
	__asm("bx lr");
}
void __attribute__ ((weak, naked)) WDOG1_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void WDOG1_IRQHandler();
	__asm("bkpt 255");
	__asm("bx lr");
}
void __attribute__ ((weak, naked)) HFXO0_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void HFXO0_IRQHandler();
	__asm("bkpt 255");
	__asm("bx lr");
}
void __attribute__ ((weak, naked)) HFRCO0_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void HFRCO0_IRQHandler();
	__asm("bkpt 255");
	__asm("bx lr");
}
void __attribute__ ((weak, naked)) HFRCOEM23_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void HFRCOEM23_IRQHandler();
	__asm("bkpt 255");
	__asm("bx lr");
}
void __attribute__ ((weak, naked)) CMU_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void CMU_IRQHandler();
	__asm("bkpt 255");
	__asm("bx lr");
}
void __attribute__ ((weak, naked)) IADC_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void IADC_IRQHandler();
	__asm("bkpt 255");
	__asm("bx lr");
}
void __attribute__ ((weak, naked)) MSC_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void MSC_IRQHandler();
	__asm("bkpt 255");
	__asm("bx lr");
}
void __attribute__ ((weak, naked)) DPLL0_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void DPLL0_IRQHandler();
	__asm("bkpt 255");
	__asm("bx lr");
}
void __attribute__ ((weak, naked)) EMUEFP_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void EMUEFP_IRQHandler();
	__asm("bkpt 255");
	__asm("bx lr");
}
void __attribute__ ((weak, naked)) DCDC_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void DCDC_IRQHandler();
	__asm("bkpt 255");
	__asm("bx lr");
}
void __attribute__ ((weak, naked)) VDAC_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void VDAC_IRQHandler();
	__asm("bkpt 255");
	__asm("bx lr");
}
void __attribute__ ((weak, naked)) PCNT0_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void PCNT0_IRQHandler();
	__asm("bkpt 255");
	__asm("bx lr");
}
void __attribute__ ((weak, naked)) SW0_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void SW0_IRQHandler();
	__asm("bkpt 255");
	__asm("bx lr");
}
void __attribute__ ((weak, naked)) SW1_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void SW1_IRQHandler();
	__asm("bkpt 255");
	__asm("bx lr");
}
void __attribute__ ((weak, naked)) SW2_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void SW2_IRQHandler();
	__asm("bkpt 255");
	__asm("bx lr");
}
void __attribute__ ((weak, naked)) SW3_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void SW3_IRQHandler();
	__asm("bkpt 255");
	__asm("bx lr");
}
void __attribute__ ((weak, naked)) KERNEL0_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void KERNEL0_IRQHandler();
	__asm("bkpt 255");
	__asm("bx lr");
}
void __attribute__ ((weak, naked)) KERNEL1_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void KERNEL1_IRQHandler();
	__asm("bkpt 255");
	__asm("bx lr");
}
void __attribute__ ((weak, naked)) M33CTI0_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void M33CTI0_IRQHandler();
	__asm("bkpt 255");
	__asm("bx lr");
}
void __attribute__ ((weak, naked)) M33CTI1_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void M33CTI1_IRQHandler();
	__asm("bkpt 255");
	__asm("bx lr");
}
void __attribute__ ((weak, naked)) FPUEXH_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void FPUEXH_IRQHandler();
	__asm("bkpt 255");
	__asm("bx lr");
}
void __attribute__ ((weak, naked)) SETAMPERHOST_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void SETAMPERHOST_IRQHandler();
	__asm("bkpt 255");
	__asm("bx lr");
}
void __attribute__ ((weak, naked)) SEMBRX_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void SEMBRX_IRQHandler();
	__asm("bkpt 255");
	__asm("bx lr");
}
void __attribute__ ((weak, naked)) SEMBTX_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void SEMBTX_IRQHandler();
	__asm("bkpt 255");
	__asm("bx lr");
}
void __attribute__ ((weak, naked)) LESENSE_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void LESENSE_IRQHandler();
	__asm("bkpt 255");
	__asm("bx lr");
}
void __attribute__ ((weak, naked)) SYSRTC_APP_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void SYSRTC_APP_IRQHandler();
	__asm("bkpt 255");
	__asm("bx lr");
}
void __attribute__ ((weak, naked)) SYSRTC_SEQ_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void SYSRTC_SEQ_IRQHandler();
	__asm("bkpt 255");
	__asm("bx lr");
}
void __attribute__ ((weak, naked)) LCD_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void LCD_IRQHandler();
	__asm("bkpt 255");
	__asm("bx lr");
}
void __attribute__ ((weak, naked)) KEYSCAN_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void KEYSCAN_IRQHandler();
	__asm("bkpt 255");
	__asm("bx lr");
}

#else
void NMI_Handler()                   __attribute__ ((weak, alias ("Default_Handler")));
void HardFault_Handler()             __attribute__ ((weak, alias ("Default_Handler")));
void MemManage_Handler()             __attribute__ ((weak, alias ("Default_Handler")));
void BusFault_Handler()              __attribute__ ((weak, alias ("Default_Handler")));
void UsageFault_Handler()            __attribute__ ((weak, alias ("Default_Handler")));
void Bootloader_MainStageTable()     __attribute__ ((weak, alias ("Default_Handler")));
void SVC_Handler()                   __attribute__ ((weak, alias ("Default_Handler")));
void DebugMon_Handler()              __attribute__ ((weak, alias ("Default_Handler")));
void sl_app_properties()             __attribute__ ((weak, alias ("Default_Handler")));
void PendSV_Handler()                __attribute__ ((weak, alias ("Default_Handler")));
void SysTick_Handler()               __attribute__ ((weak, alias ("Default_Handler")));
void SMU_SECURE_IRQHandler()         __attribute__ ((weak, alias ("Default_Handler")));
void SMU_PRIVILEGED_IRQHandler()     __attribute__ ((weak, alias ("Default_Handler")));
void SMU_NS_PRIVILEGED_IRQHandler()  __attribute__ ((weak, alias ("Default_Handler")));
void EMU_IRQHandler()                __attribute__ ((weak, alias ("Default_Handler")));
void TIMER0_IRQHandler()             __attribute__ ((weak, alias ("Default_Handler")));
void TIMER1_IRQHandler()             __attribute__ ((weak, alias ("Default_Handler")));
void TIMER2_IRQHandler()             __attribute__ ((weak, alias ("Default_Handler")));
void TIMER3_IRQHandler()             __attribute__ ((weak, alias ("Default_Handler")));
void TIMER4_IRQHandler()             __attribute__ ((weak, alias ("Default_Handler")));
void USART0_RX_IRQHandler()          __attribute__ ((weak, alias ("Default_Handler")));
void USART0_TX_IRQHandler()          __attribute__ ((weak, alias ("Default_Handler")));
void EUSART0_RX_IRQHandler()         __attribute__ ((weak, alias ("Default_Handler")));
void EUSART0_TX_IRQHandler()         __attribute__ ((weak, alias ("Default_Handler")));
void EUSART1_RX_IRQHandler()         __attribute__ ((weak, alias ("Default_Handler")));
void EUSART1_TX_IRQHandler()         __attribute__ ((weak, alias ("Default_Handler")));
void EUSART2_RX_IRQHandler()         __attribute__ ((weak, alias ("Default_Handler")));
void EUSART2_TX_IRQHandler()         __attribute__ ((weak, alias ("Default_Handler")));
void ICACHE0_IRQHandler()            __attribute__ ((weak, alias ("Default_Handler")));
void BURTC_IRQHandler()              __attribute__ ((weak, alias ("Default_Handler")));
void LETIMER0_IRQHandler()           __attribute__ ((weak, alias ("Default_Handler")));
void SYSCFG_IRQHandler()             __attribute__ ((weak, alias ("Default_Handler")));
void MPAHBRAM_IRQHandler()           __attribute__ ((weak, alias ("Default_Handler")));
void LDMA_IRQHandler()               __attribute__ ((weak, alias ("Default_Handler")));
void LFXO_IRQHandler()               __attribute__ ((weak, alias ("Default_Handler")));
void LFRCO_IRQHandler()              __attribute__ ((weak, alias ("Default_Handler")));
void ULFRCO_IRQHandler()             __attribute__ ((weak, alias ("Default_Handler")));
void GPIO_ODD_IRQHandler()           __attribute__ ((weak, alias ("Default_Handler")));
void GPIO_EVEN_IRQHandler()          __attribute__ ((weak, alias ("Default_Handler")));
void I2C0_IRQHandler()               __attribute__ ((weak, alias ("Default_Handler")));
void I2C1_IRQHandler()               __attribute__ ((weak, alias ("Default_Handler")));
void EMUDG_IRQHandler()              __attribute__ ((weak, alias ("Default_Handler")));
void HOSTMAILBOX_IRQHandler()        __attribute__ ((weak, alias ("Default_Handler")));
void ACMP0_IRQHandler()              __attribute__ ((weak, alias ("Default_Handler")));
void ACMP1_IRQHandler()              __attribute__ ((weak, alias ("Default_Handler")));
void WDOG0_IRQHandler()              __attribute__ ((weak, alias ("Default_Handler")));
void WDOG1_IRQHandler()              __attribute__ ((weak, alias ("Default_Handler")));
void HFXO0_IRQHandler()              __attribute__ ((weak, alias ("Default_Handler")));
void HFRCO0_IRQHandler()             __attribute__ ((weak, alias ("Default_Handler")));
void HFRCOEM23_IRQHandler()          __attribute__ ((weak, alias ("Default_Handler")));
void CMU_IRQHandler()                __attribute__ ((weak, alias ("Default_Handler")));
void IADC_IRQHandler()               __attribute__ ((weak, alias ("Default_Handler")));
void MSC_IRQHandler()                __attribute__ ((weak, alias ("Default_Handler")));
void DPLL0_IRQHandler()              __attribute__ ((weak, alias ("Default_Handler")));
void EMUEFP_IRQHandler()             __attribute__ ((weak, alias ("Default_Handler")));
void DCDC_IRQHandler()               __attribute__ ((weak, alias ("Default_Handler")));
void VDAC_IRQHandler()               __attribute__ ((weak, alias ("Default_Handler")));
void PCNT0_IRQHandler()              __attribute__ ((weak, alias ("Default_Handler")));
void SW0_IRQHandler()                __attribute__ ((weak, alias ("Default_Handler")));
void SW1_IRQHandler()                __attribute__ ((weak, alias ("Default_Handler")));
void SW2_IRQHandler()                __attribute__ ((weak, alias ("Default_Handler")));
void SW3_IRQHandler()                __attribute__ ((weak, alias ("Default_Handler")));
void KERNEL0_IRQHandler()            __attribute__ ((weak, alias ("Default_Handler")));
void KERNEL1_IRQHandler()            __attribute__ ((weak, alias ("Default_Handler")));
void M33CTI0_IRQHandler()            __attribute__ ((weak, alias ("Default_Handler")));
void M33CTI1_IRQHandler()            __attribute__ ((weak, alias ("Default_Handler")));
void FPUEXH_IRQHandler()             __attribute__ ((weak, alias ("Default_Handler")));
void SETAMPERHOST_IRQHandler()       __attribute__ ((weak, alias ("Default_Handler")));
void SEMBRX_IRQHandler()             __attribute__ ((weak, alias ("Default_Handler")));
void SEMBTX_IRQHandler()             __attribute__ ((weak, alias ("Default_Handler")));
void LESENSE_IRQHandler()            __attribute__ ((weak, alias ("Default_Handler")));
void SYSRTC_APP_IRQHandler()         __attribute__ ((weak, alias ("Default_Handler")));
void SYSRTC_SEQ_IRQHandler()         __attribute__ ((weak, alias ("Default_Handler")));
void LCD_IRQHandler()                __attribute__ ((weak, alias ("Default_Handler")));
void KEYSCAN_IRQHandler()            __attribute__ ((weak, alias ("Default_Handler")));
#endif

//void * g_pfnVectors[0x5c] __attribute__ ((section (".isr_vector"), used)) = 
void * g_pfnVectors[] __attribute__((section(".isr_vector"), used)) = 
{
	&_estack,
	&Reset_Handler,
	&NMI_Handler,
	&HardFault_Handler,
	&MemManage_Handler,
//	&BusFault_Handler,
//	&UsageFault_Handler,
//	NULL,
//	NULL,
//	NULL,
//	&Bootloader_MainStageTable,
//	&SVC_Handler,
//	&DebugMon_Handler,
//	&sl_app_properties,
//	&PendSV_Handler,
//	&SysTick_Handler,
//	&SMU_SECURE_IRQHandler,
//	&SMU_PRIVILEGED_IRQHandler,
//	&SMU_NS_PRIVILEGED_IRQHandler,
//	&EMU_IRQHandler,
//	&TIMER0_IRQHandler,
//	&TIMER1_IRQHandler,
//	&TIMER2_IRQHandler,
//	&TIMER3_IRQHandler,
//	&TIMER4_IRQHandler,
//	&USART0_RX_IRQHandler,
//	&USART0_TX_IRQHandler,
//	&EUSART0_RX_IRQHandler,
//	&EUSART0_TX_IRQHandler,
//	&EUSART1_RX_IRQHandler,
//	&EUSART1_TX_IRQHandler,
//	&EUSART2_RX_IRQHandler,
//	&EUSART2_TX_IRQHandler,
//	&ICACHE0_IRQHandler,
//	&BURTC_IRQHandler,
//	&LETIMER0_IRQHandler,
//	&SYSCFG_IRQHandler,
//	&MPAHBRAM_IRQHandler,
//	&LDMA_IRQHandler,
//	&LFXO_IRQHandler,
//	&LFRCO_IRQHandler,
//	&ULFRCO_IRQHandler,
//	&GPIO_ODD_IRQHandler,
//	&GPIO_EVEN_IRQHandler,
//	&I2C0_IRQHandler,
//	&I2C1_IRQHandler,
//	&EMUDG_IRQHandler,
//	NULL,
//	NULL,
//	NULL,
//	NULL,
//	NULL,
//	NULL,
//	NULL,
//	NULL,
//	&HOSTMAILBOX_IRQHandler,
//	NULL,
//	&ACMP0_IRQHandler,
//	&ACMP1_IRQHandler,
//	&WDOG0_IRQHandler,
//	&WDOG1_IRQHandler,
//	&HFXO0_IRQHandler,
//	&HFRCO0_IRQHandler,
//	&HFRCOEM23_IRQHandler,
//	&CMU_IRQHandler,
//	NULL,
//	&IADC_IRQHandler,
//	&MSC_IRQHandler,
//	&DPLL0_IRQHandler,
//	&EMUEFP_IRQHandler,
//	&DCDC_IRQHandler,
//	&VDAC_IRQHandler,
//	&PCNT0_IRQHandler,
//	&SW0_IRQHandler,
//	&SW1_IRQHandler,
//	&SW2_IRQHandler,
//	&SW3_IRQHandler,
//	&KERNEL0_IRQHandler,
//	&KERNEL1_IRQHandler,
//	&M33CTI0_IRQHandler,
//	&M33CTI1_IRQHandler,
//	&FPUEXH_IRQHandler,
//	&SETAMPERHOST_IRQHandler,
//	&SEMBRX_IRQHandler,
//	&SEMBTX_IRQHandler,
//	&LESENSE_IRQHandler,
//	&SYSRTC_APP_IRQHandler,
//	&SYSRTC_SEQ_IRQHandler,
//	&LCD_IRQHandler,
//	&KEYSCAN_IRQHandler,
//	NULL,
//	NULL,
};

void SystemInit();
void __libc_init_array();
int main();

extern void *_sidata, *_sdata, *_edata;
extern void *_sbss, *_ebss;

void __attribute__((naked, noreturn)) Reset_Handler()
{
	//Normally the CPU should will setup the based on the value from the first entry in the vector table.
	//If you encounter problems with accessing stack variables during initialization, ensure the line below is enabled.
	#if defined(sram_layout) || defined(INITIALIZE_SP_AT_RESET)
	__asm ("ldr sp, =_estack");
	#endif

	void **pSource, **pDest;
	for (pSource = &_sidata, pDest = &_sdata; pDest != &_edata; pSource++, pDest++)
		*pDest = *pSource;

	for (pDest = &_sbss; pDest != &_ebss; pDest++)
		*pDest = 0;

	SystemInit();
	__libc_init_array();
	(void)main();
	for (;;) ;
}

void __attribute__((naked, noreturn)) Default_Handler()
{
	//If you get stuck here, your code is missing a handler for some interrupt.
	//Define a 'DEBUG_DEFAULT_INTERRUPT_HANDLERS' macro via VisualGDB Project Properties and rebuild your project.
	//This will pinpoint a specific missing vector.
	for (;;) ;
}
