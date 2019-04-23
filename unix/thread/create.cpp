#include <pthread.h>
#include <unistd.h>
#include <stdio.h>

void* thread1(void *arg)
{
    pthread_t tid = pthread_self();
    printf("thread id: (0x%1x)", (unsigned long)tid);
    return ((void*)1);
}

void* thread2(void *arg)
{
    pthread_t tid = pthread_self();
    printf("thread id: (0x%1x)", (unsigned long)tid);
    pthread_exit((void*)2);
}

int main()
{
    int err;
    pthread_t tid1 = 0, tid2 = 0;
    if(0 != (err = pthread_create(&tid1, NULL, thread1, NULL)))
        perror("create1 failed");

    if(0 != (err = pthread_create(&tid2, NULL, thread2, NULL)))
        perror("create2 failed");

    void *ret1 = nullptr, *ret2 = nullptr;
    if(0 == pthread_join(tid1, &ret1))
        printf("return1 value = %ld\n", (long)ret1);

    if(0 == pthread_join(tid2, &ret2))
        printf("return2 value = %ld\n", (long)ret2);

    return 0;
}