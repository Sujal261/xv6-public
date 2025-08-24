#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

int main(int argc, char *argv[]) {
    if(argc < 3){
        printf(2, "Usage: randfile <filename> <count>\n");
        exit();
    }

    char *filename = argv[1];
    int count = atoi(argv[2]);

    int fd = open(filename, O_CREATE | O_WRONLY);
    if(fd < 0){
        printf(2, "Error: cannot create file %s\n", filename);
        exit();
    }

    unsigned int seed = 123456789;
    for(int i = 0; i < count; i++){
        seed = seed * 1103515245 + 12345;
        int r = (seed / 65536) % 32768;

        char buf[16];
        int n = 0;
        int temp = r;
        if(temp == 0) {
            buf[n++] = '0';
        } else {
            char tmpbuf[16];
            int t = 0;
            while(temp > 0){
                tmpbuf[t++] = '0' + (temp % 10);
                temp /= 10;
            }
            // reverse
            for(int j = t-1; j >= 0; j--)
                buf[n++] = tmpbuf[j];
        }
        buf[n++] = '\n';

        write(fd, buf, n);
    }

    close(fd);
    printf(1, "File %s created with %d random numbers.\n", filename, count);
    exit();
}
