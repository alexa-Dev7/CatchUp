#include <iostream>
#include "websocket_server.h"
#include "storage.h"
#include "encryption.h"

int main() {
    std::cout << "Starting Chat Server..." << std::endl;

    // Initialize storage (users, messages)
    Storage storage;
    storage.loadUsers();
    storage.loadMessages();

    // Start WebSocket Server
    WebSocketServer server(8080, &storage);
    server.run();

    return 0;
}
