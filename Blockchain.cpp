#include "Blockchain.h"

Blockchain::Blockchain() : difficulty(4), reward(10.0) {
    chain.emplace_back(createGenesisBlock());
}

Blockchain::Blockchain(uint32_t diff, double rew) : difficulty(diff), reward(rew) {
    chain.emplace_back(createGenesisBlock());
}

Block Blockchain::createGenesisBlock() {
    return Block(0, "Genesis Block", "0");
}

void Blockchain::addTransaction(const Transaction& transaction) {
    pendingTransactions.push_back(transaction);
}

void Blockchain::minePendingTransactions(const std::string& minerAddress) {
    Block block(chain.back().getIndex() + 1, pendingTransactions);
    block.mineBlock(difficulty);
    chain.push_back(block);
    pendingTransactions.clear();

    Transaction rewardTransaction("Reward", minerAddress, reward);
    pendingTransactions.push_back(rewardTransaction);
}

void Blockchain::printChain() const {
    for (const auto &block : chain) {
        std::cout << "Block #" << block.getIndex() << " - Timestamp: " << block.getTimestamp()
                  << " - Nonce: " << block.getNonce() << " - Hash: " << block.getHash()
                  << " - Previous Hash: " << block.getPreviousHash() << std::endl;

        std::cout << "Transactions:" << std::endl;
        for (const auto &transaction : block.getTransactions()) {
            std::cout << "\t" << transaction.getSender() << " -> " << transaction.getRecipient()
                      << ": " << transaction.getAmount() << " coins" << std::endl;
        }
        std::cout << std::endl;
    }
}

bool Blockchain::isChainValid() const {
    for(uint32_t i = 1; i < chain.size(); ++i){
        const Block &currentBlock = chain[i];
        const Block &previousBlock = chain[i - 1];

        if(currentBlock.getHash() != currentBlock.calculateHash()) {
            return false;
        }

        if(currentBlock.getPreviousHash() != previousBlock.getHash()) {
            return false;
        }
    }

    return true;
}

void Blockchain::validateChain() {
    for(uint32_t i = 1; i < chain.size(); ++i) {
        Block &currentBlock = chain[i];
        Block &previousBlock = chain[i - 1];

        currentBlock.setPreviousHash(previousBlock.getHash());
        currentBlock.mineBlock(difficulty);
    }
}
