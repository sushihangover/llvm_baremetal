volatile unsigned int * const UART0DR = (unsigned int *)0x101f1000;
 
void print_uart0(const char *s) {
 while(*s != '\0') { /* Loop until end of string */
 *UART0DR = (unsigned int)(*s); /* Transmit char */
 s++; /* Next char */
 }
}

/* Function to avoid linker complaints if applying "-funwind-tables */
/*
void __aeabi_unwind_cpp_pr0(void)
{
};
*/
 
void c_entry() {
 print_uart0("Hello world!\n");
}

