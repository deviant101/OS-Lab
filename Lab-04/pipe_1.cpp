#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <sys/wait.h>
using namespace std ;
int main(){
    int Parent_PID=getpid();

    int fd[2];
    pid_t childpid;
    int result = pipe(fd);
    if (result<0){
        cout<<"Error while creating file";
        exit (1);
    }
    int input=0;
    cout<<"Enter times : ";
    cin>>input;
    
    for(int i=0; i<input; ++i){
        childpid = fork();
        if(childpid==-1)
            cout<<"Error in child creation"<<endl;
        else if(childpid==0){
            cout<<"Child"<<endl;
            close(fd[0]);
            srand(getpid());
            int random = rand()%10+1;
            // cout<<"Child writing to the pipe"<<endl;
            char buffer[sizeof(int)];
            sprintf(buffer, "%d", random);
            write(fd[1], &buffer, sizeof(buffer));
            exit(0);
        }
    }
    //Reamining code is for parent process
    if(getpid()==Parent_PID){
        cout<<"Parent process"<<endl;
        close (fd[1]);
        wait(NULL);
        int predArray[input];
        // cout << "Parent reading from the pipe " <<endl;
        for(int i=0; i<input; ++i){
            char buffer[sizeof(int)];
            read(fd[0], buffer, sizeof(buffer));
            predArray[i] = atoi(buffer);
        }
        for(int i=0; i<input; ++i){
            cout << predArray[i] << " ";
        }
        int maxOccure = 0;
        int maxNumber = 0;
        for(int i=0; i<input; ++i){
            int times = 0;
            for(int j=0; j<input; ++j){
                if(predArray[i]==predArray[j]){
                    times++;
                }
            }
            if(times > maxOccure){
                maxOccure = times;
                maxNumber = predArray[i];
            }
        }
        cout << "Max times number: " << maxNumber << endl;

        exit(0);
    }
    
return 0;
}