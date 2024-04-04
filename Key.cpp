#include "Key.h"
#include <openssl/ec.h>
#include <openssl/pem.h>
#include <iostream>

Key::Key() : ecKey(EC_KEY_new()) {
    if (!ecKey) {
        std::cerr << "Errore nella creazione della chiave." << std::endl;
    }
}

Key::~Key() {
    EC_KEY_free(ecKey);
}

bool Key::generateKey() {
    if (!EC_KEY_generate_key(ecKey)) {
        std::cerr << "Errore nella generazione della chiave." << std::endl;
        return false;
    }
    return true;
}

std::string Key::getPublicKeyPEM() const {
    BIO* bio = BIO_new(BIO_s_mem());
    if (!bio) {
        std::cerr << "Errore nella creazione di BIO." << std::endl;
        return "";
    }
    if (!PEM_write_bio_EC_PUBKEY(bio, ecKey)) {
        std::cerr << "Errore nella scrittura della chiave pubblica." << std::endl;
        return "";
    }
    char* buffer;
    long length = BIO_get_mem_data(bio, &buffer);
    std::string result(buffer, length);
    BIO_free(bio);
    return result;
}

std::string Key::getPrivateKeyPEM() const {
    BIO* bio = BIO_new(BIO_s_mem());
    if (!bio) {
        std::cerr << "Errore nella creazione di BIO." << std::endl;
        return "";
    }
    if (!PEM_write_bio_ECPrivateKey(bio, ecKey, NULL, NULL, 0, NULL, NULL)) {
        std::cerr << "Errore nella scrittura della chiave privata." << std::endl;
        return "";
    }
    char* buffer;
    long length = BIO_get_mem_data(bio, &buffer);
    std::string result(buffer, length);
    BIO_free(bio);
    return result;
}