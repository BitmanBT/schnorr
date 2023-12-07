#pragma once

#include <cstdint>
#include <vector>

namespace math {
    /**
     * Returns 64-bit large random number.
     * 
     * @return 64-bit large random number
    */
    uint64_t getRandom64();

    /**
     * Here we are going to store first prime numbers.
     * 
     * Is being filled with Eratosthen Sieve.
    */
    extern std::vector<uint64_t> first_primes;

    /**
     * Generates first prime numbers.
     * 
     * @remark Uses first_primes vector.
     * @param n - max prime number which can be generated
    */
    void SieveOfEratosthenes(uint64_t n);

    /**
     * Generate a prime candidate divisible by first primes.
     * 
     * (Low-Level Primality Test)
     * 
     * @return 64-bit prime candidate
    */
    uint64_t getLowLevelPrime();

    /**
     * Calculates (a ^ b) % mod.
     * 
     * @return (a ^ b) % mod
    */
    uint64_t powmod(uint64_t a, uint64_t b, uint64_t mod);

    /**
     * Calculates (a * b) % mod.
     * 
     * @return (a * b) % mod
    */
    uint64_t mulmod(uint64_t a, uint64_t b, uint64_t mod);

    //bool prime_test(uint64_t n, int num_tests = 20);

    /**
     * The kernel of the Rabin Miller Primality Test.
    */
    bool trialComposite(uint64_t a, uint64_t evenC, uint64_t to_test, int max_div_2);

    /**
     * Rabin Miller Primality Test.
     * 
     * (High-Level Primality Test)
     * 
     * @param to_test - 64-bit prime candidate
     * @return If considered prime or not
    */
    bool MillerRabinTest(uint64_t to_test);

    /**
     * Generates 64-bit large random PRIME number.
     * 
     * @return 64-bit large random PRIME number
    */
    uint64_t getBigPrime();
} // namespace math