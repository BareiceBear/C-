//int waitpid(pid_t pid, int *statloc, int options)
//waitpid提供一个wait的非阻塞版本，返回终止子进程的进程ID
//通过WUNTRACED和WCONTINUED选项作业控制
//其参数pid
//1 == pid 等待任意子进程
//0 < pid 等待进程ID与pid相等的子进程
//0 == pid 等待组ID等于调用进程组ID的任一子进程
//-1 > pid 等待组ID等于pid绝对值的任一子进程
//option参数
//WNOHANG  若由pid指定的子进程不是立即可用，则不堵塞，返回0
//WUNTRACED 
//WCONTINUED 
//若指定的进程或进程组不存在，或参数pid指定的进程不是调用进程的子进程，则有可能出错

#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>    //exit
#include <stdio.h>

int main()
{
    pid_t pid;

    if((pid = fork()) < 0)
    {
        perror("fork error");
    }
    else if(0 == pid)       //第一个子进程进入
    {
        if((pid = fork()) < 0)
        {
            perror("fork error");
        }
        else if(pid > 0)       //第一个子进程退出
        {
            printf("first child, pid = %ld\n", (long)getpid());
            exit(0);
        }
    
        sleep(3);              //第二个子进程
        printf("second child, parent pid = %ld\n", (long)getppid());
        exit(0);
    }

    if(waitpid(pid, NULL, 0) != pid)   //父进程在这里堵塞
        perror("waitpid error");

    printf("origin pid = %ld\n", (long)getpid());
    exit(0);
}