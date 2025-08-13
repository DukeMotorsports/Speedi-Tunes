#ifdef DEBUG
#include <verbose.h>
#else
#warning verbose disabled
#define VERBOSE(...) do {} while (0)
#define TVERBOSE_INIT(...) do {} while (0)
#define TVERBOSE(...) do {} while (0)
#define __CVERBOSE(...) do {} while (0)
#endif
