#include <hacker.h>
#include <nmath.h>
#include <chrono>

using namespace std::chrono;

namespace crypto {
    const double stop = 30;

    hacker::hacker(const schnorr& Alice, const Server& Server) {
        pub_k = Alice.pub_k;
        forHacker = Server.auth;
    }

    double hacker::getPercentages() {
        return percentages;
    }

    int hacker::getPrivateKey() {
        return pr_k.w;
    }

    void hacker::hack() {
        auto start = high_resolution_clock::now();

        for (int i = 1; i < pub_k.q; i++) {
            if (forHacker.x == math::powmod(pub_k.g, i, pub_k.p)) {
                pr_k.w = (forHacker.s - i) * math::inversemod(forHacker.e, pub_k.q) % pub_k.q;
                break;
            }
            else {
                auto duration = duration_cast<seconds>(high_resolution_clock::now() - start);
                if (duration.count() >= stop) {
                    percentages = (static_cast<double>(i) / (static_cast<double>(pub_k.q - 1))) * 100;
                    break;
                }
            }
        }
    }
} // namespace crypto