#ifndef __ECU_LIMIT_H__
#define __ECU_LIMIT_H__
#include <ecu/types.h>

/**
 * @addtogroup Limit
 * @{
 */

/**
 * @fn s32 limit_min_s32(s32 arg, s32 min)
 * @arg ScriptName Min
 *
 * @brief Limit minimum value of argument
 *
 * @details <p>Ensure that <span class="param"/>arg</span> >=
 * @details <span class="param"/>min</span>.</p>
 *
 * @param arg value to limit
 * @param min minimum value
 * @return limited value
 */

static __inline __warn_unused_result s32 limit_min_s32(s32 arg, s32 min)
{
	return (arg < min) ? min : arg;
}

/**
 * @overload f32 limit_min_f32(f32 arg, f32 min)
 */

static __inline __warn_unused_result f32 limit_min_f32(f32 arg, f32 min)
{
	return (arg < min) ? min : arg;
}

/**
 * @fn s32 limit_max_s32(s32 arg, s32 max)
 * @arg ScriptName Max
 *
 * @brief Limit maximum value of argument
 *
 * @details <p>Ensure that <span class="param"/>arg</span> <=
 * @details <span class="param"/>max</span>.</p>
 *
 * @param arg value to limit
 * @param max maximum value
 * @return limited value
 */

static __inline __warn_unused_result s32 limit_max_s32(s32 arg, s32 max)
{
	return (arg > max) ? max : arg;
}

/**
 * @overload f32 limit_max_f32(f32 arg, f32 max)
 */

static __inline __warn_unused_result f32 limit_max_f32(f32 arg, f32 max)
{
	return (arg > max) ? max : arg;
}

/**
 * @fn s32 limit_range_s32(s32 arg, s32 min, s32 max)
 * @arg ScriptName Range
 *
 * @brief Limit argument to range
 *
 * @details <p>Ensure that <span class="param"/>arg</span> within range
 * @details [<span class="param"/>min</span>, <span class="param"/>max</span>].</p>
 *
 * @param arg value to limit
 * @param min minimum value
 * @param max maximum value
 * @return limited value
 */

static __inline __warn_unused_result s32 limit_range_s32(s32 arg, s32 min, s32 max)
{
	if (arg < min)
		return min;
	if (arg > max)
		return max;
	return arg;
}

/**
 * @overload f32 limit_range_f32(f32 arg, f32 min, f32 max)
 */

static __inline __warn_unused_result f32 limit_range_f32(f32 arg, f32 min, f32 max)
{
	if (arg < min)
		return min;
	if (arg > max)
		return max;
	return arg;
}

/** @} Limit */

#endif // __ECU_LIMIT_H__
