#include <iostream>
#include <thread>
using namespace std;

int Array[30]={1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30};

void calSum(){

    int sum=0;
    for(int i=0; i<30; i++){
        sum+=Array[i];
    }
    cout<<"Sum: "<<sum<<endl;
    pthread_exit( (void*) sum );

    
}

void calMul(){

    int mul=1;
    for(int i=0; i<30; i++){
        mul*=Array[i];
    }
    cout<<"Mul: "<<mul<<endl;
    pthread_exit ( (void*) mul);

}

int main(){

    pthread_t thread1,thread2;

    pthread_create (&thread1,NULL,(void* (*)(void*))calSum, NULL);
    pthread_create (&thread2,NULL,(void* (*)(void*))calMul, NULL);

    // int sum=0;
    // int mul=0;
    void* status1;
    void* status2;


    pthread_join (thread1,&status1);
    pthread_join (thread2,&status2);

    // sum=(int)status1;
    // mul=(int)status2;

    // cout<<"Sum: "<<sum<<endl<<"Mul: "<<mul<<"\n";
    printf("In main thread1 returned value is %ld \n", (int *) status1);
    printf("In main thread1 returned value is %ld \n", (int *) status2);

    return 0;
}