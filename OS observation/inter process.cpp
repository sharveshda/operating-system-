#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
int main() {
    key_t key = ftok("shmfile", 65);
    int shmid = shmget(key, 1024, 0666 | IPC_CREAT);
    char *shared_memory = (char *)shmat(shmid, NULL, 0);
    if (fork() == 0) {  
        strcpy(shared_memory, "Hello from child!");
        shmdt(shared_memory);
    } else {            
        wait(NULL);
        printf("Parent read: %s\n", shared_memory);
        shmdt(shared_memory);
        shmctl(shmid, IPC_RMID, NULL);
    }
    return 0;
}

