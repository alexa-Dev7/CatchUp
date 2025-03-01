#include "websocket_server.h"
#include <iostream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

WebSocketServer::WebSocketServer(int port, Storage* storage) : port(port), storage(storage) {}

void WebSocketServer::run() {
    h.onMessage([this](uWS::WebSocket<uWS::SERVER> *ws, char *message, size_t length, uWS::OpCode opCode) {
        std::string msg(message, length);
        json data = json::parse(msg);

        std::string type = data["type"];
        if (type == "login") {
            handleLogin(ws, msg);
        } else if (type == "register") {
            handleRegister(ws, msg);
        } else if (type == "chat") {
            handleChat(ws, msg);
        }
    });

    h.listen(port);
    std::cout << "Server running on port " << port << std::endl;
    h.run();
}

void WebSocketServer::handleLogin(uWS::WebSocket<uWS::SERVER> *ws, std::string message) {
    json data = json::parse(message);
    std::string username = data["username"];
    std::string password = data["password"];

    if (storage->validateUser(username, password)) {
        ws->send("Login successful", uWS::OpCode::TEXT);
    } else {
        ws->send("Invalid credentials", uWS::OpCode::TEXT);
    }
}

void WebSocketServer::handleRegister(uWS::WebSocket<uWS::SERVER> *ws, std::string message) {
    json data = json::parse(message);
    std::string username = data["username"];
    std::string password = data["password"];

    if (storage->addUser(username, password)) {
        ws->send("Registration successful", uWS::OpCode::TEXT);
    } else {
        ws->send("Username already exists", uWS::OpCode::TEXT);
    }
}

void WebSocketServer::handleChat(uWS::WebSocket<uWS::SERVER> *ws, std::string message) {
    json data = json::parse(message);
    std::string sender = data["sender"];
    std::string receiver = data["receiver"];
    std::string msg = data["message"];

    storage->storeMessage(sender, receiver, msg);
    ws->send("Message sent", uWS::OpCode::TEXT);
}
