#ifndef __ECU_DELAY_H__
#define __ECU_DELAY_H__
#include <ecu/types.h>
#include <ecu/system.h>

/**
 * @addtogroup Delay
 * @{
 */

/**
 * @fn bool delay_rising(delay_rising_state *state, bool cond, f32 delay)
 * @arg ScriptName Rising
 * @arg initcall lib
 *
 * @brief Rising edge delay
 *
 * @details <p>The argument <span class="param"/>cond</span> must be true for
 * @details at least <span class="param"/>delay</span> seconds before the
 * @details return value transitions to true.</p>
 * @details <p>The initial return value is the startup value of <span class="param"/>cond</span>.</p>
 *
 * @param state [provide]
 * @param cond boolean condition to delay
 * @param delay delay time
 * @return delayed state
 */

typedef struct {
	bool prev;
	s32 expire;
	bool latch;
} delay_rising_state;

#ifdef ECU_BOARD
static __inline __warn_unused_result bool delay_rising(delay_rising_state *state, bool cond, f32 delay)
{
	const s32 now = ticks_u32();
	const bool edge = !state->prev && cond;
	state->prev = cond;
	if (edge) {
		/* detected rising edge, begin timing */
		if (delay < 0)
			delay = 0;
		state->expire = now + (s32)(delay / tick_period_f32());
	}
	if (cond && !state->latch && ((now - state->expire) >= 0)) {
		/* expired, latch high state */
		state->latch = true;
	}
	if (!cond) {
		/* transitioned back to low state */
		state->latch = false;
	}
	return state->latch;
}
#endif

static __inline void delay_rising_init(delay_rising_state *state, bool cond,
    f32 delay)
{
	state->prev = state->latch = cond;
}

/**
 * @fn bool delay_falling(delay_falling_state *state, bool cond, f32 delay)
 * @arg ScriptName Falling
 * @arg initcall lib
 *
 * @brief Falling edge delay
 *
 * @details <p>The argument <span class="param"/>cond</span> must be false for
 * @details at least <span class="param"/>delay</span> seconds before the
 * @details return value transitions to false.</p>
 * @details <p>The initial return value is the startup value of <span class="param"/>cond</span>.</p>
 *
 * @param state [provide]
 * @param cond boolean condition to delay
 * @param delay delay time
 * @return delayed state
 */

typedef struct {
	bool prev;
	s32 expire;
	bool latch;
} delay_falling_state;

#ifdef ECU_BOARD
static __inline __warn_unused_result bool delay_falling(delay_falling_state *state, bool cond, f32 delay)
{
	const s32 now = ticks_u32();
	const bool edge = state->prev && !cond;
	state->prev = cond;
	if (edge) {
		/* detected falling edge, begin timing */
		if (delay < 0)
			delay = 0;
		state->expire = now + (s32)(delay / tick_period_f32());
	}
	if (!cond && state->latch && ((now - state->expire) >= 0)) {
		/* expired, latch low state */
		state->latch = false;
	}
	if (cond) {
		/* transitioned back to high state */
		state->latch = true;
	}
	return state->latch;
}
#endif

static __inline void delay_falling_init(delay_falling_state *state, bool cond,
    f32 delay)
{
	state->prev = state->latch = cond;
}

/**
 * @fn bool delay_stable_f32(delay_stable_f32_state *state, f32 arg, f32 delay, f32 delta)
 * @arg ScriptName Stable
 * @arg initcall lib
 *
 * @brief Stable value detection
 *
 * @details <p>The argument <span class="param"/>arg</span> must be stable for
 * @details at least <span class="param"/>delay</span> seconds before the
 * @details return value transitions to true.</p>
 *
 * @param state [provide]
 * @param arg value that must be stable
 * @param delay delay time
 * @param delta arg must not change by more than this much
 * @param delta <span class="param"/>arg</span> must must not change by more than this during <span class="param"/>delay</span>
 * @return true when stable
 */

typedef struct {
	f32 prev;
	s32 expire;
	bool stable;
} delay_stable_f32_state;

#ifdef ECU_BOARD
static __inline __warn_unused_result bool delay_stable_f32(delay_stable_f32_state *state, f32 arg, f32 delay, f32 delta)
{
	const s32 now = ticks_u32();
	if (__builtin_fabsf(state->prev - arg) > delta) {
		state->prev = arg;
		/* value changed, begin timing */
		if (delay < 0)
			delay = 0;
		state->expire = now + (s32)(delay / tick_period_f32());
		state->stable = false;
	} else if (state->stable)
		return true;
	else if ((now - state->expire) >= 0) {
		/* expired, latch low state */
		state->stable = true;
	}
	return state->stable;
}
#endif

static __inline void delay_stable_f32_init(delay_stable_f32_state *state,
					   f32 arg, f32 delay, f32 delta)
{
	state->prev = arg;
	state->stable = true;
}

/**
 * @overload bool delay_stable_s32(delay_stable_s32_state *state, s32 arg, f32 delay)
 */
typedef struct {
	s32 prev;
	s32 expire;
	bool stable;
} delay_stable_s32_state;

#ifdef ECU_BOARD
static __inline __warn_unused_result bool delay_stable_s32(
	delay_stable_s32_state *state, s32 arg, f32 delay)
{
	const s32 now = ticks_u32();
	if (state->prev != arg) {
		state->prev = arg;
		/* value changed, begin timing */
		if (delay < 0)
			delay = 0;
		state->expire = now + (s32)(delay / tick_period_f32());
		state->stable = false;
	} else if (state->stable)
		return true;
	else if ((now - state->expire) >= 0) {
		/* expired, latch low state */
		state->stable = true;
	}
	return state->stable;
}
#endif

static __inline void delay_stable_s32_init(delay_stable_s32_state *state,
					   s32 arg, f32 delay)
{
	state->prev = arg;
	state->stable = true;
}

/**
 * @fn f32 delay_signal15_f32(delay_signal15_f32_state *state, f32 arg, f32 delay)
 * @arg ScriptName Signal15
 * @arg initcall lib
 *
 * @brief Delay signal by up to 15 samples
 *
 * @details <p>The argument <span class="param"/>arg</span> is delayed by
 * @details <span class="param">delay</span> samples. If <span class="param>delay
 * @details </span> increases the actual delay will not increase faster than real
 * @details time. If <span class="param">delay</span> is not an integral number
 * @details of samples, two samples will be linearly interpolated.
 *
 * @param state [provide]
 * @param arg value to be delayed
 * @param delay number of samples to delay
 * @return delayed value
 */

typedef struct {
	f32 line[16];
	f32 delay;
	unsigned idx;
} delay_signal15_f32_state;

f32 __warn_unused_result delay_signal15_f32(delay_signal15_f32_state *state, f32 arg,
    f32 delay);

static __inline void delay_signal15_f32_init(delay_signal15_f32_state *state, f32 arg,
    f32 delay)
{
	state->line[0] = arg;
}

/** @} Delay */

#endif // __ECU_DELAY_H__
