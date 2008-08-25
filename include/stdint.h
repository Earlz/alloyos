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

/**types**/

#ifndef _I386__TYPES_H_
#define _I386__TYPES_H_

#define NULL ((void*)0)

typedef	signed char		int8_t;
typedef	unsigned char		uint8_t;
typedef	short			int16_t;
typedef	unsigned short		uint16_t;
typedef	int			int32_t;
typedef	unsigned int		uint32_t;

typedef	long long		int64_t;

typedef	unsigned long long	uint64_t;



typedef	long			intptr_t;
typedef	unsigned long		uintptr_t;


typedef int			clock_t;
typedef int			clockid_t;
typedef long long		off_t;
typedef long			ptrdiff_t;
typedef	unsigned long		size_t;
typedef	long			ssize_t;
typedef	int			time_t;
typedef int			timer_t;

#endif

