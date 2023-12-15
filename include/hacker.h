#pragma once

#include <data_structures.h>
#include <schnorr.h>

namespace crypto {
    class hacker : public schnorr
    {
    public:
        hacker(const schnorr& Alice, const Server& Server);

        void hack();

        double getPercentages();

        int getPrivateKey();

    private:
        authentification_info_server forHacker;
        double percentages = 0;
        private_key pr_k;
    };
} // namespace crypto