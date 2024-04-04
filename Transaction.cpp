#include "Transaction.h"
#include <openssl/evp.h>
#include <openssl/pem.h>
#include <openssl/err.h>
#include <cstring>
#include <iostream>

Transaction::Transaction(const std::string& from, const std::string& to, double amt)
    : fromAddress(from), toAddress(to), amount(amt), signature("") {}

void Transaction::signTransaction(EC_KEY* privateKey) {
    // Creo un contesto di firma
    EVP_MD_CTX* mdCtx = EVP_MD_CTX_new();
    if (!mdCtx) {
        std::cerr << "Errore nella creazione del contesto di firma." << std::endl;
        return;
    }

    if (EVP_DigestSignInit(mdCtx, NULL, EVP_sha256(), NULL, privateKey) <= 0) {
        std::cerr << "Errore nell'inizializzazione della firma." << std::endl;
        EVP_MD_CTX_free(mdCtx);
        return;
    }

    // Calcolo l'hash della transazione
    std::string transactionData = toString();
    unsigned char* hash = new unsigned char[EVP_MAX_MD_SIZE];
    unsigned int hashLen;
    if (EVP_DigestSign(mdCtx, NULL, &hashLen, (const unsigned char*)transactionData.c_str(), transactionData.size()) <= 0) {
        std::cerr << "Errore nel calcolo dell'hash." << std::endl;
        EVP_MD_CTX_free(mdCtx);
        delete[] hash;
        return;
    }

    if (EVP_DigestSign(mdCtx, hash, &hashLen, (const unsigned char*)transactionData.c_str(), transactionData.size()) <= 0) {
        std::cerr << "Errore nel calcolo dell'hash." << std::endl;
        EVP_MD_CTX_free(mdCtx);
        delete[] hash;
        return;
    }

    // Firma l'hash
    size_t sigLen;
    unsigned char* sig = new unsigned char[EVP_PKEY_size(EC_KEY_get0_public_key(privateKey))];
    if (EVP_SignFinal(mdCtx, sig, &sigLen, privateKey) <= 0) {
        std::cerr << "Errore nella firma." << std::endl;
        EVP_MD_CTX_free(mdCtx);
        delete[] hash;
        delete[] sig;
        return;
    }

    // Converti la firma in una stringa esadecimale per la memorizzazione
    signature = std::string(reinterpret_cast<char*>(sig), sigLen);

    EVP_MD_CTX_free(mdCtx);
    delete[] hash;
    delete[] sig;
}

bool Transaction::isValid(){
    if(fromAddress.empty() || toAddress.empty()) {
        std::cerr << "Indirizzi mittente e/o destinatario mancanti" << std::endl;
        return false;
    }

    if(amount <= 0) {
        std::cerr << "Importo non valido." << std::endl;
        return false;
    }

    return true;
}

std::string Transaction::toString() const {
    return fromAddress + toAddress + std::to_string(amount);
}