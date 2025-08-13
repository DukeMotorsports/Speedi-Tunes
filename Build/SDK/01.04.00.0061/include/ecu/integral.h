#ifndef __ECU_INTEGRAL_H__
#define __ECU_INTEGRAL_H__
#include <ecu/types.h>
#include <ecu/system.h>

/**
 * @addtogroup Integral
 * @{
 */

/**
 * @fn f32 integral_normal_f32(integral_normal_f32_state *state, f32 arg, f32 min, f32 max, bool reset, f32 preset)
 * @arg ScriptName Normal
 * @arg initcall lib
 *
 * @brief Calculate a normal integral
 *
 * @param state [provide]
 * @param arg value to integrate
 * @param min minimum integral value
 * @param max maximum integral value
 * @param reset reset integral value
 * @param preset value after reset
 * @return integral of <span class="param"/>arg</span> clamped to range [min, max]
 */

typedef struct {
	f32 val;
	elapsed_time_f32_state ets;
} integral_normal_f32_state;

static __inline __warn_unused_result f32 integral_normal_f32(integral_normal_f32_state *state, f32 arg, f32 min, f32 max, bool reset, f32 preset)
{
	if (reset) {
		state->val = preset;
		elapsed_time_f32_init(&state->ets);
	} else {
		const f32 dt = elapsed_time_f32(&state->ets);
		state->val += arg * dt;
	}
	if (state->val < min)
		state->val = min;
	if (state->val > max)
		state->val = max;
	return state->val;
}

static __inline void integral_normal_f32_init(integral_normal_f32_state *state, f32 arg,
    f32 min, f32 max, bool reset, f32 preset)
{
	state->val = preset;
	elapsed_time_f32_init(&state->ets);
	if (state->val < min)
		state->val = min;
	if (state->val > max)
		state->val = max;
}


/** @} Integral */

#endif // __ECU_INTEGRAL_H__
