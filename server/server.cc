#include "server.h"
#include <arpa/inet.h>
#include <cerrno>
#include <cstring>
#include <iostream>
#include <netinet/in.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <thread>
#include <unistd.h>

Server::Server() : stop(0), sockfd(-1) {
  // create a socket
  sockfd = socket(AF_INET, SOCK_STREAM, 0);

  if (sockfd == -1) {
    std::cerr << "Failed to create a socket" << std::endl;
    exit(EXIT_FAILURE);
  }

  // initialize the sockaddr structure
  memset(&sockaddr, 0, sizeof(sockaddr));
}

Server::~Server() {
  // close the server socket
  if (sockfd != -1) {
    close(sockfd);
  }
}

int Server::startServer(int port) {
  // configure the server address
  sockaddr.sin_family = AF_INET;         // IpV4
  sockaddr.sin_addr.s_addr = INADDR_ANY; // accept connections from anybody
  sockaddr.sin_port = htons(port);

  // Bind the socket to the specified port
  if (bind(sockfd, (struct sockaddr *)&sockaddr, sizeof(sockaddr)) < 0) {
    std::cerr << "Failed to bind to port " << port << ". errno: " << errno
              << std::endl;
    close(sockfd);
    return -1;
  }

  // start listening for incoming connections
  if (listen(sockfd, 10) < 0) { // 10 is backlog queue size
    std::cerr << "Failed to listen on socket. errno: " << errno << std::endl;
    close(sockfd);
    return -1;
  }

  std::cout << "Server is listening on port " << port << "..." << std::endl;
  return 0;
}

void Server::acceptClients() {
  while (!stop) { // keep accepting the clients until the server is stopped
    sockaddr_in clientSockaddr;
    socklen_t clientLen = sizeof(clientSockaddr);

    // Accept a new client connection
    int clientSock =
        accept(sockfd, (struct sockaddr *)&clientSockaddr, &clientLen);

    if (clientSock < 0) {
      if (stop)
        break;
      std::cerr << "Failed to accept connection. errno: " << errno << std::endl;
      continue;
    }

    // Display the client's IP address and port
    std::cout << "Accepted connection from "
              << inet_ntoa(clientSockaddr.sin_addr) << ":"
              << ntohs(clientSockaddr.sin_port) << std::endl;

    // Use lambda to pass the clientSock and invoke handleClient on the current
    // Server instance
    std::thread clientThread(
        [this, clientSock]() { this->handleClient(clientSock); });
    clientThread.detach(); // Detach the thread to run independently
  }
}

void Server::handleClient(int clientSock) {
  char buffer[1024] = {0}; // Buffer for client communication
  struct timeval timeout;
  timeout.tv_sec = 60; // Set timeout to 60 seconds
  timeout.tv_usec = 0;

  while (true) {
    fd_set readfds;
    FD_ZERO(&readfds);
    FD_SET(clientSock, &readfds); // Monitor the client socket

    // Wait for activity on the socket or timeout
    int activity = select(clientSock + 1, &readfds, NULL, NULL, &timeout);

    if (activity < 0) {
      std::cerr << "Select error. errno: " << errno << std::endl;
      break;
    }

    if (activity == 0) {
      // Timeout occurred, no activity
      std::cout << "Client is idle for too long. Closing connection."
                << std::endl;
      break; // Exit the loop, close the connection
    }

    // Check if the client has sent data
    if (FD_ISSET(clientSock, &readfds)) {
      ssize_t bytesRead = read(clientSock, buffer, sizeof(buffer) - 1);
      if (bytesRead > 0) {
        buffer[bytesRead] = '\0'; // Null-terminate the buffer
        std::cout << "Received message: " << buffer << std::endl;

        // Send an acknowledgment message back to the client
        const char *ackMessage = "ACK: Message received";
        ssize_t bytesSent = send(clientSock, ackMessage, strlen(ackMessage), 0);
        if (bytesSent < 0) {
          std::cerr << "Failed to send acknowledgment. errno: " << errno
                    << std::endl;
          break;
        } else {
          std::cout << "Sent acknowledgment: " << ackMessage << std::endl;
        }

        // Optionally, you can echo the message back to the client
        if (send(clientSock, buffer, bytesRead, 0) < 0) {
          std::cerr << "Failed to send message. errno: " << errno << std::endl;
          break;
        }
      } else if (bytesRead == 0) { // Client closed the connection
        std::cout << "Client disconnected." << std::endl;
        break;
      } else { // Error while reading
        std::cerr << "Failed to read from client. errno: " << errno
                  << std::endl;
        break;
      }
    }
  }

  // Close the client's socket
  close(clientSock);
  std::cout << "Connection with client closed." << std::endl;
}

void Server::shutdownServer() {
  stop = 1;      // Set the stop flag to true
  close(sockfd); // Close the server socket
  std::cout << "Server shutting down..." << std::endl;
}
