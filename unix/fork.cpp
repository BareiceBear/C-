/*
fork()
调用一次，返回两次，父进程返回子进程ID，子进程返回0
子进程获取父进程数据空间，堆和栈的副本（写时复制），与父进程共享正文段
父进程的所有打开文件描述符都被复制到子进程
不保证父进程和子进程谁先执行
*/

#include <sys/types.h> //fork
#include <stdio.h>     //perror
#include <unistd.h>    //fork sleep
#include <stdlib.h>    //exit

int globval = 6;
char buf[] = "a write to stdout\n";

int main(void)
{
    int var;
    pid_t pid;

    var = 88;
    if(write(STDOUT_FILENO, buf, sizeof(buf) - 1) != sizeof(buf) - 1)  //sizeof是在编译时计算缓冲区长度（缓冲区用已知字符串初始化，长度固定）
        perror("write error");
    printf("before fork\n");

    if((pid = fork()) < 0)   
    {
        perror("fork error");
    }
    else if(0 == pid)
    {
        globval++;
        var++;
    }
    else
    {
        sleep(2);
    }
    
    printf("pid = %ld, glob = %d, var = %d\n", (long)getpid(), globval, var);
    exit(0);
}

/*
bearpaw@ubuntu:~/cpp/unix$ cat tmp.out   //这里输出两次 “before fork”，当fork执行时， buf仍在缓冲区中，跟随数据空间被复制到子进程
a write to stdout           
before fork
pid = 57845, glob = 7, var = 89
before fork
pid = 57844, glob = 6, var = 88
bearpaw@ubuntu:~/cpp/unix$ ./a.out
a write to stdout                       //如果标准输出连到终端设备，则为行缓冲，否则为全缓冲
before fork
pid = 57917, glob = 7, var = 89
pid = 57916, glob = 6, var = 88
*/