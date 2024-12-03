#include <unistd.h>

int main(){
int fd1 = open("foo.txt", O_WRONLY);
    int FILENO = 1;
    int backup_stdout = dup( FILENO ); // save stdout for later
    dup2( FILENO, fd1); //sets FILENO's entry to the file for fd1.
    printf("TO THE FILE!!!\n");
    fflush(stdout);//not needed when a child process exits, becaue exiting a process will flush automatically.
    // dup2(backup_stdout, FILENO) //sets FILENO's entry to backup_stdout, which is stdout

    }
