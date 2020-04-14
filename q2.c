//Print the sequence cbacba............

#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

//Global so that can be used in all functions
sem_t semaphore1;//a
sem_t semaphore2;//b
sem_t semaphore3;//c

void* a (void* param) {  
  	while (1) {
     sem_wait(&semaphore1);

     printf("a");

     sem_post(&semaphore3);   	
    }
}

void* b (void* param) {  
   while (1) {
    sem_wait(&semaphore2);

    printf("b");

    sem_post(&semaphore1);
   }
}

void *c (void* param) {
 while (1) {
	 sem_wait(&semaphore3);

   printf("c");

   sem_post(&semaphore2);
  }
}

int main() {

  pthread_t id1;
  pthread_t id2; 
  pthread_t id3;

  //Need to initialize before creating threads 
  sem_init ( &semaphore1, 0, 0 );//a  
  sem_init ( &semaphore2, 0, 0 );//b
  sem_init ( &semaphore3, 0, 1 );//c  

  pthread_create ( &id1, NULL, &a, NULL );
  pthread_create ( &id2, NULL, &b, NULL );
  pthread_create ( &id3, NULL, &c, NULL );

  pthread_join ( id1, NULL );
  pthread_join ( id2, NULL );
  pthread_join ( id3, NULL );
}