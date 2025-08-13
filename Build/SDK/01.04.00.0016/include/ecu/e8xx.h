#ifndef __ECU_E8XX_H__
#define __ECU_E8XX_H__

#include <ecu/types.h>
#include <ecu/util.h>

/**
 * @addtogroup E8XX
 * @{
 */

extern struct e8xx_state_vals {
	f32 cjc[3];
	u32 output_fault;
	f32 minus_v5;
	f32 v8aux;
	f32 v5aux;
	f32 vbat;
	f32 v45;
	u32 rx_ticks;
} e8xx_state;

/**
 * @fn bool e8xx_init(s32 bus, u32 base)
 * @arg ScriptName Init
 *
 * @brief Initialise E8XX communications
 *
 * @details <p>Initialse the ECU library to receive E8XX data.
 * @details This function should only be called once per project
 * @details in a function scheduled on startup.</p>
 * @details <p>NOTE: only one E8XX is supported.</p>
 *
 * @param bus CAN bus
 * @param base CAN base ID: 0xf0(default), 0xf4, 0xf8 or 0xfc
 * @return true: success, false: fail
 */

bool __warn_unused_result e8xx_init(u32 bus, u32 base);

/**
 * @overload bool e8xx_init_default(s32 bus)
 */
static __inline __warn_unused_result bool e8xx_init_default(u32 bus)
{
	return e8xx_init(bus, 0xf0);
}

/**
 * @fn f32 e8xx_cjc(s32 idx)
 * @arg ScriptName ColdJunction
 *
 * @brief Get E8XX cold junction compensation temperature
 *
 * @param idx Cold junction compensation index (0 to 2)
 */

static __inline __warn_unused_result f32 e8xx_cjc(u32 idx)
{
	if (idx >= 3)
		err_bad_index();
	return e8xx_state.cjc[idx];
}

/**
 * @fn bool e8xx_output_fault(s32 idx)
 * @arg ScriptName OutputFault
 *
 * @brief Get E8XX digital output fault state
 *
 * @param idx Digital output index (0 to 7)
 */

static __inline __warn_unused_result bool e8xx_output_fault(u32 idx)
{
	if (idx >= 8)
		err_bad_index();
	return e8xx_state.output_fault & (1 << idx);
}

/**
 * @fn f32 e8xx_minus_5v()
 * @arg ScriptName RailMinus5v
 *
 * @brief Get E8XX -5v rail voltage
 */

static __inline __warn_unused_result f32 e8xx_minus_5v(void)
{
	return e8xx_state.minus_v5;
}

/**
 * @fn f32 e8xx_v8aux()
 * @arg ScriptName Rail8vAux
 *
 * @brief Get E8XX 8vAux rail voltage
 */

static __inline __warn_unused_result f32 e8xx_v8aux(void)
{
	return e8xx_state.v8aux;
}

/**
 * @fn f32 e8xx_v5aux()
 * @arg ScriptName Rail5vAux
 *
 * @brief Get E8XX 5vAux rail voltage
 */

static __inline __warn_unused_result f32 e8xx_v5aux(void)
{
	return e8xx_state.v5aux;
}

/**
 * @fn f32 e8xx_vbat()
 * @arg ScriptName RailvBat
 *
 * @brief Get E8XX vBat rail voltage
 */

static __inline __warn_unused_result f32 e8xx_vbat(void)
{
	return e8xx_state.vbat;
}

/**
 * @fn f32 e8xx_v45()
 * @arg ScriptName Railv45
 *
 * @brief Get E8XX 4.5v rail voltage
 */

static __inline __warn_unused_result f32 e8xx_v45(void)
{
	return e8xx_state.v45;
}

/**
 * @fn u32 e8xx_rx_ticks_since()
 * @arg ScriptName RxTicksSince
 *
 * @brief Elapsed ticks since last message received
 */

static __inline __warn_unused_result u32 e8xx_rx_ticks_since(void)
{
	if (e8xx_state.rx_ticks == 0)
		return 0x7fffffff;

	u32 ticks = ticks_since_u32(e8xx_state.rx_ticks);

	if (ticks == 0x7fffffff) {
		e8xx_state.rx_ticks = 0;
		return 0x7fffffff;
	}

	return ticks;
}

/**
 * @fn void e8xx_tx(s32 bus)
 * @arg ScriptName Transmit
 *
 * @brief Transmit output resource data
 * @param bus CAN bus (0 to 2)
 */

void e8xx_tx(u32 bus);

/** @} E8XX */

#endif // __ECU_E8XX_H__
