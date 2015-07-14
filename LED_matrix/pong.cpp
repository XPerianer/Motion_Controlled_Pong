// -*- mode: c++; c-basic-offset: 2; indent-tabs-mode: nil; -*-
// Small example how to use the library.
// For more examples, look at demo-main.cc
//
// This code is public domain
// (but note, that the led-matrix library this depends on is GPL v2)
#include "pong.h"

Game game;




//Needed for Socket
// get sockaddr, IPv4 or IPv6:
void *get_in_addr(struct sockaddr *sa)
{
    if (sa->sa_family == AF_INET) {
        return &(((struct sockaddr_in*)sa)->sin_addr);
    }

    return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

int socketfunction(){
    int sockfd, numbytes;
    char buf[MAXDATASIZE];
    struct addrinfo hints, *servinfo, *p;
    int rv;
    char s[INET6_ADDRSTRLEN];

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    if ((rv = getaddrinfo("192.168.178.45", PORT, &hints, &servinfo)) != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
        return 1;
    }

    // loop through all the results and connect to the first we can
    for(p = servinfo; p != NULL; p = p->ai_next) {
        if ((sockfd = socket(p->ai_family, p->ai_socktype,
                p->ai_protocol)) == -1) {
            perror("client: socket");
            continue;
        }

        if (connect(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
            close(sockfd);
            perror("client: connect");
            continue;
        }

        break;
    }

    if (p == NULL) {
        fprintf(stderr, "client: failed to connect\n");
        return 2;
    }

    inet_ntop(p->ai_family, get_in_addr((struct sockaddr *)p->ai_addr),
            s, sizeof s);
    printf("client: connecting to %s\n", s);

    freeaddrinfo(servinfo); // all done with this structure
    while(true){
    int index = -1;
    std::string s;
    try{ //Be safe if communication fails
    if ((numbytes = recv(sockfd, buf, MAXDATASIZE-1, 0)) == -1) {
        perror("recv");
      //  exit(1);
    }

    buf[numbytes] = '\0';

    for(int i=0;i< numbytes;i++){
      s += buf[i];
    }


    index = std::stoi(s.substr(s.find(',')+1,1));
    if(index==0){
      game.leftPaddle.position = std::stoi(s.substr(1));
    } else if(index ==1) {
      game.rightPaddle.position = std::stoi(s.substr(1));
    }
}
    catch (...){
      std::cout << "Error at Socket reading" << std::endl;
      usleep(1000000*1);
    }
    //printf("client: received '%s'\n",buf);
  }

    close(sockfd);

    return 0;
}

void gameLoop(){
  while(true){
    game.start = std::chrono::system_clock::now();
    game.draw();
    usleep(1000000 * 0.01);
    game.end = std::chrono::system_clock::now();
    game.duration = game.end-game.start;

    game.update();

  }
}

int main(int argc, char *argv[]) {

  std::thread socket_thread(socketfunction);
  std::thread game_thread(gameLoop);
  std::cout << "Press Enter to abort" << std::endl;
  getchar();
  game.destroy();



  return 0;
}
