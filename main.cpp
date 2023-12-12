#include <iostream>

#include <schnorr.h>
#include <hacker.h>

int main() {
    crypto::Server server;

    crypto::schnorr A("Alice");
    A.generateKeys(server);
    std::cout << A.pub_k << std::endl;

    std::string out = server.authentification(A);
    std::cout << out << std::endl;

    crypto::schnorr V("Vanya");
    V.generateKeys(server);
    out = server.authentification(V);
    std::cout << out << std::endl;
  
    std::string M;
    std::cin >> M;
    A.sign(M);
    std::cout << V.verify(V.mSign) << std::endl;

    crypto::hacker Hacker(A, server);
}