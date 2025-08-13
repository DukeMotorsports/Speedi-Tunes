#ifndef __ECU_CANBLOCK_H__
#define __ECU_CANBLOCK_H__

#include <ecu/system.h>
#include <ecu/util.h>

/**
 * @addtogroup CanBlock
 * @{
 * @project module
 */

/**
 * @fn bool canblock_rx_init(s32 bus, u32 base, bool compound)
 * @arg ScriptName RxInit
 *
 * @brief Initialise CAN receive
 *
 * @param bus CAN bus
 * @param base CAN base address (multiple of 8 if sequential)
 * @param compound true for compound, false for sequential can ids
 */

bool __warn_unused_result canblock_rx_init(u32 bus, u32 base, bool compound);

/**
 * @fn u32 canblock_rx_ticks_since(void)
 * @arg ScriptName RxTicksSince
 *
 * @brief Elapsed ticks since last message received
 */

u32 __warn_unused_result canblock_rx_ticks_since(void);

/**
 * @fn u32 canblock_rx_ticks(void)
 * @arg ScriptName RxTicks
 *
 * @brief Report time of last message reception
 *
 * @details <p>Returns zero if time since last reception is greater than
 * @details 2147483647 ticks or if no message has been received since startup.</p>
 */

u32 __warn_unused_result canblock_rx_ticks(void);

/** @} CanBlock */

#endif // __ECU_CANBLOCK_H__
