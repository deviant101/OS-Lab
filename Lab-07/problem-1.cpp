#include <iostream>
#include <thread>
using namespace std;

void printMsg() {
    cout<<"Hello, I am thread and my ID is "<<pthread_self()<<endl;
}

int main(){
    int n;
    cout<<"Enter the number of threads: ";
    cin>>n;

    pthread_t threads[n];

    for (int i=0; i<n; i++){
        pthread_create (&threads[i],NULL,(void* (*)(void*))printMsg, NULL);
    }
    for(int i=0; i<n; i++){
        pthread_join(threads[i],NULL);
    }

    return 0;
}