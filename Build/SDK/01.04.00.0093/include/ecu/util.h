#ifndef __ECU_UTIL_H__
#define __ECU_UTIL_H__

#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))

#ifndef ctassert
#define ctassert(x) _Static_assert (x, #x)
#endif

#define __errordecl(name, msg) \
	void name (void) __attribute__((__error__ (msg)))

__errordecl(err_bad_index, "bad index");
__errordecl(err_bad_offset, "bad offset");
__errordecl(err_bad_length, "bad length");

#endif // __ECU_UTIL_H__
