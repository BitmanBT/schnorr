#pragma once

#include <cstdint>

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
    };

    /**
     * Structure to store private key.
    */
    struct private_key
    {
        uint64_t w;
    };

    /**
     * Structure to store information while establishing connection.
    */
    struct authentification_info
    {
        uint64_t r = 0;
        uint64_t x = 0;
        uint64_t e = 0;
        uint64_t s = 0;
    };

    /**
     * Structure to store digital signature of the message.
    */
    struct messageSign
    {
        uint64_t H;
        uint64_t s1;
        uint64_t s2;
    };
} // namespace crypto