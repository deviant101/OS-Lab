#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <sys/wait.h>
#include <sys/stat.h>
#include <string.h>
#include <fcntl.h> // Include the <fcntl.h> header file

using namespace std;
int main(){
    
    mkfifo("pipe_one", 0666);
    
    int fifo = open("pipe_one", O_RDWR);
    if(fifo < 0){
        cout<<"Error opening file";
    }
    else{
        cout<<"Inside1"<<endl;
        while(1){
            
            char str[256];
            cout<<"Entertext: ";
            cin>>str;
            write(fifo,str,sizeof(str));
            if(strcmp(str,"abort")==0)
                break;

            read(fifo,str,sizeof(str));
            cout<<str<<endl;
            if(strcmp(str,"abort")==0)
                break;
        }
        close(fifo);
    }
    return 0 ;
}