#include "types.h"
#include "stat.h"
#include "user.h"

int main(int argc, char *argv[]) {
    int n = countsyscalls();
    printf(1, "Number of system calls made by this process: %d\n", n);
    exit();
}
