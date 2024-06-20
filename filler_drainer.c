/******************************************************************************

Welcome to GDB Online.
  GDB online is an online compiler and debugger tool for C, C++, Python, PHP, Ruby, 
  C#, OCaml, VB, Perl, Swift, Prolog, Javascript, Pascal, COBOL, HTML, CSS, JS
  Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <stdio.h>
#include <pthread.h>

int current_water_level=0;
pthread_mutex_t counter_mutex = PTHREAD_MUTEX_INITIALIZER; // Mutex for protecting the counter

void* filler(void* arg){
    if(current_water_level <=20){
        pthread_mutex_lock(&counter_mutex); // Lock the mutex before accessing the shared resource
        while(current_water_level<100){
        current_water_level+=10;
        printf("filler water level= %d\n",current_water_level);
        pthread_mutex_unlock(&counter_mutex); // Unlock the mutex after accessing the shared resource
    }
    }
    pthread_exit(NULL);
}

void* drainer(void* arg){
        if(current_water_level>0){
            pthread_mutex_lock(&counter_mutex); // Lock the mutex before accessing the shared resource
            current_water_level-=10;
            printf("drainer water level= %d\n",current_water_level);
            pthread_mutex_unlock(&counter_mutex); // Unlock the mutex after accessing the shared resource
        }
    pthread_exit(NULL);
}


int main()
{
   pthread_t t1,t2;
   for(int i=0;i<100;i++){
    pthread_create(&t1,NULL,filler,NULL);
    pthread_create(&t1,NULL,drainer,NULL);
    pthread_join(t1,NULL);
    pthread_join(t2,NULL);
   }
   
   pthread_mutex_destroy(&counter_mutex);
    return 0;
}



