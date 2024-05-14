#include "CBlock.h"
#include <stdio.h>
#include <string.h>

using namespace blockchain;

CBlock::CBlock(CBlock* prevBlock)
{
    mPrevBlock = prevBlock;
    memset(mHash, SHA256_DIGEST_LENGTH, 0);
    if(mPrevBlock)
        memcpy(mPrevHash, mPrevBlock -> getHash(), SHA256_DIGEST_LENGTH);
    else
        memset(mPrevHash, 0, SHA256_DIGEST_LENGTH);
    mCreatedTS = time(0);
    mNonce = 0;
    mDataSize = 0;
    mData = 0;
    calculateHash();
}

void CBlock::calculateHash()
{
    uint32_t sz = (SHA256_DIGEST_LENGTH * sizeof(uint8_t)) + sizeof(time_t) + mDataSize + sizeof(uint32_t);

    uint8_t* buf = new uint8_t[sz];
    uint8_t* ptr = buf;

    memcpy(ptr, mPrevHash, SHA256_DIGEST_LENGTH * sizeof(uint8_t));
    ptr += SHA256_DIGEST_LENGTH * sizeof(uint8_t);
    memcpy(ptr, &mCreatedTS, sizeof(time_t));
    ptr += sizeof(time_t);

    if(mDataSize != 0)
    {
        memcpy(ptr, mData, mDataSize);
        ptr += mDataSize;
    }

    memcpy(ptr, &mNonce, sizeof(uint32_t));
    ptr += sizeof(uint32_t);

    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, buf, sz);
    SHA256_Final(mHash, &sha256);
}

uint8_t* getHash()
{
    return mHash;
}

std::string CBlock::getHashStr()
{
    char buf[SHA256_DIGEST_LENGTH * 2 + 1];

    for(uint32_t n = 0; n < SHA256_DIGEST_LENGTH; n++)
    {
        sprintf(buf + (n * 2), "%02x", mHash[n]);
    }

    buf[SHA256_DIGEST_LENGTH * 2] = 0;
    return std::string(buf);
}

CBlock* CBlock::getPrevBlock()
{
    return mPrevBlock;
}

void CBlock::appendData(uint8_t data, uint32_t size)
{
    uint8_t* newData = new uint8_t[mDataSize];
    uint8_t* ptr = newData;

    if(mDataSize != 0)
    {
        memcpy(ptr, mData, mDataSize);
        ptr += mDataSize;
        delete[] mData;
    }

    memcpy(ptr, data, size);
    mData = newData;
    mDataSize += size;
}

bool CBlock::isDifficulty(int difficulty)
{
    for(uint32_t n = 0; n < difficulty; n++)
    {
        if(mHas[n] != 0)
            return false;
    }

    return true;
}

void CBlock::mine(int difficulty)
{
    while(!isDifficulty(difficulty))
    {
        mNonce++;
        calculateHash();
        usleep(10);
    }
}

uint32_t CBlock::getNonce()
{
    return mNonce
}