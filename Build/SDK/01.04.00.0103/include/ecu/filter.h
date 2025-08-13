#ifndef __ECU_FILTER_H__
#define __ECU_FILTER_H__
#include <math.h>
#include <ecu/system.h>
#include <ecu/types.h>
#include <ecu/util.h>

/* Documentation concept is based on the easiest easy to parse version
 * of doxygen with some minor extensions.
 *
 * Undocumented parameters are to be hidden from the user. The only
 * valid undocumented parameters are 'state' and 'cfg' - they are
 * structs of type $(fn)_state and $(fn)_cfg that are to be allocated
 * by setup
 */

/**
 * @addtogroup Filter
 * @{
 */

/**
 * @fn f32 filter_firstorder_reset_f32(filter_firstorder_reset_f32_state *state, f32 arg, f32 tc, bool reset)
 * @arg ScriptName FirstOrder
 * @arg initcall lib
 *
 * @brief First order filter
 *
 * @details <p>First order digital filter of the form</p>
 * @details <dl><dd>y[n] = a0 * x[n] + b1 * y[n - 1],</dd></dl>
 * @details <p>where the filter coefficients a0 and b1 are calculated such that
 * @details the filter has the time constant <span class="param"/>tc</span>
 * @details (a0 = dT/(tc+dT); b1 = 1 - a0; where dT is 1/<i>f<sub>s</sub></i>
 * @details with <i>f<sub>s</sub></i> being the sample rate in Hz).</p>
 *
 * @details <p>The range of time constants depends on the sample rate of the filter.
 * @details Recommended time constants fall in the range
 * @details (1/<i>f<sub>s</sub></i>, 1/<i>f<sub>s</sub></i> * 100]
 * @details seconds.
 * @details There is no upper limit on <span class="param"/>tc</span>,
 * @details but calculation accuracy may be reduced for excessively large values.</p>
 *
 * @details <p>If <span class="param"/>tc</span> is less than or equal
 * @details to 1/<i>f<sub>s</sub></i> the filter will have no effect.</p>
 *
 * @details <p>The filter's characteristics should not change if its sample
 * @details rate is changed unless the limits described above are encountered.</p>
 *
 * @param state [provide]
 * @param arg value to filter
 * @param tc filter time constant (seconds)
 * @param reset reinitialise filter state with current value of arg
 *
 * @return filtered value
 */

typedef struct {
	f32 y1;
	elapsed_time_f32_state ets;
} filter_firstorder_reset_f32_state;

static __inline __warn_unused_result f32 filter_firstorder_reset_f32(filter_firstorder_reset_f32_state *state, f32 arg, f32 tc, bool reset)
{
	if (!isfinite(arg))
		return state->y1 = __builtin_nan("0"); /* NAN or infinite (including FLOATMAX) */

	if (reset || !isfinite(state->y1)) {
		elapsed_time_f32_init(&state->ets);
		return state->y1 = arg;
	}

	const f32 dt = elapsed_time_f32(&state->ets);

	/* y[n] = a0 * x[n] + b1 * y[n - 1] */
	f32 a0 = dt / (tc + dt);
	if (a0 > 1)
		a0 = 1;
	const f32 b1 = 1 - a0;
	return state->y1 = (a0 * arg) + (b1 * state->y1);
}

static __inline void filter_firstorder_reset_f32_init(filter_firstorder_reset_f32_state *state,
    f32 arg, f32 tc, bool reset)
{
	state->y1 = arg;
	elapsed_time_f32_init(&state->ets);
}

/**
 * @overload f32 filter_firstorder_f32(filter_firstorder_f32_state *state, f32 arg, f32 tc)
 */

typedef filter_firstorder_reset_f32_state filter_firstorder_f32_state;

static __inline __warn_unused_result f32 filter_firstorder_f32(filter_firstorder_f32_state *state, f32 arg, f32 tc)
{
	return filter_firstorder_reset_f32(state, arg, tc, false);
}

static __inline void filter_firstorder_f32_init(filter_firstorder_f32_state *state,
    f32 arg, f32 tc)
{
	filter_firstorder_reset_f32_init(state, arg, tc, false);
}

/**
 * @fn f32 filter_max_reset_f32(filter_max_reset_f32_state *state, f32 arg, f32 tc, bool reset)
 * @arg ScriptName Maximum
 * @arg initcall lib
 *
 * @brief Maximum tracking filter
 *
 * @details <p>Tracks the maximum and filters towards the current value of
 * @details <span class="param"/>arg</span> with a first order digital filter of the form</p>
 * @details <dl><dd>y[n] = a0 * x[n] + b1 * y[n - 1],</dl></dd>
 * @details <p>where the filter coefficients a0 and b1 are calculated such that
 * @details the filter has the time constant <span class="param"/>tc</span>
 * @details (a0 = dT/(tc+dT); b1 = 1 - a0; where dT is 1/<i>f<sub>s</sub></i>
 * @details with <i>f<sub>s</sub></i> being the sample rate in Hz).</p>
 * @details <p>The filter will be reset each time <span class="param"/>reset</span> is true or
 * @details <span class="param"/>arg</span> is greater than the current filter value.</p>
 *
 * @details <p>The range of time constants depends on the sample rate of the filter.
 * @details Recommended time constants fall in the range
 * @details (1/<i>f<sub>s</sub></i>, 1/<i>f<sub>s</sub></i> * 100]
 * @details seconds.
 * @details There is no upper limit on <span class="param"/>tc</span>,
 * @details but calculation accuracy may be reduced for excessively large values.</p>
 *
 * @details <p>If <span class="param"/>tc</span> is less than or equal
 * @details to 1/<i>f<sub>s</sub></i> the filter will have no effect.</p>
 *
 * @details <p>The filter's characteristics should not change if its sample
 * @details rate is changed unless the limits described above are encountered.</p>
 *
 * @param state [provide]
 * @param arg value to filter
 * @param tc filter time constant (seconds)
 * @param reset reinitialise filter state with current value of arg
 *
 * @return filtered value
 */

typedef struct {
	f32 y1;
	elapsed_time_f32_state ets;
} filter_max_reset_f32_state;

static __inline __warn_unused_result f32 filter_max_reset_f32(filter_max_reset_f32_state *state, f32 arg, f32 tc, bool reset)
{
	if (!isfinite(arg))
		return state->y1 = __builtin_nan("0"); /* NAN or infinite (including FLOATMAX) */

	if (reset || state->y1 < arg || !isfinite(state->y1)) {
		elapsed_time_f32_init(&state->ets);
		return state->y1 = arg;
	}

	const f32 dt = elapsed_time_f32(&state->ets);

	/* y[n] = a0 * x[n] + b1 * y[n - 1] */
	f32 a0 = dt / (tc + dt);
	if (a0 > 1)
		a0 = 1;
	const f32 b1 = 1 - a0;
	return state->y1 = (a0 * arg) + (b1 * state->y1);
}

static __inline void filter_max_reset_f32_init(filter_max_reset_f32_state *state,
    f32 arg, f32 tc, bool reset)
{
	state->y1 = arg;
	elapsed_time_f32_init(&state->ets);
}

/**
 * @overload f32 filter_max_f32(filter_max_f32_state *state, f32 arg, f32 tc)
 */

typedef filter_max_reset_f32_state filter_max_f32_state;

static __inline __warn_unused_result f32 filter_max_f32(filter_max_f32_state *state, f32 arg, f32 tc)
{
	return filter_max_reset_f32(state, arg, tc, false);
}

static __inline void filter_max_f32_init(filter_max_f32_state *state,
    f32 arg, f32 tc)
{
	filter_max_reset_f32_init(state, arg, tc, false);
}

/**
 * @fn f32 filter_min_reset_f32(filter_min_reset_f32_state *state, f32 arg, f32 tc, bool reset)
 * @arg ScriptName Minimum
 * @arg initcall lib
 *
 * @brief Minimum tracking filter
 *
 * @details <p>Tracks the minimum and filters towards the current value of
 * @details <span class="param"/>arg</span> with a first order digital filter of the form</p>
 * @details <dl><dd>y[n] = a0 * x[n] + b1 * y[n - 1],</dl></dd>
 * @details <p>where the filter coefficients a0 and b1 are calculated such that
 * @details the filter has the time constant <span class="param"/>tc</span>
 * @details (a0 = dT/(tc+dT); b1 = 1 - a0; where dT is 1/<i>f<sub>s</sub></i>
 * @details with <i>f<sub>s</sub></i> being the sample rate in Hz).</p>
 * @details <p>The filter will be reset each time <span class="param"/>reset</span> is true or
 * @details <span class="param"/>arg</span> is smaller than the current filter value.</p>
 *
 * @details <p>The range of time constants depends on the sample rate of the filter.
 * @details Recommended time constants fall in the range
 * @details (1/<i>f<sub>s</sub></i>, 1/<i>f<sub>s</sub></i> * 100]
 * @details seconds.
 * @details There is no upper limit on <span class="param"/>tc</span>,
 * @details but calculation accuracy may be reduced for excessively large values.</p>
 *
 * @details <p>If <span class="param"/>tc</span> is less than or equal
 * @details to 1/<i>f<sub>s</sub></i> the filter will have no effect.</p>
 *
 * @details <p>The filter's characteristics should not change if its sample
 * @details rate is changed unless the limits described above are encountered.</p>
 *
 * @param state [provide]
 * @param arg value to filter
 * @param tc filter time constant (seconds)
 * @param reset reinitialise filter state with current value of arg
 *
 * @return filtered value
 */

typedef struct {
	f32 y1;
	elapsed_time_f32_state ets;
} filter_min_reset_f32_state;

static __inline __warn_unused_result f32 filter_min_reset_f32(filter_min_reset_f32_state *state, f32 arg, f32 tc, bool reset)
{
	if (!isfinite(arg))
		return state->y1 = __builtin_nan("0"); /* NAN or infinite (including FLOATMAX) */

	if (reset || state->y1 > arg || !isfinite(state->y1)) {
		elapsed_time_f32_init(&state->ets);
		return state->y1 = arg;
	}

	const f32 dt = elapsed_time_f32(&state->ets);

	/* y[n] = a0 * x[n] + b1 * y[n - 1] */
	f32 a0 = dt / (tc + dt);
	if (a0 > 1)
		a0 = 1;
	const f32 b1 = 1 - a0;
	return state->y1 = (a0 * arg) + (b1 * state->y1);
}

static __inline void filter_min_reset_f32_init(filter_min_reset_f32_state *state,
    f32 arg, f32 tc, bool reset)
{
	state->y1 = arg;
	elapsed_time_f32_init(&state->ets);
}

/**
 * @overload f32 filter_min_f32(filter_min_f32_state *state, f32 arg, f32 tc)
 */

typedef filter_min_reset_f32_state filter_min_f32_state;

static __inline __warn_unused_result f32 filter_min_f32(filter_min_f32_state *state, f32 arg, f32 tc)
{
	return filter_min_reset_f32(state, arg, tc, false);
}

static __inline void filter_min_f32_init(filter_min_f32_state *state,
    f32 arg, f32 tc)
{
	filter_min_reset_f32_init(state, arg, tc, false);
}

/** @} Filter */

#endif /* __ECU_FILTER_H__ */
