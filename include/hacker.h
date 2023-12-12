#pragma once

#include <data_structures.h>
#include <schnorr.h>

namespace crypto {
    class hacker : public schnorr
    {
    public:
        hacker(const schnorr& Alice, const Server& Server);

        void hack();

    private:
        authentification_info_server forHacker;
    };
} // namespace crypto