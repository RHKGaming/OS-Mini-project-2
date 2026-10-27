
#include "types.h"
#include "stat.h"
#include "user.h"

#define NUM_CHILDREN 3

int
main(int argc, char *argv[])
{
    int i;
    int pid;
    int tickets[NUM_CHILDREN];
    int numChildren;

    // Default ticket values.
    tickets[0] = 30;
    tickets[1] = 20;
    tickets[2] = 10;

    numChildren = NUM_CHILDREN;

    // Accept up to three ticket values from the command line.
    if(argc > NUM_CHILDREN + 1){
        printf(2, "Usage: schedtest [tickets...]\n");
        exit();
    }

    // Replace defaults with supplied ticket values.
    if(argc > 1){
        numChildren = argc - 1;

        for(i = 0; i < numChildren; i++){
            tickets[i] = atoi(argv[i + 1]);

            if(tickets[i] <= 0){
                printf(2, "schedtest: tickets must be positive\n");
                exit();
            }
        }
    }

    printf(1, "Scheduler test starting with %d children\n",
           numChildren);

    // Create CPU-bound child processes.
    for(i = 0; i < numChildren; i++){
        pid = fork();

        if(pid < 0){
            printf(2, "schedtest: fork failed\n");
            exit();
        }

        if(pid == 0){
            volatile uint work = 0;

            // Set this child's ticket count.
            if(settickets(tickets[i]) < 0){
                printf(2, "schedtest: settickets failed\n");
                exit();
            }

            printf(1, "Child PID %d running with %d tickets\n",
                   getpid(), tickets[i]);

            // Run indefinitely so store can measure CPU ticks.
            for(;;){
                work++;
            }
        }
    }

    // The parent exits, leaving the children running.
    printf(1, "Scheduler test started; run store twice to measure ticks\n");
    exit();
}
