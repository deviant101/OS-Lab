#include<stdio.h>
#include<unistd.h>
#include<iostream>
#include<sys/wait.h>

using namespace std;

int main(){

    for(int i=0; i<6; ++i){

        pid_t pid=fork();
        if(pid==0){
            cout<<" Hello World"<<endl;
        }
    }

    return 0;
}