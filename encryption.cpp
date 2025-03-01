#include "encryption.h"
#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <openssl/aes.h>

std::string Encryption::encryptMessage(const std::string& message) {
    // Simple encryption placeholder
    std::string encrypted = message;
    for (char& c : encrypted) c += 1;
    return encrypted;
}

std::string Encryption::decryptMessage(const std::string& message) {
    std::string decrypted = message;
    for (char& c : decrypted) c -= 1;
    return decrypted;
}
