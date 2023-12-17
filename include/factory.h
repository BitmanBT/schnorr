#pragma once

#include <string>
#include <vector>

#include <schnorr.h>
#include <hacker.h>

namespace crypto {
    class ClientFactory
    {
    public:
        ClientFactory() = default;
        ~ClientFactory();

        schnorr* createClient(std::string& name);
        schnorr* findByName(std::string& name);

        std::vector<schnorr*> clientPtrs;
        hacker Hacker;
    };
} // namespace crypto