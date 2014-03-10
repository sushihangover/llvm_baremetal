
#ifndef INLINE
# define INLINE static inline
#endif

INLINE void svcPrint(int message) {
  const int SYS_WRITE0 = 0x04;
  asm(
       "mov r0, %[cmd]\n"
       "mov r1, %[msg]\n"
       "bkpt #0xAB\n"
        :
        : [cmd] "r" (SYS_WRITE0), [msg] "r" (message)
        : "r0", "r1"
   );
}

