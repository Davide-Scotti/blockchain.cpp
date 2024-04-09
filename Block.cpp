#include "Block.h"
#include <sstream>
#include <iomanip>

Block::Block(uint32_t index, const std::string &data) : index(index), data(data) {
    nonce = 0;
    timestamp = time(nullptr);
    previousHash = "";
}

std::string Block::calculateHash() const {
    std::stringstream ss;
    ss << index << timestamp << data << nonce << previousHash;
    return ss.str(); // In questa implementazione semplificata, utilizziamo solo una concatenazione di stringhe come hash
}

uint32_t Block::getIndex() const {
    return index;
}

uint64_t Block::getNonce() const {
    return nonce;
}

time_t Block::getTimestamp() const {
    return timestamp;
}

void Block::setTimestamp(time_t ts) {
    timestamp = ts;
}

void Block::mineBlock(uint32_t difficulty) {
    std::string target(difficulty, '0');
    while (getHash().substr(0, difficulty) != target) {
        nonce++;
    }
}

std::string Block::getHash() const {
    return calculateHash();
}

std::string Block::getPreviousHash() const {
    return previousHash;
}

void Block::setPreviousHash(const std::string &prevHash) {
    previousHash = prevHash;
}

void Block::setData(const std::string &dataValue) {
    data = dataValue;
}
