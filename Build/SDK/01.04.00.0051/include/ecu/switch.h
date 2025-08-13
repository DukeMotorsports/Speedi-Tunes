#ifndef __ECU_SWITCH_H__
#define __ECU_SWITCH_H__

#include <ecu/system.h>
#include <ecu/util.h>

/**
 * @addtogroup Switch
 * *@{
 * */

#define SWITCH_COUNT 64

extern s32 switches[SWITCH_COUNT];

/**
 * @fn void switch_set(s32 idx, s32 val)
 * @arg ScriptName Set
 *
 * @brief Set switch value
 *
 * @param idx Switch index (0 to 63)
 * @param val Switch value
 */

static __inline void switch_set(u32 idx, s32 val)
{
	if (idx >= SWITCH_COUNT) {
		if (__builtin_constant_p(idx))
			err_bad_index();
		else
			debug_tmsg("Switch.Set: bad index");
	}

	switches[idx] = val;
}

/**
 * @fn s32 switch_get(s32 idx)
 * @arg ScriptName Get
 *
 * @brief Get switch value
 *
 * @param idx Switch index (0 to 63)
 */

static __inline s32 switch_get(u32 idx)
{
	if (idx >= SWITCH_COUNT) {
		if (__builtin_constant_p(idx))
			err_bad_index();
		else
			debug_tmsg("Switch.Get: bad index");
	}

	return switches[idx];
}

/** @} Switch */

#endif // __ECU_SWITCH_H__

