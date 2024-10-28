#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t mutex1;
pthread_mutex_t mutex2;

void* thread1_function(void* arg) {
    printf("Thread 1: Locking mutex1\n");
    pthread_mutex_lock(&mutex1);
    sleep(1); 
    printf("Thread 1: Locking mutex2\n");
    pthread_mutex_lock(&mutex2);
    printf("Thread 1: Both mutexes locked\n");
    pthread_mutex_unlock(&mutex2);
    pthread_mutex_unlock(&mutex1);
    return NULL;
}

void* thread2_function(void* arg) {
    printf("Thread 2: Locking mutex2\n");
    pthread_mutex_lock(&mutex2);
    sleep(1);
    printf("Thread 2: Locking mutex1\n");
    pthread_mutex_lock(&mutex1);
    printf("Thread 2: Both mutexes locked\n");
    pthread_mutex_unlock(&mutex1);
    pthread_mutex_unlock(&mutex2);
    return NULL;
}

int main() {
    pthread_t thread1, thread2;

    pthread_mutex_init(&mutex1, NULL);
    pthread_mutex_init(&mutex2, NULL);

    pthread_create(&thread1, NULL, thread1_function, NULL);
    pthread_create(&thread2, NULL, thread2_function, NULL);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    pthread_mutex_destroy(&mutex2);

    return 0;
}
