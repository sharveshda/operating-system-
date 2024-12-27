#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define THREADS 5
sem_t mutex, writeBlock;
int readCount = 0;

void *reader(void *id) {
    sem_wait(&mutex);
    if (++readCount == 1) sem_wait(&writeBlock);
    sem_post(&mutex);

    printf("Reader %d is reading\n", *(int *)id);
    sleep(1);
    printf("Reader %d finished reading\n", *(int *)id);

    sem_wait(&mutex);
    if (--readCount == 0) sem_post(&writeBlock);
    sem_post(&mutex);
    return NULL;
}

void *writer(void *id) {
    sem_wait(&writeBlock);
    printf("Writer %d is writing\n", *(int *)id);
    sleep(1);
    printf("Writer %d finished writing\n", *(int *)id);
    sem_post(&writeBlock);
    return NULL;
}

int main() {
    pthread_t readers[THREADS], writers[THREADS];
    sem_init(&mutex, 0, 1);
    sem_init(&writeBlock, 0, 1);
    int ids[THREADS];

    for (int i = 0; i < THREADS; i++) {
        ids[i] = i + 1;
        pthread_create(&readers[i], NULL, reader, &ids[i]);
        pthread_create(&writers[i], NULL, writer, &ids[i]);
    }
    for (int i = 0; i < THREADS; i++) {
        pthread_join(readers[i], NULL);
        pthread_join(writers[i], NULL);
    }
    sem_destroy(&mutex);
    sem_destroy(&writeBlock);
    return 0;
}

