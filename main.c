#include "library.h";
#include "server.h";


int main(int argc, char* argv[]) {
    myprog = argv[0];
    int id = 0;
    int arr[] = {1,2,4,5,6};
   // forkMe(id);
   //forkMeWithPipes(id);
   // forkAndSum(id, arr);
    //forkAgain(id);
    int a = 5;
    int b = 6;
    int ret1 = intmul(a, b, id);
    int ret2 = intmul(a, b, id);
    printf(stdout, "this is result: %d", ret1);

    //signals
    //check process status
    int status;
    int process = id;
    waitpid(id, &status, 0);

    if(WEXITSTATUS(status)){
        exit(EXIT_FAILURE);
    }
    // while()
    while(true){
        int a = 4;
        //read input from intmul and compare
        if(ret1 == ret2) return 1;
        //done;
    }

   return 0;
}

//https://www.youtube.com/watch?v=2hba3etpoJg
//https://www.youtube.com/watch?v=IFEFVXvjiHY