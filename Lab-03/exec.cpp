#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
using namespace std;

int main(){
    pid_t pid = fork();

    if (pid == -1){
        cout<<"Child process creation failed"<<endl;
        return 1;
    }
    else if (pid == 0){
        // Child process
        cout<<"In child process!"<<endl;
        while (1)
        {
            int choice;
            cout<<"1 - Execute C++ object file"<<endl
                <<"2 - Execute echo command"<<endl
                <<"3 - Execute grep command"<<endl
                <<"4 - Execute ls command"<<endl
                <<"5 - Execute sort command"<<endl
                <<"6 - Execute ls command and redirect output to file"<<endl
                <<"7 - Exit"<<endl
                <<"Enter your choice: ";
            cin>>choice;
            cout<<endl;
            if (choice == 1){
                execl("./objectFile", NULL);    //executing object file
            }
            else if (choice == 2){
                execlp("echo", "echo", "Hello from execlp", NULL);
            }
            else if (choice == 3){
                char *args[] = {"grep","root","/etc/passwd", NULL};     //argument vector with grep command to search for root in /etc/passwd file
                execv("/bin/grep", args);
            }
            else if (choice == 4){
                char *args[] = {"ls","-l", NULL};
                execvp("ls", args);     //using passed arguments vector and using PATH env variable to execute ls command
            }
            else if (choice == 5){
                char *args[] = {"sort", "/etc/passwd", NULL};
                execvp("sort", args);   //same as above using PATH environment variable implicitly
            }
            else if (choice == 6){
                char *env[] = {"PATH=$PATH", NULL};     //setting env variable value
                char *args[] = {"touch","output.txt", NULL};    //argument vector to create output.txt file
                execve("/bin/touch", args, env);
            }
            else if (choice == 7){
                cout<<"Exiting child process"<<endl;
                break;
            }
            else
                cout<<"Invalid choice\n\n";
        }
    }
    else{
        // Parent process
        cout<<"\nWaiting for child process completion"<<endl;
        wait(NULL);                         //waiting for child process to complete
        cout<<"\nChild process completed"<<endl;
    }

    return 0;
}