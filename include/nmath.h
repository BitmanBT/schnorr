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
     * Returns large random number which is smaller than given up_limit.
     * 
     * @param up_limit up limit of random number generated
     * @return large random number smaller than up_limit
    */
    uint64_t getRandomUpLimit(uint64_t up_limit);

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
     * @param n max prime number which can be generated
    */
    void SieveOfEratosthenes(uint64_t n);

    /**
     * Randomly generates a prime candidate divisible by first primes.
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
     * @param to_test 64-bit prime candidate
     * @return If considered prime or not
    */
    bool MillerRabinTest(uint64_t to_test);

    /**
     * Generates 64-bit large random PRIME number.
     * 
     * @return 64-bit large random PRIME number
    */
    uint64_t getBigPrime();

    /**
     * Gives you a vector of all prime factors of a number.
     * 
     * Time complexity: O(sqrt(n)).
     * 
     * @param n a number which factors we are looking for
     * @return A vector of prime delimeters of a number
    */
    std::vector<uint64_t> getPrimeFactors(uint64_t n);

    /**
     * Function to return gcd of a and b.
     * 
     * @return gcd of a and b
    */
    uint64_t gcd(uint64_t a, uint64_t b);

    /**
     * Function to find modular inverse of a under modulo m
     * 
     * @remark m should be prime
     * 
     * @return modular inverse of a under modulo m
    */
    uint64_t inversemod(uint64_t a, uint64_t m);

    /**
     * Returns generator of cyclic subgroup.
     * 
     * @param p field size
     * @param q subgroup size
     * @return Generator of cyclic subgroup
    */
    uint64_t getGenerator(uint64_t p, uint64_t q);
} // namespace math