#ifndef BLOCKCHAIN_H
#define BLOCKCHAIN_H

#include <cstdint>
#include <vector>
#include <iostream>

#include "Block.h"
#include "Transaction.h" // Aggiunta

class Blockchain {
    private: 
        uint32_t difficulty;
        double reward;
        std::vector<Block> chain;
        std::vector<Transaction> pendingTransactions;

        Block createGenesisBlock();
        bool isChainValid() const;

    public: 
        // Costruttore base
        Blockchain();

        // Costruttore con campi
        Blockchain(uint32_t diff, double rew);

        // Aggiunge una transazione alla lista delle transazioni in sospeso
        void addTransaction(const Transaction& transaction);

        // Minare un nuovo blocco contenente le transazioni in sospeso
        void minePendingTransactions(const std::string& minerAddress);

        // Stampa la blockchain
        void printChain() const;

        // Verifica e correggi la validità della blockchain se necessario
        void validateChain();
};

#endif //BLOCKCHAIN_H
