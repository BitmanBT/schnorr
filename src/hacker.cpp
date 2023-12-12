#include <hacker.h>
#include <nmath.h>

namespace crypto {
    hacker::hacker(const schnorr& Alice, const Server& Server) {
        pub_k = Alice.pub_k;
        forHacker = Server.auth;
    }

    void hacker::hack() {
        //TODO
    }
} // namespace crypto