#ifndef __ECU_DEBUG_H__
#define __ECU_DEBUG_H__
#include <ecu/types.h>

/* Documentation concept is based on the easiest easy to parse version
 * of doxygen with some minor extensions.
 */

/**
 * @addtogroup Debug
 * @{
 * @project module
 */

/**
 * @fn void segfault(void)
 * @arg ScriptName segfault
 * @brief Simulate a segmentation fault
 * @return void
 * @code
 * // example usage
 * segfault();
 * @endcode
*/

static __inline void segfault(void)
{
	volatile u32* crash_p = 0;
	*crash_p; /* seg fault */
}

/** @} Debug */

#endif /* __ECU_DEBUG_H__ */
