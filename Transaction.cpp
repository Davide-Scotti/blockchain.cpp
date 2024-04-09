#include "Transaction.h"

Transaction::Transaction(const std::string& from, const std::string& to, double amt)
    : fromAddress(from), toAddress(to), amount(amt), signature("") {}

void Transaction::signTransaction(const Key& privateKey) {
    std::string dataToSign = fromAddress + toAddress + std::to_string(amount);
    signature = privateKey.sign(dataToSign);
}

bool Transaction::isValid() const {

    return true;
}

std::string Transaction::toString() const {
    return fromAddress + toAddress + std::to_string(amount);
}