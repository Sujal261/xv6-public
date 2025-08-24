#include "types.h"
#include "user.h"

int
main(void)
{
    printf(1, "Total syscalls so far: %d\n", totalcount());
    
    getpid();
    getpid();
    getpid();
    
    printf(1, "Total syscalls after 3 more calls: %d\n", totalcount());

    exit();
}
