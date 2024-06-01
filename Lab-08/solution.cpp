#include <iostream>
#include <string>
using namespace std;

int arr[20]={1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};

void SUM(){
    int sum=0;
    for(int i=0; i<20; i++)
        sum+=arr[i];
    cout<<"Sum of all elements: "<<sum<<endl;
    pthread_exit(NULL);
}

void PRODUCT(){
    long int product=1;
    for(int i=0; i<20; i++)
        product*=arr[i];
    cout<<"Product of all elements: "<<product<<endl;
    pthread_exit(NULL);
}

void SEARCH(){
    int num;
    cout<<"Enter a number to search: ";
    cin>>num;
    for(int i=0; i<20; i++){
        if(arr[i]==num){
            cout<<"Number found at index: "<<i<<endl;
            return;
        }
    }
    cout<<"Number not found!"<<endl;
    pthread_exit(NULL);
}

int main(){

    pthread_t threads[3];

    pthread_create(&threads[0], NULL, (void*(*)(void*))SUM, NULL);
    pthread_detach(threads[0]);

    pthread_create(&threads[1], NULL, (void*(*)(void*))PRODUCT, NULL);
    pthread_detach(threads[1]);

    pthread_create(&threads[2], NULL, (void*(*)(void*))SEARCH, NULL);
    pthread_detach(threads[2]);
    return 0;
}