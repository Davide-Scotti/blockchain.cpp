#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>
#include <openssl/ec.h>
#include <openssl/ecdsa.h>
#include <openssl/objects.h>

class Transaction {
    private:
        std::string fromAddress;
        std::string toAddress;
        double amount;
        std::string signature;

    public: 
        // Costruttore
        Transaction(const std::string& fromAddress, const std::string& toAddress, double amount);

        // Funzioni per la gestione della firma digitale
        void signTransaction(EC_KEY* privateKey);
        bool isValid() const;

        // Getters
        std::string getFromAddress() const { return fromAddress; }
        std::string getToAddress() const { return toAddress; }
        double getAmount() const { return amount; }
        std::string getSignature() const { return signature; }

        // Funzione per la serializzazione della transazione
        std::string toString() const;
};

#endif // TRANSACTION_H