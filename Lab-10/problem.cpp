#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
using namespace std;

// pthread_mutex_tmutex=PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex ;

int accountBalance=0;

void *withdraw(void *){

    pthread_mutex_lock(&mutex);

    cout<<"Current Account Balance: "<<accountBalance<<endl;
    while(1){
        if(accountBalance<10){
            continue;
        }
        else{
            accountBalance-=10;
            cout<<"Withdrawal successful"<<endl;
            break;
        }
    }
    cout<<"New Account balance: "<<accountBalance<<"\n\n";

    pthread_mutex_unlock(&mutex);


    return NULL;
}

void *deposit(void *){

    pthread_mutex_lock(&mutex);

    cout<<"Current Account Balance: "<<accountBalance<<endl;
    accountBalance+=(11);
    cout<<"New Account balance: "<<accountBalance<<"\n\n";

    pthread_mutex_unlock(&mutex);
    return NULL;
}

int main(){

    pthread_mutex_init(&mutex, NULL);
    pthread_t threads[4];

    pthread_create(&threads[0], NULL, deposit, NULL);
    pthread_create(&threads[1], NULL, deposit, NULL);
    pthread_create(&threads[2], NULL, withdraw, NULL);
    pthread_create(&threads[3], NULL, withdraw, NULL);

    for(int i=0; i<4; i++){
        pthread_join(threads[i], NULL);
    }
    // sleep(1);
    // cout<<"\nAccount balance: "<<accountBalance<<endl;

    pthread_mutex_destroy(&mutex);

    
    return 0;
}