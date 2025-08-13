#ifndef __ECU_CAN_FORWARD_H__
#define __ECU_CAN_FORWARD_H__

#include <ecu/types.h>

/**
 * @addtogroup CanComms
 * @{
 */

/**
 * @fn bool cancomms_forward_std(s32 from_bus, s32 to_bus, u32 match, u32 mask)
 * @arg ScriptName ForwardStandard
 *
 * @brief Setup Forwarding of CAN messages from one CAN bus to another.
 * @brief <p><em>Only call this function from a startup script</em></p>
 * @brief <p>For example match:0x400 mask:0x00F will forward Standard CAN IDs 0x400-0x40F inclusive.</p>
 *
 * @param from_bus source CAN bus (0 to 2)
 * @param to_bus destination CAN bus (0 to 2)
 * @param match CAN id bits to match (0x0 to 0x7FF)
 * @param mask CAN id bits to ignore (0x0 to 0x7FF)
 *
 * @return false if forwarding could not be configured
 */
bool cancomms_forward_std(u32 in_bus, u32 out_bus, u32 match, u32 mask);

/**
 * @fn bool cancomms_forward_ext(s32 from_bus, s32 to_bus, u32 match, u32 mask)
 * @arg ScriptName ForwardExtended
 *
 * @brief Setup Forwarding of CAN messages from one CAN bus to another
 * @brief <p><em>Only call this function from a startup script</em></p>
 * @brief <p>For example match:0x18000 mask:0x6000 will forward 4 Extended IDs: 0x1800, 0x1A00, 0x1C00 and 0x1E00.</p>
 *
 * @param from_bus source CAN bus (0 to 2)
 * @param to_bus destination CAN bus (0 to 2)
 * @param match CAN id bits to match (0x0 to 0x1FFFFFFF)
 * @param mask CAN id bits to ignore (0x0 to 0x1FFFFFFF)
 *
 * @return false if forwarding could not be configured
 */
bool cancomms_forward_ext(u32 in_bus, u32 out_bus, u32 match, u32 mask);

/** @} CanComms */

#endif /* __ECU_CAN_FORWARD_H__ */
