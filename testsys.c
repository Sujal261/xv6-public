#include "types.h"
#include "stat.h"
#include "user.h"

int main() {
    getpid();   // syscall 1
    uptime();   // syscall 2
    getpid();   // syscall 3
    printf(1, "Number of syscalls made by this process: %d\n", countsyscalls());
    exit();
}
