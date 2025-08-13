#ifndef __ECU_TC_H__
#define __ECU_TC_H__

#include <ecu/types.h>

/**
 * @addtogroup TC
 * @{
 */

/**
 * @fn f32 tc_calculate_tp(f32 map, f32 flow)
 * @arg ScriptName TP
 *
 * @brief Calculate throttle position from manifold pressure & mass flow.
 *
 * @param map manifold pressure
 * @param flow mass flow
 */
f32 tc_calculate_tp(f32, f32);

/**
 * @fn f32 tc_calculate_co()
 * @arg ScriptName CO
 *
 * @brief Calculate mass flow through a manifold crossover pipe.
 */
f32 tc_calculate_co(void);

/** @} TC */

#endif /* __ECU_TC_H__ */
