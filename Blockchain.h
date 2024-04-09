#ifndef BLOCKCHAIN_H
#define BLOCKCHAIN_H

#include <cstdint>
#include <vector>
#include <iostream>
#include "Block.h"
#include "Transaction.h" // Assicurati di avere la classe Transaction definita

class Blockchain {
private:
    uint32_t difficulty;
    double reward;
    std::vector<Block> chain;
    std::vector<Transaction> pendingTransactions;

    Block createGenesisBlock();
    bool isChainValid() const;

public:
    Blockchain();
    Blockchain(uint32_t diff, double rew);

    void addTransaction(const Transaction& transaction);
    void minePendingTransactions(const std::string& minerAddress);
    void printChain() const;
    void validateChain();
};

#endif // BLOCKCHAIN_H
