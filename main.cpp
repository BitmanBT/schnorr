#include <iostream>

#include "schnorr.h"
#include "hacker.h"

int main()
{
    crypto::schnorr A;
    A.generateKeys();
    std::cout << A.pub_k << std::endl;

    std::string M;
    std::cin >> M;
    A.sign(M);
    std::cout << A.verify(A.mSign) << std::endl;
}