#ifndef __ECU_VCS_H__
#define __ECU_VCS_H__

#include <ecu/types.h>

/**
 * @addtogroup VCS
 * @{
 */

/**
 * @fn s32 vcs_synchronise(s32 bus, u32 id)
 * @arg ScriptName Synchronise
 *
 * @brief Transmit VCS synchronisation messages
 *
 * @details <p>CAN messages to synchronise VCS video with ECU the data logging
 * @details systems are transmitted approximately once a minute while logging is
 * @details running. This function must be called at 50Hz.</p>
 *
 * @param bus CAN bus (0 to 2)
 * @param id standard CAN id (0x1 to 0x7FF, default 0x21)
 * @return -1 for error; 0 when idle; log system number (1-8) when sync messages are generated
 */

int __warn_unused_result vcs_synchronise(u32 bus, u32 id);

/** @} VCS */

/** @} VCS */

#endif // __ECU_VCS_H__
