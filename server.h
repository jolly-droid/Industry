
#ifndef INDUSTRY_SERVER_H
#define INDUSTRY_SERVER_H

#endif //INDUSTRY_SERVER_H
#include <stdio.h>
#include <getopt.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <signal.h>
#include <netdb.h>
#include <unistd.h>
#include <time.h>

char* myprog;
char* i_arg, *p_arg;
char* port, *ind;

char* const DEFAULT_PORT = "80";
char DEFAULT_INDEX [] = {"/index.html"};

//volatile sig_atomic_t quit = 0;
//volatile sig_atomic_t working = 0;

void readHeader(void);
