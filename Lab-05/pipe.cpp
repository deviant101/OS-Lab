#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <sys/wait.h>
#include <string.h>
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
    int voters=0;
    cout<<"Enter Number of voters : ";
    cin>>voters;
    
    for(int i=0; i<voters; ++i){
        childpid = fork();
        if(childpid==-1)
            cout<<"Error in child creation"<<endl;
        else if(childpid==0){
            // cout<<"Child"<<endl;
            close(fd[0]);
            srand(getpid());
            int random = rand()%3+1;
            // cout<<"Child writing to the pipe"<<endl;
            char buffer[sizeof(int)];
            sprintf(buffer, "%d", random);
            write(fd[1], &buffer, sizeof(buffer));
            exit(0);
        }
    }
    //Reamining code is for parent process
    if(getpid()==Parent_PID){
        cout<<"Vote Results"<<endl;
        close (fd[1]);
        wait(NULL);
        int predArray[voters];
        // cout << "Parent reading from the pipe " <<endl;
        for(int i=0; i<voters; ++i){
            char buffer[sizeof(int)];
            read(fd[0], buffer, sizeof(buffer));
            predArray[i] = atoi(buffer);
        }
        int maxOccure = 0;
        int maxNumber = 0;
        for(int i=0; i<voters; ++i){
            int times = 0;
            for(int j=0; j<voters; ++j){
                if(predArray[i]==predArray[j]){
                    times++;
                }
            }
            if(times > maxOccure){
                maxOccure = times;
                maxNumber = predArray[i];
            }
        }
        //print votes for each candidate
        for(int i=1; i<=3; i++){
            int count=0;
            for(int j=0; j<voters; j++){
                if(predArray[j]==i){
                    count++;
                }
            }
            cout<<"Candidate "<<(char)('A' + i-1)<<": "<<count<<" votes"<<endl;
        }
        if(maxNumber==1){
            cout<<"Winner: Candidate A"<<endl;
        }
        else if(maxNumber==2){
            cout<<"Winner: Candidate B"<<endl;
        }
        else if(maxNumber==3){
            cout<<"Winner: Candidate C"<<endl;
        }

        exit(0);
    }
    
return 0;
}