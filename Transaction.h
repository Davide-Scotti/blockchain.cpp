#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>
#include "Key.h" // Include la classe Key per la firma

class Transaction {
private:
    std::string fromAddress;
    std::string toAddress;
    double amount;
    std::string signature;

public:
    // Costruttore
    Transaction(const std::string& from, const std::string& to, double amt);

    // Funzione per la firma della transazione
    void signTransaction(const Key& privateKey);

    // Funzione per la verifica della firma
    bool isValid() const;

    // Getters
    std::string getFromAddress() const { return fromAddress; }
    std::string getToAddress() const { return toAddress; }
    double getAmount() const { return amount; }
    std::string getSignature() const { return signature; }

    // Funzione per la rappresentazione testuale della transazione
    std::string toString() const;
};

#endif // TRANSACTION_H
