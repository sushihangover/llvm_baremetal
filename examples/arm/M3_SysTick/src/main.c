#include <stdio.h>
#include <stdlib.h>

#include "CortexM3_xx.h"
#include <core_cm3.h>
#include <stdint.h> 
#include "svc.h"

volatile uint32_t myTicks;

void SysTick_Handler(void) {
  myTicks++;
  printf("...myTicks = %lu; SysTick->VAL = %lu\n", myTicks, SysTick->VAL);
}

int main(void) {
	printf("SysTick should not be active yet...\n");
	for (int x=0; x<10; x++) {
		printf("...Current value: %lu\n", SysTick->VAL);
	}
	printf("Enable SysTick and lets poll it...\n");
	
	volatile uint32_t clock = 10000;
	SysTick->LOAD = clock - 1;
	/*
		* SysTick_CTRL_CLKSOURCE_Msk : Use core's clock
		* SysTick_CTRL_ENABLE_Msk    : Enable SysTick
		* SysTick_CTRL_TICKINT_Msk   : Active the SysTick interrupt on the NVIC
	*/ 
	SysTick->CTRL = SysTick_CTRL_CLKSOURCE_Msk | SysTick_CTRL_ENABLE_Msk;
	for (int x=0; x<10; x++) {
		printf("...Current value: %lu\n", SysTick->VAL);
	}

	printf("Enable SysTick Interrupts and watch local var get incremented...\n");
	myTicks = 0;
	SysTick->CTRL = SysTick_CTRL_CLKSOURCE_Msk |  SysTick_CTRL_ENABLE_Msk | SysTick_CTRL_TICKINT_Msk;
	
	while(myTicks <= 10) {
		asm("nop"); // Do nothing till SysTick_Handler been been called at least 10 times
	}
	exit(0);
}

