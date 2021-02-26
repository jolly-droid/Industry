#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/wait.h>
#include <stdbool.h>



#ifndef INDUSTRY_LIBRARY_H
#define INDUSTRY_LIBRARY_H

#endif //INDUSTRY_LIBRARY_H

//first small function for forking
void forkMe(int id);

//forking this time with pipes
void forkMeWithPipes(int id);

//an example from real life with pipes
void forkAndSum(int id, int arr[]);

//another forking test function
void forkAgain(int id);

//trying to implement an exercise
// @return returns the sum of the two given numbers
int intmul(int a, int b, int id);

//just another pracits method
void pracitse(char* myprog);
//conitnuing the processes with status update check
void statusupdate(int id);
