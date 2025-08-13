#ifndef __ECU_DEBOUNCE_H__
#define __ECU_DEBOUNCE_H__
#include <ecu/types.h>
#include <ecu/calculate.h>
#include <ecu/filter.h>

/**
 * @addtogroup Debounce
 * @{
 */

/**
 * @fn bool debounce_stable(debounce_stable_state *state, bool cond, f32 filter)
 * @arg ScriptName Stable
 * @arg initcall lib
 *
 * @brief Debounce boolean condition
 *
 * @details <p>Debounce <span class="param"/>cond</span> for at least
 * @details <span class="param"/>filter</span> seconds. If
 * @details <span class="param"/>cond</span> reverts to original state
 * @details filtering is restarted.</p>
 *
 * @param state [provide]
 * @param cond boolean condition to debounce
 * @param filter debounce time, latched when <span class="param"/>cond</span> changes
 * @return debounced state
 */

typedef struct {
	bool cond;
	s32 expire;
} debounce_stable_state;

static __inline __warn_unused_result bool debounce_stable(debounce_stable_state *state, bool cond, f32 filter)
{
	s32 now = ticks_u32();

	if (cond == state->cond) { /* cond state unchanged */
		state->expire = 0;
		return state->cond;
	}
	if (unlikely(state->expire == 0)) { /* starting state change */
		/* book E floating point round clamps to max s32 */
		state->expire = now + (s32)(filter / tick_period_f32());
	}
	if (unlikely((now - state->expire) >= 0)) {
		state->expire = 0;
		state->cond = cond;
	}
	return state->cond;
}

static __inline void debounce_stable_init(debounce_stable_state *state, bool cond, f32 filter)
{
	state->cond = cond; /* boolean */
}

/**
 * @fn bool debounce_fast(debounce_fast_state *state, bool cond, f32 filter)
 * @arg ScriptName Fast
 * @arg initcall lib
 *
 * @brief Debounce boolean condition
 *
 * @details <p>Debounce <span class="param"/>cond</span> for at least
 * @details <span class="param"/>filter</span> seconds.</p>
 *
 * @param state [provide]
 * @param cond boolean condition to debounce
 * @param filter debounce time, latched when <span class="param"/>cond</span> changes
 * @return debounced state
 */

typedef struct {
	bool cond;
	bool timing;
	s32 expire;
} debounce_fast_state;

static __inline __warn_unused_result bool debounce_fast(debounce_fast_state *state, bool cond, f32 filter)
{
	const s32 now = ticks_u32();

	if (state->timing) {
		if ((now - state->expire) >= 0)
			state->timing = false;
		else
			return state->cond;
	}

	if (cond != state->cond) {
		state->cond = cond;
		state->expire = now + (s32)(filter / tick_period_f32());
		state->timing = true;
	}

	return state->cond;
}

static __inline void debounce_fast_init(debounce_fast_state *state, bool cond,
    f32 filter)
{
	const s32 now = ticks_u32();
	state->cond = cond;
	state->timing = true;
	state->expire = now + (s32)(filter / tick_period_f32());
}

/**
 * @fn bool debounce_verify(debounce_verify_state *state, bool cond, f32 filter)
 * @arg ScriptName Verify
 * @arg initcall lib
 *
 * @brief Debounce boolean condition
 *
 * @details <p>Debounce <span class="param"/>cond</span> for at least
 * @details <span class="param"/>filter</span> seconds. Verify that
 * @details <span class="param"/>cond</span> is in new state after filtering.</p>
 *
 * @param state [provide]
 * @param cond boolean condition to debounce
 * @param filter debounce time, latched when <span class="param"/>cond</span> changes
 * @return debounced state
 */

typedef struct {
	bool cond;
	bool timing;
	s32 expire;
} debounce_verify_state;

static __inline __warn_unused_result bool debounce_verify(debounce_verify_state *state, bool cond, f32 filter)
{
	const s32 now = ticks_u32();

	if (state->timing) {
		if ((now - state->expire) >= 0) {
			state->cond = cond;
			state->timing = false;
		}
		return state->cond;
	}

	if (cond != state->cond) {
		state->expire = now + (s32)(filter / tick_period_f32());
		state->timing = true;
	}

	return state->cond;
}

static __inline void debounce_verify_init(debounce_verify_state *state, bool cond,
    f32 filter)
{
	state->cond = cond;
}

/**
 * @fn bool debounce_filter(debounce_filter_state *state, bool cond, f32 tc)
 * @arg ScriptName Filter
 * @arg initcall lib
 *
 * @brief Debounce boolean condition
 *
 * @details <p>Debounce <span class="param"/>cond</span> by filtering with
 * @details <span class="func">Filter.FirstOrder</span>, then performing hysteresis
 * @details with <span class="func">Calculate.Hysteresis</span> using 0.2 and 0.8
 * @details as threshold levels.</p>
 *
 * @param state [provide]
 * @param cond boolean condition to debounce
 * @param tc filter time constant <span class="func">Filter.FirstOrcer</span>
 * @return debounced state
 */

typedef struct {
	filter_firstorder_f32_state bs;
	calculate_hysteresis_f32_state hs;
} debounce_filter_state;

static __inline __warn_unused_result bool debounce_filter(debounce_filter_state *state, bool cond, f32 response)
{
	const f32 chan = filter_firstorder_f32(&state->bs, cond, response);
	return calculate_hysteresis_f32(&state->hs, chan, 0.2, 0.8, 0.0);
}

static __inline void debounce_filter_init(debounce_filter_state *state, bool cond,
    f32 response)
{
	filter_firstorder_f32_init(&state->bs, cond, response);
	calculate_hysteresis_f32_init(&state->hs, cond, 0.2, 0.8, 0.0);
}

/** @} Debounce */

#endif // __ECU_DEBOUNCE_H__
