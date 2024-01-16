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



int main()
{
    TCP_Server server(8080); // Specify the port number for the server

    if (!server.start())
    {
        std::cerr << "Failed to start server\n";
        return 1;
    }

    return 0;
}