#ifndef STORAGE_H
#define STORAGE_H

#include <string>
#include <unordered_map>
#include <vector>

class Storage {
public:
    Storage();
    void loadUsers();
    void loadMessages();
    bool addUser(std::string username, std::string password);
    bool validateUser(std::string username, std::string password);
    void storeMessage(std::string sender, std::string receiver, std::string message);

private:
    std::unordered_map<std::string, std::string> users;
    std::vector<std::string> messages;
    void saveUsers();
    void saveMessages();
};

#endif
