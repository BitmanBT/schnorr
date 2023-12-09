#include <schnorr.h>
#include <nmath.h>

namespace crypto {
    void schnorr::generateKeys() {
        pub_k.p = math::getBigPrime();  // p
        std::vector<uint64_t> factors = math::getPrimeFactors(pub_k.p-1);
        pub_k.q = factors[factors.size()-1];  // q
        pub_k.g = math::getGenerator(pub_k.p, pub_k.q);  // g
        pr_k.w = math::getRandomUpLimit(pub_k.q);  // w
        pub_k.y = math::powmod(pub_k.g, pub_k.q-pr_k.w, pub_k.p);  // y
    }

    std::vector<uint64_t>& schnorr::give_authentification_info() const {
        //TODO
    }

    void schnorr::sign(std::string& M) {
        //TODO
    }

    void schnorr::verify(const messageSign& input) const {
        //TODO
    }

    void Server::give_authentification_info(schnorr& Alice) const {
        //TODO
    }

    void Server::get_authentification_info(schnorr& Alice) {
        //TODO
    }

    std::string& Server::authentification(schnorr& Alice) {
        //TODO
    }
    
    public_key schnorr::pub_k;
    messageSign schnorr::mSign;
} // namespace crypto