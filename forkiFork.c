// test practise
#include "library.h"

#define WRITEEND 1
#define READEND 0

int forki (void){
    //read file
    char* lineL = NULL;
    char* lineR = NULL;
    size_t size = 0;

 //make pipes
 int pipefdL [2][2];
 int pipefdR [2][2];

 //piping
 if (pipe(pipefdL[0]) == -1 ) {
     fprintf(stderr, "error");
     close(pipefdL[0][READEND]);
     close(pipefdL[0][WRITEEND]);
     close(pipefdL[1][READEND]);
     close(pipefdL[1][WRITEEND]);
     exit(EXIT_FAILURE);
 }

 if (pipe(pipefdL[1])== -1) {
     fprintf(stderr, "error");
     close(pipefdR[0][READEND]);
     close(pipefdR[0][WRITEEND]);
     close(pipefdR[1][READEND]);
     close(pipefdR[1][WRITEEND]);
      exit(EXIT_FAILURE);
 }

 //write to pipes
 if (write(pipefdL[1][WRITEEND], lineL, strlen(lineL)) == - 1) exit(EXIT_FAILURE));
 if (write(pipefdR[1][WRITEEND], lineL, strlen(lineL)) == - 1) exit(EXIT_FAILURE));

//read lines in with getline or fgets
char* line = NULL;
int j = 2;
    while(getline(&line, &size, stdin) != -1){
        if(j% 2 == 0){
            write(pipefdL[1][WRITEEND], line, strlen(line));
        }else{
            write(pipefdR[1][WRITEEND], line, strlen(line));
        }
        j++;
    }

    //and now we fork ...
}

