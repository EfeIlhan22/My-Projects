#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>

#define NUM_CUSTOMERS 10  // Total number of customers that will visit the barbershop
#define NUM_CHAIRS 3      // Number of chairs in the waiting room

// Semaphores and mutex
sem_t waitingChairs;  // Controls access to the waiting chairs
sem_t barberChair;    // Ensures mutual exclusion to the barber chair
sem_t barberSleep;    // Used to wake the barber up if he is sleeping

pthread_mutex_t mutex;  // Mutex for modifying the result array
char results[NUM_CUSTOMERS];  // Results array to store '+' or '-'

void* customer(void* num);
void* barber(void* arg);
void balk(int customerNumber);
void getHairCut(int customerNumber);
void cutHair();

int main(int argc, char *argv[]) {
    pthread_t btid;
    pthread_t ctid[NUM_CUSTOMERS];
    long i;

    // Initialize semaphores and mutex
    sem_init(&waitingChairs, 0, NUM_CHAIRS);
    sem_init(&barberChair, 0, 1);
    sem_init(&barberSleep, 0, 0);
    pthread_mutex_init(&mutex, NULL);
    // Initialize result array
    for (i = 0; i < NUM_CUSTOMERS; i++) {
        results[i] = '-';
    }

    // Create barber thread
    pthread_create(&btid, NULL, barber, NULL);
    // Create customer threads
    for (i = 0; i < NUM_CUSTOMERS; i++) {
    pthread_create(&ctid[i], NULL, customer, (void*)i);
    }
    // Wait for all customer threads to finish
    for (i = 0; i < NUM_CUSTOMERS; i++) {
    pthread_join(ctid[i], NULL);
    sleep(1);
    }
    // Cancel barber thread after all customers leaved you need to do that otherwise barber will be in infinite loop  (Hint: use pthread_cancel and pthread_join)
    pthread_cancel(btid);
    pthread_join(btid, NULL);
    // Print results
    printf("\nCustomer Results:\n");
    for (i = 0; i < NUM_CUSTOMERS; i++) {
        printf("Customer %ld %c\n", i + 1, results[i]);
    }

    // Cleanup semaphores and mutex
    sem_destroy(&waitingChairs);
    sem_destroy(&barberChair);
    sem_destroy(&barberSleep);
    pthread_mutex_destroy(&mutex);
    return 0;
}

void* barber(void* data) {
    // Works until all the customers leave the barbershop
    while (1) {
        // Wait for a customer to wake up the barber
    sem_wait(&barberSleep);
    cutHair();
    // Release the barber chair when done
    sem_post(&barberChair);
    }
}

void* customer(void* num) {
    int customerNumber = (int)(intptr_t)num;
    // Try to get a waiting chair (Hint: use sem_trywait)
if(sem_trywait(&waitingChairs) == 0) {
    printf("Customer %d sits on chair and waiting \n",customerNumber);
        // Signal the barber if needed, then wait for the barber chair
    sem_post(&barberSleep);
    sem_wait(&barberChair);

        // The customer is getting a haircut
    getHairCut(customerNumber);
        // Release a waiting chair when done
    sem_post(&barberChair);
    sem_post(&waitingChairs);
        // Update results
    pthread_mutex_lock(&mutex);
    results[customerNumber] = '+';
    pthread_mutex_unlock(&mutex);

    } else {
    // Couldn't get a waiting chair, leave the barbershop
    balk(customerNumber);
    }


    return NULL;
}

void balk(int customerNumber) {
    printf("Customer %d leaves the shop as no chairs are available.\n", customerNumber);
    // update the results array as '-'
    pthread_mutex_lock(&mutex);
    results[customerNumber] = '-';
    pthread_mutex_unlock(&mutex);
}

void getHairCut(int customerNumber) {
    pthread_mutex_lock(&mutex);
    printf("Customer %d is getting a haircut.\n", customerNumber);
    sleep(3);  // Simulate the time taken for a haircut
    pthread_mutex_unlock(&mutex);
    printf("Customer %d is done with the haircut.\n", customerNumber);
}

void cutHair() {
    sleep(3);  // Simulate the time taken for a haircut
}
