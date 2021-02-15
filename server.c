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

    ///assign ports
    if (pCount >= 2 || iCount >= 2) usage();
    if (pCount == 0) port = DEFAULT_PORT;
    else if (p_arg != NULL) port = p_arg;
}
//method for connection to socekt etc;
void createEndpoint(void){
    struct addrinfo hints, *ai;
    memset(&hints,0, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    int adress = getaddrinfo(NULL, port, &hints, &ai);
    if (adress != 0) usage();

    int soc = socket(ai->ai_family, ai->ai_socktype, ai->ai_protocol);
    if(soc < 0) usage();

    int bid = bind(soc, ai->ai_addr, ai->ai_addrlen);
    if(bid<0) usage();

    freeaddrinfo(ai);

    int lis =  listen (soc, 1);
    if(lis < 0) usage();

}

