#include "types.h"
#include "defs.h"
#include "spinlock.h"
#include "syscall_counter.h"

struct {
    struct spinlock lock;
    int total_syscalls;
} syscall_counter;
