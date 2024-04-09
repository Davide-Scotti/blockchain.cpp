#ifndef BLOCK_H
#define BLOCK_H

#include <cstdint>
#include <iostream>
#include <string>
#include <ctime>

class Block {
private:
    uint32_t index;
    uint64_t nonce;
    std::string data;
    std::string previousHash;
    time_t timestamp;

    std::string calculateHash() const;

public:
    Block(uint32_t index, const std::string &data);

    uint32_t getIndex() const;
    uint64_t getNonce() const;
    time_t getTimestamp() const;
    void setTimestamp(time_t ts);
    void mineBlock(uint32_t difficulty);
    std::string getHash() const;
    std::string getPreviousHash() const;
    void setPreviousHash(const std::string &prevHash);
    void setData(const std::string &dataValue);
};

#endif // BLOCK_H
