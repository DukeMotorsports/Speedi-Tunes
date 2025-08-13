#ifndef __ECU_GPS_H__
#define __ECU_GPS_H__

#include <ecu/system.h>
#include <ecu/types.h>

/**
 * @addtogroup GPS
 * @{
 * @project module
 */

extern struct gps_vals {
	/* common */
	f32 time_utc;
	s32e7 latitude;
	s32e7 longitude;

	/* gpgga */
	s32 fix_quality;
	u32 num_sats;
	f32 hdop;
	f32 altitude;
	f32 wgs84_height;
	f32 dgps_update;
	u32 dgps_id;

	/* gprmc */
	bool valid;
	f32 speed;
	f32 true_course;
	u32 date;
	f32 magnetic_variation;
	s32 mode;

	/* latest information */
	u32 latest_ticks;

	/* timeout */
	u32 gga_ticks;
	u32 rmc_ticks;
} gps;

/**
 * @fn bool gps_init_stc(s32 bus)
 * @arg ScriptName InitSTC
 *
 * @brief Initialise GPS communications via STC
 *
 * @param bus CAN bus
 *
 * @return false if GPS already initialsed or bus is invalid
 */
__warn_unused_result bool gps_init_stc(u32 bus);

/**
 * @fn bool gps_init_rs232(s32 port)
 * @arg ScriptName InitRS232
 *
 * @param port serial port to use
 *
 * @brief Initialise GPS communications via RS232
 *
 * @return false if GPS already initialsed
 */
__warn_unused_result bool gps_init_rs232(s32 port);

/**
 * @fn bool gps_process()
 * @arg ScriptName Process
 *
 * @brief Read and decode GPS messages
 *
 * @return false if communications interface is invalid
 */
bool gps_process(void);

/**
 * @fn f32 gps_time_utc()
 * @arg ScriptName Time
 *
 * @brief Get GPS UTC time
 *
 * @details <p>UTC Time as reported by GPS receiver.</p>
 * @details <p>This value is represented as seconds since start of day.</p>
 * @details <p>This value will equal zero (0.0) if no time has been reported.</p>
 * @details <p>Common to both $GPGGA and $GPRMC sentences.</p>
 */

static __inline __warn_unused_result f32 gps_time_utc(void)
{
	return gps.time_utc;
}

/**
 * @fn s32e7 gps_latitude()
 * @arg ScriptName Latitude
 *
 * @brief Get GPS latitude in degrees
 *
 * @details <p>Latitude as reported by GPS receiver.</p>
 * @details <p>This value will equal zero (0.0) if no latitude has been reported.</p>
 * @details <p>Common to both $GPGGA and $GPRMC sentences.</p>
 */

static __inline __warn_unused_result s32e7 gps_latitude(void)
{
	return gps.latitude;
}

/**
 * @fn s32e7 gps_longitude()
 * @arg ScriptName Longitude
 *
 * @brief Get GPS longitude in degrees
 *
 * @details <p>Longitude as reported by GPS receiver.</p>
 * @details <p>This value will equal zero (0.0) if no longitude has been reported.</p>
 * @details <p>Common to both $GPGGA and $GPRMC sentences.</p>
 */

static __inline __warn_unused_result s32e7 gps_longitude(void)
{
	return gps.longitude;
}

/**
 * @fn s32 gps_fix_quality()
 * @arg ScriptName FixQuality
 *
 * @brief Get GPS fix quality
 *
 * @details <p>Fix quality as reported by GPS receiver.</p>
 * @details <table class=param>
 * @details <tr><th>Return Value</th><th>Meaning</th></tr>
 * @details <tr><td>-1</td><td>Unknown</td></tr>
 * @details <tr><td>0</td><td>Invalid</td></tr>
 * @details <tr><td>1</td><td>GPS</td></tr>
 * @details <tr><td>2</td><td>Differential GPS</td></tr>
 * @details <tr><td>3</td><td>Precise Positioning Service (PPS)</td></tr>
 * @details <tr><td>4</td><td>Real Time Kinematic (RTK)</td></tr>
 * @details <tr><td>5</td><td>Float RTK</td></tr>
 * @details <tr><td>6</td><td>Estimated (dead reckoning)</td></tr>
 * @details <tr><td>7</td><td>Manual input mode</td></tr>
 * @details <tr><td>8</td><td>Simulation mode</td></tr>
 * @details </table>
 * @details <p>Contained in $GPGGA sentence only.</p>
 */

static __inline __warn_unused_result s32 gps_fix_quality(void)
{
	return gps.fix_quality;
}

/**
 * @fn u32 gps_num_sats()
 * @arg ScriptName NumSatellites
 *
 * @brief Get number of satellites in use by GPS
 *
 * @details <p>Number of satellites in use as reported by GPS receiver.</p>
 * @details <p>This value will equal zero (0) if no satellite count has been reported.</p>
 * @details <p>Contained in $GPGGA sentence only.</p>
 */

static __inline __warn_unused_result u32 gps_num_sats(void)
{
	return gps.num_sats;
}

/**
 * @fn f32 gps_hdop()
 * @arg ScriptName HDOP
 *
 * @brief Get GPS HDOP value
 *
 * @details <p>Horizontal dilution of precision as reported by GPS receiver.</p>
 * @details <p>In general, the HDOP value can be used as a guide to the accuracy
 * @details of the reported latitude and longitude. It can be roughly interpreted
 * @details as a gain factor on the base accuracy of the receiver.</p>
 * @details <p>For example, a commercial GPS receiver usually has an accuracy of
 * @details between 5 and 7 metres. With a HDOP of 3, the reported latitude and
 * @details longitude should be roughly within 6 * 3 = 18 metres.</p>
 * @details <p>In general, the valid range for HDOP is between 1 and 50.</p>
 * @details <p>This value will equal zero (0.0) if no HDOP has been reported.</p>
 * @details <p>Contained in $GPGGA sentence only.</p>
 */

static __inline __warn_unused_result f32 gps_hdop(void)
{
	return gps.hdop;
}

/**
 * @fn f32 gps_altitude()
 * @arg ScriptName Altitude
 *
 * @brief Get GPS altitude in metres
 *
 * @details <p>Altitude in metres as reported by GPS receiver.<p>
 * @details <p>This value should be interpreted as the altitude of the GPS antenna
 * @details above mean sea level.</p>
 * @details <p>This value will equal zero (0.0) if no altitude has been reported.</p>
 * @details <p>Contained in $GPGGA sentence only.</p>
 */

static __inline __warn_unused_result f32 gps_altitude(void)
{
	return gps.altitude;
}

/**
 * @fn f32 gps_wgs84_height()
 * @arg ScriptName WGS84Height
 *
 * @brief Get GPS height above WGS84 ellipsoid in metres
 *
 * @details <p>Antenna height in metres above WGS84 ellipsoid as reported by GPS receiver.</p>
 * @details <p>This value will equal zero (0.0) if no WGS84 height has been reported.</p>
 * @details <p>Contained in $GPGGA sentence only.</p>
 */

static __inline __warn_unused_result f32 gps_wgs84_height(void)
{
	return gps.wgs84_height;
}

/**
 * @fn f32 gps_dgps_update()
 * @arg ScriptName DGPSUpdateTime
 *
 * @brief Get time since last DGPS update
 *
 * @details <p>Time in seconds since last DGPS update as reported by GPS receiver.</p>
 * @details <p>This value will equal zero (0.0) if no DGPS update has been reported.</p>
 * @details <p>Contained in $GPGGA sentence only.</p>
 */

static __inline __warn_unused_result f32 gps_dgps_update(void)
{
	return gps.dgps_update;
}

/**
 * @fn u32 gps_dgps_id()
 * @arg ScriptName DGPSStationId
 *
 * @brief Get station identifier of last DGPS update
 *
 * @details <p>Station identifier of last DGPS update as reported by GPS receiver.</p>
 * @details <p>This value will equal zero (0) if no DGPS update has been reported.</p>
 * @details <p>Contained in $GPGGA sentence only.</p>
 */

static __inline __warn_unused_result u32 gps_dgps_id(void)
{
	return gps.dgps_id;
}

/**
 * @fn bool gps_valid()
 * @arg ScriptName Valid
 *
 * @brief Get validity flag
 *
 * @details <p>Validity flag as reported by GPS receiver.</p>
 * @details <p>True if GPS receiver reported valid (A), false if receiver reported
 * @details warning (V).</p>
 * @details <p>Contained in $GPRMC sentence only.</p>
 */

static __inline __warn_unused_result bool gps_valid(void)
{
	return gps.valid;
}

/**
 * @fn f32 gps_speed()
 * @arg ScriptName Speed
 *
 * @brief Get GPS speed in metres per second
 *
 * @details <p>Speed as reported by GPS receiver converted to metres per second.</p>
 * @details <p>This value will equal zero (0.0) if no speed has been reported.</p>
 * @details <p>Contained in $GPRMC sentence only.</p>
 */

static __inline __warn_unused_result f32 gps_speed(void)
{
	return gps.speed;
}

/**
 * @fn f32 gps_true_course()
 * @arg ScriptName TrueCourse
 *
 * @brief Get GPS true course in degrees
 *
 * @details <p>True course as reported by GPS receiver.</p>
 * @details <p>Contained in $GPRMC sentence only.</p>
 */

static __inline __warn_unused_result f32 gps_true_course(void)
{
	return gps.true_course;
}

/**
 * @fn u32 gps_date()
 * @arg ScriptName Date
 *
 * @brief Get GPS date
 *
 * @details <p>Date as reported by GPS receiver.</p>
 * @details <p>This value will equal zero (0) if no date has been reported.</p>
 * @details <p>Contained in $GPRMC sentence only.</p>
 */

static __inline __warn_unused_result u32 gps_date(void)
{
	return gps.date;
}

/**
 * @fn f32 gps_magnetic_variation()
 * @arg ScriptName MagneticVariation
 *
 * @brief Get GPS magnetic variation
 *
 * @details <p>Magnetic variation as reported by GPS receiver.</p>
 * @details <p>This value will equal zero (0.0) if no magnetic variation has been
 * @details reported.</p>
 * @details <p>Contained in $GPRMC sentence only.</p>
 */

static __inline __warn_unused_result f32 gps_magnetic_variation(void)
{
	return gps.magnetic_variation;
}

/**
 * @fn s32 gps_mode()
 * @arg ScriptName Mode
 *
 * @brief Get GPS mode of operation
 *
 * @details <p>Mode of operation as reported by GPS receiver.</p>
 * @details <p>This is a subset of Fix quality.</p>
 * @details <p>Only the autonomous and differential modes correspond to an active
 * @details and reliable sentence.</p>
 * @details <p>Contained in $GPRMC version 2.3+ sentence only.</p>
 */

static __inline __warn_unused_result s32 gps_mode(void)
{
	return gps.mode;
}

/**
 * @fn bool gps_timeout_gpgga(f32 time)
 * @arg ScriptName TimeoutGPGGA
 *
 * @brief Detect $GPGGA sentence timeout
 *
 * @details <p>True if no GPS $GPGGA sentences received for
 * @details <span class="param"/>time</span> seconds.</p>
 *
 * @param time Timeout in seconds (minimum 0.1sec).
 */

static __inline __warn_unused_result bool gps_timeout_gpgga(f32 time)
{
	s32 elapsed = ticks_since_u32(gps.gga_ticks);

	time = (time < 0.1f) ? 2.0f : time; /* 2sec if bogus value */
	if (elapsed < (time / tick_period_f32()))
		return false;

	gps.gga_ticks = 0; /* timeout */
	return true;
}

/**
 * @fn bool gps_timeout_gprmc(f32 time)
 * @arg ScriptName TimeoutGPRMC
 *
 * @brief Detect $GPRMC sentence timeout
 *
 * @details <p>True if no GPS $GPRMC sentences received for
 * @details <span class="param"/>time</span> seconds.</p>
 *
 * @param time Timeout in seconds (minimum 0.1sec).
 */

static __inline __warn_unused_result bool gps_timeout_gprmc(f32 time)
{
	s32 elapsed = ticks_since_u32(gps.rmc_ticks);

	time = (time < 0.1f) ? 2.0f : time; /* 2sec if bogus value */
	if (elapsed < (time / tick_period_f32()))
		return false;

	gps.rmc_ticks = 0; /* timeout */
	return true;
}

/**
 * @fn bool gps_timeout(f32 time)
 * @arg ScriptName Timeout
 *
 * @brief Detect GPS timeout
 *
 * @details <p>True if no GPS sentences received for
 * @details <span class="param"/>time</span> seconds.</p>
 *
 * @param time Timeout in seconds (minimum 0.1sec).
 */

static __inline __warn_unused_result bool gps_timeout(f32 time)
{
	return (gps_timeout_gpgga(time) || gps_timeout_gprmc(time));
}

/**
 * @fn u32 gps_rx_ticks()
 * @arg ScriptName RxTicks
 *
 * @brief Report time of last GPS reception in system ticks
 *
 * @details <p>Returns zero if time since last reception is greater than
 * @details 2147483647 ticks or if no message has been received since startup.</p>
 */

static __inline __warn_unused_result u32 gps_rx_ticks(void)
{
	if (gps.latest_ticks == 0)
		return 0;

	u32 ticks = ticks_since_u32(gps.latest_ticks);

	if (ticks == 0x7fffffff)
		gps.latest_ticks = 0;

	return gps.latest_ticks;
}

/** @} GPS */

#endif // __ECU_GPS_H__
