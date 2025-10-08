#include "kernel/types.h"
#include "user/user.h"
#include "kernel/pstat.h"

int
main(int argc, char *argv[])
{
    if(argc < 2){
        printf("Usage: time1 command [args...]\n");
        exit(1);
    }

    int retime;
    struct rusage ru;

    int pid = fork();
    if(pid < 0){
        printf("fork failed\n");
        exit(1);
    }

    if(pid == 0){
        exec(argv[1], argv+1);
        printf("exec failed\n");
        exit(1);
    } else {
        if(wait2(&retime, &ru) < 0){
            printf("wait2 failed\n");
            exit(1);
        }

        int elapsed = retime;
        int cpu = ru.cputime;
        int percent = (elapsed > 0) ? (cpu * 100 / elapsed) : 0;

        printf("elapsed time: %d ticks, cpu time: %d ticks, %d%% CPU\n",
               elapsed, cpu, percent);
    }

    exit(0);
}
