#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(void)
{
    int p[2];
    char buf[5];
    int bytes;

    pipe(p);
    if (fork() == 0) {
        // child process
        bytes = read(p[0], buf, sizeof(buf));
        if (bytes > 0)
            fprintf(1, "%d: received %s\n", getpid(), buf);
        close(p[0]);
        write(p[1], "pong\n", 5);
        close(p[1]);
    } else {
        // parent process
        write(p[1], "ping\n", 5);
        close(p[1]);
        wait(0);
        bytes = read(p[0], buf, sizeof(buf));
        if (bytes > 0)
            fprintf(1, "%d: received %s\n", getpid(), buf);
        close(p[0]);
    }
    exit(0);
}