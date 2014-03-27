/*
	Copyright (c) 2014, SushiHangover/RobertN
	All rights reserved.

	Redistribution and use in source and binary forms, with or without
	modification, are permitted provided that the following conditions are met:
	1. Redistributions of source code must retain the above copyright
	   notice, this list of conditions and the following disclaimer.
	2. Redistributions in binary form must reproduce the above copyright
	   notice, this list of conditions and the following disclaimer in the
	   documentation and/or other materials provided with the distribution.
	3. All advertising materials mentioning features or use of this software
	   must display the following acknowledgement:
	   This product includes software developed by SushiHangover or RobertN.
	4. Neither the name of the SushiHangover or RobertN nor the
	   names of its contributors may be used to endorse or promote products
	   derived from this software without specific prior written permission.

	THIS SOFTWARE IS PROVIDED BY SushiHangover/RobertN ''AS IS'' AND ANY
	EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
	WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
	DISCLAIMED. IN NO EVENT SHALL SushiHangover/RobertN BE LIABLE FOR ANY
	DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
	(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
	LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
	ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
	(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
	SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#ifndef INLINE
# define INLINE static inline
#endif

const int SYS_WRITEC = 0x03;
const int SYS_WRITE0 = 0x04;
const int SYS_EXIT   = 0x18;

INLINE void svcPutString(void* message) {  
  asm(
       "mov r0, %[cmd]\n"
       "mov r1, %[msg]\n"
       "bkpt #0xAB\n"
        :
        : [cmd] "r" (SYS_WRITE0), [msg] "r" (message)
        : "r0", "r1"
   );
}

INLINE void svcPutChar(void* letter) {
  asm(
       "mov r0, %[cmd]\n"
       "mov r1, %[msg]\n"
       "bkpt #0xAB\n"
        :
        : [cmd] "r" (SYS_WRITEC), [msg] "r" (letter)
        : "r0", "r1"
   );
}

#ifdef QDEBUG
INLINE void svcExit() {
  asm(
       "mov r0, %[cmd]\n"
       "bkpt #0xAB\n"
        :
        : [cmd] "r" (SYS_EXIT)
        : "r0"
   );
}
#else
void svcExit() {
	// NOP
}
#endif
