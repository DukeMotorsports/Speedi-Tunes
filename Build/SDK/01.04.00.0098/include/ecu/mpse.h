#ifndef __ECU_MPSE_H__
#define __ECU_MPSE_H__

/**
 * @addtogroup MPSE
 * @{
 *
 */

/**
 * @fn f32 mpse_tmf(f32 map, f32 pup, f32 tup, f32 taf)
 * @arg ScriptName ThrottleMassFlow
 *
 * @brief Calculate throttle mass flow.
 *
 * @param map current manifold air pressure
 * @param pup air pressure upstream of throttle
 * @param tup air temperature upstream of throttle
 * @param taf throttle area factor
 */
f32 __warn_unused_result mpse_tmf(f32 map, f32 pup, f32 tup, f32 taf);

/**
 * @fn f32 mpse_prf(f32 pr)
 * @arg ScriptName PressureRatioFactor
 *
 * @brief Calculate pressure ratio factor.
 *
 * @param pr pressure ratio (0 to 1)
 */
f32 __warn_unused_result mpse_prf(f32 pr);

/**
 * @fn f32 mpse_solve(u32 n, f32 dt, f32 pup, f32 tup, f32 map, f32 mat, f32 taf, f32 mvol, f32 mafp, f32 mafe, f32 mafs, f32 k)
 * @arg ScriptName Solve
 *
 * @brief Solve the manifold pressure state equation.
 *
 * @param n number of steps
 * @param dt time step
 * @param pup air pressure upstream of throttle
 * @param tup air temperature upstream of throttle
 * @param map current estimated manifold air pressure
 * @param mat manifold air temperature
 * @param taf throttle area factor
 * @param mvol manifold volume
 * @param mafp mass flow into the engine
 * @param mafe extra mass flow into manifold (usually purge or crossover pipe)
 * @param mafs mass flow sensor value
 * @param k kalman gain
 */
f32 __warn_unused_result mpse_solve(u32 n, f32 dt, f32 pup, f32 tup, f32 map, f32 mat, f32 taf, f32 mvol, f32 mafp, f32 mafe, f32 mafs, f32 k);

/** @} MPSE */

#endif // __ECU_MPSE_H__

