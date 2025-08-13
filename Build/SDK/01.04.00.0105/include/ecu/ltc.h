#ifndef __ECU_LTC_H__
#define __ECU_LTC_H__

#include <ecu/system.h>
#include <ecu/types.h>
#include <ecu/util.h>

/**
 * @addtogroup LTC
 * @{
 */

#define NUM_LTC 32

enum lambda_type {
	lt_LTC,
	lt_PLM,
	lt_LTCN,
	NUM_LAMBDA_TYPE
};

extern struct ltc_state_vals {
	f32 lambda;
	f32 ipn_A;
	f32 temp_C;
	u32 fault_bits;
	f32 heater_duty_P;
	u32 sensor_state;
	f32 battery_V;
	f32 ip_A;
	f32 ri_O;
	f32 fwver;
	u32 serial;
	f32 vs_V;
	u32 msg_hr_ticks;
	s32 debug1;
	s32 debug2;
	s32 debug3;
	enum lambda_type type;
} ltc_state[];

/**
 * @fn bool ltc_init(s32 ltc, s32 type, s32 bus)
 * @arg ScriptName Init
 *
 * @param ltc ltc index (0 to 31, -1 for all)
 * @param type device type (0: ltc, 1: plm, 2: ltcn)
 * @brief Initialise LTC / PLM communications
 *
 * @param bus CAN bus
 */
__warn_unused_result bool ltc_init(u32 ltc, u32 type, u32 bus);

/**
 * @fn void ltc_mode(s32 ltc, bool enable)
 * @arg ScriptName Mode
 *
 * @brief Set LTC mode
 *
 * @param ltc ltc index (0 to 31, -1 for all)
 * @param enable enable flag
 */
void ltc_mode(u32 ltc, bool enable);

/**
 * @fn f32 ltc_lambda(s32 ltc)
 * @arg ScriptName Lambda
 *
 * @brief Get LTC / PLM lambda value
 *
 * @param ltc ltc index (0 to 31)
 */

static __inline __warn_unused_result f32 ltc_lambda(u32 ltc)
{
	if (ltc >= NUM_LTC) {
		if (__builtin_constant_p(ltc))
			err_bad_index();
		else {
			TPRINTF_RA("bad ltc index %d", ltc);
			return 0;
		}
	}
	return ltc_state[ltc].lambda;
}

/**
 * @fn f32 ltc_ipn_a(s32 ltc)
 * @arg ScriptName Ipn
 *
 * @brief Get LTC / PLM normalised pump cell current
 *
 * @param ltc ltc index (0 to 31)
 */

static __inline __warn_unused_result f32 ltc_ipn_a(u32 ltc)
{
	if (ltc >= NUM_LTC) {
		if (__builtin_constant_p(ltc))
			err_bad_index();
		else
			return 0;
	}
	return ltc_state[ltc].ipn_A;
}

/**
 * @fn f32 ltc_temp_c(s32 ltc)
 * @arg ScriptName InternalTemp
 *
 * @brief Get LTC / PLM internal temperature
 *
 * @param ltc ltc index (0 to 31)
 */

static __inline __warn_unused_result f32 ltc_temp_c(u32 ltc)
{
	if (ltc >= NUM_LTC) {
		if (__builtin_constant_p(ltc))
			err_bad_index();
		else
			return 0;
	}
	return ltc_state[ltc].temp_C;
}

/**
 * @fn u32 ltc_fault_bits(s32 ltc)
 * @arg ScriptName FaultBits
 *
 * @brief Get LTC / PLM fault bits
 *
 * @param ltc ltc index (0 to 31)
 */

static __inline __warn_unused_result u32 ltc_fault_bits(u32 ltc)
{
	if (ltc >= NUM_LTC) {
		if (__builtin_constant_p(ltc))
			err_bad_index();
		else
			return 0;
	}
	return ltc_state[ltc].fault_bits;
}

/**
 * @fn f32 ltc_heater_duty_p(s32 ltc)
 * @arg ScriptName HeaterDuty
 *
 * @brief Get LTC / PLM heater duty
 *
 * @param ltc ltc index (0 to 31)
 */

static __inline __warn_unused_result f32 ltc_heater_duty_p(u32 ltc)
{
	if (ltc >= NUM_LTC) {
		if (__builtin_constant_p(ltc))
			err_bad_index();
		else
			return 0;
	}
	return ltc_state[ltc].heater_duty_P;
}

/**
 * @fn s32 ltc_sensor_state(s32 ltc)
 * @arg ScriptName SensorState
 *
 * @brief Get LTC / PLM sensor state
 *
 * @param ltc ltc index (0 to 31)
 */

static __inline __warn_unused_result u32 ltc_sensor_state(u32 ltc)
{
	if (ltc >= NUM_LTC) {
		if (__builtin_constant_p(ltc))
			err_bad_index();
		else
			return 0;
	}
	return ltc_state[ltc].sensor_state;
}

/**
 * @fn f32 ltc_battery_v(s32 ltc)
 * @arg ScriptName BatteryVoltage
 *
 * @brief Get LTC / PLM battery voltage
 *
 * @param ltc ltc index (0 to 31)
 */

static __inline __warn_unused_result f32 ltc_battery_v(u32 ltc)
{
	if (ltc >= NUM_LTC) {
		if (__builtin_constant_p(ltc))
			err_bad_index();
		else
			return 0;
	}
	return ltc_state[ltc].battery_V;
}

/**
 * @fn f32 ltc_ip_a(s32 ltc)
 * @arg ScriptName Ip
 *
 * @brief Get LTC / PLM raw pump cell current
 *
 * @param ltc ltc index (0 to 31)
 */

static __inline __warn_unused_result f32 ltc_ip_a(u32 ltc)
{
	if (ltc >= NUM_LTC) {
		if (__builtin_constant_p(ltc))
			err_bad_index();
		else
			return 0;
	}
	return ltc_state[ltc].ip_A;
}

/**
 * @fn f32 ltc_ri_o(s32 ltc)
 * @arg ScriptName Ri
 *
 * @brief Get LTC / PLM sensor cell impedance
 *
 * @param ltc ltc index (0 to 31)
 */

static __inline __warn_unused_result f32 ltc_ri_o(u32 ltc)
{
	if (ltc >= NUM_LTC) {
		if (__builtin_constant_p(ltc))
			err_bad_index();
		else
			return 0;
	}
	return ltc_state[ltc].ri_O;
}

/**
 * @fn f32 ltc_fwver(s32 ltc)
 * @arg ScriptName FirmwareVersion
 *
 * @brief Get LTC / PLM firmware version
 *
 * @details <p>NOTE: the firmware letter is encoded as the third and fourth
 * @details decimal place where 00=A, 01=B. For example 1.0402 means 1.04 C</p>
 *
 * @param ltc ltc index (0 to 31)
 */

static __inline __warn_unused_result f32 ltc_fwver(u32 ltc)
{
	if (ltc >= NUM_LTC) {
		if (__builtin_constant_p(ltc))
			err_bad_index();
		else
			return 0;
	}
	return ltc_state[ltc].fwver;
}

/**
 * @fn u32 ltc_serial(s32 ltc)
 * @arg ScriptName SerialNumber
 *
 * @brief Get LTC / PLM sensor state
 *
 * @param ltc ltc index (0 to 31)
 */

static __inline __warn_unused_result u32 ltc_serial(u32 ltc)
{
	if (ltc >= NUM_LTC) {
		if (__builtin_constant_p(ltc))
			err_bad_index();
		else
			return 0;
	}
	return ltc_state[ltc].serial;
}

/**
 * @fn f32 ltc_vs(s32 ltc)
 * @arg ScriptName VS
 *
 * @brief Get LTC / PLM VS voltage
 *
 * @param ltc ltc index (0 to 31)
 */

static __inline __warn_unused_result f32 ltc_vs(u32 ltc)
{
	if (ltc >= NUM_LTC) {
		if (__builtin_constant_p(ltc))
			err_bad_index();
		else
			return 0;
	}
	return ltc_state[ltc].vs_V;
}

/**
 * @fn bool ltc_timeout(s32 ltc)
 * @arg ScriptName Timeout
 *
 * @brief Detect LTC / PLM timeout
 *
 * @details <p>True if no CAN messages received for LTC
 * @details <span class="param"/>ltc</span> for one second.</p>
 *
 * @param ltc ltc index (0 to 31)
 */

static __inline __warn_unused_result bool ltc_timeout(u32 ltc)
{
	if (ltc >= NUM_LTC) {
		if (__builtin_constant_p(ltc))
			err_bad_index();
		else
			return 0;
	}

	struct ltc_state_vals* v = ltc_state + ltc;
	s32 elapsed = hr_ticks_since_u32(v->msg_hr_ticks);

	if (elapsed < (1 / hr_tick_period_f32()))
		return false;

	v->msg_hr_ticks = 0; /* timeout */
	return true;
}

/**
 * @fn s32 ltc_debug1(s32 ltc)
 * @arg ScriptName Debug1
 *
 * @brief Get debug1
 *
 * @param ltc ltc index (0 to 31)
 */

static __inline __warn_unused_result s32 ltc_debug1(u32 ltc)
{
	if (ltc >= NUM_LTC) {
		if (__builtin_constant_p(ltc))
			err_bad_index();
		else
			return 0;
	}
	return ltc_state[ltc].debug1;
}

/**
 * @fn s32 ltc_debug2(s32 ltc)
 * @arg ScriptName Debug2
 *
 * @brief Get debug2
 *
 * @param ltc ltc index (0 to 31)
 */

static __inline __warn_unused_result s32 ltc_debug2(u32 ltc)
{
	if (ltc >= NUM_LTC) {
		if (__builtin_constant_p(ltc))
			err_bad_index();
		else
			return 0;
	}
	return ltc_state[ltc].debug2;
}

/**
 * @fn s32 ltc_debug3(s32 ltc)
 * @arg ScriptName Debug3
 *
 * @brief Get debug3
 *
 * @param ltc ltc index (0 to 31)
 */

static __inline __warn_unused_result s32 ltc_debug3(u32 ltc)
{
	if (ltc >= NUM_LTC) {
		if (__builtin_constant_p(ltc))
			err_bad_index();
		else
			return 0;
	}
	return ltc_state[ltc].debug3;
}

/** @} LTC */

#endif // __ECU_LTC_H__
