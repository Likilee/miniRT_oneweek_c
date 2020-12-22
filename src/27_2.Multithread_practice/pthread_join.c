#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

// 쓰레드 함수
// 1초를 기다린후 아규먼트^2 을 리턴한다.
void *t_function(void *data)
{
    int num = *((int *)data);
    printf("num %d\n", num);
    sleep(1);
    return (void *)(num*num);
}

int main()
{
    pthread_t p_thread;
    int thr_id;
    int status;
    int a = 100;

    thr_id = pthread_create(&p_thread, NULL, t_function, (void *)&a);
    if (thr_id < 0)
    {
        perror("thread create error : ");
        exit(0);
    }
    // 쓰레드 식별자 p_thread 가 종료되길 기다렸다가
    // 종료리턴값을 가져온다.
    pthread_join(p_thread, (void *)&status);
    printf("thread join : %d\n", status);

    return 0;
}
