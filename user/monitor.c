#include "types.h"
#include "stat.h"
#include "user.h"
#include "pstat.h"

int
main(int argc, char *argv[])
{
    struct pstat ps;
    int interval;
    int samples;
    int i, j;

    if(argc != 3){
        printf(2, "Usage: monitor interval samples\n");
        exit();
    }

    interval = atoi(argv[1]);
    samples = atoi(argv[2]);

    if(interval <= 0 || samples <= 0){
        printf(2, "monitor: values must be positive\n");
        exit();
    }

    printf(1, "Time\tPID\tTickets\tTicks\n");

    for(i = 0; i < samples; i++){
        sleep(interval);

        if(getpinfo(&ps) < 0){
            printf(2, "monitor: getpinfo failed\n");
            exit();
        }

        int time = uptime();

        for(j = 0; j < NPROC; j++){
            if(ps.inuse[j]){
                printf(1, "%d\t%d\t%d\t%d\n",
                    time,
                    ps.pid[j],
                    ps.tickets[j],
                    ps.ticks[j]);
            }
        }
    }

    exit();
}
