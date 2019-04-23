#include "pr_exit.hpp"
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>    //exit

int main()
{
    pid_t pid;
    int status;

    if((pid == fork() < 0))
        perror("fork error");
    else if(0 == pid)
        exit(7);

    if(wait(&status) != pid)
        perror("wait error");
    pr_exit(status);

    if((pid == fork()) < 0)
        perror("fork error");
    else if(0 == pid)
        abort();

    if(wait(&status) != pid)
        perror("wait error");
    pr_exit(status);

    if((pid == fork()) < 0)
        perror("fork error");
    else if(0 == pid)
        status /= 0;

    if(wait(&status) != pid)
        perror("wait error");
    pr_exit(status);

    exit(0);
}

