#ifndef __VERBOSE_H__
#define __VERBOSE_H__
#if defined( __BOOT__)
#include <boot.h>
#elif defined (__DRIVER__)
#include <driver.h>
#elif defined (__KERNEL__)
#include <sys/debug.h>
#else
#include <sys/syslog.h>
#endif
#include <sys/types.h>

/* debug string handling */
#define VERBOSE_MAP(F) /* non-additive args first */	\
	F(VB_ALL,	0x7fffffff, "all",	0,	\
	  "ALL available debug output")                 \
	F(VB_NONE,	0x00000000, "none",	0,	\
	  "NO debug output")				\
	F(VB_CRIT,	0x00000001, "crit",	0,      \
	  "Errors or other critical messages")          \
	F(VB_INFO,	0x00000002, "info",	1,	\
	  "General information")                        \
	F(VB_DEBUG,	0x00000004, "debug",	1,	\
	  "Debugging information")                      \
	F(VB_MORE,	0x00000008, "more",	1,	\
	  "More information or debug")			\
	F(VB_TRACE,	0x00000010, "trace",	1,	\
	  "Extra Program flow messages")		\
	F(VB_CAN,	0x00000100, "can",	1,      \
	  "Can subsystem messages")			\
	F(VB_ETH,	0x00000200, "eth",	1,      \
	  "Ethernet subsystem messages")		\
	F(VB_XCP,	0x00000400, "xcp",	1,      \
	  "XCP subsystem messages")			\
	F(VB_OUT,	0x00000800, "output",	1,      \
	  "OUTPUT subsystem messages")			\
	F(VB_ADC,	0x00001000, "analog",	1,      \
	  "anaolg subsystem messages")			\
	F(VB_DMA,	0x00002000, "dma",	1,      \
	  "dma subsystem messages")			\
	F(VB_CORE,	0x00004000, "core",	1,      \
	  "core system messages")			\
	F(VB_MEM,	0x00008000, "mem",	1,      \
	  "memory system messages")			\
	F(VB_RELOC,	0x00010000, "reloc",	1,      \
	  "elf relocation info")			\
	F(VB_LOGGING,	0x00020000, "logging",	1,	\
	  "Logging subsystem messages")			\
	F(VB_STREAM,	0x00040000, "stream",	1,	\
	  "Stream subsystem messages")			\
	F(VB_INIT,	0x00080000, "init",	1,	\
	  "Init messages")				\
	F(VB_SECURITY,	0x00100000, "security",	1,	\
	  "Security subsystem messages")		\
	F(VB_PTHREAD,	0x00200000, "pthread",	1,	\
	  "Pthread subsystem messages")			\
	F(VB_MIP,	0x00400000, "mip",	1,	\
	  "MoTeC IP subsystem messages")		\
	F(VB_GATEWAY,	0x00800000, "gateway",	1,	\
	  "Gateway subsystem messages")			\
	F(VB_RESOURCE,	0x01000000, "resource",	1,	\
	  "IO Resource management messages")		\
	F(VB_ANGLE,	0x02000000, "angle",	1,	\
	  "angle subsystem messages")			\
	F(VB_GENIO,	0x04000000, "genio",	1,	\
	  "Genio subsystem messages")

/* REVISIT: concept for cleanup of verbose flags:
   DEBUG - low level, most verbose, per subsystem
   TRACE - program flow per subsystem, very verbose
   INVAL - invalid argument in function call (verbose)
   INFO - occasional program information, state change, startup, etc
   WARN - unexpected operation but recoverable
   CRIT - serious problem, probably fatal

   All but CRIT can be turned on/off per subsystem
   DEBUG, TRACE compiled out in release build
   INVAL, INFO, WARN available for E7SETUP sybsystems in release build
   CRIT always available

#define VB_E7SETUP_SUBSYS_MASK // subsystems directly used by setup
#define VB_CORE_SUBSYS_MASK // core subsystems
#define VB_TYPE_MASK   // all types

   // crit must be used alone
   ct_assert((debug & VB_CRIT) == 0 || debug == VB_CRIT)

   // no subsystem overlap
   ct_assert((VB_E7SETUP_SUBSYS_MASK & VB_CORE_SUBSYS_MASK) == 0)

   // non-crit need subsystem and type
   ct_assert((debug & VB_CRIT)
             || ((debug & (VB_E7SETUP_SUBSYS_MASK | VB_SUBSYS_MASK))
                 && (debug & VB_TYPE_MASK)))

*/

enum VERBOSE_FLAGS
{
#define VERBOSE_ENUM(ARG_ENUM, ARG_VALUE, ARG_STRING, ARG_ADDITIVE, ARG_HELP) \
        ARG_ENUM = ARG_VALUE ,
        VERBOSE_MAP(VERBOSE_ENUM)
};

static inline u32 verbose_get(void)
{
	u32 val;
	asm("mfspr %0,256" : "=r" (val)); /* USPRG0 */
	return val;
}

static inline void verbose_set(u32 val)
{
	asm volatile("mtspr 256,%0" : : "r" (val));
}

/* maximum flags allowed */
#ifdef DEBUG
#ifdef CONFIG_VERBOSE_MAX
#  define VERBOSE_MAX (CONFIG_VERBOSE_MAX)
#else  /* !CONFIG_VERBOSE_MAX */
#  define VERBOSE_MAX (VB_ALL)
#endif	/* !CONFIG_VERBOSE_MAX */
#ifdef CONFIG_VERBOSE_LEVEL
#  define VERBOSE_DEFAULT (VERBOSE_MAX & (CONFIG_VERBOSE_LEVEL))
#else  /* !CONFIG_VERBOSE_LEVEL */
#  define VERBOSE_DEFAULT (VERBOSE_MAX & (~(VB_DEBUG|VB_MORE)))
#endif	/* !CONFIG_VERBOSE_LEVEL */
#define VERBOSE_FMT(fmt) "%s(%u): " fmt "\n", __func__, __LINE__

#else  /* !DEBUG */
#define VERBOSE_MAX (VB_CRIT)
#define VERBOSE_DEFAULT (VERBOSE_MAX & (VB_CRIT))
#define VERBOSE_FMT(fmt) "(%u): " fmt "\n", __LINE__

#endif	/* !DEBUG */

#define VERBOSE_ON(mask) (((verbose_get() & VERBOSE_MAX) & (mask)) == (mask) \
			  && (mask) != 0)
#define TVERBOSE_ON() (tverbose_on != 0)

#define TVERBOSE_STATIC_VARS						\
	static int tverbose_prev;					\
	static int tverbose_on;						\
	static int tverbose;

#define TVERBOSE_STATIC_INIT(mask)					\
	__TVERBOSE_INIT(mask)

#define TVERBOSE_INIT(mask)						\
	static int tverbose_prev;					\
	int tverbose, tverbose_on;					\
	__TVERBOSE_INIT(mask)

#define __TVERBOSE_INIT(mask)						\
	do {								\
		asm("mftbl %0" : "=r" (tverbose));			\
		if ((tverbose - tverbose_prev) > CONFIG_SYS_CLOCK)	\
			tverbose_prev = 0;				\
		tverbose_on = (tverbose_prev == 0 && VERBOSE_ON(mask)); \
	} while (0)
#define __TVERBOSE_CHANGE(mask) if (!tverbose_on) __TVERBOSE_INIT(mask)

#define VERBOSE(mask, fmt, ...)					\
	__VERBOSE(mask, VERBOSE_FMT(fmt), ## __VA_ARGS__)
#define CVERBOSE(mask, cond, fmt, ...)				\
	__CVERBOSE(mask, cond, VERBOSE_FMT(fmt), ## __VA_ARGS__)
#define TVERBOSE(fmt, ...)				\
	__TVERBOSE(VERBOSE_FMT(fmt), ## __VA_ARGS__)

/* wrappers for error codes with format strings. Returns the error code
 * as a -ve number but pastes the error code as a string in debug output
 *
 * Usage:
 * return RC_ERR(EINVAL);
 * return RC_ERR(EIO, "extra info %d", value);
 */
#define RC_ERR(err, ...) /* optionally add fmt and args */		\
	({								\
		VERBOSE(VB_INFO, "(" #err ")" __VA_ARGS__);		\
		-err;	/* return -ve error codes */			\
	})

#define RC_TERR(err, ...) /* optionally add fmt and args */		\
	({								\
		TVERBOSE("(" #err ")" __VA_ARGS__);			\
		-err;	/* return -ve error codes */			\
	})

#define RC_DERR(err, ...) /* optionally add fmt and args */		\
	({								\
		VERBOSE(VB_DEBUG, "(" #err ")" __VA_ARGS__);		\
		-err;	/* return -ve error codes */			\
	})

#define RC_RERR(err, ...) /* optionally add fmt and args */		\
	({								\
		VERBOSE(VB_RESOURCE, "(" #err ")" __VA_ARGS__);		\
		-err;	/* return -ve error codes */			\
	})

#define RC_NERR(err, ...) /* _no_ debug */				\
	({								\
		-err;	/* return -ve error codes */			\
	})

#define RET_ERR(err, ...) /* optionally add fmt and args */		\
	({								\
		ret64_t _ret = { .rc = -err }; /* -ve errors */		\
		VERBOSE(VB_INFO, "(" #err ")" __VA_ARGS__);		\
		_ret;							\
	})

#define RET_TERR(err, ...) /* optionally add fmt and args */		\
	({								\
		ret64_t _ret = { .rc = -err }; /* -ve errors */		\
		TVERBOSE("(" #err ")" __VA_ARGS__);			\
		_ret;							\
	})

#define RET_DERR(err, ...) /* optionally add fmt and args */		\
	({								\
		ret64_t _ret = { .rc = -err }; /* -ve errors */		\
		VERBOSE(VB_DEBUG, "(" #err ")" __VA_ARGS__);		\
		_ret;							\
	})

#define RET_RERR(err, ...) /* optionally add fmt and args */		\
	({								\
		ret64_t _ret = { .rc = -err }; /* -ve errors */		\
		VERBOSE(VB_RESOURCE, "(" #err ")" __VA_ARGS__);		\
		_ret;							\
	})

#define RET_NERR(err, ...) /* return with _no_ debug */			\
	({								\
		ret64_t _ret = { .rc = -err }; /* -ve errors */		\
		_ret;							\
	})

#define RET_OK(...)							\
	({								\
		ret64_t _ret = { .rc = 0 };				\
		VERBOSE(VB_SUBSYS|VB_TRACE, "(ok)" __VA_ARGS__);	\
		_ret;							\
	})

#define RET_OK_S32(val, ...)						\
	({								\
		ret64_t _ret = { .rc = 0, .rval.as_s32 = val };		\
		VERBOSE(VB_SUBSYS|VB_TRACE, "(ok)" __VA_ARGS__);	\
		_ret;							\
	})

#define RET_OK_U32(val, ...)						\
	({								\
		ret64_t _ret = { .rc = 0, .rval.as_u32 = val };		\
		VERBOSE(VB_SUBSYS|VB_TRACE, "(ok)" __VA_ARGS__);	\
		_ret;							\
	})

#define RET_OK_F32(val, ...)						\
	({								\
		ret64_t _ret = { .rc = 0, .rval.as_f32 = val };		\
		VERBOSE(VB_SUBSYS|VB_TRACE, "(ok)" __VA_ARGS__);	\
		_ret;							\
	})

#define RET_OK_PV(val, ...)						\
	({								\
		ret64_t _ret = { .rc = 0, .rval.as_pv = val };		\
		VERBOSE(VB_SUBSYS|VB_TRACE, "(ok)" __VA_ARGS__);	\
		_ret;							\
	})

#if defined(__KERNEL__)
#define __VERBOSE(mask, fmt, ...) do {					\
		if (VERBOSE_ON(mask)) {					\
			printf(fmt, ## __VA_ARGS__);			\
		}							\
	} while (0)
#define __CVERBOSE(mask, cond, fmt, ...) do {				\
		if (VERBOSE_ON(mask) && (cond)) {			\
			printf(fmt, ## __VA_ARGS__);			\
		}							\
	} while (0)
#define __TVERBOSE(fmt, ...) do {					\
		if (TVERBOSE_ON()) {					\
			tverbose_prev = tverbose;			\
			printf(fmt, ## __VA_ARGS__);			\
		}							\
	} while (0)
#else  /* user code */
#define __VERBOSE(mask, fmt, ...) do {					\
		if (VERBOSE_ON(mask)) {					\
			syslog(LOG_ERR, fmt, ## __VA_ARGS__);		\
		}							\
	} while (0)
#define __CVERBOSE(mask, cond, fmt, ...) do {				\
		if (VERBOSE_ON(mask) && (cond)) {			\
			syslog(LOG_ERR, fmt, ## __VA_ARGS__);		\
		}							\
	} while (0)
#define __TVERBOSE(fmt, ...) do {					\
		if (TVERBOSE_ON()) {					\
			tverbose_prev = tverbose;			\
			syslog(LOG_ERR, fmt, ## __VA_ARGS__);		\
		}							\
	} while (0)
#endif

/*
 * Helper to convert float to double.
 * Use this to avoid emulated floating point operation warnings
 */
#if defined(__cplusplus)
extern "C"
#endif
double to_double(float);

#endif /* __VERBOSE_H__ */
