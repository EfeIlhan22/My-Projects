#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t empty;
sem_t full;
sem_t mutex;
int buffer[10]={0};
int in=0;
int out=0;
void print_buffer(){
        printf("Buffer array : %d,%d,%d,%d,%d,%d,%d,%d,%d,%d \n",buffer[0],buffer[1],
        buffer[2],buffer[3],buffer[4],buffer[5],buffer[6],buffer[7],buffer[8],buffer[9]);
}
void* producer(){
    int item; 
    while (1) { 
        sem_wait(&empty);	//Wait if the buffer is full, or reduce the number of empty spaces by 1.
        sem_wait(&mutex);     //Get permission to enter the critical section.
        buffer[in]=1;
        in=(in+1)%10;
        print_buffer();
        sem_post(&mutex);    //Indicate that it exits the Critical Section.
        sem_post(&full);       //If there are any consumers waiting, wake up, or increase the number of full places in Buffer by 1.
        
        sleep(3);
}
}

void* consumer(){
    while (1) { 
        sem_wait(&full); 	//Wait if the buffer is empty, or reduce the number of full places by 1
        sem_wait(&mutex);     //Get permission to enter the critical section
        buffer[out]=0;
        out=(out+1)%10;
        print_buffer();
        sem_post(&mutex); 		//Indicate that it exits the Critical Section
        sem_post(&empty); 	//If there is a manufacturer waiting, wake up, or increase the number of empty    //spaces in Buffer by 1.
        sleep(3);
}
}

int main(){
    sem_init(&empty,0,10);
    sem_init(&full,0,0);
    sem_init(&mutex,0,1);
    pthread_t arr_prod[10];
    pthread_t arr_cons[10];
    for(int i=0 ;i<10;i++){
        pthread_create(&arr_prod[i],NULL,producer,NULL);
        pthread_create(&arr_cons[i],NULL,consumer,NULL);
    }
     for(int i=0 ;i<10;i++){
        pthread_join(arr_prod[i],NULL);
        pthread_join(arr_cons[i],NULL);

    }
}