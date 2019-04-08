/*
struct file
{
    unsigned short f_mode;
    unsigned short f_flags;
    unsigned short f_count;
    struct m_inode *f_inode;
    off_t f_pos;
}
*/

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>

char MSG_TRY[] = "try again!\n";

int main()
{
    char buffer[10];
    int len = 0;
    int fd = -1;

    int flags = fcntl(STDIN_FILENO, F_GETFL);   //获取文件描述符对应的文件的标志位
    if(-1 == flags)
    {
        perror("fcntl get");
        exit(1);
    }

    if(flags & O_RDONLY)
    {
        printf("O_RDWR\n");
    }

    flags |= O_NONBLOCK;

    if(-1 == fcntl(STDIN_FILENO, F_SETFL, flags))
    {
        perror("fcntl set");
        exit(1);
    }

    while(1)
    {
        len = read(STDIN_FILENO, buffer, 10);
        if(len < 0)
        {
            if(EAGAIN == errno)
            {
                write(STDOUT_FILENO, MSG_TRY, strlen(MSG_TRY));
                sleep(1);
            }
            else
            {
                perror("read");
                exit(1);
            }
        }
        else
        {
            break;
        }
    }

    write(STDOUT_FILENO, buffer, len);
    return 0;
}