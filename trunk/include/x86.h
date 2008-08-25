/*
<Copyright Header>
Copyright (c) 2007 - 2008 Jordan "Earlz/hckr83" Earls  <http://www.Earlz.biz.tm>
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions
are met:

1. Redistributions of source code must retain the above copyright
   notice, this list of conditions and the following disclaimer.
2. Redistributions in binary form must reproduce the above copyright
   notice, this list of conditions and the following disclaimer in the
   documentation and/or other materials provided with the distribution.
3. The name of the author may not be used to endorse or promote products
   derived from this software without specific prior written permission.
   
THIS SOFTWARE IS PROVIDED ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES,
INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY
AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL
THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

This file is part of the AlloyOS project
</Copyright Header>
*/

/**x86 inline assembly functions. Note that not all of these may work. -- mixed Ring 3 and Ring 0**/


#ifndef X86_H
#define X86_H

#include <stdint.h>

void Interrupt(uint8_t num);

inline unsigned char inportb(unsigned int port);
inline void outportb(unsigned int port,unsigned char value);
inline void stopints();
inline void startints();
inline void SetDS(unsigned short seg);
inline void SetES(unsigned short seg);
inline void SetFS(unsigned short seg);
inline void SetGS(unsigned short seg);
inline void SetSS(unsigned short seg);
inline void SetCS(unsigned short seg,void *where);
inline unsigned short GetDS();
inline unsigned short GetES();
inline unsigned short GetGS();
inline unsigned short GetFS();
inline unsigned short GetSS();
inline unsigned short GetCS();

inline void hlt();







#endif


