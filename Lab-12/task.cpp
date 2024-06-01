#include <iostream>
#include <stdlib.h>
#include <signal.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
using namespace std;

sem_t sem;
int value=1;

void *crossBridge(void *){

    cout<<"Trying to cross the bridge"<<endl;
    
    sem_wait(&sem);
    cout<<"Now car no "<<value<<" is crossing the bridge"<<endl;
    sleep(2);
    sem_post(&sem);
    
    cout<<"car no "<<value++<<" has crossed the bridge"<<endl;
    return NULL;
}


int main(){

    sem_init(&sem, 0, 3);
    pthread_t thread[15];
    for(int i=0; i<15; i++){
        pthread_create(&thread[i], NULL, crossBridge, NULL);
    }

    for(int i=0; i<15; ++i){
        pthread_join(thread[i], NULL);
    }

    return 0;
}