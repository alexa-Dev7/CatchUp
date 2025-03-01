#ifndef WEBSOCKET_SERVER_H
#define WEBSOCKET_SERVER_H

#include <uWS/uWS.h>
#include <unordered_map>
#include <string>
#include "storage.h"

class WebSocketServer {
public:
    WebSocketServer(int port, Storage* storage);
    void run();

private:
    int port;
    Storage* storage;
    uWS::Hub h;

    void handleLogin(uWS::WebSocket<uWS::SERVER> *ws, std::string message);
    void handleRegister(uWS::WebSocket<uWS::SERVER> *ws, std::string message);
    void handleChat(uWS::WebSocket<uWS::SERVER> *ws, std::string message);
};

#endif
