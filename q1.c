#include <stdio.h>       //For c lang
#include <stdlib.h>
#include <sys/types.h>
#include <sys/shm.h>     //For shared memory
#include <errno.h>
#include <semaphore.h>   //For sem_wait and sem_post
#include <fcntl.h>

struct buffer{
	int size;
    char mem[size]; 
};

buffer* b1 = NULL;
sem_t* sem1; 
sem_t* sem2;

int main(){

	// Shared mem for buffer created
	int shmid_buffer = shmget(101010, 1024, 0644|IPC_CREAT); 
    printf("Shmid_buffer : %d\n", shmid_buffer);

    if (shmid_buffer < 0){
        perror("Shared memory not created successfully\n");
        exit(0);
    }

    b1 = (buffer*) shmat(shmid_buffer, NULL, 0);

    if (b1 < 0){
        perror("Shared memory not attached successfully\n");
        exit(0);
    } 
    printf("Shared mem for buffer created\n");


   
    unsigned int N = 0;
    printf("Please enter the value for N\n");
    scanf("%u",&N);
    printf("value of N : %u\n", N);



    //Shared mem for sem1 created ----> Slots empty
    int shmid_sem1 = shmget(121212, 1024, 0644|IPC_CREAT); 
    printf("Shmid_sem1 : %d\n", shmid_sem1);

    if (shmid_sem1 < 0){
        perror("Shared memory not created successfully\n");
        exit(0);
    }

    sem1 = (sem_t*) shmat(shmid_sem1, NULL, 0);

    if (sem1 < 0){
        perror("Shared memory not attached successfully\n");
        exit(0);
    } 

    sem_open("sem1",O_CREAT|O_EXCL, 0644, N);
    sem_unlink("sem1");
    printf("Shared mem for sem1 created\n");





    //Shared mem for sem2 created ----> Slots full
    int shmid_sem2 = shmget(131313, 1024, 0644|IPC_CREAT); 
    printf("Shmid_sem2 : %d\n", shmid_sem2);

    if (shmid_sem2 < 0){
        perror("Shared memory not created successfully\n");
        exit(0);
    }

    sem2 = (sem_t*) shmat(shmid_sem2, NULL, 0);

    if (sem2 < 0){
        perror("Shared memory not attached successfully\n");
        exit(0);
    } 

    sem_open("sem2",O_CREAT|O_EXCL, 0644, 1);
    sem_unlink("sem2");
    printf("Shared mem for sem2 created\n");







	return 0;
}