#include "library.h";
#include "server.h";


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