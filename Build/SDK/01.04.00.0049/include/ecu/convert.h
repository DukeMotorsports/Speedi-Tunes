#ifndef __ECU_CONVERT_H__
#define __ECU_CONVERT_H__
#include <ecu/types.h>
#include <ecu/system.h>
#include <ecu/util.h>

/**
 * @addtogroup Convert
 * @{
 */

/**
 * @fn s32 convert_integer(f32 arg)
 * @arg ScriptName ToInteger
 *
 * @brief Convert to Integer
 *
 * @details <p>This function rounds <span class="param"/>arg</span> to
 * @details the closest integral value.
 *
 * @return rounded value of <span class="param"/>arg</span>
 */

static __inline __warn_unused_result s32 convert_integer(f32 arg)
{
	s32 ret;

	__asm__ __volatile__("efsctsi %0,%1" : "=r" (ret) : "r" (arg));
	return ret;
}

/**
 * @overload s32 convert_integer_u32(u32 arg)
 */
static __inline __warn_unused_result s32 convert_integer_u32(u32 arg)
{
	if (arg & 0x80000000)
		arg = 0x7FFFFFFF;
	return arg;
}

/**
 * @fn u32 convert_unsigned(f32 arg)
 * @arg ScriptName ToUnsignedInteger
 *
 * @brief Convert to Unsigned Integer
 *
 * @details <p>This function rounds <span class="param"/>arg</span> to
 * @details the next closest unsigned integral value.
 *
 * @return rounded value of <span class="param"/>arg</span>
 */

static __inline __warn_unused_result u32 convert_unsigned(f32 arg)
{
	u32 ret;

	__asm__ __volatile__("efsctui %0,%1" : "=r" (ret) : "r" (arg));
	return ret;
}

/**
 * @overload u32 convert_unsigned_s32(s32 arg)
 */

static __inline __warn_unused_result u32 convert_unsigned_s32(s32 arg)
{
	return (arg > 0) ? arg : 0;
}

/** @} Convert */

#endif // __ECU_CONVERT_H__
