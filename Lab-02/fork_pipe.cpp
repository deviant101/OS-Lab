#include<stdio.h>
#include<unistd.h>
#include<iostream>
#include<sys/wait.h>
using namespace std;

int pipe_1[2];
int pipe_2[2];
int pipe_3[2];

int a=1,b=6,c=6,d=9;

int main(){
    
    // cout<<pipefd[0]<<pipefd[1]<<endl;
    if(pipe(pipe_1)==-1||pipe(pipe_2)==-1||pipe(pipe_3)==-1)
        cout<<"error in pipe"<<endl;
    
    //1st child process
    pid_t pid=fork();
    if(pid==0){
        cout<< "Child1"<<endl;
        int w=d*a;
        close(pipe_1[0]);
        write(pipe_1[1],&w,sizeof(w));
        close(pipe_1[1]);
    }
    else{
        // wait(NULL);
        cout<<"Parent"<<endl;

        //2nd child process
        pid=fork();
        if(pid==0){
            cout<<"Child2"<<endl;
            int w=a+b;
            close(pipe_2[0]);
            write(pipe_2[1],&w,sizeof(w));
            close(pipe_2[1]);

            pid=fork();
            if(pid==0){
                cout<<"Grandchild"<<endl;
                int w=c-a;
                close(pipe_3[0]);
                write(pipe_3[1],&w,sizeof(w));
                close(pipe_3[1]);
            }
        }
        else{
            int a,b,c;
            read(pipe_1[0],&a,sizeof(a));
            close(pipe_1[0]);

            read(pipe_2[0],&b,sizeof(b));
            close(pipe_2[0]);

            read(pipe_3[0],&c,sizeof(c));
            close(pipe_3[0]);
            
            int sum=b+c;
            // cout<<a<<" "<<b<<" "<<c<<" "<<sum<<endl;
            int equation=a*sum;
            cout<<equation<<endl;
            write(pipe_1[1],&equation,sizeof(equation));
            close(pipe_1[1]);
            
        }
    }
    



    return 0;
}