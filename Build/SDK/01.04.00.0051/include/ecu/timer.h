#ifndef __ECU_TIMER_H__
#define __ECU_TIMER_H__
#include <ecu/types.h>
#include <ecu/system.h>

/**
 * @addtogroup Timer
 * @{
 */

/**
 * @fn void timer_set_f32(timer_f32_state *state, f32 timeout)
 * @arg ScriptName __Set
 * @arg initcall lib
 * @brief Set a count down timer.
 * @param state [object] timer to set
 * @param timeout timer duration (clamped to approx 4400 seconds)
 * @return none
*/

typedef struct {
	s32 expire;
} timer_f32_state;

static __inline void timer_set_f32(timer_f32_state *state, f32 timeout)
{
	s32 now = ticks_u32();

	state->expire = now + (s32)(timeout / tick_period_f32());
}

/**
 * @fn f32 timer_remaining_f32(timer_f32_state *state)
 * @arg ScriptName __Remaining
 * @arg initcall lib
 * @brief Get the time remaining on a count down timer.
 * @param state timer to check
 * @return time remaining
*/

static __inline __warn_unused_result f32 timer_remaining_f32(timer_f32_state *state)
{
	if (state->expire == 0)
		return 0;

	s32 remaining = state->expire - ticks_u32();

	if (remaining > 0)
		return remaining * tick_period_f32();

	state->expire = 0;
	return 0;
}

/** @} Timer */

#endif /* __ECU_TIMER_H__ */
