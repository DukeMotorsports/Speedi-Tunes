#ifndef __ECU_CAN_TX_H__
#define __ECU_CAN_TX_H__
#include <ecu/types.h>
#include <ecu/util.h>
#include <ecu/system.h>

#define CANTX_MAGIC 0x434E8458 /* CNTX */

/**
 * @addtogroup CanComms
 * @{
 */

typedef struct cancomms_tx_state {
	u32 magic;
	u32 msg_bitoff;
	u32 msg_bitlen;
	u64 msg;
	bool bigendian;
} cancomms_tx_state;

/**
 * @fn u32 cancomms_tx_open(cancomms_tx_state *state, bool bigendian)
 * @arg ScriptName TxOpen
 * @arg initcall lib
 *
 * @brief Open transmit mode CAN handle
 *
 * @param state [provide]
 * @param bigendian true for big endian, false for little endian
 *
 * @return CAN transmit handle
 */

static __inline __warn_unused_result u32 cancomms_tx_open(cancomms_tx_state *s,
    bool bigendian)
{
	s->msg_bitoff = 0;
	s->msg_bitlen = 0;

	return (u32)s;
}

void cancomms_tx_open_init(cancomms_tx_state *s, bool bigendian);

/**
 * @fn void cancomms_tx_init(u32 handle, s32 len)
 * @arg ScriptName TxInitialise
 *
 * @param handle CAN transmit handle
 * @param len CAN message length in bytes
 *
 * @brief Clear transmit message
 */

static __inline void cancomms_tx_init(u32 h, u32 len)
{
	cancomms_tx_state *s = (cancomms_tx_state*)h;

	extern u32 __bss, __ebss;
	if ((h < (u32)&__bss) || (h >= (u32)&__ebss) || (s->magic != CANTX_MAGIC)) {
		debug_msg("CanComms.TxInitialise: bad handle");
		return;
	}
	if (len > 8)
		err_bad_length();

	s->msg = 0;
	s->msg_bitlen = len * 8;
	s->msg_bitoff = s->bigendian ? 0 : (64 - s->msg_bitlen);
}

/**
 * @fn bool cancomms_tx_std(u32 handle, s32 bus, u32 id)
 * @arg ScriptName TxStandard
 *
 * @brief Transmit CAN message on standard id
 *
 * @param handle CAN transmit handle
 * @param bus CAN bus (0 to 2)
 * @param id standard CAN id (0x1 to 0x7FF)
 *
 * @return false if message could not be transmitted
 */

bool __warn_unused_result cancomms_tx_std(u32 h, u32 bus, u32 id);

/**
 * @fn bool cancomms_tx_ext(u32 handle, s32 bus, u32 id)
 * @arg ScriptName TxExtended
 *
 * @brief Transmit CAN message on extended id
 *
 * @param handle CAN transmit handle
 * @param bus CAN bus (0 to 2)
 * @param id extended CAN id (0x1 to 0x1FFFFFFF)
 *
 * @return false if message could not be transmitted
 */

bool __warn_unused_result cancomms_tx_ext(u32 h, u32 bus, u32 id);

/**
 * @fn bool cancomms_tx_std_rr(s32 bus, u32 id, u32 len)
 * @arg ScriptName TxStandardRR
 *
 * @brief Transmit CAN remote request frame with standard id
 *
 * @param bus CAN bus (0 to 2)
 * @param id standard CAN id (0x1 to 0x7FF)
 * @param len data length (1 to 8 bytes)
 *
 * @return false if message could not be transmitted
 */

bool __warn_unused_result cancomms_tx_std_rr(u32 bus, u32 id, u32 len);

/**
 * @fn bool cancomms_tx_ext_rr(s32 bus, u32 id, u32 len)
 * @arg ScriptName TxExtendedRR
 *
 * @brief Transmit CAN remote request frame with extended id
 *
 * @param bus CAN bus (0 to 2)
 * @param id extended CAN id (0x1 to 0x1FFFFFFF)
 * @param len data length (1 to 8 bytes)
 *
 * @return false if message could not be transmitted
 */

bool __warn_unused_result cancomms_tx_ext_rr(u32 bus, u32 id, u32 len);

/**
 * @fn void cancomms_set_unsignedinteger(u32 handle, s32 bitoff, s32 bitlen, u32 val)
 * @arg ScriptName SetUnsignedInteger
 *
 * @param handle CAN transmit handle
 * @param bitoff bit offset (0 to 63)
 * @param bitlen length of integer in bits (1 to 32)
 * @param val unsigned integer value
 *
 * @brief Write unsigned integer into CAN message
 */

void cancomms_set_unsignedinteger(u32 h, u32 off, u32 len, u32 val);

/**
 * @fn void cancomms_set_integer(u32 handle, s32 bitoff, s32 bitlen, s32 val)
 * @arg ScriptName SetInteger
 *
 * @param handle CAN transmit handle
 * @param bitoff bit offset (0 to 63)
 * @param bitlen length of integer in bits (1 to 32)
 * @param val signed integer value
 *
 * @brief Write signed integer into CAN message
 */

void cancomms_set_integer(u32 h, u32 off, u32 len, s32 val);

/**
 * @fn void cancomms_set_float(u32 handle, s32 bitoff, f32 val)
 * @arg ScriptName SetFloat
 *
 * @param handle CAN receive handle
 * @param bitoff bit offset (0 to 32)
 * @param val floating point value
 *
 * @brief Write 32-bit IEEE754-2008 floating point number into CAN message
 */

void cancomms_set_float(u32 h, u32 off, f32 val);

/**
 * @fn void cancomms_set_bit(u32 handle, s32 bitoff, bool val)
 * @arg ScriptName SetBit
 *
 * @param handle CAN transmit handle
 * @param bitoff bit offset (0 to 63)
 * @param val bit value
 *
 * @brief Write bit into CAN message
 */

void cancomms_set_bit(u32 h, u32 off, bool val);

/**
 * @fn u32 cancomms_xor8(u32 handle)
 * @arg ScriptName XOR8
 *
 * @param handle CAN transmit handle
 *
 * @brief Calculate exclusive or of all bytes in message
 */

__warn_unused_result u32 cancomms_xor8(u32 h);

/** @} CanComms */

#endif // __ECU_CAN_TX_H__
