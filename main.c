#include <stdio.h>
#include <unistd.h>

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <fcntl.h>

//this method forks the process
static void forkMe(int id){
    // added errohandeling
    switch(id){
        case -1:
            fprintf(stderr, "fork went wrong %s\n", strerror(errno));
            exit(EXIT_FAILURE);
            break;
        case 0:
            fprintf(stdout,"this is the child-id: %d\n", id);
            break;
        default:
            fprintf(stdout, "this is the parent-id: %d\n", id);
            break;
    }

}

static void forkMeWithPipes(int id){


}

int main() {
    int id = fork();


    forkMe(id);
   return 0;
}
