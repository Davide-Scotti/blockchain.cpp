#include <string>

#include "Block.h"

#include <sstream>
#include <ctime>
#include <iomanip>
#include <cstring>
#include <openssl/sha.h>

// Costruttore
Block::Block(uint32_t index, const std::string &data) : index(index), data(data) {
    nonce = 0;
    timestamp = time(nullptr);
    previousHash = "";
}

// Funzione privata per calcolare l'hash
std::string Block::calculateHash() const {
    std::stringstream ss;
    ss << index << timestamp << data << nonce << previousHash;
    return sha256(ss.str());
}

// Funzione per minare il blocco
void Block::mineBlock(uint32_t difficulty) {
    std::string target(difficulty, '0');
    while (getHash().substr(0, difficulty) != target){
        nonce++;
    }
}

// Getter per l'hash del blocco
std::string Block::getHash() const {
    return calculateHash();
}

// Getter per l'hash del blocco precedente
std::string Block::getPreviousHash() const {
    return previousHash;
}

std::string sha256(const std::string& input) {
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, input.c_str(), input.length());
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_Final(hash, &sha256);
    std::stringstream ss;
    for(int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
        ss << std::hex << std::setw(2) << std::setfill('0') << (int)hash[i];
    }
    return ss.str();
}