#if !defined(_MATH_H)
#define _MATH_H

static __inline unsigned __FLOAT_BITS(float __f)
{
	union {float __f; unsigned __i;} __u;
	__u.__f = __f;
	return __u.__i;
}

#define isinf(x) ( (__FLOAT_BITS(x) & 0x7fffffff) == 0x7f800000)

#define isnan(x) ( (__FLOAT_BITS(x) & 0x7fffffff) > 0x7f800000)

#define isnormal(x) ( ((__FLOAT_BITS(x)+0x00800000) & 0x7fffffff) >= 0x01000000)

/*
 * infinite is actually 0x7f800000, but for BookE PPC SPE operationas
 * on NAN and infinite inputs the result is signed floating point
 * maximum.
 *
 * We now treat this as infinite too to help with error propogation.
 */
#define isfinite(x) ( (__FLOAT_BITS(x) & 0x7fffffff) < 0x7F7FFFFF)

#if !defined(ECU_BOARD)
#define ECU_BOARD
#define SYS_CLOCK 125000000
#define SYS_TICK_SHIFT 8
#endif
#include <ecu/types.h>

extern float tanhf(float);
extern float ceilf(float);
extern float fabsf(float);
extern float floorf(float);
extern float acosf(float);
extern float asinf(float);
extern float atanf(float);
extern float atan2f(float, float);
extern float coshf(float);
extern float sinhf(float);
extern float expf(float);
extern float logf(float);
extern float log10f(float);
extern float powf(float, float);
extern float fmodf(float, float);

extern float calculate_fsqrt(float);
extern float calculate_fsin(float);
extern float calculate_fcos(float);
extern float calculate_ftan(float);

#define RAD_2_DEGREE	57.29577951308232087684

#define floor(x) floorf(x)
#define ceil(x) ceilf(x)
#define fabs(x) __builtin_fabs(x)
#define sqrt(x) calculate_fsqrt(x)
#define fmod(x, y) __builtin_fmodf(x, y)
#define fmax(x, y) __builtin_fmaxf(x, y)
#define fmaxf(x, y) __builtin_fmaxf(x, y)
#define fmin(x, y) __builtin_fminf(x, y)
#define fminf(x, y) __builtin_fminf(x, y)
#define sinf(x) calculate_fsin(x*RAD_2_DEGREE)
#define sin(x) calculate_fsin(x*RAD_2_DEGREE)
#define cosf(x) calculate_fcos(x*RAD_2_DEGREE)
#define cos(x) calculate_fcos(x*RAD_2_DEGREE)
#define tanf(x) calculate_ftan(x*RAD_2_DEGREE)
#define tan(x) calculate_ftan(x*RAD_2_DEGREE)
#define asin(x) asinf(x)
#define acos(x) acosf(x)
#define atan(x) atanf(x)
#define atan2(x,y) atan2f(x,y)
#define pow(x, y) powf(x, y)
#define log(x) logf(x)
#define log10(x) log10f(x)
#define exp(x) expf(x)
#define sinh(x) sinhf(x)
#define cosh(x) coshf(x)
#define tanh(x) tanhf(x)

#endif
