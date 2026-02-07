#include <iostream>
#include <vector>

std::vector<int> getPrimesUpTo(int limit) {
    if (limit < 2) return {};

    // Boolean vector initialized to true
    std::vector<bool> isPrime(limit + 1, true);
    isPrime[0] = isPrime[1] = false;

    for (int p = 2; p * p <= limit; p++) {
        if (isPrime[p]) {
            for (int i = p * p; i <= limit; i += p)
                isPrime[i] = false;
        }
    }

    std::vector<int> primes;
    for (int p = 2; p <= limit; p++) {
        if (isPrime[p]) primes.push_back(p);
    }
    return primes;
}