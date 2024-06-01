#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <iostream>
using namespace std;
int main(){

    int fifo = open("pipe_one", O_RDWR);
cout<<"Here2"<<endl;

    if(fifo<0){
        cout<<"Error opening file";
    }
    else{
        cout<<"Inside2"<<endl;
        while(1){

            char str[256];
            read(fifo,str,sizeof(str));
            cout<<str<<endl;
            if(strcmp(str,"abort")==0)
                break;
            
            cout<<"Entertext: ";
            cin>>str;
            write(fifo,str,sizeof(str));
            if(strcmp(str,"abort")==0)
                break;
        }
        close(fifo);
    }
    return 0 ;
}