#include "Key.h"

Key::Key() {}

Key::~Key() {}

std::string Key::generateRandomHex(const size_t len) const {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 15);

    std::stringstream ss;
    for (size_t i = 0; i < len; ++i) {
        ss << std::hex << dis(gen);
    }

    return ss.str();
}


bool Key::generateKeyPair() {
    publicKey = generateRandomHex(64);
    privateKey = generateRandomHex(128);
    return true;
}

std::string Key::getPublicKey() const {
    return publicKey;
}

std::string Key::getPrivateKey() const {
    return privateKey;
}

std::string Key::sign(const std::string& data) const {
    return data + privateKey;
}
