#include "server.h";

void readHeader() {
}

static void usage(void){
    fprintf(stderr, "%s - wrong input, please try again", myprog);
    exit(EXIT_FAILURE);
}

//initializes the server via reading the program input
void serverInit(int counter, char* arr []){
    int c, pCount, iCount;
    char* i_arg, *p_arg;
    while ( (c = getopt(counter, arr,  "p:i:")) != -1){
        switch (c){
            case 'p':
                p_arg = arr[optind-1];
                break;
            case 'i':
                i_arg = arr[optind-1];
                break;
            case '?':
                usage();
            break;
            default:
                usage();
                break;
        }
    }
}

