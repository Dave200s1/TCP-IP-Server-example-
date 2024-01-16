
#include <iostream>
#include <string>
#include <stdexcept>

#include <cstring>
#include <winsock2.h>
#include <windows.h>
#include <thread> 
#include <typeinfo>
#include <stdexcept>
#pragma comment(lib, "ws2_32.lib") 

#include "TCPserver.h"

using namespace std;

TCP_Server::TCP_Server(int port) : serverSocket(0), portNumber(port){

}

TCP_Server::~TCP_Server(){

}

bool TCP_Server::start(){
                   //Initialise Win-sock
                WSADATA wsaData;
                if(WSAStartup(MAKEWORD(2,2),&wsaData) !=0){
                    cerr<< "Failed to initialise Windsock\n";
                    return false;
                }
                //Create a socket
                serverSocket = socket(AF_INET, SOCK_STREAM, 0);
                if(serverSocket == INVALID_SOCKET){
                    cerr<<"Failed to create a socket !\n";

                    WSACleanup();
                    return false;
                }
                //Prepare the address structure
                
                serverAddress.sin_family = AF_INET;
                serverAddress.sin_addr.s_addr = INADDR_ANY;
                serverAddress.sin_port = htons(portNumber);
                //Binding the socket to the specified IP and port
                if (bind(serverSocket, (struct sockaddr*) & serverAddress, sizeof(serverAddress)) == SOCKET_ERROR){
                    cerr<<"Failed to bind the socket\n";
                    closesocket(serverSocket);
                    WSACleanup();
                    return false;
                }
                
                // Listen for incoming connections
                if (listen(serverSocket, 5) == SOCKET_ERROR) {
                    cerr << "Failed to listen\n";
                    closesocket(serverSocket);
                    WSACleanup();
                    return false;
                }
                 cout << "Server started. Listening for incoming connections on port " << portNumber << endl;

                // Start accepting client connections
                acceptConnections();
                return true;
}

void TCP_Server::setPort(int port){
    const int maxLength = 10;
    if (port > maxLength){
        throw std::invalid_argument("The port is too big, please enter another digit combination ! (4)");
    }
    portNumber = port;
}


void TCP_Server::acceptConnections(){
        while (true) {
                // Accept a client connection
                sockaddr_in clientAddress;
                int clientAddressSize = sizeof(clientAddress);
                SOCKET clientSocket = accept(serverSocket, (struct sockaddr*) & clientAddress, &clientAddressSize);
                if (clientSocket == INVALID_SOCKET) {
                    cerr << "Failed to accept client connection\n";
                    closesocket(serverSocket);
                    WSACleanup();
                    return;
                }

                cout << "New client connected\n";

                // Handle client requests
                handleClient(clientSocket);

                // Close the client connection
                closesocket(clientSocket);
         }
}

void TCP_Server::handleClient(SOCKET clientSocket){
 char buffer[1024];
            memset(buffer, 0, sizeof(buffer));
            int bytesRead = recv(clientSocket, buffer, sizeof(buffer) - 1, 0);
            if (bytesRead == SOCKET_ERROR) {
                cerr << "Failed to receive data from client\n";
                return;
            }

            cout << "Received data from client: " << buffer <<endl;

            // Send a response back to the client
            const char* response = "Hello, client!";
            int bytesSent = send(clientSocket, response, strlen(response), 0);
            if (bytesSent == SOCKET_ERROR) {
                cerr << "Failed to send response to client\n";
                return;
            }

            cout << "Response sent to client\n";
}









