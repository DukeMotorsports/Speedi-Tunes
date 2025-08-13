#if !defined(_MATH_H)
#define _MATH_H

#if !defined(ECU_BOARD)
#define ECU_BOARD
#define SYS_CLOCK 125000000
#define SYS_TICK_SHIFT 8
#endif
#include <ecu/types.h>
#include <ecu/calculate.h>

#define RAD_2_DEGREE	57.29577951308232087684
#define DEGREE_2_RAD	 0.01745329251994329576

inline static float floor(float x)
{
	return calculate_floor(x);
}

inline static float ceil(float x)
{
	return calculate_ceil(x);
}

inline static float fabs(float x)
{
	return calculate_absolute_f32(x);
}

inline static float sqrt(float x)
{
	return calculate_fsqrt(x);
}

inline static float fmod(float x, float y)
{
	return calculate_modulo_f32(x, y);
}


inline static float fmax(float x, float y)
{
	return calculate_max_f32(x, y);
}

inline static float fmaxf(float x, float y)
{
	return calculate_max_f32(x, y);
}

inline static float fmin(float x, float y)
{
	return calculate_min_f32(x, y);
}

inline static float fminf(float x, float y)
{
	return calculate_min_f32(x, y);
}

inline static float sin(float x)
{
	return calculate_fsin(x*RAD_2_DEGREE);
}

inline static float cos(float x)
{
	return calculate_fcos(x*RAD_2_DEGREE);
}

inline static float tan(float x)
{
	return calculate_ftan(x*RAD_2_DEGREE);
}

inline static float asin(float x)
{
	return calculate_asin(x)*DEGREE_2_RAD;
}

inline static float acos(float x)
{
	return calculate_acos(x)*DEGREE_2_RAD;
}

inline static float atan(float x)
{
	return calculate_atan(x)*DEGREE_2_RAD;
}

inline static float atan2(float x, float y)
{
	return calculate_atan2(x,y)*DEGREE_2_RAD;
}

inline static float pow(float x, float y)
{
	return calculate_power(x, y);
}

/*
	to be implemented
	log, log10, exp
	sinh, consh, tanh
*/
#endif
