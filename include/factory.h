#pragma once

#include <string>
#include <vector>

#include <schnorr.h>

namespace crypto {
    class ClientFactory
    {
    public:
        ClientFactory() = default;
        ~ClientFactory();

        schnorr* createClient(std::string& name);
        schnorr* findByName(std::string& name);

        std::vector<schnorr*> clientPtrs;
    };
} // namespace crypto