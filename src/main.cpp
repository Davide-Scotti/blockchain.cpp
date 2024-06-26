#include "blockchain/CChain.h"
#include <iostream>

using namespace std;
using namespace blockchain;

int main(int argc, char **argv)
{
    cout << "Start.\n";

    CChain chain(1);
    cout << "Chain initialized!\n";

    CBlock* genesis = chain.getCurrentBlock();

    uint8_t* garbage = new uint8_t[32];
    for(uint32_t n = 0; n < 32; n++)
        garbage[n] = time(0) % 255;
    
    cout << "Garbage generated. \n";

    chain.appendToCurrentBlock(garbage, 32);
    delete[] garbage;

    cout << "Garbage appended to current block.\n";

    chain.nextBlock();

    cout << "Next block mined.\n";

    cout << "Genesis hash: " << chain.getCurrentBlock() -> getPrevBlock() -> getHashStr() << "\nNonce: " << chain.getCurrentBlock() -> getNonce() << "\n";

    garbage = new uint8_t[32];
    for(uint32_t n = 0; n < 32; n++)
        garbage[n] = time(0) % 255;

    cout << "Garbage generated. \n";

    chain.appendToCurrentBlock(garbage, 32);
    delete[] garbage;

    cout << "Garbage appended to current block.\n";

    chain.nextBlock();

    cout << "Next block mined.\n";

    cout << "Previous hash: " << chain.getCurrentBlock() -> getPrevBlock() -> getHashStr() << "\nNonce: " << chain.getCurrentBlock() -> getNonce() << "\n";


    return 0;
}