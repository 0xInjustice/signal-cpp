#include "server.h"
#include <cerrno>
#include <cstdlib>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

Server::Server() : stop(false), sockfd(-1) {
  // create server
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd == -1) {
    std::cerr << "Falied to create socket" << std::endl;
    exit(EXIT_FAILURE);
  }
  memset(&sockaddr, 0, sizeof(sockaddr)); // clear the sockaddr memory space
}

Server::~Server() {
  if (sockfd != -1) {
    close(sockfd);
  }
}

int Server::startServer(int port) {
  // configure the server address
  sockaddr.sin_family = AF_INET;
  sockaddr.sin_addr.s_addr = INADDR_ANY;
  sockaddr.sin_port = htons(port);

  /*bind the socket to specifies port*/
  if (bind(sockfd, (struct sockaddr *)&sockaddr, sizeof(sockaddr)) < 0) {
    std::cerr << "failed to bind to port" << port << ".errorno:" << errno
              << std::endl;
    close(sockfd);
    return -1;
  }
  std::cout << "server is listening on port:" << port << std::endl;
  return 0;
}

void Server::acceptClients() {
  while (!stop) {
    sockaddr_in clientAddr;
    socklen_t clientLen = sizeof(clientAddr);

    // Accept a new client connection
    int clientSock = accept(sockfd, (struct sockaddr *)&clientAddr, &clientLen);
    if (clientSock < 0) {
      if (stop)
        break;
      std::cerr << "Failed to accept connection. errno: " << errno << std::endl;
      continue;
    }

    std::cout << "Accepted connection from " << inet_ntoa(clientAddr.sin_addr)
              << ":" << ntohs(clientAddr.sin_port) << std::endl;

    // Spawn a new thread to handle the client
    std::thread clientThread(&Server::handleClient, this, clientSock);
    clientThread.detach(); // Detach so it runs independently
  }
}
