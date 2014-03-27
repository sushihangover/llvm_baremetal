#include "printf.h"
#include "printf_svc.h"

void putc (void* p, char c)
{
	svcPutChar(&c);
}

int main (void)
{
	set_putc(putc);
	printf("BKPT Hello World\n");
	printf("How small is this?\n");
	
	svcExit(); // QEMU system exit
	
	while (1) { };
}
