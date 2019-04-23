include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>

int main()
{
    pid_t pid;
    if((pid = fork()) < 0)
    {
        perror("fork error");
    }
    else if(0 == pid)
    {
        //在父进程返回之前，子进程状态为僵尸进程
        printf("child pid is %ld\n", getpid());   
        exit(0);
    }

    sleep(20);   
    exit(0);
}
