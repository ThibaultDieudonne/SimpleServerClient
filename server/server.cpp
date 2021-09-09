#include "server.h"

void server::communicate()
{
    std::string msg;
    while (1)
    {
        std::getline(std::cin, msg);
        std::cout << "[SERVER] " << msg << std::endl;
        msend(msg);
        mrecv();
        std::cout << "[CLIENT] " << client_message << std::endl;
    }
}

void server::run()
{
    // initalize winsock
    #ifdef _WIN32
    WSADATA wsData;
    WORD ver = MAKEWORD(2, 2);

    int wsOk = WSAStartup(ver, &wsData);
    if (wsOk != 0)
    {
        std::cout << "Can't init winsock" << std::endl;
        return;
    }
    #endif
    // instancing server
    int serverSocket;
    struct sockaddr_in serverAddr;
    struct sockaddr_storage serverStorage;
    socklen_t addr_size;
    serverSocket = socket(AF_INET, SOCK_STREAM, 0); // Create the socket.
    serverAddr.sin_family = AF_INET; // Configure settings of the server address struct, Address family = Internet
    serverAddr.sin_port = htons(6969); //Set port number, using htons function to use proper byte order
    serverAddr.sin_addr.s_addr = inet_addr("0.0.0.0"); // Set IP address to localhost
    memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero); // Set all bits of the padding field to 0
    bind(serverSocket, (struct sockaddr *) &serverAddr, sizeof(serverAddr));
    // loop for connection management
    if(listen(serverSocket,50)==0){std::cout << "Server listening" << std::endl;}
    else{std::cout << listen(serverSocket,50) << std::endl;}
    // Accept call creates a new socket for the incoming connection
    addr_size = sizeof serverStorage;
    msocket = accept(serverSocket, (struct sockaddr *) &serverStorage, &addr_size);
    // threading incomming connection
    communicate();
    std::cout << "Registered new upcomming connection" << std::endl;
}

void server::msend(std::string server_message)
{

    const char *buffer = server_message.c_str();
    send(msocket, buffer, (int)strlen(buffer), 0);
}

void server::mrecv()
{
    memset(client_message, NULL_CHAR, sizeof client_message);
    recv(msocket, client_message, BUFFER_SIZE, 0);
}
