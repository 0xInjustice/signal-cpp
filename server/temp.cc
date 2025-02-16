#include <arpa/inet.h>
#include <cerrno>
#include <cstring>
#include <iostream>
#include <mutex>
#include <netinet/in.h>
#include <string>
#include <sys/select.h>
#include <sys/socket.h>
#include <thread>
#include <unistd.h>

class Server {
public:
  Server();
  ~Server();

  int startServer(int port);
  void acceptClients();
  void stopServer();

  // New function that saves the received data into a variable
  void databse(const std::string &data);

  // New function that sends the stored data back to the client
  void request(int clientSock);

private:
  void handleClient(int clientSock);

  int sockfd;
  struct sockaddr_in sockaddr;
  volatile bool stop;
  std::string dataStorage; // This variable simulates our "database"
  std::mutex dataMutex;    // Protects access to dataStorage
};

Server::Server() : stop(false), sockfd(-1) {
  // Create the server socket
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd == -1) {
    std::cerr << "Failed to create a socket" << std::endl;
    exit(EXIT_FAILURE);
  }
  memset(&sockaddr, 0, sizeof(sockaddr));
}

Server::~Server() {
  if (sockfd != -1) {
    close(sockfd);
  }
}

int Server::startServer(int port) {
  // Configure the server address
  sockaddr.sin_family = AF_INET;         // IPv4
  sockaddr.sin_addr.s_addr = INADDR_ANY; // Accept connections from any IP
  sockaddr.sin_port = htons(port);

  // Bind the socket to the specified port
  if (bind(sockfd, (struct sockaddr *)&sockaddr, sizeof(sockaddr)) < 0) {
    std::cerr << "Failed to bind to port " << port << ". errno: " << errno
              << std::endl;
    close(sockfd);
    return -1;
  }

  // Start listening for incoming connections (backlog of 10)
  if (listen(sockfd, 10) < 0) {
    std::cerr << "Failed to listen on socket. errno: " << errno << std::endl;
    close(sockfd);
    return -1;
  }

  std::cout << "Server is listening on port " << port << "..." << std::endl;
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

void Server::handleClient(int clientSock) {
  char buffer[1024] = {0};
  struct timeval timeout;
  timeout.tv_sec = 60; // 60-second timeout for idle clients
  timeout.tv_usec = 0;

  while (true) {
    fd_set readfds;
    FD_ZERO(&readfds);
    FD_SET(clientSock, &readfds);

    int activity = select(clientSock + 1, &readfds, nullptr, nullptr, &timeout);
    if (activity < 0) {
      std::cerr << "Select error. errno: " << errno << std::endl;
      break;
    }

    if (activity == 0) {
      std::cout << "Client idle for too long. Closing connection." << std::endl;
      break;
    }

    if (FD_ISSET(clientSock, &readfds)) {
      ssize_t bytesRead = read(clientSock, buffer, sizeof(buffer) - 1);
      if (bytesRead > 0) {
        buffer[bytesRead] = '\0';
        std::cout << "Received message: " << buffer << std::endl;

        // Check if the client sent a "request" command
        if (strncmp(buffer, "request", 7) == 0) {
          request(clientSock);
        } else {
          // Otherwise, store the message in our "database"
          databse(std::string(buffer));
          const char *ack = "Data saved";
          ssize_t bytesSent = send(clientSock, ack, strlen(ack), 0);
          if (bytesSent < 0) {
            std::cerr << "Failed to send acknowledgment. errno: " << errno
                      << std::endl;
            break;
          }
        }
      } else if (bytesRead == 0) {
        std::cout << "Client disconnected." << std::endl;
        break;
      } else {
        std::cerr << "Failed to read from client. errno: " << errno
                  << std::endl;
        break;
      }
    }
  }

  // Close the client's socket and clean up
  close(clientSock);
  std::cout << "Connection with client closed." << std::endl;
}

void Server::stopServer() {
  stop = true;
  close(sockfd);
  std::cout << "Server shutting down..." << std::endl;
}

void Server::databse(const std::string &data) {
  // Lock the mutex to safely update the data storage
  std::lock_guard<std::mutex> lock(dataMutex);
  dataStorage = data; // Here we simply overwrite the stored data.
  std::cout << "Data stored in database variable: " << dataStorage << std::endl;
}

void Server::request(int clientSock) {
  std::lock_guard<std::mutex> lock(dataMutex);
  if (!dataStorage.empty()) {
    ssize_t bytesSent =
        send(clientSock, dataStorage.c_str(), dataStorage.size(), 0);
    if (bytesSent < 0) {
      std::cerr << "Failed to send data. errno: " << errno << std::endl;
    }
  } else {
    const char *msg = "No data available";
    send(clientSock, msg, strlen(msg), 0);
  }
}

int main() {
  Server server;
  int port = 8080;
  if (server.startServer(port) == 0) {
    std::thread acceptThread(&Server::acceptClients, &server);
    std::cout << "Press Enter to stop the server..." << std::endl;
    std::cin.get();
    server.stopServer();
    acceptThread.join();
  }
  return 0;
}
