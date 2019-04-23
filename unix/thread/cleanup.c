#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

//调用pthread_exit
//响应取消请求
//用非零excute参数调用pthread_cleanup_pop时
//将执行清理函数

static void cleanup(void *arg)
{
    printf("cleanup: %s\n", (char *)arg);
}

void *thr_fn1(void *arg)
{
    printf("thread 1 start\n");
    pthread_cleanup_push(cleanup, (void*)"thread 1 first handler");
    pthread_cleanup_push(cleanup, (void*)"thread 1 second handler");
    printf("thread 1 push complete\n");
    if(arg)
        return ((void*)1);
    pthread_cleanup_pop(0);
    pthread_cleanup_pop(0);
    return ((void*)1);
}

void *thr_fn2(void *arg)
{
    printf("thread 2 start\n");
    pthread_cleanup_push(cleanup, (void*)"thread 2 first handler");
    pthread_cleanup_push(cleanup, (void*)"thread 2 second handler");
    printf("thread 2 push complete\n");
    if(arg)
        pthread_exit((void*)2);
    pthread_cleanup_pop(0);
    pthread_cleanup_pop(0);
    pthread_exit((void*)2);
}

int main(void)
{
    int err;
    pthread_t tid1, tid2;
    void *tret;

    err = pthread_create(&tid1, NULL, thr_fn1, (void*)1);
    if(0 != err)
        perror("cant create thread");

    err = pthread_create(&tid2, NULL, thr_fn2, (void*)1);
    if(0 != err)
        perror("cant create thread");

    err = pthread_join(tid1, &tret);
    if(0 != err)
        perror("cant join with thread1");
    printf("thread1 exit code  %ld\n", (long)tret);
    err = pthread_join(tid2, &tret);
    if(0 != err)
        perror("cant join with thread2");
    printf("thread2 exit code  %ld\n", (long)tret);
    exit(0);
}