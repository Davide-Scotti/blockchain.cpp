#include "Key.h"

#include <openssl/ec.h>
#include <openssl/pem.h>
#include <openssl/err.h>
#include <iostream>

Key::Key() : ecKey(nullptr) {}

Key::~Key() {
    if (ecKey != nullptr)
        EC_KEY_free(ecKey);
}

bool Key::generateKey() {
    EC_KEY* key = EC_KEY_new_by_curve_name(NID_secp256k1);
    if(!key) {
        std::cerr << "Errore nella creazione della chiave." << std::endl:
        return false;
    }

    if(!EC_KEY_generate_key(key)) {
        std::cerr << "Errore nella generazione della chiave." << std::endl;
        EC_KEY_free(key);
        return false;
    }

    ecKey = key;
    return true;
}

EC_KEY* Key::getECKey() const {
    return ecKey;
}

std::string Key::getPublicKeyPEM() const {
    if(!ecKey) {
        std::cerr << "Chiave privata non valida." << std::endl;
        return "";
    }

    BIO* bio = BIO_new(BIO_s_mem());
    PEM_write_bio_EC_PUBKEY(bio, ecKey);

    char* buffer;
    long length = BIO_get_mem_data(bio, &buffer);
    std::string result(buffer, length);

    BIO_free(bio); 

    return result;
}

std::string Key::getPrivateKeyPEM() const {
    if(!ecKey) {
        std::cerr << "Chiave privata non valida." << std::endl;
        return "";
    }

    BIO* bio = BIO_new(BIO_s_mem());
    PEM_write_bio_ECPrivateKey(bio, ecKey, NULL, NULL, 0, NULL, NULL);

    char* buffer;
    long length = BIO_get_mem_data(bio, &buffer);

    BIO_free(bio);

    return result;
}