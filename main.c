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


}

int main() {
    int id = fork();
    forkMe(id);
   // forkMeWithPipes(id);
   return 0;
}
