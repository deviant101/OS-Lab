#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <sys/wait.h>
using namespace std;

int Array[20] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};
int pipefd[2];

void SumFun(int start, int end){
    int sum=0;
    for(int i=start;i<end;++i){
        sum+=Array[i];
    }
    write(pipefd[1],&sum,sizeof(sum));
    close(pipefd[0]);
    close(pipefd[1]);
    return;
}

int main(){

    if(pipe(pipefd) == -1){
        cout<<"error in pipe\n"<<endl;
        return 1;
    }

    int no_of_childs=0;
    while(1){
        cout<<"Enter no of child processes(1-6): ";
        cin>>no_of_childs;
        if(no_of_childs<1 || no_of_childs>6)
            cout<<"Invalid no_of_childs\n";
        else
            break;
    }
    pid_t Parent_ID=getpid();

    //------------Child processes---------------//
    int compute = 20/no_of_childs;
    for(int i=0; i<no_of_childs; i++){
        pid_t child_id=fork();
        if(child_id==0){
            if((i+1)==no_of_childs)
                SumFun(i*compute,20);
            else
                SumFun(i*compute,(i+1)*compute);
        }
    }
    // ------------Parent process---------------//
    if(Parent_ID==getpid()){
        int sum=0;
        for(int i=0; i<no_of_childs; i++){
            int child_sum;
            read(pipefd[0],&child_sum,sizeof(child_sum));
            sum+=child_sum;
        }
        cout<<"Sum of all child processes: "<<sum<<endl;
    }
}