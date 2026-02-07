#include <vector>

std::vector<long long> generateFibonacci(int n) {
    if (n <= 0) return {};
    if (n == 1) return {0};

    std::vector<long long> fib = {0, 1};
    for (int i = 2; i < n; i++) {
        fib.push_back(fib[i - 1] + fib[i - 2]);
    }
    return fib;
}