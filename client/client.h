#ifndef CLIENT_H_INCLUDED
#define CLIENT_H_INCLUDED

static const char NULL_CHAR = '\0';

#include <iostream>
#include <string>
#include "stdint.h"
#include <stdlib.h>
#include <vector>

#ifdef WIN32
#include <winsock2.h>
typedef int socklen_t;
typedef int addr_size;
#else
#include<stdio.h>
#include<stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h> /
#include <unistd.h> /* close */
#define INVALID_SOCKET -1
#define SOCKET_ERROR -1
#define closesocket(s) close(s)
typedef int SOCKET;
typedef struct sockaddr_in SOCKADDR_IN;
typedef struct sockaddr SOCKADDR;
typedef struct in_addr IN_ADDR;
#endif

const uint16_t BUFFER_SIZE = 2000;

class client
{
public:
    client();
    void run();
private:
    void mrecv();
    void msend(std::string server_message);
    char message[BUFFER_SIZE];
    int clientSocket;
    struct sockaddr_in serverAddr;
    socklen_t addr_size;
};


#endif // CLIENT_H_INCLUDED
