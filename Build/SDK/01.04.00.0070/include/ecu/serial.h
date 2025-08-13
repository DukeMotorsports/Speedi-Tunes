#ifndef __ECU_SERIAL_H__
#define __ECU_SERIAL_H__

#include <ecu/types.h>
#include <ecu/util.h>
#include <ecu/system.h>

#define SERIAL_MAGIC 0x55415254 /* UART */
#define SERIAL_LEN 256

/**
 * @addtogroup Serial
 * @{
 */

typedef struct serial_state {
	u32 magic;
	s32 rx_len;
	u8 msg[SERIAL_LEN];
	bool bigendian;
} serial_state;

/**
 * @fn u32 serial_handle(serial_state *state, bool bigendian)
 * @arg ScriptName GetHandle
 * @arg initcall lib
 *
 * @brief Open a serial handle
 *
 * @param state [provide]
 * @param bigendian true for big endian, false for little endian
 *
 * @return serial handle
 */

static __inline __warn_unused_result u32 serial_handle(serial_state *s,
    bool bigendian)
{

	return (u32)s;
}

void serial_handle_init(serial_state *s, bool bigendian);

/* REVISIT: remove serial_tx_open() in 1.3.17 */
/**
 * @fn u32 serial_tx_open(serial_state *state, bool bigendian)
 * @arg ScriptName GetTransmitHandle
 * @arg initcall lib
 *
 * @brief Open transmit mode serial handle DEPRECATED: use GetHandle
 *
 * @param state [provide]
 * @param bigendian true for big endian, false for little endian
 *
 * @return serial transmit handle
 */

#define serial_tx_open serial_handle
#define serial_tx_open_init serial_handle_init
/* end remove in 1.3.17 */

/**
 * @fn void serial_tx(u32 handle, s32 port, s32 length)
 * @arg ScriptName Transmit
 *
 * @param handle serial transmit handle
 * @param port serial port to use
 * @param length serial message length in bytes
 *
 * @brief Sends len bytes on serial port
 */

void serial_tx(u32 h, u32 port, u32 len);

/**
 * @fn s32 serial_set_linhdr(u32 handle, s32 offset, s32 length, u32 id, bool tx, bool enhanced)
 * @arg ScriptName SetLinHeader
 *
 * @param handle serial transmit handle
 * @param offset byte offset into packet (0 to 255)
 * @param length LIN data length in bytes
 * @param id LIN id (1 to 63)
 * @param tx true to send data, false to request a response
 * @param enhanced true for enhanced checksum (false for classic)
 *
 * @brief Writes a LIN header into the serail message
 *
 * @return adjusted offset (offset + header length) or -ve on error
 */

__warn_unused_result s32 serial_set_linhdr(u32 h, u32 off, u32 len, u32 id, bool tx, bool enhanced);

/**
 * @fn s32 serial_set_unsignedinteger(u32 handle, s32 offset, s32 length, u32 value)
 * @arg ScriptName SetUnsignedInteger
 *
 * @param handle serial transmit handle
 * @param offset byte offset into packet (0 to 255)
 * @param length length of integer in bytes (1 to 4)
 * @param value unsigned integer value
 *
 * @brief Write unsigned integer into serial message
 *
 * @return adjusted offset (offset + length) or -ve on error
 */

__warn_unused_result s32 serial_set_unsignedinteger(u32 h, u32 off, u32 len, u32 val);

/**
 * @fn s32 serial_set_integer(u32 handle, s32 offset, s32 length, s32 value)
 * @arg ScriptName SetInteger
 *
 * @param handle serial transmit handle
 * @param offset byte offset into packet (0 to 255)
 * @param length length of integer in bytes (1 to 4)
 * @param value integer value
 *
 * @brief Write integer into serial message
 *
 * @return adjusted offset (offset + length) or -ve on error
 */

__warn_unused_result s32 serial_set_integer(u32 h, u32 off, u32 len, s32 val);

/**
 * @fn s32 serial_set_f32(u32 handle, s32 offset, f32 value)
 * @arg ScriptName SetFloat
 *
 * @param handle serial transmit handle
 * @param offset byte offset into packet (0 to 255)
 * @param value floating point value
 *
 * @brief Write floating point value into serial message
 *
 * @return adjusted offset (offset + length) or -ve on error
 */

__warn_unused_result s32 serial_set_f32(u32 h, u32 off, f32 val);

/**
 * @fn s32 serial_set_string(u32 handle, s32 offset, s32 length, string text)
 * @arg ScriptName SetString
 *
 * @param handle serial transmit handle
 * @param offset byte offset into packet (0 to 255)
 * @param length maximum length of text (1 to 256)
 * @param text string of text to insert
 *
 * @brief Write a string into serial message
 *
 * @return adjusted offset (offset + characters written) or -ve on error
 */

__warn_unused_result s32 serial_set_string(u32 h, u32 off, u32 len, const char *text);

/**
 * @fn u32 serial_xor8(u32 handle, s32 offset, s32 length)
 * @arg ScriptName XOR8
 *
 * @param handle serial transmit handle
 * @param offset byte offset into packet (0 to 255)
 * @param length number of bytes to process
 *
 * @brief Calculate exclusive-or of the message data bytes
 */

__warn_unused_result u32 serial_xor8(u32 h, u32 off, u32 len);

/**
 * @fn u32 serial_sum8(u32 handle, s32 offset, s32 length)
 * @arg ScriptName Sum8
 *
 * @param handle serial transmit handle
 * @param offset byte offset into packet (0 to 255)
 * @param length number of bytes to process
 *
 * @brief Calculate sum of the message data bytes
 */

__warn_unused_result u32 serial_sum8(u32 h, u32 off, u32 len);

/**
 * @fn bool serial_rx(u32 handle, s32 port)
 * @arg ScriptName Receive
 *
 * @param handle serial handle
 * @param port serial port to use
 *
 * @brief Receives data from the serial port
 *
 * @return true if data was received
 */

bool serial_rx(u32 h, u32 port);

/**
 * @fn s32 serial_get_linoff(u32 handle, u32 id)
 * @arg ScriptName GetLinOffset
 *
 * @param handle serial handle
 * @param id LIN id (1 to 63)
 *
 * @brief Finds the data offset for a LIN frame with the specified id
 *
 * @return frame data offset or -ve if not found
 */

s32 serial_get_linoff(u32 h, u32 id);

/**
 * @fn void serial_lindump(u32 handle)
 * @arg ScriptName LinDump
 *
 * @param handle serial handle
 *
 * @brief print all LIN packets to the ECU log
 */

void serial_lindump(u32 h);

/**
 * @fn s32 serial_get_integer(u32 handle, s32 offset, s32 length)
 * @arg ScriptName GetInteger
 *
 * @brief Read signed integer
 *
 * @param handle serial handle
 * @param offset byte offset (0 to 255)
 * @param length length of integer (1 to 4)
 *
 * @return Signed integer value
 */

__warn_unused_result s32 serial_get_integer(u32 h, u32 off, u32 len);

/**
 * @fn u32 serial_get_unsignedinteger(u32 handle, s32 offset, s32 length)
 * @arg ScriptName GetUnsignedInteger
 *
 * @brief Read unsigned integer
 *
 * @param handle serial handle
 * @param offset byte offset (0 to 255)
 * @param length length of integer (1 to 4)
 *
 * @return Unsigned integer value
 */

__warn_unused_result u32 serial_get_unsignedinteger(u32 h, u32 off, u32 len);

/**
 * @fn bool serial_port_init(s32 port, u32 baud, s32 protocol)
 * @arg ScriptName PortInit
 *
 * @brief Initialise Serial port for communications
 *
 * @details <p>Initialises serial port with baud rate <span class="param">baud</span>.</p>
 * @details <p>Data is framed as 8 data bits and one stop bit.</p>
 *
 * @param port serial port number (0: rs232, 1: LIN)
 * @param baud baud rate
 * @param protocol 0: rs232 1: lin
 *
 * @return false if serial port not available
 */
__warn_unused_result bool serial_port_init(u32 port, u32 baud, u32 protocol);

/**
 * @fn s32 serial_port_diagnostic(s32 port)
 * @arg ScriptName PortDiagnostic
 *
 * @brief Check serial port diagnostic
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
 * @details <tr><td>0x20</td><td>LIN bit error</td></tr>
 * @details <tr><td>0x40</td><td>LIN bus error</td></tr>
 * @details <tr><td>0x80</td><td>LIN checksum error</td></tr>
 * @details <tr><td>0x100</td><td>LIN timeout</td></tr>
 * @details </table>
 *
 * @param port serial port number (0: rs232, 1: LIN)
 *
 * @return Port diagnostic
 */

__warn_unused_result s32 serial_port_diagnostic(u32 port);

/** @} Serial */

#endif // __ECU_SERIAL_H__
