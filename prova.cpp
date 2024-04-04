#include "Key.h"
#include "Transaction.h"

#include <iostream>


int main(){
    // Genero una copia di chiavi pub/priv
    Key key;
    if(!key.generateKey()) {
        std::cerr << "Errore nella generazione delle chiavi." << std::endl;
        return 1;
    }

    // Creo una transazione
    Transaction transaction("mittente", "destinatario", 10.0);

    // Ottengo la chiave privata e firmo la transazione
    EC_KEY* privateKey = key.getECKey();
    transaction.signTransaction(privateKey);

    // Verifico la validità della transazione
    if(transaction.isValid()) {
        std::cout << "Transazione valida." << std::endl;
    } else {
        std::cout << "Transazione non valida." << std::endl;
    }

    return 0;
}