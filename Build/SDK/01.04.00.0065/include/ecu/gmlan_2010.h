#ifndef __ECU_GMLAN_2010_H__
#define __ECU_GMLAN_2010_H__

#include <ecu/types.h>

/**
 * @addtogroup GMLAN2010
 * @{
 * @project module
 */

/**
 * @fn bool gmlan_2010_init(s32 main_bus, s32 powertrain_bus)
 * @arg ScriptName Init
 */
__warn_unused_result bool gmlan_2010_init(u32 main_bus, u32 powertrain_bus);

/**
 * @fn void gmlan_2010_process(f32 a, f32 b, f32 c, f32 d, f32 e, bool f, bool g, bool h, bool i, bool j, bool k, u32 l, u32 m)
 * @arg ScriptName Process
 */
void gmlan_2010_process(f32, f32, f32, f32, f32, bool, bool, bool, bool, bool, bool, u32, u32);

/**
 * @fn u32 gmlan_2010_get(s32 idx)
 * @arg ScriptName Get
 */
u32 gmlan_2010_get(u32 idx);

/** @} GMLAN2010 */

#endif /* __ECU_GMLAN_2010_H__ */

