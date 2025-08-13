#ifndef __ECU_TDKLAMBDA_H__
#define __ECU_TDKLAMBDA_H__

#include <ecu/types.h>

/**
 * @addtogroup TDKLambda
 * @{
 * @project module
 */

/**
 * @fn bool tdklambda_init(s32 port)
 * @arg ScriptName Init
 *
 * @param port serial port to use
 *
 * @brief Initialise TDK-Lambda communications via RS232
 */
__warn_unused_result bool tdklambda_init(s32 port);

/**
 * @fn void tdklambda_setaddress(s32 address)
 * @arg ScriptName SetAddress
 *
 * @brief Set ZERO-UP power supply address.
 */

void tdklambda_setaddress(u32 address);

/**
 * @fn void tdklambda_setvoltage(f32 volts, s32 type)
 * @arg ScriptName SetVoltage
 *
 * @brief Set TDK-Lambda power supply voltage via RS232.
 *
 * @param volts voltage to set
 * @param type power supply type (0 for Genesys, 1 for ZERO-UP)
 */

void tdklambda_setvoltage(f32 volts, u32 type);

/** @} TDKLambda */


#endif // __ECU_TDKLAMBDA_H__

