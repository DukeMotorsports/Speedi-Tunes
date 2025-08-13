#ifndef __ECU_PDM_H__
#define __ECU_PDM_H__

#include <ecu/system.h>
#include <ecu/types.h>
#include <ecu/util.h>

/**
 * @addtogroup PDM
 * @{
 * @project module
 */

extern struct pdm_state {
	u8 input_state[23];
	u8 input_voltage[23];
	u8 output_current[32];
	u8 output_load[32];
	u8 output_voltage[32];
	u8 output_status[32];
	u8 internal_temp;
	u8 battery_voltage;
	u8 global_error;
	u8 total_current;
	u8 internal_9v5;
	u8 reset_source;
	u32 msg_hr_ticks;
} pdm_state;

/**
 * @fn bool pdm_init(s32 bus, u32 base)
 * @arg ScriptName Init
 *
 * @brief Initialise PDM communications
 *
 * @param bus CAN bus
 * @param base CAN base ID
 */

__warn_unused_result bool pdm_init(u32 bus, u32 base);

/**
 * @fn bool pdm_input_state(s32 input)
 * @arg ScriptName InputState
 *
 * @brief Get PDM input state
 *
 * @param input input index (0 to 22)
 */

static __inline __warn_unused_result bool pdm_input_state(u32 input)
{
	if (input > ARRAY_SIZE(pdm_state.input_state))
		err_bad_index();
	return pdm_state.input_state[input];
}

/**
 * @fn f32 pdm_internal_temp()
 * @arg ScriptName InternalTemp
 *
 * @brief Get PDM internal temperature
 */

static __inline __warn_unused_result f32 pdm_internal_temp(void)
{
	return pdm_state.internal_temp;
}

/**
 * @fn f32 pdm_battery_voltage()
 * @arg ScriptName BatteryVoltage
 *
 * @brief Get PDM battery voltage
 */

static __inline __warn_unused_result f32 pdm_battery_voltage(void)
{
	return pdm_state.battery_voltage * 0.1216;
}

/**
 * @fn bool pdm_global_error()
 * @arg ScriptName GlobalError
 *
 * @brief Get PDM global error flag
 */

static __inline __warn_unused_result bool pdm_global_error(void)
{
	return pdm_state.global_error;
}

/**
 * @fn f32 pdm_total_current()
 * @arg ScriptName TotalCurrent
 *
 * @brief Get PDM total current
 */

static __inline __warn_unused_result f32 pdm_total_current(void)
{
	return pdm_state.total_current;
}

/**
 * @fn f32 pdm_internal_9v5()
 * @arg ScriptName Internal9V5
 *
 * @brief Get PDM internal 9.5V rail voltage
 */

static __inline __warn_unused_result f32 pdm_internal_9v5(void)
{
	return pdm_state.internal_9v5 * 0.0615;
}

/**
 * @fn u32 pdm_reset_source()
 * @arg ScriptName ResetSource
 *
 * @brief Get PDM reset source
 */

static __inline __warn_unused_result u32 pdm_reset_source(void)
{
	return pdm_state.reset_source;
}

/**
 * @fn f32 pdm_output_current(s32 output)
 * @arg ScriptName OutputCurrent
 *
 * @brief Get PDM output current
 *
 * @param output output pin (0 to 31)
 */

static __inline __warn_unused_result f32 pdm_output_current(u32 output)
{
	if (output > ARRAY_SIZE(pdm_state.output_current))
		err_bad_index();
	return pdm_state.output_current[output] * ((output < 8) ? 0.5 : 0.2);
}

/**
 * @fn f32 pdm_output_load(s32 output)
 * @arg ScriptName OutputLoad
 *
 * @brief Get PDM output load
 *
 * @param output output pin (0 to 31)
 */

static __inline __warn_unused_result f32 pdm_output_load(u32 output)
{
	if (output > ARRAY_SIZE(pdm_state.output_load))
		err_bad_index();
	return pdm_state.output_load[output] * 0.01;
}

/**
 * @fn f32 pdm_output_voltage(s32 output)
 * @arg ScriptName OutputVoltage
 *
 * @brief Get PDM output voltage
 *
 * @param output output pin (0 to 31)
 */

static __inline __warn_unused_result f32 pdm_output_voltage(u32 output)
{
	if (output > ARRAY_SIZE(pdm_state.output_voltage))
		err_bad_index();
	return pdm_state.output_voltage[output] * 0.2;
}

/**
 * @fn u32 pdm_output_status(s32 output)
 * @arg ScriptName OutputStatus
 *
 * @brief Get PDM output status
 *
 * @param output output pin (0 to 31)
 */

static __inline __warn_unused_result u32 pdm_output_status(u32 output)
{
	if (output > ARRAY_SIZE(pdm_state.output_status))
		err_bad_index();
	return pdm_state.output_status[output];
}

/**
 * @fn f32 pdm_input_voltage(s32 input)
 * @arg ScriptName InputVoltage
 *
 * @brief Get PDM input voltage
 *
 * @param input input index (0 to 22)
 */

static __inline __warn_unused_result f32 pdm_input_voltage(u32 input)
{
	if (input > ARRAY_SIZE(pdm_state.input_voltage))
		err_bad_index();
	return pdm_state.input_voltage[input] * 0.2;
}

/**
 * @fn bool pdm_timeout()
 * @arg ScriptName Timeout
 *
 * @brief Detect PDM timeout
 *
 * @details <p>True if no CAN messages received for PDM
 * @details for one second.</p>
 */

static __inline __warn_unused_result bool pdm_timeout(void)
{
	s32 elapsed = hr_ticks_since_u32(pdm_state.msg_hr_ticks);

	if (elapsed < (1 / hr_tick_period_f32()))
		return false;

	pdm_state.msg_hr_ticks = 0; /* timeout */
	return true;
}

/**
 * @fn void pdm_tx(s32 bus, u32 id)
 * @arg ScriptName Transmit
 *
 * @brief Transmit output resource data
 * @param bus CAN bus (0 to 2)
 * @param id CAN ID
 */

void pdm_tx(u32 bus, u32 id);

/** @} PDM */

#endif // __ECU_PDM_H__
