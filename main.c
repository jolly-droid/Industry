#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>


//this method forks the process
static void forkMe(int id){
    // added errohandeling
    switch(id){
        case -1:
            fprintf(stderr, "fork went wrong %s\n", strerror(errno));
            exit(EXIT_FAILURE);
        case 0:
            fprintf(stdout,"this is the child-id: %d\n", id);
            break;
        default:
            fprintf(stdout, "this is the parent-id: %d\n", id);
            break;
    }

}

static void forkMeWithPipes(int id){
    int fd [2];
    if(pipe(fd) == -1){
        fprintf(stderr, "piping went wrong: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }
    if(id == -1) exit(EXIT_FAILURE);
    if(id == 0) { //child process
        close(fd[0]); // close read end
        int x;
        printf("enter a number: \n");
        scanf("%d", &x);
        if (write(fd[1], &x, sizeof(int)) == -1) exit(EXIT_FAILURE);
        close(fd[1]); // close write end

    }else{ //parent process
            close(fd[1]);
            int y;
            if(read(fd[0], &y, sizeof(int)) == -1) exit(EXIT_FAILURE);
            close(fd[0]);
            printf( "i got this number form child: %d\n", &y);
    }



}

int main() {
    int id = fork();
   // forkMe(id);
    forkMeWithPipes(id);
   return 0;
}
