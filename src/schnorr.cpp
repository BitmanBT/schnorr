#include "schnorr.h"
#include "nmath.h"

namespace crypto {
    schnorr::schnorr(std::string name) : name_(name) { }
    
    void schnorr::generateKeys(Server& server) {
        pub_k.p = math::getBigPrime();  // p
        std::vector<uint64_t> factors = math::getPrimeFactors(pub_k.p - 1);
        pub_k.q = factors[factors.size() - 1];  // q
        pub_k.g = math::getGenerator(pub_k.p, pub_k.q);  // g
        pr_k.w = math::getRandomUpLimit(pub_k.q);  // w
        pub_k.y = math::powmod(pub_k.g, pub_k.q-pr_k.w, pub_k.p);  // y

        auto forServer = std::make_pair(pub_k, name_);
        server.setNewMember(forServer);
    }

    std::vector<uint64_t> schnorr::give_authentification_info() {
        uint64_t r = math::getRandomUpLimit(pub_k.q);
        uint64_t x = math::powmod(pub_k.g, r, pub_k.p);
        uint64_t s = r + math::mulmod(pr_k.w, auth.e, pub_k.q);

        std::vector<uint64_t> out{ x, s };
        return out;
    }

    void schnorr::sign(std::string& M) {
        mSign.M = M;

        uint64_t r = math::getRandomUpLimit(pub_k.q);
        uint64_t x = math::powmod(pub_k.g, r, pub_k.p);

        mSign.s1 = std::hash<std::string>{}(M) + std::hash<uint64_t>{}(x);
        mSign.s2 = (r + math::mulmod(pr_k.w, mSign.s1, pub_k.q)) % pub_k.q;
    }

    bool schnorr::verify(const messageSign& input) const {
        uint64_t X = math::mulmod(math::powmod(pub_k.g, input.s2, pub_k.p), math::powmod(pub_k.y, input.s1, pub_k.p), pub_k.p);
        uint64_t H = std::hash<std::string>{}(input.M) + std::hash<uint64_t>{}(X);

        return H == input.s1;
    }

    void Server::setNewMember(std::pair<public_key, std::string> member_info) {
        storage.push_back(member_info);
    }

    void Server::give_authentification_info(schnorr& Alice) {
        auth.e = math::getRandom64();
        Alice.auth.e = auth.e;
    }

    void Server::get_authentification_info(schnorr& Alice) {
        std::vector<uint64_t> input = Alice.give_authentification_info();
        auth.x = input[0];
        auth.s = input[1];
    }

    std::string Server::authentification(schnorr& Alice) {
        give_authentification_info(Alice);
        get_authentification_info(Alice);

        std::pair<public_key, std::string> found;
        for (auto& elem : storage) {
            if (Alice.pub_k == elem.first) {
                found = elem;
                break;
            }
        }

        if (auth.x == math::mulmod(math::powmod(found.first.g, auth.s, found.first.p), math::powmod(found.first.y, auth.e, found.first.p), found.first.p)) {
            return found.second;
        } else {
            std::string out("Impostor!");
            return out;
        }
    }

    messageSign schnorr::mSign;
} // namespace crypto