#ifndef __ECU_CHANGE_H__
#define __ECU_CHANGE_H__
#include <ecu/types.h>
#include <ecu/system.h>
#include <ecu/util.h>

/**
 * @addtogroup Change
 * @{
 */

/**
 * @fn bool change_up_s32(change_up_s32_state *state, s32 arg, s32 delta, f32 filter)
 * @arg ScriptName Up
 * @arg initcall lib
 *
 * @brief Detect upwards change
 *
 * @details <p>True for one iteration after at least <span class="param"/>filter</span>
 * @details seconds from <span class="param"/>arg</span> becoming greater than its
 * @details previous value by <span class="param"/>delta</span>.</p>
 * @details <p>At startup the initial value of <span class="param"/>arg</span> is latched.</p>
 *
 * @param state [provide]
 * @param arg value to detect changes on
 * @param delta delta by which <span class="param"/>arg</span> must change
 * @param filter filter time
 * @return true if change detected
 */

typedef struct {
	s32 thresh;
	s32 expire;
	bool timing;
} change_up_s32_state;

static __inline __warn_unused_result bool change_up_s32(change_up_s32_state *state, s32 arg, s32 delta, f32 filter)
{
	if (delta < 1)
		delta = 1;

	if (arg >= state->thresh) {
		const s32 now = ticks_u32();
		if (!state->timing) {
			/* start timer */
			if (filter < 0)
				filter = 0;
			state->expire = now + (s32)(filter / tick_period_f32());
			state->timing = true;
		}
		if ((now - state->expire) >= 0) {
			/* timer expired */
			state->thresh = arg + delta;
			state->timing = false;
			return true;
		}
		return false;
	}

	state->timing = false;
	const s32 new_thresh = arg + delta;
	if (new_thresh < state->thresh)
		state->thresh = new_thresh;

	return false;
}

static __inline void change_up_s32_init(change_up_s32_state *state, s32 arg, s32 delta,
    f32 filter)
{
	if (delta < 1)
		delta = 1;

	state->thresh = arg + delta;
}

/**
 * @overload bool change_up_immed_s32(change_up_immed_s32_state *state, s32 arg, s32 delta)
 */

typedef struct {
	s32 thresh;
} change_up_immed_s32_state;

static __inline __warn_unused_result bool change_up_immed_s32(change_up_immed_s32_state *state, s32 arg, s32 delta)
{
	if (delta < 1)
		delta = 1;

	if (arg >= state->thresh) {
		state->thresh = arg + delta;
		return true;
	}

	const s32 new_thresh = arg + delta;
	if (new_thresh < state->thresh)
		state->thresh = new_thresh;

	return false;
}

static __inline void change_up_immed_s32_init(change_up_immed_s32_state *state, s32 arg, s32 delta)
{
	if (delta < 1)
		delta = 1;

	state->thresh = arg + delta;
}

/**
 * @overload bool change_up_f32(change_up_f32_state *state, f32 arg, f32 delta, f32 filter)
 */

typedef struct {
	f32 thresh;
	s32 expire;
	bool timing;
} change_up_f32_state;

static __inline __warn_unused_result bool change_up_f32(change_up_f32_state *state, f32 arg, f32 delta, f32 filter)
{
	if (delta < 0)
		delta = 0;

	if (arg > state->thresh) {
		const s32 now = ticks_u32();
		if (!state->timing) {
			/* start timer */
			if (filter < 0)
				filter = 0;
			state->expire = now + (s32)(filter / tick_period_f32());
			state->timing = true;
		}
		if ((now - state->expire) >= 0) {
			/* timer expired */
			state->thresh = arg + delta;
			state->timing = false;
			return true;
		}
		return false;
	}

	state->timing = false;
	const f32 new_thresh = arg + delta;
	if (new_thresh < state->thresh)
		state->thresh = new_thresh;

	return false;
}

static __inline void change_up_f32_init(change_up_f32_state *state, f32 arg, f32 delta,
    f32 filter)
{
	if (delta < 0)
		delta = 0;

	state->thresh = arg + delta;
}

/**
 * @overload bool change_up_immed_f32(change_up_immed_f32_state *state, f32 arg, f32 delta)
 */

typedef struct {
	f32 thresh;
} change_up_immed_f32_state;

static __inline __warn_unused_result bool change_up_immed_f32(change_up_immed_f32_state *state, f32 arg, f32 delta)
{
	if (delta < 0)
		delta = 0;

	if (arg > state->thresh) {
		state->thresh = arg + delta;
		return true;
	}

	const f32 new_thresh = arg + delta;
	if (new_thresh < state->thresh)
		state->thresh = new_thresh;

	return false;
}

static __inline void change_up_immed_f32_init(change_up_immed_f32_state *state, f32 arg, f32 delta)
{
	if (delta < 0)
		delta = 0;

	state->thresh = arg + delta;
}

/**
 * @fn bool change_down_s32(change_down_s32_state *state, s32 arg, s32 delta, f32 filter)
 * @arg ScriptName Down
 * @arg initcall lib
 *
 * @brief Detect downwards change
 *
 * @details <p>True for one iteration after at least <span class="param"/>filter</span>
 * @details seconds from <span class="param"/>arg</span> becoming less than its
 * @details previous value by <span class="param"/>delta</span>.</p>
 * @details <p>At startup the initial value of <span class="param"/>arg</span> is latched.</p>
 *
 * @param state [provide]
 * @param arg value to detect changes on
 * @param delta delta by which <span class="param"/>arg</span> must change
 * @param filter filter time
 * @return true if change detected
 */

typedef struct {
	s32 thresh;
	s32 expire;
	bool timing;
} change_down_s32_state;

static __inline __warn_unused_result bool change_down_s32(change_down_s32_state *state, s32 arg, s32 delta, f32 filter)
{
	if (delta < 1)
		delta = 1;

	if (arg <= state->thresh) {
		const s32 now = ticks_u32();
		if (!state->timing) {
			/* start timer */
			if (filter < 0)
				filter = 0;
			state->expire = now + (s32)(filter / tick_period_f32());
			state->timing = true;
		}
		if ((now - state->expire) >= 0) {
			/* timer expired */
			state->thresh = arg - delta;
			state->timing = false;
			return true;
		}
		return false;
	}

	state->timing = false;
	const s32 new_thresh = arg - delta;
	if (new_thresh > state->thresh)
		state->thresh = new_thresh;

	return false;
}

static __inline void change_down_s32_init(change_down_s32_state *state, s32 arg,
    s32 delta, f32 filter)
{
	if (delta < 1)
		delta = 1;

	state->thresh = arg - delta;
}

/**
 * @overload bool change_down_immed_s32(change_down_immed_s32_state *state, s32 arg, s32 delta)
 */

typedef struct {
	s32 thresh;
} change_down_immed_s32_state;

static __inline __warn_unused_result bool change_down_immed_s32(change_down_immed_s32_state *state, s32 arg, s32 delta)
{
	if (delta < 1)
		delta = 1;

	if (arg <= state->thresh) {
		state->thresh = arg - delta;
		return true;
	}

	const s32 new_thresh = arg - delta;
	if (new_thresh > state->thresh)
		state->thresh = new_thresh;

	return false;
}

static __inline void change_down_immed_s32_init(change_down_immed_s32_state *state, s32 arg, s32 delta)
{
	if (delta < 1)
		delta = 1;

	state->thresh = arg - delta;
}

/**
 * @overload bool change_down_f32(change_down_f32_state *state, f32 arg, f32 delta, f32 filter)
 */

typedef struct {
	f32 thresh;
	s32 expire;
	bool timing;
} change_down_f32_state;

static __inline __warn_unused_result bool change_down_f32(change_down_f32_state *state, f32 arg, f32 delta, f32 filter)
{
	if (delta < 0)
		delta = 0;

	if (arg < state->thresh) {
		const s32 now = ticks_u32();
		if (!state->timing) {
			/* start timer */
			if (filter < 0)
				filter = 0;
			state->expire = now + (s32)(filter / tick_period_f32());
			state->timing = true;
		}
		if ((now - state->expire) >= 0) {
			/* timer expired */
			state->thresh = arg - delta;
			state->timing = false;
			return true;
		}
		return false;
	}

	state->timing = false;
	const f32 new_thresh = arg - delta;
	if (new_thresh > state->thresh)
		state->thresh = new_thresh;

	return false;
}

static __inline void change_down_f32_init(change_down_f32_state *state, f32 arg,
    f32 delta, f32 filter)
{
	if (delta < 0)
		delta = 0;

	state->thresh = arg - delta;
}

/**
 * @overload bool change_down_immed_f32(change_down_immed_f32_state *state, f32 arg, f32 delta)
 */

typedef struct {
	f32 thresh;
} change_down_immed_f32_state;

static __inline __warn_unused_result bool change_down_immed_f32(change_down_immed_f32_state *state, f32 arg, f32 delta)
{
	if (delta < 0)
		delta = 0;

	if (arg < state->thresh) {
		state->thresh = arg - delta;
		return true;
	}

	const f32 new_thresh = arg - delta;
	if (new_thresh > state->thresh)
		state->thresh = new_thresh;

	return false;
}

static __inline void change_down_immed_f32_init(change_down_immed_f32_state *state, f32 arg,
    f32 delta)
{
	if (delta < 0)
		delta = 0;

	state->thresh = arg - delta;
}

/**
 * @fn bool change_by_s32(change_by_s32_state *state, s32 arg, s32 delta, f32 filter)
 * @arg ScriptName By
 * @arg initcall lib
 *
 * @brief Detect change by amount
 *
 * @details <p>True for one iteration after at least <span class="param"/>filter</span>
 * @details seconds from <span class="param"/>arg</span> becoming different to its
 * @details previous value by <span class="param"/>delta</span>.</p>
 * @details <p>At startup the initial value of <span class="param"/>arg</span> is latched.</p>
 *
 * @param state [provide]
 * @param arg value to detect changes on
 * @param delta delta by which <span class="param"/>arg</span> must change
 * @param filter filter time
 * @return true if change detected
 */

typedef struct {
	s32 prev;
	s32 expire;
	bool timing;
} change_by_s32_state;

static __inline __warn_unused_result bool change_by_s32(change_by_s32_state *state, s32 arg, s32 delta, f32 filter)
{
	if (delta < 1)
		delta = 1;

	if (__builtin_abs(arg - state->prev) >= delta) {
		const s32 now = ticks_u32();
		if (!state->timing) {
			/* start timer */
			if (filter < 0)
				filter = 0;
			state->expire = now + (s32)(filter / tick_period_f32());
			state->timing = true;
		}
		if ((now - state->expire) >= 0) {
			/* timer expired */
			state->prev = arg;
			state->timing = false;
			return true;
		}
		return false;
	}

	state->timing = false;
	return false;
}

static __inline void change_by_s32_init(change_by_s32_state *state, s32 arg, s32 delta,
    f32 filter)
{
	state->prev = arg;
}

/**
 * @overload bool change_by_immed_s32(change_by_immed_s32_state *state, s32 arg, s32 delta)
 */

typedef struct {
	s32 prev;
} change_by_immed_s32_state;

static __inline __warn_unused_result bool change_by_immed_s32(change_by_immed_s32_state *state, s32 arg, s32 delta)
{
	if (delta < 1)
		delta = 1;

	if (__builtin_abs(arg - state->prev) >= delta) {
		state->prev = arg;
		return true;
	}

	return false;
}

static __inline void change_by_immed_s32_init(change_by_immed_s32_state *state, s32 arg, s32 delta)
{
	state->prev = arg;
}

/**
 * @overload bool change_by_f32(change_by_f32_state *state, f32 arg, f32 delta, f32 filter)
 */

typedef struct {
	f32 prev;
	s32 expire;
	bool timing;
} change_by_f32_state;

static __inline __warn_unused_result bool change_by_f32(change_by_f32_state *state, f32 arg, f32 delta, f32 filter)
{
	if (delta < 0)
		delta = 0;

	if (__builtin_fabsf(arg - state->prev) > delta) {
		const s32 now = ticks_u32();
		if (!state->timing) {
			/* start timer */
			if (filter < 0)
				filter = 0;
			state->expire = now + (s32)(filter / tick_period_f32());
			state->timing = true;
		}
		if ((now - state->expire) >= 0) {
			/* timer expired */
			state->prev = arg;
			state->timing = false;
			return true;
		}
		return false;
	}

	state->timing = false;
	return false;
}

static __inline void change_by_f32_init(change_by_f32_state *state, f32 arg, f32 delta,
    f32 filter)
{
	state->prev = arg;
}

/**
 * @overload bool change_by_immed_f32(change_by_immed_f32_state *state, f32 arg, f32 delta)
 */

typedef struct {
	f32 prev;
} change_by_immed_f32_state;

static __inline __warn_unused_result bool change_by_immed_f32(change_by_immed_f32_state *state, f32 arg, f32 delta)
{
	if (delta < 0)
		delta = 0;

	if (__builtin_fabsf(arg - state->prev) > delta) {
		state->prev = arg;
		return true;
	}

	return false;
}

static __inline void change_by_immed_f32_init(change_by_immed_f32_state *state, f32 arg, f32 delta)
{
	state->prev = arg;
}

/**
 * @fn bool change_to(change_to_state *state, bool cond, f32 filter)
 * @arg ScriptName To
 * @arg initcall lib
 *
 * @brief Detect boolean change to true
 *
 * @details <p>True for one iteration after at least <span class="param"/>filter</span>
 * @details seconds from <span class="param"/>cond</span> becoming true.</p>
 * @details <p>At startup the initial value of <span class="param"/>cond</span> is latched.</p>
 *
 * @param state [provide]
 * @param cond logic condition to detect changes on
 * @param filter filter time
 * @return true if change detected
 */

typedef struct {
	bool prev;
	s32 expire;
	bool timing;
} change_to_state;

static __inline __warn_unused_result bool change_to(change_to_state *state, bool cond, f32 filter)
{
	const s32 now = ticks_u32();
	const bool edge = !state->prev && cond;
	state->prev = cond;

	if (edge) {
		/* detected rising edge, begin timing */
		if (filter < 0)
			filter = 0;
		state->expire = now + (s32)(filter / tick_period_f32());
		state->timing = true;
	}
	if (cond && state->timing && ((now - state->expire) >= 0)) {
		/* expired true for one cycle */
		state->timing = false;
		return true;
	}
	if (!cond) {
		/* low again, forget timeout */
		state->timing = false;
	}

	return false;
}

static __inline void change_to_init(change_to_state *state, bool cond, f32 filter)
{
	state->prev = cond;
}

/**
 * @overload bool change_to_immed(change_to_immed_state *state, bool cond)
 */

typedef struct {
	bool prev;
} change_to_immed_state;

static __inline __warn_unused_result bool change_to_immed(change_to_immed_state *state, bool cond)
{
	const bool edge = !state->prev && cond;
	state->prev = cond;

	return edge;
}

static __inline void change_to_immed_init(change_to_immed_state *state, bool cond)
{
	state->prev = cond;
}

/**
 * @fn bool change_from(change_from_state *state, bool cond, f32 filter)
 * @arg ScriptName From
 * @arg initcall lib
 *
 * @brief Detect boolean change from true
 *
 * @details <p>True for one iteration after at least <span class="param"/>filter</span>
 * @details seconds from <span class="param"/>cond</span> becoming false.</p>
 * @details <p>At startup the initial value of <span class="param"/>cond</span> is latched.</p>
 *
 * @param state [provide]
 * @param cond logic condition to detect changes on
 * @param filter filter time
 * @return true if change detected
 */

typedef struct {
	bool prev;
	s32 expire;
	bool timing;
} change_from_state;

static __inline __warn_unused_result bool change_from(change_from_state *state, bool cond, f32 filter)
{
	const s32 now = ticks_u32();
	const bool edge = state->prev && !cond;
	state->prev = cond;

	if (edge) {
		/* detected falling edge, begin timing */
		if (filter < 0)
			filter = 0;
		state->expire = now + (s32)(filter / tick_period_f32());
		state->timing = true;
	}
	if (!cond && state->timing && ((now - state->expire) >= 0)) {
		/* expired true for one cycle */
		state->timing = false;
		return true;
	}
	if (cond) {
		/* high again, forget timeout */
		state->timing = false;
	}

	return false;
}

static __inline void change_from_init(change_from_state *state, bool cond, f32 filter)
{
	state->prev = cond;
}

/**
 * @overload bool change_from_immed(change_from_immed_state *state, bool cond)
 */
typedef struct {
	bool prev;
} change_from_immed_state;

static __inline __warn_unused_result bool change_from_immed(change_from_immed_state *state, bool cond)
{
	const bool edge = state->prev && !cond;
	state->prev = cond;

	return edge;
}

static __inline void change_from_immed_init(change_from_immed_state *state, bool cond)
{
	state->prev = cond;
}

/**
 * @fn bool change_either(change_either_state *state, bool cond, f32 filter)
 * @arg ScriptName Either
 * @arg initcall lib
 *
 * @brief Detect boolean change
 *
 * @details <p>True for one iteration after at least <span class="param"/>filter</span>
 * @details seconds from <span class="param"/>cond</span> changing.</p>
 * @details <p>At startup the initial value of <span class="param"/>cond</span> is latched.</p>
 *
 * @param state [provide]
 * @param cond logic condition to detect changes on
 * @param filter filter time
 * @return true if change detected
 */

typedef struct {
	bool prev;
	s32 expire;
	bool timing;
} change_either_state;

static __inline __warn_unused_result bool change_either(change_either_state *state, bool cond, f32 filter)
{
	const s32 now = ticks_u32();
	const bool edge = state->prev != cond;
	state->prev = cond;

	if (edge) {
		/* detected an edge, begin timing */
		if (filter < 0)
			filter = 0;
		state->expire = now + (s32)(filter / tick_period_f32());
		state->timing = true;
	}
	if (state->timing && ((now - state->expire) >= 0)) {
		/* expired true for one cycle */
		state->timing = false;
		return true;
	}

	return false;
}

static __inline void change_either_init(change_either_state *state, bool cond, f32 filter)
{
	state->prev = cond;
}

/**
 * @overload bool change_either_immed(change_either_immed_state *state, bool cond)
 */

typedef struct {
	bool prev;
} change_either_immed_state;

static __inline __warn_unused_result bool change_either_immed(change_either_immed_state *state, bool cond)
{
	const bool edge = state->prev != cond;
	state->prev = cond;

	return edge;
}

static __inline void change_either_immed_init(change_either_immed_state *state, bool cond)
{
	state->prev = cond;
}

/** @} Change */

#endif // __ECU_CHANGE_H__
