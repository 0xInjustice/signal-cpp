#ifndef SERVER_H
#define SERVER_H

#include <arpa/inet.h> // For socket functions (bind, listen, accept)
#include <cstring>     // For memset
#include <iostream>
#include <signal.h> // For signal handling (e.g., Ctrl+C to stop the server)
#include <thread>   // For multithreading to handle concurrent clients
#include <unistd.h> // For read, write, close system calls

class Server {
public:
  Server();
  ~Server();

  int startServer(int port);
  void acceptClients();
  void stopServer();

  // New function that saves the received data into a variable
  void database(const std::string &data);

  // New function that sends the stored data back to the client
  void request(int clientSock);

private:
  void handleClient(int clientSock);

  int sockfd;
  struct sockaddr_in sockaddr;
  volatile sig_atomic_t stop; // Flag to control server shutdown
};


#endif // SERVER_H
