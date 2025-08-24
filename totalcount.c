#include "types.h"
#include "user.h"

int main(int argc, char *argv[]) {
    printf(1, "Total syscalls made by all processes: %d\n", totalcount());
    exit();
}
