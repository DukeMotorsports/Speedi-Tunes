#ifndef __ECU_BR2_H__
#define __ECU_BR2_H__

#include <ecu/types.h>

/**
 * @addtogroup BR2
 * @{
 */

extern struct br2_state {
	u32 beacon_number;
	u32 beacon_ticks;
	u32 valid_receptions;
	f32 detector_peak;
	f32 detection_time;
	u32 beacon_count;
	f32 bias;
	f32 trigger_threshold;
	f32 secondary_threshold;
	f32 detector_background;
	f32 internal_10V;
	f32 internal_12V;
	f32 latest_detector_peak;
	f32 battery_voltage;
	f32 internal_temperature;
	u32 reset_source;
	u32 version;
	u32 error_code;
	u32 noise_bits;
	bool init;
	bool timeout;
} br2_state;


/**
 * @fn bool br2_init(s32 bus, s32 lbn)
 * @arg ScriptName Init
 *
 * @brief Initialise BR2 communications
 *
 * @param bus CAN bus
 * @param lbn Lap beacon number
 */

__warn_unused_result bool br2_init(u32 bus, u32 lbn);

/**
 * @fn bool br2_beacon()
 * @arg ScriptName Beacon
 *
 * @brief True if a beacon has been received since last call
 */

bool __warn_unused_result br2_beacon(void);

/**
 * @fn s32 br2_beacon_number()
 * @arg ScriptName BeaconNumber
 *
 * @brief Get latest beacon number
 */

static __inline __warn_unused_result s32 br2_beacon_number(void)
{
	return br2_state.beacon_number;
}

/**
 * @fn u32 br2_beacon_ticks()
 * @arg ScriptName BeaconTicks
 *
 * @brief Get latest beacon time as measured by the ECU
 *
 * @details <p>This is the time that the last beacon was received as measured
 * @details by the ECU in system ticks.</p>
 */

static __inline __warn_unused_result u32 br2_beacon_ticks(void)
{
	return br2_state.beacon_ticks;
}

/**
 * @fn u32 br2_valid_receptions()
 * @arg ScriptName ValidReceptions
 *
 * @brief Get latest number of valid beacon patterns
 *
 * @details <p>The number of valid beacon patterns received in 50ms. This
 * @details gives a good indication of signal strength. The maximum number
 * @details that can be recorded here is dependent on the beacon mode and
 * @details id, but never exceeds 21.</p>
 */

static __inline __warn_unused_result u32 br2_valid_receptions(void)
{
	return br2_state.valid_receptions;
}

/**
 * @fn f32 br2_detector_peak()
 * @arg ScriptName DetectorPeak
 *
 * @brief Get latest detector peak value
 *
 * @details <p>The peak amplitude of the beacon pulses detected by the receiver
 * @details during the 50ms detection window.</p>
 */

static __inline __warn_unused_result f32 br2_detector_peak(void)
{
	return br2_state.detector_peak;
}

/**
 * @fn f32 br2_detection_time()
 * @arg ScriptName DetectionTime
 *
 * @brief Get latest beacon detection time value
 *
 * @details <p>The beacon detection time gives an indication of the beacon beam
 * @details width. It is defined as the time between the first reception and last
 * @details reception of the beacon pattern while in the detection window.
 * @details Maximum 50ms.</p>
 */

static __inline __warn_unused_result f32 br2_detection_time(void)
{
	return br2_state.detection_time;
}

/**
 * @fn u32 br2_beacon_count()
 * @arg ScriptName BeaconCount
 *
 * @brief Get latest beacon count value
 *
 * @details <p>Beacon count increases for each unique beacon detected. If this
 * @details number jumps by more than one then a weak beacon was received that
 * @details did not meet the criteria for a valid beacon. A valid beacon requires
 * @details at least two beacon patterns in a 50ms window.</p>
 */

static __inline __warn_unused_result u32 br2_beacon_count(void)
{
	return br2_state.beacon_count;
}

/**
 * @fn f32 br2_bias()
 * @arg ScriptName Bias
 *
 * @brief Get latest bias voltage value
 *
 * @details <p>This value gives an indication of the total infra-red load on
 * @details the detector. This is typically around 2.5V but may increase to
 * @details around 9V with direct sunlight or a strong light source shining
 * @details directly at the receiver.</p>
 */

static __inline __warn_unused_result f32 br2_bias(void)
{
	return br2_state.bias;
}

/**
 * @fn f32 br2_trigger_threshold()
 * @arg ScriptName TriggerThreshold
 *
 * @brief Get latest trigger threshold voltage value
 *
 * @details <p>The threshold currently in use for detecting beacon pulses.
 * @details Typically around 0.05V and increases with vehicle noise. If this
 * @details level gets too high range is reduced. An internal error is generated
 * @details if this level is high enough to reduce the BR2 range below the minimum
 * @details specified.</p>
 */

static __inline __warn_unused_result f32 br2_trigger_threshold(void)
{
	return br2_state.trigger_threshold;
}

/**
 * @fn f32 br2_secondary_threshold()
 * @arg ScriptName SecondaryThreshold
 *
 * @brief Get latest secondary threshold voltage value
 *
 * @details <p>Currently not in use.</p>
 */

static __inline __warn_unused_result f32 br2_secondary_threshold(void)
{
	return br2_state.secondary_threshold;
}

/**
 * @fn f32 br2_detector_background()
 * @arg ScriptName DetectorBackground
 *
 * @brief Get latest detector background voltage value
 *
 * @details <p>Indicates the average output of the receiver. Typically around 2.5V</p>
 */

static __inline __warn_unused_result f32 br2_detector_background(void)
{
	return br2_state.detector_background;
}

/**
 * @fn f32 br2_internal_10V()
 * @arg ScriptName Internal10V
 *
 * @brief Get latest internal 10V voltage value
 */

static __inline __warn_unused_result f32 br2_internal_10V(void)
{
	return br2_state.internal_10V;
}

/**
 * @fn f32 br2_internal_12V()
 * @arg ScriptName Internal12V
 *
 * @brief Get latest internal 12V voltage value
 */

static __inline __warn_unused_result f32 br2_internal_12V(void)
{
	return br2_state.internal_12V;
}

/**
 * @fn f32 br2_latest_detector_peak()
 * @arg ScriptName LatestDetectorPeak
 *
 * @brief Get latest detector peak voltage value
 *
 * @details <p>Indicates the peak amplitude reached for the beacon currently
 * @details being received or 0V if no current beacon.</p>
 */

static __inline __warn_unused_result f32 br2_latest_detector_peak(void)
{
	return br2_state.latest_detector_peak;
}

/**
 * @fn f32 br2_battery_voltage()
 * @arg ScriptName BatteryVoltage
 *
 * @brief Get latest battery voltage value
 */

static __inline __warn_unused_result f32 br2_battery_voltage(void)
{
	return br2_state.battery_voltage;
}

/**
 * @fn f32 br2_internal_temperature()
 * @arg ScriptName InternalTemperature
 *
 * @brief Get latest internal temperature value
 */

static __inline __warn_unused_result f32 br2_internal_temperature(void)
{
	return br2_state.internal_temperature;
}

/**
 * @fn u32 br2_reset_source()
 * @arg ScriptName ResetSource
 *
 * @brief Get latest reset source value
 *
 * @details <p>The return value will be one of the following:</p>
 * @details <table class=param>
 * @details <tr><th>Return Value</th><th>Meaning</th></tr>
 * @details <tr><td>0x02</td><td>Low Voltage reset</td></tr>
 * @details <tr><td>0x08</td><td>Illegal Address reset</td></tr>
 * @details <tr><td>0x10</td><td>Illegal operation reset</td></tr>
 * @details <tr><td>0x20</td><td>Watchdog timer reset</td></tr>
 * @details <tr><td>0x40</td><td>External reset</td></tr>
 * @details </table>
 */

static __inline __warn_unused_result u32 br2_reset_source(void)
{
	return br2_state.reset_source;
}

/**
 * @fn u32 br2_version()
 * @arg ScriptName FirmwareVersion
 *
 * @brief Get BR2 firmware version
 */

static __inline __warn_unused_result u32 br2_version(void)
{
	return br2_state.version;
}

/**
 * @fn u32 br2_error_code()
 * @arg ScriptName ErrorCode
 *
 * @brief Get latest error code value
 *
 * @details <p>Standard error codes are defined in the following table:</p>
 * @details <table class=param>
 * @details <tr><th>Return Value</th><th>Meaning</th></tr>
 * @details <tr><td>10</td><td>CONFIG_VERSION</td></tr>
 * @details <tr><td>11</td><td>CONFIG_CRC</td></tr>
 * @details <tr><td>31</td><td>CAN_HW</td></tr>
 * @details <tr><td>34</td><td>CAN_WARN</td></tr>
 * @details <tr><td>42</td><td>EE_WRITE_FAIL</td></tr>
 * @details <tr><td>100</td><td>OUTPUT_DIAG</td></tr>
 * @details <tr><td>101</td><td>RX_NOISE</td></tr>
 * @details </table>
 * @details <p>Any other error code is an indication of a possible internal
 * @details problem. The device should be returned to MoTeC for testing. These
 * @details extended error codes are:</p>
 * @details <table class=param>
 * @details <tr><td>20</td><td>CALIBRATION_VERSION</td></tr>
 * @details <tr><td>21</td><td>CALIBRATION_CRC</td></tr>
 * @details <tr><td>22</td><td>CALIBRATION_BUG</td></tr>
 * @details <tr><td>30</td><td>CAN_NO_DATA</td></tr>
 * @details <tr><td>32</td><td>CAN_INVALID_BASE_INDEX</td></tr>
 * @details <tr><td>33</td><td>CAN_RECEIVE_OVERRUN</td></tr>
 * @details <tr><td>40</td><td>EE_BUSY</td></tr>
 * @details <tr><td>41</td><td>EE_BAD_ADDRESS</td></tr>
 * @details <tr><td>80</td><td>PC_COMMS (+ comms error)</td></tr>
 * @details <tr><td>200</td><td>BKGND_ROUTINE_TIMEOUT (+ background_routine index)</td></tr>
 * @details <tr><td>252</td><td>ILAD_RESET</td></tr>
 * @details <tr><td>253</td><td>ILOP_RESET</td></tr>
 * @details <tr><td>254</td><td>COP_RESET</td></tr>
 * @details <tr><td>255</td><td>ISR_OVERRUN</td></tr>
 * @details </table>
 */

static __inline __warn_unused_result u32 br2_error_code(void)
{
	return br2_state.error_code;
}

/**
 * @fn u32 br2_noise_bits()
 * @arg ScriptName NoiseBits
 *
 * @brief Get latest noise bits value
 *
 * @details <p>The number of noise pulses received so far. This may increase
 * @details rapidly if an unknown IR source is transmitting towards the BR2.</p>
 */

static __inline __warn_unused_result u32 br2_noise_bits(void)
{
	return br2_state.noise_bits;
}

/**
 * @fn bool br2_timeout()
 * @arg ScriptName Timeout
 *
 * @brief True if no BR2 messages received for 1 second
 */

static __inline __warn_unused_result bool br2_timeout(void)
{
	return br2_state.timeout;
}

/** @} BR2 */

#endif // __ECU_BR2_H__
