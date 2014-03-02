/* startup.c */

#include <stdint.h>

/* Addresses pulled in from the linker script */
extern uint32_t _end_stack;
extern uint32_t _end_text;
extern uint32_t _start_data;
extern uint32_t _end_data;
extern uint32_t _start_bss;
extern uint32_t _end_bss;

#define WEAK_ALIAS(x) __attribute__ ((weak, alias(#x)))

/* Application main() called in reset handler */
//extern int main(void);

/* Cortex M3 core interrupt handlers */
void Reset_Handler(void);
void NMI_Handler(void) WEAK_ALIAS(Dummy_Handler);
void HardFault_Handler(void) WEAK_ALIAS(Dummy_Handler);
void MemManage_Handler(void) WEAK_ALIAS(Dummy_Handler);
void BusFault_Handler(void) WEAK_ALIAS(Dummy_Handler);
void UsageFault_Handler(void) WEAK_ALIAS(Dummy_Handler);
void SVC_Handler(void) WEAK_ALIAS(Dummy_Handler);
void DebugMon_Handler(void) WEAK_ALIAS(Dummy_Handler);
void PendSV_Handler(void) WEAK_ALIAS(Dummy_Handler);
void SysTick_Handler(void) WEAK_ALIAS(Dummy_Handler);

/* LPC13xx specific interrupt handlers */
void WAKEUP_Handler(void) WEAK_ALIAS(Dummy_Handler);
void I2C_Handler(void) WEAK_ALIAS(Dummy_Handler);
void TIMER_16_0_Handler(void) WEAK_ALIAS(Dummy_Handler);
void TIMER_16_1_Handler(void) WEAK_ALIAS(Dummy_Handler);
void TIMER_32_0_Handler(void) WEAK_ALIAS(Dummy_Handler);
void TIMER_32_1_Handler(void) WEAK_ALIAS(Dummy_Handler);
void SSP_Handler(void) WEAK_ALIAS(Dummy_Handler);
void UART_Handler(void) WEAK_ALIAS(Dummy_Handler);
void USB_IRQ_Handler(void) WEAK_ALIAS(Dummy_Handler);
void USB_FIQ_Handler(void) WEAK_ALIAS(Dummy_Handler);
void ADC_Handler(void) WEAK_ALIAS(Dummy_Handler);
void WDT_Handler(void) WEAK_ALIAS(Dummy_Handler);
void BOD_Handler(void) WEAK_ALIAS(Dummy_Handler);
void EINT3_Handler(void) WEAK_ALIAS(Dummy_Handler);
void EINT2_Handler(void) WEAK_ALIAS(Dummy_Handler);
void EINT1_Handler(void) WEAK_ALIAS(Dummy_Handler);
void EINT0_Handler(void) WEAK_ALIAS(Dummy_Handler);

void Dummy_Handler(void);

/* Stack top and vector handler table */
void *vector_table[] __attribute__ ((section(".vectors"))) = {
    &_end_stack,
    Reset_Handler,
    NMI_Handler,
    HardFault_Handler,
    MemManage_Handler,
    BusFault_Handler,
    UsageFault_Handler,
    0,
    0,
    0,
    0,
    SVC_Handler,
    DebugMon_Handler,
    0,
    PendSV_Handler,
    SysTick_Handler,
};

/* Application main() called in reset handler */
extern int main(void);

void Reset_Handler(void) {
    uint8_t *src, *dst;

    /* Copy with byte pointers to obviate unaligned access problems */

    /* Copy data section from Flash to RAM */

    src = (uint8_t *)&_end_text;
    dst = (uint8_t *)&_start_data;
    while (dst < (uint8_t *)&_end_data)
        *dst++ = *src++;

    /* Clear the bss section */

    dst = (uint8_t *)&_start_bss;
    while (dst < (uint8_t *)&_end_bss)
        *dst++ = 0;

    main();
}

void Dummy_Handler(void) {
    while (1)
        ;
}

