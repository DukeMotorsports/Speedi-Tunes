#ifndef __ECU_CAN_RX_H__
#define __ECU_CAN_RX_H__
#include <ecu/types.h>
#include <ecu/util.h>
#include <ecu/system.h>

#define CANRX_MAGIC 0x434E5258 /* CNRX */

/**
 * @addtogroup CanComms
 * @{
 */

typedef struct cancomms_rx_state {
	u32 magic;
	u32 dev;
	u32 msg_id;
	u32 msg_bitoff;
	u32 msg_bitlen;
	u32 msg_time_us;
	u64 msg;
	bool bigendian;
} cancomms_rx_state;

/**
 * @fn u32 cancomms_rx_open_std(cancomms_rx_state *state, s32 bus, u32 match, u32 mask, bool bigendian)
 * @arg ScriptName RxOpenStandard
 * @arg initcall lib
 *
 * @brief Open receive mode CAN handle
 *
 * @param state [provide]
 * @param bus CAN bus
 * @param match CAN id bits to match
 * @param mask CAN id bits to ignore
 * @param bigendian true for big endian, false for little endian
 *
 * @return CAN receive handle
 */

static __inline __warn_unused_result u32 cancomms_rx_open_std(cancomms_rx_state *s,
    u32 bus, u32 match, u32 mask, bool bigendian)
{
	return (u32)s;
}

void cancomms_rx_open_std_init(cancomms_rx_state *s, u32 bus, u32 match, u32 mask,
    bool bigendian);

/**
 * @fn u32 cancomms_rx_open_ext(cancomms_rx_state *state, s32 bus, u32 match, u32 mask, bool bigendian)
 * @arg ScriptName RxOpenExtended
 * @arg initcall lib
 *
 * @brief Open receive mode CAN handle
 *
 * @param state [provide]
 * @param bus CAN bus
 * @param match CAN id bits to match
 * @param mask CAN id bits to ignore
 * @param bigendian true for big endian, false for little endian
 *
 * @return CAN receive handle
 */

static __inline __warn_unused_result u32 cancomms_rx_open_ext(cancomms_rx_state *s,
    u32 bus, u32 match, u32 mask, bool bigendian)
{
	return (u32)s;
}

void cancomms_rx_open_ext_init(cancomms_rx_state *s, u32 bus, u32 match, u32 mask,
    bool bigendian);

/**
 * @fn bool cancomms_rx_message(u32 handle)
 * @arg ScriptName RxMessage
 *
 * @brief Receive CAN message
 *
 * @param handle CAN receive handle
 *
 * @return true if message received
 */

bool __warn_unused_result cancomms_rx_message(u32 h);

/**
 * @fn u32 cancomms_get_unsignedinteger(u32 handle, s32 bitoff, s32 bitlen)
 * @arg ScriptName GetUnsignedInteger
 *
 * @brief Read unsigned integer from CAN message
 *
 * @details <p>The return value will be the CAN value or one of the following error codes:</p>
 * @details <table class=param>
 * @details <tr><th>Return Value</th><Meaning</th></tr>
 * @details <tr><td>2147483647 (0x7FFFFFFF)</td><td>Bad offset</td></tr>
 * @details <tr><td>2147483646 (0x7FFFFFFE)</td><td>Bad length</td></tr>
 * @details <tr><td>2147483645 (0x7FFFFFFD)</td><td>Bad handle</td></tr>
 * @details <tr><td>2147483644 (0x7FFFFFFC)</td><td>Buffer overrun</td></tr>
 * @details </table>
 *
 * @param handle CAN receive handle
 * @param bitoff bit offset (0 to 63)
 * @param bitlen length of integer in bits (1 to 32)
 *
 * @return Unsigned integer value or error code
 */

__warn_unused_result u32 cancomms_get_unsignedinteger(u32 h, u32 off, u32 len);

/**
 * @fn s32 cancomms_get_integer(u32 handle, s32 bitoff, s32 bitlen)
 * @arg ScriptName GetInteger
 *
 * @brief Read signed integer from CAN message
 *
 * @details <p>The return value will be the CAN value or one of the following error codes:</p>
 * @details <table class=param>
 * @details <tr><th>Return Value</th><Meaning</th></tr>
 * @details <tr><td>2147483647 (0x7FFFFFFF)</td><td>Bad offset</td></tr>
 * @details <tr><td>2147483646 (0x7FFFFFFE)</td><td>Bad length</td></tr>
 * @details <tr><td>2147483645 (0x7FFFFFFD)</td><td>Bad handle</td></tr>
 * @details <tr><td>2147483644 (0x7FFFFFFC)</td><td>Buffer overrun</td></tr>
 * @details </table>
 *
 * @param handle CAN receive handle
 * @param bitoff bit offset (0 to 63)
 * @param bitlen length of integer in bits (1 to 32)
 *
 * @return Signed integer value or error code
 */

__warn_unused_result s32 cancomms_get_integer(u32 h, u32 off, u32 len);

/**
 * @fn f32 cancomms_get_float(u32 handle, s32 bitoff)
 * @arg ScriptName GetFloat
 *
 * @brief Read 32-bit IEEE754-2008 floating point number from CAN message
 *
 * @details <p>The return value will be the CAN value or NAN if an error occurs.</p>
 *
 * @param handle CAN receive handle
 * @param bitoff bit offset (0 to 32)
 *
 * @return Floating point value or NAN on error
 */

__warn_unused_result f32 cancomms_get_float(u32 h, u32 off);

/**
 * @fn bool cancomms_get_bit(u32 handle, s32 bitoff)
 * @arg ScriptName GetBit
 *
 * @brief Read bit from CAN message
 *
 * @details <p>The return value will be the CAN value or false if an error occurs.</p>
 *
 * @param handle CAN receive handle
 * @param bitoff bit offset (0 to 63)
 *
 * @return bit value or false on error
 */

__warn_unused_result bool cancomms_get_bit(u32 h, u32 off);

/**
 * @fn s32 cancomms_get_length(u32 handle)
 * @arg ScriptName GetLength
 *
 * @brief Get received message length in bytes
 *
 * @details <p>The return value will be the length of the CAN message or one of the following error codes:</p>
 * @details <tr><th>Return Value</th><Meaning</th></tr>
 * @details <tr><td>2147483645 (0x7FFFFFFD)</td><td>Bad handle</td></tr>
 * @details </table>
 *
 * @param handle CAN receive handle
 *
 * @return Length of received message in bytes
 */

__warn_unused_result s32 cancomms_get_length(u32 h);

/**
 * @fn u32 cancomms_get_id(u32 handle)
 * @arg ScriptName GetID
 *
 * @brief Get received message ID
 *
 * @details <p>The return value will be the length of the CAN message or one of the following error codes:</p>
 * @details <tr><th>Return Value</th><Meaning</th></tr>
 * @details <tr><td>2147483645 (0x7FFFFFFD)</td><td>Bad handle</td></tr>
 * @details </table>
 *
 * @param handle CAN receive handle
 *
 * @return ID of received message
 */

__warn_unused_result u32 cancomms_get_id(u32 h);

/**
 * @fn u32 cancomms_get_ticks(u32 handle)
 * @arg ScriptName GetTicks
 *
 * @brief Get message receive time in ticks
 *
 * @param handle CAN receive handle
 *
 * @return Time of last message reception in ticks
 */

__warn_unused_result u32 cancomms_get_ticks(u32 h);

/**
 * @fn s32e7 cancomms_get_s32e7(u32 handle, s32 bitoff)
 * @arg ScriptName GetFixed7DP
 *
 * @brief Read fixed point 7DP number from CAN message
 *
 * @details <p>The return value will be the CAN value or one of the following error codes:</p>
 * @details <table class=param>
 * @details <tr><th>Return Value</th><Meaning</th></tr>
 * @details <tr><td>2147483647 (0x7FFFFFFF)</td><td>Bad offset</td></tr>
 * @details <tr><td>2147483646 (0x7FFFFFFE)</td><td>Bad length</td></tr>
 * @details <tr><td>2147483645 (0x7FFFFFFD)</td><td>Bad handle</td></tr>
 * @details <tr><td>2147483644 (0x7FFFFFFC)</td><td>Buffer overrun</td></tr>
 * @details </table>
 *
 * @param handle CAN receive handle
 * @param bitoff bit offset (0 to 63)
 *
 * @return Fixed point value or error code
 */

static __inline __warn_unused_result s32e7 cancomms_get_s32e7(u32 h, u32 off)
{
	return cancomms_get_integer(h, off, 32);
}

/** @} CanComms */

#endif // __ECU_CAN_RX_H__

