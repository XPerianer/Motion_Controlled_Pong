#include "game.h"

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <thread>

#include <chrono>

//Used for Socket communication
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#define PORT "1337" // the port client will be connecting to
#define MAXDATASIZE 100 // max number of bytes we can get at once
