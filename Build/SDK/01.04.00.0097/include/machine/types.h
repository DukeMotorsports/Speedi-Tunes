/*-
 * Copyright (c) 2007-8, Motec
 * All rights reserved.
 *
 */

#ifndef	_PPC_TYPES_H
#define	_PPC_TYPES_H

#include <sys/cdefs.h>

/*
 * Basic integral types.  Omit the typedef if
 * not possible for a machine/compiler combination.
 */
typedef	signed char		   int8_t;
typedef	unsigned char		  uint8_t;
typedef	short			  int16_t;
typedef	unsigned short		 uint16_t;
typedef	int			  int32_t;
typedef	unsigned int		 uint32_t;
typedef	long long		  int64_t;
typedef	unsigned long long	 uint64_t;
typedef	long long		 intmax_t;
typedef	unsigned long long	uintmax_t;

typedef int8_t		     int_least8_t;
typedef uint8_t		    uint_least8_t;
typedef int16_t		    int_least16_t;
typedef uint16_t	   uint_least16_t;
typedef int32_t		    int_least32_t;
typedef uint32_t	   uint_least32_t;
typedef int64_t		    int_least64_t;
typedef uint64_t	   uint_least64_t;

typedef int8_t		      int_fast8_t;
typedef uint8_t		     uint_fast8_t;
typedef int32_t		     int_fast16_t;
typedef uint32_t	    uint_fast16_t;
typedef int32_t		     int_fast32_t;
typedef uint32_t	    uint_fast32_t;
typedef int64_t		     int_fast64_t;
typedef uint64_t	    uint_fast64_t;

typedef int32_t			 intptr_t;
typedef uint32_t		uintptr_t;

#define INT8_MIN   (-1-0x7f)
#define INT16_MIN  (-1-0x7fff)
#define INT32_MIN  (-1-0x7fffffff)
#define INT64_MIN  (-1-0x7fffffffffffffff)

#define INT8_MAX   (0x7f)
#define INT16_MAX  (0x7fff)
#define INT32_MAX  (0x7fffffff)
#define INT64_MAX  (0x7fffffffffffffff)

#define UINT8_MAX  (0xff)
#define UINT16_MAX (0xffff)
#define UINT32_MAX (0xffffffffu)
#define UINT64_MAX (0xffffffffffffffffu)

#define INT_FAST8_MIN   INT8_MIN
#define INT_FAST16_MIN  INT32_MIN
#define INT_FAST32_MIN  INT32_MIN
#define INT_FAST64_MIN  INT64_MIN

#define INT_LEAST8_MIN   INT8_MIN
#define INT_LEAST16_MIN  INT16_MIN
#define INT_LEAST32_MIN  INT32_MIN
#define INT_LEAST64_MIN  INT64_MIN

#define INT_FAST8_MAX   INT8_MAX
#define INT_FAST16_MAX  INT32_MAX
#define INT_FAST32_MAX  INT32_MAX
#define INT_FAST64_MAX  INT64_MAX

#define INT_LEAST8_MAX   INT8_MAX
#define INT_LEAST16_MAX  INT16_MAX
#define INT_LEAST32_MAX  INT32_MAX
#define INT_LEAST64_MAX  INT64_MAX

#define UINT_FAST8_MAX  UINT8_MAX
#define UINT_FAST16_MAX UINT32_MAX
#define UINT_FAST32_MAX UINT32_MAX
#define UINT_FAST64_MAX UINT64_MAX

#define UINT_LEAST8_MAX  UINT8_MAX
#define UINT_LEAST16_MAX UINT16_MAX
#define UINT_LEAST32_MAX UINT32_MAX
#define UINT_LEAST64_MAX UINT64_MAX

#define INTMAX_MIN  INT64_MIN
#define INTMAX_MAX  INT64_MAX
#define UINTMAX_MAX UINT64_MAX

#define INTPTR_MIN      INT32_MIN
#define INTPTR_MAX      INT32_MAX
#define UINTPTR_MAX     UINT32_MAX
#define PTRDIFF_MIN     INT32_MIN
#define PTRDIFF_MAX     INT32_MAX
#define SIZE_MAX        UINT32_MAX

typedef unsigned long	  paddr_t;	/* type for a physical address */
typedef unsigned long	  vaddr_t;	/* type for a virtual address */
#define PADDR_NULL ((paddr_t)0)

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;
typedef int8_t s8;
typedef int16_t s16;
typedef int32_t s32;
typedef int64_t s64;
typedef float f32;
typedef volatile u8 vu8;
typedef volatile s16 vs16;
typedef volatile u16 vu16;
typedef volatile s32 vs32;
typedef volatile u32 vu32;

typedef int8_t __attribute__((__may_alias__)) as8;
typedef int16_t __attribute__((__may_alias__)) as16;
typedef int32_t __attribute__((__may_alias__)) as32;
typedef uint8_t __attribute__((__may_alias__)) au8;
typedef uint16_t __attribute__((__may_alias__)) au16;
typedef uint32_t __attribute__((__may_alias__)) au32;

typedef union {
	s32 as_s32;
	u32 as_u32;
	f32 as_f32;
	void *as_pv;
} arg_t __attribute__ ((__transparent_union__));

/* functions can optionally return 64 bits */
typedef struct {
	int rc;
	arg_t rval;
} ret64_t;

typedef struct {
	int rc;
	f32 rval;
} rcf32;

#define __always_inline __inline__ __attribute__((__always_inline__))

#endif	/* _PPC_TYPES_H */

