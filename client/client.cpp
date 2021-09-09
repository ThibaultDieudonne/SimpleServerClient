#include "client.h"

client::client()
{
    // initalize winsock
    #ifdef _WIN32
    WSADATA wsData;
    WORD ver = MAKEWORD(2, 2);

    int wsOk = WSAStartup(ver, &wsData);
    if (wsOk != 0)
    {
        std::cout << "Can't init winsock" << std::endl;
        std::cin.get();
        exit(EXIT_FAILURE);
    }
    #endif
    // connect
    clientSocket = socket(PF_INET, SOCK_STREAM, 0);
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(6969);
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1"); // doesn't work with hostnames
    memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);
    addr_size = sizeof serverAddr;
    if (connect(clientSocket, (struct sockaddr *) &serverAddr, addr_size) < 0)
    {
        std::cout << "Can't connect to server" << std::endl;
        std::cin.get();
        exit(EXIT_FAILURE);
    }
    std::cout << "Connected" << std::endl;
}

void client::run()
{
    std::string str_message;
    while (1)
    {
        mrecv();
        std::cout << "[SERVER] " << (std::string)message << std::endl;
        std::getline(std::cin, str_message);
        std::cout << "[CLIENT] " << str_message << std::endl;
        msend(str_message);
    }
}

void client::mrecv()
{
    memset(message, NULL_CHAR, sizeof message);
    recv(clientSocket, message, BUFFER_SIZE, 0);
}

void client::msend(std::string server_message)
{
    const char *buffer = server_message.c_str();
    send(clientSocket, buffer, (int)strlen(buffer), 0);
}
