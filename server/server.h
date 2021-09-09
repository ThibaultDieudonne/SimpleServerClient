#ifndef SERVER_H_INCLUDED
#define SERVER_H_INCLUDED

#include "stdint.h"
#include<stdlib.h>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstddef>
#include <random>

// network stuff
#ifdef WIN32
#include <winsock2.h>
typedef int socklen_t;
typedef int addr_size;
#else
#include<stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <unistd.h> /* close */
#include <netdb.h> /* gethostbyname */
#define INVALID_SOCKET -1
#define SOCKET_ERROR -1
#define closesocket(s) close(s)
typedef int SOCKET;
typedef struct sockaddr_in SOCKADDR_IN;
typedef struct sockaddr SOCKADDR;
typedef struct in_addr IN_ADDR;
#endif

static const uint16_t BUFFER_SIZE = 2000;
static const char NULL_CHAR = '\0';

class server
{
public:
    void run(); // connections handler
    void communicate(); // communication handler

private:
    int msocket;
    void msend(std::string server_message);
    void mrecv();
    char client_message[BUFFER_SIZE];
};

#endif // SERVER_H_INCLUDED
