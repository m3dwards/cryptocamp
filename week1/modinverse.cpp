#include <iostream>
#include <format>

// Fast modular exponentiation: computes base^exp mod m
long long modExp(long long base, long long exp, long long mod) {
    long long result = 1;
    base %= mod;
    while (exp > 0) {
        if (exp % 2 == 1)
            result = (result * base) % mod;
        base = (base * base) % mod;
        exp /= 2;
    }
    return result;
}

bool isPrime(long long n) {
    if (n < 2) return false;
    for (long long i = 2; i * i <= n; i++)
        if (n % i == 0) return false;
    return true;
}

// Fermat's little theorem: a^(p-1) ≡ 1 (mod p) for prime p
// Multiply both sides by a^-1: a^(p-2) ≡ a^-1 (mod p)
// So the inverse is a modular exponentiation, computed efficiently with square-and-multiply.
long long modInverse(long long a, long long p) {
    return modExp(a, p - 2, p);
}

int main() {
    long long a, p;
    std::cout << "Enter element a: ";
    std::cin >> a;
    std::cout << "Enter prime p: ";
    std::cin >> p;

    if (!isPrime(p)) {
        std::cout << std::format("Error: {} is not prime.\n", p);
        return 1;
    }

    long long inv = modInverse(a, p);
    std::cout << std::format("{}^-1 mod {} = {}\n", a, p, inv);
    std::cout << std::format("Verify: {} * {} mod {} = {}\n", a, inv, p, (a * inv) % p);
}
