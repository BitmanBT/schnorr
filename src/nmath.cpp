#include <nmath.h>

#include <cstdint>
#include <cmath>
#include <random>
#include <cstring>
#include <bitset>

namespace math {
    std::vector<uint64_t> first_primes;

    uint64_t getRandom64() {
        // the value need to be 63 bits because you can not using 64 bit values do a^2 which is needed
        constexpr int bits = 63;
        std::bitset<bits> a;

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<short> distr(0, 1);

        for (int i = 0; i < bits; i++) {
            a[i] = distr(gen);
        }

        a[0] = 1;
        a[bits - 1] = 1;

        return a.to_ullong();
    }

    uint64_t getRandomUpLimit(uint64_t up_limit) {
        return getRandom64() % up_limit;
    }

    void SieveOfEratosthenes(uint64_t n) {
        // Create a boolean array "prime[0..n]" and initialize 
        // all entries it as true. A value in prime[i] will 
        // finally be false if i is Not a prime, else true. 
        bool* prime = new bool[n + 1];
        memset(prime, true, sizeof(prime));

        for (uint64_t p = 2; p * p <= n; p++) {
            // If prime[p] is not changed, then it is a prime 
            if (prime[p] == true) {
                // Update all multiples of p greater than or 
                // equal to the square of it numbers which are 
                // multiple of p and are less than p^2 are 
                // already been marked. 
                for (uint64_t i = p * p; i <= n; i += p)
                    prime[i] = false;
            }
        }

        // Save all numbers to first_primes vector 
        for (uint64_t p = 2; p <= n; p++)
            if (prime[p])
                first_primes.push_back(p);
    }

    uint64_t getLowLevelPrime() {
        //  Repeat until a number satisfying 
        //  the test isn't found 
        while (true)
        {
            uint64_t candidate = getRandom64();
            bool is_prime = true;
            for (int i = 0; i < first_primes.size(); i++) {
                if (candidate == first_primes[i])
                    return candidate;

                if (candidate % first_primes[i] == 0) {
                    is_prime = false;
                    break;
                }
            }
            if (is_prime)
                return candidate;
        }
    }

    uint64_t powmod(uint64_t a, uint64_t b, uint64_t mod) {
        uint64_t x = 1;

        a %= mod;

        while (b > 0) {
            if (b % 2 == 1) {
                x = mulmod(x, a, mod); // multiplying with base
            }
            a = mulmod(a, a, mod); // squaring the base
            b >>= 1;
        }
        return x % mod;
    }

    uint64_t mulmod(uint64_t a, uint64_t b, uint64_t mod) {
        uint64_t res = 0; // Initialize result
        a = a % mod;
        while (b > 0)
        {
            // If b is odd, add 'a' to result
            if (b % 2 == 1)
                res = (res + a) % mod;
    
            // Multiply 'a' with 2
            a = (a * 2) % mod;
    
            // Divide b by 2
            b /= 2;
        }
    
        // Return result
        return res % mod;
    }

    bool trialComposite(uint64_t a, uint64_t evenC, uint64_t to_test, int max_div_2) {
        if (powmod(a, evenC, to_test) == 1)
            return false;

        for (int i = 0; i < max_div_2; i++) {
            uint64_t temp = static_cast<uint64_t>(1) << i;
            if (powmod(a, temp * evenC, to_test) == to_test - 1)
                return false;
        }

        return true;
    }

    bool MillerRabinTest(uint64_t to_test) {
        constexpr int accuracy = 20;

        int max_div_2 = 0;
        uint64_t evenC = to_test - 1;
        while (evenC % 2 == 0) {
            evenC >>= 1;
            max_div_2++;
        }

        // random numbers init
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<uint64_t> distr(2, to_test);

        for (int i = 0; i < accuracy; i++) {
            uint64_t a = distr(gen);

            if (trialComposite(a, evenC, to_test, max_div_2)) {
                return false;
            }
        }

        return true;
    }

    uint64_t getBigPrime() {
        SieveOfEratosthenes(1000);
        while (true) {
            uint64_t candidate = getLowLevelPrime();
            if (MillerRabinTest(candidate))
                return candidate;
        }
    }

    std::vector<uint64_t> getPrimeFactors(uint64_t n) {
        std::vector<uint64_t> out;

        // Print the number of 2s that divide n  
        while (n % 2 == 0) {
            out.push_back(2);
            n = n / 2;
        }

        // n must be odd at this point. So we can skip  
        // one element (Note i = i +2)  
        for (uint64_t i = 3; i <= sqrt(n); i = i + 2) {
            // While i divides n, print i and divide n  
            while (n % i == 0) {
                out.push_back(i);
                n = n / i;
            }
        }

        // This condition is to handle the case when n  
        // is a prime number greater than 2  
        if (n > 2) {
            out.push_back(n);
        }

        return out;
    }

    uint64_t gcd(uint64_t a, uint64_t b) {
        if (a == 0)
            return b;
        return gcd(b % a, a);
    }

    uint64_t inversemod(uint64_t a, uint64_t m) {
        uint64_t g = gcd(a, m);
        if (g != 1) {
            return 0;
        }
        else {
            // If a and m are relatively prime, then modulo 
            // inverse is a^(m-2) mode m 
            return powmod(a, m - 2, m);
        }
    }

    uint64_t getGenerator(uint64_t p, uint64_t q) {
        return powmod(getRandomUpLimit(p), static_cast<uint64_t>((p - 1) / q), p);
    }
} // namespace math