#ifndef SERVER_H
#define SERVER_H

#include <arpa/inet.h> // For socket functions (bind, listen, accept)
#include <cstring>     // For memset
#include <iostream>
#include <signal.h> // For signal handling (e.g., Ctrl+C to stop the server)
#include <thread>   // For multithreading to handle concurrent clients
#include <unistd.h> // For read, write, close system calls

class Server {
private:
  int sockfd;                 // Server socket file descriptor
  sockaddr_in sockaddr;       // Server address structure
  volatile sig_atomic_t stop; // Flag to control server shutdown

public:
  Server();                  // Constructor to initialize the server
  ~Server();                 // Destructor to clean up resources
  int startServer(int port); // Set up and start the server
  void acceptClients();      // Main loop to handle clients
  static void handleClient(int clientSock); // Static method for client threads
  void shutdownServer();                    // Method to stop the server
};

#endif // SERVER_H
