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
    if(id == 0){
        fprintf(stdout,"this is the child");

    }else{
        fprintf(stdout, "this is the parent");
    }
}

int main() {
    int id = fork();
    forkMe(id);
   return 0;
}
