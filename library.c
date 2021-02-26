//implementtion of fork functions

#include "library.h";

//this method forks the process
void forkMe(int id){
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
void forkMeWithPipes(int id){
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
}


/*an example from real life
 *
*/

void forkAndSum(int id, int arr[]){
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
void forkAgain(int id){
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


    }

}

/*
 * \section*{Assignment -- Integer Multiplication}
Implement an algorithm for the efficient multiplication of large integers.

The program takes two hexadecimal integers $A$ and $B$ with an equal number of digits as input,
multiplies them and prints the result.
The input is read from stdin and consists of two lines:
the first line is the integer $A$ and the second line is the integer $B$.

Your program must accept any number of digits.
Terminate the program with exit status |EXIT_FAILURE|
if an invalid input is encountered
or if the two integers do not have equal length.

The multiplication of the input values is calculated recursively,
i.e. by the program calling itself:
If $A$ and $B$ both consist of only 1 hexadecimal digit, then multiply them,
write the result to stdout and exit with status |EXIT_SUCCESS|.
 Otherwise $A$ and $B$ both consist of $n>1$ digits. Split them both into two parts each,
with each part consisting of $n/2$ digits:

Terminate the program with exit status \verb|EXIT_FAILURE|
if the number of digits is not even.

\item Using \osuefunc{fork(2)} and \osuefunc{execlp(3)},
recursively execute this program in four child processes,
one for each of the multiplications $A_h\cdot B_h$, $A_h\cdot B_l$, $A_l\cdot B_h$ and  $A_l\cdot B_l$.
Use two unnamed pipes per child
to redirect \osueglvar{stdin} and \osueglvar{stdout}
(see \osuefunc{pipe(2)} and \osuefunc{dup2(3)}).
Write the two values to be multiplied to \osueglvar{stdin} of each child.
Read the respective result from each child's \osueglvar{stdout}.
The four child processes must run simultaneously!

\item Use \osuefunc{wait(2)} or \osuefunc{waitpid(2)}
to read the exit status of the children.
Terminate the program with exit status \verb|EXIT_FAILURE|
if the exit status of any of the two child processes is not \verb|EXIT_SUCCESS|.

\item The result of the multiplication $A\cdot B$ can now be calculated as follows:
\[
A\cdot B=A_h\cdot B_h\cdot 16^n + A_h\cdot B_l\cdot 16^{n/2} + A_l\cdot B_h\cdot 16^{n/2} + A_l\cdot B_l
\]

Find a clever way to write the result of this operation to \texttt{stdout},
even if the numbers are too large for the C data types.
Remember that your program must deal with integers of any size!
Leading zeros should also be printed,
such that the result has twice as many digits as the input values.
Terminate the program with exit status \verb|EXIT_SUCCESS|.

 Think of a way to add the four intermediate results together
one digit at a time while keeping track of the carry.
 In order to avoid endless recursion\footnote{\url{http://en.wikipedia.org/wiki/Fork\_bomb}},
fork only if the input number is greater than 1.
\item To output error messages and debug messages, always use
\osueglvar{stderr} because \osueglvar{stdout} is redirected in most cases.
\item Due to the rejection of sequences of odd length by each (child-)process,
the algorithm has the property of only correctly processing sequences
where the length is a power of 2.
\end{itemize}
 */


//TODO: returns some pointerstuff not the number
int intmul(int a, int b, int id){
    int fd [2];
    int ret = 0;
    if (a == 1 || b == 1) return a*b;
    if (sizeof(int)*a != sizeof(int)*b) exit(EXIT_FAILURE);

    if(pipe(fd) == -1) exit(EXIT_FAILURE);
    id = fork();

    switch(id){
        case -1: exit(EXIT_FAILURE);
        case 0: // child process
            close(fd[0]);
            a = a +5;
            if(write (fd[1], &a, sizeof(int)) == -1) exit(EXIT_FAILURE);
            close(fd[1]);
            // call exec
            break;

        default: // parent process
            close(fd[1]);
            if(read(fd[0], &b, sizeof(int)) == -1) exit(EXIT_FAILURE);
            int sum = b + a;
            close(fd[0]);
            fprintf(stdout, "this is result:%d", sum);
            ret = sum;
            break;
    }




    return ret;

}

static void practice(int id){
    //first pipe
    int fd[2];
    if(pipe(fd) == -1) exit(EXIT_FAILURE);

    //then fork
    id = fork();
    int transport = 9;
    int readme = 0;
    //then say what children do
    switch(id){
        case -1 : exit(EXIT_FAILURE);
        case 0: // child
            close(fd[0]);

            if(write(fd[1], &transport, sizeof(int)) == -1) exit(EXIT_FAILURE);
            //execlp(myprog, parameter1, parameter 2);
            close(fd[1]);
        break;

        default:
            close(fd[1]);
            if(read(fd[0], &readme, sizeof(int))== -1) exit(EXIT_FAILURE);
            close(fd[0]);

    }

    int sum = transport + readme;
    fprintf(stdout, "see the result: %d", sum);
   //then compare and rest of the programm
}

void practise (char* myprog){
    int fd[2];
    pipe(fd);

    int id = fork();

    char* recieved = "";
    switch(id){
        case 0:
            //child process
            close(fd[0]);
            char* message = "thisistheDARKSIDE";
            if(write(fd[1], message, sizeof(char)) == -1) exit(EXIT_FAILURE);
            close(fd[1]);
           if( execlp(myprog, id, NULL) == -1) exit(EXIT_FAILURE);
            break;
        case -1:
            fprintf(stderr, "error on forking");
            exit(EXIT_FAILURE);
        default:
            //parent
            close(fd[1]);
            if(read(fd[0], recieved, sizeof(char)) == -1) exit(EXIT_FAILURE);
            close(fd[0]);
            break;


    }
    char* adme = "LOL";
    char* result = strcat(recieved,adme);

    fprintf(stdout, "this + %s", result);
    statusupdate(id);

}

void statusupdate(int id){
    int status;
    waitpid(id, &status, 0);
}


