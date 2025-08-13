#ifndef __ECU_RS232COMMS_H__
#define __ECU_RS232COMMS_H__

#include "serial.h"
#include <ecu/types.h>

/**
 * @addtogroup RS232Comms
 * @{
 */

/**
 * @fn bool rs232_init(u32 baud)
 * @arg ScriptName Init
 *
 * @brief Initialise RS232 port for communications
 *
 * @details <p>Initialises RS232 port with baud rate <span class="param">baud</span>.</p>
 * @details <p>Data is framed as 8 data bits and one stop bit.</p>
 *
 * @param baud baud rate
 */
static __inline __warn_unused_result bool rs232_init(u32 baud)
{
	return serial_port_init(0, baud, false); /* compatibility */
}

/**
 * @fn s32 rs232_diagnostic(void)
 * @arg ScriptName Diagnostic
 *
 * @brief Check RS232 diagnostic
 *
 * @details <p>The return value will be the sum of one or more of these values:</p>
 * @details <table class=param>
 * @details <tr><th>Return Value</th><th>Meaning</th></tr>
 * @details <tr><td>-1</td><td>Not in Use</td></tr>
 * @details <tr><td>0</td><td>OK</td></tr>
 * @details <tr><td>0x01</td><td>Break received</td></tr>
 * @details <tr><td>0x02</td><td>Framing Error</td></tr>
 * @details <tr><td>0x04</td><td>Parity Error</td></tr>
 * @details <tr><td>0x08</td><td>Overrun</td></tr>
 * @details <tr><td>0x10</td><td>Noise</td></tr>
 * @details </table>
 *
 * @return RS232 diagnostic
 */

static __inline s32 __warn_unused_result rs232_diagnostic(void)
{
	return serial_port_diagnostic(0); /* compatibility */
}

/** @} RS232Comms */

#endif // __ECU_RS232COMMS_H__
