#ifndef __ECU_UNIXTIME_H__
#define __ECU_UNIXTIME_H__

#include <ecu/types.h>

/**
 * @addtogroup UnixTime
 * @{
 */
extern s32 make_time(const char *sdk_fn, s32 year, s32 month, s32 day, s32 hour, s32 minute, s32 second, s32 local);
extern s32 time_to_year(const char *sdk_fn, s32 time, s32 local);
extern s32 time_to_mon(const char *sdk_fn, s32 time, s32 local);
extern s32 time_to_mday(const char *sdk_fn, s32 time, s32 local);
extern s32 time_to_hour(const char *sdk_fn, s32 time, s32 local);
extern s32 time_to_minute(const char *sdk_fn, s32 time, s32 local);
extern s32 time_to_second(const char *sdk_fn, s32 time, s32 local);
extern s32 time_to_wday(const char *sdk_fn, s32 time, s32 local);
extern s32 time_to_yday(const char *sdk_fn, s32 time, s32 local);

/**
 * @fn void tz(s32 hour)
 * @arg ScriptName Timezone
 * @brief Set the local time zone.
 * @param hour Hours (-12 to +14) or HHMM (-1245 to 1445)
 *
 * @details <p>This function allows the local time zone offset from UTC to be specified.
 * @details <span class="param"/>hours</span> is between -12 and +14 for most time zones.</p>
 * @details <p>However there are some special cases where the zone includes an offset in minutes
 * @details (30 or 45). To cater for these cases <span class="param"/>hours</span> can be scaled
 * @details by 100 to represent the time zone expressed as hours and minutes. Examples below:</p>
 *
 * @details <table class=param>
 * @details <tr><th>hours</th><th>HHMM</th><th>time zone</th></tr>
 * @details <tr><td>-12</td> <td>-1200</td> <td>UTC−12:00 Baker Island</td></tr>
 * @details <tr><td>-8</td>  <td>-800</td>  <td>UTC−08:00 California (PST)</td></tr>
 * @details <tr><td></td>    <td>545</td>   <td>UTC+05:45 Nepal</td></tr>
 * @details <tr><td>0</td>   <td>0</td>     <td>UTC±00:00 United Kingdom (UTC)</td></tr>
 * @details <tr><td></td>    <td>±15</td>   <td>UTC±00:15 Minimum time offset in minutes</td></tr>
 * @details <tr><td>±1</td>  <td>±100</td>  <td>UTC±01:00 Minimum time offset in whole hours</td></tr>
 * @details <tr><td>10</td>  <td>1000</td>  <td>UTC+10:00 Melbourne (AEST)</td></tr>
 * @details <tr><td>14</td>  <td>1400</td>  <td>UTC+14:00 Kiribati: Line Islands</td></tr>
 * @details </table>
 *
 * @return none
 */
extern void tz(s32 hour);

/**
 * @fn s32 utc_to_time(s32 year, s32 month, s32 day, s32 hour, s32 minute, s32 second)
 * @arg ScriptName FromUtc
 * @brief <p class="device_help">Convert UTC time to a unix time.</p>
 *
 * @details <p class="device_help">Convert the individual fields representing UTC time to a unix time.</p>
 * @details <p class="device_help"><em class="device_help">NOTE:</em><ul>
 * @details <li>month starts at January = 0</li>
 * @details </ul></p>
 *
 * @param year Year (1970-2038)
 * @param month Month (0-11) where January = 0
 * @param day Day of the month (1-31)
 * @param hour Hours (0-23) where midnight = 0
 * @param minute Minutes (0-59)
 * @param second Seconds (0-61) to allow for leap seconds
 * @return Unix time, or -1 to indicate an error
 */
static __inline s32 utc_to_time(s32 year, s32 month, s32 day, s32 hour, s32 minute, s32 second)
{
	const int local = 0;
	return make_time("UnixTime.FromUtc", year, month, day, hour, minute, second, local);
}

/**
 * @fn s32 local_to_time(s32 year, s32 month, s32 day, s32 hour, s32 minute, s32 second)
 * @arg ScriptName FromLocal
 * @brief Convert local time to a unix time.
 *
 * @details <p class="device_help">Convert the individual fields representing local time to a unix time.</p>
 * @details <p class="device_help"><em class="device_help">NOTE:</em><ul>
 * @details <li>month starts at January = 0</li>
 * @details <li>local time zone offset must be set before calling this function. See UnixTime.Timezone().</li>
 * @details </ul></p>
 *
 * @param year Year (1970-2038)
 * @param month Month (0-11) where January = 0
 * @param day Day of the month (1-31)
 * @param hour Hours (0-23) where midnight = 0
 * @param minute Minutes (0-59)
 * @param second Seconds (0-61) to allow for leap seconds
 * @return Unix time, or -1 to indicate an error
 */
static __inline s32 local_to_time(s32 year, s32 month, s32 day, s32 hour, s32 minute, s32 second)
{
	const int local = 1;
	return make_time("UnixTime.FromLocal", year, month, day, hour, minute, second, local);
}

/**
 * @fn s32 gps_to_time(u32 date, f32 time)
 * @arg ScriptName FromGPS
 * @brief Convert GPS date and time to unix time.
 * @param date Date expressed as DDMMYY, as reported by GPS.Date().
 * @param time UTC seconds since midnight, as reported by GPS.Time().
 * @return Unix time, or -1 to indicate an error
 */
extern __warn_unused_result s32 gps_to_time(u32 date, f32 time);

/**
 * @fn s32 unix_to_utc_year(s32 unix)
 * @arg ScriptName ToUtcYear
 * @brief Convert UNIX time to UTC year.
 * @return year (1900-2032), or -1 to indicate an error
 */
static __inline __warn_unused_result s32 unix_to_utc_year(s32 time)
{
	const int local = 0;
	return time_to_year("UnixTime.ToUtcYear", time, local);
}

/**
 * @fn s32 unix_to_utc_mon(s32 unix)
 * @arg ScriptName ToUtcMonth
 * @brief Convert UNIX time to UTC month.
 * @return month (0-11) where January = 0, or -1 to indicate an error
 */
static __inline __warn_unused_result s32 unix_to_utc_mon(s32 time)
{
	const int local = 0;
	return time_to_mon("UnixTime.ToUtcMonth", time, local);
}

/**
 * @fn s32 unix_to_utc_mday(s32 unix)
 * @arg ScriptName ToUtcDay
 * @brief Convert UNIX time to UTC day of month.
 * @return day of month (1-31), or -1 to indicate an error
 */
static __inline __warn_unused_result s32 unix_to_utc_mday(s32 time)
{
	const int local = 0;
	return time_to_mday("UnixTime.ToUtcDay", time, local);
}

/**
 * @fn s32 unix_to_utc_hour(s32 unix)
 * @arg ScriptName ToUtcHour
 * @brief Convert UNIX time to UTC hour.
 * @return hour (0-23) where midnight = 0, or -1 to indicate an error
 */
static __inline __warn_unused_result s32 unix_to_utc_hour(s32 time)
{
	const int local = 0;
	return time_to_hour("UnixTime.ToUtcHour", time, local);
}

/**
 * @fn s32 unix_to_utc_minute(s32 unix)
 * @arg ScriptName ToUtcMinute
 * @brief Convert UNIX time to UTC minute.
 * @return minute (0-59), or -1 to indicate an error
 */
static __inline __warn_unused_result s32 unix_to_utc_minute(s32 time)
{
	const int local = 0;
	return time_to_minute("UnixTime.ToUtcMinute", time, local);
}

/**
 * @fn s32 unix_to_utc_second(s32 unix)
 * @arg ScriptName ToUtcSecond
 * @brief Convert UNIX time to UTC second.
 * @return second (0-59), or -1 to indicate an error
 */
static __inline __warn_unused_result s32 unix_to_utc_second(s32 time)
{
	const int local = 0;
	return time_to_second("UnixTime.ToUtcSecond", time, local);
}

/**
 * @fn s32 unix_to_utc_wday(s32 unix)
 * @arg ScriptName ToUtcWeekDay
 * @brief Convert UNIX time to UTC Week Day.
 * @return week day (0-6) where Sunday = 0, or -1 to indicate an error
 */
static __inline __warn_unused_result s32 unix_to_utc_wday(s32 time)
{
	const int local = 0;
	return time_to_wday("UnixTime.ToUtcWeekDay", time, local);
}

/**
 * @fn s32 unix_to_utc_yday(s32 unix)
 * @arg ScriptName ToUtcYearDay
 * @brief Convert UNIX time to UTC day of year
 * @return day of year (0-365) where 1st January = 0, or -1 to indicate an error
 */
static __inline __warn_unused_result s32 unix_to_utc_yday(s32 time)
{
	const int local = 0;
	return time_to_yday("UnixTime.ToUtcYearDay", time, local);
}

/**
 * @fn s32 unix_to_local_year(s32 unix)
 * @arg ScriptName ToLocalYear
 * @brief Convert UNIX time to local time zone year. See UnixTime.Timezone().
 * @return year (1900-2032), or -1 to indicate an error
 */
static __inline __warn_unused_result s32 unix_to_local_year(s32 time)
{
	const int local = 1;
	return time_to_year("UnixTime.ToLocalYear", time, local);
}

/**
 * @fn s32 unix_to_local_mon(s32 unix)
 * @arg ScriptName ToLocalMonth
 * @brief Convert UNIX time to local time zone month. See UnixTime.Timezone().
 * @return month (0-11) where January = 0, or -1 to indicate an error
 */
static __inline __warn_unused_result s32 unix_to_local_mon(s32 time)
{
	const int local = 1;
	return time_to_mon("UnixTime.ToLocalMonth", time, local);
}

/**
 * @fn s32 unix_to_local_mday(s32 unix)
 * @arg ScriptName ToLocalDay
 * @brief Convert UNIX time to local time zone day of month. See UnixTime.Timezone().
 * @return day of month (1-31), or -1 to indicate an error
 */
static __inline __warn_unused_result s32 unix_to_local_mday(s32 time)
{
	const int local = 1;
	return time_to_mday("UnixTime.ToLocalDay", time, local);
}

/**
 * @fn s32 unix_to_local_hour(s32 unix)
 * @arg ScriptName ToLocalHour
 * @brief Convert UNIX time to local time zone hour. See UnixTime.Timezone().
 * @return hour (0-23), or -1 to indicate an error
 */
static __inline __warn_unused_result s32 unix_to_local_hour(s32 time)
{
	const int local = 1;
	return time_to_hour("UnixTime.ToLocalHour", time, local);
}

/**
 * @fn s32 unix_to_local_minute(s32 unix)
 * @arg ScriptName ToLocalMinute
 * @brief Convert UNIX time to local time zone minute. See UnixTime.Timezone().
 * @return minute (0-59), or -1 to indicate an error
 */
static __inline __warn_unused_result s32 unix_to_local_minute(s32 time)
{
	const int local = 1;
	return time_to_minute("UnixTime.ToLocalMinute", time, local);
}

/**
 * @fn s32 unix_to_local_second(s32 unix)
 * @arg ScriptName ToLocalSecond
 * @brief Convert UNIX time to local time zone second. See UnixTime.Timezone().
 * @return second (0-59), or -1 to indicate an error
 */
static __inline __warn_unused_result s32 unix_to_local_second(s32 time)
{
	const int local = 1;
	return time_to_second("UnixTime.ToLocalSecond", time, local);
}

/**
 * @fn s32 unix_to_local_wday(s32 unix)
 * @arg ScriptName ToLocalWeekDay
 * @brief Convert UNIX time to local time zone week day. See UnixTime.Timezone().
 * @return week day (0-6) where Sunday = 0, or -1 to indicate an error
 */
static __inline __warn_unused_result s32 unix_to_local_wday(s32 time)
{
	const int local = 1;
	return time_to_wday("UnixTime.ToLocalWeekDay", time, local);
}

/**
 * @fn s32 unix_to_local_yday(s32 unix)
 * @arg ScriptName ToLocalYearDay
 * @brief Convert UNIX time to local time zone day of year. See UnixTime.Timezone().
 * @return day of year (0-365) where 1st January = 0, or -1 to indicate an error
 */
static __inline __warn_unused_result s32 unix_to_local_yday(s32 time)
{
	const int local = 1;
	return time_to_yday("UnixTime.ToLocalYearDay", time, local);
}

/** @} UnixTime */

#endif /* __ECU_UNIXTIME_H__ */
