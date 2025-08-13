#ifndef __ECU_TYPES_H__
#define __ECU_TYPES_H__

#ifdef _ECU_SOURCE

/*
 * data types to use in ecu code
 */
typedef float f32;
typedef int s32;
typedef unsigned int u32;
typedef short s16;
typedef unsigned short u16;
typedef signed char s8;
typedef unsigned char u8;
typedef long long s64;
typedef unsigned long long u64;

#define __inline inline __attribute__((always_inline))
#define __warn_unused_result __attribute__((warn_unused_result))

#else	/* !_ECU_SOURCE */
#include <machine/types.h>

#endif	/* !_ECU_SOURCE */

typedef const char *string;

/*
 * fixed point data types
 * <s|u><width>e<exponent>
 * eg: s32e7 = signed 32 bit stored with 10^7 exponent (i.e. 7 decimal places)
 */
typedef s32 s32e7;

#if !defined(__cplusplus)
#define bool _Bool
#define true	1
#define false	0
#endif

/* internal macros */
#define __sect(name, n, flags)						\
	__attribute__((section(name # n flags),used))

/* macros to provide information to optimiser */
#define likely(x) __builtin_expect((!!(x)),1)
#define unlikely(x) __builtin_expect((!!(x)),0)

#define __extern_symbol __attribute__((__externally_visible__))

/*****************************************************************************
 * variables must be taged with these macros to be visible to calibrarion
 * software. These macros are a prefix for declarations
 * data may be read via XCP Data acquisition (DAQ)
 * data may be written via XCP Stimulation (STIM) - required firmware support
 */

/*
 * normal ecu data (channel)
 * - initial value = 0
 */
#define __ecu_data(n)       volatile __sect(".ecu_data", n, ", \"aw\", @nobits#") __extern_symbol
#define __extern_ecu_data   extern volatile __extern_symbol

/*
 * flash backed data (preserved channel)
 * - first initial value = 0
 * - value is periodically preserved to flash
 * - subsequent initial value is restored from flash
 */
#define __ecu_fdata(n)     volatile __sect(".ecu_fdata", n, ", \"aw\", @nobits#") __extern_symbol
#define __extern_ecu_fdata extern volatile __extern_symbol

/*
 * battery backed data (battery backed channel)
 * - first initial value = 0
 * - location is battery backed
 * - value is periodically preserved to flash
 * - ram valid (ECC ok): ram value is used
 * - ram invalid: initial value is restored from flash
 */
#define __ecu_bdata(n)     volatile __sect(".ecu_bdata", n, ", \"aw\", @nobits#") __extern_symbol
#define __extern_ecu_bdata extern volatile __extern_symbol

/*
 * example variable definitions - data accessible by calibration program
 * may be read via XCP Data acquisition (DAQ)
 * may be written via XCP Stimulation (STIM) - required firmware support
 */
#if 0

/* global normal data channel in security group 0 */
__ecu_data(0)     f32 engine_rpm;	/* code */
__extern_ecu_data f32 engine_rpm;	/* header */

/* local flash data channel in security group 1. initial value 0,
   subsequent initial value loaded from flash */
__ecu_fdata(1) static f32 inj7_trim; /* code */

#endif

/*****************************************************************************
 * calibration values must be taged with these macros to be accessible by
 * setup and tune. Use these macros as a prefix for tune declarations
 */

/*
 * normal calibration constants
 * - const to firmware
 * - writable by calibration, value may be saved to flash
 * - initial value = 0 until written by calibration program
 * - data from calibration program is preserved to flash by XCP "set request"
 * - preserved value is restored from flash before firmware started
 */
#define __ecu_cal(n)       const volatile __sect(".ecu_cal", n, ", \"a\", @nobits#") __extern_symbol
#define __extern_ecu_cal   extern const volatile __extern_symbol

/*
 * example calibration value definitions
 */
#if 0

/* local constant in security group 2, visible and adjustable in tune */
__ecu_cal(2) f32 base_pw;	/* code */

#endif

/*****************************************************************************
 * initcall mechanism to mark function to run on specific system events
 */

typedef void (*initcall_t)(void);
typedef void (*exitcall_t)(void);

#define __make_initcall(sect, fn)  const static initcall_t __initcall_##fn \
	__attribute__((__used__, section(".initcall." sect))) = fn
#define __make_exitcall(sect, fn)  const static exitcall_t __exitcall_##fn \
	__attribute__((__used__, section(".exitcall." sect))) = fn

/* sorted initcalls, higher numbers run first */
#define __initcall_driver(fn)  __make_initcall("9.driver", fn)
#define __initcall_resource(fn) __make_initcall("7.resource", fn)
#define __initcall_cfg(fn)     __make_initcall("5.cfg", fn)
#define __initcall_data(fn)    __make_initcall("3.data", fn)
#define __initcall_startup(fn) __make_initcall("2.startup", fn)
#define __initcall_lib(fn)     __make_initcall("1.lib", fn)
#define __initcall(fn)         __make_initcall("0.final", fn)

/* sorted exitcalls, higher numbers run last */
#define __exitcall_driver(fn)  __make_exitcall("9.driver", fn)
#define __exitcall_resource(fn) __make_exitcall("7.resource", fn)
#define __exitcall_thread(fn)  __make_exitcall("1.thread", fn)
#define __exitcall(fn)	       __make_exitcall("0.first", fn)

/*****************************************************************************
 * macros to access masked channels
 */
#define __mask(len) ((1<<(len))-1)

#define __mask_get(chan, len, shift)		\
	/* ct_assert((len + shift) <= 32) */	\
	(((chan) >> (shift)) & __mask(len))

#define __mask_set(chan, len, shift, val)			\
	/* ct_assert((len + shift) <= 32) */			\
	chan = ((chan) & ~(__mask(len)<<(shift))) |		\
		(((val) << (shift)) & (__mask(len)<<(shift)))

#endif /* __ECU_TYPES_H__ */
