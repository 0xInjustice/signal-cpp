#include "server/server.h"

// Global pointer to access the Server instance
Server *globalServer = nullptr;

// Signal handler for shutting down the server gracefully
void signalHandler(int signal) {
  std::cout << "Signal " << signal << " received. Stopping server..."
            << std::endl;
  if (globalServer) {
    globalServer->shutdownServer();
  }
}

int main(int argc, char *argv[]) {
  Server server;

  // Assign the global pointer to the Server instance
  globalServer = &server;

  // Register the signal handler for Ctrl+C (SIGINT)
  signal(SIGINT, signalHandler);

  int port = 8080; // Default port number for the server

  // Check if the user has provided a port number as an argument
  if (argc > 1) {
    port = std::atoi(argv[1]);       // Convert the argument to an integer
    if (port <= 0 || port > 65535) { // Validate the port number
      std::cerr << "Invalid port number. Using default port 8080." << std::endl;
      port = 8080;
    }
  }

  std::cout << "Server starting on port " << port << "..." << std::endl;

  // Start the server
  if (server.startServer(port) < 0) {
    return -1;
  }

  // Handle clients in the main loop
  server.acceptClients();

  // Shut down the server gracefully
  server.shutdownServer();
  return 0;
}

