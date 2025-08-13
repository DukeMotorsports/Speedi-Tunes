#ifndef __ECU_J1939_H__
#define __ECU_J1939_H__

#include <ecu/types.h>

#if defined(__cplusplus)
extern "C" {
#endif

/**
 * @addtogroup J1939
 * @{
 */

typedef struct {
	void *p;
	u32 magic;
} j1939_state;

typedef struct __attribute__((packed)) {
	bool active : 1;
	unsigned count : 7;
} j1939_dtc_state_fdata;

typedef struct {
	void *p;
	j1939_dtc_state_fdata *f;
	u32 spn;
	u32 fmi;
	u32 magic;
} j1939_dtc_state;

/**
 * @fn u32 j1939_open(j1939_state *state, s32 bus, s32 address, s32 manufacturer, s32 ecu_instance, s32 function_instance, s32 function, s32 vehicle_system, s32 vehicle_instance, s32 industry_group, bool arbitrary_address)
 * @arg ScriptName Open
 * @arg initcall lib
 *
 * @brief Open J1939 handle
 *
 * @param state [provide]
 * @param bus CAN bus (0 to 2)
 *
 * @return J1939 handle
 */
static __inline __warn_unused_result u32 j1939_open(j1939_state *s, u32 bus,
    u32 address, u32 manufacturer, u32 ecu_instance, u32 function_instance,
    u32 function, u32 vehicle_system, u32 vehicle_instance, u32 industry_group,
    bool arbitrary_address)
{
	return (u32)s;
}

void j1939_open_init(j1939_state *s, u32 bus, u32 address, u32 manufacturer,
    u32 ecu_instance, u32 function_instance, u32 function, u32 vehicle_system,
    u32 vehicle_instance, u32 industry_group, bool arbitrary_address);

/**
 * @fn s32 j1939_get_state(u32 j1939_handle)
 * @arg ScriptName State
 *
 * @brief Get J1939 state
 *
 * @details <p>The return value will be one of the following:</p>
 * @details <table class=param>
 * @details <tr><th>Return Value</th><Meaning</th></tr>
 * @details <tr><td>-6</td><td>Invalid handle</td></tr>
 * @details <tr><td>-5</td><td>Unrecoverable error</td></tr>
 * @details <tr><td>-4</td><td>Invalid source address</td></tr>
 * @details <tr><td>-3</td><td>Waiting for address contention</td></tr>
 * @details <tr><td>-2</td><td>Cannot claim address</td></tr>
 * @details <tr><td>-1</td><td>Bus off</td></tr>
 * @details <tr><td>0</td><td>OK</td></tr>
 * @details </table>
 *
 * @return J1939 state
 */
s32 j1939_get_state(u32 j1939_handle);

/**
 * @fn s32 j1939_get_address(u32 j1939_handle)
 * @arg ScriptName Address
 *
 * @brief get J1939 address
 *
 * @return J1939 address
 */
s32 j1939_get_address(u32 j1939_handle);

/**
 * @fn void j1939_request(u32 j1939_handle, u32 pgn, s32 da)
 * @arg ScriptName Request
 *
 * @brief Send request for J1939 data
 */
void j1939_request(u32 j1939_handle, u32 pgn, u32 da);

/**
 * @fn u32 j1939_rx_pg(j1939_state *state, u32 pgn, s32 sa, s32 max_length)
 * @arg ScriptName RxParameterGroup
 * @arg initcall lib
 *
 * @brief Create J1939 receive parameter group
 *
 * @param state [provide]
 *
 * @return J1939 receive paramter group handle
 */
static __inline __warn_unused_result u32 j1939_rx_pg(j1939_state *s,
    u32 pgn, u32 sa, u32 max_length)
{
	return (u32)s;
}

void j1939_rx_pg_init(j1939_state *s, u32 pgn, u32 sa, u32 max_length);

/**
 * @fn void j1939_rx_pg_register(u32 j1939_rx_pg_handle, u32 j1939_handle)
 * @arg ScriptName RxRegister
 *
 * @brief Register J1939 property group for reception
 */
void j1939_rx_pg_register(u32 j1939_rx_pg_handle, u32 j1939_handle);

/**
 * @fn s32 j1939_pg_get_length(u32 j1939_pg_handle)
 * @arch ScriptName GetLength
 *
 * @brief Get length of data in J1939 receive parameter group
 */
s32 j1939_pg_get_length(u32 j1939_pg_handle);

/**
 * @fn u32 j1939_pg_get_unsignedinteger(u32 j1939_pg_handle, s32 byte, s32 bit, s32 bitlen)
 * @arg ScriptName GetUnsignedInteger
 *
 * @details <p>The return value will be the CAN value or 0xFFFFFFFF on error.</p>
 *
 * @brief Read unsigned integer from J1939 parameter group
 */
u32 j1939_pg_get_unsignedinteger(u32 j1939_pg_handle, u32 byte, u32 bit,
    u32 bitlen);

/**
 * @fn u32 j1939_rx_pg_ticks(u32 j1939_rx_pg_handle)
 * @arg ScriptName RxTicks
 *
 * @brief Get receive parameter group receive time in ticks
 */
u32 j1939_rx_pg_ticks(u32 j1939_rx_pg_handle);

/**
 * @fn u32 j1939_tx_pg(j1939_state *state, u32 pgn, s32 default_priority, s32 max_length)
 * @arg ScriptName TxParameterGroup
 * @arg initcall lib
 *
 * @brief Create J1939 transmit parameter group
 *
 * @param state [provide]
 *
 * @return J1939 transmit paramter group handle
 */
static __inline __warn_unused_result u32 j1939_tx_pg(j1939_state *s,
    u32 pgn, u32 default_priority, u32 max_length)
{
	return (u32)s;
}

void j1939_tx_pg_init(j1939_state *s, u32 pgn, u32 default_priority,
    u32 max_length);

/**
 * @fn void j1939_tx_pg_register(u32 j1939_tx_pg_handle, u32 j1939_handle)
 * @arg ScriptName TxRegister
 *
 * @brief Register J1939 property group for transmission
 */
void j1939_tx_pg_register(u32 j1939_tx_pg_handle, u32 j1939_handle);

/**
 * @fn void j1939_tx_pg_clear(u32 j1939_tx_pg_handle)
 * @arg ScriptName TxClear
 *
 * @brief Clear J1939 property group
 */
void j1939_tx_pg_clear(u32 tx_pg_handle);

/**
 * @fn void j1939_tx_pg_set_unsignedinteger(u32 j1939_tx_pg_handle, s32 byte, s32 bit, s32 bitlen, u32 val)
 * @arg ScriptName TxSetUnsignedInteger
 *
 * @brief Write unsigned integer to J1939 transmit parameter group
 */
void j1939_tx_pg_set_unsignedinteger(u32 j1939_tx_pg_handle, u32 byte, u32 bit,
    u32 bitlen, u32 val);

/**
 * @fn void j1939_tx_pg_tx(u32 j1939_tx_pg_handle, u32 j1939_handle, s32 da)
 * @arg ScriptName TxTransmit
 *
 * @brief Transmit J1939 transmit parameter group
 */
void j1939_tx_pg_tx(u32 j1939_tx_pg_handle, u32 j1939_handle, u32 da);

/**
 * @fn u32 j1939_dtc(j1939_dtc_state *state, s32 spn, s32 fmi)
 * @arg ScriptName DTC
 * @arg initcall lib
 *
 * @brief Create J1939 DTC
 *
 * @param state [provide]
 *
 * @return J1939 DTC handle
 */
static __inline __warn_unused_result u32 j1939_dtc(j1939_dtc_state *s,
    u32 spn, u32 fmi)
{
	return (u32)s;
}

#define j1939_dtc_init(...) \
	__sect(".ecu_fdata", 0, ", \"aw\", @nobits#") static j1939_dtc_state_fdata dtc_fdata; \
	j1939_dtc_init_fdata(&dtc_fdata, __VA_ARGS__)

void j1939_dtc_init_fdata(j1939_dtc_state_fdata *f, j1939_dtc_state *s,
    u32 spn, u32 fmi);

/**
 * @fn void j1939_dtc_register(u32 j1939_dtc_handle, u32 j1939_handle)
 * @arg ScriptName DTCRegister
 *
 * @brief Register J1939 DTC
 */
void j1939_dtc_register(u32 j1939_dtc_handle, u32 j1939_handle);

/**
 * @fn void j1939_dtc_set_active(u32 j1939_dtc_handle, u32 j1939_handle, s32 mi_lamp, s32 stop_lamp, s32 warning_lamp, s32 protect_lamp)
 * @arg ScriptName DTCSetActive
 *
 * @details <table class=param>
 * @details <tr><th>mi_lamp value</th><th>MI lamp state</th></tr>
 * @details <tr><td>0</td><td>off</td></tr>
 * @details <tr><td>1</td><td>off, class C previously active</td></tr>
 * @details <tr><td>2</td><td>off, class C active</td></tr>
 * @details <tr><td>3</td><td>short MI previously active</td></tr>
 * @details <tr><td>4</td><td>short MI active</td></tr>
 * @details <tr><td>5</td><td>on</td></tr>
 * @details <tr><td>6</td><td>on, slow flash</td></tr>
 * @details <tr><td>7</td><td>on, fast flash</td></tr>
 * @details </table>
 * @details <table class=param>
 * @details <tr><th>value</th><th>stop, warning, protect lamp state</th></tr>
 * @details <tr><td>0</td><td>off</td></tr>
 * @details <tr><td>1</td><td>on</td></tr>
 * @details <tr><td>2</td><td>on, slow flash</td></tr>
 * @details <tr><td>3</td><td>on, fast flash</td></tr>
 * @details </table>
 *
 * @brief Set DTC active
 */
void j1939_dtc_set_active(u32 j1939_dtc_handle, u32 j1939_handle,
    u32 mi_lamp, u32 stop_lamp, u32 warning_lamp, u32 protect_lamp);

/**
 * @overload void j1939_dtc_set_active_simple(u32 j1939_dtc_handle, u32 j1939_handle)
 */
void j1939_dtc_set_active_simple(u32 j1939_dtc_handle, u32 j1939_handle);

/**
 * @fn void j1939_dtc_set_inactive(u32 j1939_dtc_handle, u32 j1939_handle)
 * @arg ScriptName DTCSetInactive
 *
 * @brief Set DCT inactive
 */
void j1939_dtc_set_inactive(u32 j1939_dtc_handle, u32 j1939_handle);

/**
 * @fn s32 j1939_dtc_count(u32 j1939_dtc_handle)
 * @arg ScriptName DTCCount
 *
 * @brief Get DTC active count
 */
s32 j1939_dtc_count(u32 j1939_dtc_handle);

/**
 * @fn bool j1939_dtc_active(u32 j1939_dtc_handle)
 * @arg ScriptName DTCActive
 *
 * @brief Get DTC active state
 */
bool j1939_dtc_active(u32 j1939_dtc_handle);

/** @} J1939 */

#if defined(__cplusplus)
} /* extern "C" */
#endif

#endif /* __ECU_J1939_H__ */
