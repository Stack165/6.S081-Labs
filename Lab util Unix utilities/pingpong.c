#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[]) {
    int p1[2] = {0}; //f - > c
    int p2[2] = {0}; // c - > f
    char buf[1] = "!";
    pipe(p1);
    pipe(p2);
    int pid = fork();

    if (pid == 0) {
        close(p1[1]);
        close(p2[0]);
        read(p1[0],buf,1);
        printf("%d: received ping\n",pid);
        write(p2[1],buf,1);
        close(p1[0]);
        close(p2[1]);
    } else {
        close(p1[0]);
        close(p2[1]);
        write(p1[1],buf,1);
        read(p2[0],buf,1);
        printf("%d: received pong\n",pid);
        close(p1[1]);
        close(p2[0]);
    }
    exit(0);
}