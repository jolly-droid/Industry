#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

/*
//this method forks the process
static void forkMe(int id){
    // added errohandeling
    id = fork();
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

//forking this time with pipes
static void forkMeWithPipes(int id){
    int fd [2];
    if(pipe(fd) == -1){
        fprintf(stderr, "piping went wrong: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }
    id = fork();

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
            printf( "i got this number form child: %d\n", y);
    }
}*/
/*an example from real life
 *
*/
static void forkAndSum(int id, int arr[]){
    int arrSize = sizeof(arr)/ sizeof(int);
    int fd[2];
    int start, end; //start and end of array
    if (pipe(fd) == -1){
        printf("error on piping\n");
        exit(EXIT_FAILURE);
    }

    id = fork();
    if (id == -1) exit (EXIT_FAILURE);

    if (id == 0){ // child process
        start = 0;
        end = start + arrSize/2;
    }else{ //parent process
        start = arrSize/2;
        end = arrSize;
    }

    //summing up
    int sum = 0;
    for(int i = start; i < end; i++){
        sum += arr[i];
    }

    if (id == 0){ // child process
        printf("calculated partial sum - child %d \n", sum);
    }else{ //parent process
        printf("calculated partial sum - parent %d \n", sum);
    }

    if (id == 0){ // child process

        close(fd[0]);
        if (write(fd[1], &sum, sizeof (sum)) == -1) exit(EXIT_FAILURE);
        close(fd[1]);

    }else{ //parent process

        int sumFromChild = 0;
        close(fd[1]);
        if(read(fd[0], &sumFromChild, sizeof (sumFromChild)) == -1) exit(EXIT_FAILURE);
        close(fd[0]);

        int totalSum = sum + sumFromChild;
        printf("this is sum %d\n", totalSum);

    }


}
static void forkAgain(int id){
    int fd[2];
    if (pipe(fd) == -1) exit(EXIT_FAILURE);

    id = fork();

    switch(id){
        case -1: exit(EXIT_FAILURE);
        break;
        case 0:
            close(fd[0]);
            fprintf(stdout, "here we have le child");
            char f [] = "WE ware here";
            if (write(fd[1], &f, sizeof(char)) == -1) exit(EXIT_FAILURE);
            close(fd[1]);
            break;

        default:
            exit(EXIT_FAILURE);
            break;

    }

}


static int intmul(int a, int b, int id){
    int fd [2];

    if(pipe(fd) == -1) exit(EXIT_FAILURE);
    id = fork();

    switch(id){
        case -1: exit(EXIT_FAILURE);
        case 0: // child process
            close(fd[0]);
            a = a +5;
            if(write (fd[1], &a, sizeof(int)) == -1) exit(EXIT_FAILURE);
            close(fd[1]);
        break;

        default: // parent process
            close(fd[1]);
            if(read(fd[0], &b, sizeof(int)) == -1) exit(EXIT_FAILURE);
            int sum = b + a;
            close(fd[0]);
            fprintf(stdout, "this is result:%d", sum);
        break;
    }


}

int main(int argc, char* argv[]) {
    int id = 0;
    int arr[] = {1,2,4,5,6};
   // forkMe(id);
   //forkMeWithPipes(id);
   // forkAndSum(id, arr);
    //forkAgain(id);
    int a = 5;
    int b = 6;
    int ret = intmul(a, b, id);
    printf(stdout, "this is result: %d", ret);

   return 0;
}

//https://www.youtube.com/watch?v=2hba3etpoJg
//https://www.youtube.com/watch?v=IFEFVXvjiHY