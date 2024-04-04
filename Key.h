#ifndef KEY_H
#define KEY_H

#include <string>
#include <openssl/ec.h>

class Key {
    private: 
        EC_KEY* ecKey;

    public:
        Key();
        ~Key();

        bool generateKey();
        EC_KEY* getECKey() const;
        std::string getPublicKeyPEM() const;
        std::string getPrivateKeyPEM() const;
};

#endif // KEY_H