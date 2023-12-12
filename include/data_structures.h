#pragma once

#include <cstdint>
#include <ostream>
#include <vector>

namespace crypto {
    /**
     * Structure to store public key.
    */
    struct public_key
    {
        uint64_t p = 0;
        uint64_t q = 0;
        uint64_t g = 0;
        uint64_t y = 0;

        friend std::ostream& operator<<(std::ostream& os, public_key& obj);
        friend bool operator==(public_key& left, public_key& right);
    };

    /**
     * Structure to store private key.
    */
    struct private_key
    {
        uint64_t w;
    };

    /**
     * Structure to store information on schnorr class side while authentification.
    */
    struct authentification_info_schnorr
    {
        uint64_t e = 0;
    };

    /**
     * Structure to store information on server class side while authentification.
    */
    struct authentification_info_server
    {
        uint64_t e = 0;
        uint64_t x = 0;
        uint64_t s = 0;
    };

    /**
     * Structure to store digital signature of the message.
    */
    struct messageSign //Передать публичный ключ
    {
        public_key pub_k;
        std::string M;
        std::size_t s1;
        uint64_t s2;
    };
} // namespace crypto