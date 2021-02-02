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
        fprintf(stdout,"this is the child-id: %d\n", id);

    }else{
        fprintf(stdout, "this is the parent-id: %d\n", id);
    }
}

static void forkMeWithPipes(int id){
/*
 * https://www.youtube.com/watch?v=Mqb2dVRe0uo

https://www.youtube.com/watch?v=6u_iPGVkfZ4

https://www.youtube.com/watch?v=2hba3etpoJg

https://www.youtube.com/watch?v=IFEFVXvjiHY
 */

}

int main() {
    int id = fork();
    forkMe(id);
   return 0;
}
