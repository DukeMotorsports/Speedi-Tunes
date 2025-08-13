/* prex implementations for pthread types, for inclusion in sys/types.h */

#ifndef _PREX_PTHREADTYPES_H
#define _PREX_PTHREADTYPES_H
#ifndef KERNEL
#include <sys/futex.h>

typedef struct pthread_attr {
	int sched_priority;
	int sched_policy;
	int detached;
	unsigned stacktype;	/* MEM_NORMAL or MEM_FAST */
	unsigned long stacksize;
	unsigned long magic;
	char name[12];
	const void *key;	/* REVISIT: do keys better! */
} pthread_attr_t;

typedef struct pthread_mutex {
	/*
	 * 0			=> unlocked
	 * tid			=> locked
	 * tid | FUTEX_WAITERS	=> locked with waiters
	 */
	futex_t futex;
	unsigned long count;
} pthread_mutex_t;

typedef struct pthread_cond {
	pthread_mutex_t lock;
	pthread_mutex_t *mutex;
	futex_t futex;
	int wait;
	int signal;
} pthread_cond_t;

typedef unsigned long	pthread_condattr_t;
typedef unsigned long	pthread_key_t;

typedef struct pthread_mutexattr {
	unsigned long magic;
	int type;
} pthread_mutexattr_t;

typedef unsigned long	pthread_once_t;
typedef unsigned long	pthread_rwlock_t;
typedef unsigned long	pthread_rwlockattr_t;

struct pthread_info;
typedef struct pthread_info* pthread_t;

#endif /* KERNEL */
#endif /* !_PREX_PTHREADTYPES_H */
