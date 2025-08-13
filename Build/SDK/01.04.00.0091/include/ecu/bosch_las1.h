#ifndef __ECU_BOSCH_LAS1_H__
#define __ECU_BOSCH_LAS1_H__

#include <ecu/types.h>

/**
 * @addtogroup BoschLAS1
 * @{
 * @project module
 */

extern struct bosch_las1_state {
	f32 yaw_rate;
	f32 roll_rate;
	f32 acc_x;
	f32 acc_y;
	u32 yaw_rate_stat;
	u32 roll_rate_stat;
	u32 acc_x_stat;
	u32 acc_y_stat;
	bool init;
	bool timeout;
} bosch_las1_state;

/**
 * @fn bool bosch_las1_init(s32 bus)
 * @arg ScriptName Init
 *
 * @brief Initialise Bosch LAS1 communications
 *
 * @param bus CAN bus
 */

__warn_unused_result bool bosch_las1_init(u32 bus);

/**
 * @fn f32 bosch_las1_yaw_rate()
 * @arg ScriptName YawRate
 *
 * @brief Get Bosch LAS1 yaw rate in °/s
 */

static __inline __warn_unused_result f32 bosch_las1_yaw_rate(void)
{
	return bosch_las1_state.yaw_rate;
}

/**
 * @fn f32 bosch_las1_roll_rate()
 * @arg ScriptName RollRate
 *
 * @brief Get Bosch LAS1 roll rate in °/s
 */

static __inline __warn_unused_result f32 bosch_las1_roll_rate(void)
{
	return bosch_las1_state.roll_rate;
}

/**
 * @fn f32 bosch_las1_acc_x()
 * @arg ScriptName AccelerationX
 *
 * @brief Get Bosch LAS1 X acceleration in g force
 */

static __inline __warn_unused_result f32 bosch_las1_acc_x(void)
{
	return bosch_las1_state.acc_x;
}

/**
 * @fn f32 bosch_las1_acc_y()
 * @arg ScriptName AccelerationY
 *
 * @brief Get Bosch LAS1 X acceleration in g force
 */

static __inline __warn_unused_result f32 bosch_las1_acc_y(void)
{
	return bosch_las1_state.acc_y;
}

/**
 * @fn u32 bosch_las1_yaw_rate_stat()
 * @arg ScriptName YawRateStatus
 *
 * @brief Get Bosch LAS1 yaw rate status flags
 */

static __inline __warn_unused_result u32 bosch_las1_yaw_rate_stat(void)
{
	return bosch_las1_state.yaw_rate_stat;
}

/**
 * @fn u32 bosch_las1_roll_rate_stat()
 * @arg ScriptName RollRateStatus
 *
 * @brief Get Bosch LAS1 roll rate status flags
 */

static __inline __warn_unused_result u32 bosch_las1_roll_rate_stat(void)
{
	return bosch_las1_state.roll_rate_stat;
}

/**
 * @fn u32 bosch_las1_acc_x_stat()
 * @arg ScriptName AccelerationXStatus
 *
 * @brief Get Bosch LAS1 X acceleration status flags
 */

static __inline __warn_unused_result u32 bosch_las1_acc_x_stat(void)
{
	return bosch_las1_state.acc_x_stat;
}

/**
 * @fn u32 bosch_las1_acc_y_stat()
 * @arg ScriptName AccelerationYStatus
 *
 * @brief Get Bosch LAS1 Y acceleration status flags
 */

static __inline __warn_unused_result u32 bosch_las1_acc_y_stat(void)
{
	return bosch_las1_state.acc_y_stat;
}

/**
 * @fn bool bosch_las1_timeout()
 * @arg ScriptName Timeout
 *
 * @brief True if no Bosch LAS1 message received for 1 second
 */

static __inline __warn_unused_result bool bosch_las1_timeout(void)
{
	return bosch_las1_state.timeout || !bosch_las1_state.init;
}

/** @} BoschLAS1 */

#endif // __ECU_BOSCH_LAS1_H__
