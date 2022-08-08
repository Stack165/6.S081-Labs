#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

#define readflag 0
#define writeflag 1

void digui(int pd[])
{
    int n = 0;
    int p = 0;
    int pr[2] = {0};
    close(pd[writeflag]);
    if (read(pd[readflag], &p, sizeof(int)) == 0)
    {
        exit(0);
    };
    pipe(pr);
    if (fork() == 0)
    {
        digui(pr);
    }
    else
    {
        close(pr[readflag]);
        printf("prime %d\n", p);
        while (read(pd[readflag], &n, sizeof(int)) != 0)
        {
            if (n % p != 0)
            {
                write(pr[writeflag], &n, sizeof(int));
            }
        }
        close(pr[writeflag]);
        wait((int *)0);
        exit(0);
    }
}

int main(int argc, char *argv[])
{
    int pd[2] = {0};
    pipe(pd);
    if (fork() == 0)
    {
        digui(pd);
    }
    else
    {
        close(pd[readflag]);
        for (int i = 2; i < 36; i++)
        {
            write(pd[writeflag], &i, sizeof(int));
        }
        close(pd[writeflag]);
        wait((int *)0);
    }
    exit(0);
}