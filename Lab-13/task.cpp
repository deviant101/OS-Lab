#include <iostream>
#include <stdlib.h>
#include <signal.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
using namespace std;

sem_t sem;
int value=1;

void *EAT(void *){

    // cout<<"Person "<<value<<" is entering the restaurant"<<endl;
    
    sem_wait(&sem);
    cout<<"Person "<<value<<" is eating"<<endl;
    sleep(2);
    sem_post(&sem);
    
    cout<<"Person "<<value++<<" is done eating"<<endl;
    return NULL;
}


int main(){

    sem_init(&sem, 0, 10);
    pthread_t thread[20];
    for(int i=0; i<20; i++){
        pthread_create(&thread[i], NULL, EAT, NULL);
    }

    for(int i=0; i<20; ++i){
        pthread_join(thread[i], NULL);
    }

    return 0;
}