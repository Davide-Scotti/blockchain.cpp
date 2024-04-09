#ifndef KEY_H
#define KEY_H

#include <string>
#include <iostream>
#include <random>
#include <iomanip>

class Key {
private:
    std::string publicKey;
    std::string privateKey;

    std::string generateRandomHex(const size_t len) const;

public:
    Key();
    ~Key();

    bool generateKeyPair();
    std::string getPublicKey() const;
    std::string getPrivateKey() const;
    std::string sign(const std::string& data) const;
};

#endif // KEY_H
