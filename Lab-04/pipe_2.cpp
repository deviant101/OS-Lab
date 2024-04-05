#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <sys/wait.h>

using namespace std ;
int main(){
    int Parent_PID=getpid();

    pid_t childpid;
    int input=0;
    cout<<"Enter times : ";
    cin>>input;

    int numArray[20]={1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};
    for(int i=0; i<input; ++i){
        childpid = fork();
        if(childpid==-1)
            cout<<"Error in child creation"<<endl;
        else if(childpid==0){
            cout<<"Child"<<endl;
            int max;
            for(int i=0; i<20; ++i){
                //find max number in the numArray
                max = numArray[i];
                for(int j=i+1; j<20; ++j){
                    if(numArray[j]>max){
                        max = numArray[j];
                    }
                }
            }
            exit(max);
        }
    }
    //Reamining code is for parent process
    if(getpid()==Parent_PID){
        cout<<"Parent process"<<endl;
        int status;
        wait(&status);
        int res=WEXITSTATUS(status);
        cout<<"this is parent and recieved : "<<res<<endl;
    }
    
return 0;
}