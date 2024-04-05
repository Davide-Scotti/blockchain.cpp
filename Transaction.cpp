#include "Transaction.h"
#include "Key.h" 

#include <openssl/evp.h>
#include <openssl/ec.h>
#include <openssl/pem.h>
#include <iostream>

Transaction::Transaction(const std::string& from, const std::string& to, double amt)
    : fromAddress(from), toAddress(to), amount(amt), signature("") {}

void Transaction::signTransaction(EC_KEY* privateKey) {
    EVP_MD_CTX* mdCtx = EVP_MD_CTX_new();
    if (!mdCtx) {
        std::cerr << "Errore nella creazione del contesto di firma." << std::endl;
        return;
    }

    EVP_PKEY* pkey = EVP_PKEY_new();
    if (!pkey) {
        std::cerr << "Errore nella creazione della chiave EVP_PKEY." << std::endl;
        EVP_MD_CTX_free(mdCtx);
        return;
    }
    if (EVP_PKEY_assign_EC_KEY(pkey, privateKey) <= 0) {
        std::cerr << "Errore nell'assegnazione della chiave privata." << std::endl;
        EVP_PKEY_free(pkey);
        EVP_MD_CTX_free(mdCtx);
        return;
    }

    if (EVP_DigestSignInit(mdCtx, NULL, EVP_sha256(), NULL, pkey) <= 0) {
        std::cerr << "Errore nell'inizializzazione della firma." << std::endl;
        EVP_PKEY_free(pkey);
        EVP_MD_CTX_free(mdCtx);
        return;
    }

    std::string transactionData = toString();
    unsigned char* hash = new unsigned char[EVP_MAX_MD_SIZE];
    size_t hashLen;
    if (EVP_DigestSignUpdate(mdCtx, (const unsigned char*)transactionData.c_str(), transactionData.size()) <= 0) {
        std::cerr << "Errore nel calcolo dell'hash." << std::endl;
        EVP_PKEY_free(pkey);
        EVP_MD_CTX_free(mdCtx);
        delete[] hash;
        return;
    }

    if (EVP_DigestSignFinal(mdCtx, NULL, &hashLen) <= 0) {
        std::cerr << "Errore nel calcolo dell'hash." << std::endl;
        EVP_PKEY_free(pkey);
        EVP_MD_CTX_free(mdCtx);
        delete[] hash;
        return;
    }

    if (EVP_DigestSignFinal(mdCtx, hash, &hashLen) <= 0) {
        std::cerr << "Errore nella firma." << std::endl;
        EVP_PKEY_free(pkey);
        EVP_MD_CTX_free(mdCtx);
        delete[] hash;
        return;
    }

    signature = std::string(reinterpret_cast<char*>(hash), hashLen);

    EVP_PKEY_free(pkey);
    EVP_MD_CTX_free(mdCtx);
    delete[] hash;
}

bool Transaction::isValid() const {
    if (fromAddress.empty() || toAddress.empty()) {
        std::cerr << "Indirizzi mittente e/o destinatario mancanti" << std::endl;
        return false;
    }

    if (amount <= 0) {
        std::cerr << "Importo non valido." << std::endl;
        return false;
    }

    // Verifico che la firma sia stata generata
    if (signature.empty()) {
        std::cerr << "Firma mancante." << std::endl;
        return false;
    }

    // Carico la chiave pubblica
    Key key;
    EC_KEY* publicKey = nullptr;
    if (key.loadPublicKey(fromAddress)) {
        publicKey = key.getECKey(); // Ottieni la chiave pubblica caricata
    } else {
        std::cerr << "Errore nel caricamento della chiave pubblica." << std::endl;
        return false;
    }

    // Verifico la firma della transazione
    if (!verifySignature(toString(), signature, publicKey)) {
        std::cerr << "Firma non valida." << std::endl;
        EC_KEY_free(publicKey);
        return false;
    }

    // Rilascio la chiave pubblica
    EC_KEY_free(publicKey);

    return true;
}

std::string Transaction::toString() const {
    return fromAddress + toAddress + std::to_string(amount);
}