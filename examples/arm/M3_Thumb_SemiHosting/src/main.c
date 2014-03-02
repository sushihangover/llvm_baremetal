
int main() {

  // A 'NOP' so we can 'see' the start of the folllowing svc call
  asm volatile("mov r0,r0");

  volatile int a = 0;
  a++;

  int SYS_WRITEC = 0x03;
  int SYS_WRITE0 = 0x04;
  register int reg0 asm("r0");
  register int reg1 asm("r1");

  int outstring = (int)&"Print this SVC request\n\0";

  asm(
       "mov r0, %[cmd]\n"
       "mov r1, %[msg]\n" 
       "bkpt #0xAB\n"
	:                              
	: [cmd] "r" (SYS_WRITE0), [msg] "r" (outstring)
	: "r0", "r1"
   );

   return a; 
}

