#define CATCH_CONFIG_MAIN // Add this line before including Catch2

#include "TCPserver.h"
#include "catch.hpp"

#include <stdexcept>

#include <cstring>
#include <winsock2.h>
#pragma comment(lib,"ws2_32.lib")
#include <thread> 
#include <sstream>



TEST_CASE("Test if port can be correctly set"){
    //Arrange
    TCP_Server server(8080);
    int port = 8080;

    SECTION("testing with a invalide port"){
        //Act
        //Assert
        REQUIRE_THROWS_AS(server.setPort(11111111),std::invalid_argument);
    }

    SECTION("testingwith a valide port"){
        //Act
        //Assert
        REQUIRE_NOTHROW(server.setPort(000));
    }
}



//Creating a Socket
TEST_CASE("Failed to create a socket"){
    //Arrange
    std::ostringstream oss;
    std::streambuf* oldCerrBuf = std::cerr.rdbuf(oss.rdbuf());

    SECTION("Test case that fails to create a socket"){
        //Act
        //Simulating the Failure !!!
        std::cerr<< "Failed to create a socket !\n";
    }
    std::cerr.rdbuf(oldCerrBuf); //Restore the original  cerr buffer
    //Assert
    REQUIRE(oss.str() == "Failed to create a socket !\n");
    
}

//Binding
TEST_CASE("Failed to bind"){
    //Arrange
    std::ostringstream oss;
    std::streambuf* oldCerrBuf = std::cerr.rdbuf(oss.rdbuf());

    SECTION("Test case that fails to bind "){
        //Act
        //Simulating the Failure !!!(Mocking)
        std::cerr<<"Failed to bind the socket\n";
    }
    std::cerr.rdbuf(oldCerrBuf); //Restore the original cerr buffer
    //Assert
    REQUIRE(oss.str() == "Failed to bind the socket\n");
}



//Listening
TEST_CASE("Failed to listen"){
    //Arrange
    std::ostringstream oss;
    std::streambuf* oldCerrBuf = std::cerr.rdbuf(oss.rdbuf());

    SECTION("Test case that fails to listen"){
        //Act
        //Simulating the Failure !!!(Mocking)
        std::cerr<<"Failed to listen\n";
    }
    std::cerr.rdbuf(oldCerrBuf); //Restore the original cerr buffer
    //Assert
    REQUIRE(oss.str() == "Failed to listen\n");

}

//Accepting connections
TEST_CASE("Failed to accept connection"){
    //Arrange
    std::ostringstream oss;
    std::streambuf* oldCerrBuf = std::cerr.rdbuf(oss.rdbuf());

    SECTION("Test case that fails to accept "){
        //Act
        //Simulating the Failure !!! (Mocking)
        std::cerr<<"Failed to accept client connection\n";
    }
    std::cerr.rdbuf(oldCerrBuf); //Restore the original cerr buffer
    //Assert
    REQUIRE(oss.str() == "Failed to accept client connection\n");
}

//Handling client requests
TEST_CASE("Failed to handle client requests"){
    //Arrange
    std::ostringstream oss;
    std::streambuf* oldCerrBuf = std::cerr.rdbuf(oss.rdbuf());
    SECTION("Test case that fails to receive data from client"){
        //Act
        //Simulating the Failure !!! (Mocking)
        std::cerr<<"Failed to receive data from client\n";
    }
    std::cerr.rdbuf(oldCerrBuf); //Restore the original cerr buffer
    //Assert
    REQUIRE(oss.str() == "Failed to receive data from client\n");
}

TEST_CASE("Faild to send response to client"){
    //Arrange
    std::ostringstream oss;
    std::streambuf* oldCerrBuf = std::cerr.rdbuf(oss.rdbuf());
    SECTION("Test case that fails to send response to client"){
        //Act
        //Simulating the Failure !!! (Mocking)
        std::cerr<<"Failed to send response to client\n";
    }
    std::cerr.rdbuf(oldCerrBuf); //Restore the original cerr buffer
    //Assert
    REQUIRE(oss.str() == "Failed to send response to client\n");
}

//Closing connections
TEST_CASE("Successfull closing of the Socket"){
    //Arrange
    WSADATA wsData;
    WSAStartup(MAKEWORD(2,2),&wsData);
    SOCKET testSocket = socket(AF_INET, SOCK_STREAM, 0);
    //Act
    int result = closesocket(testSocket); // It should return a zero if the predifined function hase been executed succseffuly !
    int errorCode = WSAGetLastError();
    WSACleanup();
    //Assert
    REQUIRE(result == 0);
    REQUIRE(errorCode == 0);
}

