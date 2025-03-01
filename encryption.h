#ifndef ENCRYPTION_H
#define ENCRYPTION_H

#include <string>

class Encryption {
public:
    static std::string encryptMessage(const std::string& message);
    static std::string decryptMessage(const std::string& message);
};

#endif
