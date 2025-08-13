#ifndef __ECU_THREAD_H__
#define __ECU_THREAD_H__

#ifdef _ECU_SOURCE
typedef unsigned long	thread_t;

#else
#include <prex/types.h>

#endif

/*
 * Parameter for trigger_wait()
 */
#define TRIGGER_1S	(1<<0)
#define TRIGGER_500MS	(1<<1)
#define TRIGGER_200MS	(1<<2)
#define TRIGGER_100MS	(1<<3)
#define TRIGGER_50MS	(1<<4)
#define TRIGGER_20MS	(1<<5)
#define TRIGGER_10MS	(1<<6)
#define TRIGGER_5MS	(1<<7)
#define TRIGGER_2MS	(1<<8)
#define TRIGGER_1MS	(1<<9)

#define ecu_thread_t thread_t

extern thread_t ecu_thread_create(void (*thread)(void), const char *name,
				  int priority) __warn_unused_result;
extern void ecu_thread_terminate(void);
extern void ecu_thread_yield(void);
extern void ecu_thread_cancel(thread_t th);
extern void ecu_thread_join(thread_t th);
extern void ecu_thread_testcancel(void);
extern void ecu_run(void);

extern long trigger_wait(long mask);
extern long trigger_miss(thread_t th) __warn_unused_result;

#endif /* __ECU_THREAD_H__ */
