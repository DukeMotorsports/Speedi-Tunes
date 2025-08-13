#ifndef __ECU_DERIVATIVE_H__
#define __ECU_DERIVATIVE_H__
#include <ecu/types.h>
#include <ecu/system.h>

/**
 * @addtogroup Derivative
 * @{
 */

/**
 * @fn f32 derivative_normal_f32(derivative_normal_f32_state *state, f32 arg)
 * @arg ScriptName Normal
 * @arg initcall lib
 *
 * @brief Calculate a normal derivative
 *
 * @param state [provide]
 * @param arg value to derive
 * @return derivative of <span class="param"/>arg</span>
 */

typedef struct {
	f32 prev;
	elapsed_time_f32_state ets;
} derivative_normal_f32_state;

static __inline __warn_unused_result f32 derivative_normal_f32(derivative_normal_f32_state *state, f32 arg)
{
	const f32 dt = elapsed_time_f32(&state->ets);
	const f32 derivative = (arg - state->prev) / dt;
	state->prev = arg;
	return derivative;
}

static __inline void derivative_normal_f32_init(derivative_normal_f32_state *state,
    f32 arg)
{
	state->prev = arg;
	elapsed_time_f32_init(&state->ets);
}

/**
 * @fn f32 derivative_filtered_f32(derivative_filtered_f32_state *state, f32 arg)
 * @arg ScriptName Filtered
 * @arg initcall lib
 *
 * @brief Calculate a filtered derivative
 *
 * @param state [provide]
 * @param arg value to derive
 * @return filtered derivative of <span class="param"/>arg</span>
 */

typedef struct {
	f32 prev;
	f32 deriv;
	elapsed_time_f32_state ets;
} derivative_filtered_f32_state;

static __inline __warn_unused_result f32 derivative_filtered_f32(derivative_filtered_f32_state *state, f32 arg)
{
	const f32 dt = elapsed_time_f32(&state->ets);
	const f32 derivative = (arg - state->prev) / dt;
	state->deriv = (state->deriv + derivative) / 2;
	state->prev = arg;
	return state->deriv;
}

static __inline void derivative_filtered_f32_init(derivative_filtered_f32_state *state, f32 arg)
{
	state->prev = arg;
	state->deriv = 0;
	elapsed_time_f32_init(&state->ets);
}

/**
 * @fn f32 derivative_adaptive_f32(derivative_adaptive_f32_state *state, f32 arg, f32 delta, f32 max_dt)
 * @arg ScriptName Adaptive
 * @arg initcall lib
 *
 * @brief Calculate an adaptive filtered derivative
 *
 * @param state [provide]
 * @param arg value to derive
 * @param delta minimum delta before derivative update
 * @param max_dt maximum time before derivative update
 * @return adaptive derivative of <span class="param"/>arg</span>
 */

typedef struct {
	f32 prev_chan;
	s32 prev_t;
	f32 deriv;
} derivative_adaptive_f32_state;

static __inline __warn_unused_result f32 derivative_adaptive_f32(derivative_adaptive_f32_state *state, f32 arg, f32 delta, f32 max_dt)
{
	const s32 now = ticks_u32();
	const f32 dx = arg - state->prev_chan;
	const f32 dt = (now - state->prev_t) * tick_period_f32();
	if ((__builtin_fabsf(dx) >= delta) || (dt >= max_dt)) {
		state->deriv = dx / dt;
		state->prev_chan = arg;
		state->prev_t = now;
	}
	return state->deriv;
}

static __inline void derivative_adaptive_f32_init(derivative_adaptive_f32_state *state,
    f32 arg, f32 delta, f32 max_dt)
{
	state->prev_chan = arg;
	state->prev_t = ticks_u32();
	state->deriv = 0;
}

/** @} Derivative */

#endif // __ECU_DERIVATIVE_H__
