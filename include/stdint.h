
#ifndef _I386__TYPES_H_
#define _I386__TYPES_H_

#define NULL ((void*)0)

typedef	signed char		int8_t;
typedef	unsigned char		uint8_t;
typedef	short			int16_t;
typedef	unsigned short		uint16_t;
typedef	int			int32_t;
typedef	unsigned int		uint32_t;
/* LONGLONG */
typedef	long long		int64_t;
/* LONGLONG */
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

