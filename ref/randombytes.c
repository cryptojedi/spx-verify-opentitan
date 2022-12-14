/*
This code was taken from the SPHINCS reference implementation and is public domain.
*/

#include <fcntl.h>
#include <unistd.h>

#include "randombytes.h"

static int fd = -1;

void randombytes(unsigned char *x, unsigned long xlen)
{
    unsigned long i;
    ssize_t r;

    if (fd == -1) {
        for (;;) {
            fd = open("/dev/urandom", O_RDONLY);
            if (fd != -1) {
                break;
            }
            sleep(1);
        }
    }

    while (xlen > 0) {
        if (xlen < 1048576) {
            i = xlen;
        }
        else {
            i = 1048576;
        }

        r = read(fd, x, i);
        if (r < 1) {
            sleep(1);
            continue;
        }

        x += (unsigned long)r;
        xlen -= (unsigned long)r;
    }
}
