#ifndef BLOCK_H
#define BLOCK_H

#include <cstdint>
#include <iostream>

class Block {
private:
    uint32_t index;
    uint64_t nonce;
    std::string data;
    std::string previousHash;
    time_t timestamp;

    std::string calculateHash() const;

public:
    // Costruttore
    Block(uint32_t index, const std::string &data);

    // Getter per l'indice del blocco
    uint32_t getIndex() const { return index; }

    // Getter per il nonce
    uint64_t getNonce() const { return nonce; }

    // Getter per il timestamp
    time_t getTimestamp() const { return timestamp; }

    // Setter per il timestamp
    void setTimestamp(time_t ts) { timestamp = ts; }

    // Funzione per minare il blocco
    void mineBlock(uint32_t difficulty);

     // Getter per l'hash del blocco
    std::string getHash() const;

    // Getter per l'hash del blocco precedente
    std::string getPreviousHash() const;

    // Setter per l'hash del blocco precedente 
    void setPreviousHash(const std::string &prevHash) { previousHash = prevHash; }

    // Setter per i dati del blocco
    void setData(const std::string &dataValue) { data = dataValue; }
};

#endif //BLOCK_H
