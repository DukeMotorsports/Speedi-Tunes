#ifndef __ECU_CALCULATE_H__
#define __ECU_CALCULATE_H__

#include <math.h>
#include <ecu/types.h>
#include <ecu/system.h>

/**
 * @addtogroup Calculate
 * @{
 */

/**
 * @fn bool calculate_hysteresis_s32(calculate_hysteresis_s32_state *state, s32 arg, s32 low, s32 high, f32 filter)
 * @arg ScriptName Hysteresis
 * @arg initcall lib
 *
 * @brief Filtered hysteresis calculation
 *
 * @details <p>True when <span class="param"/>arg</span> >=
 * @details <span class="param"/>high</span> for at least
 * @details <span class="param"/>filter</span> seconds. False when
 * @details <span class="param"/>arg</span> <= <span class="param"/>low</span>
 * @details for at least <span class="param"/>filter</span> seconds.</p>
 *
 * @param state [provide]
 * @param arg input argument
 * @param high high level
 * @param low low level
 * @param filter filter time
 * @return filtered hysteresis value
 */

typedef struct {
	bool latch;
	bool timing;
	s32 expire;
} calculate_hysteresis_s32_state;

static __inline __warn_unused_result bool calculate_hysteresis_s32(calculate_hysteresis_s32_state *state, s32 arg, s32 low, s32 high, f32 filter)
{
	if (arg >= high) {
		if (!state->latch) {
			/* transitioning to high, process time */
			const s32 now = ticks_u32();
			if (!state->timing) {
				/* start timer */
				if (filter < 0)
					filter = 0;
				state->expire = now + (s32)(filter / tick_period_f32());
				state->timing = true;
			}
			if ((now - state->expire) >= 0) {
				/* timer expired, latch state */
				state->latch = true;
				state->timing = false;
			}
			return state->latch;
		}
	} else if (arg <= low) {
		if (state->latch) {
			/* transitioning to low, process time */
			const s32 now = ticks_u32();
			if (!state->timing) {
				/* start timer */
				if (filter < 0)
					filter = 0;
				state->expire = now + (s32)(filter / tick_period_f32());
				state->timing = true;
			}
			if ((now - state->expire) >= 0) {
				/* timer expired, latch state */
				state->latch = false;
				state->timing = false;
			}
			return state->latch;
		}
	}

	state->timing = false;
	return state->latch;
}

static __inline void calculate_hysteresis_s32_init(calculate_hysteresis_s32_state *state,
    s32 arg, s32 low, s32 high, f32 filter)
{
	state->latch = arg >= high;
}

/**
 * @overload bool calculate_hysteresis_f32(calculate_hysteresis_f32_state *state, f32 arg, f32 min, f32 max, f32 filter)
 */

typedef struct {
	bool latch;
	bool timing;
	s32 expire;
} calculate_hysteresis_f32_state;

static __inline __warn_unused_result bool calculate_hysteresis_f32(calculate_hysteresis_f32_state *state, f32 arg, f32 low, f32 high, f32 filter)
{
	if (arg >= high) {
		if (!state->latch) {
			/* transitioning to high, process time */
			const s32 now = ticks_u32();
			if (!state->timing) {
				/* start timer */
				if (filter < 0)
					filter = 0;
				state->expire = now + (s32)(filter / tick_period_f32());
				state->timing = true;
			}
			if ((now - state->expire) >= 0) {
				/* timer expired, latch state */
				state->latch = true;
				state->timing = false;
			}
			return state->latch;
		}
	} else if (arg <= low) {
		if (state->latch) {
			/* transitioning to low, process time */
			const s32 now = ticks_u32();
			if (!state->timing) {
				/* start timer */
				if (filter < 0)
					filter = 0;
				state->expire = now + (s32)(filter / tick_period_f32());
				state->timing = true;
			}
			if ((now - state->expire) >= 0) {
				/* timer expired, latch state */
				state->latch = false;
				state->timing = false;
			}
			return state->latch;
		}
	}

	state->timing = false;
	return state->latch;
}

static __inline void calculate_hysteresis_f32_init(calculate_hysteresis_f32_state *state,
    f32 arg, f32 low, f32 high, f32 filter)
{
	state->latch = arg >= high;
}

/**
 * @fn bool calculate_between_s32(calculate_between_s32_state *state, s32 arg, s32 min, s32 max, f32 filter)
 * @arg ScriptName Between
 * @arg initcall lib
 *
 * @brief Filtered inside range test
 *
 * @details <p>True when <span class="param"/>arg</span> within range
 * @details [<span class="param"/>min</span>, <span class="param"/>max</span>]
 * @details for at least <span class="param"/>filter</span> seconds.</p>
 *
 * @param state [provide]
 * @param arg input argument
 * @param min minimum value
 * @param max maximum value
 * @param filter filter time
 * @return filtered inside range test
 */

typedef struct {
	bool latch;
	bool timing;
	s32 expire;
} calculate_between_s32_state;

static __inline __warn_unused_result bool calculate_between_s32(calculate_between_s32_state *state, s32 arg, s32 min, s32 max, f32 filter)
{
	if ((arg >= min) && (arg <= max)) {
		/* inside range */
		if (!state->latch) {
			const s32 now = ticks_u32();
			if (!state->timing) {
				/* start timer */
				if (filter < 0)
					filter = 0;
				state->expire = now + (s32)(filter / tick_period_f32());
				state->timing = true;
			}
			if ((now - state->expire) >= 0) {
				/* timer expired, latch state */
				state->latch = true;
				state->timing = false;
			}
		}
	} else {
		/* outside range */
		state->latch = false;
		state->timing = false;
	}

	return state->latch;
}

static __inline void calculate_between_s32_init(calculate_between_s32_state *state,
    s32 arg, s32 min, s32 max, f32 filter)
{
	state->latch = (arg >= min) && (arg <= max);
}

/**
 * @overload bool calculate_between_f32(calculate_between_f32_state *state, f32 arg, f32 min, f32 max, f32 filter)
 */

typedef struct {
	bool latch;
	bool timing;
	s32 expire;
} calculate_between_f32_state;

static __inline __warn_unused_result bool calculate_between_f32(calculate_between_f32_state *state, f32 arg, f32 min, f32 max, f32 filter)
{
	if ((arg >= min) && (arg <= max)) {
		/* inside range */
		if (!state->latch) {
			const s32 now = ticks_u32();
			if (!state->timing) {
				/* start timer */
				if (filter < 0)
					filter = 0;
				state->expire = now + (s32)(filter / tick_period_f32());
				state->timing = true;
			}
			if ((now - state->expire) >= 0) {
				/* timer expired, latch state */
				state->latch = true;
				state->timing = false;
			}
		}
	} else {
		/* outside range */
		state->latch = false;
		state->timing = false;
	}

	return state->latch;
}

static __inline void calculate_between_f32_init(calculate_between_f32_state *state,
    f32 arg, f32 min, f32 max, f32 filter)
{
	state->latch = (arg >= min) && (arg <= max);
}

/**
 * @fn bool calculate_beyond_s32(calculate_beyond_s32_state *state, s32 arg, s32 min, s32 max, f32 filter)
 * @arg ScriptName Beyond
 * @arg initcall lib
 *
 * @brief Filtered outside range test
 *
 * @details <p>True when <span class="param"/>arg</span> outside range
 * @details [<span class="param"/>min</span>, <span class="param"/>max</span>]
 * @details for at least <span class="param"/>filter</span> seconds.</p>
 *
 * @param state [provide]
 * @param arg input argument
 * @param min minimum value
 * @param max maximum value
 * @param filter filter time
 * @return filtered outside range test
 */

typedef struct {
	bool latch;
	bool timing;
	s32 expire;
} calculate_beyond_s32_state;

static __inline __warn_unused_result bool calculate_beyond_s32(calculate_beyond_s32_state *state, s32 arg, s32 min, s32 max, f32 filter)
{
	if ((arg < min) || (arg > max)) {
		/* outside range */
		if (!state->latch) {
			const s32 now = ticks_u32();
			if (!state->timing) {
				/* start timer */
				if (filter < 0)
					filter = 0;
				state->expire = now + (s32)(filter / tick_period_f32());
				state->timing = true;
				state->timing = false;
			}
			if ((now - state->expire) >= 0) {
				/* timer expired, latch state */
				state->latch = true;
				state->timing = false;
			}
		}
	} else {
		/* inside range */
		state->latch = false;
		state->timing = false;
	}

	return state->latch;
}

static __inline void calculate_beyond_s32_init(calculate_beyond_s32_state *state,
    s32 arg, s32 min, s32 max, f32 filter)
{
	state->latch = (arg < min) || (arg > max);
}

/**
 * @overload bool calculate_beyond_f32(calculate_beyond_f32_state *state, f32 arg, f32 min, f32 max, f32 filter)
 */

typedef struct {
	bool latch;
	bool timing;
	s32 expire;
} calculate_beyond_f32_state;

static __inline __warn_unused_result bool calculate_beyond_f32(calculate_beyond_f32_state *state, f32 arg, f32 min, f32 max, f32 filter)
{
	if ((arg < min) || (arg > max)) {
		/* outside range */
		if (!state->latch) {
			const s32 now = ticks_u32();
			if (!state->timing) {
				/* start timer */
				if (filter < 0)
					filter = 0;
				state->expire = now + (s32)(filter / tick_period_f32());
				state->timing = true;
			}
			if ((now - state->expire) >= 0) {
				/* timer expired, latch state */
				state->latch = true;
				state->timing = false;
			}
		}
	} else {
		/* inside range */
		state->latch = false;
		state->timing = false;
	}

	return state->latch;
}

static __inline void calculate_beyond_f32_init(calculate_beyond_f32_state *state,
    f32 arg, f32 min, f32 max, f32 filter)
{
	state->latch = (arg < min) || (arg > max);
}

/**
 * @fn bool calculate_stable_s32(calculate_stable_s32_state *state, s32 arg, f32 filter)
 * @arg ScriptName Stable
 * @arg initcall lib
 *
 * @brief Stability test
 *
 * @details <p>Returns true when <span class="param"/>arg</span> has not changed
 * @details for at least <span class="param"/>filter</span> seconds.</p>
 *
 * @param state [provide]
 * @param arg input argument
 * @param filter filter time
 * @return true when <span class="param"/>arg</span> is stable
 */

typedef struct {
	bool timing;
	s32 expire;
	s32 prev;
} calculate_stable_s32_state;

static __inline __warn_unused_result bool calculate_stable_s32(calculate_stable_s32_state *state, s32 arg, f32 filter)
{
	const s32 now = ticks_u32();
	const bool change = arg != state->prev;
	state->prev = arg;
	if (change) {
		/* start timer */
		if (filter < 0)
			filter = 0;
		state->expire = now + (s32)(filter / tick_period_f32());
		state->timing = true;
	}
	if (state->timing && ((now - state->expire) >= 0))
		state->timing = false;
	return !state->timing;
}

static __inline void calculate_stable_s32_init(calculate_stable_s32_state *state, s32 arg, f32 filter)
{
	const s32 now = ticks_u32();
	state->timing = true;
	state->expire = now + (s32)(filter / tick_period_f32());
	state->prev = arg;
}

/**
 * @fn s32 calculate_min_s32(s32 a, s32 b)
 * @arg ScriptName Min
 *
 * @brief Return the lesser of two arguments
 *
 * @details <p>Returns the lesser of <span class="param"/>a</span> and
 * @details <span class="param"/>b</span>.</p>
 *
 * @param a first input argument
 * @param b second input argument
 * @return lesser of <span class="param"/>a</span> and <span class="param"/>b</span>
 */

static __inline __warn_unused_result s32 calculate_min_s32(s32 a, s32 b)
{
	return (a < b) ? a : b;
}

/**
 * @overload f32 calculate_min_f32(f32 a, f32 b)
 */

static __inline __warn_unused_result f32 calculate_min_f32(f32 a, f32 b)
{
	return (a < b) ? a : b;
}

/**
 * @fn s32 calculate_max_s32(s32 a, s32 b)
 * @arg ScriptName Max
 *
 * @brief Return the greater of two arguments
 *
 * @details <p>Returns the greater of <span class="param"/>a</span> and
 * @details <span class="param"/>b</span>.</p>
 *
 * @param a first input argument
 * @param b second input argument
 * @return greater of <span class="param"/>a</span> and <span class="param"/>b</span>
 */

static __inline __warn_unused_result s32 calculate_max_s32(s32 a, s32 b)
{
	return (a > b) ? a : b;
}

/**
 * @overload f32 calculate_max_f32(f32 a, f32 b)
 */

static __inline __warn_unused_result f32 calculate_max_f32(f32 a, f32 b)
{
	return (a > b) ? a : b;
}

/**
 * @fn s32 calculate_average_s32(s32 a, s32 b)
 * @arg ScriptName Average
 *
 * @brief Compute average of two arguments
 *
 * @details <p>Returns the average of <span class="param"/>a</span> and
 * @details <span class="param"/>b</span>.</p>
 *
 * @param a first input argument
 * @param b second input argument
 * @return average of <span class="param"/>a</span> and <span class="param"/>b</span>
 */

static __inline __warn_unused_result s32 calculate_average_s32(s32 a, s32 b)
{
	return (a + b) / 2;
}

/**
 * @overload f32 calculate_average_f32(f32 a, f32 b)
 */

static __inline __warn_unused_result f32 calculate_average_f32(f32 a, f32 b)
{
	return (a + b) / 2;
}

/**
 * @fn s32 calculate_absolute_s32(s32 arg)
 * @arg ScriptName Absolute
 *
 * @brief Compute absolute value of argument
 *
 * @details <p>Returns the absolute value of <span class="param"/>arg</span>.</p>
 *
 * @param arg input argument
 * @return absolute value of <span class="param"/>arg</span>
 */

static __inline __warn_unused_result s32 calculate_absolute_s32(s32 arg)
{
	return __builtin_abs(arg);
}

/**
 * @overload f32 calculate_absolute_f32(f32 arg)
 */

static __inline __warn_unused_result f32 calculate_absolute_f32(f32 arg)
{
	return __builtin_fabsf(arg);
}

/**
 * @fn s32 calculate_modulo_s32(s32 arg, s32 denom)
 * @arg ScriptName Modulo
 *
 * @brief Compute remainder of division
 *
 * @details <p>Returns the remainder of
 * @details <span class="param"/>arg</span>/<span class="param"/>denom</span>.</p>
 * @details <p>The remainder of a division operation is the result of subtracting
 * @details the integral quotient multiplied by the denominator from the numerator:</p>
 * @details <dl><dd>remainder = numerator - (quotient * denominator)</dd></dl>
 *
 * @param arg input argument
 * @param denom denominator
 * @return remainder of <span class="param"/>arg</span>/<span class="param"/>denom</span>
 */

static __inline __warn_unused_result s32 calculate_modulo_s32(s32 arg, s32 denom)
{
	return (arg % denom);
}

/**
 * @overload f32 calculate_modulo_f32(f32 arg, f32 denom)
 */

static __inline __warn_unused_result f32 calculate_modulo_f32(f32 arg, f32 denom)
{
	if (!isfinite(arg) || isnan(denom) || denom == 0) /* conforming to C99 */
		return __builtin_nan("0");

	const int i = arg / denom;
	return arg - i * denom;
}

/**
 * @fn s32 calculate_bias_s32(s32 a, s32 b, f32 bias)
 * @arg ScriptName Bias
 *
 * @brief Compute biased average of two arguments
 *
 * @details <p>Returns the biased average of <span class="param"/>a</span> and
 * @details <span class="param"/>b</span>. The calculation can be adjusted by changing
 * @details <span class="param"/>bias</span>:</p>
 * @details <table class=param>
 * @details <tr><th>bias</th><th>Return Value</th></tr>
 * @details <tr><td>-1</td><td>minimum of <span class="param"/>a</span> and <span class="param"/>b</span></td></tr>
 * @details <tr><td>0</td><td>true average of <span class="param"/>a</span> and <span class="param"/>b</span></td></tr>
 * @details <tr><td>1</td><td>maximum of <span class="param"/>a</span> and <span class="param"/>b</span></td></tr>
 * @details </table>
 *
 * @param a first input argument
 * @param b second input argument
 * @param bias controls average calculation
 * @return biased average of average of <span class="param"/>a</span> and <span class="param"/>b</span>
 */

static __inline __warn_unused_result s32 calculate_bias_s32(s32 a, s32 b, f32 bias)
{
	if (bias > 1)
		bias = 1;
	if (bias < -1)
		bias = -1;

	if (a > b)
		return (((a * (1 + bias)) + (b * (1 - bias))) / 2) + 0.5;
	else
		return (((b * (1 + bias)) + (a * (1 - bias))) / 2) + 0.5;
}

/**
 * @overload f32 calculate_bias_f32(f32 a, f32 b, f32 bias)
 */

static __inline __warn_unused_result f32 calculate_bias_f32(f32 a, f32 b, f32 bias)
{
	if (bias > 1)
		bias = 1;
	if (bias < -1)
		bias = -1;

	if (a > b)
		return ((a * (1 + bias)) + (b * (1 - bias))) / 2;
	else
		return ((b * (1 + bias)) + (a * (1 - bias))) / 2;
}

/**
 * @fn f32 calculate_fsqrt(f32 arg)
 * @arg ScriptName FastSquareRoot
 *
 * @brief Calculate approximate square root
 *
 * @details <p>This function calculates the approximate square root of
 * @details <span class="param"/>arg</span> with a maximum relative error of about
 * @details 0.0013%.</p>
 *
 * @param arg input argument
 * @return square root of <span class="param"/>arg</span>
 */

__warn_unused_result f32 calculate_fsqrt(f32 arg);

/**
 * @fn f32 calculate_fsin(f32 arg)
 * @arg ScriptName FastSin
 *
 * @brief Calculate approximate sine
 *
 * @details <p>This function calculates the approximate sine of
 * @details <span class="param"/>arg</span> with a maximum relative error of about
 * @details 0.5%.</p>
 *
 * @param arg input argument
 * @return sine of <span class="param"/>arg</span>
 */

__warn_unused_result f32 calculate_fsin(f32 arg);

/**
 * @fn f32 calculate_fcos(f32 arg)
 * @arg ScriptName FastCos
 *
 * @brief Calculate approximate cosine
 *
 * @details <p>This function calculates the approximate cosine of
 * @details <span class="param"/>arg</span> with a maximum relative error of about
 * @details 0.5%.</p>
 *
 * @param arg input argument
 * @return cosine of <span class="param"/>arg</span>
 */

__warn_unused_result f32 calculate_fcos(f32 arg);

/**
 * @fn f32 calculate_ftan(f32 arg)
 * @arg ScriptName FastTan
 *
 * @brief Calculate approximate tangent
 *
 * @details <p>This function calculates the approximate tangent of
 * @details <span class="param"/>arg</span> with a maximum relative error of about
 * @details 0.5%.</p>
 *
 * @param arg input argument
 * @return tangent of <span class="param"/>arg</span>
 */

__warn_unused_result f32 calculate_ftan(f32 arg);

/**
 * @fn f32 calculate_asin(f32 arg)
 * @arg ScriptName InverseSin
 *
 * @brief Calculate inverse sine
 *
 * @param arg input argument
 * @return inverse sine of <span class="param"/>arg</span>
 */

__warn_unused_result f32 calculate_asin(f32 arg);

/**
 * @fn f32 calculate_acos(f32 arg)
 * @arg ScriptName InverseCos
 *
 * @brief Calculate inverse cosine
 *
 * @param arg input argument
 * @return inverse cosine of <span class="param"/>arg</span>
 */

__warn_unused_result f32 calculate_acos(f32 arg);

/**
 * @fn f32 calculate_atan(f32 arg)
 * @arg ScriptName InverseTan
 *
 * @brief Calculate inverse tangent
 *
 * @param arg input argument
 * @return inverse tangent of <span class="param"/>arg</span>
 */

__warn_unused_result f32 calculate_atan(f32 arg);

/**
 * @fn f32 calculate_atan2(f32 y, f32 x)
 * @arg ScriptName InverseTan2
 *
 * @brief Calculate inverse tangent including quadrant
 *
 * @param y y input argument
 * @param x x input argument
 * @return inverse tangent of <span class="param"/>y</span>/<span class="param"/>x</span>
 */

__warn_unused_result f32 calculate_atan2(f32 y, f32 x);

/**
 * @fn f32 calculate_floor(f32 arg)
 * @arg ScriptName Floor
 *
 * @brief Calculate floor
 *
 * @details <p>This function rounds <span class="param"/>arg</span> to
 * @details the next closest integral value towards -inf.
 *
 * @param arg input argument
 * @return floor of <span class="param"/>arg</span>
 */

__warn_unused_result f32 calculate_floor(f32 arg);

/**
 * @fn f32 calculate_ceil(f32 arg)
 * @arg ScriptName Ceiling
 *
 * @brief Calculate ceiling
 *
 * @details <p>This function rounds <span class="param"/>arg</span> to
 * @details the next closest integral value towards +inf.
 *
 * @param arg input argument
 * @return ceiling of <span class="param"/>arg</span>
 */

__warn_unused_result f32 calculate_ceil(f32 arg);

/**
 * @fn f32 calculate_pi()
 * @arg ScriptName PI
 *
 * @brief Return the value of the constant PI
 *
 * @return the value of PI
 */

static __inline __warn_unused_result f32 calculate_pi(void)
{
	return 3.14159265358979323846;
}

/**
 * @fn f32 calculate_power(f32 x, f32 y)
 * @arg ScriptName Power
 *
 * @brief Calculate x to the power of y
 *
 * @param x x input argument
 * @param y y input argument
 * @return x to the power of y
 */

__warn_unused_result f32 calculate_power(f32 x, f32 y);

/**
 * @fn f32 calculate_nan()
 * @arg ScriptName NAN
 *
 * @brief Return a value that represents "not a number"
 *
 * @return Not a number
 */

static __inline __warn_unused_result f32 calculate_nan(void)
{
	return __builtin_nan("0");
}

/**
 * @fn f32 calculate_inf()
 * @arg ScriptName Infinity
 *
 * @brief Return a value that represents positive infinity
 *
 * @return Infinity
 */

static __inline __warn_unused_result f32 calculate_inf(void)
{
	return __builtin_inff();
}

/**
 * @fn f32 calculate_fltmax()
 * @arg ScriptName MaximumFloat
 *
 * @brief Return the maximum floating point value
 *
 * @return Maximum floating point value
 */
static __inline __warn_unused_result f32 calculate_fltmax(void)
{
	return __FLT_MAX__;
}

/**
 * @fn bool calculate_isnan(f32 arg)
 * @arg ScriptName IsNAN
 *
 * @brief Test whether <span class="param">arg</span> is "Not a Number"
 *
 * @param arg input argument
 * @return True if <span class="param">arg</span> is "Not a Number"
 */
static __inline __warn_unused_result bool calculate_isnan(f32 arg)
{
	return isnan(arg);
}

/**
 * @fn bool calculate_isfinite(f32 arg)
 * @arg ScriptName IsFinite
 *
 * @brief Test whether <span class="param">arg</span> is neither "Not a Number" or infinity
 *
 * @param arg input argument
 * @return True if <span class="param">arg</span> is a finite value
 */
static __inline __warn_unused_result bool calculate_isfinite(f32 arg)
{
	return isfinite(arg);
}

/** @} Calculate */

#endif // __ECU_CALCULATE_H__
