#ifndef __ECU_ANDGF_H__
#define __ECU_ANDGF_H__

#include <ecu/system.h>
#include <ecu/types.h>

/**
 * @addtogroup ANDGF
 * @{
 * @project module
 */

extern struct andgf_vals {
	s32 state;
	f32 val_kg;
	u32 ticks;
} andgf;

/**
 * @fn bool andgf_init_stc(s32 bus)
 * @arg ScriptName InitSTC
 *
 * @brief Initialise AND GF communications via STC
 *
 * @param bus CAN bus
 */
__warn_unused_result bool andgf_init_stc(u32 bus);

/**
 * @fn bool andgf_init_rs232(s32 port)
 * @arg ScriptName InitRS232
 *
 * @param port serial port to use
 *
 * @brief Initialise AND GF communications via RS232
 */
__warn_unused_result bool andgf_init_rs232(s32 port);

/**
 * @fn void andgf_process()
 * @arg ScriptName Process
 *
 * @brief Read and decode AND GF communications
 */
void andgf_process(void);

/**
 * @fn s32 andgf_state()
 * @arg ScriptName State
 *
 * @brief Get AND GF state
 *
 * @details <p>State as reported by AND GF scales.</p>
 * @details <table class=param>
 * @details <tr><th>Return Value</th><th>Meaning</th></tr>
 * @details <tr><td>-1</td><td>Overload</td></tr>
 * @details <tr><td>0</td><td>Unstable</td></tr>
 * @details <tr><td>1</td><td>Stable</td></tr>
 * @details </table>
 */
static __inline __warn_unused_result s32 andgf_state(void)
{
	return andgf.state;
}

/**
 * @fn f32 andgf_val()
 * @arg ScriptName Value
 *
 * @brief Get AND GF value in kilograms
 */
static __inline __warn_unused_result f32 andgf_val(void)
{
	return andgf.val_kg;
}

/**
 * @fn bool andgf_timeout(f32 time)
 * @arg ScriptName Timeout
 *
 * @brief Detect AND GF communications timeout
 *
 * @details <p>True if no AND GF messages received for
 * @details <span class="param"/>time</span> seconds.</p>
 *
 * @param time Timeout in seconds.
 */
static __inline __warn_unused_result bool andgf_timeout(f32 time)
{
	s32 elapsed = hr_ticks_since_u32(andgf.ticks);

	if (elapsed < (time / hr_tick_period_f32()))
		return false;

	andgf.ticks = 0; /* timeout */
	return true;

}

/** @} ANDGF */

#endif // __ECU_ANDGF_H__

