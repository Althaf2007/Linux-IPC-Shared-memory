
#include <stdio.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <unistd.h>
int main() {
    int id = shmget(1234, 100, 0666 | IPC_CREAT);
    char *p = shmat(id, NULL, 0);

    if (fork() == 0) {
        printf("Child: %s\n", p);
    } else {
        sprintf(p, "Hello from Parent");
        wait(NULL);
    }

    shmdt(p);
    shmctl(id, IPC_RMID, NULL);

    return 0;
}

