#ifndef __ECU_PRODUCTION_H__
#define __ECU_PRODUCTION_H__
#include <ecu/types.h>

/**
 * @addtogroup Production
 * @{
 * @project production
 * @project module
 */

extern struct emctest_vals {
	f32 frequency;
	f32 attenuation;
} emctest;

/**
 * @fn void calibration_default()
 * @arg ScriptName LoadDefaultCalibration
 */
extern void calibration_default(void);

/**
 * @fn bool calibration_default_done()
 * @arg ScriptName LoadDefaultCalibrationDone
 */
extern bool calibration_default_done(void) __warn_unused_result;

/**
 * @fn void calibration_store()
 * @arg ScriptName StoreCalibration
 */
extern void calibration_store(void);

/**
 * @fn bool calibration_store_done()
 * @arg ScriptName StoreCalibrationDone
 */
extern bool calibration_store_done(void) __warn_unused_result;

/**
 * @fn bool _calibrated()
 * @arg ScriptName Calibrated
 */
extern bool _calibrated(void) __warn_unused_result;

/**
 * @fn bool can_test(s32 bus)
 * @arg ScriptName CanTest
 *
 * @param bus CAN bus index
 */
extern bool can_test(u32 bus) __warn_unused_result;

/**
 * @fn bool lin_test()
 * @arg ScriptName LinTest
 */
extern bool lin_test(void) __warn_unused_result;

/**
 * @fn bool rs232_test()
 * @arg ScriptName RS232Test
 */
extern bool rs232_test(void) __warn_unused_result;

/**
 * @fn f32 emc_frequency()
 * @arg ScriptName EMCFrequency
 */
static __inline __warn_unused_result f32 emc_frequency(void)
{
	return emctest.frequency;
}

/**
 * @fn f32 emc_attenuation()
 * @arg ScriptName EMCAttenuation
 */
static __inline __warn_unused_result f32 emc_attenuation(void)
{
	return emctest.attenuation;
}

/** @} Production */

#endif /* __ECU_PRODUCTION_H__ */
