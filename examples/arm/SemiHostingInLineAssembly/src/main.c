
void main() {
  int SYS_WRITEC = 0x03;
  int SYS_WRITE0 = 0x04;
  register int reg0 asm("r0");
  register int reg1 asm("r1");
  char outchar = '_';

  // A 'NOP' so we can 'see' the start of the folllowing svc call
  asm volatile("mov r0,r0");

  outchar = '!';
  reg0 = SYS_WRITEC;
  reg1 = (int)&outchar;
  asm("svc 0x00123456");
 
  // A 'NOP' so we can 'see' the start of the folllowing svc call
  asm volatile("mov r0,r0");
  reg0 = SYS_WRITEC;
  outchar = '\n';
  reg1 = (int)&outchar;
  asm("svc 0x00123456");

  // A 'NOP' so we can 'see' the start of the folllowing svc call
  asm volatile("mov r0, r0");

  reg0 = SYS_WRITE0;
  reg1 = (int)&"Print this to my jtag debugger\n";
  asm("svc 0x00123456");
}

