#ifndef TCPserver_H
#define TCPserver_H
#include <string>
#include <string>
#include <stdexcept>

#include <cstring>
#include <winsock2.h>
#include <windows.h>
#include <thread> 
#include <typeinfo>
#include <stdexcept>

using namespace std;

class TCP_Server
{
    private:
        SOCKET serverSocket;
        int portNumber;
        sockaddr_in serverAddress;

        void acceptConnections();

        void handleClient(SOCKET clientSocket);

    public:

        TCP_Server(int port);

        ~TCP_Server();

        bool start();

        void setPort(int port);


};


#endif //TCPserver_H