#include "types.h"
#include "stat.h"
#include "user.h"

int
main(int argc, char *argv[])
{
    int i;
    int pid;
    int start;
    int count = 0;

    for(i = 0; i < 30; i++){
        pid = fork();

        if(pid < 0){
            printf(2, "gamer: fork failed\n");
            break;
        }

        if(pid == 0){
            start = uptime();

            while(uptime() - start < 100){
                count++;
            }
            
            printf(1, "Child PID %d finished\n", getpid());
            exit();
        }

        sleep(20);
    }

    while(wait() > 0){
    }

    printf(1, "Gamer completed all children\n");
    exit();
}
