#ifndef __ECU_SYSTEM_H__
#define __ECU_SYSTEM_H__

#include <ecu/thread.h>
#include <ecu/types.h>

#if !defined(ECU_BOARD)
#include <conf/config.h>
#endif

#if defined(__cplusplus)
extern "C" {
#endif

/**
 * @addtogroup System
 * @{
 */
#define SYS_TICK_SHIFT 8

/**
 * @fn u32 ticks_u32(void)
 * @arg ScriptName Ticks
 *
 * @brief System tick count
 *
 * @return current system tick value
 */
static __inline __warn_unused_result u32 ticks_u32(void)
{
	u32 tbhi, tblo, tbhi2;

	do {
		asm volatile("mftbu %0" : "=r" (tbhi));
		asm volatile("mftbl %0" : "=r" (tblo));
		asm volatile("mftbu %0" : "=r" (tbhi2));
	} while (tbhi != tbhi2);

	return (tbhi << (32 - SYS_TICK_SHIFT)) | (tblo >> SYS_TICK_SHIFT);
}

/**
 * @fn u32 ticks_between_u32(u32 begin, u32 end)
 * @arg ScriptName TicksBetween
 *
 * @brief Compute ticks between arguments
 *
 * @details <p>Returns elapsed ticks between <span class="param"/>begin</span> and
 * @details <span class="param"/>end</span>.</p>
 *
 * @param begin starting tick value
 * @param end ending tick value
 * @return ticks between arguments
 */
static __inline __warn_unused_result u32 ticks_between_u32(u32 b, u32 e)
{
	s32 elapsed = e - b;

	if (unlikely(elapsed < 0)) /* catch overflow */
		elapsed = 0x7fffffff;

	return elapsed;
}

/**
 * @fn u32 ticks_since_u32(u32 prev)
 * @arg ScriptName TicksSince
 *
 * @brief Compute ticks elapsed
 *
 * @details <p>Returns elapsed ticks since <span class="param"/>prev</span>.</p>
 *
 * @param prev previous tick value
 * @return elapsed ticks
 */
static __inline __warn_unused_result u32 ticks_since_u32(u32 prev)
{
	return ticks_between_u32(prev, ticks_u32());
}

/**
 * @fn u32 ticks_remaining_u32(u32 ticks, u32 limit)
 * @arg ScriptName TicksRemaining
 *
 * @brief Compute ticks remaining
 *
 * @details <p>Returns ticks remaining between <span class="param"/>ticks</span>
 * @details and <span class="param"/>expire</span> or 0 if
 * @details <span class="param"/>ticks</span> >= <span class="param"/>expire</span>.</p>
 *
 * @param ticks tick value to test
 * @param limit end tick value
 * @return ticks remaining
 */
static __inline __warn_unused_result u32 ticks_remaining_u32(u32 ticks, u32 limit)
{
	s32 delta = limit - ticks;

	if (unlikely(delta < 0))
		return 0;

	return delta;
}

/**
 * @fn u32 hr_ticks_u32(void)
 * @arg ScriptName HiResTicks
 *
 * @brief High resolution system tick count for times < 10 sec
 *
 * @return current system tick value
 */
static __inline __warn_unused_result u32 hr_ticks_u32(void)
{
	u32 tblo;
	asm volatile("mftbl %0" : "=r" (tblo));
	return (tblo) ? tblo : 1;
}

/**
 * @fn u32 hr_ticks_since_u32(u32 prev)
 * @arg ScriptName HiResTicksSince
 *
 * @brief Compute high resolution ticks elapsed
 *
 * @details <p>Returns elapsed high resolution ticks since
 * @details <span class="param"/>prev</span>.</p>
 *
 * @param prev previous high resolution tick value
 * @return elapsed high resolution ticks
 */
static __inline __warn_unused_result u32 hr_ticks_since_u32(u32 prev)
{
	s32 elapsed = hr_ticks_u32() - prev;

	if (unlikely(prev == 0 || elapsed < 0)) /* catch overflow */
		elapsed = 0x7fffffff;

	return elapsed;
}

/*
 * Functions that depend on hardware specific constants are only
 * available for hardware specific code...
 */

/**
 * @fn f32 tick_period_f32(void)
 * @arg ScriptName TickPeriod
 *
 * @brief System tick period in seconds
 *
 * @return period of one tick
 */
static __inline __warn_unused_result f32 tick_period_f32(void)
{
#if defined(ECU_BOARD)
	return (1 << SYS_TICK_SHIFT) / (f32)SYS_CLOCK;
#else
	return (1 << SYS_TICK_SHIFT) / (f32)CONFIG_SYS_CLOCK;
#endif
}

/**
 * @fn f32 hr_tick_period_f32(void)
 * @arg ScriptName HiResTickPeriod
 *
 * @brief High resolution system tick period in seconds
 *
 * @return period of one high resolution tick
 */
static __inline __warn_unused_result f32 hr_tick_period_f32(void)
{
#if defined(ECU_BOARD)
	return 1 / (f32)SYS_CLOCK;
#else
	return 1 / (f32)CONFIG_SYS_CLOCK;
#endif
}

/**
 * @fn f32 elapsed_time_f32(elapsed_time_f32_state *state)
 * @arg ScriptName ElapsedTime
 * @arg initcall lib
 *
 * @brief Elapsed time since current line of script was last executed in seconds
 *
 * @param state [provide]
 * @return time in seconds (max approx 4 hours)
 * @code
 * // example usage
 * __chan(0) f32 elapsed;
 * static elapsed_time_f32_state elapsed_state;
 * elapsed = elapsed_time_f32(&elapsed_state);
 * @endcode
*/

typedef struct {
	s32 prev;
} elapsed_time_f32_state;

static __inline __warn_unused_result f32 elapsed_time_f32(elapsed_time_f32_state *state)
{
	s32 now = ticks_u32();
	s32 elapsed = now - state->prev;
	state->prev = now;

	if (unlikely(elapsed < 0)) /* catch overflow */
		elapsed = 0x7fffffff;

	return elapsed * tick_period_f32();
}

static __inline void elapsed_time_f32_init(elapsed_time_f32_state *state)
{
	state->prev = ticks_u32();
}

/**
 * @fn u32 event_miss_u32(void)
 * @arg ScriptName EventMiss
 *
 * @brief Number of times this thread has missed an event
 *
 * @return number of misses
 */
static __inline __warn_unused_result u32 event_miss_u32(void)
{
	return trigger_miss(0);
}

/**
 * @fn void fdata_store(void)
 * @arg ScriptName Preserve
 *
 * @brief Preserve all flash backed channels
 */
extern void fdata_store(void);

/**
 * @fn void allow_tuning(bool val)
 * @arg ScriptName AllowTuning
 *
 * @brief Enable or disable calibration modifications
 */
extern void allow_tuning(bool val);

/**
 * @fn void debug_msg_3_f32(string msg, f32 val1, f32 val2, f32 val3)
 * @arg ScriptName Debug
 *
 * @brief Write a message to the ECU System Log with optional values
 */
extern void debug_msg_3_f32(const char *msg, f32 val1, f32 val2, f32 val3);

/**
 * @overload void debug_msg_2_f32(string msg, f32 val1, f32 val2)
 */
extern void debug_msg_2_f32(const char *msg, f32 val1, f32 val2);

/**
 * @overload void debug_msg_f32(string msg, f32 value)
 */
extern void debug_msg_f32(const char *msg, f32 val);

/**
 * @overload void debug_msg(string msg)
 */
extern void debug_msg(const char *msg);

/**
 * @overload void debug_msg_string(string msg, string msg2)
 */
extern void debug_msg_string(const char *msg, const char *msg2);
/**
 * @fn void debug_tmsg(string msg)
 * @arg ScriptName TimedDebug
 *
 * @brief Write a message to the ECU System - Limited to one message per second
 */
extern void debug_tmsg(const char *msg);

/**
 * @fn u32 serial(void)
 * @arg ScriptName SerialNumber
 *
 * @brief Returns the ECU Serial Number
 */
extern u32 __warn_unused_result serial(void);

/**
 * @fn u32 flash_size(void)
 * @arg ScriptName FlashSize
 *
 * @brief Returns the FLASH size (in bytes)
 */
extern u32 __warn_unused_result flash_size(void);

/**
 * @fn u32 flash_free(void)
 * @arg ScriptName FlashFree
 *
 * @brief Returns the FLASH free space (in bytes)
 */
extern u32 __warn_unused_result flash_free(void);

/**
 * @fn u32 ram_size(void)
 * @arg ScriptName RamSize
 *
 * @brief Returns the RAM size (in bytes)
 */
extern u32 __warn_unused_result ram_size(void);

/**
 * @fn bool xcp_connected(void)
 * @arg ScriptName XcpConnected
 *
 * @brief Reports if Tune is connected
 */
extern bool __warn_unused_result xcp_connected(void);

/**
 * @fn f32 cpu_idle_f32(void)
 * @arg ScriptName CpuIdle
 * @arg initcall lib
 *
 * @brief The proportion of time the cpu is idle
 *
 * @return idle time as a ratio
*/
extern f32 __warn_unused_result cpu_idle_f32(void);

static __inline void cpu_idle_f32_init(void)
{
	/*
	 * Valid to ignore return value as first call initialises internal state.
	 * Alternatively, we could refactor to have an actual cpu_idle_f32_init function.
	 */
	f32 dummy = cpu_idle_f32();
	dummy = dummy;
}

/**
 * @fn void system_set_firmware_resource(s32 index, f32 val)
 * @arg ScriptName SetFirmwareResource
 *
 * @brief Set floating point value for a firmware resource
 *
 * @param index Firmware resource index (0 to 31)
 */

void system_set_firmware_resource(u32 index, f32 val);

#if defined(__cplusplus)
} /* extern "C" */
#endif

/** @} System */
#endif /* __ECU_SYSTEM_H__ */
