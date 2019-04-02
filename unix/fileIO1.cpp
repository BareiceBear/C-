#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

#define BUFFERSIZE 1024

//int open(const char*, int)
//int open(const char*, int, mode_t)
//int:必选 O_RDONLY O_WRONLY O_RDWR
//    可选 O_CREAT O_APPEND O_EXCL O_TRUNC O_NONBLOCK
//    O_EXCL与O_CREAT配合使用，当文件已存在时返回-1
//
//ssize_t read(int, void*, size_t)
//    读取size_t个字符，返回实际读取字符
//ssize_t write(int, const void*, size_t)
//    写入size_t个字符，对设备来说，实际写入字符可少于size_t

int main(int argc, char *argv[])
{
    if(argc != 3)
    {
	printf("usage:\nmycp src dst\n");
	return 1;
    }

    int srcfd = open(argv[1], O_RDONLY);
    if(-1 == srcfd)
    {
        perror("open src failed");
	return 1;
    }

    int dstfd = open(argv[2], O_CREAT | O_WRONLY | O_EXCL, 0666);
    if(-1 == dstfd)
    {
	perror("open dst failed");
	close(srcfd);
	return 1;
    }
    
    int len = 0;
    char buffer[BUFFERSIZE] = {0};

    while((len = read(srcfd, buffer, BUFFERSIZE)) > 0)
    {
        if(len != write(dstfd, buffer, len))
	{
	    perror("write error");
            close(srcfd);
            close(dstfd);	    
	    return 1;
	}
    }

    if(len < 0)
        perror("read error");

    close(srcfd);
    close(dstfd);

    return 0;
}
