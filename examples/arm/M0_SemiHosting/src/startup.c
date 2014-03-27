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

/* Cortex M0 core interrupt handlers */
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
    uint8_t *src, *dst, *end, len;

    /* Copy with byte pointers to obviate unaligned access problems */

    /* Copy data section from Flash to RAM */
    src = (uint8_t *)&_end_text;
    dst = (uint8_t *)&_start_data;
    end = (uint8_t *)&_end_data;
    while (dst < end)
    {
        *dst++ = *src++;
    }

    /* Clear the bss section */
    dst = (uint8_t *)&_start_bss;
    end = (uint8_t *)&_end_bss;
    while (dst < end)
    {
        *dst++ = 0;
    }
    main();
}

void Dummy_Handler(void) {
    while (1)
        ;
}

