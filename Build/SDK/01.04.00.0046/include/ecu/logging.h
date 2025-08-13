#ifndef __ECU_LOGGING_H__
#define __ECU_LOGGING_H__

/**
 * @addtogroup Logging
 * @{
 */

/**
 * @fn bool logging_sys_running(s32 sys)
 * @arg ScriptName Running
 *
 * @brief Check if log system is running
 *
 * @param sys log system index (0 to 7)
 * @return true if running
 */

bool __warn_unused_result logging_sys_running(u32 sys);

/**
 * @overload bool logging_running()
 */

bool __warn_unused_result logging_running(void);

/**
 * @fn bool logging_sys_unloading(s32 sys)
 * @arg ScriptName Unloading
 *
 * @brief Check if log system is unloading
 *
 * @param sys log system index (0 to 7)
 * @return true if unloading
 */

bool __warn_unused_result logging_sys_unloading(u32 sys);

/**
 * @overload bool logging_unloading()
 */

bool __warn_unused_result logging_unloading(void);

/**
 * @fn f32 logging_sys_used(s32 sys)
 * @arg ScriptName Used
 *
 * @brief Check log system usage
 *
 * @param sys log system index (0 to 7)
 * @return ratio of flash memory used
 */

f32 __warn_unused_result logging_sys_used(u32 sys);

/** @} Logging */

#endif // __ECU_LOGGING_H__
