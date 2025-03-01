#include "storage.h"
#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>
#include <bcrypt.h>

using json = nlohmann::json;

Storage::Storage() {}

void Storage::loadUsers() {
    std::ifstream file("users.json");
    if (!file) return;

    json data;
    file >> data;
    for (auto& [key, value] : data.items()) {
        users[key] = value;
    }
}

void Storage::loadMessages() {
    std::ifstream file("messages.json");
    if (!file) return;

    json data;
    file >> data;
    for (auto& message : data) {
        messages.push_back(message);
    }
}

bool Storage::addUser(std::string username, std::string password) {
    if (users.find(username) != users.end()) return false;

    char hashed[60];
    bcrypt_hashpw(password.c_str(), bcrypt_gensalt(), hashed);
    users[username] = std::string(hashed);

    saveUsers();
    return true;
}

bool Storage::validateUser(std::string username, std::string password) {
    if (users.find(username) == users.end()) return false;

    return bcrypt_checkpw(password.c_str(), users[username].c_str()) == 0;
}

void Storage::storeMessage(std::string sender, std::string receiver, std::string message) {
    messages.push_back(sender + " -> " + receiver + ": " + message);
    saveMessages();
}

void Storage::saveUsers() {
    json data(users);
    std::ofstream file("users.json");
    file << data.dump(4);
}

void Storage::saveMessages() {
    json data(messages);
    std::ofstream file("messages.json");
    file << data.dump(4);
}
