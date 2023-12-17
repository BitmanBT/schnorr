#include <factory.h>

namespace crypto {
    ClientFactory::~ClientFactory() {
        for (auto& elem : clientPtrs) {
            delete elem;
        }
    }
    
    schnorr* ClientFactory::createClient(std::string& name) {
        schnorr* out = new schnorr(name);
        clientPtrs.push_back(out);
        return out;
    }

    schnorr* ClientFactory::findByName(std::string& name) {
        if (clientPtrs.empty())
            return nullptr;
        
        for (auto& elem : clientPtrs) {
            if (elem->name_ == name) {
                return elem;
            }
        }

        return nullptr;
    }
} // namespace crypto