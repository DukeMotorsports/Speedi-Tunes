#ifndef __ECU_CAN_FORWARD_H__
#define __ECU_CAN_FORWARD_H__

#include <ecu/types.h>

/**
 * @addtogroup CanComms
 * @{
 */

/**
 * @fn bool cancomms_forward(s32 from_bus, s32 to_bus, u32 match, u32 mask)
 * @arg ScriptName Forward
 *
 * @brief Forward CAN messages from one CAN bus to another
 *
 * @param from_bus source CAN bus
 * @param to_bus destination CAN bus
 * @param match CAN id bits to match
 * @param mask CAN id bits to ignore
 *
 * @return false if forwarding could not be configured
 */
bool cancomms_forward(u32 in_bus, u32 out_bus, u32 match, u32 mask);

/** @} CanComms */

#endif /* __ECU_CAN_FORWARD_H__ */
