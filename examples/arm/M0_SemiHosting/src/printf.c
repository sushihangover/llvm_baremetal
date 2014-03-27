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

#include "printf.h"

typedef void (*putcf)(void*, char);
static putcf out_putf;
static void* out_putp;

void set_putc(void (*putf)(void*, char)) {
	out_putf = putf;
}

void setup_printf(void* putp, void (*putf)(void*, char)) {
	out_putf = putf;
	out_putp = putp;
}

#ifdef PRINTF_LONG
static void uli2a(unsigned long int num, unsigned int base, int uc,char * bf)
{
	int n=0;
	unsigned int d=1;
	while (num/d >= base)
	d*=base;
	while (d!=0) {
		int dgt = num / d;
		num%=d;
		d/=base;
		if (n || dgt>0|| d==0) {
			*bf++ = dgt+(dgt<10 ? '0' : (uc ? 'A' : 'a')-10);
			++n;
		}
	}
	*bf=0;
}

static void li2a (long num, char * bf)
{
	if (num<0) {
		num=-num;
		*bf++ = '-';
	}
	uli2a(num,10,0,bf);
}
#endif

static void ui2a(unsigned int num, unsigned int base, int uc, char * bf) {
	int n = 0;
	unsigned int d = 1;
	while (num / d >= base)
		d *= base;
	while (d != 0) {
		int dgt = num / d;
		num %= d;
		d /= base;
		if (n || dgt > 0 || d == 0) {
			*bf++ = dgt + (dgt < 10 ? '0' : (uc ? 'A' : 'a') - 10);
			++n;
		}
	}
	*bf = 0;
}

static void i2a(int num, char * bf) {
	if (num < 0) {
		num = -num;
		*bf++ = '-';
	}
	ui2a(num, 10, 0, bf);
}

static int a2d(char ch) {
	if (ch >= '0' && ch <= '9')
		return ch - '0';
	else if (ch >= 'a' && ch <= 'f')
		return ch - 'a' + 10;
	else if (ch >= 'A' && ch <= 'F')
		return ch - 'A' + 10;
	else
		return -1;
}

static char a2i(char ch, char** src, int base, int* nump) {
	char* p = *src;
	int num = 0;
	int digit;
	while ((digit = a2d(ch)) >= 0) {
		if (digit > base)
			break;
		num = num * base + digit;
		ch = *p++;
	}
	*src = p;
	*nump = num;
	return ch;
}

static void putchw(void* putp, putcf putf, int n, char z, char* bf) {
	char fc = z ? '0' : ' ';
	char ch;
	char* p = bf;
	while (*p++ && n > 0)
		n--;
	while (n-- > 0)
		putf(putp, fc);
	while ((ch = *bf++))
		putf(putp, ch);
}

void svc_format(void* putp, putcf putf, char *fmt, va_list va) {
	char bf[12];
	char ch;

	while ((ch = *(fmt++))) {
		if (ch != '%')
			putf(putp, ch);
		else {
			char lz = 0;
#ifdef PRINTF_LONG
			char lng=0;
#endif
			int w = 0;
			ch = *(fmt++);
			if (ch == '0') {
				ch = *(fmt++);
				lz = 1;
			}
			if (ch >= '0' && ch <= '9') {
				ch = a2i(ch, &fmt, 10, &w);
			}
#ifdef PRINTF_LONG
			if (ch=='l') {
				ch=*(fmt++);
				lng=1;
			}
#endif
			switch (ch) {
			case 0:
				goto abort;
			case 'u': {
#ifdef PRINTF_LONG
				if (lng)
				uli2a(va_arg(va, unsigned long int),10,0,bf);
				else
#endif
				ui2a(va_arg(va, unsigned int),10,0,bf);
				putchw(putp, putf, w, lz, bf);
				break;
			}
			case 'd': {
#ifdef PRINTF_LONG
				if (lng)
				li2a(va_arg(va, unsigned long int),bf);
				else
#endif
				i2a(va_arg(va, int),bf);
				putchw(putp, putf, w, lz, bf);
				break;
			}
			case 'x':
			case 'X':
#ifdef PRINTF_LONG
				if (lng)
				uli2a(va_arg(va, unsigned long int),16,(ch=='X'),bf);
				else
#endif
				ui2a(va_arg(va, unsigned int),16,(ch=='X'),bf);
				putchw(putp, putf, w, lz, bf);
				break;
			case 'c':
				putf(putp,(char)(va_arg(va, int)));
				break;
			case 's':
				putchw(putp,putf,w,0,va_arg(va, char*));
				break;
			case '%':
				putf(putp, ch);
			default:
				break;
			}
		}
	}
	abort: ;
}


void svc_printf(char *fmt, ...) {
	va_list va;
	va_start(va, fmt);
	svc_format(out_putp, out_putf, fmt, va);
	va_end(va);
}

static void putcp(void* p, char c) {
	*(*((char**) p))++ = c;
}

void svc_sprintf(char* s, char *fmt, ...) {
	va_list va;
	va_start(va, fmt);
	svc_format(&s, putcp, fmt, va);
	putcp(&s, 0);
	va_end(va);
}

