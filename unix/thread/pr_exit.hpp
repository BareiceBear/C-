//WIFEXITED(status)  正常返回则为真  WEXITSTATUS获取
//WIFSIGNALED(status) 异常终止子程序返回时为真   WTERMSIG获取
//WIFSTOPPED（status) 当前暂停子进程的返回的状态  WSTOPSIG获取
//WIFCONTINUED(status) 作业控制暂停后已经继续的子进程返回了状态  

#include <sys/wait.h>
#include <stdio.h>

void pr_exit(int status)
{
    if(WIFEXITED(status))
    {
        printf("normal termination, exit status = %d\n", WEXITSTATUS(status));
    }
    else if(WIFSIGNALED(status))
    {
        printf("abnormal termination, signal number = %d%s\n", 
                WTERMSIG(status),
#ifdef WCOREDUMP
                WCOREDUMP(status) ? "(core file generated)" : "");
#else
                "");
#endif
    }
    else if(WIFSTOPPED(status))
    {
        printf("child stopped, signal number = %d\n", WSTOPSIG(status));
    }
}