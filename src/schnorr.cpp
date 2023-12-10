#include "schnorr.h"
#include "nmath.h"

#include <iostream>

namespace crypto {
    std::hash<std::string> hash_fn;

    void schnorr::generateKeys() {
        pub_k.p = math::getBigPrime();  // p
        std::vector<uint64_t> factors = math::getPrimeFactors(pub_k.p - 1);
        pub_k.q = factors[factors.size() - 1];  // q
        pub_k.g = math::getGenerator(pub_k.p, pub_k.q);  // g
        pr_k.w = math::getRandomUpLimit(pub_k.q);  // w
        pub_k.y = math::powmod(pub_k.g, pub_k.q - pr_k.w, pub_k.p);  // y
    }

    std::vector<uint64_t>& schnorr::give_authentification_info() const {
        //TODO
        std::vector<uint64_t> X;
        return X;
    }

    void schnorr::sign(std::string& M) {
        mSign.M = M;

        uint64_t r = math::getRandomUpLimit(pub_k.q);
        uint64_t x = math::powmod(pub_k.g, r, pub_k.p);

        mSign.s1 = hash_fn(M + std::to_string(x));
        mSign.s2 = (r + math::mulmod(pr_k.w, mSign.s1, pub_k.q)) % pub_k.q;
    }

    bool schnorr::verify(const messageSign& input) const {
        uint64_t X = math::mulmod(math::powmod(pub_k.g, input.s2, pub_k.p), math::powmod(pub_k.y, input.s1, pub_k.p), pub_k.p);
        uint64_t H = hash_fn(input.M + std::to_string(X));

        return H == input.s1;
    }

    void Server::give_authentification_info(schnorr& Alice) const {
        //TODO
    }

    void Server::get_authentification_info(schnorr& Alice) {
        //TODO
    }

    std::string& Server::authentification(schnorr& Alice) {
        //TODO
        std::string Y;
        return Y;
    }

    public_key schnorr::pub_k;
    messageSign schnorr::mSign;
} // namespace crypto