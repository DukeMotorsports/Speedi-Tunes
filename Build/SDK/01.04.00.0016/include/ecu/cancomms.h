#ifndef __ECU_CANCOMMS_H__
#define __ECU_CANCOMMS_H__
#include <ecu/types.h>

/**
 * @addtogroup CanComms
 * @{
 */

/**
 * @fn bool can_init(s32 bus, s32 kbaud)
 * @arg ScriptName Init
 *
 * @brief Initialise CAN bus for communications
 *
 * @param bus CAN bus
 * @param kbaud baud rate in kilobaud
 */
bool __warn_unused_result can_init(u32 bus, u32 kbaud);

/**
 * @fn u32 can_bus_status(s32 bus)
 * @arg ScriptName BusStatus
 *
 * @brief Check CAN bus status
 *
 * @param bus CAN bus (0 to 2)
 *
 * @details <p>The return value will be the sum of one or more of these values:</p>
 * @details <table class=param>
 * @details <tr><th>Return Value</th><th>Meaning</th></tr>
 * @details <tr><td>0</td><td>Ok</td></tr>
 * @details <tr><td>0x01</td><td>Message received</td></tr>
 * @details <tr><td>0x02</td><td>Message overrun</td></tr>
 * @details <tr><td>0x04</td><td>Bus off</td></tr>
 * @details <tr><td>0x08</td><td>Transmit error passive</td></tr>
 * @details <tr><td>0x10</td><td>Receive error passive</td></tr>
 * @details <tr><td>0x20</td><td>Transmit warning</td></tr>
 * @details <tr><td>0x40</td><td>Receive warning</td></tr>
 * @details <tr><td>0x80</td><td>Loopback</td></tr>
 * @details <tr><td>0x100</td><td>Timeout</td></tr>
 * @details <tr><td>0x200</td><td>Wrong Speed (Transmit disabled)</td></tr>
 * @details <tr><td>0x400</td><td>Transmit Overrun</td></tr>
 * @details <tr><td>0x800</td><td>Receive Overrun</td></tr>
 * @details </table>
 *
 * @return CAN bus status
 */

u32 __warn_unused_result can_bus_status(u32 bus);

/** @} CanComms */

#endif /* __ECU_CANCOMMS_H__ */
