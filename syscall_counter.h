#ifndef SYSCALL_COUNTER_H
#define SYSCALL_COUNTER_H

#include "spinlock.h"

extern struct {
    struct spinlock lock;
    int total_syscalls;
} syscall_counter;

#endif
