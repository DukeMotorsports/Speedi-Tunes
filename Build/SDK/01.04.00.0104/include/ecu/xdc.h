#ifndef __ECU_XDC_H__
#define __ECU_XDC_H__

#include <ecu/system.h>

/**
 * @addtogroup XDC
 * @{
 * @project module
 */

extern struct xdc_state {
	union {
		u8 as_u8[8];
		u16 as_u16[4];
		s8 as_s8[8];
		s16 as_s16[4];
	} m[8];

	u32 msg_ticks;
} xdc_state;

/**
 * @fn bool xdc_init(s32 bus)
 * @arg ScriptName Init
 *
 * @brief Initialise XDC communications
 *
 * @return false if XDC already initialised or bus is invalid
 */
__warn_unused_result bool xdc_init(u32 bus);

/**
 * @fn bool xdc_process()
 * @arg ScriptName Process
 *
 * @brief Call at 50Hz
 *
 * @return false if XDC is not initialised or CAN rx error
 */
__warn_unused_result bool xdc_process(void);

/**
 * @fn u32 xdc_rx_ticks()
 * @arg ScriptName RxTicks
 *
 * @brief Report time of last XDC reception in system ticks
 *
 * @details <p>Returns zero if time since last reception is greater than
 * @details 2147483647 ticks or if no message has been received since startup.</p>
 */
static __inline __warn_unused_result u32 xdc_rx_ticks(void)
{
	if (xdc_state.msg_ticks == 0)
		return 0;

	u32 ticks = ticks_since_u32(xdc_state.msg_ticks);
	if (ticks == 0x7fffffff)
		xdc_state.msg_ticks = 0;

	return xdc_state.msg_ticks;
}

/**
 * @fn u32 xdc_get_unsigned(s32 msg, s32 off, bool word)
 * @arg ScriptName GetUnsigned
 *
 * @brief Get XDC unsigned message data
 */
static __inline __warn_unused_result u32 xdc_get_unsigned(u32 msg, u32 off, bool word)
{
	if (msg > 7)
		return 0;
	if (word) {
		if (off > 3)
			return 0;
		return xdc_state.m[msg].as_u16[off];
	} else {
		if (off > 7)
			return 0;
		return xdc_state.m[msg].as_u8[off];
	}
}

/**
 * @fn s32 xdc_get_signed(s32 msg, s32 off, bool word)
 * @arg ScriptName GetSigned
 *
 * @brief Get XDC signed message data
 */
static __inline __warn_unused_result s32 xdc_get_signed(u32 msg, u32 off, bool word)
{
	if (msg > 7)
		return 0;
	if (word) {
		if (off > 3)
			return 0;
		return xdc_state.m[msg].as_s16[off];
	} else {
		if (off > 7)
			return 0;
		return xdc_state.m[msg].as_s8[off];
	}
}

#endif /* __ECU_XDC_H__ */

